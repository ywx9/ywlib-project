#include <ywlibx>
using namespace yw;

int main::main() {

  main::show();
  color c;
  while (main::update()) {
    if (key::lbutton.down()) c = color::red;
    else c = color::green;
    main::draw(c);
    print(main::point);
  }

  return 0;
}
