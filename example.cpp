#include <ywlibx>
using namespace yw;

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


yw::main::main(int width = 1200, int height = 800) {
  ::MessageBoxW(0, ::GetCommandLineW(), L"Command Line", 0);
  // window.show();
  // MSG msg;
  // while (::GetMessageW(&msg, nullptr, 0, 0))
  //   ::TranslateMessage(&msg), ::DispatchMessageW(&msg);
}
