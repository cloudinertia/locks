#include <iostream>
#include <atomic>
#include <thread>
#include <cstdlib>

//std::atomic_flag _lock = ATOMIC_FLAG_INIT;
std::atomic<bool> _lock;
int incr = 0 ;

bool test_and_set(std::atomic<bool> &b) {
    if (b)
    {
        return true;
    }
    else
    {
        b = true;
        return false;
    }
}
void lock(void) {
    do {
        while (_lock) ;
        if(!test_and_set(_lock)) return; 
    } while (true);
}

void unlock(void) {
    _lock = false;
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
