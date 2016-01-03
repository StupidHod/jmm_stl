#include "jmm_stl_allocator.h"

#include "jmm_stl_iterator.h"
#include "jmm_stl_list.h"
#include "jmm_stl_vector.h"
#include "jmm_stl_stack.h"
#include "jmm_stl_vector.h"
#include <utility>
#include <iostream>
#include <string>
#include "jmm_stl_heap.h"
#include "jmm_stl_queue.h"
#include "jmm_stl_slist.h"
#include "jmm_stl_rb_tree.h"
#include "jmm_stl_set.h"
#include "jmm_stl_map.h"
#include "jmm_stl_hashtable.h"
#include "jmm_stl_hash_fun.h"
#include "jmm_stl_hash_set.h"
#include <cstring>
#include "jmm_stl_hash_map.h"
#include "jmm_stl_numeric.h"
#include "jmm_stl_algo.h"

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

void test_slist()
{
	int i;
	slist<int> islist;
	std::cout << "size=" << islist.size() << std::endl;
	islist.push_front(9);
	islist.push_front(1);
	islist.push_front(2);
	islist.push_front(3);
	islist.push_front(4);
	std::cout << "size=" << islist.size() << std::endl;

	slist<int>::iterator ite = islist.begin();
	slist<int>::iterator ite2 = islist.end();
	for (; ite != ite2; ++ite)
	{
		std::cout << *ite << "\t";
	}

	std::cout << std::endl;

	
}

void test_rb_tree()
{
	rb_tree<int, int, identity<int>, less<int>> itree;
	std::cout << itree.size() << std::endl;
	itree.insert_unique(10);
	itree.insert_unique(7);
	itree.insert_unique(8);

	itree.insert_unique(15);
	itree.insert_unique(5);
	itree.insert_unique(6);


	itree.insert_unique(11);
	itree.insert_unique(13);
	itree.insert_unique(12);
	std::cout << itree.size() << std::endl;
	outputIterator(itree.begin(), itree.end());
}


void test_set()
{
	int ia[5] = { 0, 1, 2, 3, 4 };
	set<int> iset(ia, ia + 5);
	
	std::cout << "size=" << iset.size() << std::endl;
	std::cout << "3 count=" << iset.count(3) << std::endl;
	outputIterator(iset.begin(), iset.end());

	iset.insert(5);
	std::cout << "size=" << iset.size() << std::endl;
	std::cout << "3 count=" << iset.count(3) << std::endl;
	outputIterator(iset.begin(), iset.end());
	
	iset.erase(1);
	std::cout << "size=" << iset.size() << std::endl;
	std::cout << "3 count=" << iset.count(3) << std::endl;
	std::cout << "1 count=" << iset.count(3) << std::endl;

	outputIterator(iset.begin(), iset.end());

	
	set<int>::iterator ite1 = iset.find(3);
	if (ite1 != iset.end())
	{
		std::cout << "3 found!" << std::endl;
	}
	else
	{
		std::cout << "3 not found!" << std::endl;
	}

	ite1 = iset.find(1);

	if (ite1 != iset.end())
	{
		std::cout << "1 found!" << std::endl;
	}
	else
	{
		std::cout << "1 not found!" << std::endl;
	}
}

void test_map()
{
	map<std::string, int> simap;
	simap[std::string("jjhou")] = 1;
	simap[std::string("jerry")] = 2;
	simap[std::string("jason")] = 3;
	simap[std::string("jjmmy")] = 4;

	pair<std::string, int> value(std::string("david"), 5);
	simap.insert(value);

	std::cout << simap.size() << std::endl;

	map<std::string, int>::iterator simap_iter = simap.begin();
	for (; simap_iter != simap.end(); ++simap_iter)
	{
		std::cout<<simap_iter->first << "\t" << simap_iter->second << std::endl;
	
	}

	int number = simap[std::string("jjhou")];
	std::cout << number << std::endl;


	map<std::string, int>::iterator ite1;
	ite1 = simap.find(std::string("mchen"));
	if (ite1 == simap.end())
	{
		std::cout << "mchen not found" << std::endl;
	}
	else
	{
		std::cout << "mchen found" << std::endl;
	}

	ite1 = simap.find(std::string("jerry"));
	if (ite1 == simap.end())
	{
		std::cout << "jerry not found" << std::endl;
	}
	else
	{
		std::cout << "jerry found" << std::endl;
	}

	
	int numer2 = simap[std::string("jerry")];
	std::cout << numer2 << std::endl;

	ite1->second = 9;
	numer2 = simap[std::string("jerry")];
	std::cout << numer2 << std::endl;

	
}

void test_hashtable()
{
	hashtable<int, int, hash<int>, identity<int>, equal_to<int>, alloc> iht(50, hash<int>(), equal_to<int>());

	std::cout << iht.size() << std::endl;
	std::cout << iht.bucket_count() << std::endl;
	std::cout << iht.max_bucket_count() << std::endl;


	auto i = iht.begin();
	//iterator_category(i);
	
	iht.insert_unique(59);
	iht.insert_unique(63);
	iht.insert_unique(108);
	iht.insert_unique(2);
	iht.insert_unique(53);
	iht.insert_unique(55);

	std::cout << iht.size() << std::endl;

	auto ite = iht.begin();

	outputIterator(iht.begin(), iht.end());

	for (int i = 0; i < iht.bucket_count(); ++i)
	{
		int n = iht.elems_in_bucket(i);
		if (n != 0)
		{
			std::cout << "bucket[" << i << "] has " << n << " elems." << std::endl;
		}
	}


	for (int i = 0; i <= 47; ++i)
	{
		iht.insert_equal(i);
	}

	std::cout << iht.bucket_count() << std::endl;

	for (int i = 0; i < iht.bucket_count(); ++i)
	{
		int n = iht.elems_in_bucket(i);
		if (n != 0)
		{
			std::cout << "bucket[" << i << "] has " << n << " elems." << std::endl;
		}
	}

	outputIterator(iht.begin(), iht.end());

	std::cout << *(iht.find(2)) << std::endl;
	std::cout << iht.count(2) << std::endl;
	
}


