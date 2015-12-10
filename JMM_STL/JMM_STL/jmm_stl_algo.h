#ifndef __JMM_STL_ALGO
#define __JMM_STL_ALGO

#include "jmm_stl_iterator.h"

namespace JMM_STL
{
	template<class ForwardIterator, class T, class Distance>
	ForwardIterator __lower_bound(ForwardIterator first, ForwardIterator last,
		const T& value, Distance*, forward_iterator_tag)
	{
		Distance len = 0;
		distance(first, last, len);
		Distance half;
		ForwardIterator middle;
		while (len >0)
		{
			half = len >> 1;
			middle = first;
			advance(middle, half);
			if (*middle < value)
			{
				first = middle;
				++first;
				len = len - half - 1;
			}
			else
			{
				len = half;
			}
		}

		return first;
	}

	template<class RandomIterator, class T, class Distance>
	RandomIterator __lower_bound(RandomIterator first, RandomIterator last,
		const T& value, Distance*, random_access_iterator_tag)
	{
		Distance len = 0;
		distance(first, last, len);
		Distance half;
		RandomIterator middle;
		while (len >0)
		{
			half = len >> 1;
			middle = first + half;
			if (*middle < value)
			{
				first = middle + 1;
				len = len - half - 1;
			}
			else
			{
				len = half;
			}
		}

		return first;
	}



	template<class ForwardIterator, class T, class Compare , class Distance>
	ForwardIterator __lower_bound(ForwardIterator first, ForwardIterator last,
		const T& value, Compare comp, Distance*, forward_iterator_tag)
	{
		Distance len = 0;
		distance(first, last, len);
		Distance half;
		ForwardIterator middle;
		while (len >0)
		{
			half = len >> 1;
			middle = first;
			advance(middle, half);
			if (comp(*middle , value))
			{
				first = middle;
				++first;
				len = len - half - 1;
			}
			else
			{
				len = half;
			}
		}

		return first;
	}

	template<class RandomIterator, class T, class Compare, class Distance>
	RandomIterator __lower_bound(RandomIterator first, RandomIterator last,
		const T& value, Compare comp, Distance*, random_access_iterator_tag)
	{
		Distance len = 0;
		distance(first, last, len);
		Distance half;
		middle;
		while (len >0)
		{
			half = len >> 1;
			middle = first + half;
			if (comp(*middle , value))
			{
				first = middle + 1;
				len = len - half - 1;
			}
			else
			{
				len = half;
			}
		}

		return first;
	}

	template <class ForwardIterator, class T>
	inline ForwardIterator lower_bound(ForwardIterator first, ForwardIterator last,
		const T& value)
	{
		return __lower_bound(first, last, value, distance_type(first), iterator_category(first));
	}

	template <class ForwardIterator, class T, class Compare>
	inline ForwardIterator lower_bound(ForwardIterator first, ForwardIterator last,
		const T& value, Compare comp)
	{
		return __lower_bound(first, last, value, comp, distance_type(first),
			iterator_category(first));
	}


	template<class ForwardIterator, class T, class Distance>
	ForwardIterator __upper_bound(ForwardIterator first, ForwardIterator last,
		const T& value, Distance*, forward_iterator_tag)
	{
		Distance len = 0;
		distance(first, last, len);
		Distance half;
		ForwardIterator middle;
		while (len >0)
		{
			half = len >> 1;
			middle = first;
			advance(middle, half);
			if (value<*middle)
			{

				len = half;
			}
			else
			{

				first = middle;
				++first;
				len = len - half - 1;
			}
		}

		return first;
	}

	template<class RandomIterator, class T, class Distance>
	RandomIterator __upper_bound(RandomIterator first, RandomIterator last,
		const T& value, Distance*, random_access_iterator_tag)
	{
		Distance len = 0;
		distance(first, last, len);
		Distance half;
		middle;
		while (len >0)
		{
			half = len >> 1;
			middle = first + half;
			if (value<*middle)
			{

				len = half;
			}
			else
			{

				first = middle + 1;
				len = len - half - 1;
			}
		}

		return first;
	}


	template<class ForwardIterator, class T, class Compare, class Distance>
	ForwardIterator __upper_bound(ForwardIterator first, ForwardIterator last,
		const T& value, Compare comp, Distance*, forward_iterator_tag)
	{
		Distance len = 0;
		distance(first, last, len);
		Distance half;
		ForwardIterator middle;
		while (len >0)
		{
			half = len >> 1;
			middle = first;
			advance(middle, half);
			if (comp(value, *middle))
			{

				len = half;
			}
			else
			{

				first = middle;
				++first;
				len = len - half - 1;
			}
		}

		return first;
	}

	template<class RandomIterator, class T, class Compare, class Distance>
	RandomIterator __upper_bound(RandomIterator first, RandomIterator last,
		const T& value, Compare comp, Distance*, random_access_iterator_tag)
	{
		Distance len = 0;
		distance(first, last, len);
		Distance half;
		middle;
		while (len >0)
		{
			half = len >> 1;
			middle = first + half;
			if (comp(value, *middle))
			{

				len = half;
			}
			else
			{

				first = middle + 1;
				len = len - half - 1;
			}
		}

		return first;
	}

	template <class ForwardIterator, class T, class Compare>
	inline ForwardIterator upper_bound(ForwardIterator first, ForwardIterator last,
		const T& value, Compare comp)
	{
		return __upper_bound(first, last, value, comp, distance_type(first),
			iterator_category(first));
	}


	template <class ForwardIterator, class T>
	inline ForwardIterator upper_bound(ForwardIterator first, ForwardIterator last,
		const T& value)
	{
		return __upper_bound(first, last, value, distance_type(first),
			iterator_category(first));
	}
}


#endif