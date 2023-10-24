
#pragma once

#include <deque>
#include <mutex>
#include <sstream>
#include <thread>
#include <vector>

// ANSI Escape Codes:
// - 0: reset
// - 1: bold
// - 2: lightweight
// - 3: italic
// - 4: underline
// - 9: strikethrough
// - 21: double underline
// - 22: normal intensity
// - 23: reset italic
// - 24: not underlined
// - 29: not crossed out
// Colors:
// - 30 / 40: black
// - 31 / 41: red
// - 32 / 42: green
// - 33 / 43: yellow
// - 34 / 44: blue
// - 35 / 45: purple
// - 36 / 46: aqua
// - 37 / 47: white

struct TerminalCell {
  uint64_t ansi = 0;
  uint8_t fg256 = 0;
  uint8_t bg256 = 0;
  char character = ' ';
};
std::ostream& operator<<(std::ostream& os, const TerminalCell &cell);

class TerminalEmulator {
public:
  TerminalEmulator(size_t height = 32, size_t width = 120)
      : cells(height, std::vector<TerminalCell>(width, TerminalCell{})), height(height), width(width), ansi_mode(0), cursor_row(0), cursor_col(0) {}

  std::string to_html();
  void add_char(char c);
  void add_input(const std::string &i);

private:
  friend class Wash;
  template <typename T>
  friend TerminalEmulator& operator<<(TerminalEmulator& os, T x);

  std::mutex lock;
  std::deque<std::vector<TerminalCell>> cells;
  size_t height = 0;
  size_t width = 0;
  uint64_t ansi_mode = 0;
  uint8_t ansi_fg_256 = 0;
  uint8_t ansi_bg_256 = 0;
  size_t cursor_row = 0;
  size_t cursor_col = 0;

  void move_cursor(int drow, int dcol);
  void set_cursor_to(char c);
};

#include <iostream>

template <typename T>
TerminalEmulator& operator<<(TerminalEmulator& os, T x) {
  std::cout << "operator<< on terminalemulator" << std::endl;
  std::ostringstream oss;
  oss << x;
  std::cout << "pre add input" << std::endl;
  os.add_input(oss.str());
  std::cout << "post add input" << std::endl;
  return os;
}
