#ifndef SORT_HPP
#define SORT_HPP

#include "ComplexSortClassifier.hpp"

namespace OpenMIMO
{
    class Sorter
    {
    public:
        template <typename Iterator, typename Compare>
        static void Sort(Iterator begin, Iterator end, Compare compare, size_t size, double variation = 1.0E-6);

    private:
        template <typename Iterator, typename Compare>
        static void BubbleSort(Iterator begin, Iterator end, Compare compare, double variation);

        template <typename Iterator, typename Compare>
        static void QuickSort(Iterator begin, Iterator end, Compare compare, double variation);
    };
}

#include "Sort.inl"

#endif