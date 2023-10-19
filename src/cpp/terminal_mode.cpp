
#include <iostream>

#include "terminal_emulator.hpp"
#include "terminal_mode_interface.hpp"

TerminalEmulator emulator;

void update_terminal() {
  std::string value = emulator.to_html();
  char* ptr = new char[value.size() + 1];
  memcpy(ptr, value.c_str(), value.size() + 1);
  set_terminal(ptr);
}

extern "C" {
  void key_pressed(char key, bool ctrl, bool alt, bool shift, bool meta) {
    emulator.add_char(key);
    update_terminal();
  }
}

int main() {
  emulator.add_input("\e[36mdaniel\e[37m@\e[34mdanlliu.github.io\e[0m % ");
  update_terminal();
}
