#include <ywlib>

namespace yw {

enum class commandline_type {
  invalid,
  boolean,
  integer,
  value,
  string,
};

struct commandline_option {
  commandline_type type{};
  std::wstring name, desc;
};

namespace main {
inline std::unordered_map<commandline_option, std::variant<bool, int, double, std::wstring>> args = [](int i) {
  std::unordered_map<commandline_option, std::variant<bool, int, double, std::wstring>> a;
  wchar_t** as = ::CommandLineToArgvW(::GetCommandLineW(), &i);
  auto as_end = as + i;
  args[{commandline_type::string, L"command", L"executable name"}] = std::wstring(as[0]);

  return a;
}({});
}
}
