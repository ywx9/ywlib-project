#pragma once
#include <yw-args.hpp>
#include <yw-bitmap.hpp>

namespace yw {

namespace main {

/// user-defined window procedure
inline bool (*userproc)(wmessage msg, size_t wp, size_t lp) = nullptr;

/// path to the dropped files into main-window
inline array<path> dropped_files{};

namespace sys {

/// flag to check if the main-window is active
inline bool is_active = false;

/// main-window procedure
size_t __stdcall window_proc(HANDLE hw, int msg, size_t wp, size_t lp) {
  if (userproc && userproc(wmessage(msg), wp, lp)) return 0;
  else if (msg == WM_CTLCOLOREDIT) {
    print(source{});
    HANDLE hdc = (HANDLE)wp;
    ::SetBkMode(hdc, 1);
    return (size_t)::GetStockObject(5); // NULL BRUSH
  } else if (msg == WM_DROPFILES) {
    auto drop = (HANDLE)wp;
    POINT pt;
    ::DragQueryPoint(drop, &pt);
    auto n = ::DragQueryFileW(drop, 0xffffffff, nullptr, 0);
    dropped_files.reserve(n), dropped_files.resize(n);
    wchar_t s[FILENAME_MAX];
    for (int i{}; i < n; ++i) dropped_files[i] = path(wstr(s, ::DragQueryFileW(drop, i, s, FILENAME_MAX)));
    ::DragFinish(drop);
  } else if (msg == WM_DESTROY) is_active = false, ::PostQuitMessage(0);
  return ::DefWindowProcW(hw, msg, wp, lp);
}

/// instance handle
inline const HANDLE instance = ::GetModuleHandleW(nullptr);

/// windows username
inline const wstr username = [](int n) -> wstr {
  ::GetUserNameW(nullptr, &n);
  wstr s(n - 1, L'\0');
  ::GetUserNameW(s.data(), &n);
  return s;
}({});

/// primary desktop window size
inline const vector2<int> desktop_size = []() -> vector2<int> {
  RECT rc;
  ::GetClientRect(::GetDesktopWindow(), &rc);
  return {rc.right, rc.bottom};
}();

/// main-window class name
inline constexpr const wchar_t* class_name = L"ywlib-main-window";

/// main-window class atom
inline const uint16_t class_atom = [](WNDCLASSEXW wc) {
  wc.hInstance     = instance;
  wc.hCursor       = ::LoadCursorW(nullptr, IDC_ARROW);
  wc.hbrBackground = (HANDLE)(COLOR_WINDOW + 1);
  wc.lpszClassName = class_name;
  auto a           = ::RegisterClassExW(&wc);
  if (!a) yw::ok(L"Failed to register window class", L"Fatal Error");
  return a;
}({sizeof(WNDCLASSEXW), {}, window_proc});

/// main-window padding
inline vector4<int> padding{};

/// main-window handle
inline const HANDLE hwnd = []() -> HANDLE {
  constexpr int sz{400};
  auto hw = ::CreateWindowExW(WS_EX_ACCEPTFILES, class_name, 0, WS_SYSMENU | WS_CLIPCHILDREN, 0, 0, sz, sz, 0, 0, instance, 0);
  if (!hw) return yw::ok(L"Failed to create main-window", L"Fatal Error"), nullptr;
  is_active = true;
  ::GetClientRect(hw, (RECT*)&padding);
  padding.x = (sz - padding.z) / 2, padding.z = 2 * padding.x;
  padding.y = sz - padding.w - padding.x, padding.w = padding.x + padding.y;
  int init_x = int(stoi(main::argv.option("--main-x", "-1")));
  int init_y = int(stoi(main::argv.option("--main-y", "-1")));
  int init_w = int(abs(stoi(main::argv.option("--main-width", "800"))));
  int init_h = int(abs(stoi(main::argv.option("--main-height", "600"))));
  init_w += padding.z, init_h += padding.w;
  if (init_x < 0) init_x = (desktop_size.x - init_w) / 2;
  if (init_y < 0) init_y = (desktop_size.y - init_h) / 2;
  ::SetWindowPos(hw, nullptr, init_x, init_y, init_w, init_h, SWP_NOZORDER);
  if (main::argv.option("--main-show")) ::ShowWindow(hw, SW_SHOW), ::SetForegroundWindow(hw), ::SetActiveWindow(hw);
  return hw;
}();

/// main-window message
inline MSG message{};

/// swap-chain for the main-window
inline comptr<::IDXGISwapChain1> swapchain = [](comptr<::IDXGISwapChain1> p) -> comptr<::IDXGISwapChain1> {
  RECT r;
  ::GetClientRect(sys::hwnd, &r); // clang-format off
  DXGI_SWAP_CHAIN_DESC1 desc{uint32_t(r.right), uint32_t(r.bottom), default_dxgi_format, false, {1, 0}, {}, 2}; // clang-format on
  desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
  desc.SwapEffect  = DXGI_SWAP_EFFECT_DISCARD;
  auto hr          = dxgi_factory->CreateSwapChainForHwnd(d3d_device.get(), hwnd, &desc, nullptr, nullptr, &p.get());
  if (hr != 0) yw::ok(L"Failed to create swapchain", L"Fatal Error");
  else if (debug) print("Created swapchain for main-window: {}x{}", desc.Width, desc.Height);
  return p;
}({});

/// render-target for the main-window
inline bitmap rendertarget = [] {
  try {
    return bitmap(swapchain.get());
  } catch (const std::exception& e) {
    print("Error: {}", e.what());
    yw::ok(L"Failed to create render-target", L"Fatal Error");
    return bitmap{};
  }
}();
}

/// shows, activates and brings the main-window to the foreground
inline void show() noexcept {
  ::ShowWindow(sys::hwnd, SW_SHOW);
  ::SetForegroundWindow(sys::hwnd);
  ::SetActiveWindow(sys::hwnd);
}

/// hides the main-window
inline void hide() noexcept {
  ::ShowWindow(sys::hwnd, SW_HIDE);
}

/// functor for `yw::main::title`
struct Title {
  /// gets the title of the main-window
  wstr operator()() const {
    int n = ::GetWindowTextLengthW(sys::hwnd);
    if (n <= 0) return wstr{};
    wstr buf(n, L'\0');
    ::GetWindowTextW(sys::hwnd, buf.data(), n + 1);
    return buf;
  }
  /// gets the title of the main-window
  operator wstr() const { return operator()(); }
  /// sets the title of the main-window
  template<stringable S> void operator()(S&& s) const {
    auto ss = unicode<wchar_t>(static_cast<S&&>(s));
    ::SetWindowTextW(sys::hwnd, ss.c_str());
  }
};
/// gets/sets the title of the main-window
inline constexpr caster<Title> title{};

/// functor for `yw::main::size`
struct Size {
  /// gets the size of the main-window
  vector2<int> operator()() const {
    RECT r;
    ::GetClientRect(sys::hwnd, &r);
    return {r.right, r.bottom};
  }
  /// gets the size of the main-window
  operator vector2<int>() const { return operator()(); }
  /// sets the size of the main-window
  void operator()(const vector2<int>& size, const source& _ = {}) const {
    main::sys::rendertarget = {};
    auto hr                 = main::sys::swapchain->ResizeBuffers(2, size.x, size.y, {}, 0);
    if (hr != 0) throw std::runtime_error(format("Error {:x}: {} <- {}", hr, source{}, _));
    main::sys::rendertarget = bitmap(main::sys::swapchain.get());
    ::SetWindowPos(sys::hwnd, nullptr, 0, 0, size.x + main::sys::padding.z, size.y + main::sys::padding.w, SWP_NOMOVE | SWP_NOZORDER);
  }
  /// sets the size of the main-window
  void operator()(convertible_to<int> auto&& Width, convertible_to<int> auto&& Height, const source& _ = {}) const {
    operator()(vector2<int>{static_cast<int>(Width), static_cast<int>(Height)}, _);
  }
};
/// gets/sets the size of the main-window
inline constexpr caster<Size> size{};
/// gets the width of the main-window
inline constexpr caster width{[]() -> int { return size().x; }};
/// gets the height of the main-window
inline constexpr caster height{[]() -> int { return size().y; }};

/// functor for `yw::main::key`
class Key {
  inline static bool now{};
  inline static array<array<char, 256>, 2> state{};
public:
  /// updates key state
  static void update() { ::GetKeyboardState(state[now = !now].data()); }
  /// virtual key code
  const int code;
  /// constructor
  Key(int code) noexcept : code(code & 0xff) {}
  /// checks if the key is down
  bool down() const noexcept { return state[now][code] & 0x80; }
  /// checks if the key is just pressed
  bool pressed() const noexcept { return (state[now][code] & 0x80) && !(state[!now][code] & 0x80); }
  /// checks if the key is just released
  bool released() const noexcept { return !(state[now][code] & 0x80) && (state[!now][code] & 0x80); }
  /// checks if the key is down
  operator bool() const noexcept { return down(); }
};

namespace key {
inline const Key lbutton(0x01), rbutton(0x02), mbutton(0x04), xbutton1(0x05), xbutton2(0x06);
inline const Key back(0x08), tab(0x09), enter(0x0d), shift(0x10), ctrl(0x11), alt(0x12), capslock(0x14);
inline const Key escape(0x1B), space(0x20), pageup(0x21), pagedown(0x22), end(0x23), home(0x24);
inline const Key left(0x25), up(0x26), right(0x27), down(0x28);
inline const Key insert(0x2D), delete_(0x2E), printscreen(0x2C);
inline const Key n0(0x30), n1(0x31), n2(0x32), n3(0x33), n4(0x34), n5(0x35), n6(0x36), n7(0x37), n8(0x38), n9(0x39);
inline const Key a(0x41), b(0x42), c(0x43), d(0x44), e(0x45), f(0x46), g(0x47), h(0x48), i(0x49);
inline const Key j(0x4A), k(0x4B), l(0x4C), m(0x4D), n(0x4E), o(0x4F), p(0x50), q(0x51), r(0x52);
inline const Key s(0x53), t(0x54), u(0x55), v(0x56), w(0x57), x(0x58), y(0x59), z(0x5A);
inline const Key np0(0x60), np1(0x61), np2(0x62), np3(0x63), np4(0x64), np5(0x65), np6(0x66), np7(0x67), np8(0x68), np9(0x69);
inline const Key np_mul(0x6A), np_add(0x6B), np_sub(0x6D), np_dec(0x6E), np_div(0x6F);
inline const Key f1(0x70), f2(0x71), f3(0x72), f4(0x73), f5(0x74), f6(0x75);
inline const Key f7(0x76), f8(0x77), f9(0x78), f10(0x79), f11(0x7A), f12(0x7B);
inline const Key numlock(0x90), scrolllock(0x91);
inline const Key lshift(0xA0), rshift(0xA1), lcontrol(0xA2), rcontrol(0xA3), lmenu(0xA4), rmenu(0xA5);
}

/// functor for `yw::main::point`
class Point : public vector2<int> {
  inline static vector2<int> old{};
public:
  /// gets the cursor position
  vector2<int> operator()() const { return {x, y}; }
  /// sets the cursor position
  void operator()(vector2<int> xy) { ::ClientToScreen(sys::hwnd, (POINT*)&xy), ::SetCursorPos(x = xy.x, y = xy.y); }
  /// gets delta of the cursor position
  vector2<int> delta() const { return {x - old.x, y - old.y}; }
  /// updates cursor position
  void update() { old = {x, y}, ::GetCursorPos((POINT*)this), ::ScreenToClient(sys::hwnd, (POINT*)this); }
};
/// cursor position relative to the client area of the main-window
inline caster<Point> point{};

class edit {
  inline static const WNDCLASSEXW original_wndclass = [](WNDCLASSEXW wc) -> WNDCLASSEXW {
    ::GetClassInfoExW(sys::instance, L"EDIT", &wc);
    wc.cbSize = sizeof(WNDCLASSEXW);
    return wc;
  }({});
  static size_t __stdcall customized_wndproc(HANDLE hwnd, int msg, size_t wp, size_t lp) {
    switch (wmessage(msg)) {
    }
    return original_wndclass.lpfnWndProc(hwnd, msg, wp, lp);
  }
  inline static const WNDCLASSEXW customized_wndclass = []() -> WNDCLASSEXW {
    WNDCLASSEXW wc   = original_wndclass;
    wc.lpszClassName = L"__ywlib_edit__";
    return wc;
  }();
  inline static const uint16_t customized_wndclass_atom = ::RegisterClassExW(&customized_wndclass);
public:
  HANDLE hwnd;
  edit(vector2<int> xy, vector2<int> wh, const source& _ = {})
    : hwnd(::CreateWindowExW(WS_EX_TRANSPARENT, customized_wndclass.lpszClassName, nullptr, WS_CHILD | WS_VISIBLE, //
                             xy.x, xy.y, wh.x, wh.y, sys::hwnd, nullptr, sys::instance, nullptr)) {
    if (!hwnd) throw std::runtime_error(format("Failed to create edit control: {} <- {}", source{}, _));
  }
};

/// functor for `yw::main::update`
struct Update {
  /// updates the main-window
  bool operator()() const {
    sys::swapchain->Present(1, 0);
    while (true) {
      if (::PeekMessageW(&sys::message, nullptr, 0, 0, 1)) {
        ::TranslateMessage(&sys::message), ::DispatchMessageW(&sys::message);
        continue;
      }
      Key::update();
      point.update();
      return sys::is_active;
    }
    return false;
  }
  /// updates the main-window
  operator bool() const { return operator()(); }
};
/// updates the main-window
inline constexpr caster<Update> update{};

/// begins drawing on the main-window
inline bitmap::drawing draw() { return main::sys::rendertarget.draw(); }

/// begins drawing on the main-window with a clear color
inline bitmap::drawing draw(const yw::color& Clear) { return main::sys::rendertarget.draw(Clear); }

/// saves the screenshot
inline void screenshot(const path& File) { sys::rendertarget.to_file(File); }
}
}
