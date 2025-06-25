#include <ywlibx>
using namespace yw;

int main::main() {

  edit e({100, 100}, {200, 30});
  print(base64.encode("ABCDEFG"));
  print(base64.decode("QUJDREVGRw=="));

  main::show();
  color c;
  while (main::update()) {
    if (key::lbutton.down()) c = color::red;
    else c = color::green;
    main::draw(c);
    // print(main::point);
  }

  return 0;
}
