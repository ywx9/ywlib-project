#pragma once
#include <ywlib>

namespace yw {

// class xml {
//   ustr _str;
// public:
//   xml() = default;
//   template<stringable S> xml(S&& Str) : _str(unicode<uchar>(static_cast<S&&>(Str))) {}
//   xml(const path& File) {
//     auto f = File.read();
//     if (f.size() < 4) return;
//     else if (f[0] != 0) _str = unicode<char32_t>(f);
//     else if (f[1] != 0) _str = unicode<char32_t>(wstrview((wchar_t*)f.data(), f.size() / sizeof(wchar_t)));
//     else _str = ustr(ustr((char32_t*)f.data(), f.size() / sizeof(char32_t)));
//   }
// };

namespace xml {

inline constexpr bool is_space_char(const char32_t u) noexcept {
  return u == 0x09 || u == 0x0a || u == 0x0d || u == 0x20;
}

inline constexpr bool is_number_char(const char32_t u) noexcept {
  return '0' <= u && u <= '9';
}

inline constexpr bool is_char(const char32_t u) noexcept {
  return is_space_char(u) || (0x20 < u && u < 0xd800) || (0xe000 <= u && (u & 0xfffe) != 0xfffe);
};

inline constexpr bool is_name_start_char(const char32_t u) noexcept {
  return ('a' <= u && u <= 'z') || ('A' <= u && u <= 'Z') || u == ':' || u == '_' ||
         (0xc0 <= u && u <= 0x2ff && u != 0xd7 && u != 0xf7) ||
         (0x370 <= u && u <= 0x1fff && u != 0x37e) || u == 0x200c || u == 0x200d ||
         (0x2070 <= u && u <= 0x218f) || (0x2c00 <= u && u <= 0x2fef) ||
         (0x3001 <= u && u <= 0xd7ff) || (0xf900 <= u && u <= 0xfdcf) ||
         (0xfdf0 <= u && (u & 0xfffe) != 0xfffe);
}

inline constexpr bool is_name_char(const char32_t u) noexcept {
  return ('a' <= u && u <= 'z') || ('A' <= u && u <= 'Z') || ('0' <= u && u <= ':') || u == '.' || u == '_' ||
         (u == 0xb7) || (0xc0 <= u && u <= 0x2ff && u != 0xd7 && u != 0xf7) ||
         (0x300 <= u && u <= 0x1fff && u != 0x37e) || u == 0x200c || u == 0x200d || u == 0x203f || u == 0x2040 ||
         (0x2070 <= u && u <= 0x218f) || (0x2c00 <= u && u <= 0x2fef) ||
         (0x3001 <= u && u <= 0xd7ff) || (0xf900 <= u && u <= 0xfdcf) ||
         (0xfdf0 <= u && (u & 0xfffe) != 0xfffe);
}

/// removes comments from the xml string
template<char_type C> constexpr string<C> remove_comments(string_view<C> s) {
  constexpr C comment_start[]{'<', '!', '-', '-'};
  constexpr C comment_end[]{'-', '-', '>'};
  string<C> result;
  result.reserve(s.size()), result.resize(s.size());
  auto out{s.begin()};
  for (auto sr = std::ranges::search(s, comment_start); !sr.empty(); sr = std::ranges::search(s, comment_start)) {
    auto cr  = std::ranges::copy(s.begin(), sr.begin(), out);
    out      = cr.out;
    auto sr2 = std::ranges::search(string_view(cr.in, s.end()), comment_end);
    if (sr2.empty()) throw std::invalid_argument("xml::remove_comments: Unclosed comment");
    s = string_view(sr2.end(), s.end());
  }
  result.resize(out - result.begin());
  return result;
}

inline void analyze_element(ustrview& Str, ustr& Name, std::map<ustr, ustr, std::less<>>& Attributes, array<std::unique_ptr<element>>& Children);

/// class to represent XML element
class element {
public:
  ustr name;
  std::map<ustr, ustr, std::less<>> attributes;
  array<std::unique_ptr<element>> children;
  element(ustrview& Str) { analyze_element(Str, name, attributes, children); }
};

inline void analyze_element(ustrview& Str, ustr& Name, std::map<ustr, ustr, std::less<>>& Attributes, array<std::unique_ptr<element>>& Children) {
  auto fr = std::ranges::find_if_not(Str, [](const char32_t u) { return is_space_char(u); });
  if (fr == Str.end()) return; // empty string
  if (*fr++ != '<') throw std::invalid_argument(format("xml::element: invalid element", uint32_t(*fr)));
  // obtains element name
  if (fr == Str.end() || !is_name_start_char(*fr)) throw std::invalid_argument("xml::element: invalid element");
  auto fr2 = std::ranges::find_if(ustrview(fr, Str.end()), [](const char32_t u) { return !is_name_char(u); });
  Name     = ustr(fr, fr2);
  Str      = ustrview(fr2, Str.end());
  // obtains attributes
  while (true) {
    fr = std::ranges::find_if_not(Str, [](const char32_t u) { return is_space_char(u); });
    if (fr == Str.end()) throw std::invalid_argument(format("xml::element: element({}) is not well-formed", unicode<char>(Name)));
    if (*fr == '/') {
      ++fr;
      if (fr != Str.end() && *fr++ == '>') {
        Str = ustrview(fr, Str.end());
        return;
      } else throw std::invalid_argument(format("xml::element: element({}) is not well-formed", unicode<char>(Name)));
    } else if (is_name_start_char(*fr)) {
      auto fr2       = std::ranges::find_if(ustrview(fr, Str.end()), [](const char32_t u) { return !is_name_char(u); });
      auto attr_name = ustrview(fr, fr2);
      fr             = std::ranges::find_if_not(ustrview(fr2, Str.end()), [](const char32_t u) { return is_space_char(u); });
      if (fr == Str.end() || *fr++ != '=') throw std::invalid_argument(format("xml::element: element({})-attribute({}) is not well-formed", unicode<char>(Name), unicode<char>(attr_name)));
      fr = std::ranges::find_if_not(ustrview(fr, Str.end()), [](const char32_t u) { return is_space_char(u); });
      if (fr == Str.end()) throw std::invalid_argument(format("xml::element: element({})-attribute({}) is not well-formed", unicode<char>(Name), unicode<char>(attr_name)));
      if (*fr == '"') fr2 = std::ranges::find(ustrview(++fr, Str.end()), '"');
      else if (*fr == '\'') fr2 = std::ranges::find(ustrview(++fr, Str.end()), '\'');
      else throw std::invalid_argument(format("xml::element: element({})-attribute({}) is not well-formed", unicode<char>(Name), unicode<char>(attr_name)));
      Attributes[ustr(attr_name)] = ustrview(fr, fr2);
      Str                         = ustrview(fr2, Str.end());
    } else if (*fr == '>') break;
    else throw std::invalid_argument(format("xml::element: element({}) is not well-formed", unicode<char>(Name)));
  }
  // obtains children
  for (int i{};; ++i) {
    try {
      element child(Str);
      if (child.name.empty()) break;
      Children.push_back(std::make_unique<element>(mv(child)));
    } catch (const std::exception& e) {
      throw std::invalid_argument(format("xml::element: {}-th child of element({}) throws exception;\n -> {}", i, unicode<char>(Name), e.what()));
    }
  }
  // check closing tag
  fr = std::ranges::find_if_not(Str, [](const char32_t u) { return is_space_char(u); });
  if (fr == Str.end() || *fr++ != '<') throw std::invalid_argument(format("xml::element: element({}) is not well-formed", unicode<char>(Name)));
  if (fr == Str.end() || *fr++ != '/') throw std::invalid_argument(format("xml::element: element({}) is not well-formed", unicode<char>(Name)));
  if (!std::ranges::starts_with(ustrview(fr, Str.end()), Name)) throw std::invalid_argument(format("xml::element: element({}) is not well-formed", unicode<char>(Name)));
  fr += Name.size();
  if (fr == Str.end() || *fr++ != '>') throw std::invalid_argument(format("xml::element: element({}) is not well-formed", unicode<char>(Name)));
  Str = ustrview(fr, Str.end());
}

/// class to represent XML root
class root : public element {
public:
  std::map<ustr, ustr, std::less<>> declaration;
  root() = default;
  template<stringable S> root(S&& Str) {
    using C = iter_value_t<S>;
    ustr ss;
    ustrview sv;
    if constexpr (different_from<C, uchar>) {
      ss = unicode<uchar>(static_cast<S&&>(Str));
      sv = ustrview(ss);
    } else sv = ustrview(Str);
    // obtains declaration
    auto fr = std::ranges::find_if_not(sv, [](const char32_t u) { return is_space_char(u); });
    if (std::ranges::starts_with(ustrview(fr, sv.end()), U"<?xml")) {
      fr = std::ranges::find_if_not(ustrview(fr + 5, sv.end()), [](const char32_t u) { return is_space_char(u); });
      // version
      if (std::ranges::starts_with(ustrview(fr, sv.end()), "version")) {
        fr = std::ranges::find_if_not(ustrview(fr + 7, sv.end()), [](const char32_t u) { return is_space_char(u); });
        if (fr == sv.end() || *fr++ != '=') throw std::invalid_argument(format("xml::root: xml declaration is not well-formed"));
        fr = std::ranges::find_if_not(ustrview(fr, sv.end()), [](const char32_t u) { return is_space_char(u); });
        if (std::ranges::starts_with(ustrview(fr, sv.end()), "'1.")) {
          if (fr == sv.end() || !is_number_char(*fr++)) throw std::invalid_argument(format("xml::root: xml declaration is not well-formed"));
          fr = std::ranges::find_if_not(ustrview(fr, sv.end()), [](const char32_t u) { return is_number_char(u); });
          if (fr == sv.end() || *fr++ != '\'') throw std::invalid_argument(format("xml::root: xml declaration is not well-formed"));
          declaration["version"] = ustrview(fr, sv.end());
        } else if (std::ranges::starts_with(ustrview(fr, sv.end()), "\"1.")) {
          if (fr == sv.end() || !is_number_char(*fr++)) throw std::invalid_argument(format("xml::root: xml declaration is not well-formed"));
          fr = std::ranges::find_if_not(ustrview(fr, sv.end()), [](const char32_t u) { return is_number_char(u); });
          if (fr == sv.end() || *fr++ != '"') throw std::invalid_argument(format("xml::root: xml declaration is not well-formed"));
          declaration["version"] = ustrview(fr, sv.end());
        } else throw std::invalid_argument(format("xml::root: xml declaration is not well-formed"));
      } else throw std::invalid_argument(format("xml::root: xml declaration is not well-formed"));
      fr = std::ranges::find_if_not(ustrview(fr, sv.end()), [](const char32_t u) { return is_space_char(u); });
      // encoding
      if (std::ranges::starts_with(ustrview(fr, sv.end()), "encoding")) {
        fr = std::ranges::find_if_not(ustrview(fr + 8, sv.end()), [](const char32_t u) { return is_space_char(u); });
        if (fr == sv.end() || *fr++ != '=') throw std::invalid_argument(format("xml::root: xml declaration is not well-formed"));
        fr = std::ranges::find_if_not(ustrview(fr, sv.end()), [](const char32_t u) { return is_space_char(u); });
        if (std::ranges::starts_with(ustrview(fr, sv.end()), "'UTF-8")) {
          if (fr == sv.end() || *fr++ != '\'') throw std::invalid_argument(format("xml::root: xml declaration is not well-formed"));
          declaration["encoding"] = ustrview(fr, sv.end());
        } else if (std::ranges::starts_with(ustrview(fr, sv.end()), "\"UTF-8")) {
          if (fr == sv.end() || *fr++ != '"') throw std::invalid_argument(format("xml::root: xml declaration is not well-formed"));
          declaration["encoding"] = ustrview(fr, sv.end());
        } else throw std::invalid_argument(format("xml::root: xml declaration is not well-formed"));
      } else throw std::invalid_argument(format("xml::root: xml declaration is not well-formed"));
    } else throw std::invalid_argument(format("xml::root: xml declaration is not well-formed"));
  }
};

inline ustr open(const path& File) {
}

}

// /// simple map class for `str`
// class strmap {
//   std::map<str, str, std::less<>> _map;
// public:
//   /// index operator
//   const str& operator[](const strview name) const {
//     auto it = _map.find(name);
//     return it != _map.end() ? it->second : "";
//   }
//   /// index operator
//   str& operator[](const strview name) {
//     return _map[str(name)];
//   }
// };

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
