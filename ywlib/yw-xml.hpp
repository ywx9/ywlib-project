#pragma once
#include <ywlib>

namespace yw {

/// xml document handler
class xml {
  ustr raw;
  ustr convert(const str& s) {
    if (s.size() < 4) throw std::invalid_argument("invalid XML");
    if (s[1] != '0') return unicode<uchar>(s);
    else if (s[2] != '0') return unicode<uchar>(wstrview((const wchar_t*)s.data(), s.size() / 2));
    else return unicode<uchar>(ustrview((const uchar*)s.data(), s.size() / 4));
  }
public:
  /// exception class thrown by xml parser; derived from `std::runtime_error`
  class exception : public std::runtime_error {
    static constexpr vector2<int> position_in_document(const ustrview::iterator Current, const ustrview& Document) {
      if (Current < Document.begin() || Current > Document.end()) throw std::invalid_argument("Invalid position");
      int line = 1, column = 1;
      for (auto it = Document.begin(); it != Current; ++it) *it == '\n' ? ++line, column = 1 : ++column;
      return {line, column};
    }
    static std::runtime_error create(const ustrview::iterator p, const ustrview d, const char* m) {
      auto [line, column] = position_in_document(p, d);
      auto s{format("yw-xml error at ({},{}); {}", line, column, m)};
      return std::runtime_error(s);
    }
  public:
    exception(const ustrview::iterator Position, const ustrview& Document, const char* Message)
      : std::runtime_error(create(Position, Document, Message)) {}
  };

  /// `PI`
  struct processing_instruction {
    ustrview target, data;
  };

  /// `Comment`
  struct comment {
    ustrview data;
  };

  /// `Text`
  struct text {
    ustrview data;
  };

  /// `Attribute`
  struct attribute {
    ustrview name, value;
  };

  /// `Element`
  struct element {
    ustrview name;
    std::vector<attribute> attributes;
    std::vector<std::variant<comment, processing_instruction, text, element>> children;
  };

  /// `DocumentTypeDeclaration`
  struct doctypedecl {
    ustrview name, keyword, fri, uri;
  };

