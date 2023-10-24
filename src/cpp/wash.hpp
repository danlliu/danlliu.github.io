#pragma once

/*
                   _
__      ____ _ ___| |__
\ \ /\ / / _` / __| '_ \
 \ V  V / (_| \__ \ | | |
  \_/\_/ \__,_|___/_| |_|

the WebAssembly SHell
*/

#include <condition_variable>
#include <deque>
#include <getopt.h>
#include <iostream>
#include <mutex>
#include <optional>
#include <set>
#include <sstream>
#include <thread>

using namespace std::literals::chrono_literals;

#include "args.hpp"
#include "filesystem.hpp"
#include "terminal_emulator.hpp"
#include "terminal_mode_interface.hpp"

std::string parse_escaped_string(const std::string &escaped);

std::set<char> parse_options(int argc, const char *argv[], const char *short_opts, struct option long_opts[]);

class Wash {
public:
  Wash(TerminalEmulator &emulator, Filesystem &fs) : emulator(emulator), fs(fs), env{} {
    // environment variables
    env["PS1"] = "\e[36mdaniel\e[37m@\e[34mdanlliu.github.io\e[0m % ";
    env["SHELL"] = "/bin/wash";
    print_prompt();

    cwd_ptr = fs.root.get();
  }

  void input_key(char key, bool ctrl, bool alt, bool shift, bool meta);

private:
  TerminalEmulator &emulator;
  Filesystem &fs;
  std::unordered_map<std::string, std::string> env;

  FilesystemPath cwd{};
  FSINode *cwd_ptr;
  std::string entered_chars = "";

  std::mutex buffer_mutex;
  std::condition_variable buffer_cv;
  bool is_executing = false;
  std::deque<char> buffer;

  char wait_for_char() {
    std::unique_lock<std::mutex> hold(buffer_mutex);
    buffer_cv.wait(hold, [&](){return buffer.size() > 0;});
    std::cout << "finished waiting!" << std::endl;
    char c = buffer.front();
    buffer.pop_front();
    return c;
  }

  std::optional<std::string> wait_for_line() {
    std::string result;
    while (char c = wait_for_char()) {
      // newline, ^C, or ^D
      if (c == '\n') {
        break;
      }
      if (c == 3 || c == 4) return {};
      if (c == '\b') {
        result.pop_back();
      } else {
        result.push_back(c);
      }
    }
    return result;
  }

  void print_prompt();

