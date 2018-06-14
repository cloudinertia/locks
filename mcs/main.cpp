#include <iostream>
#include <atomic>
#include <thread>
#include <cstdlib>
#include "mcs_lock.h"

int incr = 0 ;
sync::mcs_lock m;
void lock(void) {
    m.lock();
}

void unlock(void) {
    m.unlock();
}

void thread_f(void) {
    while ( incr < 10000000 )
    {
        lock();
        incr ++;
        unlock();
    }
    std::cout << "done!" <<std::endl;
}

int main(int argc, char **argv) {
    int num_threads = atoi(argv[1]);
    std::thread t[num_threads];

    for (int i=0; i<num_threads; i++)
        t[i] = std::thread(thread_f);
    for (int i=0; i<num_threads; i++)
        t[i].join();
    return 0;
}
