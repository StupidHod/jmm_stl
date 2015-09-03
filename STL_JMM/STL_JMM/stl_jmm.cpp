

#include "jmm_stl_allocator.h"

#include "jmm_stl_iterator.h"
#include "jmm_stl_list.h"
#include "jmm_stl_vector.h"
#include "jmm_stl_stack.h"
#include <vector>
#include <utility>
#include <iostream>



struct B{};

struct D1 :public B{};

struct D2 :public D1{};

template <class I>
void func(I& p, B)
{

	std::cout << "B version" << std::endl;

}

template <class I>
void func(I& p, D2)
{

	std::cout << "D2 version" << std::endl;

}


int main()
{
	int *p;

	func(p, B());
	func(p, D1());


	func(p, D2());
}