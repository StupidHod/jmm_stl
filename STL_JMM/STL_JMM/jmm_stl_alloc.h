namespace jmm_stl
{

#if 0
#	include <new>
#	define __THROW_BAD_ALLOC throw bad_alloc
#elif !defined(__THROW_BAD_ALLOC)
#	include <iostream>
#	define __THROW_BAD_ALLOC cerr<<"out of memory"<<endl;exit(1)
#endif

	template<int inst>
	class __malloc_alloc_template{

	private:
		static void *oom_malloc(size_t);
		static void *oom_realloc(void*, size_t);
		static void(*__malloc_alloc_oom_handle)();

	public:
		static void *allocate(size_t n)
		{
		
			void *result = malloc(n);

			if (0 == result)
			{
				result == oom_malloc(n);
			}
		
			return result;
		}

		static void deallocate(void* p, size_t n)
		{
		
			free(p);
		
		}

		static void* reallocate(void* p, size_t old_sz, size_t new_sz)
		{
		
			void *result = realloc(p, new_sz);
			if (0 == result)
			{
				result == oom_realloc(p, new_sz);
			}

			return result;
		
		}

		

	};
	
}