#ifndef __PUSHPUSH_UTIL_HPP__
#define __PUSHPUSH_UTIL_HPP__

namespace pushpush {

class ZPoint {
  public:
    int x, y;
    ZPoint() : x(0), y(0) { }
    ZPoint(int n1, int n2) : x(n1), y(n2) { }
    void set(int n1, int n2) {
        x = n1, y = n2;
    }
};

class ZSize {
  public:
    size_t width, height;
    ZSize() : width(0), height(0) { }
    ZSize(size_t n1, size_t n2) : width(n1), height(n2) { }
};

// template<class InputIterator, class Function> Function for_each(InputIterator first, InputIterator last, Function fn) {
//     while (first!=last) {
//         fn (*first);
//         ++first;
//     }
//     return fn;
// }

template<class t> struct Deletor {
  void operator() (t* p) { delete p; }
};

// Deletor<ZPoint> deletorPoint;
// Deletor<ZSize> deletorSize;

};

#endif
