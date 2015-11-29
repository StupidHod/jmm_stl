#ifndef JMM_STL_DEQUE
#define JMM_STL_DEQUE

#include "jmm_memory.h"
#include "jmm_stl_iterator.h"
#include "jmm_stl_algobase.h"


namespace JMM_STL
{
	inline size_t __deque_buf_size(size_t n, size_t sz)
	{

		return n != 0 ? n : (sz < 512 ? size_t(512 / sz) : size_t(1));
	
	}

	template <class T, class Ref, class Ptr, size_t BufSiz>
	struct __deque_iterator
	{
		typedef __deque_iterator<T, T&, T*, BufSiz>	iterator;
		typedef __deque_iterator<T, const T&, const T*, BufSiz> const_iterator;
		static size_t buff_size()
		{
		
			return __deque_buf_size(BufSiz, sizeof(T));
		
		}

	

		typedef random_access_iterator_tag iterator_category;
		typedef T value_type;
		typedef Ptr pointer;
		typedef Ref reference;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		typedef T** map_pointer;


		typedef __deque_iterator self;


		T* cur;
		T* first;
		T* last;
		map_pointer node;

		void set_node(map_pointer new_node)
		{
			node = new_node;
			first = *new_node;
			last = first + difference_type(buff_size());
		
		}

		reference operator*() const{
			

			return *cur;
		
		}

		pointer operator&() const
		{
		
			return &(operator*());
		
		}


		difference_type operator-(const self&x) const
		{
		
			return difference_type(buff_size()) * (node - x.node - 1) + (cur - first) + (x.last - x.cur);
		
		}


		self& operator++()
		{
			if (cur == last)
			{
				set_node(node + 1);
				cur = first;
			}

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
			if (cur == first)
			{
				set_node(node - 1);
				cur = last;
			}

			--cur;
			return *this;
		
		}


		self operator--(int)
		{
			self tmp = *this;
			--*this;
			return tmp;
		
		}


		self & operator+=(difference_type n)
		{
		
			difference_type offset = n + (cur - first);
			if (offset >= 0 && offset < difference_type(buff_size()))
			{
				cur += n;

			}
			else
			{
				difference_type node_offset =

					offset>0 ? offset / difference_type(buff_size())
					: -difference_type((-offset - 1) / buff_size()) - 1;

				set_node(node + node_offset);

				cur = first + (offset - node_offset * difference_type(buff_size()));
			}

			return *this;
		
		}


		self operator+(difference_type n) const
		{
		
			self tmp = *this;
			return tmp += n;
		
		}

		self& operator-=(difference_type n)
		{
		
			return *this += -n;
		
		}


		self operator-(difference_type n)
		{
		
			self tmp = *this;

			return tmp -= n;
		
		
		}


		reference operator[](difference_type n)const
		{
		
			return *(*this + n);
		
		}


		bool operator==(const self&x) const
		{
		
			return cur == x.cur;
		
		}

		bool operator!=(const self&x)const
		{
		
			return !(*this == x);
		
		}

		bool operator<(const self&x) const
		{
			return (node == x.node) ? (cur < x.cur) : (node < x.node);
		
		}

	};



	template <class T, class Alloc = alloc, size_t BufSiz = 0>
	class deque
	{


	public:
		typedef T value_type;
		typedef value_type* pointer;
		typedef const value_type* const_pointer;
		typedef value_type& reference;
		typedef const value_type& const_reference;
	//	typedef list_node* link_type;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;


		typedef __deque_iterator<T, T&, T*, BufSiz> iterator;
		typedef simple_alloc<value_type, Alloc> data_allocater;
		typedef simple_alloc<pointer, Alloc> map_allocater;


	protected:

		typedef pointer* map_pointer;
		


	protected:
		map_pointer map;
		size_type map_size;
		iterator start;
		iterator finish;
	//	map_pointer map;


	protected:
		pointer allocate_node()
		{
		
			return data_allocater::allocate(buffer_size());
		
		}

		pointer deallocate_node(pointer n)
		{
		
			return data_allocater::deallocate(n, buffer_size());
		
		}


	public:
		iterator begin()
		{
			return start;
		}


		iterator end()
		{
		
			return finish;
		
		}

