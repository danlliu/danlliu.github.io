#pragma once

#include <string>

#include "terminal_emulator.hpp"

extern "C" {
  extern void set_terminal(char*);
}

inline void update_terminal(TerminalEmulator& emulator) {
  std::string value = emulator.to_html();
  char* ptr = new char[value.size() + 1];
  memcpy(ptr, value.c_str(), value.size() + 1);
  set_terminal(ptr);
}
