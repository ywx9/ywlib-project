#pragma once
#include <ywlib>

#ifndef YWLIB_CMDLINE_KEY
#define YWLIB_CMDLINE_KEY "--"
#endif

namespace yw::main {

/// class for `yw::main::argv`
class Argv {
  inline static array<str> _argv = [](array<str> a, int i) {
    wchar_t** as = ::CommandLineToArgvW(::GetCommandLineW(), &i);
    for (int j = (a.reserve(i), 0); j < i; ++j) a.push_back(unicode<char>(as[j]));
    return a;
  }({}, {});
public:
  const str& operator[](size_t i) const { return _argv[i]; }
  static size_t size() { return _argv.size(); }
  static auto begin() { return _argv.begin(); }
  static auto end() { return _argv.end(); }
  template<size_t I> static const str& get() { return _argv[I]; }
  /// search a option (such as --input) and returns the next argument if found
  static str option(stringable auto&& name, const str& default_value) {
    auto it = std::ranges::find(_argv, unicode<char>(name));
    return (it != _argv.end() && ++it != _argv.end()) ? *it : default_value;
  }
  /// search a option (such as --input) and returns boolean if found
  static bool option(stringable auto&& name) {
    return std::ranges::find(_argv, unicode<char>(name)) != _argv.end();
  }
};

/// command line arguments
/// \note `yw::main::argv[0]` is the executable name.
/// \note `yw::main::argv[i]` is the `i`-th command line argument.
/// \note `yw::main::argv.option("--input", "default-str")` returns the argument after `--input`.
/// \note `yw::main::argv.option("--debug")` returns `true` if `--debug` is present.
inline const Argv argv{};
}
