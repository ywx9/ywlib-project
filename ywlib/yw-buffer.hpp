#pragma once
#include <yw-com.hpp>

namespace yw {

template<typename T> class staging_buffer;

/// base class for gpu buffers
template<typename T> class buffer {
protected:
  comptr<::ID3D11Buffer> d3d_buffer{};
  buffer(arithmetic auto Count) noexcept : count(int(Count)) {}
public:
  using value_type = T;
  explicit operator bool() const noexcept { return bool(d3d_buffer); }
  ::ID3D11Buffer* operator->() const noexcept { return d3d_buffer.get(); }
  const int count{};
  /// default constructor
  buffer() noexcept = default;
  /// move constructor
  buffer(buffer&& b) noexcept : d3d_buffer(mv(b.d3d_buffer)), count(b.count) {}
  /// move assignment
  buffer& operator=(buffer&& b) noexcept {
    if (this != &b) d3d_buffer = mv(b.d3d_buffer), const_cast<int&>(count) = b.count;
    return *this;
  }
  void from(const buffer& src, const source& _ = {}) {
    if (!src) throw std::runtime_error(format("Source buffer is empty: {} <- {}", source{}, _));
    if (!d3d_buffer) throw std::runtime_error(format("Destination buffer is empty: {} <- {}", source{}, _));
    if (src.count != count) throw std::runtime_error(format("Buffer size mismatch: {} <- {}", source{}, _));
    main::sys::d3d_context->CopyResource(d3d_buffer, src.d3d_buffer);
  }
  /// copies data from gpu to cpu
  array<T> to_cpu(const source& = {}) const;
  /// copies data from gpu to cpu
  array<T> to_cpu(staging_buffer<T>&, const source& = {}) const;
};

/// class to copy data from GPU to CPU
template<typename T> class staging_buffer : public buffer<T> {
public:
  using buffer<T>::operator bool;
  using buffer<T>::operator->;
  staging_buffer() noexcept = default;
  explicit staging_buffer(const buffer<T>& b, const source& _ = {}) : staging_buffer(int(b.count), _) { buffer<T>::from(b); }
  explicit staging_buffer(arithmetic auto Count, const source& _ = {}) : buffer<T>(Count) {
    D3D11_BUFFER_DESC desc{int(sizeof(T) * Count), D3D11_USAGE_STAGING, {}, D3D11_CPU_ACCESS_READ, {}, 0};
    auto hr = main::sys::d3d_device->CreateBuffer(&desc, nullptr, &buffer<T>::d3d_buffer.get());
    if (hr != 0) throw std::runtime_error(format("Error {:x}: {} <- {}", hr, source{}, _));
  }
  array<T> to_cpu(const source& _ = {}) const {
    array<T> Data(buffer<T>::count);
    D3D11_MAPPED_SUBRESOURCE mapped;
    auto hr = main::sys::d3d_context->Map(buffer<T>::operator->(), 0, D3D11_MAP_READ, 0, &mapped);
    if (hr != 0) throw std::runtime_error(format("Error {:x}: {} <- {}", hr, source{}, _));
    std::memcpy(Data.data(), mapped.pData, buffer<T>::count * sizeof(T));
    main::sys::d3d_context->Unmap(buffer<T>::operator->(), 0);
    return Data;
  }
};
template<typename T> staging_buffer(const buffer<T>&) -> staging_buffer<T>;

template<typename T> array<T> buffer<T>::to_cpu(const source& _) const {
  staging_buffer<T> staging(*this);
  return staging.to_cpu(_);
}
template<typename T> array<T> buffer<T>::to_cpu(staging_buffer<T>& Staging, const source& _) const {
  Staging.from(*this, _);
  return Staging.to_cpu(_);
}

/// constant buffer class
template<typename T> requires(sizeof(T) % 16 == 0) class constant_buffer : public buffer<T> {
  static constexpr D3D11_BUFFER_DESC desc{sizeof(T), D3D11_USAGE_DYNAMIC, D3D11_BIND_CONSTANT_BUFFER, D3D11_CPU_ACCESS_WRITE};
public:
  using buffer<T>::operator bool;
  using buffer<T>::operator->;
  constant_buffer() : buffer<T>(1) {
    auto hr = main::sys::d3d_device->CreateBuffer(&desc, nullptr, &buffer<T>::d3d_buffer.get());
    if (hr != 0) throw std::runtime_error(format("Error {:x}: {}", hr, source{}));
  }
  explicit constant_buffer(const T& Val, const source& _ = {}) : buffer<T>(1) {
    D3D11_SUBRESOURCE_DATA srd(&Val, 0, 0);
    auto hr = main::sys::d3d_device->CreateBuffer(&desc, &srd, &buffer<T>::d3d_buffer.get());
    if (hr != 0) throw std::runtime_error(format("Error {:x}: {} <- {}", hr, source{}, _));
  }
  void from(const T& Val, const source& _ = {}) {
    D3D11_MAPPED_SUBRESOURCE mapped;
    auto hr = main::sys::d3d_context->Map(this, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped);
    if (hr != 0) throw std::runtime_error(format("Error {:x}: {} <- {}", hr, source{}, _));
    std::memcpy(mapped.pData, &Val, sizeof(T));
    main::sys::d3d_context->Unmap(this, 0);
  }
};
template<typename T> constant_buffer(const T&) -> constant_buffer<T>;

/// read-only structured buffer class
template<typename T> class structured_buffer : public buffer<T> {
  void _init(const T* Data, const source& _) {
    HRESULT hr{};
    D3D11_BUFFER_DESC bd{int(sizeof(T) * buffer<T>::count), {}, D3D11_BIND_SHADER_RESOURCE, {}, D3D11_RESOURCE_MISC_BUFFER_STRUCTURED, sizeof(T)};
    if (Data) {
      D3D11_SUBRESOURCE_DATA srd{Data, int(sizeof(T))};
      hr = main::sys::d3d_device->CreateBuffer(&bd, &srd, &buffer<T>::d3d_buffer.get());
    } else hr = main::sys::d3d_device->CreateBuffer(&bd, nullptr, &buffer<T>::d3d_buffer.get());
    if (hr != 0) throw std::runtime_error(format("Error {:x}: {} <- {}", hr, source{}, _));
    D3D11_SHADER_RESOURCE_VIEW_DESC srv_desc{
      {},
      D3D11_SRV_DIMENSION_BUFFER,
      D3D11_BUFFER_SRV{0, buffer<T>::count}
    };
    hr = main::sys::d3d_device->CreateShaderResourceView(buffer<T>::operator->(), &srv_desc, &d3d_srv.get());
    if (hr != 0) throw std::runtime_error(format("Error {:x}: {} <- {}", hr, source{}, _));
  }
protected:
  comptr<::ID3D11ShaderResourceView> d3d_srv{};
public:
  explicit operator bool() const noexcept { return buffer<T>::d3d_buffer && d3d_srv; }
  ::ID3D11ShaderResourceView* operator->() const noexcept { return d3d_srv.get(); }
  structured_buffer() noexcept = default;
  explicit structured_buffer(const buffer<T>& Src, const source& _ = {}) : structured_buffer(Src.count, _) { buffer<T>::from(Src); }
  explicit structured_buffer(size_t Count, const source& _ = {}) : buffer<T>(Count) { _init(nullptr, _); }
  explicit structured_buffer(const T* Data, size_t Count, const source& _ = {}) : buffer<T>(Count) { _init(Data, _); }
  template<contiguous_range R> requires same_as<iter_value_t<R>, T>
  explicit structured_buffer(R&& r, const source& _ = {}) : structured_buffer(data(r), size(r), _) {}
  template<contiguous_range R> requires same_as<iter_value_t<R>, T> void from(R&& r, const source& _ = {}) {
    if (buffer<T>::count != yw::size(r)) throw std::runtime_error(format("invalid source: {} <- {}", source{}, _));
    main::sys::d3d_context->UpdateSubresource(buffer<T>::operator ::ID3D11Buffer*(), 0, nullptr, yw::data(r), 0, 0);
  }
};
template<typename T> structured_buffer(const buffer<T>&) -> structured_buffer<T>;
template<typename T> structured_buffer(const T*, size_t, const source& = {}) -> structured_buffer<T>;
template<contiguous_range R> structured_buffer(R&&, const source& = {}) -> structured_buffer<iter_value_t<R>>;

/// read-write structured buffer class
template<typename T> class rw_structured_buffer : public buffer<T> {
  void _init(const T* Data, const source& _) {
    HRESULT hr{};
    D3D11_BUFFER_DESC desc{int(sizeof(T) * buffer<T>::count), {}, D3D11_BIND_UNORDERED_ACCESS, {}, D3D11_RESOURCE_MISC_BUFFER_STRUCTURED, sizeof(T)};
    if (Data) {
      D3D11_SUBRESOURCE_DATA srd{Data, int(sizeof(T))};
      hr = main::sys::d3d_device->CreateBuffer(&desc, &srd, &buffer<T>::d3d_buffer.get());
    } else hr = main::sys::d3d_device->CreateBuffer(&desc, nullptr, &buffer<T>::d3d_buffer.get());
    if (hr != 0) throw std::runtime_error(format("Error {:x}: {} <- {}", hr, source{}, _));
    hr = main::sys::d3d_device->CreateUnorderedAccessView(buffer<T>::operator->(), nullptr, &d3d_uav.get());
    if (hr != 0) throw std::runtime_error(format("Error {:x}: {} <- {}", hr, source{}, _));
  }
protected:
  comptr<::ID3D11UnorderedAccessView> d3d_uav;
public:
  explicit operator bool() const noexcept { return buffer<T>::d3d_buffer && d3d_uav; }
  ::ID3D11UnorderedAccessView* operator->() const noexcept { return d3d_uav.get(); }
  /// default constructor
  rw_structured_buffer() noexcept = default;
  /// constructs a read-write structured buffer and initializes it with another buffer
  explicit rw_structured_buffer(const buffer<T>& Src, const source& _ = {})
    : rw_structured_buffer(Src.count, _) { buffer<T>::from(Src); }
  /// constructs a read-write structured buffer with the specified size
  explicit rw_structured_buffer(size_t Count, const source& _ = {}) : buffer<T>(Count) { _init(nullptr, _); }
  /// constructs a read-write structured buffer and initializes it with cpu data
  explicit rw_structured_buffer(const T* Data, size_t Count, const source& _ = {}) : buffer<T>(Count) { _init(Data, _); }
  /// constructs a read-write structured buffer and initializes it with cpu data
  template<contiguous_range<T> R> explicit rw_structured_buffer(R&& r, const source& _ = {})
    : rw_structured_buffer(data(r), size(r), _) {}
  /// assigns cpu data to the buffer
  template<contiguous_range<T> R> void from(R&& r, const source& _ = {}) {
    if (buffer<T>::count != yw::size(r)) throw std::runtime_error(format("Buffer size mismatch: {} <- {}", source{}, _));
    main::sys::d3d_context->UpdateSubresource(this, 0, nullptr, data(r), 0, 0);
  }
};
template<typename T> rw_structured_buffer(const buffer<T>&) -> rw_structured_buffer<T>;
template<typename T> rw_structured_buffer(const T*, size_t, const source& = {}) -> rw_structured_buffer<T>;
template<contiguous_range R> rw_structured_buffer(R&&, const source& = {}) -> rw_structured_buffer<iter_value_t<R>>;
}
