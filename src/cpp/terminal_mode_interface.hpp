#pragma once

#include <emscripten/proxying.h>
#include <string>

#include "terminal_emulator.hpp"

extern "C" {
  extern void set_terminal(char*);
}

extern pthread_t main_thread;
extern em_proxying_queue* proxy_queue;

inline void update_terminal(TerminalEmulator& emulator) {
  std::string value = emulator.to_html();
  char* ptr = new char[value.size() + 1];
  memcpy(ptr, value.c_str(), value.size() + 1);
  set_terminal(ptr);
}

inline void update_terminal_ptr(void* ptr) {
  update_terminal(*reinterpret_cast<TerminalEmulator*>(ptr));
}

inline void update_by_proxy(TerminalEmulator& emulator) {
  emscripten_proxy_sync(proxy_queue, main_thread, update_terminal_ptr, &emulator);
  std::cout << "finish update by proxy" << std::endl;
}
