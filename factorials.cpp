#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <iterator>

int main(int argc, char* argv[])
{
  const int factorial = 10000;
  auto log10 = [](int v) { int log = 1; while(v /= 10) { log++; }; return log; };
  int digit_count = factorial * log10(factorial); // max result digit numbers (overestimated)

  auto res = std::vector<int>(digit_count,1); // factorial result as series of 0-9 numbers, init with 1
  std::cout << "1: 1"; // also print out this result separately

  int res_size = 1; // the size of the result number
  // incrementing factorials loop
  for(int f = 2; f <= factorial; f++) {
    std::cout << "\n" << f << ": ";
    int rem = 0;
    // multiplication of already existing digits one by one
    for(int d = 0; d < res_size; d++) {
      int v = res[d] * f + rem;
      res[d] = v % 10;
         rem = v / 10;
    }
    // remainder enlarges the result, sometimes with multiple digits
    while (rem) {
      res[res_size++] = rem % 10;
      rem /= 10;
    };

    // print out this factorial
#if __cplusplus/100 < 2017
    std::stringstream s;
    std::reverse_copy(res.begin(), res.begin() + res_size, std::ostream_iterator<int>(s));
    std::cout << s.str();
#else
    // I've seen this copy() with rbegin() rend() thing on the internet, let's give it a try
    // update: it is even faster, roughly by 30%
    std::stringstream s;
    std::copy(std::rbegin(res) + digit_count - res_size, std::rend(res), std::ostream_iterator<int>(s));
    std::cout << s.str();
#endif


  }
  std::cout << "\n";
}
