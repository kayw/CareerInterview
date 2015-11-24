#ifndef MULTIARRAY_H
#define MULTIARRAY_H

//https://github.com/search?l=C%2B%2B&q=multiarray&type=Repositories
#include <iterator>
#include <memory>
#include <array>
#include <stdexcept>
#include <vector>

namespace sequtils {
template<unsigned int ...S> struct seq {};
template<unsigned int N, unsigned int ...S> struct gens : gens<N-1, N-1, S...> {};
template<unsigned int ...S> struct gens<0, S...>{ typedef seq<S...> type; };
}

namespace sliceutils {
//slice helpers
//
template<unsigned int N, typename Ti, typename ... Types>
struct count_idx : count_idx<N+(std::is_integral<Ti>::value?1:0), Types...> {};

template<unsigned int N, typename Ti>
struct count_idx<N, Ti> { constexpr static unsigned int value=N+(std::is_integral<Ti>::value?1:0); };
}
class range : public std::vector<unsigned int> {
public:
    range(unsigned int first, unsigned int last) : std::vector<unsigned int>(last-first+1) {
        for(unsigned int i=0; i<size(); ++i)
            at(i)=i+first;
    }

    range(std::initializer_list<unsigned int> list) : std::vector<unsigned int>(list) {}

    range() : std::vector<unsigned int>() {}
};

template<typename T, unsigned int ndim>
class MultiArray
{
public:
    typedef unsigned long long int idx_t;
    typedef unsigned int smallidx_t;
    typedef typename sequtils::gens<ndim>::type idxseq;
    typedef std::array<smallidx_t,ndim> multiIdx_t;
private:
    std::shared_ptr<idx_t> strides;
    idx_t arr_size;
    std::shared_ptr<T> data;
    multiIdx_t msize;

    inline idx_t index(smallidx_t, smallidx_t i) const {
        return i;
    }

    template<typename ... Types>
    inline idx_t index(smallidx_t stridesidx, smallidx_t i, Types... rest) const {
        return i*strides.get()[stridesidx]+index(stridesidx+1,rest...);
    }

    inline idx_t fill_strides(smallidx_t stridesidx,smallidx_t i) const {
        return strides.get()[stridesidx]=i;
    }

    template<typename ... Types>
    inline idx_t fill_strides(smallidx_t stridesidx, smallidx_t i, Types... rest) const {
        return strides.get()[stridesidx]=fill_strides(stridesidx+1,rest...)*i;
    }

    inline const T& operator[](idx_t idx) const {
        check_size(idx);
        return data.get()[idx];
    }

    inline T& operator[](idx_t idx) {
        check_size(idx);
        if(!data.unique()) {
            std::shared_ptr<T> other(new T[arr_size],std::default_delete<T[]>());
            std::copy(data.get(),data.get()+arr_size,other.get());
            data.swap(other);
        }
        return data.get()[idx];
    }

    inline void check_valid() const {
        if(!valid())
            throw std::logic_error("Using invalid MultiArray");
    }

    inline void check_size(idx_t idx) const {
        if(idx>=arr_size)
            throw std::out_of_range("MultiArray index out of range");
    }

    //array-based helpers
    template<typename A, smallidx_t ... I>
    inline const T& get_impl(const A& arr, sequtils::seq<I...>) const {
        return get(arr[I]...);
    }

    template<typename A, smallidx_t ... I>
    inline T& set_impl(const A& arr, sequtils::seq<I...>) {
        return set(arr[I]...);
    }
    // TODO try clang3.5+
    //slice helpers

    template<smallidx_t slice_ndim, typename ... Types>
    inline void slice_size(typename MultiArray<T,slice_ndim>::multiIdx_t &res, smallidx_t i, smallidx_t j, range& first, Types&...rest) {
        if(first.size()==0)
            first=range(0,size()[j]-1);
        res[i]=first.size();
        slice_size<slice_ndim>(res,i+1,j+1,rest...);
    }

    template<smallidx_t slice_ndim, typename ... Types>
    inline void slice_size(typename MultiArray<T,slice_ndim>::multiIdx_t &res, smallidx_t i, smallidx_t j, smallidx_t, Types&...rest) {
        slice_size<slice_ndim>(res,i,j+1,rest...);
    }

    template<smallidx_t slice_ndim, typename ... Types>
    inline void slice_size(typename MultiArray<T,slice_ndim>::multiIdx_t &, smallidx_t, smallidx_t) {}

