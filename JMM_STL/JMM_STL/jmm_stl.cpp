

#include "jmm_stl_allocator.h"

#include "jmm_stl_iterator.h"
#include "jmm_stl_list.h"
#include "jmm_stl_vector.h"
#include "jmm_stl_stack.h"
#include "jmm_stl_vector.h"
#include <utility>
#include <iostream>
#include "jmm_stl_heap.h"
#include "jmm_stl_queue.h"


using namespace JMM_STL;

template <class RandomAccessIterator>
void outputIterator(RandomAccessIterator first, RandomAccessIterator last)
{
	while (first!=last)
	{
		std::cout << *(first++) << "\t";
	}

	std::cout << std::endl;
}


void test_vector_heap()
{

	int ia[9] = { 0, 1, 2, 3, 4, 8, 9, 3, 5 };
	vector<int> ivec(ia, ia + 9);
	outputIterator(ia, ia + 9);

	make_heap(ivec.begin(), ivec.end());
	outputIterator(ivec.begin(), ivec.end());


	ivec.push_back(7);
	push_heap(ivec.begin(), ivec.end());
	outputIterator(ivec.begin(), ivec.end());

	pop_heap(ivec.begin(), ivec.end());
	outputIterator(ivec.begin(), ivec.end());
	ivec.pop_back();
	outputIterator(ivec.begin(), ivec.end());

	sort_heap(ivec.begin(), ivec.end());
	outputIterator(ivec.begin(), ivec.end());


}

void test_priority_queue()
{
	int ia[9] = { 0, 1, 2, 3, 4, 8, 9, 3, 5 };
	priority_queue<int> ipq(ia, ia + 9);
	while (!ipq.empty())
	{
		std::cout << ipq.top() << "\t";
		ipq.pop();
	}
}

int main()
{
	int wait;

	//test_vector_heap();
	test_priority_queue();

	std::cin >> wait;
}