		reference operator[](size_type n)
		{
		
			return start[difference_type(n)];
		
		}

		reference front()
		{
		
			return *start;
		
		}

		reference back()
		{
		
			iterator tmp = finish;
			--tmp;
			return *tmp;
		
		}


		size_type size() const
		{
		
			return finish - start;
		
		}

		size_type max_size() const
		{
		
			return size_type(-1);
		
		}

		bool empty() const
		{
		
			return finish == start;
		
		}


		static size_t buffer_size()
		{

			return __deque_buf_size(BufSiz, sizeof(T));

		}

		inline size_type initial_map_size()
		{
		
			return 8;
		
		}



		void create_map_and_nodes(size_type num_elements)
		{
		
			size_type num_nodes = num_elements / buffer_size() + 1;

			map_size = initial_map_size() > num_nodes + 2 ? initial_map_size() : num_nodes + 2;
		
			map = map_allocater::allocate(map_size);

			map_pointer nstart = map + (map_size - num_nodes) / 2;
			map_pointer nfinish = nstart + num_nodes - 1;

			map_pointer cur;

			for (cur = start; cur <= nfinish; ++cur)
			{

				*cur = allocate_node();
				
			}

			start.set_node(nstart);
			finish.set_node(nfinish);
			start.cur = start.first;
			finish.cur = finish.first + num_elements%buffer_size();

		
		}


		void fill_initialize(size_type n, const value_type& value)
		{
		
			create_map_and_nodes();
			map_pointer cur;
			for (cur = start.node; cur < finish.node; ++cur)
			{
				__uninitialized_fill(*cur, *cur + buffer_size(), value);
			}

			__uninitialized_fill(finish.first, finish.cur, value);
		
		}


		deque(int n, const value_type& value) :start(), finish(), map(0), map_size(0)
		{
		
			fill_initialize(n, value);
		
		}

		void push_back(const value_type&t)
		{
		
			if (finish.cur != finish.last - 1)
			{
				construct(finish.cur, t);
				++finish.cur;
			}
			else
			{
			
				push_back_aux(t);
			
			}
		
		}


		void push_back_aux(const value_type&t)
		{
		
			value_type t_copy = t;
			reverse_map_at_back();
			*(finish.node + 1) = allocate_node();

			try
			{

				construct(finish.cur, t_copy);
				finish.set_node(finish.node + 1);
				finish.cur = finish.first;

			}
			catch (...)
			{
				deallocate_node(*(finish.node + 1));
			}
		}


		void push_front(const value_type& t)
		{
		
			if (start.cur != start.first)
			{
				construct(start.cur - 1, t);
				--start.cur;
			}
			else
			{
				push_front_aux(t);
			}
		
		
		
		}


		void push_front_aux(const value_type& t)
		{
		
			value_type t_copy = t;
			reverse_map_at_front();
			*(start.node - 1) = allocate_node();
			try
			{
				start.set_node(start.node - 1);
				start.cur = start.last - 1;
				construct(start.cur, t_copy);
			}
			catch (...)
			{
				start.set_node(start.node + 1);
				start.cur = start.first;
				deallocate_node(*(start.node - 1));
				throw;
			
			
			}
		
		}
		

		void pop_back()
		{
		
			if (!finish.cur != finish.first)
			{
				--finish.cur;
				destroy(finish.cur);
			}
			else
			{
				pop_back_aux();
			}
		
		}


		void pop_back_aux()
		{
		
			deallocate_node(finish.first);
			finish.set_node(finish.node - 1);
			finish.cur = finish.last - 1;
			destroy(finish.cur);
		
		}


		void pop_front()
		{
		
			if (start.cur != start.first)
			{
				destroy(start.cur);

				start.cur++;
			}
			else
			{
			}
		
		
		
		}


		void pop_front_aux()
		{
		
			destroy(start.cur);

			deallocate_node(start.first);
			start.set_node(start.node + 1);
			start.cur = start.first;
			
		
		
		
		}


		void clear()
		{
		
			for (map_pointer node = start.node + 1; node < finish.node; ++node)
			{
				destroy(*node, *node + buffer_size());
			

				data_allocater::deallocate(*node, buffer_size());
			}


			if (start.node != finish.node)
			{
				destroy(start.cur, start.last);
				destroy(finish.first, finish.cur);

				data_allocater::deallocate(finish.first, buffer_size());
			}
			else
			{
				destroy(start.cur, finish.cur);
			}

			finish = start;
		
		}

