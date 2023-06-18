#include "unikey.h"

#include <iostream>
#include <cassert>

int main() {
  unikey::SimpleUnikey* unikey = new unikey::SimpleUnikey();

  const std::string& r = unikey->get_result();

  unikey->process('t');
  unikey->process('u');
  assert(r == "tu");
  unikey->process(L"wowng");
  assert(r == "tương");

  unikey->process('s');
  assert(r == "tướng");

  unikey->restore();
  assert(r == "tuwowngs");

  // test some wide characters available on French keyboard
  unikey->reset();
  unikey->process(L'€');
  unikey->process(L'ç');
  unikey->process(L'£');
  unikey->process(L'µ');
  assert(r == "€ç£µ");

  // test modern style on
  unikey->reset();
  unikey->process(L"thuys");
  assert(r == "thúy");
  auto opt = unikey::Options{};
  opt.modern_style = 1;
  unikey->set_options(opt);
  unikey->process(L" thuys");
  assert(r == "thúy thuý");

  // test restore non vn on
  unikey->reset();
  opt.spellcheck = 1; // auto-restore require spellcheck on
  opt.auto_restore_non_vn = 1;
  unikey->set_options(opt);
  unikey->process(L"teenn ");
  assert(r == "teenn ");

  unikey->set_input_method(unikey::SimpleUnikey::InputMethod::VNI);
  unikey->process(L"thuong7");
  assert(r == "thương");

  unikey->reset();
  assert(r == "");

  std::cout << "ALL TEST SUCCESS" << std::endl;

  delete unikey;
  return 0;
}
