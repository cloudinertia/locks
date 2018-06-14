#include "mcs_lock.h"

namespace sync {

    void mcs_lock::lock() {
        auto prior_node = tail.exchange(&local_node,
                                        std::memory_order_acquire);
        if(prior_node != nullptr) {
            local_node.locked = true;
            prior_node->next = &local_node;
            while(local_node.locked)
                ;
        }
    }

    void mcs_lock::unlock() {
        if(local_node.next == nullptr) {
            mcs_node* p = &local_node;
            if(tail.compare_exchange_strong(p,nullptr,
                                            std::memory_order_release,
                                            std::memory_order_relaxed)) {
                return;
            }
            while (local_node.next == nullptr) {};
        }
        local_node.next->locked = false;
        local_node.next = nullptr;
    }

    thread_local mcs_lock::mcs_node mcs_lock::local_node = mcs_lock::mcs_node{};

}
