template <class InputIterator1, class InputIterator2>
inline bool equal(InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2, InputIterator2 last2)
{

	for (; first1 != last1; ++first1, ++first2)
	{
		if (*first1 != *first2)
		{
			return false;
		}
	}


	return true;

}


template <class InputIterator1, class InputIterator2, class BinaryPredicate>
inline bool equal(InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2, InputIterator2 last2, BinaryPredicate binary_pred)
{

	for (; first1 != last1; ++first1, ++first2)
	{
		if (!binary_pred(*first1,*first2))
		{
			return false;
		}
	}


	return true;

}


template <class ForwardIterator, class T>
void fill(ForwardIterator first, ForwardIterator last, const T& value)
{

	for (; first != last; ++first)
	{
		*first = value;
	}


}



template <class OutputIterator, class Size, Class T>
OutputIterator fill_n(OutputIterator fist, Size n, const T& value)
{

	for (; n > 0; --n, ++first)
	{
		*fist = value;
	}

	return fist;
}


template<class ForwardIterator1, class ForwardIterator2, class T>
inline void __iter_swap(ForwardIterator1 a, ForwardIterator2 b, T*)
{

	T tmp = *a;

	*a = *b;

	*b = tmp;


}

