
#include "terminal_emulator.hpp"

#include <iomanip>
#include <iostream>

constexpr int BOLD = 1L << 0;
constexpr int LIGHT = 1L << 1;
constexpr int ITALIC = 1L << 2;
constexpr int UNDERLINE = 1L << 3;
constexpr int STRIKETHROUGH = 1L << 4;
constexpr int DUNDER = 1L << 5;

constexpr int FG_BLACK = 1L << 6;
constexpr int FG_RED = 1L << 7;
constexpr int FG_GREEN = 1L << 8;
constexpr int FG_YELLOW = 1L << 9;
constexpr int FG_BLUE = 1L << 10;
constexpr int FG_PURPLE = 1L << 11;
constexpr int FG_AQUA = 1L << 12;
constexpr int FG_WHITE = 1L << 13;
constexpr int FG_256 = 1L << 14;

constexpr int FG_GRAY = 1L << 15;

constexpr int CLEAR_FG =
    ~(FG_BLACK | FG_RED | FG_GREEN | FG_YELLOW | FG_BLUE | FG_PURPLE | FG_AQUA | FG_WHITE | FG_GRAY | FG_256);

constexpr int BG_BLACK = 1L << 16;
constexpr int BG_RED = 1L << 17;
constexpr int BG_GREEN = 1L << 18;
constexpr int BG_YELLOW = 1L << 19;
constexpr int BG_BLUE = 1L << 20;
constexpr int BG_PURPLE = 1L << 21;
constexpr int BG_AQUA = 1L << 22;
constexpr int BG_WHITE = 1L << 23;
constexpr int BG_256 = 1L << 24;

constexpr int CLEAR_BG = ~(BG_BLACK | BG_RED | BG_GREEN | BG_YELLOW | BG_BLUE | BG_PURPLE | BG_AQUA | BG_WHITE | BG_256);

constexpr int CURSOR = 1L << 30;

inline std::string color_256_class(uint8_t val, std::string prefix) {
  switch (val) {
    case 0:
      return prefix + "black";
    case 8:
      return prefix + "gray";
    case 1:
    case 9:
      return prefix + "red";
    case 2:
    case 10:
      return prefix + "green";
    case 3:
    case 11:
      return prefix + "yellow";
    case 4:
    case 12:
      return prefix + "blue";
    case 5:
    case 13:
      return prefix + "purple";
    case 6:
    case 14:
      return prefix + "aqua";
    case 7:
    case 15:
      return prefix + "white";
    default:
      return "";
  }
}

std::string color_256_style(uint8_t val) {
  if (val < 16) return "";
  if (val < 232) {
    uint8_t base = val - 16;
    uint8_t r = base / 36;
    uint8_t g = (base / 6) % 6;
    uint8_t b = base % 6;
    r *= 51;
    g *= 51;
    b *= 51;
    std::ostringstream oss;
    oss << std::setbase(16) << std::setfill('0');
    oss << std::setw(2) << (int)r;
    oss << std::setw(2) << (int)g;
    oss << std::setw(2) << (int)b;
    return oss.str();
  }
  uint8_t base = val - 232;
  uint8_t gray = base * 10 + 8;
  std::ostringstream oss;
  oss << std::setbase(16) << std::setfill('0');
  oss << std::setw(2) << (int)gray;
  oss << std::setw(2) << (int)gray;
  oss << std::setw(2) << (int)gray;
  return oss.str();
}