    template<int N2,typename ... Types>
    inline void fill(MultiArray<T,N2> &res, typename MultiArray<T,N2>::multiIdx_t& idx, unsigned int idxn, multiIdx_t& idx2, unsigned int idxn2, range& first, Types&...rest) {
        for(idx[idxn]=0; idx[idxn]<res.size()[idxn]; ++idx[idxn]) {
            idx2[idxn2] = first[idx[idxn]];
            fill<N2>(res,idx,idxn+1,idx2,idxn2+1,rest...);
        }
    }

    template<int N2,typename ... Types>
    inline void fill(MultiArray<T,N2> &res, typename MultiArray<T,N2>::multiIdx_t& idx, unsigned int idxn, multiIdx_t& idx2, unsigned int idxn2, unsigned int first, Types&...rest) {
        idx2[idxn2] = first;
        fill<N2>(res,idx,idxn,idx2,idxn2+1,rest...);
    }

    template<int N2>
    inline void fill(MultiArray<T,N2> &res, typename MultiArray<T,N2>::multiIdx_t& idx, unsigned int, multiIdx_t& idx2, unsigned int) {
        res(idx)=(*this)(idx2);
    }

    template<typename R, typename A, smallidx_t ... I>
    inline R slice_impl(const A& arr, sequtils::seq<I...>) {
        return slice(std::get<I>(arr)...);
    }

public:
    MultiArray() :
        strides(nullptr),
        arr_size(0),
        data(nullptr),
        msize{{0}}
    {

    }

    template<typename ... Types>
    MultiArray(smallidx_t nfirst, Types... counts) :
        strides(new idx_t[ndim-1],std::default_delete<idx_t[]>()),
        arr_size(nfirst*fill_strides(0,counts...)),
        data(new T[arr_size],std::default_delete<T[]>()),
        msize{{nfirst, counts...}}
	//http://stackoverflow.com/questions/20176176/function-taking-variadic-number-of-initializer-lists-with-different-types
	//http://stackoverflow.com/questions/9146534/stdarray-initializer-list-initialization-in-initialization-list
	//http://stackoverflow.com/questions/8298214/size-of-built-in-multidimensional-array-using-variadic-template-function
	//http://stackoverflow.com/questions/10364874/create-stdarray-from-variadic-template
    {
        static_assert(ndim==sizeof...(counts)+1,"Invalid number of arguments in MultiArray constructor");
    }

    MultiArray(smallidx_t nfirst) :
        strides(nullptr),
        arr_size(nfirst),
        data(new T[arr_size],std::default_delete<T[]>()),
        msize{nfirst}
    {
        static_assert(ndim==1,"Invalid number of arguments in MultiArray constructor");
    }

    MultiArray(const MultiArray &) = default;

    MultiArray(MultiArray &&other) :
        MultiArray(other)
    {
        other.clear();
    }

    MultiArray & operator=(const MultiArray &) = default;

    MultiArray & operator=(MultiArray &&other) {
        *this = other;
        other.clear();
        return *this;
    }

    //arg-based
    template<typename ... Types>
    inline const T& get(Types... indexes) const {
        static_assert(sizeof...(indexes)==ndim,"Invalid number of arguments in MultiArray::get(...)");
        check_valid();
        return (*this)[index(0,indexes...)];
    }

    template<typename ... Types>
    inline T& set(Types... indexes) {
        static_assert(sizeof...(indexes)==ndim,"Invalid number of arguments in MultiArray::set(...)");
        check_valid();
        return (*this)[index(0,indexes...)];
    }

    template<typename ... Types>
    inline const T& operator()(Types... indexes) const {
        return get(indexes...);
    }

    template<typename ... Types>
    inline T& operator()(Types... indexes) {
        return set(indexes...);
    }

    //array-based

    inline const T& get(const multiIdx_t& arr) const {
        return get_impl(arr,idxseq());
    }

    inline T& set(const multiIdx_t& arr) {
        return set_impl(arr,idxseq());
    }

    inline const T& operator()(const multiIdx_t &arr) const {
        return get(arr);
    }

    inline T& operator()(const multiIdx_t &arr) {
        return set(arr);
    }

    //utility

    inline multiIdx_t size() const {
        return msize;
    }

    inline bool valid() const {
        return (strides||ndim==1) && data && arr_size;
    }

    inline void clear() {
        strides.reset();
        data.reset();
        arr_size=0;
        msize={0};
    }

    template<typename ... Types>
    MultiArray<T,ndim - sliceutils::count_idx<0,Types...>::value> slice(Types... args);

    template<typename ... Types>
    MultiArray<T,ndim - sliceutils::count_idx<0,Types...>::value> slice(std::tuple<Types...> arg) {
        return slice_impl<
                MultiArray<T,ndim - sliceutils::count_idx<0,Types...>::value>
                >(arg,typename sequtils::gens<sizeof...(Types)>::type());
    }

    //iterators

