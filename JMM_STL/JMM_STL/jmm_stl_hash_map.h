#ifndef __JMM_STL_HASH_MAP
#define __JMM_STL_HASH_MAP

#include "jmm_stl_hash_fun.h"
#include "jmm_stl_hashtable.h"
#include "jmm_stl_alloc.h"
#include "jmm_stl_function.h"
#include "jmm_stl_pair.h"


namespace JMM_STL
{
	template <class Key, class T, class HashFun = hash<Key>, class EqualKey = equal_to<Key>, class Alloc = alloc>
	class hash_map
	{
	private:
		typedef hashtable < pair<const Key, T>, Key, HashFun,
			select1st<pair<const Key, T>>, EqualKey, Alloc > ht;

		ht rep;

	public:
		typedef typename ht::key_type key_type;
		typedef T data_type;
		typedef T mapped_type;
		typedef typename ht::value_type value_type;
		typedef typename ht::hasher hasher;
		typedef typename ht::key_equal key_equal;


		typedef typename ht::size_type size_type;
		typedef typename ht::difference_type difference_type;
		typedef typename ht::pointer pointer;
		typedef typename ht::const_pointer const_pointer;
		typedef typename ht::reference reference;
		typedef typename ht::const_reference const_reference;

		typedef typename ht::iterator iterator;
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
		hash_map() :rep(100, hasher(), key_equal()){}
		explicit hash_map(size_type n) :rep(n, hasher(), key_eq()){}
		hash_map(size_type n, const hasher& hf) : rep(n, hf, key_eq()){}
		hash_map(size_type n, const hasher& hf, const key_equal& eql) :rep(n, hf, eql){}


		template<class InputIterator>
		hash_map(InputIterator first, InputIterator last)
			: rep(100, hasher(), key_eq())
		{
			rep.insert_unique(first, last);
		}

		template<class InputIterator>
		hash_map(InputIterator first, InputIterator last, size_type n) :
			rep(n, hasher(), key_eq())
		{
			rep.insert_unique(first, last);
		}

		template<class InputIterator>
		hash_map(InputIterator first, InputIterator last, size_type n, const hasher& hf) :
			rep(n, hf, key_eq())
		{
			rep.insert_unique(first, last);
		}


		template<class InputIterator>
		hash_map(InputIterator first, InputIterator last, size_type n, const hasher& hf, const key_equal& eq) :
			rep(n, hf, eq)
		{
			rep.insert_unique(first, last);
		}


	public:
		size_type size() const
		{
			return rep.size();
		}

		size_type max_size()
		{
			return rep.max_size();
		}

		bool empty()
		{
			return rep.empty();
		}


		void swap(hash_map& hs)
		{
			rep.swap(hs.rep);
		}

		friend bool operator==(const hash_map&, const hash_map&);

		iterator begin()
		{
			return rep.begin();
		}

		iterator end()
		{
			return rep.end();
		}

		const_iterator begin() const
		{
			return rep.begin();
		}

		const_iterator end() const
		{
			return rep.end();
		}

	public:

		pair<iterator, bool> insert(const value_type& obj)
		{
			return rep.insert_unique(obj);
		}

		template<class InputIterator>
		void insert(InputIterator first, InputIterator last)
		{
			rep.insert_unique(first, last);
		}

		pair<iterator, bool> insert_noresize(const value_type& obj)
		{
			return rep.insert_unqiue_noresize(obj);
		}

		iterator find(const key_type& key)
		{
			return rep.find(key);
		}


		const_iterator find(const key_type* key) const
		{
			return rep.find(key);
		}

		T& operator[](const key_type& key)
		{
			return rep.find_or_insert(value_type(key, T())).second;
		}

		size_type count(const key_type& key) const
		{
			return rep.count(key);
		}

		pair<iterator, iterator> equal_range(const key_type& key)
		{
			return rep.equal_range(key);
		}

		pair<const_iterator, const_iterator> equal_range(const key_type& key) const
		{
			return rep.equal_range(key);
		}


		size_type erase(const key_type& key)
		{
			return rep.erase(key);
		}

		void erase(iterator it)
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


		size_type  bucket_count() const
		{
			return rep.bucket_count();
		}

		size_type max_bucket_count() const
		{
			return rep.max_bucket_count();
		}

		size_type elems_in_bucket(size_type n)
		{
			return rep.elems_in_bucket(n);
		}
	};


	template<class Key, class T, class HashFun, class EqualKey, class Alloc>
	inline bool operator==(hash_map<Key, T, HashFun, EqualKey, Alloc>& hm1,
		hash_map<Key, T, HashFun, EqualKey, Alloc>& hm2)
	{
		return hm1.rep == hm1.rep;
	}
}

#endif