std::ostream &operator<<(std::ostream &os, const TerminalCell &cell) {
  os << "<span class=\"";
  if (cell.ansi & BOLD)
    os << "font-bold ";
  if (cell.ansi & LIGHT)
    os << "font-light ";
  if (cell.ansi & ITALIC)
    os << "italic ";
  if (cell.ansi & UNDERLINE)
    os << "underline ";
  if (cell.ansi & STRIKETHROUGH)
    os << "line-through";
  if (cell.ansi & DUNDER)
    os << "underline decoration-double ";
  if (cell.ansi & FG_BLACK)
    os << "text-black ";
  if (cell.ansi & FG_RED)
    os << "text-red ";
  if (cell.ansi & FG_GREEN)
    os << "text-green ";
  if (cell.ansi & FG_YELLOW)
    os << "text-yellow ";
  if (cell.ansi & FG_BLUE)
    os << "text-blue ";
  if (cell.ansi & FG_PURPLE)
    os << "text-purple ";
  if (cell.ansi & FG_AQUA)
    os << "text-aqua ";
  if (cell.ansi & FG_WHITE)
    os << "text-white ";
  if (cell.ansi & FG_GRAY)
    os << "text-gray ";
  if (cell.ansi & BG_BLACK)
    os << "bg-black ";
  if (cell.ansi & BG_RED)
    os << "bg-red ";
  if (cell.ansi & BG_GREEN)
    os << "bg-green ";
  if (cell.ansi & BG_YELLOW)
    os << "bg-yellow ";
  if (cell.ansi & BG_BLUE)
    os << "bg-blue ";
  if (cell.ansi & BG_PURPLE)
    os << "bg-purple ";
  if (cell.ansi & BG_AQUA)
    os << "bg-aqua ";
  if (cell.ansi & BG_WHITE)
    os << "bg-white ";
  if (cell.ansi & CURSOR)
    os << "bg-gray/50 ";
  if (cell.ansi & FG_256)
    os << color_256_class(cell.fg256, "text-") << " ";
  if (cell.ansi & BG_256)
    os << color_256_class(cell.bg256, "bg-") << " ";
  os << "\" style=\"";
  if (cell.ansi & FG_256)
    os << "color:#" << color_256_style(cell.fg256) << ";";
  if (cell.ansi & BG_256)
    os << "background-color:#" << color_256_style(cell.bg256) << ";";
  os << "\">";
  if (cell.character == '>')
    os << "&gt;";
  else if (cell.character == '<')
    os << "&lt;";
  else if (cell.character == '&')
    os << "&amp;";
  else if (cell.character == '"')
    os << "&quot;";
  else if (cell.character == '\'')
    os << "&#39;";
  else
    os << cell.character;
  os << "</span>";
  return os;
}

std::string TerminalEmulator::to_html() {
  std::stringstream oss;
  size_t row = 0;
  for (auto &r : cells) {
    size_t col = 0;
    for (auto c : r) {
      if (row == cursor_row && col == cursor_col)
        c.ansi |= CURSOR;
      oss << c;
      ++col;
    }
    oss << "\n";
    ++row;
  }
  return oss.str();
}

void TerminalEmulator::add_char(char c) {
  std::unique_lock<std::mutex> hold(lock);
  if (c == '\n') {
    cursor_col = 0;
    if (cursor_row == cells.size() - 1) {
      cells.push_back(std::vector<TerminalCell>(width, TerminalCell{}));
      cells.pop_front();
    } else {
      cursor_row += 1;
    }
  } else if (c == '\t') {
    for (int i = 0; i < 4; ++i)
      add_char(' ');
  } else if (c == '\b') {
    if (cursor_col)
      cursor_col -= 1;
    else {
      if (cursor_row) {
        cursor_col = width - 1;
        cursor_row -= 1;
      }
    }
    cells[cursor_row][cursor_col] = {0, 0, 0, ' '};
  } else {
    cells[cursor_row][cursor_col] = {ansi_mode, ansi_fg_256, ansi_bg_256, c};
    cursor_col++;
    if (cursor_col >= width)
      add_char('\n');
  }
}