  template <typename outstream>
  bool try_builtin(const std::vector<std::string> &argv, outstream &output) {
    std::cout << "args:" << std::endl;

    auto argv_cstr = std::make_unique<const char *[]>(argv.size());
    for (size_t i = 0; i < argv.size(); ++i) {
      argv_cstr.get()[i] = argv[i].c_str();
    }

    for (auto arg : argv) {
      std::cout << "- " << arg << std::endl;
    }
    if (argv.size() == 0) {
      // empty command does nothing!
      return true;
    }

    // 0 argument commands
    // - clear
    // - pwd

    if (argv[0] == "clear") {
      output << "\033[2J";
      return true;
    }
    if (argv[0] == "pwd") {
      if (cwd.size() == 0) {
        output << "/\n";
        return true;
      }
      for (auto component : cwd) {
        output << "/" << component;
      }
      output << "\n";
      return true;
    }

    // non-path argument commands
    // - echo args... 
    // - sleep time

    if (argv[0] == "echo") {
      for (size_t i = 1; i < argv.size(); ++i) {
        if (i != 1) {
          output << " ";
        }
        output << argv[i];
      }
      output << "\n";
      return true;
    }
    if (argv[0] == "sleep") {
      int seconds = std::stoi(argv[1]);
      std::this_thread::sleep_for(seconds * 1s);
      return true;
    }

    // 1 path argument commands
    // - cat
    // - cd
    // - ls

    if (argv[0] == "cat") {
      if (argv.size() == 1) {
        // echo back input as we get it
        while (true) {
          auto c = wait_for_line();
          if (!c) break;
          output << *c << "\n";
          update_by_proxy(output);
        }
        output << "\n";
        return true;
      }
      auto new_path = compute_path(cwd, argv[1]);
      auto inode = fs.get_inode(new_path);
      if (inode->type == INodeType::INODE_FILE) {
        output << inode->content << "\n";
      } else {
        output << "cat <file>\n";
      }
      return true;
    }
    if (argv[0] == "cd") {
      if (argv.size() == 1) {
        output << "cd <directory>\n";
        return true;
      }
      auto new_path = compute_path(cwd, argv[1]);
      auto inode = fs.get_inode(new_path);
      if (inode->type == INodeType::INODE_DIR) {
        cwd = new_path;
      } else {
        output << "cd <directory>\n";
      }
      return true;
    }
    if (argv[0] == "ls") {
      Args ls_args;
      ls_args.add_arg(Args::ArgBuilder("all", 'a'));
      ls_args.add_arg(Args::ArgBuilder("", 'l'));
      ls_args.num_positionals(1);
      auto result = ls_args.parse(argv.size(), argv_cstr.get());

      bool all = result.has('a');
      bool long_mode = result.has('l');

      auto path = cwd;
      if (!result.positionals.empty()) {
        // edit path TODO
        auto arg_path = result.positionals[0];
        path = compute_path(path, arg_path);
      }

      auto inode = fs.get_inode(path);
      if (long_mode) {
        for (auto &[child, child_inode] : inode->get_children()) {
          if (child[0] == '.' && !all) continue;
          if (child_inode->type == INodeType::INODE_DIR) {
            output << "\033[34md\033[0m";
          } else {
            output << ".";
          }

          // r = 33
          // w = 31
          // x = 32
          for (size_t m = 9; m != 0; --m) {
            if (child_inode->perms & (1 << (m - 1))) {
              switch (m % 3) {
              case 0: // r
                output << "\033[33mr\033[0m";
                break;
              case 2: // w
                output << "\033[32mw\033[0m";
                break;
              case 1: // x
                output << "\033[31mx\033[0m";
                break;
              }
            } else
              output << "\033[90m-\033[0m";
          }

          output << " ";

          if (child_inode->type == INodeType::INODE_DIR) {
            output << "   \033[90m-\033[0m ";
          } else {
            std::string size = child_inode->file_size();
            for (size_t i = 0; i < 4 - size.size(); ++i) {
              output << " ";
            }
            output << size << " ";
          }
          if (child_inode->type == INodeType::INODE_DIR) {
            output << "\033[34m" << child << "\033[0m";
          } else if (child_inode->perms & 0111) {
            output << "\033[32m" << child << "\033[0m";
          } else {
            output << child;
          }
          output << "\n";
        }
      } else {
        for (auto &[child, child_inode] : inode->get_children()) {
          if (child[0] == '.' && !all) continue;
          if (child_inode->type == INodeType::INODE_DIR) {
            output << "\033[34m" << child << "\033[0m  ";
          } else if (child_inode->perms & 0111) {
            output << "\033[32m" << child << "\033[0m  ";
          } else {
            output << child << "  ";
          }
        }
        output << "\n";
      }
      return true;
    }

    return false;
  }

  template <typename outstream>
  void execute_command(const std::string &command, outstream &output) {
    std::vector<std::string> args;
    {
      std::string arg;
      char stringmode = 0;
      bool backslash = false;
      for (char c : command) {
        if (c == ' ' && stringmode == 0) {
          if (arg.size())
            args.emplace_back(arg);
          arg = "";
        } else {
          arg += c;
          if (stringmode != 0) {
            if (!backslash && c == stringmode)
              stringmode = 0;
          } else {
            if (!backslash && (c == '\'' || c == '\"')) {
              stringmode = c;
            }
          }
          backslash = c == '\\';
        }
      }
      if (arg.size())
        args.emplace_back(arg);
    }
    {
      for (auto &arg : args) {
        if (arg[0] == '\'' or arg[0] == '\"') {
          arg.pop_back();
          arg = parse_escaped_string(arg);
        }
      }
    }
    if (try_builtin(args, output)) {
    } else {
      output << "wash: unrecognized command " << args[0] << "\n";
    }
  }
};
