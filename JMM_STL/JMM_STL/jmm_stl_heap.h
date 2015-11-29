#ifndef __JMM_STL_HEAP
#define __JMM_STL_HEAP

#include "jmm_stl_iterator.h"

namespace JMM_STL
{

	template<class RandomAccessIterator,class Distance, class T>
	void __push_heap(RandomAccessIterator first, Distance holeIndex, Distance topIndex, T value)
	{
		Distance parent = (holeIndex - 1) / 2;
		while (holeIndex>topIndex && *(first+parent)<value)
		{
			*(first + holeIndex) = *(first + parent);
			holeIndex = parent;
			parent = (holeIndex - 1) / 2;
			
		}
		*(first + holeIndex) = value;
	}

	template<class RandomAccessIterator, class Distance, class T>
	inline void __push_heap_aux(RandomAccessIterator first,
		RandomAccessIterator last, Distance*, T*)
	{
		__push_heap(first, Distance(last - first - 1), Distance(0), T(*(last - 1)));
	
	}

	template <class RandomAccessIterator>
	inline void push_heap(RandomAccessIterator first, RandomAccessIterator last)
	{
		__push_heap_aux(first, last, distance_type(first), value_type(first));
	}


	template <class RandomAccessIterator, class Distance, class T>
	void __adjust_heap(RandomAccessIterator first, Distance holeIndex,
		Distance len, T value)
	{
		Distance topIndex = holeIndex;
		Distance secondChild = holeIndex * 2 + 2;
		while (secondChild<len)
		{
			if (*(secondChild + first) < *(first + (secondChild - 1)))
			{
				--secondChild;
			}
			*(first + holeIndex) = *(first + secondChild);
			holeIndex = secondChild;
			secondChild = holeIndex * 2 + 2;

		}

		if (secondChild == len)
		{
			*(first + holeIndex) = *(first + (secondChild - 1));
			holeIndex = secondChild - 1;
		}

		__push_heap(first, holeIndex, topIndex, value);
	}

	template <class RandomAccessIterator, class T, class Distance>
	inline void __pop_heap(RandomAccessIterator first, RandomAccessIterator last,
		RandomAccessIterator result, T value, Distance*)
	{
	
		*result = *first;

		__adjust_heap(first, Distance(0), Distance(last - first), value);
	}


	template<class RandomAccessIterator, class T>
	inline void __pop_heap_aux(RandomAccessIterator first, RandomAccessIterator last, T*)
	{
		__pop_heap(first, last-1, last - 1, *(last - 1), distance_type(first));
	
	}

	template<class RandomAccessIterator>
	inline void pop_heap(RandomAccessIterator first, RandomAccessIterator last)
	{
		__pop_heap_aux(first, last, value_type(first));
	}


	template <class RandomAccessIterator>
	void sort_heap(RandomAccessIterator first, RandomAccessIterator last)
	{
		while (last-first>1)
		{
			pop_heap(first, last--);
		}
	}


	template<class RandomAccessIterator, class T, class Distance>
	void __make_heap(RandomAccessIterator first, RandomAccessIterator last, T*, Distance*)
	{
		if (last - first < 2)
		{
			return;
		}
		Distance len = last - first;
		Distance parent = (len - 2) / 2;
		while (true)
		{
			__adjust_heap(first, parent , len, T(*(first + parent)));
			if (parent == 0)
			{
				return;
			}
			parent--;
		}
	}

	template<class RandomAccessIterator>
	inline void make_heap(RandomAccessIterator first, RandomAccessIterator last)
	{
		__make_heap(first, last, value_type(first), distance_type(first));
	}



	/*

	Below with compare function

	*/



	template<class RandomAccessIterator, class Distance, class T, class Compare>
	void __push_heap(RandomAccessIterator first, Distance holeIndex, Distance topIndex, T value, Compare comp)
	{
		Distance parent = (holeIndex - 1) / 2;
		while (holeIndex>topIndex && comp(*(first + parent),value))
		{
			*(first + holeIndex) = *(first + parent);
			holeIndex = parent;
			parent = (holeIndex - 1) / 2;

		}
		*(first + holeIndex) = value;
	}

	template<class RandomAccessIterator, class Distance, class T,class Compare>
	inline void __push_heap_aux(RandomAccessIterator first,
		RandomAccessIterator last, Distance*, T*, Compare comp)
	{
		__push_heap(first, Distance(last - first - 1), Distance(0), T(*(last - 1)),comp);
	}

	template <class RandomAccessIterator, class Compare>
	inline void push_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
	{
		__push_heap_aux(first, last, distance_type(first), value_type(first), comp);
	}


	template <class RandomAccessIterator, class Distance, class T, class Compare>
	void __adjust_heap(RandomAccessIterator first, Distance holeIndex,
		Distance len, T value, Compare comp)
	{
		Distance topIndex = holeIndex;
		Distance secondChild = holeIndex * 2 + 2;
		while (secondChild<len)
		{
			if (comp(*(secondChild + first) , *(first + (secondChild - 1))))
			{
				--secondChild;
			}
			*(first + holeIndex) = *(first + secondChild);
			holeIndex = secondChild;
			secondChild = holeIndex * 2 + 2;

		}

		if (secondChild == len)
		{
			*(first + holeIndex) = *(first + (secondChild - 1));
			holeIndex = secondChild - 1;
		}

		__push_heap(first, holeIndex, topIndex, value,comp);
	}

	template <class RandomAccessIterator, class T, class Distance, class Compare>
	inline void __pop_heap(RandomAccessIterator first, RandomAccessIterator last,
		RandomAccessIterator result, T value, Distance*, Compare comp)
	{

		*result = *first;

		__adjust_heap(first, Distance(0), Distance(last - first), value, comp);
	}


	template<class RandomAccessIterator, class T, class Compare>
	inline void __pop_heap_aux(RandomAccessIterator first, RandomAccessIterator last, T*,Compare comp)
	{
		__pop_heap(first, last - 1, last - 1, *(last - 1), distance_type(first), comp);

	}

	template<class RandomAccessIterator, class Compare>
	inline void pop_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
	{
		__pop_heap_aux(first, last, value_type(first), comp);
	}


	template <class RandomAccessIterator, class Compare>
	void sort_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
	{
		while (last - first>1)
		{
			pop_heap(first, last--, comp);
		}
	}


	template<class RandomAccessIterator, class T, class Distance, class Compare>
	void __make_heap(RandomAccessIterator first, RandomAccessIterator last, T*, Distance*, Compare comp)
	{
		if (last - first < 2)
		{
			return;
		}
		Distance len = last - first;
		Distance parent = (len - 2) / 2;
		while (true)
		{
			__adjust_heap(first, parent + first, len, T(*(first + parent)), comp);
			if (parent == 0)
			{
				return;
			}
			parent--;
		}
	}

	template<class RandomAccessIterator, class Compare>
	inline void make_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
	{
		__make_heap(first, last, value_type(first), distance_type(first), comp);
	}


	

}

#endif