		iterator erase(iterator pos)
		{
		
			iterator next = pos;
			++next;
			difference_type index = pos - start;
			if (index < (size() >> 1))
			{
				copy_backward(start, pos, next);
				pop_front();
			}
			else
			{
				copy(next, finish, pos);
				pop_back();
			}

			return start + index;
		
		}


		iterator erase(iterator first, iterator last)
		{
		
			if (first == start && last == finish)
			{
				clear();
				return start;
			}
			else
			{
				difference_type n = last - first;
				difference_type elems_before = first - start;
				if (elems_before < (size() - n) / 2)
				{
					copy_backward(start, first, last);
					iterator new_start = start + n;
					destroy(start, new_start);

					for (map_pointer cur = start.node; cur < new_start.node; ++cur)
					{
						data_allocater::deallocate(*cur, buffer_size());
					}

					start = new_start;
				}
				else
				{
					copy(last, finish, first);
					iterator new_finish = finish - n;
					destroy(new_finish, finish);
					for (map_pointer cur = new_finish.node + 1; cur <= finish.node; ++cur)
					{
						data_allocater::deallocate(*cur, buffer_size());
					}

					finish = new_finish;
				}

				return start + elems_before;
			}
		
		
		
		}


		iterator insert(iterator position, const value_type& x)
		{
		
			if (position.cur == start.cur)
			{
				push_front(x);
				return start;
			}
			else if (position.cur == finish.cur)
			{
				push_back(x);
				iterator tmp = finish;
				--tmp;
				return tmp;

			}
			else
			{
				return  insert_aux(position, x);
			}
		
		
		}


		iterator insert_aux(iterator pos, const value_type&x)
		{
		
			difference_type index = pos - start;
			value_type x_copy = x;
			if (index < size() / 2)
			{
				push_front(front()); 
				iterator front1 = start;
				++front1;
				iterator front2 = front1;
				++front2;
				pos = start + index;
				iterator pos1 = pos;
				++pos1;
				copy(front2, pos1, front1);
			}
			else
			{
				push_back(back());
				iterator back1 = back;
				--back1;
				iterator back2 = back1;
				--back2;
				pos = start + index;
				copy_backward(pos, back2, back1);
			}

			*pos = x_copy;
			return pos;
		
		
		}

		void realllocate_map(size_type nodes_to_add, bool add_at_front)
		{
		
			size_type old_num_nodes = finish.node - start.node + 1;
			size_type new_num_nodes = old_num_nodes + nodes_to_add;

			map_pointer new_nstart;
			if (map_size > 2 * new_num_nodes)
			{
				new_nstart = map + (map_size - new_num_nodes) / 2
					+ (add_at_front ? nodes_to_add : 0);

				if (new_nstart < start.node)
				{
					copy(start.node, finish.node + 1, new_nstart);
				}
				else
				{
					copy_backward(start.node, finish.node + 1, new_nstart + old_num_nodes);
				}
					

			}
			else
			{
				size_type new_map_size = map_size + max(map_size, nodes_to_add) + 2;
				map_pointer new_map = map_allocater::allocate(new_map_size);
				new_nstart = new_map + (new_map_size - new_num_nodes) / 2
					+ (add_at_front ? nodes_to_add : 0);

				copy(start.node, finish.node + 1, new_nstart);

				map_allocater::deallocate(map, map_size);
				map = new_map;
				map_size = new_map_size;
			}
		
			start.set_node(new_nstart);
			finish.set_node(new_nstart + old_num_nodes - 1);
		
		}


		void reverse_map_at_back(size_type nodes_to_add = 1)
		{
		
			if (nodes_to_add + 1 > map_size - (finish.node - map))
			{
				realllocate_map(nodes_to_add, false);
			}
		
		
		}


		void reverse_map_at_front(size_type nodes_to_add = 1)
		{
		
			if (nodes_to_add > start.node - map)
			{
			
				realllocate_map(nodes_to_add, true);
			
			}
		
		
		}


	};

}


#endif