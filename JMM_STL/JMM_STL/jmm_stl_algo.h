#ifndef __JMM_STL_ALGO
#define __JMM_STL_ALGO

#include "jmm_stl_iterator.h"
#include "jmm_stl_heap.h"
#include <stddef.h>


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
		while (len > 0)
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
		while (len > 0)
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



	template<class ForwardIterator, class T, class Compare, class Distance>
	ForwardIterator __lower_bound(ForwardIterator first, ForwardIterator last,
		const T& value, Compare comp, Distance*, forward_iterator_tag)
	{
		Distance len = 0;
		distance(first, last, len);
		Distance half;
		ForwardIterator middle;
		while (len > 0)
		{
			half = len >> 1;
			middle = first;
			advance(middle, half);
			if (comp(*middle, value))
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
		while (len > 0)
		{
			half = len >> 1;
			middle = first + half;
			if (comp(*middle, value))
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
		while (len > 0)
		{
			half = len >> 1;
			middle = first;
			advance(middle, half);
			if (value < *middle)
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
		RandomIterator middle;
		while (len > 0)
		{
			half = len >> 1;
			middle = first + half;
			if (value < *middle)
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
		while (len > 0)
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
		while (len > 0)
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


	template<class InputIterator1, class InputIterator2, class OutputIterator>
	OutputIterator set_union(InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2, OutputIterator result)
	{
		while (first1 != last1&&first2 != last2)
		{
			if (*first1 < *first2)
			{
				*result = *first1;
				++first1;
			}
			else if (*first2 < *first1)
			{
				*result = *first2;
				++first2;
			}
			else
			{
				*result = *first1;
				++first1;
				++first22;
			}
			++result;

		}

		return copy(first2, last2, copy(first1, last1, result));
	}


	template<class InputIterator1, class InputIterator2, class OutputIterator, class BinaryPredicate>
	OutputIterator set_union(InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2, OutputIterator result, BinaryPredicate binary_pred)
	{
		while (first1 != last1&&first2 != last2)
		{
			if (binary_pred(*first1, *first2))
			{
				*result = *first1;
				++first1;
			}
			else if (binary_pred(*first2, *first1))
			{
				*result = *first2;
				++first2;
			}
			else
			{
				*result = *first1;
				++first1;
				++first22;
			}
			++result;

		}

		return copy(first2, last2, copy(first1, last1, result));
	}


	template< class InputIterator1, class InputIterator2, class OutputIterator>
	OutputIterator set_intersection(InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2, OutputIterator result)
	{
		while (first1 != last1&&first2 != last2)
		{
			if (*first1 < *first2)
			{
				++first1;
			}

			else if (*first2 < *first1)
			{
				++first2;
			}
			else
			{
				*result = *first1;
				++first1;
				++first2;
			}

		}

		return result;
	}

	template< class InputIterator1, class InputIterator2, class OutputIterator, class BinaryPredicate>
	OutputIterator set_intersection(InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2, OutputIterator result, BinaryPredicate binary_pred)
	{
		while (first1 != last1&&first2 != last2)
		{
			if (binary_pred(*first1, *first2))
			{
				++first1;
			}

			else if (binary_pred(*first2, *first1))
			{
				++first2;
			}
			else
			{
				*result = *first1;
				++first1;
				++first2;
			}

		}

		return result;
	}


	template<class InputIterator1, class InputIterator2, class OutputIterator>
	OutputIterator set_difference(InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2, OutputIterator result)
	{
		while (first1 != last1&&first2 != last2)
		{
			if (*first1 < *first2)
			{
				*(result++) = *(first1++);
			}
			else if (*first2 < *first1)
			{
				++first2;
			}
			else
			{
				++first1;
				++first2;

			}

		}

		return copy(first1, last1, result);
	}


	template<class InputIterator1, class InputIterator2, class OutputIterator, class BinaryPredicate>
	OutputIterator set_difference(InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2, OutputIterator result, BinaryPredicate binary_pred)
	{
		while (first1 != last1&&first2 != last2)
		{
			if (binary_pred(*first1, *first2))
			{
				*(result++) = *(first1++);
			}
			else if (binary_pred(*first2, *first1))
			{
				++first2;
			}
			else
			{
				++first1;
				++first2;

			}

		}

		return copy(first1, last1, result);
	}


	template<class InputIterator1, class InputIterator2, class OutputIterator>
	OutputIterator set_symmetric_difference(InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2, OutputIterator result)
	{
		while (first1 != last1&&first2 != last2)
		{
			if (*first1 < *first2)
			{
				*(result++) = *(first1++);
			}
			else if (*first2 < *first1)
			{
				*(result++) = *(first2++);
			}
			else
			{
				++first1;
				++first2;

			}

		}

		return copy(first1, last1, result);
	}


	template<class InputIterator1, class InputIterator2, class OutputIterator, class BinaryPredicate>
	OutputIterator set_symmetric_difference(InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2, OutputIterator result, BinaryPredicate binary_pred)
	{
		while (first1 != last1&&first2 != last2)
		{
			if (binary_pred(*first1, *first2))
			{
				*(result++) = *(first1++);
			}
			else if (binary_pred(*first2, *first1))
			{
				*(result++) = *(first2++);
			}
			else
			{
				++first1;
				++first2;

			}

		}

		return copy(first2, last2, copy(first1, last1, result));
	}


	template <class ForwardIterator>
	ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last)
	{
		if (first == last)
		{
			return last;
		}

		ForwardIterator next=first;
		while (++next != last)
		{
			if (*next == *first)
			{
				return first;
			}

			first = next;
		}

		return last;
	}



	template <class ForwardIterator, class BinaryPredicate>
	ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last, BinaryPredicate binary_pred)
	{
		if (first == last)
		{
			return last;
		}

		ForwardIterator next=first;
		while (++next != last)
		{
			if (binary_pred(*next, *first))
			{
				return first;
			}

			first = next;
		}

		return last;
	}

	template<class InputIterator, class T>
	typename iterator_traits<InputIterator>::difference_type
		count(InputIterator first, InputIterator last, const T& value)
	{
		typename iterator_traits<InputIterator>::difference_type n = 0;
		for (; first != last; ++first)
		{
			if (*first == value)
			{
				++n;
			}
		}

		return n;
	}

	template<class InputIterator, class Predicate>
	typename iterator_traits<InputIterator>::difference_type
		count_if(InputIterator first, InputIterator last, Predicate pred)
	{
		typename iterator_traits<InputIterator>::difference_type n = 0;
		for (; first != last; ++first)
		{
			if (pred(*first))
			{
				++n;
			}
		}

		return n;
	}

	template<class InputIterator, class T>
	InputIterator find(InputIterator first, InputIterator last, const T& value)
	{
		while (first!=last&&*first!=value)
		{
			++first;
		}

		return first;
	}

	template<class InputIterator, class Predicate>
	InputIterator find_if(InputIterator first, InputIterator last, Predicate pred)
	{
		while (first != last&&!pred(*first))
		{
			++first;
		}

		return first;
	}


	template<class ForwardIterator1,class ForwardIterator2, class Distance1, class Distance2>
	ForwardIterator1 __search(ForwardIterator1 first1, ForwardIterator1 last1,
		ForwardIterator2 first2, ForwardIterator2 last2, Distance1*, Distance2*)
	{
		Distance1 d1 = 0;
		distance(first1, last1, d1);
		Distance2 d2 = 0;
		distance(first2, last2, d2);

		if (d1 < d2)
		{
			return last1;
		}

		ForwardIterator1 current1 = first1;
		ForwardIterator2 current2 = first2;

		while (current2!=last2)
		{
			if (*current1 == *current2)
			{
				++current1;
				++current2;
			}
			else{

				if (d1 == d2)
				{
					return last1;
				}
				else
				{
					current1 = ++first1;
					current2 = first2;
					--d1;
				}
			}

		}

		return first1;
	}
	


	template<class ForwardIterator1, class ForwardIterator2>
	inline ForwardIterator1 search(ForwardIterator1 first1, ForwardIterator1 last1,
		ForwardIterator2 first2, ForwardIterator2 last2)
	{

		return __search(first1, last1, first2, last2, distance_type(first1), distance_type(first2));
	}




	template<class ForwardIterator, class Integer, class T>
	ForwardIterator search_n(ForwardIterator first, ForwardIterator last, Integer count,const T& value)
	{
		if (count <= 0)
		{
			return first;
		}
		else
		{
			first = find(first, last, value);
			while (first!=last)
			{
				Integer n = count - 1;
				ForwardIterator i = first;
				++i;
				while (i!=last&&n!=0&&*i==value)
				{
					++i;
					--n;
				}

				if (n == 0)
				{
					return first;
				}
				else
				{
					first = find(i, last, value);
				}

			}

			return last;
		}
	}


	template<class ForwardIterator, class Integer, class T, class BinaryPredicate>
	ForwardIterator search_n(ForwardIterator first, ForwardIterator last, Integer count,
		const T& value, BinaryPredicate binary_pred)
	{
		if (count <= 0)
		{
			return first;
		}
		else
		{
			while (first != last)
			{
				if (binary_pred(value, *first))
				{
					break;
				}

				++first;

			}
			while (first != last)
			{
				Integer n = count - 1;
				ForwardIterator i = first;
				++i;
				while (i != last&&n != 0 && binary_pred(*i, value))
				{
					++i;
					--n;
				}

				if (n == 0)
				{
					return first;
				}
				else
				{
					while (i != last)
					{
						if (binary_pred(value, *i))
						{
							break;
						}

						++i;

					}

					first = i;
				}

			}

			return last;
		}
	}

	template<class ForwardIterator1, class ForwardIterator2>
	ForwardIterator1 __find_end(ForwardIterator1 first1, ForwardIterator1 last1,
		ForwardIterator2 first2, ForwardIterator2 last2, forward_iterator_tag, forward_iterator_tag)
	{
		if (first2 == last2)
		{
			return last1;
		}

		else
		{
			ForwardIterator1 result = last1;
			while (1)
			{
				ForwardIterator1 new_result = search(first1, last1, first2, last2);//
				if (new_result == last1)
				{
					return result;
				}
				else
				{
					result = new_result;
					first1 = new_result;
					++first1;
				}
			}
		}
	}


	template<class BidirectionalIterator1, class BidirectionalIterator2>
	BidirectionalIterator1
		__find_end(BidirectionalIterator1 first1, BidirectionalIterator1 last1,
		BidirectionalIterator2 first2, BidirectionalIterator2 last2, bidirectional_iterator_tag)
	{
		typedef reverse_iterator<BidirectionalIterator1> reviter1;
		typedef reverse_iterator<BidirectionalIterator2> reviter2;

		reviter1 rlast1(first1);
		reviter2 rlast2(first2);

		reviter1 rresult = search(reviter1(last1), rlast1,
			reviter2(last2), rlast2);

		if (rresult == rlast1)
		{
			return last1;
		}
		else
		{
			BidirectionalIterator1 result = rresult.base();
			advance(result, -distance(first2, last2));
			return result;
		}
	}


	template<class ForwardIterator1, class ForwardIterator2>
	inline ForwardIterator1 find_end(ForwardIterator1 first1, ForwardIterator1 last1,
		ForwardIterator2 first2, ForwardIterator2 last2)
	{
		typedef typename iterator_traits<ForwardIterator1>::iterator_category category1;
		typedef typename iterator_traits<ForwardIterator2>::iterator_category category2;
		return __find_end(first1, last1, first2, last2, category1(), category2());
	}

	template<class ForwardIterator1, class ForwardIterator2>
	inline ForwardIterator1 find_first_of(ForwardIterator1 first1, ForwardIterator1 last1,
		ForwardIterator2 first2, ForwardIterator2 last2)
	{
		for (; first1 != last1; ++first1)
		{
			for (ForwardIterator1 iter = first2; iter != last2; ++iter)
			{
				if (*first1 == *iter)
				{
					return first1;
				}
			}
		}

		return last1;
	}


	template<class InputIterator, class Function>
	Function for_each(InputIterator first, InputIterator last, Function f)
	{
		for (; first != last; ++first)
		{
			f(*first);
		}

		return f;
	}

	template<class ForwardIterator, class Generator>
	void generate(ForwardIterator first, ForwardIterator last, Generator gen)
	{
		for (; first != last; ++first)
		{
			*first = gen();
		}
	}


	template<class OutputIterator, class Size, class Generator>
	OutputIterator generate_n(OutputIterator first, Size n, Generator gen)
	{
		for (; n > 0; --n, ++first)
		{
			*first = gen();
		}

		return first;
	}

	template<class InputIterator1, class InputIterator2>
	bool include(InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2)
	{
		while (first1!=last1&&first2!=last2)
		{
			if (*first2 < *first1)
			{
				return false;
			}
			else if (*first1 < *first2)
			{
				++first1;
			}
			else
			{
				++first1;
				++first2;
			}

		}

		return  first2 == last2;
	}

	template<class InputIterator1, class InputIterator2, class Compare>
	bool include(InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2, Compare comp)
	{
		while (first1 != last1&&first2 != last2)
		{
			if (comp(*first2 , *first1))
			{
				return false;
			}
			else if (comp(*first1 , *first2))
			{
				++first1;
			}
			else
			{
				++first1;
				++first2;
			}

		}

		return  first2 == last2;
	}


	template<class ForwardIterator>
	ForwardIterator max_element(ForwardIterator first, ForwardIterator last)
	{
		if (first == last)
		{
			return first;
		}
		ForwardIterator result = first;
		while (++first!=last)
		{
			if (*result < *first)
			{
				result = first;
			}
		}

		return result;
	}


	template<class ForwardIterator, class Compare>
	ForwardIterator max_element(ForwardIterator first, ForwardIterator last, Compare comp)
	{
		if (first == last)
		{
			return first;
		}
		ForwardIterator result = first;
		while (++first != last)
		{
			if (comp(*result , *first))
			{
				result = first;
			}
		}

		return result;
	}


	template<class ForwardIterator>
	ForwardIterator min_element(ForwardIterator first, ForwardIterator last)
	{
		if (first == last)
		{
			return first;
		}
		ForwardIterator result = first;
		while (++first != last)
		{
			if (*first < *result)
			{
				result = first;
			}
		}

		return result;
	}


	template<class ForwardIterator, class Compare>
	ForwardIterator min_element(ForwardIterator first, ForwardIterator last, Compare comp)
	{
		if (first == last)
		{
			return first;
		}
		ForwardIterator result = first;
		while (++first != last)
		{
			if (comp(*first, *result))
			{
				result = first;
			}
		}

		return result;
	}

	template<class InputIterator1, class InputIterator2, class OutputIterator>
	OutputIterator merge(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2,
		OutputIterator result)
	{
		while (first1!=last1&&first2!=last2)
		{
			if (*first1 < *first2)
			{
				*(result++) = *(first1++);
			}
			else
			{
				*(result++) = *(first2++);
			}
		}

		return copy(first2, last2, copy(first1, last1, result));
	}


	template<class InputIterator1, class InputIterator2, class OutputIterator, class Compare>
	OutputIterator merge(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2,
		OutputIterator result, Compare comp)
	{
		while (first1 != last1&&first2 != last2)
		{
			if (comp(*first1 , *first2))
			{
				*(result++) = *(first1++);
			}
			else
			{
				*(result++) = *(first2++);
			}
		}

		return copy(first2, last2, copy(first1, last1, result));
	}



	template<class BidirectionalIterator, class Predicate>
	BidirectionalIterator partition(BidirectionalIterator first, BidirectionalIterator last, Predicate pred)
	{
		while (true)
		{
			while (true)
			{
				if (first == last)
				{
					return first;
				}
				else if (pred(*first))
				{
					++first;
				}
				else
				{
					break;
				}

			}

			--last;
			while (true)
			{
				if (first == last)
				{
					return first;
				}
				else if (!pred(*last))
				{
					--last;
				}
				else
				{
					break;
				}
			}
		}

		iter_swap(first, last);
		++first;
	}

	template<class InputIterator, class OutputIterator, class T>
	OutputIterator remove_copy(InputIterator first, InputIterator last, OutputIterator result, const T& value)
	{
		for (; first != last; ++first)
		{
			if (*first != value)
			{
				*(result++) = *first;
			}
		}

		return result;
	}


	template<class InputIterator, class OutputIterator, class Predicate>
	OutputIterator remove_copy_if(InputIterator first, InputIterator last, OutputIterator result, Predicate pred)
	{
		for (; first != last; ++first)
		{
			if (!pred(*first , value))
			{
				*(result++) = *first;
			}
		}

		return result;
	}


	template<class ForwardIterator, class T>
	ForwardIterator remove(ForwardIterator first, ForwardIterator last, const T& value)
	{
		first = find(first, last, value);
		ForwardIterator next = first;
		return first == last ? first : remove_copy(++next, last, first, value);
	}


	template<class ForwardIterator, class Predicate>
	ForwardIterator remove_if(ForwardIterator first, ForwardIterator last, Predicate pred)
	{
		first = find(first, last, pred);
		ForwardIterator next = first;
		return first == last ? first : remove_copy_if(++next, last, first, pred);
	}


	template<class ForwardIterator, class T>
	void replace(ForwardIterator first, ForwardIterator last, const T& old_value, const T& new_value)
	{
		for (; first != last; ++first)
		{
			if (*first == old_value)
			{
				*first = new_value;
			}
		}
	}


	template<class InputIterator, class OutputIterator, class T>
	void replace_copy(InputIterator first, InputIterator last, OutputIterator result,
		const T& old_value, const T& new_value)
	{
		for (; first != last; ++first, ++result)
		{
			*result = *first == old_value ? new_value : *first;
		}
	}



	template<class ForwardIterator, class Predicate, class T>
	void replace_if(ForwardIterator first, ForwardIterator last, Predicate pred, const T& old_value, const T& new_value)
	{
		for (; first != last; ++first)
		{
			if (pred(*first , old_value))
			{
				*first = new_value;
			}
		}
	}

	template<class InputIterator, class OutputIterator, class Predicate, class T>
	void replace_copy_if(InputIterator first, InputIterator last, OutputIterator result,
		Predicate pred, const T& old_value, const T& new_value)
	{
		for (; first != last; ++first, ++result)
		{
			*result = pred( *first, old_value) ? new_value : *first;
		}
	}

	template<class BidirectionalIterator>
	void __reverse(BidirectionalIterator first, BidirectionalIterator last, bidirectional_iterator_tag)
	{
		while (true)
		{
			if (first == last || first == --last)
			{
				return;
			}
			else
			{
				iter_swap(first, last);
			}
		}
	}

	template<class RandomAccessIterator>
	void __reverse(RandomAccessIterator first, RandomAccessIterator last, random_access_iterator_tag)
	{
		while (first<last)
		{
			iter_swap(first++, last--);
		}
	}

	template <class BidirectionalIterator>
	void reverse(BidirectionalIterator first, BidirectionalIterator last)
	{
		__reverse(first, last, iterator_category(first));
	}


	template<class BidirectionalIterator, class OutputIterator>
	OutputIterator reverse_copy(BidirectionalIterator first, BidirectionalIterator last,
		OutputIterator result)
	{
		while (first!=last)
		{
			--last;
			*result = *last;
			++result;
		}

		return result;
	}


	template<class ForwardIterator, class Distance>
	void __rotate(ForwardIterator first, ForwardIterator middle, ForwardIterator last, Distance*, forward_iterator_tag)
	{
		for (ForwardIterator i = middle;;)
		{
			iter_swap(first, i);
			++first;
			++i;
			if (first == middle)
			{
				if (i == = last)
				{
					return;
				}

				middle = i;
			}
			else if (i == last)
			{
				i = middle;
			}
		}
	}


	template<class BidirectionalIterator, class Distance>
	void __rotate(BidirectionalIterator first, BidirectionalIterator middle, BidirectionalIterator last,
		Distance*, bidirectional_iterator_tag)
	{
		reverse(first, middle);
		reverse(middle, last);
		reverse(first, last);
	}



	template<class EuclideanRingElement>
	EuclideanRingElement __gcd(EuclideanRingElement m, EuclideanRingElement n)
	{
		while (n!=0)
		{
			EuclideanRingElement t = m%n;
			m = n;
			n = t;
		}

		return m ;
	}

	template<class RandomAccessIterator, class Distance, class T>
	void __rotate_cycle(RandomAccessIterator first, RandomAccessIterator last,
		RandomAccessIterator initial, Distance shift, T*)
	{

		T value = *initial;
		RandomAccessIterator ptr1 = initial;
		RandomAccessIterator ptr2 = ptr1 + shift;
		while (ptr2!=initial)
		{
			*ptr1 = *ptr2;
			ptr1 = ptr2;
			if (last - ptr2 > shift)
			{
				ptr2 += shift;
			}
			else
			{
				ptr2 = first + (shift - (last - ptr2));
			}

		}

		*ptr1 = value;
	}
	

	template<class RandomAccessIterator, class Distance>
	void __rotate(RandomAccessIterator first, RandomAccessIterator middle, RandomAccessIterator last,
		Distance*, random_access_iterator_tag)
	{
		Distance n = __gcd(last - first, middle - first);
		while (n--)
		{
			__rotate_cycle(first, last, first + n, middle - first, value_type(first));
		}
	}
	

	template<class ForwardIterator>
	inline void rotate(ForwardIterator first, ForwardIterator middle, ForwardIterator last)
	{
		__rotate(first, middle, last, distance_type(first), iterator_category(first));
	}


	template<class ForwardIterator, class OutputIterator>
	OutputIterator rotate_copy(ForwardIterator first, ForwardIterator middle,
		ForwardIterator last, OutputIterator result)
	{
		return copy(first, middle, copy(middle, last, result));
	}


		
	template<class ForwardIterator1, class ForwardIterator2>
	ForwardIterator2 swap_range(ForwardIterator1 first1, ForwardIterator1 last1,
		ForwardIterator2 first2)
	{
		for (; first1 != last1; ++first1, ++first2)
		{
			iter_swap(first1, first2);
		}

		return first2;
	}


	template<class InputIterator, class OutputIterator, class UnaryOperation>
	OutputIterator transform(InputIterator first, InputIterator last, OutputIterator result,
		UnaryOperation op)
	{
		for (; first != last; ++first, ++result)
		{
			*result = op(*first);
		}

		return result;
	}


	template<class InputIterator1, class InputIterator2, class OutputIterator, class BinaryOperation>
	OutputIterator transform(InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, OutputIterator result, BinaryOperation binary_op)
	{
		for (; first1 != last1; ++first1, ++first2, ++result)
		{
			*result = binary_op(*first1, *first2);
		}

		return result;

	}


	template<class InputIterator, class ForwardIterator>
	ForwardIterator __unique_copy(InputIterator first, InputIterator last,
		ForwardIterator result, forward_iterator_tag)
	{
		*result = *first;
		while (++first!=last)
		{
			if (*result != last)
			{
				*++result = *first;
			}
		}
		return ++result;
	}


	template<class InputIterator, class OutputIterator, class T>
	OutputIterator __unique_copy(InputIterator first, InputIterator last, OutputIterator result,
		T*)
	{
		T value = *first;
		*result = value;
		while (++first!=last)
		{
			if (value != *first)
			{
				value = *first;
				*++result = value;
			}
		}
	}

	template<class InputIterator,class OutputIterator>
	inline OutputIterator __unique_copy(InputIterator first, InputIterator last,
		OutputIterator result, output_iterator_tag)
	{
		return __unique_copy(first, last, result, value_type(first));
	}

	template<class InputIterator, class OutputIterator>
	inline OutputIterator unique_copy(InputIterator first, InputIterator last, OutputIterator result)
	{
		if (first == last)
		{
			return result;
		}

		return __unique_copy(first, last, result, iterator_category(first));

	}


	template<class ForwardIterator>
	ForwardIterator unique(ForwardIterator first, ForwardIterator last)
	{
		first = adjacent_find(first, last);
		return __unique_copy(first, last, first);
	}


	template<class ForwardIterator, class T>
	bool binary_search(ForwardIterator first, ForwardIterator last, const T& value)
	{
		ForwardIterator i = lower_bound(first, last, value);
		return i != last&&!(value < *i);
	}


	template<class ForwardIterator, class T, class Compare>
	bool binary_search(ForwardIterator first, ForwardIterator last, const T& value,
		Compare comp)
	{
		ForwardIterator i = lower_bound(first, last, value, comp);
		return i != last&&!comp(value, *i);
	}

	template<class BidirectionalIterator>
	bool next_premutation(BidirectionalIterator first, BidirectionalIterator last)
	{
		if (first == last)
		{
			return false;
		}

		BidirectionalIterator i = first;
		++i;
		if (i == last)
		{
			return false;
		}
		i = last;
		--i;

		for (;;)
		{
			BidirectionalIterator ii = i;
			--i;
			if (*i < *ii)
			{
				BidirectionalIterator j = last;
				while (!(*i<*--j))
				{

				}
				iter_swap(i, j);
				reverse(ii, last);
				return true;
			}
			if (i == first)
			{
				reverse(first, last);
				return false;
			}

		}
	}

	template<class BidirectionalIterator, class Compare>
	bool next_premutation(BidirectionalIterator first, BidirectionalIterator last,
		Compare comp)
	{
		if (first == last)
		{
			return false;
		}

		BidirectionalIterator i = first;
		++i;
		if (i == last)
		{
			return false;
		}
		i = last;
		--i;

		for (;;)
		{
			BidirectionalIterator ii = i;
			--i;
			if (comp(*i , *ii))
			{
				BidirectionalIterator j = last;
				while (!comp(*i,*--j))
				{

				}
				iter_swap(i, j);
				reverse(ii, last);
				return true;
			}
			if (i == first)
			{
				reverse(first, last);
				return false;
			}

		}
	}


	template<class BidirectionalIterator>
	bool prev_permutation(BidirectionalIterator first, BidirectionalIterator last)
	{
		if (first == last)
		{
			return false;
		}
		BidirectionalIterator i = first;
		++i;
		if (i == last)
		{
			return false;
		}

		i = last;
		--i;
		for (;;)
		{
			BidirectionalIterator ii = i;
			--i;
			if (*ii < i)
			{
				BidirectionalIterator j = last;
				while (*--j<*i)
				{

				}
				iter_swap(i, j);
				reverse(ii, last);
				return true;

			}

			if (i == first)
			{
				reverse(first, last);
				return false;
			}
		}
	}

	template<class BidirectionalIterator, class Compare>
	bool prev_permutation(BidirectionalIterator first, BidirectionalIterator last,
		Compare comp)
	{
		if (first == last)
		{
			return false;
		}
		BidirectionalIterator i = first;
		++i;
		if (i == last)
		{
			return false;
		}

		i = last;
		--i;
		for (;;)
		{
			BidirectionalIterator ii = i;
			--i;
			if (comp(*ii, i))
			{
				BidirectionalIterator j = last;
				while (comp(*--j, *i));
				iter_swap(i, j);
				reverse(ii, last);
				return true;

			}

			if (i == first)
			{
				reverse(first, last);
				return false;
			}
		}
	}

	template<class RandomAccessIterator, class Distance>
	void __random_shuffle(RandomAccessIterator first, RandomAccessIterator last, Distance*)
	{
		if (first == last)
		{
			return;
		}

		for (RandomAccessIterator i = first + 1; != last; ++i)
		{
			iter_swap(i, first + Distance(rand() % ((i - first) + 1)));
		}

	}



	template<class RandomAccessIterator>
	inline void random_shuffle(RandomAccessIterator first, RandomAccessIterator last)
	{
		__random_shuffle(first, last, distance_type(first));
	}


	template<class RandomAccessIterator, class RandomNumberGenerator>
	void random_shuffle(RandomAccessIterator first, RandomAccessIterator last,
		RandomNumberGenerator& rand)
	{
		if (first == last)
		{
			return;
		}

		for (RandomAccessIterator i = first + 1; i != last; ++i)
		{
			iter_swap(i, first + rand((i - first) + 1));
		}
	}


	template<class RandomAccessIterator>
	inline void partoa;

}


#endif