#include <ywlibx>
using namespace yw;

int main::main() {
  if (main::argv.option("--ywlib")) {
    ::MessageBoxW(0, L"--ywlib is in command line", L"Info", 0);
  } else {
    ::MessageBoxW(0, L"--ywlib is NOT in command line", L"Info", 0);
  }
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
