
#include "wash.hpp"

#include <iostream>

#include "terminal_mode_interface.hpp"

void Wash::print_prompt() {
  emulator.add_input(env["PS1"]);
}

void Wash::input_key(char key, bool ctrl, bool alt, bool shift, bool meta) {
  std::cout << "key down!" << std::endl;
  if (ctrl)
    std::cout << "^";
  if (alt)
    std::cout << "<alt>";
  if (shift)
    std::cout << "<shift>";
  if (meta)
    std::cout << "<meta>";
  std::cout << key << std::endl;
  bool executing = false;
  {
    std::unique_lock<std::mutex> lock(buffer_mutex);
    executing = is_executing;
  }
  if (!executing) {
    if (key == '\b') {
      if (entered_chars.size() != 0) {
        entered_chars.pop_back();
        emulator.add_char('\b');
      }
    } else if (key == '\n') {
      std::cout << "entered command: " << entered_chars << std::endl;
      emulator.add_char('\n');
      update_terminal(emulator);

      // spin up a thread for command

      auto command_handler = [&]() {
        std::string command = entered_chars;
        {
          std::unique_lock<std::mutex> lock(buffer_mutex);
          is_executing = true;
          entered_chars = "";
        }
        execute_command(command, emulator);
        print_prompt();
        update_by_proxy(emulator);
        {
          std::unique_lock<std::mutex> lock(buffer_mutex);
          entered_chars = {begin(buffer), end(buffer)};
          emulator.add_input(entered_chars);
          update_by_proxy(emulator);
          buffer.clear();
          is_executing = false;
        }
      };
      std::thread t(command_handler);
      t.detach();
    } else {
      if (ctrl) {
        if (key >= 'a' && key <= 'z') {
          emulator.add_char('^');
          emulator.add_char(key);
          if (key == 'c') {
            // control C current command
            entered_chars = "";
            emulator.add_char('\n');
            print_prompt();
            update_terminal(emulator);
          }
        }
      } else {
        entered_chars.push_back(key);
        emulator.add_char(key);
      }
    }
  } else {
    std::unique_lock<std::mutex> lock(buffer_mutex);
    if (ctrl) {
      if (key >= 'a' && key <= 'z') {
        emulator.add_char('^');
        emulator.add_char(key);
        buffer.push_back(key - 'a' + 1);
        buffer_cv.notify_all();
      }
    } else {
      emulator.add_char(key);
      update_terminal(emulator);
      buffer.push_back(key);
      buffer_cv.notify_all();
    }
  }
  std::cout << "end input key" << std::endl;
  update_terminal(emulator);
}

std::set<char> parse_options(int argc, char *const argv[], const char *short_opts, struct option long_opts[]) {
  std::set<char> result;
  while (1) {
    int option_index = 0;
    int c = getopt_long(argc, argv, short_opts, long_opts, &option_index);
    if (c == -1)
      break;
    result.insert(static_cast<char>(c));
  }
  return result;
}

std::string parse_escaped_string(const std::string &escaped) {
  std::string result;
  result.reserve(escaped.size());
  for (size_t i = 1; i < size(escaped);) {
    if (escaped[i] == '\\') {
      // \n
      // \t
      // \\
      // \'
      // \"
      ++i;
      if (i < escaped.size()) {
        switch (escaped[i]) {
        case 'n':
          result += '\n';
          break;
        case 't':
          result += '\t';
          break;
        case 'e':
          result += '\e';
          break;
        case '\\':
          result += '\\';
          break;
        case '\'':
          result += '\'';
          break;
        case '"':
          result += '\"';
          break;
        case 'x': {
          if (i + 2 >= escaped.size())
            return result;
          char c = 0;
          if (escaped[i + 1] >= '0' && escaped[i + 1] <= '9') {
            c += (escaped[i + 1] - '0') << 4;
          } else if (escaped[i + 1] % 32 <= 6 && escaped[i + 1] >= 'A') {
            c += ((escaped[i + 1] - 'A') % 32) << 4;
          }

          if (escaped[i + 2] >= '0' && escaped[i + 2] <= '9') {
            c += (escaped[i + 2] - '0');
          } else if (escaped[i + 2] % 32 <= 6 && escaped[i + 2] >= 'A') {
            c += ((escaped[i + 2] - 'A') % 32);
          }
          result += c;
          i += 3;
        } break;
        case '0':
          // octal
          {
            char c = 0;
            int num_digits = 0;
            ++i;
            while (i < escaped.size() && escaped[i] >= '0' && escaped[i] <= '7' && num_digits < 3) {
              c <<= 3;
              c |= (escaped[i++] - '0');
              ++num_digits;
            }
            result += c;
          }
          break;
        default:
          break;
        }
      } else {
        result += '\\';
      }
    } else {
      result += escaped[i++];
    }
  }
  return result;
}
