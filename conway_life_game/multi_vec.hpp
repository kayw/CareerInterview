#ifndef MULTI_VEC_HPP_61174810_0908_4CC0_93BD_9B95C71D9989
#define MULTI_VEC_HPP_61174810_0908_4CC0_93BD_9B95C71D9989

//http://stackoverflow.com/questions/20846684/c11-dynamic-multidimensional-array-of-any-type-using-vector-initilizer-list
#include<memory>
#include<algorithm>
template <class T>
class multi_vec
{
public:
    using param=std::vector<size_t>;

    explicit multi_vec(const param& dimensions)
        : dim{dimensions}, prod {1}
    {
        std::for_each(dim.begin(), dim.end(), [this] (std::size_t val)
        {
            mult.emplace_back(prod);
            prod *= val;
        } );
        ptr.reset(new T[prod]);
    }
    std::size_t capacity() const { return prod; }

    // undefined if elements in lookup != elemenets in dim
    // undefined if any element in lookup
        // is greater than or equal to corresponding dim element
    T& operator[](const param& lookup)
    {
        return ptr[get_offset(lookup)];
    }
    const T operator[](const param& lookup) const
    {
        return ptr[get_offset(lookup)];
    }
private:
    std::size_t get_offset(const param& lookup) const
    {
        std::size_t offset=0;
        auto mit=mult.begin();
        std::for_each(lookup.begin(), lookup.end(), [&offset, &mit] (std::size_t val)
        {
            offset+=*mit * val;
           ++mit;
        } );
        return offset;
    }
    param dim;
    param mult;
    std::size_t prod;
    std::unique_ptr<T[]> ptr;
};

#endif /* MULTI_VEC_HPP_61174810_0908_4CC0_93BD_9B95C71D9989 */
//http://www.cplusplus.com/forum/articles/7459/
//http://www.wilmott.com/messageview.cfm?catid=10&threadid=86999
