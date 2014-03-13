#ifndef CONFIGNODEITR_H
#define CONFIGNODEITR_H

#include <iterator>

namespace frts
{
    class ConfigNode;

    class ConfigNodeItr
    {
    public:
        typedef ConfigNodeItr self_type;
        typedef ConfigNode value_type;
        typedef ConfigNode& reference;
        typedef ConfigNode* pointer;
        typedef std::forward_iterator_tag iterator_category;
        typedef int difference_type;

        virtual self_type* operator++() = 0;
        virtual self_type* operator++(int junk) = 0;
        virtual reference operator*() = 0;
        virtual pointer operator->() = 0;
        virtual bool operator==(const self_type& rhs) = 0;
        virtual bool operator!=(const self_type& rhs) = 0;
    };
}

#endif // CONFIGNODEITR_H
