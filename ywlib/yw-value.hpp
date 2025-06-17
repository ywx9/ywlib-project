// #pragma once
// #include <ywlib>

// namespace yw {

// /// types for `yw::value`
// enum class value_type {
//   null,
//   boolean,
//   integer,
//   real,
//   string,
// };

// /// generic value type used for tables and command line arguments
// class value {
//   union {
//     bool _bool;
//     int8_t _int;
//     double _real;
//     std::string _str;
//   };
//   value_type _type{};
// public:
//   constexpr value() : _str("null"), _type(value_type::null) {}
//   constexpr value(const bool b) : _bool(b), _type(value_type::boolean) {}
//   constexpr value(const integral auto i) : _int(i), _type(value_type::integer) {}
//   constexpr value(const floating auto v) : _real(v), _type(value_type::real) {}
//   constexpr value(std::string&& s) : _str(mv(s)), _type(value_type::string) {}
//   constexpr value(stringable auto&& s) : _str(unicode<char>(s)), _type(value_type::string) {}
//   explicit constexpr value(const char* s) : _str(s), _type(value_type::string) {}
//   value_type type() const { return _type; }
//   constexpr bool get_as_boolean() const {
//     if (_type == value_type::boolean) return _bool;
//     else if (_type == value_type::integer) return _int != 0;
//     else if (_type == value_type::real) return _real != 0.0;
//     else if (_type == value_type::string) return !_str.empty();
//     else return false;
//   }
//   constexpr int8_t get_as_integer() const {
//     if (_type == value_type::boolean) return _bool;
//     else if (_type == value_type::integer) return _int;
//     else if (_type == value_type::real) return static_cast<int8_t>(_real);
//     else if (_type == value_type::string) {
//       int8_t result = 0;
//       auto fcr      = std::from_chars(_str.data(), _str.data() + _str.size(), result);
//       return fcr.ec == std::errc() ? result : 0;
//     } else return 0;
//   }
//   constexpr double get_as_real() const {
//     if (_type == value_type::boolean) return _bool;
//     else if (_type == value_type::integer) return static_cast<double>(_int);
//     else if (_type == value_type::real) return _real;
//     else if (_type == value_type::string) {
//       double result = 0.0;
//       auto fcr      = std::from_chars(_str.data(), _str.data() + _str.size(), result);
//       return fcr.ec == std::errc() ? result : 0.0;
//     } else return 0.0;
//   }
//   constexpr std::string get_as_string() const {
//     if (_type == value_type::boolean) return _bool ? "true" : "false";
//     else if (_type == value_type::integer) {
//       std::string result(32, '\0');
//       auto tcr = std::to_chars(result.data(), result.data() + result.size(), _int);
//       return tcr.ec == std::errc() ? result : "0";
//     } else if (_type == value_type::real) {
//       std::string result(32, '\0');
//       auto tcr = std::to_chars(result.data(), result.data() + result.size(), _real);
//       return tcr.ec == std::errc() ? result : "0.0";
//     } else if (_type == value_type::string) return _str;
//     else return "null";
//   }
//   template<value_type T> constexpr auto get() const {
//     if (T != _type) throw std::bad_variant_access();
//     if constexpr (T == value_type::null) return none{};
//     else if constexpr (T == value_type::boolean) return _bool;
//     else if constexpr (T == value_type::integer) return _int;
//     else if constexpr (T == value_type::real) return _real;
//     else if constexpr (T == value_type::string) return _str;
//     else static_assert(T != T, "Invalid value type");
//   }
// };
// }