    class iterator : public std::iterator<std::forward_iterator_tag, T>
    {
    protected:
        friend class MultiArray;
        MultiArray* const arr;
        idx_t idx;
        iterator(MultiArray* arr, idx_t idx) : arr(arr), idx(idx) {}
    public:
        iterator& operator++() {++idx; return *this;}
        iterator operator++(int) {iterator tmp(*this); operator++(); return tmp;}
        bool operator==(const iterator& rhs) const {return !(*this!=rhs);}
        bool operator!=(const iterator& rhs) const {return arr!=rhs.arr || idx!=rhs.idx;}
        T& operator*() {arr->check_valid(); return (*arr)[idx];}
        T* operator->() {return &(**this);}

        MultiArray* parent() { return arr; }
        const multiIdx_t index() const {
            arr->check_valid();
            std::array<smallidx_t,ndim> i;
            auto t=idx;
            for(smallidx_t j=0; j<ndim-1; ++j) {
                i[j]=t/arr->strides.get()[j];
                t=t%arr->strides.get()[j];
            }
            i[ndim-1]=t;
            return i;
        }
    };

    class const_iterator : public std::iterator<std::forward_iterator_tag, T>
    {
    protected:
        friend class MultiArray;
        const MultiArray* arr;
        idx_t idx;
        const_iterator(const MultiArray* arr, idx_t idx) : arr(arr), idx(idx) {}
    public:
        const_iterator& operator++() {++idx; return *this;}
        const_iterator operator++(int) {const_iterator tmp(*this); operator++(); return tmp;}
        bool operator==(const const_iterator& rhs) const {return !(*this!=rhs);}
        bool operator!=(const const_iterator& rhs) const {return arr!=rhs.arr || idx!=rhs.idx;}
        const T& operator*() const {arr->check_valid(); return (*arr)[idx];}
        const T* operator->() const {return &(**this);}

        const MultiArray* parent() const { return arr; }
        const multiIdx_t index() const {
            arr->check_valid();
            std::array<smallidx_t,ndim> i;
            auto t=idx;
            for(smallidx_t j=0; j<ndim-1; ++j) {
                i[j]=t/arr->strides.get()[j];
                t=t%arr->strides.get()[j];
            }
            i[ndim-1]=t;
            return i;
        }
    };

    iterator begin() {
        return iterator(this,0);
    }

    iterator end() {
        return iterator(this,arr_size);
    }

    template<typename ... Types>
    iterator make_iterator(Types... indices) {
        return iterator(this, index(0,indices...));
    }

    const_iterator const_begin() const {
        return const_iterator(this,0);
    }

    const_iterator const_end() const {
        return const_iterator(this,arr_size);
    }

    template<typename ... Types>
    const_iterator make_const_iterator(Types... indices) const {
        return const_iterator(this, index(0,indices...));
    }
};

namespace typeutils {
template <template <typename> class pred, typename...> struct query_all;
template <template <typename> class pred> struct query_all<pred>
    : std::integral_constant<bool, true> {};
template <template <typename> class pred, typename T, typename... Args> struct query_all<pred, T, Args...>
    : std::integral_constant<bool, pred<T>::value && query_all<pred, Args...>::value> {};
}

template<typename T, typename ... Types,
         typename = typename std::enable_if<typeutils::query_all<std::is_integral,Types...>::value>::type>
auto make_array(Types... counts) -> MultiArray<T,sizeof...(Types)> {
    return MultiArray<T,sizeof...(Types)>(counts...);
}

template<typename T, typename A, unsigned int ... I>
auto make_array_helper(A arr, sequtils::seq<I...>) -> MultiArray<T,sizeof...(I)> {
    return MultiArray<T,arr.size()>(arr[I]...);
}

template<typename T, std::size_t N>
auto make_array(std::array<unsigned int,N> size) -> MultiArray<T,N> {
    return make_array_helper<T>(size,typename sequtils::gens<N>::type());
}

template<typename T, unsigned int ndim>
template<typename ... Types>
MultiArray<T,ndim - sliceutils::count_idx<0,Types...>::value> MultiArray<T,ndim>::slice(Types... args) {
    constexpr auto N = sliceutils::count_idx<0,Types...>::value;
    static_assert(N<ndim,"Slice of dimension<=0. Probably that's not what you want!");
    std::array<unsigned int,ndim-N> size;
    slice_size<ndim-N>(size,0,0,args...);
    MultiArray<T,ndim-N> result = make_array<T>(size);
    auto idx1=typename MultiArray<T,ndim-N>::multiIdx_t{0};
    auto idx2=multiIdx_t{0};
    fill<ndim-N>(result,idx1,0,idx2,0,args...);
    return result;
}

#endif // MULTIARRAY_H
