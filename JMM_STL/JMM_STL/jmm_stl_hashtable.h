#ifndef __JMM_STL_HASHTABLE
#define __JMM_STL_HASHTABLE

#include "jmm_stl_alloc.h"
#include "jmm_stl_vector.h"
#include "jmm_stl_iterator.h"
#include <stddef.h>
#include "jmm_stl_algobase.h"
#include "jmm_stl_algo.h"
#include "jmm_stl_construct.h"
#include "jmm_stl_function.h"
#include "jmm_stl_uninitialized.h"
#include "jmm_stl_pair.h"

namespace JMM_STL
{

	template<class Value, class Key, class HashFun,
		class ExtractKey, class EqualKey, class Alloc = alloc>
	class hashtable;

	template<class Value, class Key, class HashFun,
		class ExtractKey, class EqualKey, class Alloc>
	struct __hashtable_iterator;

	template<class Value, class Key, class HashFun,
		class ExtractKey, class EqualKey, class Alloc>
	struct __hashtable_const_iterator;

	template <class Value>
	struct  __hashtable_node
	{
		__hashtable_node* next;
		Value val;
	};

	template<class Value, class Key, class HashFun,
		class ExtractKey, class EqualKey, class Alloc>
	struct __hashtable_iterator{

		typedef hashtable<Value, Key, HashFun, ExtractKey, EqualKey, Alloc> hashtable;
		typedef __hashtable_iterator<Value, Key, HashFun, ExtractKey, EqualKey, Alloc> iterator;
		typedef __hashtable_const_iterator<Value, Key, HashFun, ExtractKey, EqualKey, Alloc> const_iterator;
		typedef __hashtable_node<Value> node;

		
		typedef forward_iterator_tag iterator_category;
		typedef Value value_type;
		typedef ptrdiff_t difference_type;
		typedef size_t size_type;
		typedef Value& reference;
		typedef Value* pointer;

		node* cur;
		hashtable* ht;

		__hashtable_iterator(node* n, hashtable* tab) :cur(n), ht(tab){}
		__hashtable_iterator();

		reference operator*() const
		{
			return cur->val;
		}
		pointer operator->() const
		{
			return &(operator*());
		}

		iterator& operator++();
		iterator operator++(int);
		bool operator==(const iterator& it) const
		{
			return cur == it.cur;
		}

		bool operator!=(const iterator& it) const
		{
			return cur != it.cur;
		}

	};


	template<class Value, class Key, class HashFun,
	class ExtractKey, class EqualKey, class Alloc>
	struct __hashtable_const_iterator{
	

		typedef hashtable<Value, Key, HashFun, ExtractKey, EqualKey, Alloc> hashtable;
		typedef __hashtable_iterator<Value, Key, HashFun, ExtractKey, EqualKey, Alloc> iterator;
		typedef __hashtable_const_iterator<Value, Key, HashFun, ExtractKey, EqualKey, Alloc> const_iterator;
		typedef __hashtable_node<Value> node;


		typedef forward_iterator_tag iterator_category;
		typedef Value value_type;
		typedef ptrdiff_t difference_type;
		typedef size_t size_type;
		typedef const Value& reference;
		typedef const Value* pointer;

		const node* cur;
		const hashtable* ht;

		__hashtable_const_iterator(const node* n, const hashtable* tab) :cur(n), ht(tab){}
		__hashtable_const_iterator();
		__hashtable_const_iterator(const iterator& it) :cur(it.cur), ht(it.ht){}

		reference operator*() const
		{
			return cur->val;
		}
		pointer operator->() const
		{
			return &(operator*());
		}

		const_iterator& operator++();
		const_iterator operator++(int);
		bool operator==(const const_iterator& it) const
		{
			return cur == it.cur;
		}

		bool operator!=(const const_iterator& it) const
		{
			return cur != it.cur;
		}
	
	};

	template<class Value, class Key, class HashFun,class ExtractKey, class EqualKey, class Alloc>
		__hashtable_iterator<Value, Key, HashFun, ExtractKey, EqualKey, Alloc>&
		__hashtable_iterator<Value, Key, HashFun, ExtractKey, EqualKey, Alloc>::operator++()
	{
		const node* old = cur;
		cur = cur->next;
		if (!cur)
		{
			size_type bucket = ht->bkt_num(old->val);
			while (!cur && ++bucket < ht->buckets.size())
			{
				cur = ht->buckets[bucket];
			}

		}

		return *this;

	}

	template<class Value, class Key, class HashFun,
	class ExtractKey, class EqualKey, class Alloc>
		__hashtable_iterator<Value, Key, HashFun, ExtractKey, EqualKey, Alloc>
		__hashtable_iterator<Value, Key, HashFun, ExtractKey, EqualKey, Alloc>::operator++(int)
	{
		iterator tmp = *this;
		++*this;
		return tmp;
	}

