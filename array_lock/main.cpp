#include <iostream>
#include <atomic>
#include <thread>
#include <cstdlib>
#include <vector>

int incr = 0 ;
int current_i = 0;
int N;
std::vector<std::atomic<bool>> locks;

void lock(int i) {
    
    while ( locks[(i -1) >=0 ? (i-1) : N-1 ] )
    {
    }
    locks[i] = true;
}

void unlock(int i) {
    locks[i] = false;
}

void thread_f(int i) {
    while ( incr < 10000000 )
    {
        lock(i);
        incr ++;
        unlock(i);
    }
    std::cout << "done!" <<std::endl;
}

int main(int argc, char **argv) {
    int num_threads = atoi(argv[1]);
    std::thread t[num_threads];
    N = num_threads;
    locks = std::vector<std::atomic<bool>>(N);
    for (int i =0; i<N; i++)
        locks[i] = false;
    locks[0] = true;

    for (int i=0; i<num_threads; i++)
        t[i] = std::thread(thread_f,i);
    for (int i=0; i<num_threads; i++)
        t[i].join();
    return 0;
}
