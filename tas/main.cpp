#include <iostream>
#include <atomic>
#include <thread>
#include <cstdlib>

std::atomic_flag _lock = ATOMIC_FLAG_INIT;
int incr = 0 ;

void lock(void) {
    while(std::atomic_flag_test_and_set_explicit(&_lock, std::memory_order_acquire))
        ;
}

void unlock(void) {
    std::atomic_flag_clear_explicit(&_lock, std::memory_order_release);

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
