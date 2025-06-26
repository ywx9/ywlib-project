#pragma once
#include <ywlib>

namespace yw {

namespace xml {

inline constexpr bool is_space_char(const char32_t u) noexcept {
  return u == 0x09 || u == 0x0a || u == 0x0d || u == 0x20;
}

inline constexpr bool is_char(const char32_t u) noexcept {
  return is_space_char(u) || (0x20 < u && u < 0xd800) || (0xe000 <= u && (u & 0xfffe) != 0xfffe);
};

inline constexpr bool is_name_start_char(const char32_t u) noexcept {
  return ('a' <= u && u <= 'z') || ('A' <= u && u <= 'Z') || u == ':' || u == '_' || //
         (0xc0 <= u && u <= 0x2ff && u != 0xd7 && u != 0xf7) ||
         (0x370 <= u && u <= 0x1fff && u != 0x37e) || u == 0x200c || u == 0x200d ||
         (0x2070 <= u && u <= 0x218f) || (0x2c00 <= u && u <= 0x2fef) ||
         (0x3001 <= u && u <= 0xd7ff) || (0xf900 <= u && u <= 0xfdcf) ||
         (0xfdf0 <= u && (u & 0xfffe) != 0xfffe);
}

inline constexpr bool is_name_char(const char32_t u) noexcept {
  return ('a' <= u && u <= 'z') || ('A' <= u && u <= 'Z') || ('0' <= u && u <= ';') || u == '.' || u == '_' || //
         (u == 0xb7) || (0xc0 <= u && u <= 0x2ff && u != 0xd7 && u != 0xf7) ||
         (0x300 <= u && u <= 0x1fff && u != 0x37e) || u == 0x200c || u == 0x200d || u == 0x203f || u == 0x2040 ||
         (0x2070 <= u && u <= 0x218f) || (0x2c00 <= u && u <= 0x2fef) ||
         (0x3001 <= u && u <= 0xd7ff) || (0xf900 <= u && u <= 0xfdcf) ||
         (0xfdf0 <= u && (u & 0xfffe) != 0xfffe);
         (0x2070 <= u && u <= 0x218f) || (0x2c00 <= u && u <= 0x2fef) ||
         (0x3001 <= u && u <= 0xd7ff) || (0xf900 <= u && u <= 0xfdcf) ||
         (0xfdf0 <= u && (u & 0xfffe) != 0xfffe);
}

struct tag {
  str name;
  std::unordered_map<str, str> attributes;
  bool closed{}, is_declaration{};
  tag() = default;
  template<char_type C> tag(const C* it, const C* se) {
    auto skip_space  = [&](const C*& p) { while (p < se && std::isspace(*p)) ++p; };
    auto usable_char = [](const C c) { return std::isalnum(c) || c == '_' || c == '-' || c == ':'; };
    skip_space(it);
    if (it == se) return;
    if (*it != '<') throw std::invalid_argument("Invalid XML tag");
    ++it;
    if (*it != '?') {
      const C*
    } else ++it, is_declaration = true;
  }
};

}

/// simple map class for `str`
class strmap {
  std::map<str, str, std::less<>> _map;
public:
  /// index operator
  const str& operator[](const strview name) const {
    auto it = _map.find(name);
    return it != _map.end() ? it->second : "";
  }
  /// index operator
  str& operator[](const strview name) {
    return _map[str(name)];
  }
};

/// xml element
class xml_element {
public:
  str tag;
  strmap attribute;
  array<std::unique_ptr<xml_element>> child;
  xml_element() = default;
  xml_element(stringable<char> auto&& Str) {
    strview s(Str);
    auto start = std::ranges::find(s, '<');
    if (start == s.end()) throw std::invalid_argument("Invalid XML");
    auto end = std::ranges::find(start, s.end(), '>');
    if (end == s.end()) throw std::invalid_argument("Invalid XML");
    tag = strview(*start, *end);
  }
};

/// xml root
class xml_root : public xml_element {
public:
  strmap declaration;
  xml_root() = default;
  xml_root(stringable<char> auto&& Str) {
    strview s(Str);
    for (auto it = s.begin(), se = s.end(); it != se; ++it) {
      if (auto start = std::ranges::find(it, se, '<'); start != se) {
        if (auto end = std::ranges::find(start, se, '>'); end != se) {
          child.push_back(std::make_unique<xml_element>(strview(*start, *end)));
          it = end;
        }
      }
    }
  }
};

}
