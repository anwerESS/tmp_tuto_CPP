// 0. std::deque is an indexed sequence container.
// 1. It allows fast insertion at both beginning and end.
// 2. Unlike vector elements of deque are not stored contiguous.
// 3. it uses individual allocated fixed size array, with additional bookkeeping, meaning index based access to deque
//    must perform two pointer dereference, but in vector we get in one dereference.
// 4. The storage of a deque is automatically expanded and contracted as needed.
// 5. Expansion of deque is cheaper than expansion of vector.
// 6. A deque holding just one element has to allocate its full internal array (e.g. 8 times the object size on
//    64-bit libstdc++; 16 times the object size or 4096 bytes, whichever is larger, on 64-bit libc++).

// TIME COMPLEXITY:
// Random access - constant O(1)
// Insertion or removal of elements at the end or beginning - constant O(1)
// Insertion or removal of elements - linear O(n)

#include <iostream>
#include <deque>


int main(int argc, char const *argv[])
{
    std::deque<int> deq{2, 3, 4};

    deq.push_back(5);
    deq.push_front(1);

    std::cout << "BACK : " << deq.back() << '\n'; // BACK : 5
    std::cout << "FRONT : " << deq.front() << '\n'; // FRONT : 1

    deq.pop_back();
    deq.pop_front();

    for (auto el : deq) std::cout << el << ' '; // 2 3 4
    std::cout << '\n';

    return 0;
}
