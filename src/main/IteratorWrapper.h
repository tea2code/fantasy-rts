#ifndef FRTS_ITERATORWRAPPER_H
#define FRTS_ITERATORWRAPPER_H

#include <iterator>
#include <memory>


namespace frts
{
    /**
     * @brief Wrapper around a iterator implementation. Hides the specifig
     * iterator implementation and can be used with interfaces.
     */
    template<class IteratorImpl, class Value, class Reference, class Pointer>
    class IteratorWrapper
    {
    public:
        typedef IteratorWrapper self_type;
        typedef Value value_type;
        typedef Reference reference;
        typedef Pointer pointer;
        typedef std::forward_iterator_tag iterator_category;
        typedef int difference_type;

        explicit IteratorWrapper(IteratorImpl *iterator) : iterator(std::shared_ptr<IteratorImpl>(iterator)) {}

        self_type& operator++() { ++(*iterator); return *this; }
        self_type operator++(int) { self_type i = *this; (*iterator)++; return i; }
        reference operator*() { return *(*iterator); }
        pointer operator->() { return &(*(*iterator)); }
        bool operator==(const self_type& rhs) { return *iterator == *rhs.iterator; }
        bool operator!=(const self_type& rhs) { return *iterator != *rhs.iterator; }

    private:
        std::shared_ptr<IteratorImpl> iterator;
    };
}

#endif // FRTS_ITERATORWRAPPER_H
