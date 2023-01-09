#include <iostream>
#include <vector>
#include <set>

static int counter = 0;

template<typename T>
T det(std::vector< std::vector< T > >& m,
              std::set<int>& xs, int y = 0) {
  if (xs.empty()) { return 1; }
  T res = 0, s = 1;
  for (int x: xs) {
    auto xs_next = xs; xs_next.erase(x);
    counter++; // counter to see, how time complex determinat calculation is
    res += s * m[y][x] * det(m, xs_next, y + 1); // recursive formula
    s *= -1;
  }
  return res;
}

template<typename T>
T determinant(std::vector< std::vector< T > > m) {
  std::set<int> xs;
  for (int x = 0; x < m.size(); x++) { xs.emplace(x); }
  return det(m, xs);
}

int main()
{
    using matrix_t = long long; // this will be the type T above in func templates
    const int N = 8; // this is the size of the quad matrix

    auto m = std::vector< std::vector< matrix_t >>(N);
    auto row = std::vector< matrix_t >(N);

    for (int y = 0; y < N; ++y) {
        for (int x = 0; x < N; ++x) {
            row[x] = (rand() & 255) - 128;
        }
        m[y] = row;
    }

// you can compile this program with -DSHOW_MATRIX
#ifdef SHOW_MATRIX
    for (int y = 0; y < N; ++y) {
        for (int x = 0; x < N; ++x) {
            std::cout << m[y][x] << " ";
        }
        std::cout << "\n";
    }
#endif
    std::cout << "Matrix determinant: " << determinant(m) << "\n";
    std::cout << "Amount of operations: " << counter << "\n";
}
