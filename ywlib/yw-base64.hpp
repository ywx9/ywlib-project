#pragma once
#include <ywlib>

namespace yw {

/// functor for `yw::base64`
class Base64 {
public:
  /// decode table
  static constexpr array<char, 128> decode_table{
    // clang-format off
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 62, -1, -1, -1, 63,
    52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1, +0, -1, -1,
    -1, +0, +1, +2, +3, +4, +5, +6, +7, +8, +9, 10, 11, 12, 13, 14,
    15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1,
    -1, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
    41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, -1, -1, -1, -1, -1, }; // clang-format on
  /// decodes a Base64 encoded string
  static constexpr array<char> decode(const str& Base64) {
    const size_t m = Base64.size(), n = (m * 3) / 4;
    if (m % 4 != 0) throw std::invalid_argument("Invalid Base64 string");
    array<char> result;
    result.reserve(n), result.resize(n);
    const char* in = Base64.data();
    char* out = result.data();
    for (const char* const end = in + m; in < end;) {
      const auto a = decode_table[*in++];
      const auto b = decode_table[*in++];
      const auto c = decode_table[*in++];
      const auto d = decode_table[*in++];
      *out++ = (a << 2) | (b >> 4);
      *out++ = (b << 4) | (c >> 2);
      *out++ = (c << 6) | d;
    }
    return result;
  }
  /// encode table
  static constexpr array<char, 64> encode_table{
    // clang-format off
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
    'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/' }; // clang-format on
  /// encodes a binary to Base64
  static constexpr str encode(const void* Input, const size_t Size) {
    const size_t m = Size * 8;        // input size in bits
    const size_t n = (m + 5) / 6;     // 6-bit block number
    const size_t o = (n + 3) / 4 * 4; // output size in bytes
    str result;
    result.reserve(o), result.resize(o, '=');
    const char* const input = static_cast<const char*>(Input);
    size_t i = 0;
    auto out = result.data();
    for (; i + 3 < Size; i += 3) {
      *out++ = encode_table[input[i] >> 2];
      *out++ = encode_table[((input[i] & 3) << 4) | (input[i + 1] >> 4)];
      *out++ = encode_table[((input[i + 1] & 15) << 2) | (input[i + 2] >> 6)];
      *out++ = encode_table[input[i + 2] & 63];
    }
    switch (Size - i) {
    case 2:
      *out++ = encode_table[input[i] >> 2];
      *out++ = encode_table[(input[i] & 3) << 4];
      break;
    case 3:
      *out++ = encode_table[input[i] >> 2];
      *out++ = encode_table[(input[i] & 3) << 4 | (input[i + 1] >> 4)];
      *out++ = encode_table[(input[i + 1] & 15) << 2];
      break;
    }
    return result;
  }
  /// encodes a binary to Base64
  static constexpr str encode(contiguous_range auto&& Range) {
    return encode(f::data(Range), f::size(Range));
  }
};

/// encodes/decodes base64 string
inline constexpr Base64 base64;
}
