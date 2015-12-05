#ifndef __JMM_STL_RB_TREE
#define __JMM_STL_RB_TREE

#include <stddef.h>
#include "jmm_stl_iterator.h"
#include "jmm_stl_alloc.h"
#include "jmm_stl_allocator.h"
#include "jmm_stl_construct.h"
#include "jmm_stl_uninitialized.h"
#include "jmm_stl_pair.h"


namespace JMM_STL
{
	typedef bool __rb_tree_color_type;
	const __rb_tree_color_type __rb_tree_red = false;
	const __rb_tree_color_type __rb_tree_black = true;

	struct  __rb_tree_node_base
	{
		typedef __rb_tree_color_type color_type;
		typedef __rb_tree_node_base* base_ptr;

		color_type color;
		base_ptr parent;
		base_ptr left;
		base_ptr right;
	
		static base_ptr minimum(base_ptr x)
		{
			while (x->left!=0)
			{
				x = x->left;
			}

			return x;
		}


		static base_ptr maximum(base_ptr x)
		{
			while (x->right!=0)
			{
				x = x->right;
			}

			return x;
		}

	
	};

	template <class Value>
	struct __rb_tree_node:public __rb_tree_node_base
	{
		typedef __rb_tree_node<Value>* link_type;
		Value value_field;

	};


	struct __rb_tree_base_iterator
	{
		typedef __rb_tree_node_base::base_ptr base_ptr;
		typedef bidirectional_iterator_tag iterator_category;
		typedef ptrdiff_t difference_type;

		base_ptr node;

		void increment()
		{
			if (node->right != NULL)
			{
				node = node->right;
				while (node->left!=0)
				{
					node = node->left;

				}
			}
			else
			{
				base_ptr y = node->parent;
				while (node==y->right)
				{
					node = y;
					y = y->parent;

				}

				if (node->right != y)
				{
					node = y;
				}
			}
		}


		void decrement()
		{
			if (node->color == __rb_tree_red&&
				node->parent->parent == node)
			{
				node = node->right;
			} else if (node->left!=0)
			{
				base_ptr y = node->left;
				while (y->right!=0)
				{
					y = y->right;

				}
				node = y;

			}
			else
			{
				base_ptr y = node->parent;
				while (node ==y->left)
				{
					node = y;

					y = node->parent;

				}

				node = y;
			}
		}

	
	};


	template <class Value, class Ref, class Ptr>
	struct __rb_tree_iterator :public __rb_tree_base_iterator
	{

		typedef Value value_type;
		typedef Ref reference;
		typedef Ptr pointer;
		typedef __rb_tree_iterator<Value, Value&, Value*> iterator;
		typedef __rb_tree_iterator<Value ,const Value&, const Value*> const_iterator;
		typedef __rb_tree_iterator<Value, Ref, Ptr> self;
		typedef __rb_tree_node<Value>* link_type;


		__rb_tree_iterator(){}
		__rb_tree_iterator(link_type x){ node = x };
		__rb_tree_iterator(const iterator& it){ node = it.node };


		reference operator*() const
		{
			return link_type(node)->value_field;
		}


		pointer operator->() const
		{
			return &(operator*());
		}

		self& operator++()
		{
			increment();
			return this;
		}

		self operator++(int)
		{
			self tmp = this;
			increment();
			return tmp;
		}


		self& operator--()
		{
			decrement();
			return this;
		}

		self operator--(int)
		{
			self tmp = this;
			decrement();
			return tmp;
		}



	};


	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc=alloc>
	class rb_tree
	{
	protected:
		typedef void* void_pointer;
		typedef __rb_tree_node_base* base_ptr;
		typedef __rb_tree_node<Value> rb_tree_node;
		typedef simple_alloc<rb_tree_node, Alloc> rb_tree_node_allocator;
		typedef __rb_tree_color_type color_type;

	protected:
		typedef Key key_type;
		typedef Value value_type;
		typedef value_type* pointer;
		typedef const value_type* const_pointer;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef rb_tree_node* link_type;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;

	protected:
		link_type get_node()
		{
			return rb_tree_node_allocator::allocate();
		}

		void put_node(link_type p)
		{
			rb_tree_node_allocator::deallocate(p);
		}

		link_type create_node(const value_type& x)
		{
			link_type tmp = get_node();
			try
			{
				construct(&tmp->value_field, x);
			}
			catch (...)
			{

				put_node(tmp);
			}
		}


		link_type clone_node(link_type x)
		{
			link_type tmp = create_node(x->value_field);
			tmp->color = x->color;
			tmp->left = 0;
			tmp->right = 0;
			return tmp;
		}

		void destroy_node(link_type p)
		{
			destroy(&p->value_field);
			put_node(p);
		}

	protected:
		size_type node_count;
		link_type header;
		Compare key_compare;

