
#include "wash.hpp"

#include <iostream>

#include "terminal_mode_interface.hpp"

void Wash::print_prompt() {
  emulator.add_input(env["PS1"]);
}

void Wash::input_key(char key, bool ctrl, bool alt, bool shift, bool meta) {
  if (key == '\b') {
    if (entered_chars.size() != 0) {
      entered_chars.pop_back();
      emulator.add_char('\b');
    }
  } else if (key == '\n') {
    std::cout << "entered command: " << entered_chars << std::endl;
    emulator.add_char('\n');
    // call command

    execute_command(entered_chars, key, emulator);
    update_terminal(emulator);

    print_prompt();
    entered_chars = "";
  } else {
    entered_chars.push_back(key);
    emulator.add_char(key);
  }

  update_terminal(emulator);
}

std::set<char> parse_options(int argc, char* const argv[], const char* short_opts, struct option long_opts[]) {
  std::set<char> result;
  while (1) {
    int option_index = 0;
    int c = getopt_long(argc, argv, short_opts, long_opts, &option_index); 
    if (c == -1) break;
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
