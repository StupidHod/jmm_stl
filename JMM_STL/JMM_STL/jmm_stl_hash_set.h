#ifndef __JMM_STL_HASH_SET
#define __JMM_STL_HASH_SET

#include "jmm_stl_hash_fun.h"
#include "jmm_stl_hashtable.h"
#include "jmm_stl_alloc.h"
#include "jmm_stl_function.h"

namespace JMM_STL
{

	template<class Value, class HashFun = hash<Value>, class EqualKey = equal_to<Value>, class Alloc = alloc>
	class hash_set
	{
	private:
		typedef hashtable<Value, Value, HashFun, identity<Value>, EqualKey, Alloc> ht;
		ht rep;

	public:
		typedef typename ht::key_type key_type;
		typedef typename ht::value_type value_type;
		typedef typename ht::hasher hasher;
		typedef typename ht::key_equal key_equal;

		typedef typename ht::size_type size_type;
		typedef typename ht::difference_type difference_type;
		typedef typename ht::const_pointer pointer;
		typedef typename ht::const_pointer const_pointer;
		typedef typename ht::const_reference reference;
		typedef typename ht::const_reference const_reference;


		typedef typename ht::const_iterator iterator;
		typedef typename ht::const_iterator const_iterator;


		hasher hash_funct() const
		{
			return rep.hash_funct();
		}

		key_equal key_eq() const
		{
			return rep.key_eq();
		}


	public:
		hash_set() :rep(100, hasher(), key_equal()){}
		explicit hash_set(size_type n) :rep(n, hasher(), key_equal()){}
		hash_set(size_type n, const hasher& hf) :rep(n, hf, key_equal()){}
		hash_set(size_type n, const hasher& hf, const key_equal& eql) :rep(n, hf, eql){}

		template<class InputIterator>
		hash_set(InputIterator first, InputIterator last) :
			rep(100, hasher(), key_equal())
		{
			rep.insert_unique(first, last);
		}


		template<class InputIterator>
		hash_set(InputIterator first, InputIterator last, size_type n) :
			rep(n, hasher(), key_equal())
		{
			rep.insert_unique(first, last);
		}

		template<class InputIterator>
		hash_set(InputIterator first, InputIterator last, size_type n, const hasher& hf) :
			rep(n, hf, key_equal())
		{
			rep.insert_unique(first, last);
		}


		template<class InputIterator>
		hash_set(InputIterator first, InputIterator last, size_type n, const hasher& hf, const key_equal& eql) :
			rep(n, hf, eql)
		{
			rep.insert_unique(first, last);
		}

	public:
		size_type size() const
		{
			return rep.size();
		}

		size_type max_size() const
		{
			return rep.max_size();
		}


		bool empty()
		{
			return rep.empty();
		}


		void swap(hash_set& hs)
		{
			rep.swap(hs.rep);
		}


		friend bool operator==(const hash_set&, const hash_set&);
		iterator begin()
		{
			return rep.begin();
		}

		iterator end()
		{
			return rep.end();
		}

		const_iterator end() const
		{
			return rep.end();
		}

	public:
		pair<iterator, bool> insert(const value_type& obj)
		{
			pair<typename ht::iterator, bool> p = rep.insert_unique(obj);
			return pair<iterator, bool>(p.first, p.second);
		}


		template<class InputIterator>
		void insert(InputIterator first, InputIterator last)
		{
			rep.insert_unique(first, last);
		}

		pair<iterator, bool> insert_noresize(const value_type& obj)
		{
			pair<typename ht::iterator, bool> p = rep.insert_unqiue_noresize(obj);

			return pair<iterator, bool>(p.first, p.second);
		}

		iterator find(const key_type& key) const
		{
			return rep.find(key);
		}

		size_type count(const key_type& key) const
		{
			return rep.count(key);
		}

		pair<iterator, iterator> equal_range(const key_type& key) const
		{
			return rep.equal_range(key);
		}

		size_type erase(const key_type& key)
		{
			return rep.erase(key);
		}


		void erase(iterator& it)
		{
			rep.erase(it);
		}

		void erase(iterator f, iterator l)
		{
			rep.erase(f, l);
		}

		void clear()
		{
			rep.clear();
		}


	public:

		void resize(size_type hint)
		{
			rep.resize(hint);
		}

		size_type bucket_count() const
		{
			return rep.bucket_count();
		}

		size_type max_bucket_count() const
		{
			return rep.max_bucket_count();
		}

		size_type elems_in_bucket(size_type n) const
		{
			return rep.elems_in_bucket(n);
		}

	};


	template<class Value, class HashFun, class EqualKey, class Alloc>
	inline bool operator==(const hash_set < Value, HashFun, EqualKey, Alloc>& hs1,
		const hash_set < Value, HashFun, EqualKey, Alloc>& hs2)
	{
		return hs1.rep == hs2.rep;
	}
}



#endif