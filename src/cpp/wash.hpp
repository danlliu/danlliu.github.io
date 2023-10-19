#pragma once

/*
                   _
__      ____ _ ___| |__
\ \ /\ / / _` / __| '_ \
 \ V  V / (_| \__ \ | | |
  \_/\_/ \__,_|___/_| |_|

the WebAssembly SHell
*/

#include <iostream>

#include "terminal_emulator.hpp"

class Wash {
public:
  Wash(TerminalEmulator &emulator) : emulator(emulator), env{} {
    // environment variables
    env["PS1"] = "\e[36mdaniel\e[37m@\e[34mdanlliu.github.io\e[0m % ";
    env["SHELL"] = "/bin/wash";
    print_prompt();
  }

  void input_key(char key, bool ctrl, bool alt, bool shift, bool meta);

private:
  TerminalEmulator &emulator;
  std::unordered_map<std::string, std::string> env;

  std::string entered_chars = "";

  void print_prompt();
};

std::string parse_escaped_string(const std::string &escaped);

template <typename instream, typename outstream>
bool try_builtin(const std::vector<std::string> &argv, instream &input, outstream &output) {
  std::cout << "args:" << std::endl;
  for (auto arg : argv) {
    std::cout << "- " << arg << std::endl;
  }
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
  return false;
}

template <typename instream, typename outstream>
void execute_command(const std::string &command, instream &input, outstream &output) {
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
  if (try_builtin(args, input, output)) {
  } else {
    output << "unrecognized command " << args[0] << "\n";
  }
}
