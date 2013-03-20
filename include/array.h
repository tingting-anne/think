#ifndef _BASE_ARRAY_H_
#define _BASE_ARRAY_H_
#include <stdexcept>
#include <algorithm>
namespace THINK{

template<class T, std::size_t N>
class array {
  public:
    T elems[N];    // fixed-size array of elements of type T

  public:
    // type definitions
    typedef T              value_type;
    typedef T*             iterator;
    typedef const T*       const_iterator;
    typedef T&             reference;
    typedef const T&       const_reference;
    typedef std::size_t    size_type;
    typedef std::ptrdiff_t difference_type;

    // iterator support
    iterator        begin()       { return elems; }
    const_iterator  begin() const { return elems; }
    
    iterator        end()       { return elems+N; }
    const_iterator  end() const { return elems+N; }

    // operator[]
    reference operator[](size_type i) 
    { 
        assert( i < N && "out of range" ); 
        return elems[i];
    }
    
    const_reference operator[](size_type i) const 
    {     
        assert( i < N && "out of range" ); 
        return elems[i]; 
    }

    // at() with range check
    reference at(size_type i) { rangecheck(i); return elems[i]; }
    const_reference at(size_type i) const { rangecheck(i); return elems[i]; }

    // front() and back()
    reference front() 
    { 
        return elems[0]; 
    }
    
    const_reference front() const 
    {
        return elems[0];
    }
    
    reference back() 
    { 
        return elems[N-1]; 
    }
    
    const_reference back() const 
    { 
        return elems[N-1]; 
    }

    // size is constant
    static size_type size() { return N; }
    static bool empty() { return false; }
    static size_type max_size() { return N; }
    enum { static_size = N };

    // swap (note: linear complexity)
    void swap (array<T,N>& y) {
        for (size_type i = 0; i < N; ++i)
            std::swap(elems[i],y.elems[i]);
    }

    // direct access to data (read-only)
    const T* data() const { return elems; }
    T* data() { return elems; }

    // use array as C array (direct read/write access to data)
    T* c_array() { return elems; }

    // assignment with type conversion
    template <typename T2>
    array<T,N>& operator= (const array<T2,N>& rhs) {
        std::copy(rhs.begin(),rhs.end(), begin());
        return *this;
    }

    // assign one value to all elements
    void assign (const T& value) { fill ( value ); }    // A synonym for fill
    void fill   (const T& value)
    {
        std::fill_n(begin(),size(),value);
    }

    // check range (may be private because it is static)
    static void rangecheck (size_type i) {
        if (i >= size()) {
            std::out_of_range e("array<>: index out of range");
        }
    }

};
}//end of THINK
#endif
