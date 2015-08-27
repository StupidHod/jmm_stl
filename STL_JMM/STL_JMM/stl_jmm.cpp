#include <iostream>
#include <utility>
#include "jmm_stl_allocator.h"
#include <vector>
#include "jmm_stl_iterator.h"


using namespace std;

struct B{};

struct D1 :public B{};

struct D2 :public D1{};

template <class I>
void func(I& p, B)
{

	cout << "B version" << endl;

}

template <class I>
void func(I& p, D2)
{

	cout << "D2 version" << endl;

}


int main()
{
	int *p;

	func(p, B());
	func(p, D1());


	func(p, D2());
}