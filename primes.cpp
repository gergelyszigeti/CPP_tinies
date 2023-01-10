#include <limits>
#include <string>
#include <stdio.h>

bool isPrime(unsigned int value)
{
  // see wikipedia, primality test
  //if (value == 2 || value == 3) return true;
  if ((value % 2) == 0 || (value % 3) == 0) { return false; }
  // up to 25 these two ifs (here one if) above work well

  // from 25, we need a for loop, up to the square root of the value
  for (unsigned int i = 5; i * i <= value; i += 6) {
    // i and (i + 2) are values that are not divisible by 2 and 3
    // (mostly prime numbers or divisible by prime numbers)
    if (value % i == 0 || value % (i + 2) == 0) { return false; }
  }
  return true;
}

int main(int argc, char* argv[])
{
    // what will be the ceiling of our prime numbers, can be given in command line
    unsigned int print_to = 1e6;  // default value is 1 million
    if (argc == 2) {
        long long print_to_ll = atoll(argv[1]);
        if ( print_to_ll < 3 || 4e9 < print_to_ll ) {
            fprintf(stderr, "error: given number must be greater than 2 and at most 4 billion ");
            fprintf(stderr, "(4 with 9 trailing zeros)\n");
            exit(1);
        }
        print_to = static_cast<int>(print_to_ll); // nothing will be lost
    }

    // init progress "bar"
    unsigned int progress_step = print_to / 100;
    unsigned int progress = 0;

    // let's always start prime numbers with 2 and 3
    printf("2\n3\n");

    // we simple take 6k-1 and 6k+1 values for k > 0, up to the given ceiling
    // not all of them are prime, but all prime numbers can be expressed like that
    for (unsigned int i = 6; i < print_to; i += 6) {
        if (isPrime(i-1)) { printf("%u\n", i - 1); }
        if (isPrime(i+1)) { printf("%u\n", i + 1); }

        // progress "bar" if needed
        if (print_to > 3e6 && i > progress) {
            progress += progress_step;
            fprintf(stderr, "\rProgress: %lu%%", static_cast<unsigned long int>(i)*100/print_to);
        }
    }

    fprintf(stderr, "\rDone         \n");
}
