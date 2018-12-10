#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <tuple>
#include <utility>

namespace filters {

struct NoRepeatedNumbers {
  bool operator()(char c) {
    if (std::isdigit(c)) {
      is_last_num_ = true;
      if (last_num_ == c) {
        return false;
      }
      last_num_ = c;
    } else {
      is_last_num_ = false;
    }
    return true;
  }

private:
  char last_num_ = 0;
  bool is_last_num_ = false;
};

struct AlphNum {
  bool operator()(char c) { return std::isalnum(c); }
};

struct NoA {
  bool operator()(char c) { return c != 'a' && c != 'A'; }
};
}

template <size_t I = 0, typename... Tf>
inline typename std::enable_if<I == sizeof...(Tf), bool>::type
filter_char_check(char c, std::tuple<Tf...> &functors) {
  return true;
}

template <size_t I = 0, typename... Tf>
    inline typename std::enable_if <
    I<sizeof...(Tf), bool>::type
    filter_char_check(char c, std::tuple<Tf...> &functors) {
  auto &func = std::get<I>(functors);
  return func(c) && filter_char_check<I + 1>(c, functors);
}

template <typename... TFunctors>
size_t filter(std::string in, std::string &out) {
  std::tuple<TFunctors...> functors;
  for (auto c : in) {
    if (filter_char_check(c, functors)) {
      out += c;
    }
  }
  return out.size();
}

int main() {
  std::string in, out;
  in = "aAbBcC%^&122223";
  size_t s = filter<filters::NoRepeatedNumbers,
    filters::AlphNum,
    filters::NoA>(in, out);

  std::cout << "Filt: " << out << "\n";
  return 0;
}
