#ifndef __JMM_STL_FUNCTION
#define __JMM_STL_FUNCTION

namespace JMM_STL
{
	template <class Arg1, class Arg2, class Result>
	struct binary_function
	{
		typedef Arg1 first_argument_type;
		typedef Arg2 second_argument_type;
		typedef Result result_type;

	};


	template<class T>
	struct less:public binary_function<T,T,bool>
	{
		bool operator()(const T&x, const T&y)
		{
			return x < y;
		}

	};
}

#endif