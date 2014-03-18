#ifndef ITERATORWRAPPER_H
#define ITERATORWRAPPER_H

#include <iterator>

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

        IteratorWrapper(IteratorImpl *iterator) : iterator(iterator) {}

        self_type operator++() { self_type i = *this; (*iterator)++; return i; }
        self_type operator++(int junk) { (*iterator)++; return *this; }
        reference operator*() { return *(*iterator); }
        pointer operator->() { return &(*(*iterator)); }
        bool operator==(const self_type& rhs) { return *iterator == *rhs.iterator; }
        bool operator!=(const self_type& rhs) { return *iterator != *rhs.iterator; }

    private:
        IteratorImpl *iterator;
    };
}

#endif // ITERATORWRAPPER_H
