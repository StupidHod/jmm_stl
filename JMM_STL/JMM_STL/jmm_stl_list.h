#ifndef __JMM_STL_LIST
#define __JMM_STL_LIST

#include "jmm_stl_iterator.h"
#include "jmm_memory.h"


namespace JMM_STL
{
	template <class T>
	struct __list_node
	{
		typedef void* void_pointer;
		void_pointer prev;
		void_pointer next;
		T data;
	};

	template <class T, class Ref, class Ptr>
	struct  __list_iterator
	{
		typedef __list_iterator<T, T&, T*> iterator;
		typedef __list_iterator<T, const T&, const T*> const_iterator;
		typedef __list_iterator<T, Ref, Ptr> self;

		typedef bidirectional_iterator_tag iterator_category;
		typedef T value_type;
		typedef Ptr pointer;
		typedef Ref reference;
		typedef __list_node<T>* link_type;
		typedef size_t	size_type;
		typedef ptrdiff_t difference_type;


		link_type node;

		__list_iterator(link_type x) :node(x){}
		__list_iterator(){}
		__list_iterator(const iterator& x) :node(x.node){}

		bool operator==(const self& x) const { return node == x.node };
		bool operator!=(const self&x) const { return node != x.node };


		reference operator*() const { return (*node).data };

		pointer operator->() const { return &(operator*()) };


		self& operator++()
		{
			
		
			node = (link_type)(*node).next;

			return *this;
		
		}

		self operator++(int)
		{
			self tmp = *this;
			++*this;
			return tmp;
		


		}


		self& operator--()
		{
		
			node = (link_type)(*node).prev

			return *this;
		
		}


		self operator--(int)
		{
		
			self tmp = *this;

			--(*this);

			return tmp;
		
		}
	};

	template <class T, class Alloc = alloc>
	class list
	{
	protected:
		typedef __list_node<T> list_node;
	public:
		typedef list_node* link_type;

		typedef __list_iterator<T, T&, T*> iterator;
		typedef __list_iterator<T, const T&, const T*> const_iterator;


	public:
		typedef T value_type;
		typedef value_type* pointer;
		typedef const value_type* const_pointer;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef list_node* link_type;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;


	protected:
		link_type node;


	public:
		iterator begin()
		{
			return (link_type)((*node).next);

		}

		iterator end()
		{
			return node;

		}

		bool empty() const
		{
			return node->next == node;

		}

		size_type size() const
		{
			size_type result = 0;
			distance(begin(), end(), result);

			return result;

		}


		reference front(){

			return *begin();

		}


		reference back()
		{


			return *(--end());

		}

		typedef simple_alloc<list_node, Alloc> list_node_allocater;

	protected:

		link_type get_node()
		{

			return list_node_allocater::allocate();

		}


		void put_node(link_type p)
		{
		
			list_node_allocater::deallocater(p);
		
		}

		link_type create_node(const T& x)
		{
		
			link_type p = get_node();

			construct(&p->data, x);

			return p;
		
		}


		void destroy_node(link_type p)
		{

			destroy(p->data);

			put_node(p);

		}

		void empty_initialize()
		{

			node = get_node();
			node->next = node;
			node->prev = node;

		}

		
	
		
	public:
			
		list()
		{

			empty_initialize();

		}

		void push_back(const T& x)
		{

			insert(end(), x);
		
		
		}

		iterator insert(iterator position, const T& x)
		{
			link_type tmp = create_node(x);

			tmp->next = position.node;
			tmp->prev = position.node->prev;


			(link_type(position.node->prev))->next = tmp;
			position.node->prev = tmp;
			return tmp;

		
		}


		void transfer(iterator position, iterator first, iterator last)
		{
		
			if (position != last)
			{
				(*link_type((*last.node).prev)).next = position.node;
				(*link_type((*first.node).prev)).next = last.node;
				(*link_type((*position.node).prev)).next = first.node;
				link_type tmp = link_type((*position.node).prev);
				(*position.node).prev = (*last.node).prev;
				(*last.node).prev = first.node->prev;
				(*first.node).prev = tmp;
			}
		
		
		}

		void splice(iterator position, list&x)
		{
			if (!x.empty())
			{
				transfer(position, x.begin(), x.end());

			}
		
		
		}

		void splice(iterator position, list&, iterator i)
		{
			iterator j = i;
			++j;
			if (position == j || position == i)return;

			transfer(position, i, j);
		
		}


		void splice(iterator position, list&, iterator first, iterator last)
		{
		
			if (first != last)
			{
				transfer(position, first, last);
			}
		
		}

		void merge(list &x)
		{
		
			iterator first1 = begin();
			iterator last1 = end();
			iterator first2 = begin();
			iterator last2 = end();


			while (first1!=last1&&first2!=last2)
			{
				if (*first1 > *first2)
				{
					iterator next = first2;

					splice(first1, first2, ++next);

					first2 = next;
				}
				else
				{
					++first1;
				}

			}

			if (first2 != last2)
			{
				transfer(last1, first2, last2);
			}
		
		}
		/*
		void sort()
		{
		
			if (node->next == node || link_type(node->next)->next = node)
			{
				return;
			
			}


			list<T, Alloc> carry;
			list<T, Alloc> counter[64];

			int fill = 0;

			while (!empty())
			{
				carry.splice(carry.begin(), *this, begin());
			
				int i = 0;
				while (i < fill && !counter[i].empty())
				{
					counter[i].merge(carry);

				}

			
			}
		
		
		}*/

	};


	
}

#endif