	template<class Value, class Key, class HashFun,
	class ExtractKey, class EqualKey, class Alloc>
		__hashtable_const_iterator<Value, Key, HashFun, ExtractKey, EqualKey, Alloc>&
		__hashtable_const_iterator<Value, Key, HashFun, ExtractKey, EqualKey, Alloc>::operator++()
	{
		const node* old = cur;
		cur = cur->next;
		if (!cur)
		{
			size_type bucket = ht->bkt_num(old->val);
			while (!cur && ++bucket < ht->buckets.size())
			{
				cur = ht->buckets[bucket];
			}

		}

		return *this;

	}

	template<class Value, class Key, class HashFun,
	class ExtractKey, class EqualKey, class Alloc>
		__hashtable_const_iterator<Value, Key, HashFun, ExtractKey, EqualKey, Alloc>
		__hashtable_const_iterator<Value, Key, HashFun, ExtractKey, EqualKey, Alloc>::operator++(int)
	{
		const_iterator tmp = *this;
		++*this;
		return tmp;
	}

	static const int __stl_num_primes = 28;
	static const unsigned long __stl_prime_list[__stl_num_primes] =
	{
		53, 97, 193, 389, 769,
		1543, 3079, 6151, 12289, 24593,
		49157, 98317, 196613, 393241, 786433,
		1572869, 3145739, 6291469, 12582917, 25165843,
		50331653, 100663319, 201326611, 402653189, 805306457,
		1610612741, 3221225473ul, 4294967291ul
	};

	inline unsigned long __stl_next_prime(unsigned long n)
	{
		const unsigned long* first = __stl_prime_list;
		const unsigned long* last = __stl_prime_list + __stl_num_primes;
		const unsigned long* pos = JMM_STL::lower_bound(first, last, n);
		return pos == last ? *(last - 1) : *pos;
	}

	
	template<class Value, class Key, class HashFun,
	class ExtractKey, class EqualKey, class Alloc>
	class hashtable
	{
	public:
		typedef HashFun hasher;
		typedef EqualKey key_equal;
		typedef Value value_type;
		typedef Key key_type;

		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		typedef value_type* pointer;
		typedef const value_type* const_pointer;
		typedef value_type& reference;
		typedef const value_type& const_reference;

	private:
		hasher hash;
		key_equal equals;
		ExtractKey get_key;

		typedef __hashtable_node<Value> node;
		typedef simple_alloc<node, Alloc> node_allocator;
		vector<node*, Alloc> buckets;
		size_type num_elements;


	public:

		

		typedef typename __hashtable_iterator<Value, Key, HashFun, ExtractKey, EqualKey, Alloc> iterator;
		typedef typename __hashtable_const_iterator<Value, Key, HashFun, ExtractKey, EqualKey, Alloc> const_iterator;

		friend struct
			__hashtable_iterator < Value, Key, HashFun, ExtractKey, EqualKey, Alloc >;

		friend struct
			__hashtable_const_iterator < Value, Key, HashFun, ExtractKey, EqualKey, Alloc >;

	public:



		hashtable(size_type n,
			const HashFun& hf, const EqualKey& eql) :hash(hf), equals(eql), get_key(ExtractKey()), num_elements(0)
		{
			initialize_buckets(n);
			

		}

		iterator begin()
		{
			for (size_type n = 0; n < buckets.size(); ++n)
			{
				if (buckets[n])
				{
					return iterator(buckets[n], this);
				}
			}

			return end();
		}

		iterator end()
		{
			return iterator(0, this);
		}

		const_iterator begin() const
		{
			for (size_type n = 0; n < buckets.size(); ++n)
			{
				if (buckets[n])
				{
					return const_iterator(buckets[n], this);
				}
			}

			return end();
		}

		const_iterator end() const
		{
			return const_iterator(0, this);
		}


		size_type bucket_count() const
		{
			return buckets.size();
		}

		size_type max_bucket_count() const
		{
			return __stl_prime_list[__stl_num_primes - 1];
		}


		pair<iterator, bool> insert_unique(const value_type& obj)
		{
			resize(num_elements + 1);
			return insert_unqiue_noresize(obj);

		}

		iterator insert_equal(const value_type& obj)
		{
			resize(num_elements + 1);
			return insert_equal_noresize(obj);
		}

		size_type size()
		{
			return num_elements;
		}


		size_type elems_in_bucket(size_type bucket) const
		{
			size_type result = 0;
			for (node* cur = buckets[bucket]; cur; cur = cur->next)
			{
				++result;
			}

			return result;
		}

		void clear();

		void copy_from(const hashtable& ht);

		iterator find(const key_type& key)
		{
			size_type n = bkt_num_key(key);
			node* first;
			for (first = buckets[n]; first&&!equals(get_key(first->val), key); first = first->next){}
			return iterator(first, this);
		}

		const_iterator find(const key_type& key) const
		{
			size_type n = bkt_num_key(key);
			const node* first;
			for (first = buckets[n]; first&&!equals(get_key(first->val), key); first = first->next){}
			return const_iterator(first, this);
		}

		size_type count(const key_type& key) const
		{
			size_type result = 0;

			const size_type n = bkt_num_key(key);
		
			for (const node*first = buckets[n]; first; first = first->next){
				if (equals(get_key(first->val), key))
				{
					++result;
				}
			}

			return result;
		
		}

