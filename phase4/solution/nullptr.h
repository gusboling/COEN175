/* Ah, the beauty and the ugliness of C++ all rolled into one.  Most of
   this file is taken from various articles about C++'s lack of a null
   pointer constant.  In C++, NULL is simply 0, which leads to confusion
   when overloading on a pointer and a numerical type:

       void f(int x);
       void f(int *x);

   Which function is called on f(NULL)?  Well, since f(NULL) is really just
   f(0), it's ambiguous.  A good compiler will report the problem.  A bad
   compiler will just blindly call the first function.  Surprise!

   The new C++ standard introduces a new constant nullptr.  Until it's
   fully supported, this class comes as close as you can get to mimicking
   it.  The final four functions don't seem to be needed under all versions
   of GCC, but they seem to work regardless. */

# ifndef NULLPTR_H
# define NULLPTR_H
# include <cstddef>
# if (__cplusplus == 1)

const class nullptr_t {
    void operator &() const;
public:
    template<class T> operator T*() const { return 0; }
    template<class C, class T> operator T C::*() const { return 0; }
} nullptr = {};

template<class T> bool operator ==(nullptr_t lhs, T *rhs) { return rhs == 0; }
template<class T> bool operator ==(T *lhs, nullptr_t rhs) { return lhs == 0; }
template<class T> bool operator !=(nullptr_t lhs, T *rhs) { return rhs != 0; }
template<class T> bool operator !=(T *lhs, nullptr_t rhs) { return lhs != 0; }

# endif
# endif /* NULLPTR_H */
