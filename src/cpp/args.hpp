
// thanks @brenfwd!

#pragma once

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

class Args {
private:
  struct Arg {
    char short_option = '\0';
    std::string long_option = "";
    bool required = false;
    bool has_value = false;
    std::string description = "";
    std::string placeholder = "";
  };

  class Parsed {
  private:
    Arg _arg;
    std::string _value;

  public:
    Parsed(Arg &arg, const std::string &value) : _arg(arg), _value(value) {}

    char short_option() const {
      return _arg.short_option;
    }

    std::string long_option() const {
      return _arg.long_option;
    }

    std::string value() const {
      return _value;
    }
  };

  struct ParseResult {
    bool ok = true;
    std::vector<std::string> positionals;
    std::vector<Parsed> parsed;

    bool has(const std::string &long_option) const {
      for (const auto &p : parsed) {
        if (p.long_option() == long_option)
          return true;
      }
      return false;
    }

    bool has(char short_option) const {
      for (const auto &p : parsed) {
        if (p.short_option() == short_option)
          return true;
      }
      return false;
    }

    // Returns the raw string value passed in to an option
    // For options that were not specified, or options with no value taken,
    // this will return an empty string.
    std::string value(const std::string &long_option) const {
      for (const auto &p : parsed) {
        if (p.long_option() == long_option)
          return p.value();
      }
      return "";
    }

    std::string value(char short_option) const {
      for (const auto &p : parsed) {
        if (p.short_option() == short_option)
          return p.value();
      }
      return "";
    }
  };

public:
  class ArgBuilder {
  private:
    Arg arg;

  public:
    ArgBuilder(const std::string &p_long_option = "", char p_short_option = '\0') {
      arg.long_option = p_long_option;
      arg.short_option = p_short_option;
    }

    ArgBuilder &short_option(char v) {
      arg.short_option = v;
      return *this;
    }

    ArgBuilder &long_option(const std::string &v) {
      arg.long_option = v;
      return *this;
    }

    ArgBuilder &required(bool v = true) {
      arg.required = v;
      return *this;
    }

    ArgBuilder &has_value(bool v = true) {
      arg.has_value = v;
      return *this;
    }

    ArgBuilder &description(const std::string &v) {
      arg.description = v;
      return *this;
    }

    ArgBuilder &placeholder(const std::string &v) {
      arg.placeholder = v;
      return *this;
    }

    const Arg to_arg() const {
      assert(arg.required ? arg.has_value : true);
      assert((arg.placeholder != "") == (arg.has_value));
      return arg; // copy
    }
  };

private:
  std::vector<Arg> args;
  std::string _description;
  int _num_positionals = 0;
  int _num_positionals_required = 0;

public:
  Args &description(const std::string &v) {
    _description = v;
    return *this;
  }

  Args &add_arg(const ArgBuilder &builder) {
    args.push_back(builder.to_arg());
    return *this;
  }

  Args &num_positionals(int n) {
    assert(n >= 0);
    _num_positionals = n;
    return *this;
  }

  Args &num_positional_required(int n) {
    assert(n >= 0);
    assert(n <= _num_positionals);
    _num_positionals_required = n;
    return *this;
  }

private:
  bool arg_by_short_option(char c, Arg &a) {
    for (const auto &arg : args) {
      if (arg.short_option == c) {
        a = arg;
        return true;
      }
    }
    return false;
  }

  bool arg_by_long_option(const std::string &str, Arg &a) {
    for (const auto &arg : args) {
      if (arg.long_option == str) {
        a = arg;
        return true;
      }
    }
    return false;
  }

  bool consume_next(int argc, const char *argv[], int &i, std::string &r) {
    if (i + 1 >= argc) {
      return false;
    }
    r = std::string(argv[++i]);
    return true;
  }

public:
  ParseResult parse(int argc, const char *argv[]) {
    ParseResult result;

    for (int i = 1; i < argc; ++i) {
      if (!result.ok)
        break;

      std::string arg(argv[i]);

      if (arg[0] != '-') {
        handlePositional(arg, result);
      } else if (arg == "--") {
        break;
      } else {
        handleOption(argc, argv, i, arg, result);
      }
    }

    if (result.positionals.size() < (size_t)_num_positionals_required) {
      result.ok = false;
    }

    return result;
  }

private:
  void handlePositional(const std::string &arg, ParseResult &result) {
    if (result.positionals.size() >= (size_t)_num_positionals) {
      result.ok = false;
    } else {
      result.positionals.push_back(arg);
    }
  }

  void handleOption(int argc, const char *argv[], int &i, const std::string &arg, ParseResult &result) {
    if (arg[1] != '-') {
      handleShortOption(argc, argv, i, arg, result);
    } else {
      handleLongOption(argc, argv, i, arg, result);
    }
  }

  void handleShortOption(int argc, const char *argv[], int &i, const std::string &arg, ParseResult &result) {
    for (size_t j = 1; j < arg.size(); ++j) {
      char c = arg[j];
      Arg a;
      if (!isalnum(c) || !arg_by_short_option(c, a)) {
        result.ok = false;
        return;
      }

      std::string v;
      if (a.has_value && !consume_next(argc, argv, i, v)) {
        result.ok = false;
        return;
      }

      if (result.has(a.long_option)) {
        result.ok = false;
        return;
      }
      result.parsed.emplace_back(a, v);
    }
  }

  void handleLongOption(int argc, const char *argv[], int &i, const std::string &arg, ParseResult &result) {
    std::string long_option = arg.substr(2);
    Arg a;

    if (!arg_by_long_option(long_option, a)) {
      result.ok = false;
      return;
    }

    std::string v;
    if (a.has_value && !consume_next(argc, argv, i, v)) {
      result.ok = false;
      return;
    }

    if (result.has(a.long_option)) {
      result.ok = false;
      return;
    }
    result.parsed.emplace_back(a, v);
  }
};