void TerminalEmulator::add_input(const std::string &input) {
  for (size_t i = 0; i < input.size();) {
    if (input[i] == '\033') {
      // begin ANSI
      ++i;
      // [
      ++i;
      std::string params;
      std::string intermediate;
      char final;
      // parse params
      while (0x30 <= input[i] && input[i] <= 0x3f) {
        params += input[i++];
        if (i >= input.size())
          return;
      }
      while (0x20 <= input[i] && input[i] <= 0x2f) {
        intermediate += input[i++];
        if (i >= input.size())
          return;
      }

      if (0x40 <= input[i] && input[i] <= 0x7e) {
        final = input[i++];
      } else {
        continue;
      }
      // handle ANSI

      std::istringstream iss(params);
      std::unique_lock<std::mutex> hold(lock);

      switch (final) {
      case 'A': {
        // CUU
        int n = std::stoi(params);
        if (cursor_row <= n)
          cursor_row = 0;
        else
          cursor_row -= n;
      } break;
      case 'B': {
        // CUD
        int n = std::stoi(params);
        if (cursor_row >= height - n)
          cursor_row = height - 1;
        else
          cursor_row += n;
      } break;
      case 'C': {
        // CUF
        int n = std::stoi(params);
        if (cursor_col >= width - n)
          cursor_col = height - 1;
        else
          cursor_col += n;
      } break;
      case 'D': {
        // CUB
        int n = std::stoi(params);
        if (cursor_col <= n)
          cursor_col = 0;
        else
          cursor_col -= n;
      } break;
      case 'E': {
        // CNL
        int n = std::stoi(params);
        if (cursor_row >= height - n)
          cursor_row = height - 1;
        else
          cursor_row += n;
        cursor_col = 0;
      } break;
      case 'F': {
        // CPL
        int n = std::stoi(params);
        if (cursor_row <= n)
          cursor_row = 0;
        else
          cursor_row -= n;
        cursor_col = 0;
      } break;
      case 'G': {
        // CHA
        int n = std::stoi(params);
        if (n < 1 || n > width) break;
        cursor_col = n - 1;
      } break;
      case 'H': {
        // CUP
        int n = 1;
        int m = 1;
        {
          std::string first, second;
          size_t i = 0;
          for (; i < size(params); ++i) {
            if (params[i] == ';') ++i;
            first += params[i];
          }
          for (; i < size(params); ++i) {
            second += params[i];
          }

          if (!first.empty()) n = std::stoi(first);
          if (!second.empty()) m = std::stoi(second);
        }
        // bounds checking
        if (n < 1 || n > height) break;
        if (m < 1 || m > width) break;
        cursor_row = n - 1;
        cursor_col = m - 1;
      } break;
      case 'J': {
        // ED
        int n = params.size() ? std::stoi(params) : 0;
        switch (n) {
          case 0:
            // clear until end of display
            {
              int r = cursor_row, c = cursor_col;
              while (r < height && c < width) {
                cells[r][c] = {0, 0, 0, ' '};
                ++c;
                if (c == width) {
                  c = 0;
                  ++r;
                }
              }
            }
            break;
          case 1:
            // clear to beginning of display
            {
              int r = cursor_row, c = cursor_col;
              while (r >= 0 && c >= 0) {
                cells[r][c] = {0, 0, 0, ' '};
                --c;
                if (c == 0) {
                  c = width - 1;
                  --r;
                }
              }
            }
            break;
          case 2:
            // clear entire screen, move to top left
            {
              for (size_t r = 0; r < height; ++r) {
                for (size_t c = 0; c < width; ++c) {
                  cells[r][c] = {0, 0, 0, ' '};
                }
              }
              cursor_row = 0;
              cursor_col = 0;
            }
            break;
        }
      } break;
      // TODO: remaining ANSI control codes
      case 'm': {
        // SGR
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
        // - 38 / 48: 256 bit
        // - 39 / 49: default fg/bg
        // - 90 : gray text

        // parse parameters into integers
        std::vector<int> param_ints;
        {
          std::size_t pos{};
          while (pos < size(params)) {
            try {
              std::size_t len{};
              int val = std::stoi(params.substr(pos), &len);
              param_ints.push_back(val);
              pos += len;
              ++pos;
            } catch (std::invalid_argument) {
              break;
            }
          }
        }

        int n = param_ints[0];
        switch (n) {
        case 0:
          ansi_mode = 0;
          break;
        case 1:
          ansi_mode |= BOLD;
          break;
        case 2:
          ansi_mode |= LIGHT;
          break;
        case 3:
          ansi_mode |= ITALIC;
          break;
        case 4:
          ansi_mode |= UNDERLINE;
          break;
        case 9:
          ansi_mode |= STRIKETHROUGH;
          break;
        case 21:
          ansi_mode |= DUNDER;
          break;
        case 22:
          ansi_mode &= ~(BOLD | LIGHT);
          break;
        case 23:
          ansi_mode &= ~ITALIC;
          break;
        case 24:
          ansi_mode &= ~UNDERLINE;
          break;
        case 29:
          ansi_mode &= ~STRIKETHROUGH;
          break;
        case 30:
          ansi_mode &= CLEAR_FG;
          ansi_mode |= FG_BLACK;
          break;
        case 31:
          ansi_mode &= CLEAR_FG;
          ansi_mode |= FG_RED;
          break;
        case 32:
          ansi_mode &= CLEAR_FG;
          ansi_mode |= FG_GREEN;
          break;
        case 33:
          ansi_mode &= CLEAR_FG;
          ansi_mode |= FG_YELLOW;
          break;
        case 34:
          ansi_mode &= CLEAR_FG;
          ansi_mode |= FG_BLUE;
          break;
        case 35:
          ansi_mode &= CLEAR_FG;
          ansi_mode |= FG_PURPLE;
          break;
        case 36:
          ansi_mode &= CLEAR_FG;
          ansi_mode |= FG_AQUA;
          break;
        case 37:
        case 39:
          ansi_mode &= CLEAR_FG;
          ansi_mode |= FG_WHITE;
          break;
        case 38:
          ansi_mode &= CLEAR_FG;
          ansi_mode |= FG_256;
          // 38 ; 5 ; n
          ansi_fg_256 = param_ints[2];
          break;
        case 40:
        case 49:
          ansi_mode &= CLEAR_BG;
          ansi_mode |= BG_BLACK;
          break;
        case 41:
          ansi_mode &= CLEAR_BG;
          ansi_mode |= BG_RED;
          break;
        case 42:
          ansi_mode &= CLEAR_BG;
          ansi_mode |= BG_GREEN;
          break;
        case 43:
          ansi_mode &= CLEAR_BG;
          ansi_mode |= BG_YELLOW;
          break;
        case 44:
          ansi_mode &= CLEAR_BG;
          ansi_mode |= BG_BLUE;
          break;
        case 45:
          ansi_mode &= CLEAR_BG;
          ansi_mode |= BG_PURPLE;
          break;
        case 46:
          ansi_mode &= CLEAR_BG;
          ansi_mode |= BG_AQUA;
          break;
        case 47:
          ansi_mode &= CLEAR_BG;
          ansi_mode |= BG_WHITE;
          break;
        case 48:
          ansi_mode &= CLEAR_BG;
          ansi_mode |= BG_256;
          // 38 ; 5 ; n
          ansi_bg_256 = param_ints[2];
          break;
        case 90:
          ansi_mode &= CLEAR_FG;
          ansi_mode |= FG_GRAY;
          break;
        }
      } break;
      default:
        std::cerr << "Invalid final ANSI character!" << std::endl;
      }
    } else {
      add_char(input[i++]);
    }
  }
}

void TerminalEmulator::move_cursor(int drow, int dcol) {
  cursor_row += drow;
  cursor_col += dcol;
}

void TerminalEmulator::set_cursor_to(char c) {
  cells[cursor_row][cursor_col] = {ansi_mode, 0, 0, c};
}