struct  eqstr
{
	bool operator()(const char* s1, const char* s2) const
	{
		return strcmp(s1, s2) == 0;
	}
};

void lookup(const hash_set<const char*, hash<const char*>, eqstr>& Set,
	const char* word)
{
	hash_set<const char*, hash<const char*>, eqstr>::const_iterator it
		=Set.find(word);

	std::cout << "\t" << word << ":"
		<< (it !=  Set.end() ? "present" : "not present")
		<< std::endl;
}

void test_hash_set()
{
	hash_set<const char*, hash<const char*>, eqstr> Set;
	Set.insert("kiwi");
	Set.insert("plum");
	Set.insert("apple");
	Set.insert("mango");
	Set.insert("apricot");
	Set.insert("banana");

	lookup(Set, "mango");
	lookup(Set, "apple");
	lookup(Set, "durian");

	outputIterator(Set.begin(), Set.end());
}

void test_hash_map()
{
	hash_map<const char*, int, hash<const char*>, eqstr> days;
	days["january"] = 31;
	days["february"] = 28;
	days["march"] = 31;
	days["april"] = 30;
	days["may"] = 31;
	days["june"] = 30;
	days["july"] = 31;
	days["august"] = 31;
	days["september"] = 30;
	days["october"] = 31;
	days["november"] = 30;
	days["december"] = 31;


	std::cout << "september\t-> " << days["september"] << std::endl;
	std::cout << "june\t-> " << days["june"] << std::endl;
	std::cout << "february\t-> " << days["february"] << std::endl;
	std::cout << "december\t-> " << days["december"] << std::endl;

	for (auto first = days.begin(); first != days.end(); ++first)
	{
		std::cout << first->first << "\t";
	}
}

void test_numeric()
{
	std::cout << "2^10 = " << JMM_STL::power(2, 10) << std::endl;


}


template<class T>
struct display
{
	void operator()(const T& x) const
	{
		std::cout << x << "\t";
	}
};


struct even
{
	bool operator()(int x) const
	{
		return x % 2 ? false : true;
	}

};

struct even_by_two
{
public:
	int operator()()const
	{
		return _x += 2;
	}
private:
	static int _x;
};

int even_by_two::_x = 0;


void test_algo_1()
{
	int ia[] = { 0,1, 2, 3, 4, 5, 6,6,6, 7 ,8 };

	vector<int> iv(ia, ia + sizeof(ia) / sizeof(int));
	std::cout << *adjacent_find(iv.begin(), iv.end()) << std::endl;
	std::cout << *adjacent_find(iv.begin(), iv.end(), equal_to<int>()) << std::endl;

	std::cout << count(iv.begin(), iv.end(),6) << std::endl;

	std::cout << count_if(iv.begin(), iv.end(), bind2nd(less<int>(),7)) << std::endl;

	std::cout << *find(iv.begin(), iv.end(), 4) << std::endl;

	std::cout << *find_if(iv.begin(), iv.end(), bind2nd(greater<int>(), 2)) << std::endl;

	vector<int> iv2(ia + 6, ia + 8);
	outputIterator(iv2.begin(), iv2.end());
	outputIterator(iv.begin(), iv.end());
	std::cout << *(find_end(iv.begin(), iv.end(), iv2.begin(),iv2.end())+3) << std::endl;
	std::cout << *(find_first_of(iv.begin(), iv.end(), iv2.begin(), iv2.end()) + 3) << std::endl;
	

	for_each(iv.begin(), iv.end(), display<int>());
	std::cout << std::endl;
	generate(iv2.begin(), iv2.end(), even_by_two());
	for_each(iv2.begin(), iv2.end(), display<int>());
	std::cout << std::endl;


	generate_n(iv.begin(), 3, even_by_two());
	for_each(iv.begin(), iv.end(), display<int>());
	std::cout << std::endl;


}






void test_algo_2()
{
	int ia[] = { 12, 17, 20, 22, 23, 30, 33, 40 };
	vector<int> iv(ia, ia + sizeof(ia) / sizeof(int));


	std::cout << *lower_bound(iv.begin(), iv.end(), 21) << std::endl;
	std::cout << *upper_bound(iv.begin(), iv.end(), 21) << std::endl;
	std::cout << *lower_bound(iv.begin(), iv.end(), 22) << std::endl;
	std::cout << *upper_bound(iv.begin(), iv.end(), 22) << std::endl;


}

int main()
{
	int wait;

	//test_vector_heap();
	//test_priority_queue();
	//test_slist();
	//test_rb_tree();
	//test_set();
	//test_map();
	//test_hashtable();
	//test_hash_set();
	//test_hash_map();

	//test_numeric();

	test_algo_1();
	//test_algo_2();

	std::cin >> wait;
}