#ifndef JMM_STL_ITERATOR
#define JMM_STL_ITERATOR

namespace JMM_STL
{


	struct input_iterator_tag{};
	struct output_iterator_tag{};
	struct forward_iterator_tag :public input_iterator_tag{};
	struct bidirectional_iterator_tag :public forward_iterator_tag{};
	struct random_access_iterator_tag :public bidirectional_iterator_tag{};


	template <class Category, class T, class Distance = ptrdiff_t,
	class Pointer = T*, class Reference = T&>
	struct iterator
	{
		typedef Category	iterator_category;
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;

	};


	template <class Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::iterator_category	iterator_category;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;

	};


	template <class T>
	struct iterator_traits<T*>
	{
		typedef typename random_access_iterator_tag		iterator_category;
		typedef typename T								value_type;
		typedef typename ptrdiff_t						difference_type;
		typedef typename T*								pointer;
		typedef typename T&								reference;

	};


	template <class T>
	struct iterator_traits<const T*>
	{
		typedef typename random_access_iterator_tag		iterator_category;
		typedef typename T								value_type;
		typedef typename ptrdiff_t						difference_type;
		typedef typename T*								pointer;
		typedef typename T&								reference;

	};



	template<class InputIterator>
	inline typename iterator_traits<InputIterator>::iterator_catergory
		iterator_category(InputIterator & i)
	{
		typedef typename iterator_traits<InputIterator>::iterator_catergory category;

		return catergory();
	}

	template <class Iterator>
	inline typename iterator_traits<Iterator>::difference_type *
		distance_type(const Iterator&)
	{
		return static_cast<typename iterator_traits<Iterator>::difference_type*>(0);

	}


	template <class Iterator>
	inline typename iterator_traits<Iterator>::value_type *
		value_type(const Iterator&)
	{
		return static_cast<typename iterator_traits<Iterator>::value_type*>(0);

	}


	template <class InputIterator>
	inline typename iterator_traits<InputIterator>::difference_type
		__distance(InputIterator first, InputIterator last, input_iterator_tag)
	{
		iterator_traits<InputIterator>::difference_type n = 0;
		while (first != last)
		{
			++first;

			++n;

		}


		return n;

	}


	template <class RandomAcessIterator>
	inline typename iterator_traits<RandomAcessIterator>::difference_type
		__distance(RandomAcessIterator first, RandomAcessIterator last, random_access_iterator_tag)
	{
		iterator_traits<RandomAcessIterator>::difference_type n = 0;


		return last - first;

	}


	template <class InputIterator>
	inline typename iterator_traits<InputIterator>::difference_type
		distance(InputIterator first, InputIterator last)
	{
		typedef typename
			iterator_traits<InputIterator>::iterator_category category;
		return __distance(first, last, category());

	}


	template <class InputIterator, class Distance>
	inline void __advance(InputIterator& i, Distance n,
		input_iterator_tag){

		while (n--)++i;

	}

	template <class BidirectionalIterator, class Distance>
	inline void __advance(BidirectionalIterator &i, Distance n,
		bidirectional_iterator_tag)
	{
		if (n >= 0)
		{
			while (n--)
			{
				++i;
			}
		}
		else
		{
			while (n--)
			{
				--i;
			}
		}

	}


	template <class RandomAccessIterator, class Distance>
	inline void __advance(RandomAccessIterator &i, Distance n,
		random_access_iterator_tag)
	{
		i += n;

	}


	template <class InputIterator, class Distance>
	inline void advance(InputIterator& i, Distance n)
	{
		return __advance(i, n, iterator_category(i));
	}


	template <class Iterator>
	class reverse_iterator
	{
	protected:
		Iterator current;
	public:
		typedef typename iterator_traits<Iterator>::iterator_category
			iterator_category;
		typedef typename iterator_traits<Iterator>::value_type
			value_type;
		typedef typename iterator_traits<Iterator>::difference_type
			difference_type;
		typedef typename iterator_traits<Iterator>::pointer
			pointer;
		typedef typename iterator_traits<Iterator>::reference
			reference;

		typedef Iterator iterator_type;
		typedef reverse_iterator<Iterator> self;

	public:
		reverse_iterator() {}
		explicit reverse_iterator(iterator_type x) : current(x) {}

		reverse_iterator(const self& x) : current(x.current) {}



		iterator_type base() const { return current; }
		reference operator*() const {
			Iterator tmp = current;
			return *--tmp;
		}

		pointer operator->() const { return &(operator*()); }

		self& operator++() {
			--current;
			return *this;
		}
		self operator++(int) {
			self tmp = *this;
			--current;
			return tmp;
		}
		self& operator--() {
			++current;
			return *this;
		}
		self operator--(int) {
			self tmp = *this;
			++current;
			return tmp;
		}

		self operator+(difference_type n) const {
			return self(current - n);
		}
		self& operator+=(difference_type n) {
			current -= n;
			return *this;
		}
		self operator-(difference_type n) const {
			return self(current + n);
		}
		self& operator-=(difference_type n) {
			current += n;
			return *this;
		}
		reference operator[](difference_type n) const { return *(*this + n); }
	};

}

#endif