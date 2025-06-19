#include <ywlibx>
using namespace yw;

int main::main() {
  title(format("{}", main::size));
  main::show();
  {
    auto d = main::sys::rendertarget.draw(color::yellow);
    d.line({100, 100}, {200, 200});
  }
  while (main::update()) {}
  return 0;
}

// int wmain(wchar_t**, int) {
//   std::cout << main::hinstance << std::endl;
//   std::cout << main::window.hwnd << std::endl;
//   main::window.show();

//   MSG msg;
//   while (::GetMessageW(&msg, nullptr, 0, 0)) {
//     ::TranslateMessage(&msg);
//     ::DispatchMessageW(&msg);
//   }
// }

// yw::main::main(int width = 1200, int height = 800) {
//   ::MessageBoxW(0, ::GetCommandLineW(), L"Command Line", 0);
//   // window.show();
//   // MSG msg;
//   // while (::GetMessageW(&msg, nullptr, 0, 0))
//   //   ::TranslateMessage(&msg), ::DispatchMessageW(&msg);
// }
