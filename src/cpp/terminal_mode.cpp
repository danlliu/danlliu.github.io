
#include <iostream>

#include "terminal_emulator.hpp"
#include "terminal_mode_interface.hpp"
#include "wash.hpp"

TerminalEmulator emulator;
Wash shell(emulator);

extern "C" {
  void key_pressed(char key, bool ctrl, bool alt, bool shift, bool meta) {
    shell.input_key(key, ctrl, alt, shift, meta);
  }
}

int main() {
  update_terminal(emulator);
}