		link_type& root() const
		{
			return (link_type&)header->parent;
		}

		link_type& left_most() const
		{
			return (link_type&)header->left;

		}


		link_type& right_most() const
		{
			return (link_type&)header->right;
		}

		static link_type& left(link_type x)
		{
			return (link_type&)(x->left);
		}

		static link_type& right(link_type x)
		{
			return (link_type&)(x->right);
		}

		static link_type& parent(link_type x)
		{
			return (link_type&)(x->parent);
		}

		static reference value(link_type x)
		{
			return x->value_field;
		}

		static const Key& key(link_type x)
		{
			return KeyOfValue()(value(x);
		}


		static color_type& color(link_type x)
		{
			return (color_type&)(x->color);
		}




		static link_type& left(base_ptr x)
		{
			return (link_type&)(x->left);
		}

		static link_type& right(base_ptr x)
		{
			return (link_type&)(x->right);
		}

		static link_type& parent(base_ptr x)
		{
			return (link_type&)(x->parent);
		}

		static reference value(base_ptr x)
		{
			return x->value_field;
		}

		static const Key& key(base_ptr x)
		{
			return KeyOfValue()(value(x);
		}


		static color_type& color(base_ptr x)
		{
			return (color_type&)(x->color);
		}


		static link_type minimum(link_type x)
		{
			return (link_type)__rb_tree_node_base::minimum(x);
		}


		static link_type maximum(link_type x)
		{
			return (link_type)__rb_tree_node_base::maximum(x);
		}

	public:
		typedef __rb_tree_iterator<value_type, reference, pointer> iterator;

	private:
		iterator __insert(base_ptr x, base_ptr y, const value_type& v);
		link_type __copy(link_type x, link_type p);
		void __erase(link_type x);
		void init()
		{
			header = get_node();
			color(header) = __rb_tree_red;

			root() = 0;
			left_most() = header;
			right_most() = header;
		}

		inline void __rb_tree_rebalance(__rb_tree_node_base* x, __rb_tree_node_base*& root)
		{
			x->color = __rb_tree_red;
			while (x!=root && x->parent->color == __rb_tree_red)
			{
				if (x->parent == x->parent->parent->left)

			}
		}


	public:

		rb_tree(const Compare& ccmp = Compare())
			:node_count(0), key_compare(comp)
		{
			init();
		}

		~rb_tree()
		{
			clear();
			put_node(header);
		}

		rb_tree<Key, Value, KeyOfValue, Compare, Alloc>&
			operator=(const rb_tree<Key, Value, KeyOfValue, Compare, Alloc>& x);

	public:

		Compare key_comp() const{

			return key_compare();
		}

		iterator begin()
		{
			return left_most();
		}

		iterator end()
		{
			return header;
		}

		bool empty() const
		{
			return node_count == 0;
		}

		size_type size() const
		{
			return node_count;
		}

		size_type max_size() const
		{
			return size_type(-1);
		}


	public:
		pair<iterator, bool> insert_unique(const value_type& x);
		iterator insert_equal(const value_type& x);
	};

	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator
		rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::insert_equal(const Value& v)
	{
		link_type y = header;
		link_type x = root();
		while (x!=0)
		{
			y = x;
			x = key_compare(KeyOfValue()(v), key(x)) ? left(x), right(x);

		}

		return __insert(x, v, v);
	}


	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	pair<typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator,bool>
		rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::insert_unique(const Value& x)
	{
		link_type y = header;
		link_type x = root();
		bool comp = true;

		while (x!=0)
		{
			y = x;
			comp = key_compare(KeyOfValue()(v), key(x));
			x = comp ? left(x) : right(x);
		}


		iterator j = iterator(y);
		if (comp)
		{
			if (j == begin())
			{
				return pair<iterator, bool>(__insert(x, y, v), true);
			}
			else
			{
				--j;
			}
		}

		if (key_compare(key(j.node), KeyOfValue()(v)))
		{
			return pair < iterator, bool)(__insert(x, y, v), true);
		}


		return pair<iterator, bool>(j, false);
	
	
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator
		rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::__insert(base_ptr x__, base_ptr y__, const Value& v)
	{
		link_type x = (link_type)x__;
		link_type y = (link_type)y__;
		link_type z;


		if (y == header || x != 0 || key_compare(KeyOfValue()(v), key(y)))
		{
			z = create_node(v);
			left(y) = z;
			if (y == header)
			{
				root() = z;
				right_most = z;
			}
			else if (y == left_most())
			{
				left_most() = z;
			}
		}
		else
		{
			z = create_node(v);
			right(y) = z;
			if (y == right_most())
			{
				right_most() = z;
			}
		}

		parent(z) = y;
		left(z) = 0;
		right(z) = 0;

		__rb_tree_rebalance(z, header->parent);
		++node_count;
		return iterator(z);

	}



	
}

#endif