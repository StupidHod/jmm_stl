#ifndef STL_JMM_UNINITIALIZED
#define STL_JMM_UNINITIALIZED



#include "jmm_stl_type_traits.h"
#include "jmm_stl_iterator.h"
#include "jmm_stl_construct.h"

namespace JMM_STL
{

	template<class ForwardIterator, class size, class T>
	inline ForwardIterator __uninitialized_fill_n_aux(ForwardIterator first, size n, const T& x, __false_type)
	{

		ForwardIterator cur = first;
		for (; n > 0; --n, ++cur)
		{
			construct(&*cur, x);
		}


		return cur;

	}

	template<class ForwardIterator, class size, class T>
	inline ForwardIterator __uninitialized_fill_n_aux(ForwardIterator first, size n, const T& x, __true_type)
	{

#pragma message("replace with fill_n")

		return __uninitialized_fill_n_aux(first, n, x, __false_type());

	}


	

	template<class ForwardIterator, class size, class T, class T1>
	inline ForwardIterator __uninitialized_fill_n(ForwardIterator first, size n, const T& x, T1*)
	{
		typedef typename __type_traits<T1>::is_POD_type is_POD;

		return __uninitialized_fill_n_aux(fist, n, x, is_POD());
		
	}



	template<class ForwardIterator, class size, class T>
	inline ForwardIterator uninitialized_fill_n(ForwardIterator first, size n, const T& x)
	{
		return __uninitialized_fill_n(first, n, x, value_type(T));

	}	
	

	template <class InputIterator, class ForwardIterator>
	ForwardIterator __uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator result,
		__false_type)
	{
		ForwardIterator cur = result;

		for (; first != last;++first, ++cur)
		{
			construct(&*cur, *first);

		}
	
		return cur;
	
	}

	template <class InputIterator, class ForwardIterator>
	inline ForwardIterator __uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator result,
		__true_type)
	{
		
#pragma message("replace with [copy(first,last,result)] laster")

		return __uninitialized_copy_aux(first, last, result, __false_type());

	}


	template<class InputIterator, class ForwardIterator,class T>
	inline ForwardIterator __uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result, T*)
	{
	
		typedef typename __type_traits<T>::is_POD_type is_POD;
		return __uninitialized_copy_aux(first, last, result, is_POD());
	
	
	}


	template<class InputIterator, class ForwardIterator>
	inline ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result)
	{
	
		return __uninitialized_copy(first, last, result, value_type(result));
	
	
	
	}


	template <class ForwardIterator,class T>
	inline ForwardIterator  __uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T& x, __false_type)
	{
	
		ForwardIterator cur = first;

		for (; first != last; ++first, ++cur)
		{
			construct(&*first, x);
		}
	
		return cur;
	
	}


	template <class ForwardIterator, class T>
	inline ForwardIterator  __uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T& x, __true_type)
	{

#pragma message("replace copy(first,last,x) later")
		
		return __uninitialized_fill_aux(first, last, x, __false_type());


	}


	template<class ForwardIterator, class T,class T1>
	inline ForwardIterator  __uninitialized_fill(ForwardIterator first, ForwardIterator last, const T&x)
	{

		typedef typename __type_traits<T>::is_POD_TYPE is_POD;
		return __uninitialized_copy_aux(first, last, x, is_POD());
	
	
	}

	/*
	template<class ForwardIterator, class T>
	inline ForwardIterator uninitialized_copy(ForwardIterator first, ForwardIterator last, const T& x)
	{
	
		return __uninitialized_copy(first, last, x, value_type(T));
	}

	*/
}



#endif