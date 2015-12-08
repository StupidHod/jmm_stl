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
		__rb_tree_iterator(link_type x){ node = x; }
		__rb_tree_iterator(const iterator& it){ node = it.node; };


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
			self tmp = *this;
			increment();
			return tmp;
		}


		self& operator--()
		{
			decrement();
			return *this;
		}

		self operator--(int)
		{
			self tmp = *this;
			decrement();
			return tmp;
		}

		bool operator==(self x)
		{
			return x.node == node;
		}


		bool operator!=(self x)
		{
			return x.node != node;
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

			return tmp;
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
			return KeyOfValue()(value(x));
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
			return ((link_type)x)->value_field;
		}

		static const Key& key(base_ptr x)
		{
			return KeyOfValue()(value(x));
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
		typedef __rb_tree_iterator<value_type, const_reference, const_pointer> const_iterator;
		typedef reverse_iterator<iterator> reverse_iterator;
		typedef reverse_iterator<const_iterator> const_reverse_iterator;

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



	public:

		rb_tree(const Compare& comp = Compare())
			:node_count(0), key_compare(comp)
		{
			init();
		}

		~rb_tree()
		{
			//clear();
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


		reverse_iterator rbegin()
		{
			return reverse_iterator(end());
		}


		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(end());
		}

		reverse_iterator rend()
		{
			return reverse_iterator(begin());
		}

		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(begin());
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

		void swap(rb_tree<Key, Value, KeyOfValue, Compare, Alloc>& t)
		{
			JMM_STL::swap(header, t.header);
			JMM_STL::swap(node_count, t.node_count);
			JMM_STL::swap(key_compare, t.key_compare);
		}


	public:
		pair<iterator, bool> insert_unique(const value_type& x);
		iterator insert_equal(const value_type& x);

		iterator insert_unique(iterator position, const value_type& x);
		iterator insert_equal(iterator position, const value_type& x);

		template<class InputIterator>
		void insert_unique(InputIterator first, InputIterator last);
		template<class InputIterator>
		void insert_equal(InputIterator first, InputIterator last);
		

		void erase(iterator position);
		size_type erase(const key_type& x);
		void erase(iterator first, iterator last);
		void erase(const key_type* first, const key_type* last);
		void clear()
		{
			if (node_count != 0)
			{
				__erase(root());
				left_most() = header;
				root() = 0;
				right_most() = header;
				node_count = 0;
			
			}
		}
		
		iterator find(const Key& k);
		pair<iterator, iterator> equal_range(const key_type& x);
		pair<const_iterator, const_iterator> equal_range(const key_type& x) const;
		iterator lower_bound(const key_type& x);
		const_iterator lower_bound(const key_type& x)const;
		iterator upper_bound(const key_type& x);
		const_iterator upper_bound(const key_type& x) const;

	};


	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator
		rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::lower_bound(const Key& k)
	{
		link_type y = header;
		link_type x = root();

		while (x!=0)
		{
			if (!key_compare(key(x), k))
			{
				y = x, x = left(x);
			}
			else
			{
				x = right(x);
			}
		}

		return iterator(y);
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::const_iterator
		rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::lower_bound(const Key& k) const
	{
		link_type y = header;
		link_type x = root();

		while (x != 0)
		{
			if (!key_compare(key(x), k))
			{
				y = x, x = left(x);
			}
			else
			{
				x = right(x);
			}
		}

		return const_iterator(y);
	}



	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator
		rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::upper_bound(const Key& k)
	{
		link_type y = header;
		link_type x = root();

		while (x != 0)
		{
			if (key_compare(k, key(x)))
			{
				y = x, x = left(x);
			}
			else
			{
				x = right(x);
			}
		}

		return iterator(y);
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::const_iterator
		rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::lower_bound(const Key& k) const
	{
		link_type y = header;
		link_type x = root();

		while (x != 0)
		{
			if (key_compare(k, key(x)))
			{
				y = x, x = left(x);
			}
			else
			{
				x = right(x);
			}
		}

		return const_iterator(y);
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	inline pair<typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator,
		typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator>
		rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::equal_range(const Key& k)
	{
		return pair<iterator, iterator>(lower_bound(k), upper_bound(k));
	}


	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	inline pair<typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::const_iterator,
		typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::const_iterator>
		rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::equal_range(const Key& k) const
	{
		return pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k));
	}

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

		return __insert(x, y, v);
	}


	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	pair<typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator,bool>
		rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::insert_unique(const Value& v)
	{
		link_type y = header;
		link_type x = root();
		bool comp = true;

		while (x != 0)
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
			return pair < iterator, bool>(__insert(x, y, v), true);
		}


		return pair<iterator, bool>(j, false);


	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator
		rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::insert_unique(iterator position, const Value& v)
	{
		if (position.node = header->left)
		{
			if (size() > 0 && key_compare(KeyOfValue()(v), key(position.node)))
			{
				return __insert(position.node, position.node, v);
			}
			else
			{
				return insert_unique(v).first;
			}
		}
		else if (position.node == header)
		{
			if (key_compare(key(right_most()), KeyOfValue()(v), key(position.node)))
			{
				return __insert(0, right_most(), v);
			}
			else
			{
				return insert_unique(v).first;
			}
		}
		else
		{
			iterator before = position;
			--before;
			if (key_compare(key(before.node), KeyOfValue()(v))
				&& key_compare(KeyOfValue()(v), key(position.node))
			{
				if (right(before.node) == 0)
				{
					return __insert(0, before, node, v);
				}
				else
				{
					return __insert(position.node, position.node, v);
				}
			}
			else
			{
				return insert_unqiue(v).first;
			}

		}
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator
		rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::insert_equal(iterator position, const Value& v)
	{
		if (position.node = header->left)
		{
			if (size() > 0 && key_compare(KeyOfValue()(v), key(position.node)))
			{
				return __insert(position.node, position.node, v);
			}
			else
			{
				return insert_equal(v);
			}
		}
		else if (position.node == header)
		{
			if (!key_compare(KeyOfValue()(v), key(right_most())))
			{
				return __insert(0, right_most(), v);
			}
			else
			{
				return insert_equal(v);
			}
		}
		else
		{
			iterator before = position;
			--before;
			if (!key_compare(key(before.node), KeyOfValue()(v))
				&& !key_compare(KeyOfValue()(v), key(position.node))
			{
				if (right(before.node) == 0)
				{
					return __insert(0, before, node, v);
				}
				else
				{
					return __insert(position.node, position.node, v);
				}
			}
			else
			{
				return insert_equal(v);
			}

		}
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	template<class InputIterator>
	void rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::insert_equal(InputIterator first, InputIterator last)
	{
		for (; first != last; ++first)
		{
			insert_equal(*first);
		}
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	template<class InputIterator>
	void rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::insert_unique(InputIterator first, InputIterator last)
	{
		for (; first != last; ++first)
		{
			insert_unique(*first);
		}
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
				right_most() = z;
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

	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	void rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::__erase(link_type x)
	{
		while (x!=0)
		{
			__erase(right(x));
			link_type y = left(x);
			destroy_node(x);
			x = y;
		}
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	void rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::erase(iterator first, iterator last)
	{
		if (first == begin() && last == end())
		{
			clear();
		}
		else
		{
			while (first!=last)
			{
				erase(first++);
			}
		}
	}


	// in the first section, replace the erase node with real erased position
	// in the second section, rebalance the tree
	inline __rb_tree_node_base*
		__rb_tree_rebalance_for_erase(__rb_tree_node_base * z,
		__rb_tree_node_base*& root,
		__rb_tree_node_base*& leftmost,
		__rb_tree_node_base*& rightmost)
	{

		//real erase node
		__rb_tree_node_base* y = z;

		//real erase node's children
		__rb_tree_node_base* x = 0;
		__rb_tree_node_base* x_parent = 0;


		//to get the successor and its children of the node to erase
		if (y->left == 0)
		{
			x = y->right;
		}
		else
		{
			if (y->right == 0)
			{
				x = y->left;
			}
			else
			{
				y = y->right;
				while (y->left!=0)
				{
					y = y->left;

				}
				x = y->right;
			}
		}


		
		if (y != z)
		{
			//if z has two children, y is the next node of z and x is the right children of y, as y do not have left children
			//replace the position of y and z, z is the node to erase, y is the node be erased really

			z->left->parent = y;
			y->left = z->left;

			//if y is not z's direct children, erase node y and replace it with x
			if (y != z->right)
			{
				x_parent = y->parent;
				if (x)
				{
					//x is the only children of y, if x is not null, replace x's parent from z to y
					x->parent = y->parent;
					y->parent->left = x;
					y->right = z->right;
					z->right->parent = y;
				}
			}
			else
			{ 
				x_parent = y;
			}


			//replace z's position with y's node
			if (root == z)
			{
				root = y;
			}
			else if (z->parent->left == z)
			{
				z->parent->left = y;
			}
			else
			{
				z->parent->right = y;
			}

			y->parent = z->parent;
			JMM_STL::swap(y->color, z->color);
			y = z;

		}
		else
		{
			//if the number of z'children are not more than one, 
			//x is the right children of z if z's left children is null, or x is null
			//replace z with x

			x_parent = y->parent;
			if (x)
			{
				x->parent = y->parent;
			}

			if (root = z)
			{
				root = x;
			}
			else
			{
				
				// replace z's position with y's node
				if (z->parent->left == z)
				{
					z->parent->left = x;
				}
				else
				{
					z->parent->right = x;
				}

				if (leftmost == z)
				{
					if (z->right == 0)
					{
						leftmost = z->parent;
					}
					else
					{
						leftmost = __rb_tree_node_base::minimum(x);
					}
				}

				if (rightmost == z)
				{
					if (z->left == 0)
					{
						rightmost = z->parent;
					}
					else
					{
						rightmost = __rb_tree_node_base::maximum(x);
					}
				
				}



			}
			
		}

		if (y->color != __rb_tree_red)
		{
			//if the color of x is red, erase it directly, no need to do anythibg
			while (x!=root && (x == 0 || x->color == __rb_tree_black))
			{
				//if the color of x and y are all black
				if (x == x_parent->left)
				{
					// w is y's brother
					__rb_tree_node_base* w = x_parent->right;
					
					//if brother is red, LL rotate with node x_parent, set w with black, x_parent with red
					if (w->color == __rb_tree_red)
					{
						w->color = __rb_tree_black;
						x_parent->color = __rb_tree_red;
						__rb_tree_rotate_left(x_parent, root);
						w = x_parent->right;
					}


					// if w's children are all black, just set w's color with red 
					if ((w->left == 0 || w->left->color == __rb_tree_black) &&
						(w->right == 0 || w->right->color == __rb_tree_black))
					{
						w->color = __rb_tree_red;
						x = x->parent;
						x_parent = x_parent->parent;
					}
					else
					{
						//if w's children is 

						// w's right children is red, set w's left children with black, rotate right for w
						if (w->right == 0 || w->right->color == __rb_tree_black)
						{
							if (w->left)
							{
								w->left->color = __rb_tree_black;
							}
							w->color = __rb_tree_red;
							__rb_tree_rotate_right(w, root);
							w = x_parent->right;
						}
						w->color = x_parent->color;
						x_parent->color = __rb_tree_black;
						if (w->right)
						{
							w->right->color = __rb_tree_black;
						}
						__rb_tree_rotate_left(x_parent, root);
						break;
					}
				}
				else
				{
					__rb_tree_node_base* w = x->parent->left;
					if (w->color == __rb_tree_red)
					{
						w->color = __rb_tree_black;
						x_parent->color = __rb_tree_red;
						__rb_tree_rotate_right(x_parent, root);
						w = x->parent->left;
					}
					if ((w->right == 0 || w->right->color == __rb_tree_black) &&
						(w->left == 0 || w->left->color == __rb_tree_black))
					{
						w->color = __rb_tree_red;
						x = x_parent;
						x_parent = x_parent->parent;
					}
					else
					{
						if (w->left == 0 || w->left->color == __rb_tree_black)
						{
							if (w->right)
							{
								w->right->color = __rb_tree_black;
							}
							w->color = __rb_tree_red;
							__rb_tree_rotate_left(w, root);
							w = x_parent->left;
						}
						w->color = x_parent->color;
						x_parent->color = __rb_tree_black;
						if (w->left)
						{
							w->left->color = __rb_tree_black;
						}
						__rb_tree_rotate_right(x_parent, root);
						break;
					}
				}



				if (x)
				{
					x->color = __rb_tree_black;
				}

			}

		}

		return y;

	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	void rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::erase(iterator position)
	{
		link_type y = (link_type)__rb_tree_rebalance_for_erase(position.node,
			header->parent,
			header->left,
			header->right);

		destroy_node(y);
		--node_count;
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::size_type 
		rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::erase(const Key& x)
	{
		pair<iterator, iterator> p = equal_range(x);
		size_type n = 0;
		distance(p.first, p.second, n);
		erase(p.first, p.second);
		return n;
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator
		rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::find(const Key& k)
	{
		link_type y = header;
		link_type x = root();

		while (x!=0)
		{
			if (!key_compare(key(x), k))
			{
				y = x;
				x = left(x);
			}
			else
			{
				x = right(x);
			}
		}

		iterator j = iterator(y);
		return (j == end() || key_compare(k, key(j.node))) ? end() : j;
	}

	inline void __rb_tree_rotate_left(__rb_tree_node_base* x, __rb_tree_node_base*& root)
	{
		__rb_tree_node_base* y = x->right;
		x->right = y->left;
		if (y->left != 0)
		{
			y->left->parent = x;
		}

		y->parent = x->parent;

		if (x == root)
		{
			root = y;
		}
		else if (x == x->parent->left)
		{
			x->parent->left = y;
		}
		else
		{
			x->parent->right = y;
		}

		y->left = x;
		x->parent = y;
	}


	inline void __rb_tree_rotate_right(__rb_tree_node_base* x,
		__rb_tree_node_base*& root)
	{
		__rb_tree_node_base* y = x->left;


		x->left = y->right;

		if (y->right != 0)
		{
			y->right->parent = x;
		}

		y->parent = x->parent;

		if (x == root)
		{
			root = y;
		}
		else if (x == x->parent->right)
		{
			x->parent->right = y;
		}
		else
		{
			x->parent->left = y;
		}

		x->parent = y;

		y->right = x;



	}


	inline void __rb_tree_rebalance(__rb_tree_node_base* x, __rb_tree_node_base*& root)
	{
		x->color = __rb_tree_red;
		while (x != root && x->parent->color == __rb_tree_red)
		{
			if (x->parent == x->parent->parent->left)
			{
				__rb_tree_node_base* y = x->parent->parent->right;
				if (y&&y->color == __rb_tree_red)
				{
					x->parent->color = __rb_tree_black;
					y->color = __rb_tree_black;
					x->parent->parent->color = __rb_tree_red;
					x = x->parent->parent;
				}
				else
				{
					if (x == x->parent->right)
					{
						x = x->parent;
						__rb_tree_rotate_left(x, root);
					}

					x->parent->color = __rb_tree_black;
					x->parent->parent->color = __rb_tree_red;
					__rb_tree_rotate_right(x->parent->parent, root);
				}
			}
			else
			{
				__rb_tree_node_base* y = x->parent->parent->left;
				if (y&&y->color == __rb_tree_red)
				{
					x->parent->color == __rb_tree_black;
					y->color = __rb_tree_black;
					x->parent->parent->color = __rb_tree_red;
					x = x->parent->parent;
				}
				else
				{
					if (x == x->parent->left)
					{
						x = x->parent;
						__rb_tree_rotate_right(x, root);
					}

					x->parent->color = __rb_tree_black;
					x->parent->parent->color = __rb_tree_red;
					__rb_tree_rotate_left(x->parent->parent, root);
				}
			}

		}
		root->color = __rb_tree_black;
	}


}

#endif