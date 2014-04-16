#ifndef FRTS_CONFIGNODEITR_H
#define FRTS_CONFIGNODEITR_H

#include "ConfigNodePtr.h"

#include <iterator>


namespace frts
{
    /**
     * @brief Interface of ConfigNode iterators.
     */
    class ConfigNodeItr
    {
    public:
        typedef ConfigNodeItr self_type;
        typedef ConfigNodePtr value_type;
        typedef ConfigNodePtr reference;
        typedef ConfigNodePtr pointer;
        typedef std::forward_iterator_tag iterator_category;
        typedef int difference_type;

        virtual ~ConfigNodeItr() {}

        virtual self_type* operator++() = 0;
        virtual self_type* operator++(int) = 0;
        virtual reference operator*() = 0;
        virtual pointer operator->() = 0;
        virtual bool operator==(const self_type& rhs) = 0;
        virtual bool operator!=(const self_type& rhs) = 0;
    };
}

#endif // FRTS_CONFIGNODEITR_H
