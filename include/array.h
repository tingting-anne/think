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
//ÌØ»¯
template<typename T>
class TArray< T, 0 >
{
public:
	typedef T										value_type;
	typedef value_type*								pointer;
	typedef const value_type*						const_pointer;
	typedef value_type&								reference;
	typedef const value_type&						const_reference;
	typedef value_type*								iterator;
	typedef const value_type*						const_iterator;
	typedef std::size_t								size_type;
	typedef std::ptrdiff_t							difference_type;
	typedef std::reverse_iterator<iterator>			reverse_iterator;
	typedef std::reverse_iterator<const_iterator>	const_reverse_iterator;

	// assign one value to all elements
	void assign (const T& ) {}

	void swap (TArray<T,0>& y) {}

	// iterator support
	iterator begin()
	{ return iterator(reinterpret_cast<T*>(this)); }

	const_iterator begin() const
	{ return const_iterator(reinterpret_cast<T const*>(this)); }

	iterator end()
	{ return begin(); }

	const_iterator end() const
	{ return begin(); }

	// size is constant
	static size_type size() { return 0; }

	static bool empty() { return true; }

	static size_type max_size() { return 0; }

	enum { static_size = 0 };

	// operator[]
	reference operator[](size_type i)
	{ return failed_rangecheck(); }

	const_reference operator[](size_type i) const
	{ return failed_rangecheck(); }

	// at() with range check
	reference at(size_type i)
	{ return failed_rangecheck(); }

	const_reference at(size_type i) const
	{ return failed_rangecheck(); }

	// front() and back()
	reference front()
	{ return failed_rangecheck(); }

	const_reference front() const
	{ return failed_rangecheck(); }

	reference back()
	{ return failed_rangecheck(); }

	const_reference back() const
	{ return failed_rangecheck(); }

	// direct access to data (read-only)
	const T* data() const { return 0; }

	T* data() { return 0; }

private:
	// check range (may be private because it is static)
	static reference failed_rangecheck ()
	{
		throw std::out_of_range("attempt to access element of an empty array");

		//
		// We need to return something here to keep
		// some compilers happy: however we will never
		// actually get here....
		//
		static T placeholder;
		return placeholder;
	}
};

// TArray comparisons.
template<typename T, std::size_t N>
inline bool operator==(TArray<T, N> const& x, TArray<T, N> const& y)
{ return std::equal(x.begin(), x.end(), y.begin()); }

template<typename T, std::size_t N>
inline bool operator!=(TArray<T, N> const& x, TArray<T, N> const& y)
{ return !(x == y); }

template<typename T, std::size_t N>
inline bool operator<(TArray<T, N> const& x, TArray<T, N> const& y)
{ return std::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()); }

template<typename T, std::size_t N>
inline bool operator>(TArray<T, N> const& x, TArray<T, N> const& y)
{ return y < x; }

template<typename T, std::size_t N>
inline bool operator<=(TArray<T, N> const& x, TArray<T, N> const& y)
{ return !(x > y); }

template<typename T, std::size_t N>
inline bool operator>=(TArray<T, N> const& x, TArray<T, N> const& y)
{ return !(x < y); }

// global swap()
template<typename T, std::size_t N>
inline void swap(TArray<T, N>& x, TArray<T, N>& y)
{ x.swap(y); }


}//end of THINK
#endif
