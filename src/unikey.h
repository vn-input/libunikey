#ifndef __LIB_UNIKEY__
#define __LIB_UNIKEY__

#include <string>

class UkEngine;
struct UkSharedMem;

namespace unikey {

struct Options {
  // use oà uý instead of òa úy
  bool modern_style;
  // véion --after space-> version
  bool auto_restore_non_vn;
  // type gõtiếngviệt will be gõtieensgvieejt
  bool spellcheck;
};

// simple interface wrapper for unikey
class SimpleUnikey {
public:
  SimpleUnikey();
  ~SimpleUnikey();

  enum class InputMethod {
    TELEX,
    VNI,
    TELEX_SIMPLE,
  };

  void reset();
  void process(unsigned int c);
  void process(std::wstring const& str);
  void process_backspace();
  void restore();
  const std::string& get_result();

  void set_input_method(const InputMethod im);
  void set_options(const Options& opt);

private:
  UkEngine *engine;
  UkSharedMem *sharedMem;

  std::string result;
  void appendCodePoint(std::string& str, unsigned int codePoint);

  // engine results
  unsigned char engine_buf[1024];
  int engine_buf_size;
  int engine_buf_back;
  void update_result(unsigned int c);
};

}

#endif // __LIB_UNIKEY__
