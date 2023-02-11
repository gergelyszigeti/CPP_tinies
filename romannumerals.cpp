#include <string>
#include <iostream>
#include <chrono>

class RomanHelper{
  public:
    std::string to_roman(unsigned int n){
      // helper function - note, it is not speed optimal, pos LUT needed
      auto symbol = [](unsigned int n, const int m) {
        const char* common_patterns = "2a3aa4aaa3ab2b3ba4baa5baaa3ac2c";
        const char* symbols = "IVXLCDM";
        std::string ret_symbol;
        // find the nth generic symbol in common table
        int i = 0; while(--n) { i += common_patterns[i] - '0';}
        // substitute char placeholders with proper symbols
        for (int j = 1; j < common_patterns[i] - '0'; j++ ) {
          ret_symbol += symbols[common_patterns[i+j] - 'a' + m * 2];
        }
        return ret_symbol;
      };

      // parser, each line for one digit
      std::string roman;
      while (n > 999) { roman += "M"; n -= 1000;}
      if (n / 100) { roman += symbol(n / 100, 2); n %= 100; }
      if (n /  10) { roman += symbol(n /  10, 1); n %=  10; }
      if (n /   1) { roman += symbol(n /   1, 0);           }
      return roman;
      //--------------------------------------------------------------------
    }
    int from_roman(std::string rn){
      int i = 0;
      // helper function
      auto get_same_chars = [&rn, &i] {
        const char* symbols = "IVXLCDM"; // note: this string is a duplicate
        char c = rn.c_str()[i]; if (c == 0) { return 0; }
        int s = 0;
        // note: count and value are separate variables only for readability
        int count = 1; while (rn.c_str()[++i] == c) { count++; }
        int value = 1; while (   symbols[s++] != c) { value *= s%2? 5 : 2; }
        return count * value;
      };

      // parser loop
      int arabic = 0, last_value = 5000;
      while (int value = get_same_chars()) {
        if (value > last_value) { value -= last_value * 2; }
        arabic += value;
        last_value = value;
      }
      return arabic;
    }
} RomanNumerals;

int main(int argc, const char* argv[])
{
    for (int i = 0; i < 20; i++) {
       // let's see, maybe these are microseconds if I'm correct
       // note, numbers should be between 1 and 4000
       int number = static_cast<int>(std::chrono::system_clock::
                       now().time_since_epoch().count() % 4000 + 1);
       auto  roman = RomanNumerals.to_roman(number);
       auto arabic = RomanNumerals.from_roman(roman);
       std::cout << number << " converted to roman is " << roman << ", "
                 << roman << " converted to arabic is " << arabic << "\n";
       // this below never happens ;)
       if (arabic != number) { std::cerr << "OOOPPPPSSSS, I'm failed\n"; }
    }
}
