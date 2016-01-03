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


	template<class Arg, class Result>
	struct unary_function
	{
		typedef Arg argument_type;
		typedef Result result_type;
	};

	template<class T>
	struct less:public binary_function<T,T,bool>
	{
		bool operator()(const T&x, const T&y) const
		{
			return x < y;
		}

	};

	template<class T>
	struct greater:binary_function<T,T,bool>
	{
		bool operator()(const T& x, const T& y) const
		{
			return x>y;
		}
	};

	template<class T>
	struct identity :public unary_function < T, T >
	{
		const T& operator()(const T& x) const
		{
			return x;
		}
	};

	template<class Pair>
	struct select1st : public unary_function<Pair, typename Pair::first_type>
	{
		const typename Pair::first_type& operator()(const Pair& x) const
		{
			return x.first;
		}
		
	};


	template <class T>
	struct equal_to :public binary_function < T, T, bool >
	{
		bool operator()(const T& x, const T& y) const
		{
			return x == y;
		}

	};


	template<class T>
	struct plus :public binary_function < T, T, T >
	{
		T operator()(const T& x, const T& y) const
		{
			return x + y;
		}
	};

	template<class T>
	struct multiplies :public binary_function < T, T, T >
	{
		T operator()(const T& x, const T& y) const
		{
			return x*y;
		}
	};

	template<class T> 
	inline T identity_element(plus<T>)
	{
		return T(0);
	}


	template<class T>
	inline T identity_element(multiplies<T>)
	{
		return T(1);
	}


	template<class Operation>
	class binder2nd :public unary_function<typename Operation::first_argument_type,
		typename Operation::result_type>
	{
	protected:
		Operation op;
		typename Operation::second_argument_type value;
	public:
		binder2nd(const Operation& x,
			const typename Operation::second_argument_type& y) :op(x), value(y)
		{

		}

		typename Operation::result_type  operator()
			(const typename Operation::first_argument_type& x) const
		{
			return op(x, value);
		}
	};

	template<class Operation, class T>
	inline binder2nd<Operation> bind2nd(const Operation& op, const T& x)
	{
		typedef typename Operation::second_argument_type arg2_type;
		return binder2nd<Operation>(op, arg2_type(x));
	}
}

#endif