	private:

		node* new_node(const value_type& obj)
		{
			node* n = node_allocator::allocate();
			n->next = 0;
			try
			{
				construct(&n->val, obj);
				return n;
			}
			catch (...)
			{
				node_allocator::deallocate(n);
			}
		}

		void delete_node(node *n)
		{
			destroy(&n->val);
			node_allocator::deallocate(n);
		}


		size_type next_size(size_type n) const
		{
			return __stl_next_prime(n);
		}

		void initialize_buckets(size_type n)
		{
			const size_type n_buckets = next_size(n);
			buckets.reserve(n_buckets);
			buckets.insert(buckets.end(), n_buckets, (node*)0);
			num_elements = 0;
		}

		pair<iterator, bool> insert_unqiue_noresize(const value_type& obj);
		iterator insert_equal_noresize(const value_type& obj);

		void resize(size_type num_elements_hint);

		size_type bkt_num(const value_type& obj, size_t n) const
		{
			return bkt_num_key(get_key(obj), n);

		}

		size_type bkt_num(const value_type& obj) const
		{
			return bkt_num_key(get_key(obj));
		}

		size_type bkt_num_key(const key_type& key) const
		{
			return bkt_num_key(key, buckets.size());
		}


		size_type bkt_num_key(const key_type& key, size_t n) const
		{
			
			return hash(key) % n;
		}
	};


	template <class V, class K, class HF, class Ex, class Eq, class A>
	void hashtable<V, K, HF, Ex, Eq, A>::resize(size_type num_elements_hint)
	{
		const size_type old_n = buckets.size();
		if (num_elements_hint > old_n)
		{
			const size_type n = next_size(num_elements_hint);
			if (n > old_n)
			{
				vector<node*, A> tmp(n, (node*)0);
				try
				{
					for (size_type bucket = 0; bucket < old_n; ++bucket)
					{
						node* first = buckets[bucket];
						while (first)
						{
							size_type new_bucket = bkt_num(first->val, n);
							buckets[bucket] = first->next;
							first->next = tmp[new_bucket];
							tmp[new_bucket] = first;
							first = buckets[bucket];
						}
					}

					buckets.swap(tmp);
				}
				catch (...)
				{
				}
			}
		}
	}

	template <class V, class K, class HF, class Ex, class Eq, class A>
	pair<typename hashtable<V, K, HF, Ex, Eq, A>::iterator, bool>
		hashtable<V, K, HF, Ex, Eq, A>::insert_unqiue_noresize(const value_type& obj)
	{
		const size_type n = bkt_num(obj);
		node* first = buckets[n];

		for (node* cur = first; cur; cur = cur->next)
		{
			if (equals(get_key(cur->val), get_key(obj)))
			{
				return pair<iterator, bool>(iterator(cur, this), false);
			}
		
		}

		node* tmp = new_node(obj);
		tmp->next = first;
		buckets[n] = tmp;
		++num_elements;
		return pair<iterator, bool>(iterator(tmp, this), true);
	}

	template <class V, class K, class HF, class Ex, class Eq, class A>
	typename hashtable<V, K, HF, Ex, Eq, A>::iterator
		hashtable<V, K, HF, Ex, Eq, A>::insert_equal_noresize(const value_type& obj)
	{
		const size_type n = bkt_num(obj);
		node* first = buckets[n];

		for (node* cur = first; cur; cur = cur->next)
		{
			if (equals(get_key(cur->val), get_key(obj)))
			{
				node* tmp = new_node(obj);
				tmp->next = cur->next;
				cur->next = tmp;
				++num_elements;
				return iterator(tmp, this);
			}

		}

		node* tmp = new_node(obj);
		tmp->next = first;
		buckets[n] = tmp;
		++num_elements;
		return iterator(tmp, this);
	}

	template <class V, class K, class HF, class Ex, class Eq, class A>
	void hashtable<V, K, HF, Ex, Eq, A>::clear()
	{
		for (size_type i = 0; i < buckets.size(); ++i)
		{
			node* cur = buckets[i];
			node* next = 0;
			while (cur!=0)
			{
				next = cur->next;
				delete_node(cur);
				cur = next;
			}
			buckets[i] = 0;
		}

		num_elements = 0;
	}

	template <class V, class K, class HF, class Ex, class Eq, class A>
	void hashtable<V, K, HF, Ex, Eq, A>::copy_from(const hashtable& ht)
	{
		clear();
		buckets.reserve(ht.buckets.size());

		buckets.insert(buckets.end(), ht.buckets.size(), (node*)0);
		try
		{
			for (size_type n = 0; i < ht.buckets.size(); ++i)
			{
				if (const node*cur = ht.buckets[i])
				{
					node* copy = new_node(cur->val);
					buckets[i] = copy;
					for (node* next = cur->next; next; cur = next, next = cur->next)
					{
						copy->next = new_node(next->val);
						copy = copy->next;
					}
				}
			}

			num_elements = ht.num_elements;
		}
		catch (...)
		{
			clear();
		}

	}
}

#endif