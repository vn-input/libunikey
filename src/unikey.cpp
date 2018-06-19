#include <map>
#include <ukengine.h>

#include "unikey.h"

using namespace unikey;

bool initLib = false;

const std::map<SimpleUnikey::InputMethod, UkInputMethod> INPUTMETHOD_MAPPING {
  {SimpleUnikey::InputMethod::TELEX, UkTelex},
  {SimpleUnikey::InputMethod::VNI, UkVni},
};

void set_default_option(UnikeyOptions *pOpt)
{
  pOpt->freeMarking = 1;
  pOpt->modernStyle = 0;
  pOpt->macroEnabled = 0;
  pOpt->useUnicodeClipboard = 0;
  pOpt->alwaysMacro = 0;
  pOpt->spellCheckEnabled = 0;
  pOpt->autoNonVnRestore = 0;
}

static void erase_utf8_chars(std::string& str, int count)
{
  int i = str.length();

  for (;i > 0;) {
    unsigned char code = str[i-1];

    // count down if code is the first byte of utf-8 char
    // REF: http://en.wikipedia.org/wiki/UTF-8
    if (code >> 6 != 2) { // ignore 10xxxxxx
      count--;
    }
    i--;

    if (count == 0) {
			break;
	  }
  }

  str.erase(i);
}

SimpleUnikey::SimpleUnikey() {
  if (!initLib) {
    SetupUnikeyEngine();
    initLib = true;
  }

  sharedMem = new UkSharedMem;
  sharedMem->charsetId = CONV_CHARSET_XUTF8;
  sharedMem->input.init();
  sharedMem->macStore.init();
  sharedMem->vietKey = 1;
  sharedMem->usrKeyMapLoaded = 0;

  engine = new UkEngine;
  engine->setCtrlInfo(sharedMem);
  engine->setCheckKbCaseFunc(NULL);

  sharedMem->initialized = 1;
  set_default_option(&sharedMem->options);
}

SimpleUnikey::~SimpleUnikey() {
  delete engine;
  delete sharedMem;
}

void SimpleUnikey::update_result(unsigned char c) {
  if (engine_buf_back > 0) {
    erase_utf8_chars(result, engine_buf_back);
  }

  if (engine_buf_size > 0) {
    result.append((char*)engine_buf, engine_buf_size);
  } else if (c > 0) {
    result.append(1, c);
  }
}

void SimpleUnikey::process(unsigned char c) {
  UkOutputType _;
  engine_buf_size = sizeof(engine_buf);

  engine->process(c, engine_buf_back, engine_buf, engine_buf_size, _);
  update_result(c);
}

void SimpleUnikey::process_backspace() {
  UkOutputType _;
  engine_buf_size = sizeof(engine_buf);

  engine->processBackspace(engine_buf_back, engine_buf, engine_buf_size, _);
  update_result(0);
}

void SimpleUnikey::process(std::string const& str) {
  UkOutputType oType;
  for (int i = 0; i < str.length(); i++) {
    process(str[i]);
  }
}

void SimpleUnikey::restore() {
  UkOutputType _;
  engine_buf_size = sizeof(engine_buf);

  engine->restoreKeyStrokes(engine_buf_back, engine_buf, engine_buf_size, _);

  if (engine_buf_back > 0) {
    erase_utf8_chars(result, engine_buf_back);
  }

  if (engine_buf_size > 0) {
    result.append((char*)engine_buf, engine_buf_size);
  }
}

const std::string& SimpleUnikey::get_result() {
  return result;
}

void SimpleUnikey::reset() {
  engine->reset();
  result.clear();
}

void SimpleUnikey::set_input_method(const InputMethod im) {
  sharedMem->input.setIM(INPUTMETHOD_MAPPING.at(im));
  reset();
}

void SimpleUnikey::set_options(const Options& opt) {
  sharedMem->options.modernStyle = opt.modern_style;
  sharedMem->options.autoNonVnRestore = opt.auto_restore_non_vn;
  sharedMem->options.spellCheckEnabled = opt.spellcheck;
}
