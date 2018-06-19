#include "unikey.h"

#include <iostream>
#include <cassert>

int main() {
  unikey::SimpleUnikey* unikey = new unikey::SimpleUnikey();

  const std::string& r = unikey->get_result();

  unikey->process('t');
  unikey->process('u');
  assert(r == "tu");
  unikey->process("wowng");
  assert(r == "tương");

  unikey->process('s');
  assert(r == "tướng");

  unikey->restore();
  assert(r == "tuwowngs");

  // test modern style on
  unikey->reset();
  unikey->process("thuys");
  assert(r == "thúy");
  auto opt = unikey::Options{
    .modern_style = 1,
  };
  unikey->set_options(opt);
  unikey->process(" thuys");
  assert(r == "thúy thuý");

  // test restore non vn on
  unikey->reset();
  opt.auto_restore_non_vn = 1;
  unikey->set_options(opt);
  unikey->process("teenn ");
  assert(r == "teenn ");

  unikey->set_input_method(unikey::SimpleUnikey::IM_VNI);
  unikey->process("thuong7");
  assert(r == "thương");

  unikey->reset();
  assert(r == "");

  std::cout << "ALL TEST SUCCESS" << std::endl;

  delete unikey;
  return 0;
}
