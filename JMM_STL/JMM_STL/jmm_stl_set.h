#ifndef __JMM_STL_SET
#define __JMM_STL_SET

#include "jmm_stl_function.h"
#include "jmm_stl_rb_tree.h"
#include "jmm_stl_alloc.h"
#include "jmm_stl_allocator.h"
#include "jmm_stl_iterator.h"

namespace JMM_STL
{
	template<class Key, class Compare = less<Key>, class Alloc=alloc>
	class set
	{
	public:
		typedef Key key_type;
		typedef Key value_type;
		typedef Compare key_compare;
		typedef Compare value_compare;

	private:
		template<class T>
		struct identity :public unary_function < T, T >
		{
			const T& operator()(const T& x) const
			{
				return x;
			}
		};

		typedef rb_tree < key_type, value_type, identity<value_type>, key_compare, Alloc >
			rep_type;
		rep_type t;

	public:
		typedef typename rep_type::const_pointer pointer;
		typedef typename rep_type::const_pointer const_pointer;
		typedef typename rep_type::const_reference reference;
		typedef typename rep_type::const_reference const_refernce;
		typedef typename rep_type::const_iterator iterator;

		typedef typename rep_type::const_iterator const_iterator;
		typedef typename rep_type::const_reverse_iterator const_reverse_iterator;
		typedef typename rep_type::reverse_iterator reverse_iterator;
		typedef typename rep_type::size_type size_type;
		typedef typename rep_type::difference_type difference_type;


		set() :t(Compare()){}
		explicit set(const Compare& comp) :t(comp){}

		template<class InputIterator>
		set(InputIterator first, InputIterator last) : t(Compare())
		{
			t.insert_unique(first, last);

		}

		template<class InputIterator>
		set(InputIterator first, InputIterator last, const Compare& comp) : t(comp)
		{
			t.insert_unique(first, last);
	
		}

		set(const set<Key, Compare, Alloc>& x) :t(x.t){}

		set<Key, Compare, Alloc>& operator=(const set<Key, Compare, Alloc>& x)
		{
			t = x.t;
			return *this;
		}

		key_compare key_comp() const
		{
			return t.key_comp();
		}

		value_compare value_comp() const
		{
			return t.key_comp();
		}

		iterator begin() const
		{
			return t.begin();
		}

		iterator end() const
		{
			return t.end();
		}


		reverse_iterator rbegin() const
		{
			return t.rbegin();
		}

		reverse_iterator rend() const
		{
			return t.rend();
		}

		bool empty()
		{
			return t.empty();
		}


		size_type size() const
		{
			return t.size();
		}

		size_type max_size() const
		{
			return t.max_size();
		}

		void swap(set<Key, Compare, Alloc>& x)
		{
			t.swap(x.t);
		}



		typedef pair<iterator, bool> pair_iterator_bool;
		pair<iterator, bool> insert(const value_type& x)
		{
			pair<typename rep_type::iterator, bool> p = t.insert_unique)(x);
			return pair<iterator, bool>(p.first, p.second);
		}

		iterator insert(iterator position, const value_type& x)
		{
			typedef typename rep_type::iterator rep_iterator;
			return t.insert_unique((rep_iterator)position, x);
		}


		template <class InputIterator>
		void insert(InputIterator first, InputIterator last)
		{
			t.insert_unique(first, last);
		}


		






	};

}

#endif