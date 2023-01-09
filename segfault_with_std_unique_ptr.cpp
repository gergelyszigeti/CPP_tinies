#include <memory>

int main()
{
    // This is a demonstration that even smart pointers must be
    // used and initialized properly. Otherwise, segfault can occur.

    int obj = 666;
    auto badptr = std::unique_ptr<int>(&obj); // ouch!

    // Here, the root of the evil was not the number 666.
    // It was the raw pointer to it. Yes, &obj is a raw pointer.

    // Bad design because: badptr thinks badptr is the only reference
    // to the number 666. However, it is not true, obj is also a
    // reference to it.

    // Here below, the closing curly bracket is where the
    // "fun" begins: obj is an object on the stack, it must be
    // destroyed when we leave its scope. However, badptr is also
    // an object on the stack, it must be also destroyed.
    // badptr's destructor is called, which must destroy obj,
    // as "badptr was the only reference to it" (unfortunatelly not).

    // So, obj is tried to be destroyed twice.
}

// end note: if you really want a unique_ptr to an int number 666:
// auto goodptr = std::unique_ptr<int>(new int{666}); // C++11
// IMPORTANT: no 'delete' needed for this 'new'! (after 'delete', you can
// only enter 'goodptr' anyway, which is not a pointer in reality)
// From C++14, it is much clearer and simpler:
// auto goodptr = std::make_unique<int>(666);  // C++14 and above
// Bonus with make_unique<int>: initializon with raw pointer won't compile
