#ifndef __PUSHPUSH_UTIL_HPP__
#define __PUSHPUSH_UTIL_HPP__

namespace pushpush {

class Point {
  public:
    int x, y;
    Point() : x(0), y(0) { }
    Point(int n1, int n2) : x(n1), y(n2) { }
};

class Size {
  public:
    size_t width, height;
    Size() : width(0), height(0) { }
    Size(size_t n1, size_t n2) : width(n1), height(n2) { }
};

template<class InputIterator, class Function> Function for_each(InputIterator first, InputIterator last, Function fn) {
    while (first!=last) {
        fn (*first);
        ++first;
    }
    return fn;
}

template<class t> struct Deletor {
  void operator() (t* p) { delete p; }
};

Deletor<Point> deletorPoint;
Deletor<Size> deletorSize;

};

#endif
