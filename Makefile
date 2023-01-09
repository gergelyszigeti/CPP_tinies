.PHONY: clean all

TINIES = determinant factorials permutation permutation_wo_repeat primes
TINIES += segfault_with_std_unique_ptr # sometimes it runs without trouble
all: $(TINIES)

$(TINIES): $(TINY=$(.TARGET))

CXX      = g++
CXXFLAGS = -Wall -std=c++17 -O3

$(TINY): $(TINY).cpp
	# note: I could have written $(CXX) $(CXXFLAGS) $< -o $@
	# but I would never do that; guess why (yes, readibility)
	$(CXX) $(CXXFLAGS) $(TINY).cpp -o $(TINY)

clean:
	rm -f $(TINIES)
