#pragma once
#include <ywlib>

namespace yw::xml {

/// returns the position (line, column) of the given iterator in the document
constexpr vector2<int> position_in_document(const ustrview::iterator Current, const ustrview& Document) {
  if (Current < Document.begin() || Current > Document.end()) throw std::invalid_argument("Invalid position");
  int line = 1, column = 1;
  for (auto it = Document.begin(); it != Current; ++it) *it == '\n' ? ++line, column = 1 : ++column;
  return {line, column};
}

/// exception class for XML errors
class exception : public std::runtime_error {
  static std::runtime_error create(const ustrview::iterator p, const ustrview d, const char* m) {
    auto [line, column] = position_in_document(p, d);
    auto s              = format("yw-xml: error at ({},{}) {}", line, column, m);
    return std::runtime_error(s);
  }
public:
  exception(const ustrview::iterator Position, const ustrview& Document, const char* Message)
    : std::runtime_error(create(Position, Document, Message)) {}
};

/// [1] document ::= prolog element Misc*

/// [2] Char ::= #x9 | #xA | #xD | [#x20-#xD7FF] | [#xE000-#xFFFD] | [#x10000-#x10FFFF]
/// \return `true` if the character is a char
constexpr bool is_char(const char32_t c) noexcept {
  return c == 0x9 || c == 0xa || c == 0xd || (0x20 <= c && c <= 0xd7ff) || (0xe000 <= c && (c & 0xfffe) != 0xfffe);
}

/// [3] S ::= (#x20 | #x9 | #xD | #xA)+
/// \return `true` if one or more whitespace characters are skipped
constexpr bool skip_space(ustrview& s, const ustrview& Document) noexcept {
  auto is_s = [](const char32_t c) noexcept { return (c == 0x20 || c == 0x9 || c == 0xd || c == 0xa); };
  auto it   = s.begin();
  while (it != s.end() && is_s(*it)) ++it;
  const bool skipped{it != s.begin()};
  s = ustrview(it, s.end());
  return skipped;
}

/// [4] NameStartChar ::= ":" | [A-Z] | "_" | [a-z] | [#xC0-#xD6] | [#xD8-#xF6] | [#xF8-#x2FF] | [#x370-#x37D] | [#x37F-#x1FFF] | [#x200C-#x200D] | [#x2070-#x218F] | [#x2C00-#x2FEF] | [#x3001-#xD7FF] | [#xF900-#xFDCF] | [#xFDF0-#xFFFD] | [#x10000-#xEFFFF]
/// \return `true` if the character is a name start char
constexpr bool is_name_start_char(const char32_t c) noexcept {
  return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || c == ':' || c == '_' ||
         (0xc0 <= c && c <= 0x2ff && c != 0xd7 && c != 0xf7) ||
         (0x370 <= c && c <= 0x1fff && c != 0x37e) || c == 0x200c || c == 0x200d ||
         (0x2070 <= c && c <= 0x218f) || (0x2c00 <= c && c <= 0x2fef) ||
         (0x3001 <= c && c <= 0xd7ff) || (0xf900 <= c && c <= 0xfdcf) ||
         (0xfdf0 <= c && (c & 0xfffe) != 0xfffe);
}

/// [4a] NameChar ::= NameStartChar | "-" | "." | [0-9] | #xB7 | [#x0300-#x036F] | [#x203F-#x2040]
/// \return `true` if the character is a name char
constexpr bool is_name_char(const char32_t c) noexcept {
  return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || ('0' <= c && c <= ':') || c == '.' || c == '_' ||
         (c == 0xb7) || (0xc0 <= c && c <= 0x2ff && c != 0xd7 && c != 0xf7) ||
         (0x300 <= c && c <= 0x1fff && c != 0x37e) || c == 0x200c || c == 0x200d || c == 0x203f || c == 0x2040 ||
         (0x2070 <= c && c <= 0x218f) || (0x2c00 <= c && c <= 0x2fef) ||
         (0x3001 <= c && c <= 0xd7ff) || (0xf900 <= c && c <= 0xfdcf) ||
         (0xfdf0 <= c && (c & 0xfffe) != 0xfffe);
}

/// [5] Name ::= NameStartChar (NameChar)*
/// \return `Name`
constexpr ustrview get_name(ustrview& s, const ustrview& Document) {
  auto it = s.begin();
  if (it == s.end() || !is_name_start_char(*it++)) throw exception(it, Document, "`Name` must start with 'NameStartChar");
  while (it != s.end() && is_name_char(*it)) ++it;
  ustrview result{s.begin(), it};
  s = ustrview{it, s.end()};
  return result;
}

/// [6] Names ::= Name (#x20 Name)*
/// \return array of `Name`
constexpr array<ustrview> get_names(ustrview& s, const ustrview& Document) {
  array<ustrview> names;
  names.push_back(get_name(s, Document));
  auto it = s.begin();
  while (it != s.end()) {
    if (*it == 0x20) {
      try {
        s = ustrview{it + 1, s.end()};
        names.push_back(get_name(s, Document));
        it = s.begin();
      } catch (const exception& e) {
        s = ustrview{it, s.end()};
        return names;
      }
    } else return names;
  }
  return names;
}

/// [7] Nmtoken ::= (NameChar)+
/// \returns `Nmtoken`
constexpr ustrview get_nmtoken(ustrview& s, const ustrview& Document) {
  auto it = s.begin();
  if (it == s.end() || !is_name_char(*it++)) throw exception(it, Document, "`Nmtoken` must start with 'NameChar");
  while (it != s.end() && is_name_char(*it)) ++it;
  s = ustrview{it, s.end()};
  return ustrview{s.begin(), it};
}

/// [8] Nmtokens ::= (Nmtoken)+
/// \returns array of `Nmtoken`
constexpr array<ustrview> get_nmtokens(ustrview& s, const ustrview& Document) {
  array<ustrview> nmtokens;
  nmtokens.push_back(get_nmtoken(s, Document));
  auto it = s.begin();
  while (it != s.end()) {
    if (*it == 0x20) {
      try {
        s = ustrview{it + 1, s.end()};
        nmtokens.push_back(get_nmtoken(s, Document));
        it = s.begin();
      } catch (const exception& e) {
        s = ustrview{it, s.end()};
        return nmtokens;
      }
    } else return nmtokens;
  }
  return nmtokens;
}

/// [9] EntityValue ::= '"' ([^%&"] | PEReference | Reference)* '"' |  "'" ([^%&'] | PEReference | Reference)* "'"
/// [10] AttValue ::= '"' ([^<&"] | Reference)* '"' | "'" ([^<&'] | Reference)* "'"

/// [11] SystemLiteral ::= ('"' [^"]* '"') | ("'" [^']* "'")
/// \returns `SystemLiteral`
constexpr ustrview get_system_literal(ustrview& s, const ustrview& Document) {
  auto it = s.begin();
  if (it == s.end()) throw exception(it, Document, "`SystemLiteral` must start with '\"' or '\\''");
  if (*it++ == '"') {
    while (it != s.end() && *it != '"') ++it;
    if (it == s.end()) throw exception(it, Document, "`SystemLiteral` must end with '\"'");
  } else if (*it++ == '\'') {
    while (it != s.end() && *it != '\'') ++it;
    if (it == s.end()) throw exception(it, Document, "`SystemLiteral` must end with '\\''");
  } else throw exception(it, Document, "`SystemLiteral` must start with '\"' or '\\''");
  ustrview result{s.begin() + 1, it};
  s = ustrview{it + 1, s.end()};
  return result;
}

/// [13] PubidChar ::= #x20 | #xD | #xA | [a-zA-Z0-9] | [-'()+,./:=?;!*#@$_%]
/// \return `true` if the character is `PubidChar`
constexpr bool is_pubid_char(const char32_t u) noexcept {
  return u == 0xd || u == 0xa || (0x5f <= u && u <= 0x7a && (u != 0x60)) ||
         (0x20 <= u && u <= 0x90 && (u != 0x22 && u != 0x26 && u != 0x60 && u != 0x62 && u != 0x64));
}

/// [12] PubidLiteral ::= '"' PubidChar* '"' | "'" (PubidChar - "'")* "'"
/// \return `PubidLiteral`
constexpr ustrview get_pubid_literal(ustrview& s, const ustrview& Document) {
  auto it = s.begin();
  if (it == s.end()) throw exception(it, Document, "`PubidLiteral` must start with '\"' or '\\''");
  if (*it++ == '"') {
    while (it != s.end() && is_pubid_char(*it)) ++it;
    if (it == s.end() || *it != '"') throw exception(it, Document, "`PubidLiteral` must end with '\"'");
  } else if (*it++ == '\'') {
    while (it != s.end() && is_pubid_char(*it)) ++it;
    if (it == s.end() || *it != '\'') throw exception(it, Document, "`PubidLiteral` must end with '\\''");
  } else throw exception(it, Document, "`PubidLiteral` must start with '\"' or '\\''");
  ustrview result{s.begin() + 1, it};
  s = ustrview{it + 1, s.end()};
  return result;
}

/// [14] CharData ::= [^<&]* - ([^<&]* ']]>' [^<&]*)
/// \return `CharData`
constexpr ustrview get_char_data(ustrview& s, const ustrview& Document) {
  auto it = s.begin();
  while (it != s.end() && *it != '<' && *it != '&' && !std::ranges::starts_with(ustrview(it, s.end()), ustrview(U"]]>"))) ++it;
  ustrview result{s.begin(), it};
  s = ustrview{it, s.end()};
  return result;
}

/// [15] Comment ::= '<!--' ((Char - '-') | ('-' (Char - '-')))* '-->'
/// \return `Comment`
constexpr ustrview get_comment(ustrview& s, const ustrview& Document) {
  auto it = s.begin();
  if (!std::ranges::starts_with(ustrview(it, s.end()), ustrview(U"<!--"))) throw exception(it, Document, "`Comment` must start with '<!--'");
  s.remove_prefix(4);
  auto sr = std::ranges::search(s, ustrview(U"-->"));
  if (sr.empty()) throw exception(s.end(), Document, "`Comment` must end with '-->'");
  ustrview comment{s.begin(), sr.begin()};
  if (comment.empty()) throw exception(s.begin(), Document, "`Comment` must not be empty");
  else if (comment.front() == '-') throw exception(s.begin(), Document, "`Comment` must not start with '<!---'");
  if (std::ranges::search(comment, ustrview(U"--"))) throw exception(s.begin(), Document, "`Comment` must not include '--'");
  if (std::ranges::any_of(comment, [](uchar c) noexcept { return !is_char(c); })) throw exception(s.begin(), Document, "`Comment` must only include valid characters");
  s = ustrview{sr.end(), s.end()};
  return comment;
}

/// [15] PITarget ::= Name - (('X' | 'x') ('M' | 'm') ('L' | 'l'))
/// \return `PITarget`
constexpr ustrview get_pi_target(ustrview& s, const ustrview& Document) {
  auto result = get_name(s, Document);
  if (std::ranges::starts_with(result, ustrview(U"XML"), [](uchar a, uchar b) noexcept { return (a & ~0x10) == b; }))
    throw exception(result.begin(), Document, "`PITarget` must not be 'XML'");
  return result;
}

/// [16] PI ::= '<?' PITarget (S (Char* - (Char* '?>' Char*)))? '?>'
/// \return `PITarget` and data
constexpr tuple<ustrview, ustrview> get_processing_instruction(ustrview& s, const ustrview& Document) {
  if (!std::ranges::starts_with(s, ustrview(U"<?"))) throw exception(s.begin(), Document, "`PI` must start with '<?'");
  s.remove_prefix(2);
  ustrview target = get_pi_target(s, Document), data;
  auto sr = std::ranges::search(s, ustrview(U"?>"));
  if (sr.empty()) throw exception(s.end(), Document, "`PI` must end with '?>'");
  ustrview data{s.begin(), sr.begin()};
  skip_space(data, Document);
  s = ustrview{sr.end(), s.end()};
  return {target, data};
}

/// [18] CDSect ::= CDStart CData CDEnd
/// [19] CDStart ::= '<![CDATA['
/// [21] CDEnd ::= ']]>'

/// [20] CData ::= (Char* - (Char* ']]>' Char*))
/// \return `CData`
constexpr ustrview get_cdata(ustrview& s, const ustrview& Document) {
  if (!std::ranges::starts_with(s, ustrview(U"<![CDATA["))) throw exception(s.begin(), Document, "`CData` must start with '<![CDATA['");
  s.remove_prefix(9);
  auto sr = std::ranges::search(s, ustrview(U"]]>"));
  if (sr.empty()) throw exception(s.end(), Document, "`CData` must end with ']]>'");
  ustrview result{s.begin(), sr.begin()};
  s = ustrview{sr.end(), s.end()};
  return result;
}

/// [22] prolog ::= XMLDecl? Misc* (doctypedec|Misc*)?

/// [23] XMLDecl ::= '<?xml' VersionInfo EncodingDecl? SDDecl? S? '>'

/// [25] Eq ::= S? '=' S?
/// \return `true` if `Eq` is found and skipped
constexpr bool skip_eq(ustrview& s, const ustrview& Document) {
  skip_space(s, Document);
  if (s.empty() || s.front() != '=') throw exception(s.begin(), Document, "'Eq' must have '='");
  s.remove_prefix(1);
  skip_space(s, Document);
  return true;
}

/// [26] VersionNum ::= '1.' [0-9]+
/// \return `VersionNum`
constexpr ustrview get_version_num(ustrview& s, const ustrview& Document) {
  auto is_digit = [](const char32_t u) { return u >= '0' && u <= '9'; };
  if (!std::ranges::starts_with(s, ustrview(U"1."))) throw exception(s.begin(), Document, "`VersionNum` must start with '1.'");
  s.remove_prefix(2);
  if (s.empty() || !is_digit(s.front())) throw exception(s.begin(), Document, "invalid `VersionNum`");
  s.remove_prefix(1);
  auto it = std::ranges::find_if_not(s, is_digit);
  ustrview result{s.begin(), it};
  s = ustrview{it, s.end()};
  return result;
}

/// [24] VersionInfo ::= S 'version' Eq ("'" VersionNum"'"" | '"' VersionNum '"' )
//// \return `VersionNum`
constexpr ustrview get_version_info(ustrview& s, const ustrview& Document) {
  skip_space(s, Document);
  if (!std::ranges::starts_with(s, ustrview(U"version"))) throw exception(s.begin(), Document, "`VersionInfo` must start with 'version'");
  s.remove_prefix(7);
  if (!skip_eq(s, Document)) throw exception(s.begin(), Document, "`VersionInfo` must have '='");
  if (s.empty()) throw exception(s.end(), Document, "invalid `VersionInfo`");
  if (s.front() == '"') {
    s.remove_prefix(1);
    auto version_num = get_version_num(s, Document);
    if (s.empty() || s.front() != '"') throw exception(s.begin(), Document, "invalid `VersionInfo`");
    return version_num;
  } else if (s.front() == '\'') {
    s.remove_prefix(1);
    auto version_num = get_version_num(s, Document);
    if (s.empty() || s.front() != '\'') throw exception(s.begin(), Document, "invalid `VersionInfo`");
    s.remove_prefix(1);
    return version_num;
  } else throw exception(s.begin(), Document, "`VersionInfo` must have 'version' followed by '=' and a quoted string");
}

/// [27] Misc ::= Comment | PI | S
/// \return `{empty, Comment}` if Comment, `{PITarget, data}` if PI, `{empty, empty}` if S
constexpr tuple<ustrview, ustrview> get_misc(ustrview& s, const ustrview& Document) {
  try {
    auto s2 = s;
    auto comment = get_comment(s2, Document);
    s = s2;
    return {ustrview{}, comment};
  } catch (const exception& e) {} // misc is not comment
  try {
    auto s2 = s;
    auto [target, data] = get_processing_instruction(s2, Document);
    s = s2;
    return {target, data};
  } catch (const exception& e) {} // misc is not PI
  if (!skip_space(s, Document)) throw exception(s.begin(), Document, "`Misc` must have comment, PI or space");
  return {ustrview{}, ustrview{}};
}

/// [28] doctypedecl ::= '<!DOCTYPE' S Name (S ExternalID)? S? ('[' intSubset ']' S?)? '>'
/// [28a] DeclSep ::= PEReference | S
/// [28b]intSubset ::= (markupdecl | DeclSep)*
/// [29] markupdecl ::= elementdecl | AttlistDecl | EntityDecl | NotationDecl | PI | Comment
/// [30] extSubset ::= TextDecl? extSubsetDecl
/// [31] extSubsetDecl ::= ( markupdecl | conditionalSect | DeclSep)*

/// [32] SDDecl ::= S 'standalone' Eq (("'" ('yes' | 'no') "'") | ('"' ('yes' | 'no') '"'))
/// \return "yes" or "no"
constexpr ustrview get_sddecl(ustrview& s, const ustrview& Document) {
  skip_space(s, Document);
  if (!std::ranges::starts_with(s, ustrview(U"standalone"))) throw exception(s.begin(), Document, "`SDDecl` must start with 'standalone'");
  s.remove_prefix(10);
  if (!skip_eq(s, Document)) throw exception(s.begin(), Document, "`SDDecl` must have '='");
  if (s.empty()) throw exception(s.end(), Document, "invalid `SDDecl`");
  if (s.front() == '"') {
    s.remove_prefix(1);
    if (std::ranges::starts_with(s, ustrview(U"yes\""))) {
      auto result = s.substr(0, 3);
      s.remove_prefix(4);
      return result;
    } else if (std::ranges::starts_with(s, ustrview(U"no\""))) {
      auto result = s.substr(0, 2);
      s.remove_prefix(3);
      return result;
    } else throw exception(s.begin(), Document, "invalid `SDDecl`");
  } else if (s.front() == '\'') {
    s.remove_prefix(1);
    if (std::ranges::starts_with(s, ustrview(U"yes'"))) {
      s.remove_prefix(4);
      return s.substr(0, 3);
    } else if (std::ranges::starts_with(s, ustrview(U"no'"))) {
      s.remove_prefix(3);
      return s.substr(0, 2);
    } else throw exception(s.begin(), Document, "invalid `SDDecl`");
  } else throw exception(s.begin(), Document, "`SDDecl` must have 'yes' or 'no'");
}

// //   xml() = default;
// //   template<stringable S> xml(S&& Str) : _str(unicode<uchar>(static_cast<S&&>(Str))) {}
// //   xml(const path& File) {
// //     auto f = File.read();
// //     if (f.size() < 4) return;
// //     else if (f[0] != 0) _str = unicode<char32_t>(f);
// //     else if (f[1] != 0) _str = unicode<char32_t>(wstrview((wchar_t*)f.data(), f.size() / sizeof(wchar_t)));
// //     else _str = ustr(ustr((char32_t*)f.data(), f.size() / sizeof(char32_t)));
// //   }
// // };

// namespace xml {

// class element;
// class root;

// constexpr bool is_space_char(const char32_t u) noexcept {
//   return u == 0x09 || u == 0x0a || u == 0x0d || u == 0x20;
// }

// constexpr bool is_number_char(const char32_t u) noexcept {
//   return '0' <= u && u <= '9';
// }

// constexpr bool is_char(const char32_t u) noexcept {
//   return is_space_char(u) || (0x20 < u && u < 0xd800) || (0xe000 <= u && (u & 0xfffe) != 0xfffe);
// };

// constexpr bool is_name_start_char(const char32_t u) noexcept {
//   return ('a' <= u && u <= 'z') || ('A' <= u && u <= 'Z') || u == ':' || u == '_' ||
//          (0xc0 <= u && u <= 0x2ff && u != 0xd7 && u != 0xf7) ||
//          (0x370 <= u && u <= 0x1fff && u != 0x37e) || u == 0x200c || u == 0x200d ||
//          (0x2070 <= u && u <= 0x218f) || (0x2c00 <= u && u <= 0x2fef) ||
//          (0x3001 <= u && u <= 0xd7ff) || (0xf900 <= u && u <= 0xfdcf) ||
//          (0xfdf0 <= u && (u & 0xfffe) != 0xfffe);
// }

// constexpr bool is_name_char(const char32_t u) noexcept {
//   return ('a' <= u && u <= 'z') || ('A' <= u && u <= 'Z') || ('0' <= u && u <= ':') || u == '.' || u == '_' ||
//          (u == 0xb7) || (0xc0 <= u && u <= 0x2ff && u != 0xd7 && u != 0xf7) ||
//          (0x300 <= u && u <= 0x1fff && u != 0x37e) || u == 0x200c || u == 0x200d || u == 0x203f || u == 0x2040 ||
//          (0x2070 <= u && u <= 0x218f) || (0x2c00 <= u && u <= 0x2fef) ||
//          (0x3001 <= u && u <= 0xd7ff) || (0xf900 <= u && u <= 0xfdcf) ||
//          (0xfdf0 <= u && (u & 0xfffe) != 0xfffe);
// }

// /// removes comments from the xml string
// template<char_type C> constexpr string<C> remove_comments(string_view<C> s) {
//   constexpr C comment_start[]{'<', '!', '-', '-'};
//   constexpr C comment_end[]{'-', '-', '>'};
//   string<C> result;
//   result.reserve(s.size()), result.resize(s.size());
//   auto out{s.begin()};
//   for (auto sr = std::ranges::search(s, comment_start); !sr.empty(); sr = std::ranges::search(s, comment_start)) {
//     auto cr  = std::ranges::copy(s.begin(), sr.begin(), out);
//     out      = cr.out;
//     auto sr2 = std::ranges::search(string_view(cr.in, s.end()), comment_end);
//     if (sr2.empty()) throw std::invalid_argument("xml::remove_comments: Unclosed comment");
//     s = string_view(sr2.end(), s.end());
//   }
//   result.resize(out - result.begin());
//   return result;
// }

// inline void analyze_element(ustrview& Str, ustr& Name, std::map<ustr, ustr, std::less<>>& Attributes, array<std::unique_ptr<element>>& Children);

// /// analyzes the string as attributes until the next `not NameStartChar`

// /// class to represent XML element
// class element {
// public:
//   ustr name;
//   std::map<ustr, ustr, std::less<>> attributes;
//   array<std::unique_ptr<element>> children;
//   element(ustrview& Str) { analyze_element(Str, name, attributes, children); }
// };

// inline void analyze_element(ustrview& Str, ustr& Name, std::map<ustr, ustr, std::less<>>& Attributes, array<std::unique_ptr<element>>& Children) {
//   auto fr = std::ranges::find_if_not(Str, [](const char32_t u) { return is_space_char(u); });
//   if (fr == Str.end()) return;
//   if (*fr++ != '<') throw std::invalid_argument(format("xml::element: invalid element", uint32_t(*fr)));
//   // obtains element name
//   if (fr == Str.end() || !is_name_start_char(*fr)) throw std::invalid_argument("xml::element: invalid element");
//   auto fr2 = std::ranges::find_if(ustrview(fr, Str.end()), [](const char32_t u) { return !is_name_char(u); });
//   Name     = ustr(fr, fr2);
//   Str      = ustrview(fr2, Str.end());
//   // obtains attributes
//   while (true) {
//     fr = std::ranges::find_if_not(Str, [](const char32_t u) { return is_space_char(u); });
//     if (fr == Str.end()) throw std::invalid_argument(format("xml::element: element({}) is not well-formed", unicode<char>(Name)));
//     if (*fr == '/') {
//       ++fr;
//       if (fr != Str.end() && *fr++ == '>') {
//         Str = ustrview(fr, Str.end());
//         return;
//       } else throw std::invalid_argument(format("xml::element: element({}) is not well-formed", unicode<char>(Name)));
//     } else if (is_name_start_char(*fr)) {
//       auto fr2       = std::ranges::find_if(ustrview(fr, Str.end()), [](const char32_t u) { return !is_name_char(u); });
//       auto attr_name = ustrview(fr, fr2);
//       fr             = std::ranges::find_if_not(ustrview(fr2, Str.end()), [](const char32_t u) { return is_space_char(u); });
//       if (fr == Str.end() || *fr++ != '=') throw std::invalid_argument(format("xml::element: element({})-attribute({}) is not well-formed", unicode<char>(Name), unicode<char>(attr_name)));
//       fr = std::ranges::find_if_not(ustrview(fr, Str.end()), [](const char32_t u) { return is_space_char(u); });
//       if (fr == Str.end()) throw std::invalid_argument(format("xml::element: element({})-attribute({}) is not well-formed", unicode<char>(Name), unicode<char>(attr_name)));
//       if (*fr == '"') fr2 = std::ranges::find(ustrview(++fr, Str.end()), '"');
//       else if (*fr == '\'') fr2 = std::ranges::find(ustrview(++fr, Str.end()), '\'');
//       else throw std::invalid_argument(format("xml::element: element({})-attribute({}) is not well-formed", unicode<char>(Name), unicode<char>(attr_name)));
//       Attributes[ustr(attr_name)] = ustrview(fr, fr2);
//       Str                         = ustrview(fr2, Str.end());
//     } else if (*fr == '>') break;
//     else throw std::invalid_argument(format("xml::element: element({}) is not well-formed", unicode<char>(Name)));
//   }
//   // obtains children
//   for (int i{};; ++i) {
//     try {
//       element child(Str);
//       if (child.name.empty()) break;
//       Children.push_back(std::make_unique<element>(mv(child)));
//     } catch (const std::exception& e) {
//       throw std::invalid_argument(format("xml::element: {}-th child of element({}) throws exception;\n -> {}", i, unicode<char>(Name), e.what()));
//     }
//   }
//   // check closing tag
//   fr = std::ranges::find_if_not(Str, [](const char32_t u) { return is_space_char(u); });
//   if (fr == Str.end() || *fr++ != '<') throw std::invalid_argument(format("xml::element: element({}) is not well-formed", unicode<char>(Name)));
//   if (fr == Str.end() || *fr++ != '/') throw std::invalid_argument(format("xml::element: element({}) is not well-formed", unicode<char>(Name)));
//   if (!std::ranges::starts_with(ustrview(fr, Str.end()), Name)) throw std::invalid_argument(format("xml::element: element({}) is not well-formed", unicode<char>(Name)));
//   fr += Name.size();
//   if (fr == Str.end() || *fr++ != '>') throw std::invalid_argument(format("xml::element: element({}) is not well-formed", unicode<char>(Name)));
//   Str = ustrview(fr, Str.end());
// }

// /// class to represent XML root
// class root : public element {
// public:
//   std::map<ustr, ustr, std::less<>> declaration;
//   root() = default;
//   template<stringable S> root(S&& Str) {
//     using C = iter_value_t<S>;
//     ustr ss;
//     ustrview sv;
//     if constexpr (different_from<C, uchar>) {
//       ss = unicode<uchar>(static_cast<S&&>(Str));
//       sv = ustrview(ss);
//     } else sv = ustrview(Str);
//     // obtains declaration
//     auto fr = std::ranges::find_if_not(sv, [](const char32_t u) { return is_space_char(u); });
//     if (std::ranges::starts_with(ustrview(fr, sv.end()), U"<?xml")) {
//       fr = std::ranges::find_if_not(ustrview(fr + 5, sv.end()), [](const char32_t u) { return is_space_char(u); });
//       // version
//       if (std::ranges::starts_with(ustrview(fr, sv.end()), "version")) {
//         fr = std::ranges::find_if_not(ustrview(fr + 7, sv.end()), [](const char32_t u) { return is_space_char(u); });
//         if (fr == sv.end() || *fr++ != '=') throw std::invalid_argument(format("xml::root: xml declaration is not well-formed"));
//         fr = std::ranges::find_if_not(ustrview(fr, sv.end()), [](const char32_t u) { return is_space_char(u); });
//         if (std::ranges::starts_with(ustrview(fr, sv.end()), "'1.")) {
//           if (fr == sv.end() || !is_number_char(*fr++)) throw std::invalid_argument(format("xml::root: xml declaration is not well-formed"));
//           fr = std::ranges::find_if_not(ustrview(fr, sv.end()), [](const char32_t u) { return is_number_char(u); });
//           if (fr == sv.end() || *fr++ != '\'') throw std::invalid_argument(format("xml::root: xml declaration is not well-formed"));
//           declaration["version"] = ustrview(fr, sv.end());
//         } else if (std::ranges::starts_with(ustrview(fr, sv.end()), "\"1.")) {
//           if (fr == sv.end() || !is_number_char(*fr++)) throw std::invalid_argument(format("xml::root: xml declaration is not well-formed"));
//           fr = std::ranges::find_if_not(ustrview(fr, sv.end()), [](const char32_t u) { return is_number_char(u); });
//           if (fr == sv.end() || *fr++ != '"') throw std::invalid_argument(format("xml::root: xml declaration is not well-formed"));
//           declaration["version"] = ustrview(fr, sv.end());
//         } else throw std::invalid_argument(format("xml::root: xml declaration is not well-formed"));
//       } else throw std::invalid_argument(format("xml::root: xml declaration is not well-formed"));
//       fr = std::ranges::find_if_not(ustrview(fr, sv.end()), [](const char32_t u) { return is_space_char(u); });
//       // encoding
//       if (std::ranges::starts_with(ustrview(fr, sv.end()), "encoding")) {
//         fr = std::ranges::find_if_not(ustrview(fr + 8, sv.end()), [](const char32_t u) { return is_space_char(u); });
//         if (fr == sv.end() || *fr++ != '=') throw std::invalid_argument(format("xml::root: xml declaration is not well-formed"));
//         fr = std::ranges::find_if_not(ustrview(fr, sv.end()), [](const char32_t u) { return is_space_char(u); });
//         if (std::ranges::starts_with(ustrview(fr, sv.end()), "'UTF-8")) {
//           if (fr == sv.end() || *fr++ != '\'') throw std::invalid_argument(format("xml::root: xml declaration is not well-formed"));
//           declaration["encoding"] = ustrview(fr, sv.end());
//         } else if (std::ranges::starts_with(ustrview(fr, sv.end()), "\"UTF-8")) {
//           if (fr == sv.end() || *fr++ != '"') throw std::invalid_argument(format("xml::root: xml declaration is not well-formed"));
//           declaration["encoding"] = ustrview(fr, sv.end());
//         } else throw std::invalid_argument(format("xml::root: xml declaration is not well-formed"));
//       } else throw std::invalid_argument(format("xml::root: xml declaration is not well-formed"));
//     } else throw std::invalid_argument(format("xml::root: xml declaration is not well-formed"));
//   }
// };

// inline ustr open(const path& File) {
// }

// /// [5] `Name ::= NameStartChar (NameChar)*`
// /// \return name
// constexpr ustrview get_name(ustrview& s, const ustrview& Document) {
//   auto fr = s.begin();
//   if (fr == s.end() || !is_name_start_char(*fr++)) throw exception(fr, Document, "`Name` does not start with 'NameStartChar");
//   while (fr != s.end() && is_name_char(*fr)) ++fr;
//   s = ustrview{fr, s.end()};
//   return ustrview{s.begin(), fr};
// }

// /// [14] `CharData ::= [^<&]* - ([^<&]*']]>' [^<&]*)

// /// [15] `Comment ::= '<!--' ((Char - '-') | ('-' (Char - '-')))* '-->'`
// /// \return comment content; may start/end with spaces
// constexpr ustrview get_comment(ustrview& s, const ustrview& Document) {
//   auto fr = s.begin();
//   if (fr == s.end() || *fr++ != '<') throw exception(fr, Document, "`Comment` must start with '<!--'");
//   if (fr == s.end() || *fr++ != '!') throw exception(fr, Document, "`Comment` must start with '<!--'");
//   if (fr == s.end() || *fr++ != '-') throw exception(fr, Document, "`Comment` must start with '<!--'");
//   if (fr == s.end() || *fr++ != '-') throw exception(fr, Document, "`Comment` must start with '<!--'");
//   if (fr == s.end() || !is_char(*fr) || *fr == '-') throw exception(fr, Document, "`Comment` has invalid char after '<!--'");
//   auto sr = std::ranges::search(ustrview(fr, s.end()), ustrview{U"-->"});
//   if (sr.empty()) throw exception(fr, Document, "`Comment` must end with '-->'");
//   s = ustrview{sr.end(), s.end()};
//   return ustrview{fr, sr.begin()};
// }

// /// [17] `PITarget ::= Name - (('X' | 'x') ('M' | 'm') ('L' | 'l'))`
// /// \return target name as `ustr`
// constexpr ustrview get_pi_target(ustrview& s, const ustrview& Document) {
//   auto name = get_name(s, Document);
//   if (name.size() == 3 && (name[0] & ~0x10) == 'X' && (name[1] & ~0x10) == 'M' && (name[2] & ~0x10) == 'L')
//     throw exception(name.begin(), Document, "`PITarget` must not be 'XML'");
//   return name;
// }

// /// [16] `PI ::= '<?' PITarget (S (Char* - (Char* '?>' char*)))? '?>'`
// constexpr tuple<ustrview, ustrview> get_pi(ustrview& s, const ustrview& Document) {
//   auto fr = s.begin();
//   if (fr == s.end() || *fr++ != '<') throw exception(fr, Document, "`PI` must start with '<?'");
//   if (fr == s.end() || *fr++ != '?') throw exception(fr, Document, "`PI` must start with '<?'");
//   s = ustrview{fr, s.end()};
//   auto target = get_pi_target(s, Document);
//   fr = target.end();
//   if (fr == s.end()) throw exception(fr, Document, "`PI` must end with '?>'");
//   if (*fr++ == '?') {
//     if (fr == s.end() || *fr++ != '>') throw exception(fr, Document, "`PI` must end with '?>'");
//     s = ustrview{fr, s.end()};
//     return {target, {}};
//   } else if (is_space_char(*fr)) {
//     fr = std::ranges::find_if_not(ustrview(fr, s.end()), [](const char32_t u) { return is_space_char(u); });
//     auto sr = std::ranges::search(ustrview(fr, s.end()), ustrview{U"?>"});
//     if (sr.empty()) throw exception(fr, Document, "`PI` must end with '?>'");
//     s = ustrview{sr.end(), s.end()};
//     return {target, ustrview{fr, s.begin()}};
//   } else throw exception(fr, Document, "`PI` must end with '?>'");
// }



// /// [27] `Misc ::= Comment | PI | S`

// }
// }
