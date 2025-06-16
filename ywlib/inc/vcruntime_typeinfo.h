#pragma once
#include <inc/vcruntime_exception.h>

extern "C++" struct __type_info_node;
extern "C++" extern __type_info_node __type_info_root_node;

extern "C" {
struct __std_type_info_data {
  const char* _UndecoratedName;
  const char _DecoratedName[1];
  __std_type_info_data() = delete;
  __std_type_info_data(const __std_type_info_data&) = delete;
  __std_type_info_data(__std_type_info_data&&) = delete;
  __std_type_info_data& operator=(const __std_type_info_data&) = delete;
  __std_type_info_data& operator=(__std_type_info_data&&) = delete;
};
int __cdecl __std_type_info_compare(const __std_type_info_data* _Lhs, const __std_type_info_data* _Rhs);
size_t __cdecl __std_type_info_hash(const __std_type_info_data* _Data);
const char* __cdecl __std_type_info_name(__std_type_info_data* _Data, __type_info_node* _RootNode);
}

export extern "C++" class type_info {
  mutable __std_type_info_data _Data;
public:
  type_info(const type_info&) = delete;
  type_info& operator=(const type_info&) = delete;
  _NODISCARD size_t hash_code() const noexcept { return __std_type_info_hash(&_Data); }
  _NODISCARD constexpr bool operator==(const type_info& _Other) const noexcept {
    if (__builtin_is_constant_evaluated()) return &_Data == &_Other._Data;
    return __std_type_info_compare(&_Data, &_Other._Data) == 0;
  }
  _NODISCARD bool operator!=(const type_info& _Other) const noexcept { return __std_type_info_compare(&_Data, &_Other._Data) != 0; }
  _NODISCARD bool before(const type_info& _Other) const noexcept { return __std_type_info_compare(&_Data, &_Other._Data) < 0; }
  _NODISCARD const char* name() const noexcept { return __std_type_info_name(&_Data, &__type_info_root_node); }
  _NODISCARD const char* raw_name() const noexcept { return _Data._DecoratedName; }
  virtual ~type_info() noexcept;
};

export namespace std {

using ::type_info;

class bad_cast : public exception {
  bad_cast(const char* const _Message, int) noexcept: exception(_Message, 1) {}
public:
  bad_cast() noexcept: exception("bad cast", 1) {}
  static bad_cast __construct_from_string_literal(const char* const _Message) noexcept {return bad_cast(_Message, 1);}
};

class bad_typeid: public exception {
  friend class __non_rtti_object;
  bad_typeid(const char* const _Message, int) noexcept: exception(_Message, 1) {}
public:
  bad_typeid() noexcept: exception("bad typeid", 1) {}
  static bad_typeid __construct_from_string_literal(const char* const _Message) noexcept {return bad_typeid(_Message, 1);}
};

class __non_rtti_object: public bad_typeid {
  __non_rtti_object(const char* const _Message, int) noexcept: bad_typeid(_Message, 1) {}
public:
  static __non_rtti_object __construct_from_string_literal(const char* const _Message) noexcept {return __non_rtti_object(_Message, 1);}
};
} // namespace std
