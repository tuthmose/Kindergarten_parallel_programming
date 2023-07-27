#include <iostream>
#include <sstream>
#include <omp.h>
#include <utmpx.h>
#include <random>

int main(){
    #pragma omp parallel
    {
        std::default_random_engine rand;
	int num = 0;
	#pragma omp for
	for(size_t i = 0; i < 1000000000; ++i) num += rand();
	auto cpu = sched_getcpu();
	std::ostringstream os;
	     os<<"\nThread "<<omp_get_thread_num()<<" on cpu "<<sched_getcpu()<<std::endl;
	     std::cout<<os.str()<<std::flush;
	std::cout<<num;
	}
}