  /// helper functions
  struct helper {
    /// returns `true` if the character is an alphabetic character
    static constexpr auto is_alphabet = [](const uchar c) noexcept {
      return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z');
    };
    /// returns `true` if the character is a valid XML character
    static constexpr auto is_character = [](const uchar c) noexcept {
      return c == 0x9 || c == 0xa || c == 0xd || (0x20 <= c && c <= 0xd7ff) || (0xe000 <= c && (c & 0xfffe) != 0xfffe);
    };
    /// returns `true` if the character is a digit
    static constexpr auto is_digit = [](const uchar c) noexcept {
      return '0' <= c && c <= '9';
    };
    /// returns `true` if the character can be used for encoding names
    static constexpr auto is_encname = [](const uchar c) noexcept {
      return is_alphabet(c) || is_digit(c) || c == '-' || c == '_' || c == '.';
    };
    /// returns `true` if the character can be used for names except the first character
    static constexpr auto is_namechar = [](const uchar c) noexcept {
      return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || ('0' <= c && c <= ':') || c == '.' || c == '_' ||
             (c == 0xb7) || (0xc0 <= c && c <= 0x2ff && c != 0xd7 && c != 0xf7) ||
             (0x300 <= c && c <= 0x1fff && c != 0x37e) || c == 0x200c || c == 0x200d || c == 0x203f || c == 0x2040 ||
             (0x2070 <= c && c <= 0x218f) || (0x2c00 <= c && c <= 0x2fef) || (0x3001 <= c && c <= 0xd7ff) ||
             (0xf900 <= c && c <= 0xfdcf) || (0xfdf0 <= c && (c & 0xfffe) != 0xfffe);
    };
    /// returns `true` if the character can be used as the first character of a name
    static constexpr auto is_namestartchar = [](const uchar c) noexcept {
      return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || c == ':' || c == '_' ||
             (0xc0 <= c && c <= 0x2ff && c != 0xd7 && c != 0xf7) ||
             (0x370 <= c && c <= 0x1fff && c != 0x37e) || c == 0x200c || c == 0x200d ||
             (0x2070 <= c && c <= 0x218f) || (0x2c00 <= c && c <= 0x2fef) || (0x3001 <= c && c <= 0xd7ff) ||
             (0xf900 <= c && c <= 0xfdcf) || (0xfdf0 <= c && (c & 0xfffe) != 0xfffe);
    };
    /// returns `true` if the character can be used in a public identifier
    static constexpr auto is_pubidchar = [](const uchar c) noexcept {
      return c == 0xd || c == 0xa || (0x5f <= c && c <= 0x7a && (c != 0x60)) ||
             (0x20 <= c && c <= 0x90 && (c != 0x22 && c != 0x26 && c != 0x60 && c != 0x62 && c != 0x64));
    };
    /// returns `true` if the character is a whitespace character
    static constexpr auto is_whitespace = [](const uchar c) noexcept {
      return c == 0x20 || c == 0x9 || c == 0xd || c == 0xa;
    };
    /// extracts `S ::= whitespaces`
    static constexpr ustrview extract_whitespaces(ustrview& sv) {
      auto it = std::ranges::find_if_not(sv, helper::is_whitespace);
      ustrview result{sv.begin(), it};
      sv = ustrview(result.end(), sv.end());
      return result;
    }
    /// extracts `Eq ::= S? '=' S?`
    static constexpr ustrview extract_equal(ustrview& sv) {
      auto it = std::ranges::find_if_not(sv, helper::is_whitespace);
      if (it == sv.end() || *it++ != '=') return {};
      ustrview result(sv.begin(), std::ranges::find_if_not(it, sv.end(), helper::is_whitespace));
      sv = ustrview(result.end(), sv.end());
      return result;
    }
    /// extracts `Name ::= NameStartChar NameChar*`
    static constexpr ustrview extract_name(ustrview& sv, const ustr& Raw) {
      if (sv.empty() || !helper::is_namestartchar(*sv.begin())) return {};
      auto result = ustrview(sv.begin(), std::ranges::find_if_not(sv, helper::is_namechar));
      sv          = ustrview(result.end(), sv.end());
      return result;
    }
    /// extracts `PubidLiteral ::= '"' PubidChar* '"' | "'" PubidChar* "'"`
    static constexpr ustrview extract_pubidliteral(ustrview& sv, const ustr& Raw) {
      if (sv.empty()) throw exception(sv.begin(), Raw, "invalid PubidLiteral; PubidLiteral must start with '\"' or \"'\"");
      uchar quote = sv.front();
      if (quote != '"' && quote != '\'') throw exception(sv.begin(), Raw, "invalid PubidLiteral; PubidLiteral must start with '\"' or \"'\"");
      sv.remove_prefix(1);
      ustrview result(sv.begin(), std::ranges::find(sv, quote));
      if (result.end() == sv.end()) throw exception(sv.begin(), Raw, "unclosed PubidLiteral; PubidLiteral must end with '\"' or \"'\"");
      sv = ustrview(result.end() + 1, sv.end());
      return result;
    }
    /// extracts `SystemLiteral ::= '"' [^"]* '"' | "'" [^']* "'"`
    static constexpr ustrview extract_systemliteral(ustrview& sv, const ustr& Raw) {
      if (sv.empty()) throw exception(sv.begin(), Raw, "invalid SystemLiteral; SystemLiteral must start with '\"' or \"'\"");
      uchar quote = sv.front();
      if (quote != '"' && quote != '\'') throw exception(sv.begin(), Raw, "invalid SystemLiteral; SystemLiteral must start with '\"' or \"'");
      sv.remove_prefix(1);
      auto it = std::ranges::find(sv, quote);
      if (it == sv.end()) throw exception(sv.begin(), Raw, "unclosed SystemLiteral; SystemLiteral must end with '\"' or \"'");
      ustrview result(sv.begin(), it);
      sv = ustrview(it + 1, sv.end());
      return result;
    }
    /// extracts `Comment`
    static constexpr comment extract_comment(ustrview& sv, const ustr& Raw) {
      if (!sv.starts_with(U"<!--"sv)) throw exception(sv.begin(), Raw, "invalid comment; comment must start with '<!--'");
      auto comment_start = sv.begin() + 4;
      if (comment_start == sv.end()) throw exception(sv.begin(), Raw, "unclosed comment");
      if (*comment_start == '-') throw exception(sv.begin(), Raw, "invalid comment; comment must not start with '<!---'");
      auto sr = std::ranges::search(ustrview(comment_start, sv.end()), U"-->"sv);
      if (sr.empty()) throw exception(sv.begin(), Raw, "unclosed comment");
      if (!std::ranges::search(ustrview(comment_start, sr.begin()), U"--"sv))
        throw exception(sv.begin(), Raw, "invalid comment; comment must not contain '--'");
      comment c{ustrview(comment_start, sr.begin())};
      sv = ustrview(sr.end(), sv.end());
      return c;
    }
    /// extracts `PI`
    static constexpr processing_instruction extract_pi(ustrview& sv, const ustr& Raw) {
      if (!sv.starts_with(U"<?"sv)) throw exception(sv.begin(), Raw, "invalid PI; processing instruction must start with '<?'");
      sv.remove_prefix(2);
      auto target = helper::extract_name(sv, Raw);
      if (target.size() == 3 && (target[0] & ~0x10) == 'X' && (target[1] & ~0x10) == 'M' && (target[2] & ~0x10) == 'L')
        throw exception(sv.begin(), Raw, "invalid PI; PI target must not be 'XML'");
      auto space = helper::extract_whitespaces(sv);
      if (space.empty()) {
        if (!sv.starts_with(U"?>"sv)) throw exception(sv.begin(), Raw, "invalid PI; processing instruction must end with '?>'");
        sv.remove_prefix(2);
        return processing_instruction{target, {}};
      } else {
        auto sr = std::ranges::search(sv, U"?>"sv);
        if (sr.empty()) throw exception(sv.begin(), Raw, "unclosed processing instruction");
        if (sr.begin() == sv.begin()) return processing_instruction{target, {}};
        ustrview data{sv.begin(), sr.begin()};
        if (!std::ranges::all_of(data, helper::is_character))
          throw exception(sv.begin(), Raw, "invalid PI; processing instruction data must contain valid XML characters");
        return processing_instruction{target, data};
      }
    }
    /// extracts `Misc ::= Comment | PI | S`
    static constexpr std::variant<comment, processing_instruction> extract_misc(ustrview& sv, const ustr& Raw) {
      try {
        auto sv2     = sv;
        auto comment = extract_comment(sv2, Raw);
        sv           = sv2;
        return comment;
      } catch (const exception&) {}
      try {
        auto pi = extract_pi(sv, Raw);
        sv.remove_prefix(2); // remove '?>'
        return pi;
      } catch (const exception&) {}
      auto whitespace = extract_whitespaces(sv);
      return whitespace.empty() ? std::variant<comment, processing_instruction>{} : extract_misc(sv, Raw);
    }
    /// extracts `doctypedecl ::= 'DOCTYPE' S? Name (S ExternalID)? S? ('[' intSubset ']' S?)? '>'`
    static constexpr doctypedecl extract_dtd(ustrview& sv, const ustr& Raw) {
      doctypedecl dtd;
      if (!sv.starts_with(U"<!DOCTYPE"sv)) throw exception(sv.begin(), Raw, "invalid DOCTYPE declaration");
      sv.remove_prefix(9);
      auto whitespace = helper::extract_whitespaces(sv);
      if (whitespace.empty()) throw exception(sv.begin(), Raw, "invalid DOCTYPE declaration; whitespace is required");
      dtd.name = helper::extract_name(sv, Raw);
      if (dtd.name.empty()) throw exception(sv.begin(), Raw, "invalid DOCTYPE declaration; name is required");
      whitespace = helper::extract_whitespaces(sv);
      if (!whitespace.empty()) {
        if (sv.starts_with(U"'PUBLIC'"sv)) {
          sv.remove_prefix(8);
          whitespace = helper::extract_whitespaces(sv);
          if (whitespace.empty()) throw exception(sv.begin(), Raw, "invalid DOCTYPE declaration; whitespace is required");
          dtd.fri    = helper::extract_pubidliteral(sv, Raw);
          whitespace = helper::extract_whitespaces(sv);
          if (whitespace.empty()) throw exception(sv.begin(), Raw, "invalid DOCTYPE declaration; whitespace is required");
          dtd.uri = helper::extract_systemliteral(sv, Raw);
        } else if (sv.starts_with(U"'SYSTEM'"sv)) {
          sv.remove_prefix(8);
          whitespace = helper::extract_whitespaces(sv);
          if (whitespace.empty()) throw exception(sv.begin(), Raw, "invalid DOCTYPE declaration; whitespace is required");
          dtd.fri = helper::extract_pubidliteral(sv, Raw);
        } else throw exception(sv.begin(), Raw, "invalid DOCTYPE declaration; unrecognized keyword");
        helper::extract_whitespaces(sv);
      }
      if (sv.empty()) throw exception(sv.begin(), Raw, "invalid DOCTYPE declaration");
      if (sv.front() == '[') throw exception(sv.begin(), Raw, "internal subset is not supported");
      if (sv.front() != '>') throw exception(sv.begin(), Raw, "invalid DOCTYPE declaration; '>' is required");
      sv.remove_prefix(1);
    }
  };
  double version{};
  ustrview encoding;
  bool standalone{};
  std::vector<std::variant<comment, processing_instruction>> miscs;
  element root;
  std::vector<std::variant<comment, processing_instruction>> miscs_after_root;
  constexpr xml() = default;
  constexpr xml(ustr&& Text) : raw(mv(Text)) { analyze(); }
  constexpr xml(stringable auto&& Text) : raw(unicode<uchar>(Text)) { analyze(); }
  constexpr xml(const path& File) : raw(convert(File.read())) { analyze(); }
private:
  constexpr void analyze() {
    ustrview sv = raw;
    // analyzes XML declaration
    if (std::ranges::starts_with(sv, U"<?xml"sv)) {
      sv.remove_prefix(5);
      auto whitespaces = helper::extract_whitespaces(sv);
      if (whitespaces.empty()) throw exception(sv.begin(), raw, "whitespaces are required after '<?xml'");
      if (!sv.starts_with(U"version"sv)) throw exception(sv.begin(), raw, "'version' is required");
      sv.remove_prefix(7);
      auto eq = helper::extract_equal(sv);
      if (eq.empty()) throw exception(sv.begin(), raw, "'=' is required");
      if (!sv.starts_with(U"1."sv)) throw exception(sv.begin(), raw, "version number must start with '1.'");
      auto version_number_start = sv.begin();
      sv.remove_prefix(2);
      if (sv.empty() || helper::is_digit(sv.front())) throw exception(sv.begin(), raw, "at least one digit is required after '1.'");
      auto version_number_end = std::ranges::find_if_not(sv.begin() + 1, sv.end(), helper::is_digit);
      if (version_number_end == sv.end()) throw exception(version_number_end, raw, "invalid xml document");
      version = stof(ustrview(version_number_start, version_number_end));
      helper::extract_whitespaces(sv);
      if (sv.starts_with(U"encoding"sv)) {
        sv.remove_prefix(8);
        eq = helper::extract_equal(sv);
        if (eq.empty()) throw exception(sv.begin(), raw, "'=' is required");
        if (sv.empty()) throw exception(sv.begin(), raw, "invalid encoding value");
        auto quote = sv.front();
        if (quote != '"' && quote != '\'') throw exception(sv.begin(), raw, "invalid encoding value");
        auto encoding_start = sv.begin() + 1;
        auto encoding_end   = std::ranges::find_if_not(encoding_start, sv.end(), helper::is_encname);
        if (encoding_end == sv.end() || *encoding_end != quote) throw exception(sv.begin(), raw, "invalid encoding value");
        encoding = ustrview(encoding_start, encoding_end);
        sv       = ustrview(encoding_end + 1, sv.end());
        helper::extract_whitespaces(sv);
      }
      if (sv.starts_with(U"standalone"sv)) {
        sv.remove_prefix(10);
        eq = helper::extract_equal(sv);
        if (eq.empty()) throw exception(sv.begin(), raw, "'=' is required");
        if (sv.empty()) throw exception(sv.begin(), raw, "invalid standalone value");
        auto quote = sv.front();
        if (quote != '"' && quote != '\'') throw exception(sv.begin(), raw, "invalid standalone value");
        sv.remove_prefix(1);
        if (sv.starts_with(U"yes"sv) && !(sv.remove_prefix(3), sv).empty() && sv.front() == quote) standalone = true;
        else if (sv.starts_with(U"no"sv) && !(sv.remove_prefix(2), sv).empty() && sv.front() == quote) standalone = false;
        else throw exception(sv.begin(), raw, "invalid standalone value");
        sv.remove_prefix(1);
        helper::extract_whitespaces(sv);
      }
      if (!sv.starts_with(U"?>"sv)) throw exception(sv.begin(), raw, "invalid XML declaration");
      sv.remove_prefix(2);
    }
    // analyzes miscs
    auto misc = helper::extract_misc(sv, raw);
    while (!(misc.index() == 0 && f::get<0>(misc).data.empty())) {
      if (std::holds_alternative<comment>(misc)) miscs.push_back(std::get<0>(misc));
      else if (std::holds_alternative<processing_instruction>(misc)) miscs.push_back(std::get<1>(misc));
      else throw exception(sv.begin(), raw, "invalid miscellaneous content");
    }
    // analyzes root-element
  }
};

// };

// int analyze_dtd(ustrview& sv) {
//   if (!std::ranges::starts_with(sv, U"<!DOCTYPE"sv)) return 0;
//   sv.remove_prefix(8);
//   auto it = std::ranges::find_if_not(sv, is_whitespace);
//   if (it == sv.begin()) throw exception(sv.begin(), raw, "Invalid DOCTYPE declaration; whitespaces expected");
//   if (it == sv.end()) throw exception(sv.begin(), raw, "Invalid DOCTYPE declaration");
//   if (!is_namestartchar(*it)) throw exception(sv.begin(), raw, "Invalid DOCTYPE declaration; invalid root element");
//   auto root_element_start = it++;
//   auto root_element_end   = std::ranges::find_if_not(it, sv.end(), is_namechar);
//   if (root_element_end == sv.end()) throw exception(it, raw, "Invalid DOCTYPE declaration; invalid root element");
//   dtd.root_element = ustrview(root_element_start, root_element_end);
//   sv               = ustrview(std::ranges::find_if_not(root_element_end, sv.end(), is_whitespace), sv.end());
//   if (std::ranges::starts_with(sv, U"PUBLIC"sv)) {
//     sv.remove_prefix(6);
//     sv = ustrview(std::ranges::find_if_not(sv, is_whitespace), sv.end());
//     if
//   }
// }
// int analyze_miscs(ustrview& sv) {
//   if (std::ranges::starts_with(sv, U"<!--"sv)) {
//     sv.remove_prefix(4);
//     if (sv.empty()) throw exception(sv.begin(), raw, "comment must end with -->");
//     if (sv.front() == '-') throw exception(sv.begin(), raw, "comment must not start with <---");
//     sv.remove_prefix(1);
//     auto sr = std::ranges::search(sv, U"-->"sv);
//     if (sr.empty()) throw exception(sv.begin(), raw, "comment must end with -->");
//     sv = ustrview(sr.begin(), sr.end());
//     analyze_miscs(sv);
//   } else if (std::ranges::starts_with(sv, U"<?"sv)) {
//     sv.remove_prefix(2);
//     auto target = get_name(sv);
//     if (target.empty()) throw exception(sv.begin(), raw, "invalid processing instruction target");
//     if (target.size() == 3 && (target[0] & ~0x10) == 'X' && (target[1] & ~0x10) == 'M' && (target[2] & ~0x10) == 'L')
//       throw exception(sv.begin(), raw, "invalid processing instruction target");
//     sv.remove_prefix(target.size());
//     auto sr = std::ranges::search(sv, U"?>"sv);
//     if (sr.empty()) throw exception(sv.begin(), raw, "processing instruction must end with ?>");
//     pi.push_back({
//       target, ustrview{sv.begin(), sr.begin()}
//     });
//     sv = ustrview(sr.begin(), sv.end());
//     analyze_miscs(sv);
//   } else if (!sv.empty() && is_whitespace(sv.front())) {
//     sv = ustrview(std::ranges::find_if_not(sv, is_whitespace), sv.end());
//     analyze_miscs(sv);
//   } else return 0;
// }
// int analyze_xmldecl(ustrview& sv) {
//   if (!std::ranges::starts_with(sv, U"<?xml"sv)) return 0; // xml declaration may be missing
//   sv.remove_prefix(5);
//   sv = ustrview(std::ranges::find_if_not(sv, is_whitespace), sv.end());
//   if (!std::ranges::starts_with(sv, U"version"sv)) throw exception(sv.begin(), raw, "Invalid XML version");
//   sv.remove_prefix(8);
//   sv = ustrview(std::ranges::find_if_not(sv, is_whitespace), sv.end());
//   if (sv.empty() || sv.front() != U'=') throw exception(sv.begin(), raw, "Invalid XML version");
//   sv.remove_prefix(1);
//   sv = ustrview(std::ranges::find_if_not(sv, is_whitespace), sv.end());
//   if (sv.empty()) throw exception(sv.begin(), raw, "Invalid XML version");
//   auto quote = sv.front();
//   sv.remove_prefix(1);
//   if (!std::ranges::starts_with(sv, U"1."sv)) throw exception(sv.begin(), raw, "Invalid XML version");
//   auto version_num_start = sv.begin();
//   sv.remove_prefix(2);
//   if (sv.empty() || !is_digit(sv.front())) throw exception(sv.begin(), raw, "Invalid XML version");
//   sv.remove_prefix(1);
//   sv = ustrview(std::ranges::find_if_not(sv, is_digit), sv.end());
//   auto version_num_end{sv.begin()};
//   if (sv.empty() || sv.front() != quote) throw exception(sv.begin(), raw, "Invalid XML version");
//   sv.remove_prefix(1);
//   { // sets version
//     double a{1};
//     version = 1;
//     for (auto it = version_num_start; it != version_num_end; ++it)
//       version = version * 10 + (*it - '0'), a *= 10;
//     version /= a;
//   }
//   sv = ustrview(std::ranges::find_if_not(sv, is_whitespace), sv.end());
//   if (std::ranges::starts_with(sv, U"encoding"sv)) {
//     sv.remove_prefix(8);
//     sv = ustrview(std::ranges::find_if_not(sv, is_whitespace), sv.end());
//     if (sv.empty() || sv.front() != U'=') throw exception(sv.begin(), raw, "Invalid XML encoding");
//     sv.remove_prefix(1);
//     sv = ustrview(std::ranges::find_if_not(sv, is_whitespace), sv.end());
//     if (sv.empty()) throw exception(sv.begin(), raw, "Invalid XML encoding");
//     auto quote = sv.front();
//     sv.remove_prefix(1);
//     if (sv.empty() || !is_alphabet(sv.front())) throw exception(sv.begin(), raw, "Invalid XML encoding");
//     auto encoding_start{sv.begin()};
//     sv.remove_prefix(1);
//     sv = ustrview(std::ranges::find_if_not(sv, is_encname), sv.end());
//     auto encoding_end{sv.begin()};
//     if (sv.empty() || sv.front() != quote) throw exception(sv.begin(), raw, "Invalid XML encoding");
//     sv.remove_prefix(1);
//     encoding = ustrview(encoding_start, encoding_end);
//   }
//   sv = ustrview(std::ranges::find_if_not(sv, is_whitespace), sv.end());
//   if (std::ranges::starts_with(sv, U"standalone"sv)) {
//     sv.remove_prefix(10);
//     sv = ustrview(std::ranges::find_if_not(sv, is_whitespace), sv.end());
//     if (sv.empty() || sv.front() != U'=') throw exception(sv.begin(), raw, "Invalid XML standalone");
//     sv.remove_prefix(1);
//     sv = ustrview(std::ranges::find_if_not(sv, is_whitespace), sv.end());
//     if (sv.empty()) throw exception(sv.begin(), raw, "Invalid XML standalone");
//     auto quote = sv.front();
//     sv.remove_prefix(1);
//     if (std::ranges::starts_with(sv, U"yes"sv)) standalone = true, sv.remove_prefix(3);
//     else if (std::ranges::starts_with(sv, U"no"sv)) standalone = false, sv.remove_prefix(2);
//     else throw exception(sv.begin(), raw, "Invalid XML standalone");
//     if (sv.empty() || sv.front() != quote) throw exception(sv.begin(), raw, "Invalid XML standalone");
//     sv.remove_prefix(1);
//   }
//   sv = ustrview(std::ranges::find_if_not(sv, is_whitespace), sv.end());
//   if (!std::ranges::starts_with(sv, U"?>")) throw exception(sv.begin(), raw, "Invalid XML declaration");
// }
// public:
// };
// }

// namespace yw::Xml {

// /// returns the position (line, column) of the given iterator in the document
// constexpr vector2<int> position_in_document(const ustrview::iterator Current, const ustrview& Document) {
//   if (Current < Document.begin() || Current > Document.end()) throw std::invalid_argument("Invalid position");
//   int line = 1, column = 1;
//   for (auto it = Document.begin(); it != Current; ++it) *it == '\n' ? ++line, column = 1 : ++column;
//   return {line, column};
// }

// /// exception class for XML errors
// class exception : public std::runtime_error {
//   static std::runtime_error create(const ustrview::iterator p, const ustrview d, const char* m) {
//     auto [line, column] = position_in_document(p, d);
//     auto s              = format("yw-xml: error at ({},{}) {}", line, column, m);
//     return std::runtime_error(s);
//   }
// public:
//   exception(const ustrview::iterator Position, const ustrview& Document, const char* Message)
//     : std::runtime_error(create(Position, Document, Message)) {}
// };

// /// xml definition ids
// enum class id {
//   invalid,
//   document,
//   character,  // Char
//   whitespace, // S
//   namestartchar,
//   namechar = namestartchar,
//   name,
//   names,
//   nmtoken,
//   nmtokens,
//   entityvalue,
//   attvalue,
//   systemliteral,
//   pubidliteral,
//   pubidchar,
//   chardata,
//   comment,
//   pi,
//   pitarget,
//   cdsect,
//   cdstart,
//   cdata,
//   cdend,
//   prolog,
//   xmldecl,
//   versioninfo,
//   eq,
//   versionnum,
//   misc,
//   doctypedecl,
//   declsep   = doctypedecl,
//   intsubset = doctypedecl,
//   markupdecl,
//   extsubset,
//   extsubsetdecl,
//   sddecl,
//   element = 39,
//   stag,
//   attribute,
//   etag,
//   content,
//   emptyelemtag,
//   elementdecl,
//   contentspec,
//   children,
//   cp,
//   choice,
//   seq,
//   mixed,
//   attlistdecl,
//   attdef,
//   atttype,
//   stringtype,
//   tokenizedtype,
//   enumeratedtype,
//   notationtype,
//   enumeration,
//   defaultdecl,
//   conditionalsect,
//   includesect,
//   ignoresect,
//   ignoresectcontents,
//   ignore,
//   charref,
//   reference,
//   entityref,
//   pereference,
//   entitydecl,
//   gedecl,
//   pedecl,
//   entitydef,
//   pedef,
//   externalid,
//   ndatadecl,
//   textdecl,
//   extparsedent,
//   encodingdecl = 80,
//   encname,
//   notationdecl,
//   publicid,
//   letter,
//   basechar,
//   ideographic,
//   combiningchar,
//   digit,
//   extender,
// };

// /// returns `Xmldecl` and removes it from the input string
// constexpr ustrview get_xmldecl(ustrview& s, const ustrview& Document) {
//   auto start = s.begin();
//   if (!std::ranges::starts_with(s, ustrview(U"<?xml")))
//     throw exception(s.begin(), Document, "`Xmldecl` must start with <?xml");
//   s.remove_prefix(5);
//   get_versioninfo(s, Document);
//   try {
//     auto s2 = s;
//     get_encodingdecl(s2, Document);
//     s = s2;
//   } catch (const exception& e) {}
//   try {
//     auto s2 = s;
//     get_sddecl(s2, Document);
//     s = s2;
//   } catch (const exception& e) {}
//   auto end = std::ranges::find_if_not(s, is_whitespace);
//   if (!std::ranges::starts_with(ustrview{end, s.end()}, ustrview(U"?>")))
//     throw exception(s.begin(), Document, "`Xmldecl` must end with ?>");
//   ustrview result{start, end + 2};
//   s = ustrview{end + 2, s.end()};
//   return result;
// }

// /// returns `Prolog` and removes it from the input string
// constexpr ustrview get_prolog(
//   ustrview& s, const ustrview& Document, ustrview* xmldecl = nullptr, //
//   ustrview* misc1 = nullptr, ustrview* doctypedecl = nullptr, ustrview* misc2 = nullptr) {
//   auto start = s.begin();
//   try {
//     auto s2 = s;
//     if (xmldecl) *xmldecl = get_xmldecl(s2, Document);
//     else get_xmldecl(s2, Document);
//     s = s2;
//   } catch (const exception& e) {}
//   auto it = s.begin();
//   while (!s.empty()) {
//     try {
//       auto s2 = s;
//       get_misc(s2, Document);
//       s = s2;
//     } catch (const exception& e) { break; }
//   }
//   if (misc1) *misc1 = ustrview{it, s.begin()};
//   try {
//     auto s2 = s;
//     if (doctypedecl) *doctypedecl = get_doctypedecl(s2, Document);
//     else get_doctypedecl(s2, Document);
//     s  = s2;
//     it = s.begin();
//     while (!s.empty()) {
//       try {
//         s2 = s;
//         get_element(s2, Document);
//         s = s2;
//       } catch (const exception& e) { break; }
//     }
//     if (misc2) *misc2 = ustrview{it, s.begin()};
//   } catch (const exception& e) { return ustrview(start, s.begin()); }
// }

// /// returns `Document` and removes it from the input string
// constexpr ustrview get_document(
//   ustrview& s, const ustrview& Document, ustrview* prolog = nullptr, //
//   ustrview* element = nullptr, ustrview* misc = nullptr) {
//   auto start = s.begin();
//   if (prolog) *prolog = get_prolog(s, Document);
//   else get_prolog(s, Document);
//   if (element) *element = get_element(s, Document);
//   else get_element(s, Document);
//   auto it = s.begin();
//   while (!s.empty()) {
//     try {
//       auto s2 = s;
//       get_misc(s2, Document);
//       s = s2;
//     } catch (const exception& e) { break; }
//   }
//   if (misc) *misc = ustrview{it, s.begin()};
//   return ustrview{start, s.begin()};
// }

// /// returns `true` if the character is `Char`

// /// returns `S` and removes it from the input string
// constexpr ustrview get_whitespace(ustrview& s, const ustrview& Document) {
//   auto it = std::ranges::find_if_not(s, is_whitespace);
//   ustrview result{s.begin(), it};
//   s = ustrview{it, s.end()};
//   return result;
// }

// /// returns `true` if the character is `NameStartChar`

// /// returns `Name` and removes it from the input string
// constexpr ustrview get_name(ustrview& s, const ustrview& Document) {
//   auto it = s.begin();
//   if (s.empty() || !is_namestartchar(*it)) throw exception(it, Document, "`Name` must start with 'NameStartChar'");
//   it = std::ranges::find_if_not(ustrview{it + 1, s.end()}, is_namechar);
//   ustrview result{s.begin(), it};
//   s = ustrview{it, s.end()};
//   return result;
// }

// // `Names` is not used.

// /// returns `Nmtoken` and removes it from the input string
// constexpr ustrview get_nmtoken(ustrview& s, const ustrview& Document) {
//   auto it = s.begin();
//   if (s.empty() || !is_namechar(*it)) throw exception(it, Document, "`Nmtoken` must start with 'NameChar'");
//   it = std::ranges::find_if_not(ustrview{it + 1, s.end()}, is_namechar);
//   ustrview result{s.begin(), it};
//   s = ustrview{it, s.end()};
//   return result;
// }

// /// returns `Nmtokens` and removes it from the input string
// constexpr ustrview get_nmtokens(ustrview& s, const ustrview& Document) {
//   auto start = s.begin();
//   get_nmtoken(s, Document);
//   while (!s.empty()) {
//     try {
//       if (s.front() != 0x20) break;
//       auto s2 = s;
//       get_nmtoken(s2, Document);
//       s = s2;
//     } catch (const exception& e) { break; }
//   }
//   return ustrview{start, s.begin()};
// }

// /// returns `EntityValue` and removes it from the input string
// constexpr ustrview get_entityvalue(ustrview& s, const ustrview& Document) {
//   ustrview::iterator start = s.begin(), end;
//   if (s.empty()) throw exception(s.begin(), Document, "`EntityValue` must start with \" or '");
//   if (s.front() == '"') end = std::ranges::find(ustrview{s.begin() + 1, s.end()}, '"');
//   else if (s.front() == '\'') end = std::ranges::find(ustrview{s.begin() + 1, s.end()}, '\'');
//   else throw exception(s.begin(), Document, "`EntityValue` must start with \" or '");
//   if (end == s.end()) throw exception(s.begin(), Document, "`EntityValue` must end with \" or '");
//   ustrview test{start + 1, end};
//   while (!test.empty()) {
//     if (test.front() == '%') get_pereference(test, Document);
//     else if (test.front() == '&') get_reference(test, Document);
//     else test.remove_prefix(1);
//   }
//   s = ustrview{end + 1, s.end()};
//   return ustrview{start, end + 1};
// }

// /// returns `AttValue` and removes it from the input string
// constexpr ustrview get_attvalue(ustrview& s, const ustrview& Document) {
//   ustrview::iterator start = s.begin(), end;
//   if (s.empty()) throw exception(s.begin(), Document, "`AttValue` must start with \" or '");
//   if (s.front() == '"') end = std::ranges::find(ustrview{s.begin() + 1, s.end()}, '"');
//   else if (s.front() == '\'') end = std::ranges::find(ustrview{s.begin() + 1, s.end()}, '\'');
//   else throw exception(s.begin(), Document, "`AttValue` must start with \" or '");
//   if (end == s.end()) throw exception(s.begin(), Document, "`AttValue` must end with \" or '");
//   ustrview test{start + 1, end};
//   while (!test.empty()) {
//     if (test.front() == '&') get_reference(test, Document);
//     else if (test.front() == '<') throw exception(test.begin(), Document, "`AttValue` must not contain '<'");
//     else test.remove_prefix(1);
//   }
//   s = ustrview{end + 1, s.end()};
//   return ustrview{start, end + 1};
// }

// /// returns `SystemLiteral` and removes it from the input string
// constexpr ustrview get_systemliteral(ustrview& s, const ustrview& Document) {
//   ustrview::iterator start = s.begin(), end;
//   if (s.empty()) throw exception(s.begin(), Document, "`SystemLiteral` must start with \" or '");
//   if (s.front() == '"') end = std::ranges::find(ustrview{s.begin() + 1, s.end()}, '"');
//   else if (s.front() == '\'') end = std::ranges::find(ustrview{s.begin() + 1, s.end()}, '\'');
//   else throw exception(s.begin(), Document, "`SystemLiteral` must start with \" or '");
//   if (end == s.end()) throw exception(s.begin(), Document, "`SystemLiteral` must end with \" or '");
//   s = ustrview{end + 1, s.end()};
//   return ustrview{start, end + 1};
// }

// /// returns `PubidLiteral` and removes it from the input string
// constexpr ustrview get_pubidliteral(ustrview& s, const ustrview& Document) {
//   ustrview::iterator start = s.begin(), end;
//   if (s.empty()) throw exception(s.begin(), Document, "`PubidLiteral` must start with \" or '");
//   if (s.front() == '"') end = std::ranges::find(ustrview{s.begin() + 1, s.end()}, '"');
//   else if (s.front() == '\'') end = std::ranges::find(ustrview{s.begin() + 1, s.end()}, '\'');
//   else throw exception(s.begin(), Document, "`PubidLiteral` must start with \" or '");
//   if (end == s.end()) throw exception(s.begin(), Document, "`PubidLiteral` must end with \" or '");
//   if (!std::ranges::all_of(ustrview{start + 1, end}, is_pubidchar)) throw exception(s.begin(), Document, "`PubidLiteral` must contain only PubidChars");
//   s = ustrview{end + 1, s.end()};
//   return ustrview{start, end + 1};
// }

// /// returns `true` if the character is `PubidChar`

// /// returns `Chardata` and removes it from the input string
// constexpr ustrview get_chardata(ustrview& s, const ustrview& Document) {
//   auto it = s.begin();
//   for (; it != s.end(); ++it) {
//     if (*it == '<' || *it == '&') break;
//     else if (*it == ']')
//       if (auto it2 = it + 1; it2 != s.end() && *it2++ == ']' && it2 != s.end() && *it2 == '>') break;
//   }
//   ustrview result{s.begin(), it};
//   s = ustrview{it, s.end()};
//   return result;
// }

// /// returns `Comment` and removes it from the input string
// constexpr ustrview get_comment(ustrview& s, const ustrview& Document) {
//   auto start = s.begin();
//   if (!std::ranges::starts_with(s, ustrview(U"<!--"))) throw exception(s.begin(), Document, "`Comment` must start with <!--");
//   start += 4;
//   if (start == s.end()) throw exception(s.end(), Document, "`Comment` must end with -->");
//   if (*start == '-') throw exception(start, Document, "`Comment` must not start with <!---");
//   auto end = std::ranges::search(ustrview{start, s.end()}, ustrview(U"-->")).begin();
//   if (end == s.end()) throw exception(s.begin(), Document, "`Comment` must end with -->");
//   if (!std::ranges::search(ustrview(start, end), ustrview(U"--")).empty()) throw exception(start, Document, "`Comment` must not contain --");
//   ustrview result(s.begin(), end + 3);
//   s = ustrview{end + 3, s.end()};
//   return result;
// }

// /// returns `PI` and removes it from the input string
// constexpr ustrview get_pi(ustrview& s, const ustrview& Document) {
//   auto start = s.begin();
//   if (!std::ranges::starts_with(s, ustrview(U"<?"))) throw exception(s.begin(), Document, "`PI` must start with <?");
//   s.remove_prefix(2);
//   get_pitarget(s, Document);
//   auto sr = std::ranges::search(s, ustrview(U"?>"));
//   if (sr.empty()) throw exception(s.begin(), Document, "`PI` must end with ?>");
//   ustrview test{s.begin(), sr.begin()};
//   inline constexpr auto test_fn = [](const uchar c) noexcept { return is_whitespace(c) || is_character(c); };
//   if (!std::ranges::all_of(test, test_fn)) throw exception(test.begin(), Document, "invalid PI");
//   ustrview result{s.begin(), sr.end()};
//   s = ustrview{sr.end(), s.end()};
//   return result;
// }

// /// returns `Pitarget` and removes it from the input string
// constexpr ustrview get_pitarget(ustrview& s, const ustrview& Document) {
//   auto name = get_name(s, Document);
//   if (name.size() == 3 && (name[0] & ~0x10) == 'X' && (name[1] & ~0x10) == 'M' && (name[2] & ~0x10) == 'L')
//     throw exception(name.begin(), Document, "`Pitarget` must not be XML");
//   return name;
// }

// /// returns `Cdsect` and removes it from the input string
// constexpr ustrview get_cdsect(ustrview& s, const ustrview& Document) {
//   auto start = s.begin();
//   get_cdstart(s, Document);
//   get_cdata(s, Document);
//   s.remove_prefix(3);
//   return ustrview{start, s.begin()};
// }

// /// returns `Cdstart` and removes it from the input string
// constexpr ustrview get_cdstart(ustrview& s, const ustrview& Document) {
//   auto start = s.begin();
//   if (!std::ranges::starts_with(s, ustrview(U"<![CDATA["))) throw exception(s.begin(), Document, "`Cdstart` must start with <![CDATA[");
//   s.remove_prefix(9);
//   return ustrview{start, s.begin()};
// }

// /// returns `Cdata` and removes it from the input string
// constexpr ustrview get_cdata(ustrview& s, const ustrview& Document) {
//   auto sr = std::ranges::search(s, ustrview(U"]]>"));
//   if (sr.empty()) throw exception(s.begin(), Document, "`Cdata` must end with ]]>");
//   ustrview result{s.begin(), sr.begin()};
//   s = ustrview{sr.end(), s.end()};
//   return result;
// }

// /// returns `Cdend` and removes it from the input string
// constexpr ustrview get_cdend(ustrview& s, const ustrview& Document) {
//   if (!std::ranges::starts_with(s, ustrview(U"]]>"))) throw exception(s.begin(), Document, "`Cdend` must start with ]]>");
//   ustrview result{s.begin(), s.begin() + 3};
//   s.remove_prefix(3);
//   return result;
// }

// /// returns `VersionInfo` and removes it from the input string
// constexpr ustrview get_versioninfo(ustrview& s, const ustrview& Document) {
//   auto start = s.begin();
//   auto it    = std::ranges::find_if_not(s, is_whitespace);
//   if (!std::ranges::starts_with(ustrview{it, s.end()}, ustrview(U"version")))
//     throw exception(s.begin(), Document, "`VersionInfo` must start with version=");
//   s.remove_prefix(8);
//   get_eq(s, Document);
//   if (s.empty()) throw exception(s.begin(), Document, "`VersionInfo` must have `VersionNum`");
//   if (s.front() == '"') {
//     s.remove_prefix(1);
//     get_versionnum(s, Document);
//     if (s.empty() || s.front() != '"') throw exception(s.begin(), Document, "invalid `VersionInfo`");
//     s.remove_prefix(1);
//   } else if (s.front() == '\'') {
//     s.remove_prefix(1);
//     get_versionnum(s, Document);
//     if (s.empty() || s.front() != '\'') throw exception(s.begin(), Document, "invalid `VersionInfo`");
//     s.remove_prefix(1);
//   } else throw exception(s.begin(), Document, "`VersionInfo` must have `VersionNum`");
//   return ustrview{start, s.begin()};
// }

// /// returns `Eq` and removes it from the input string
// constexpr ustrview get_eq(ustrview& s, const ustrview& Document) {
//   auto it = std::ranges::find_if_not(s, is_whitespace);
//   if (it == s.end() || *it++ != '=') throw exception(s.begin(), Document, "`Eq` must contain =");
//   auto it = std::ranges::find_if_not(ustrview{it, s.end()}, is_whitespace);
//   ustrview result{s.begin(), it};
//   s = ustrview{it, s.end()};
//   return result;
// }

// /// returns `VersionNum` and removes it from the input string
// constexpr ustrview get_versionnum(ustrview& s, const ustrview& Document) {
//   constexpr auto is_digit = [](uchar c) { return c >= U'0' && c <= U'9'; };
//   if (!std::ranges::starts_with(s, ustrview(U"1.")))
//     throw exception(s.begin(), Document, "`VersionNum` must start with 1.");
//   auto it = s.begin() + 2;
//   if (it == s.end() || !is_digit(*it++)) throw exception(s.begin(), Document, "invalid `VersionNum`");
//   it = std::ranges::find_if_not(it, s.end(), is_digit);
//   ustrview result{s.begin(), it};
//   s = ustrview{it, s.end()};
//   return result;
// }

// /// returns `Misc` and removes it from the input string
// constexpr ustrview get_misc(ustrview& s, const ustrview& Document) {
//   auto start = s.begin();
//   try {
//     auto s2 = s;
//     get_comment(s2, Document);
//     s = s2;
//   } catch (const exception& e) {
//     try {
//       auto s2 = s;
//       get_pi(s2, Document);
//       s = s2;
//     } catch (const exception& e) {
//       try {
//         auto s2 = s;
//         get_whitespace(s2, Document);
//         s = s2;
//       } catch (const exception& e) { throw exception(start, Document, "invalid `Misc`"); }
//     }
//   }
//   return ustrview{start, s.begin()};
// }

// /// returns `DoctypeDecl` and removes it from the input string
// constexpr ustrview get_doctypedecl(ustrview& s, const ustrview& Document) {
// }

// /// returns `DeclSep` and removes it from the input string
// constexpr ustrview get_declsep(ustrview& s, const ustrview& Document);
// /* 28b */ constexpr ustrview get_intsubset(ustrview& s, const ustrview& Document);
// /* 29  */ constexpr ustrview get_markupdecl(ustrview& s, const ustrview& Document);
// /* 30  */ constexpr ustrview get_extsubset(ustrview& s, const ustrview& Document);
// /* 31  */ constexpr ustrview get_extsubsetdecl(ustrview& s, const ustrview& Document);
// /* 32  */ constexpr ustrview get_sddecl(ustrview& s, const ustrview& Document);
// /* 39  */ constexpr ustrview get_element(ustrview& s, const ustrview& Document);
// /* 40  */ constexpr ustrview get_stag(ustrview& s, const ustrview& Document);
// /* 41  */ constexpr ustrview get_attribute(ustrview& s, const ustrview& Document);
// /* 42  */ constexpr ustrview get_etag(ustrview& s, const ustrview& Document);
// /* 43  */ constexpr ustrview get_content(ustrview& s, const ustrview& Document);
// /* 44  */ constexpr ustrview get_emptyelemtag(ustrview& s, const ustrview& Document);
// /* 45  */ constexpr ustrview get_elementdecl(ustrview& s, const ustrview& Document);
// /* 46  */ constexpr ustrview get_contentspec(ustrview& s, const ustrview& Document);
// /* 47  */ constexpr ustrview get_children(ustrview& s, const ustrview& Document);
// /* 48  */ constexpr ustrview get_cp(ustrview& s, const ustrview& Document);
// /* 49  */ constexpr ustrview get_choice(ustrview& s, const ustrview& Document);
// /* 50  */ constexpr ustrview get_seq(ustrview& s, const ustrview& Document);
// /* 51  */ constexpr ustrview get_mixed(ustrview& s, const ustrview& Document);
// /* 52  */ constexpr ustrview get_attlistdecl(ustrview& s, const ustrview& Document);
// /* 53  */ constexpr ustrview get_attdef(ustrview& s, const ustrview& Document);
// /* 54  */ constexpr ustrview get_atttype(ustrview& s, const ustrview& Document);
// /* 55  */ constexpr ustrview get_stringtype(ustrview& s, const ustrview& Document);
// /* 56  */ constexpr ustrview get_tokenizedtype(ustrview& s, const ustrview& Document);
// /* 57  */ constexpr ustrview get_enumeratedtype(ustrview& s, const ustrview& Document);
// /* 58  */ constexpr ustrview get_notationtype(ustrview& s, const ustrview& Document);
// /* 59  */ constexpr ustrview get_enumeration(ustrview& s, const ustrview& Document);
// /* 60  */ constexpr ustrview get_defaultdecl(ustrview& s, const ustrview& Document);
// /* 61  */ constexpr ustrview get_conditionalsect(ustrview& s, const ustrview& Document);
// /* 62  */ constexpr ustrview get_includesect(ustrview& s, const ustrview& Document);
// /* 63  */ constexpr ustrview get_ignoresect(ustrview& s, const ustrview& Document);
// /* 64  */ constexpr ustrview get_ignoresectcontents(ustrview& s, const ustrview& Document);
// /* 65  */ constexpr ustrview get_ignore(ustrview& s, const ustrview& Document);
// /* 66  */ constexpr ustrview get_charref(ustrview& s, const ustrview& Document);
// /* 67  */ constexpr ustrview get_reference(ustrview& s, const ustrview& Document);
// /* 68  */ constexpr ustrview get_entityref(ustrview& s, const ustrview& Document);
// /* 69  */ constexpr ustrview get_pereference(ustrview& s, const ustrview& Document);
// /* 70  */ constexpr ustrview get_entitydecl(ustrview& s, const ustrview& Document);
// /* 71  */ constexpr ustrview get_pedef(ustrview& s, const ustrview& Document);
// /* 72  */ constexpr ustrview get_externalid(ustrview& s, const ustrview& Document);
// /* 73  */ constexpr ustrview get_ndatadecl(ustrview& s, const ustrview& Document);
// /* 74  */ constexpr ustrview get_textdecl(ustrview& s, const ustrview& Document);
// /* 75  */ constexpr ustrview get_extparsedent(ustrview& s, const ustrview& Document);
// /* 80  */ constexpr ustrview get_encodingdecl(ustrview& s, const ustrview& Document);
// /* 81  */ constexpr ustrview get_encname(ustrview& s, const ustrview& Document);
// /* 82  */ constexpr ustrview get_notationdecl(ustrview& s, const ustrview& Document);
// /* 83  */ constexpr ustrview get_publicid(ustrview& s, const ustrview& Document);
// /* 84  */ constexpr ustrview is_letter(ustrview& s, const ustrview& Document);
// /* 85  */ constexpr ustrview is_basechar(ustrview& s, const ustrview& Document);
// /* 86  */ constexpr ustrview is_ideographic(ustrview& s, const ustrview& Document);
// /* 87  */ constexpr ustrview is_combiningchar(ustrview& s, const ustrview& Document);
// /* 88  */ constexpr ustrview is_digit(ustrview& s, const ustrview& Document);
// /* 89  */ constexpr ustrview is_extender(ustrview& s, const ustrview& Document);
// }

// // /// returns `true` if the character is `Char`
// // constexpr bool is_char(const uchar c) noexcept {
// //   return c == 0x9 || c == 0xa || c == 0xd || (0x20 <= c && c <= 0xd7ff) || (0xe000 <= c && (c & 0xfffe) != 0xfffe);
// // }

// // /// returns whitespaces and removes them from the input string
// // constexpr ustrview skip_space(ustrview& s, const ustrview& Document) noexcept {
// //   constexpr auto is_space = [](const uchar c) noexcept { return (c == 0x20 || c == 0x9 || c == 0xd || c == 0xa); };
// //   auto it                 = s.begin();
// //   while (it != s.end() && is_space(*it)) ++it;
// //   ustrview result{s.begin(), it};
// //   s = ustrview{it, s.end()};
// //   return result;
// // }

// // /// returns `true` if the character `NameStartChar`
// // constexpr bool is_namestartchar(const uchar c) noexcept {
// //   return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || c == ':' || c == '_' ||
// //          (0xc0 <= c && c <= 0x2ff && c != 0xd7 && c != 0xf7) ||
// //          (0x370 <= c && c <= 0x1fff && c != 0x37e) || c == 0x200c || c == 0x200d ||
// //          (0x2070 <= c && c <= 0x218f) || (0x2c00 <= c && c <= 0x2fef) ||
// //          (0x3001 <= c && c <= 0xd7ff) || (0xf900 <= c && c <= 0xfdcf) ||
// //          (0xfdf0 <= c && (c & 0xfffe) != 0xfffe);
// // }

// // /// returns `true` if the character is `NameChar`
// // constexpr bool is_namechar(const uchar c) noexcept {
// //   return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || ('0' <= c && c <= ':') || c == '.' || c == '_' ||
// //          (c == 0xb7) || (0xc0 <= c && c <= 0x2ff && c != 0xd7 && c != 0xf7) ||
// //          (0x300 <= c && c <= 0x1fff && c != 0x37e) || c == 0x200c || c == 0x200d || c == 0x203f || c == 0x2040 ||
// //          (0x2070 <= c && c <= 0x218f) || (0x2c00 <= c && c <= 0x2fef) ||
// //          (0x3001 <= c && c <= 0xd7ff) || (0xf900 <= c && c <= 0xfdcf) ||
// //          (0xfdf0 <= c && (c & 0xfffe) != 0xfffe);
// // }

// // /// returns `Name` and removes it from the input string
// // constexpr ustrview get_name(ustrview& s, const ustrview& Document) {
// //   auto it = s.begin();
// //   if (it == s.end() || !is_namestartchar(*it++)) throw exception(it, Document, "`Name` must start with 'NameStartChar");
// //   while (it != s.end() && is_namechar(*it)) ++it;
// //   ustrview result{s.begin(), it};
// //   s = ustrview{it, s.end()};
// //   return result;
// // }

// // /// returns `Names` and removes it from the input string
// // constexpr array<ustrview> get_names(ustrview& s, const ustrview& Document) {
// //   array<ustrview> names;
// //   names.push_back(get_name(s, Document));
// //   auto it = s.begin();
// //   while (it != s.end()) {
// //     if (*it == 0x20) {
// //       try {
// //         s = ustrview{it + 1, s.end()};
// //         names.push_back(get_name(s, Document));
// //         it = s.begin();
// //       } catch (const exception& e) {
// //         s = ustrview{it, s.end()};
// //         return names;
// //       }
// //     } else return names;
// //   }
// //   return names;
// // }

// // /// returns `Nmtoken` and removes it from the input string
// // constexpr ustrview get_nmtoken(ustrview& s, const ustrview& Document) {
// //   auto it = s.begin();
// //   if (it == s.end() || !is_namechar(*it++)) throw exception(it, Document, "`Nmtoken` must start with 'NameChar");
// //   while (it != s.end() && is_namechar(*it)) ++it;
// //   s = ustrview{it, s.end()};
// //   return ustrview{s.begin(), it};
// // }

// // /// returns `Nmtokens` and removes it from the input string
// // constexpr array<ustrview> get_nmtokens(ustrview& s, const ustrview& Document) {
// //   array<ustrview> nmtokens;
// //   nmtokens.push_back(get_nmtoken(s, Document));
// //   auto it = s.begin();
// //   while (it != s.end()) {
// //     if (*it == 0x20) {
// //       try {
// //         s = ustrview{it + 1, s.end()};
// //         nmtokens.push_back(get_nmtoken(s, Document));
// //         it = s.begin();
// //       } catch (const exception& e) {
// //         s = ustrview{it, s.end()};
// //         return nmtokens;
// //       }
// //     } else return nmtokens;
// //   }
// //   return nmtokens;
// // }

// // /// returns `CharRef(&#...;)` and removes it from the input string
// // constexpr ustrview get_charref(ustrview& s, const ustrview& Document) {
// //   constexpr auto is_digit = [](const uchar c) noexcept { return '0' <= c && c <= '9'; };
// //   constexpr auto is_hex   = [](const uchar c) noexcept { return is_digit(c) || ('a' <= c && c <= 'f') || ('A' <= c && c <= 'F'); };
// //   if (!std::ranges::starts_with(s, ustrview(U"&#"))) throw exception(s.begin(), Document, "`CharRef` must start with '&#'");
// //   s.remove_prefix(2);
// //   if (s.empty()) throw exception(s.begin(), Document, "`CharRef` must be followed by a digit or a hexadecimal digit");
// //   if (s.front() == 'x') {
// //     s.remove_prefix(1);
// //     auto it = std::ranges::find_if_not(s, is_hex);
// //     if (it == s.end() || *it++ != ';') throw exception(it, Document, "`CharRef` must end with ';'");
// //     ustrview result{s.begin() - 3, it};
// //     s = ustrview{it, s.end()};
// //     return result;
// //   } else {
// //     auto it = std::ranges::find_if_not(s, is_digit);
// //     if (it == s.end() || *it++ != ';') throw exception(it, Document, "`CharRef` must end with ';'");
// //     ustrview result{s.begin() - 2, it};
// //     s = ustrview{it, s.end()};
// //     return result;
// //   }
// // }

// // /// returns `EntityRef(&...;)` and removes it from the input string
// // constexpr ustrview get_entityref(ustrview& s, const ustrview& Document) {
// //   auto it = s.begin();
// //   if (it == s.end() || *it != '&') throw exception(it, Document, "`EntityRef` must start with '&'");
// //   ustrview name = get_name(s, Document);
// //   if (s.empty() || s.front() != ';') throw exception(it, Document, "`EntityRef` must end with ';'");
// //   s.remove_prefix(1);
// //   return ustrview{it, s.begin()};
// // }

// // /// returns `PEReference(%...;)` and removes it from the input string
// // constexpr ustrview get_pereference(ustrview& s, const ustrview& Document) {
// //   auto it = s.begin();
// //   if (it == s.end() || *it != '%') throw exception(it, Document, "`PEReference` must start with '%'");
// //   s.remove_prefix(1);
// //   ustrview name = get_name(s, Document);
// //   if (name.empty()) throw exception(it, Document, "`PEReference` must have a valid `Name`");
// //   if (s.empty() || s.front() != ';') throw exception(it, Document, "`PEReference` must end with ';'");
// //   s.remove_prefix(1);
// //   return ustrview{it, s.begin()};
// // }

// // /// returns `{EntityRef, id::entityref}` or `{CharRef, id::charref}`
// // constexpr tuple<ustrview, id> get_reference(ustrview& s, const ustrview& Document) {
// //   try {
// //     auto s2     = s;
// //     auto result = get_entityref(s2, Document);
// //     s           = s2;
// //     return {result, id::entityref};
// //   } catch (const exception& e) {}
// //   try {
// //     auto s2     = s;
// //     auto result = get_charref(s2, Document);
// //     s           = s2;
// //     return {result, id::charref};
// //   } catch (const exception& e) {}
// //   throw exception(s.begin(), Document, "`Reference` must be either `EntityRef` or `CharRef`");
// // }

// // /// returns `EntityValue`; `"..."` or `'...'`
// // constexpr ustrview get_entityvalue(ustrview& s, const ustrview& Document) {
// //   if (s.empty()) throw exception(s.begin(), Document, "`EntityValue` must start with '\"' or \"'\"");
// //   ustrview::iterator it = s.begin(), it2;
// //   if (*it == '"') {
// //     it2 = std::ranges::find(ustrview{it + 1, s.end()}, '"');
// //     if (it2 == s.end()) throw exception(it2, Document, "`EntityValue` must end with '\"'");
// //   } else if (*it == '\'') {
// //     it2 = std::ranges::find(ustrview{it + 1, s.end()}, '\'');
// //     if (it2 == s.end()) throw exception(it2, Document, "`EntityValue` must end with \"'\"");
// //   }
// //   ustrview test{it + 1, it2};
// //   while (!test.empty()) {
// //     if (test.front() == '%') get_pereference(test, Document);
// //     else if (test.front() == '&') get_reference(test, Document);
// //     test.remove_prefix(1);
// //   }
// //   ustrview result{it, ++it2};
// //   s = ustrview{it2, s.end()};
// //   return result;
// // }

// // /// [10] AttValue ::= '"' ([^<&"] | Reference)* '"' | "'" ([^<&'] | Reference)* "'"
// // constexpr ustrview get_attvalue(ustrview& s, const ustrview& Document) {
// //   if (s.empty()) throw exception(s.begin(), Document, "`AttValue` must start with '\"' or \"'\"");
// //   ustrview::iterator it = s.begin(), it2;
// //   if (*it == '"') {
// //     it2 = std::ranges::find(ustrview{it + 1, s.end()}, '"');
// //     if (it2 == s.end()) throw exception(it2, Document, "`AttValue` must end with '\"'");
// //   } else if (*it == '\'') {
// //     it2 = std::ranges::find(ustrview{it + 1, s.end()}, '\'');
// //     if (it2 == s.end()) throw exception(it2, Document, "`AttValue` must end with \"'\"");
// //   } else throw exception(it, Document, "`AttValue` must start with '\"' or \"'\"");
// //   ustrview test{it + 1, it2};
// //   while (!test.empty()) {
// //     if (test.front() == '<') throw exception(test.begin(), Document, "`AttValue` must not contain '<'");
// //     else if (test.front() == '&') get_reference(test, Document);
// //     test.remove_prefix(1);
// //   }
// //   ustrview result{it, ++it2};
// //   s = ustrview{it2, s.end()};
// //   return result;
// // }

// // /// [11] SystemLiteral ::= ('"' [^"]* '"') | ("'" [^']* "'")
// // /// \return `SystemLiteral`
// // constexpr ustrview get_systemliteral(ustrview& s, const ustrview& Document) {
// //   auto it = s.begin();
// //   if (it == s.end()) throw exception(it, Document, "`SystemLiteral` must start with '\"' or '\\''");
// //   if (*it++ == '"') {
// //     while (it != s.end() && *it != '"') ++it;
// //     if (it == s.end()) throw exception(it, Document, "`SystemLiteral` must end with '\"'");
// //   } else if (*it++ == '\'') {
// //     while (it != s.end() && *it != '\'') ++it;
// //     if (it == s.end()) throw exception(it, Document, "`SystemLiteral` must end with '\\''");
// //   } else throw exception(it, Document, "`SystemLiteral` must start with '\"' or '\\''");
// //   ustrview result{s.begin() + 1, it};
// //   s = ustrview{it + 1, s.end()};
// //   return result;
// // }

// // /// [13] PubidChar ::= #x20 | #xD | #xA | [a-zA-Z0-9] | [-'()+,./:=?;!*#@$_%]
// // /// \return `true` if the character is `PubidChar`
// // constexpr bool is_pubid_char(const uchar u) noexcept {
// //   return u == 0xd || u == 0xa || (0x5f <= u && u <= 0x7a && (u != 0x60)) ||
// //          (0x20 <= u && u <= 0x90 && (u != 0x22 && u != 0x26 && u != 0x60 && u != 0x62 && u != 0x64));
// // }

// // /// [12] PubidLiteral ::= '"' PubidChar* '"' | "'" (PubidChar - "'")* "'"
// // /// \return `PubidLiteral`
// // constexpr ustrview get_pubid_literal(ustrview& s, const ustrview& Document) {
// //   auto it = s.begin();
// //   if (it == s.end()) throw exception(it, Document, "`PubidLiteral` must start with '\"' or '\\''");
// //   if (*it++ == '"') {
// //     while (it != s.end() && is_pubid_char(*it)) ++it;
// //     if (it == s.end() || *it != '"') throw exception(it, Document, "`PubidLiteral` must end with '\"'");
// //   } else if (*it++ == '\'') {
// //     while (it != s.end() && is_pubid_char(*it)) ++it;
// //     if (it == s.end() || *it != '\'') throw exception(it, Document, "`PubidLiteral` must end with '\\''");
// //   } else throw exception(it, Document, "`PubidLiteral` must start with '\"' or '\\''");
// //   ustrview result{s.begin() + 1, it};
// //   s = ustrview{it + 1, s.end()};
// //   return result;
// // }

// // /// [14] CharData ::= [^<&]* - ([^<&]* ']]>' [^<&]*)
// // /// \return `CharData`
// // constexpr ustrview get_char_data(ustrview& s, const ustrview& Document) {
// //   auto it = s.begin();
// //   while (it != s.end() && *it != '<' && *it != '&' && !std::ranges::starts_with(ustrview(it, s.end()), ustrview(U"]]>"))) ++it;
// //   ustrview result{s.begin(), it};
// //   s = ustrview{it, s.end()};
// //   return result;
// // }

// // /// [15] Comment ::= '<!--' ((Char - '-') | ('-' (Char - '-')))* '-->'
// // /// \return `Comment`
// // constexpr ustrview get_comment(ustrview& s, const ustrview& Document) {
// //   auto it = s.begin();
// //   if (!std::ranges::starts_with(ustrview(it, s.end()), ustrview(U"<!--"))) throw exception(it, Document, "`Comment` must start with '<!--'");
// //   s.remove_prefix(4);
// //   auto sr = std::ranges::search(s, ustrview(U"-->"));
// //   if (sr.empty()) throw exception(s.end(), Document, "`Comment` must end with '-->'");
// //   ustrview comment{s.begin(), sr.begin()};
// //   if (comment.empty()) throw exception(s.begin(), Document, "`Comment` must not be empty");
// //   else if (comment.front() == '-') throw exception(s.begin(), Document, "`Comment` must not start with '<!---'");
// //   if (std::ranges::search(comment, ustrview(U"--"))) throw exception(s.begin(), Document, "`Comment` must not include '--'");
// //   if (std::ranges::any_of(comment, [](uchar c) noexcept { return !is_char(c); })) throw exception(s.begin(), Document, "`Comment` must only include valid characters");
// //   s = ustrview{sr.end(), s.end()};
// //   return comment;
// // }

// // /// [15] PITarget ::= Name - (('X' | 'x') ('M' | 'm') ('L' | 'l'))
// // /// \return `PITarget`
// // constexpr ustrview get_pi_target(ustrview& s, const ustrview& Document) {
// //   auto result = get_name(s, Document);
// //   if (std::ranges::starts_with(result, ustrview(U"XML"), [](uchar a, uchar b) noexcept { return (a & ~0x10) == b; }))
// //     throw exception(result.begin(), Document, "`PITarget` must not be 'XML'");
// //   return result;
// // }

// // /// [16] PI ::= '<?' PITarget (S (Char* - (Char* '?>' Char*)))? '?>'
// // /// \return `PITarget` and data
// // constexpr tuple<ustrview, ustrview> get_processing_instruction(ustrview& s, const ustrview& Document) {
// //   if (!std::ranges::starts_with(s, ustrview(U"<?"))) throw exception(s.begin(), Document, "`PI` must start with '<?'");
// //   s.remove_prefix(2);
// //   ustrview target = get_pi_target(s, Document), data;
// //   auto sr         = std::ranges::search(s, ustrview(U"?>"));
// //   if (sr.empty()) throw exception(s.end(), Document, "`PI` must end with '?>'");
// //   ustrview data{s.begin(), sr.begin()};
// //   skip_space(data, Document);
// //   s = ustrview{sr.end(), s.end()};
// //   return {target, data};
// // }

// // /// [18] CDSect ::= CDStart CData CDEnd
// // /// [19] CDStart ::= '<![CDATA['
// // /// [21] CDEnd ::= ']]>'

// // /// [20] CData ::= (Char* - (Char* ']]>' Char*))
// // /// \return `CData`
// // constexpr ustrview get_cdata(ustrview& s, const ustrview& Document) {
// //   if (!std::ranges::starts_with(s, ustrview(U"<![CDATA["))) throw exception(s.begin(), Document, "`CData` must start with '<![CDATA['");
// //   s.remove_prefix(9);
// //   auto sr = std::ranges::search(s, ustrview(U"]]>"));
// //   if (sr.empty()) throw exception(s.end(), Document, "`CData` must end with ']]>'");
// //   ustrview result{s.begin(), sr.begin()};
// //   s = ustrview{sr.end(), s.end()};
// //   return result;
// // }

// // /// [22] prolog ::= XMLDecl? Misc* (doctypedec|Misc*)?

// // /// [23] XMLDecl ::= '<?xml' VersionInfo EncodingDecl? SDDecl? S? '>'

// // /// [25] Eq ::= S? '=' S?
// // /// \return `true` if `Eq` is found and skipped
// // constexpr bool skip_eq(ustrview& s, const ustrview& Document) {
// //   skip_space(s, Document);
// //   if (s.empty() || s.front() != '=') throw exception(s.begin(), Document, "'Eq' must have '='");
// //   s.remove_prefix(1);
// //   skip_space(s, Document);
// //   return true;
// // }

// // /// [26] VersionNum ::= '1.' [0-9]+
// // /// \return `VersionNum`
// // constexpr ustrview get_version_num(ustrview& s, const ustrview& Document) {
// //   auto is_digit = [](const uchar u) { return u >= '0' && u <= '9'; };
// //   if (!std::ranges::starts_with(s, ustrview(U"1."))) throw exception(s.begin(), Document, "`VersionNum` must start with '1.'");
// //   s.remove_prefix(2);
// //   if (s.empty() || !is_digit(s.front())) throw exception(s.begin(), Document, "invalid `VersionNum`");
// //   s.remove_prefix(1);
// //   auto it = std::ranges::find_if_not(s, is_digit);
// //   ustrview result{s.begin(), it};
// //   s = ustrview{it, s.end()};
// //   return result;
// // }

// // /// [24] VersionInfo ::= S 'version' Eq ("'" VersionNum"'"" | '"' VersionNum '"' )
// // //// \return `VersionNum`
// // constexpr ustrview get_version_info(ustrview& s, const ustrview& Document) {
// //   skip_space(s, Document);
// //   if (!std::ranges::starts_with(s, ustrview(U"version"))) throw exception(s.begin(), Document, "`VersionInfo` must start with 'version'");
// //   s.remove_prefix(7);
// //   if (!skip_eq(s, Document)) throw exception(s.begin(), Document, "`VersionInfo` must have '='");
// //   if (s.empty()) throw exception(s.end(), Document, "invalid `VersionInfo`");
// //   if (s.front() == '"') {
// //     s.remove_prefix(1);
// //     auto version_num = get_version_num(s, Document);
// //     if (s.empty() || s.front() != '"') throw exception(s.begin(), Document, "invalid `VersionInfo`");
// //     return version_num;
// //   } else if (s.front() == '\'') {
// //     s.remove_prefix(1);
// //     auto version_num = get_version_num(s, Document);
// //     if (s.empty() || s.front() != '\'') throw exception(s.begin(), Document, "invalid `VersionInfo`");
// //     s.remove_prefix(1);
// //     return version_num;
// //   } else throw exception(s.begin(), Document, "`VersionInfo` must have 'version' followed by '=' and a quoted string");
// // }

// // /// [27] Misc ::= Comment | PI | S
// // /// \return `{empty, Comment}` if Comment, `{PITarget, data}` if PI, `{empty, empty}` if S
// // constexpr tuple<ustrview, ustrview> get_misc(ustrview& s, const ustrview& Document) {
// //   try {
// //     auto s2      = s;
// //     auto comment = get_comment(s2, Document);
// //     s            = s2;
// //     return {ustrview{}, comment};
// //   } catch (const exception& e) {} // misc is not comment
// //   try {
// //     auto s2             = s;
// //     auto [target, data] = get_processing_instruction(s2, Document);
// //     s                   = s2;
// //     return {target, data};
// //   } catch (const exception& e) {} // misc is not PI
// //   if (skip_space(s, Document).empty()) throw exception(s.begin(), Document, "`Misc` must have comment, PI or space");
// //   return {ustrview{}, ustrview{}};
// // }

// // /// [28] doctypedecl ::= '<!DOCTYPE' S Name (S ExternalID)? S? ('[' intSubset ']' S?)? '>'
// // /// [28a] DeclSep ::= PEReference | S
// // /// [28b] intSubset ::= (markupdecl | DeclSep)*
// // /// [29] markupdecl ::= elementdecl | AttlistDecl | EntityDecl | NotationDecl | PI | Comment
// // /// [30] extSubset ::= TextDecl? extSubsetDecl
// // /// [31] extSubsetDecl ::= ( markupdecl | conditionalSect | DeclSep)*

// // /// [32] SDDecl ::= S 'standalone' Eq (("'" ('yes' | 'no') "'") | ('"' ('yes' | 'no') '"'))
// // /// \return "yes" or "no"
// // constexpr ustrview get_sddecl(ustrview& s, const ustrview& Document) {
// //   skip_space(s, Document);
// //   if (!std::ranges::starts_with(s, ustrview(U"standalone"))) throw exception(s.begin(), Document, "`SDDecl` must start with 'standalone'");
// //   s.remove_prefix(10);
// //   if (!skip_eq(s, Document)) throw exception(s.begin(), Document, "`SDDecl` must have '='");
// //   if (s.empty()) throw exception(s.end(), Document, "invalid `SDDecl`");
// //   if (s.front() == '"') {
// //     s.remove_prefix(1);
// //     if (std::ranges::starts_with(s, ustrview(U"yes\""))) {
// //       auto result = s.substr(0, 3);
// //       s.remove_prefix(4);
// //       return result;
// //     } else if (std::ranges::starts_with(s, ustrview(U"no\""))) {
// //       auto result = s.substr(0, 2);
// //       s.remove_prefix(3);
// //       return result;
// //     } else throw exception(s.begin(), Document, "invalid `SDDecl`");
// //   } else if (s.front() == '\'') {
// //     s.remove_prefix(1);
// //     if (std::ranges::starts_with(s, ustrview(U"yes'"))) {
// //       s.remove_prefix(4);
// //       return s.substr(0, 3);
// //     } else if (std::ranges::starts_with(s, ustrview(U"no'"))) {
// //       s.remove_prefix(3);
// //       return s.substr(0, 2);
// //     } else throw exception(s.begin(), Document, "invalid `SDDecl`");
// //   } else throw exception(s.begin(), Document, "`SDDecl` must have 'yes' or 'no'");
// // }

// // /// [41] Sttribute ::= Name Eq AttValue

// // /// [40] Stag ::= '<' Name (S Attribute)* S? '>'

// // /// [39] element ::= EmptyElemTag | STag content ETag

// // // namespace xml {

// // // class element;
// // // class root;

// // // constexpr bool is_space_char(const uchar u) noexcept {
// // //   return u == 0x09 || u == 0x0a || u == 0x0d || u == 0x20;
// // // }

// // // constexpr bool is_number_char(const uchar u) noexcept {
// // //   return '0' <= u && u <= '9';
// // // }

// // // constexpr bool is_char(const uchar u) noexcept {
// // //   return is_space_char(u) || (0x20 < u && u < 0xd800) || (0xe000 <= u && (u & 0xfffe) != 0xfffe);
// // // };

// // // constexpr bool is_namestartchar(const uchar u) noexcept {
// // //   return ('a' <= u && u <= 'z') || ('A' <= u && u <= 'Z') || u == ':' || u == '_' ||
// // //          (0xc0 <= u && u <= 0x2ff && u != 0xd7 && u != 0xf7) ||
// // //          (0x370 <= u && u <= 0x1fff && u != 0x37e) || u == 0x200c || u == 0x200d ||
// // //          (0x2070 <= u && u <= 0x218f) || (0x2c00 <= u && u <= 0x2fef) ||
// // //          (0x3001 <= u && u <= 0xd7ff) || (0xf900 <= u && u <= 0xfdcf) ||
// // //          (0xfdf0 <= u && (u & 0xfffe) != 0xfffe);
// // // }

// // // constexpr bool is_namechar(const uchar u) noexcept {
// // //   return ('a' <= u && u <= 'z') || ('A' <= u && u <= 'Z') || ('0' <= u && u <= ':') || u == '.' || u == '_' ||
// // //          (u == 0xb7) || (0xc0 <= u && u <= 0x2ff && u != 0xd7 && u != 0xf7) ||
// // //          (0x300 <= u && u <= 0x1fff && u != 0x37e) || u == 0x200c || u == 0x200d || u == 0x203f || u == 0x2040 ||
// // //          (0x2070 <= u && u <= 0x218f) || (0x2c00 <= u && u <= 0x2fef) ||
// // //          (0x3001 <= u && u <= 0xd7ff) || (0xf900 <= u && u <= 0xfdcf) ||
// // //          (0xfdf0 <= u && (u & 0xfffe) != 0xfffe);
// // // }

// // // /// removes comments from the xml string
// // // template<char_type C> constexpr string<C> remove_comments(string_view<C> s) {
// // //   constexpr C comment_start[]{'<', '!', '-', '-'};
// // //   constexpr C comment_end[]{'-', '-', '>'};
// // //   string<C> result;
// // //   result.reserve(s.size()), result.resize(s.size());
// // //   auto out{s.begin()};
// // //   for (auto sr = std::ranges::search(s, comment_start); !sr.empty(); sr = std::ranges::search(s, comment_start)) {
// // //     auto cr  = std::ranges::copy(s.begin(), sr.begin(), out);
// // //     out      = cr.out;
// // //     auto sr2 = std::ranges::search(string_view(cr.in, s.end()), comment_end);
// // //     if (sr2.empty()) throw std::invalid_argument("xml::remove_comments: Unclosed comment");
// // //     s = string_view(sr2.end(), s.end());
// // //   }
// // //   result.resize(out - result.begin());
// // //   return result;
// // // }

// // // inline void analyze_element(ustrview& Str, ustr& Name, std::map<ustr, ustr, std::less<>>& Attributes, array<std::unique_ptr<element>>& Children);

// // // /// analyzes the string as attributes until the next `not NameStartChar`

// // // /// class to represent XML element
// // // class element {
// // // public:
// // //   ustr name;
// // //   std::map<ustr, ustr, std::less<>> attributes;
// // //   array<std::unique_ptr<element>> children;
// // //   element(ustrview& Str) { analyze_element(Str, name, attributes, children); }
// // // };

// // // inline void analyze_element(ustrview& Str, ustr& Name, std::map<ustr, ustr, std::less<>>& Attributes, array<std::unique_ptr<element>>& Children) {
// // //   auto fr = std::ranges::find_if_not(Str, [](const uchar u) { return is_space_char(u); });
// // //   if (fr == Str.end()) return;
// // //   if (*fr++ != '<') throw std::invalid_argument(format("xml::element: invalid element", uint32_t(*fr)));
// // //   // obtains element name
// // //   if (fr == Str.end() || !is_namestartchar(*fr)) throw std::invalid_argument("xml::element: invalid element");
// // //   auto fr2 = std::ranges::find_if(ustrview(fr, Str.end()), [](const uchar u) { return !is_namechar(u); });
// // //   Name     = ustr(fr, fr2);
// // //   Str      = ustrview(fr2, Str.end());
// // //   // obtains attributes
// // //   while (true) {
// // //     fr = std::ranges::find_if_not(Str, [](const uchar u) { return is_space_char(u); });
// // //     if (fr == Str.end()) throw std::invalid_argument(format("xml::element: element({}) is not well-formed", unicode<char>(Name)));
// // //     if (*fr == '/') {
// // //       ++fr;
// // //       if (fr != Str.end() && *fr++ == '>') {
// // //         Str = ustrview(fr, Str.end());
// // //         return;
// // //       } else throw std::invalid_argument(format("xml::element: element({}) is not well-formed", unicode<char>(Name)));
// // //     } else if (is_namestartchar(*fr)) {
// // //       auto fr2       = std::ranges::find_if(ustrview(fr, Str.end()), [](const uchar u) { return !is_namechar(u); });
// // //       auto attr_name = ustrview(fr, fr2);
// // //       fr             = std::ranges::find_if_not(ustrview(fr2, Str.end()), [](const uchar u) { return is_space_char(u); });
// // //       if (fr == Str.end() || *fr++ != '=') throw std::invalid_argument(format("xml::element: element({})-attribute({}) is not well-formed", unicode<char>(Name), unicode<char>(attr_name)));
// // //       fr = std::ranges::find_if_not(ustrview(fr, Str.end()), [](const uchar u) { return is_space_char(u); });
// // //       if (fr == Str.end()) throw std::invalid_argument(format("xml::element: element({})-attribute({}) is not well-formed", unicode<char>(Name), unicode<char>(attr_name)));
// // //       if (*fr == '"') fr2 = std::ranges::find(ustrview(++fr, Str.end()), '"');
// // //       else if (*fr == '\'') fr2 = std::ranges::find(ustrview(++fr, Str.end()), '\'');
// // //       else throw std::invalid_argument(format("xml::element: element({})-attribute({}) is not well-formed", unicode<char>(Name), unicode<char>(attr_name)));
// // //       Attributes[ustr(attr_name)] = ustrview(fr, fr2);
// // //       Str                         = ustrview(fr2, Str.end());
// // //     } else if (*fr == '>') break;
// // //     else throw std::invalid_argument(format("xml::element: element({}) is not well-formed", unicode<char>(Name)));
// // //   }
// // //   // obtains children
// // //   for (int i{};; ++i) {
// // //     try {
// // //       element child(Str);
// // //       if (child.name.empty()) break;
// // //       Children.push_back(std::make_unique<element>(mv(child)));
// // //     } catch (const std::exception& e) {
// // //       throw std::invalid_argument(format("xml::element: {}-th child of element({}) throws exception;\n -> {}", i, unicode<char>(Name), e.what()));
// // //     }
// // //   }
// // //   // check closing tag
// // //   fr = std::ranges::find_if_not(Str, [](const uchar u) { return is_space_char(u); });
// // //   if (fr == Str.end() || *fr++ != '<') throw std::invalid_argument(format("xml::element: element({}) is not well-formed", unicode<char>(Name)));
// // //   if (fr == Str.end() || *fr++ != '/') throw std::invalid_argument(format("xml::element: element({}) is not well-formed", unicode<char>(Name)));
// // //   if (!std::ranges::starts_with(ustrview(fr, Str.end()), Name)) throw std::invalid_argument(format("xml::element: element({}) is not well-formed", unicode<char>(Name)));
// // //   fr += Name.size();
// // //   if (fr == Str.end() || *fr++ != '>') throw std::invalid_argument(format("xml::element: element({}) is not well-formed", unicode<char>(Name)));
// // //   Str = ustrview(fr, Str.end());
// // // }

// // // /// class to represent XML root
// // // class root : public element {
// // // public:
// // //   std::map<ustr, ustr, std::less<>> declaration;
// // //   root() = default;
// // //   template<stringable S> root(S&& Str) {
// // //     using C = iter_value_t<S>;
// // //     ustr ss;
// // //     ustrview sv;
// // //     if constexpr (different_from<C, uchar>) {
// // //       ss = unicode<uchar>(static_cast<S&&>(Str));
// // //       sv = ustrview(ss);
// // //     } else sv = ustrview(Str);
// // //     // obtains declaration
// // //     auto fr = std::ranges::find_if_not(sv, [](const uchar u) { return is_space_char(u); });
// // //     if (std::ranges::starts_with(ustrview(fr, sv.end()), U"<?xml")) {
// // //       fr = std::ranges::find_if_not(ustrview(fr + 5, sv.end()), [](const uchar u) { return is_space_char(u); });
// // //       // version
// // //       if (std::ranges::starts_with(ustrview(fr, sv.end()), "version")) {
// // //         fr = std::ranges::find_if_not(ustrview(fr + 7, sv.end()), [](const uchar u) { return is_space_char(u); });
// // //         if (fr == sv.end() || *fr++ != '=') throw std::invalid_argument(format("xml::root: xml declaration is not well-formed"));
// // //         fr = std::ranges::find_if_not(ustrview(fr, sv.end()), [](const uchar u) { return is_space_char(u); });
// // //         if (std::ranges::starts_with(ustrview(fr, sv.end()), "'1.")) {
// // //           if (fr == sv.end() || !is_number_char(*fr++)) throw std::invalid_argument(format("xml::root: xml declaration is not well-formed"));
// // //           fr = std::ranges::find_if_not(ustrview(fr, sv.end()), [](const uchar u) { return is_number_char(u); });
// // //           if (fr == sv.end() || *fr++ != '\'') throw std::invalid_argument(format("xml::root: xml declaration is not well-formed"));
// // //           declaration["version"] = ustrview(fr, sv.end());
// // //         } else if (std::ranges::starts_with(ustrview(fr, sv.end()), "\"1.")) {
// // //           if (fr == sv.end() || !is_number_char(*fr++)) throw std::invalid_argument(format("xml::root: xml declaration is not well-formed"));
// // //           fr = std::ranges::find_if_not(ustrview(fr, sv.end()), [](const uchar u) { return is_number_char(u); });
// // //           if (fr == sv.end() || *fr++ != '"') throw std::invalid_argument(format("xml::root: xml declaration is not well-formed"));
// // //           declaration["version"] = ustrview(fr, sv.end());
// // //         } else throw std::invalid_argument(format("xml::root: xml declaration is not well-formed"));
// // //       } else throw std::invalid_argument(format("xml::root: xml declaration is not well-formed"));
// // //       fr = std::ranges::find_if_not(ustrview(fr, sv.end()), [](const uchar u) { return is_space_char(u); });
// // //       // encoding
// // //       if (std::ranges::starts_with(ustrview(fr, sv.end()), "encoding")) {
// // //         fr = std::ranges::find_if_not(ustrview(fr + 8, sv.end()), [](const uchar u) { return is_space_char(u); });
// // //         if (fr == sv.end() || *fr++ != '=') throw std::invalid_argument(format("xml::root: xml declaration is not well-formed"));
// // //         fr = std::ranges::find_if_not(ustrview(fr, sv.end()), [](const uchar u) { return is_space_char(u); });
// // //         if (std::ranges::starts_with(ustrview(fr, sv.end()), "'UTF-8")) {
// // //           if (fr == sv.end() || *fr++ != '\'') throw std::invalid_argument(format("xml::root: xml declaration is not well-formed"));
// // //           declaration["encoding"] = ustrview(fr, sv.end());
// // //         } else if (std::ranges::starts_with(ustrview(fr, sv.end()), "\"UTF-8")) {
// // //           if (fr == sv.end() || *fr++ != '"') throw std::invalid_argument(format("xml::root: xml declaration is not well-formed"));
// // //           declaration["encoding"] = ustrview(fr, sv.end());
// // //         } else throw std::invalid_argument(format("xml::root: xml declaration is not well-formed"));
// // //       } else throw std::invalid_argument(format("xml::root: xml declaration is not well-formed"));
// // //     } else throw std::invalid_argument(format("xml::root: xml declaration is not well-formed"));
// // //   }
// // // };

// // // inline ustr open(const path& File) {
// // // }

// // // /// [5] `Name ::= NameStartChar (NameChar)*`
// // // /// \return name
// // // constexpr ustrview get_name(ustrview& s, const ustrview& Document) {
// // //   auto fr = s.begin();
// // //   if (fr == s.end() || !is_namestartchar(*fr++)) throw exception(fr, Document, "`Name` does not start with 'NameStartChar");
// // //   while (fr != s.end() && is_namechar(*fr)) ++fr;
// // //   s = ustrview{fr, s.end()};
// // //   return ustrview{s.begin(), fr};
// // // }

// // // /// [14] `CharData ::= [^<&]* - ([^<&]*']]>' [^<&]*)

// // // /// [15] `Comment ::= '<!--' ((Char - '-') | ('-' (Char - '-')))* '-->'`
// // // /// \return comment content; may start/end with spaces
// // // constexpr ustrview get_comment(ustrview& s, const ustrview& Document) {
// // //   auto fr = s.begin();
// // //   if (fr == s.end() || *fr++ != '<') throw exception(fr, Document, "`Comment` must start with '<!--'");
// // //   if (fr == s.end() || *fr++ != '!') throw exception(fr, Document, "`Comment` must start with '<!--'");
// // //   if (fr == s.end() || *fr++ != '-') throw exception(fr, Document, "`Comment` must start with '<!--'");
// // //   if (fr == s.end() || *fr++ != '-') throw exception(fr, Document, "`Comment` must start with '<!--'");
// // //   if (fr == s.end() || !is_char(*fr) || *fr == '-') throw exception(fr, Document, "`Comment` has invalid char after '<!--'");
// // //   auto sr = std::ranges::search(ustrview(fr, s.end()), ustrview{U"-->"});
// // //   if (sr.empty()) throw exception(fr, Document, "`Comment` must end with '-->'");
// // //   s = ustrview{sr.end(), s.end()};
// // //   return ustrview{fr, sr.begin()};
// // // }

// // // /// [17] `PITarget ::= Name - (('X' | 'x') ('M' | 'm') ('L' | 'l'))`
// // // /// \return target name as `ustr`
// // // constexpr ustrview get_pi_target(ustrview& s, const ustrview& Document) {
// // //   auto name = get_name(s, Document);
// // //   if (name.size() == 3 && (name[0] & ~0x10) == 'X' && (name[1] & ~0x10) == 'M' && (name[2] & ~0x10) == 'L')
// // //     throw exception(name.begin(), Document, "`PITarget` must not be 'XML'");
// // //   return name;
// // // }

// // // /// [16] `PI ::= '<?' PITarget (S (Char* - (Char* '?>' char*)))? '?>'`
// // // constexpr tuple<ustrview, ustrview> get_pi(ustrview& s, const ustrview& Document) {
// // //   auto fr = s.begin();
// // //   if (fr == s.end() || *fr++ != '<') throw exception(fr, Document, "`PI` must start with '<?'");
// // //   if (fr == s.end() || *fr++ != '?') throw exception(fr, Document, "`PI` must start with '<?'");
// // //   s = ustrview{fr, s.end()};
// // //   auto target = get_pi_target(s, Document);
// // //   fr = target.end();
// // //   if (fr == s.end()) throw exception(fr, Document, "`PI` must end with '?>'");
// // //   if (*fr++ == '?') {
// // //     if (fr == s.end() || *fr++ != '>') throw exception(fr, Document, "`PI` must end with '?>'");
// // //     s = ustrview{fr, s.end()};
// // //     return {target, {}};
// // //   } else if (is_space_char(*fr)) {
// // //     fr = std::ranges::find_if_not(ustrview(fr, s.end()), [](const uchar u) { return is_space_char(u); });
// // //     auto sr = std::ranges::search(ustrview(fr, s.end()), ustrview{U"?>"});
// // //     if (sr.empty()) throw exception(fr, Document, "`PI` must end with '?>'");
// // //     s = ustrview{sr.end(), s.end()};
// // //     return {target, ustrview{fr, s.begin()}};
// // //   } else throw exception(fr, Document, "`PI` must end with '?>'");
// // // }

// // // /// [27] `Misc ::= Comment | PI | S`

// // // }
// // // }
