template <typename Iterator, typename Compare>
inline void OpenMIMO::Sorter::BubbleSort(Iterator begin, Iterator end, Compare compare, double variation)
{
    for (Iterator i = begin; i != end; ++i)
        for (Iterator j = begin; j < i; ++j)
            if (compare(*i, *j, variation))
                std::iter_swap(i, j);
}

template <typename Iterator, typename Compare>
inline void OpenMIMO::Sorter::QuickSort(Iterator begin, Iterator end, Compare compare, double variation)
{
    if (end <= begin) return;
    Iterator pivot = begin, middle = begin + 1;
    for (Iterator i = begin + 1; i < end; ++i) {
        if (compare(*i, *pivot, variation)) {
            std::iter_swap(i, middle);
            ++middle;
        }
    }
    std::iter_swap(begin, middle - 1);
    QuickSort(begin, middle - 1, compare, variation);
    QuickSort(middle, end, compare, variation);
}

template <typename Iterator, typename Compare>
inline void OpenMIMO::Sorter::Sort(Iterator begin, Iterator end, Compare compare, size_t size, double variation)
{
    if (size <= 5)
        BubbleSort(begin, end, compare, variation);
    else
        QuickSort(begin, end, compare, variation);
}