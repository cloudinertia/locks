#ifndef MCS_LOCK_H
#define MCS_LOCK_H

#include <cstdint>
#include <assert.h>
#include <atomic>
#include <thread>

#include <iostream>

#define CACHELINE_SIZE 64

namespace sync {
  
    class mcs_lock {

        struct mcs_node {

            bool locked{true};
            uint8_t pad1[CACHELINE_SIZE - sizeof(bool)];

            mcs_node* next{nullptr};
            uint8_t pad2[CACHELINE_SIZE - sizeof(mcs_node*)];

        };

        static_assert(sizeof(mcs_node) == 2 * CACHELINE_SIZE, "");

    public:

        void lock();

        void unlock();

    private:

        std::atomic<mcs_node*> tail{nullptr};

        static thread_local mcs_node local_node;

    };

}


#endif // MCS_LOCK_H

