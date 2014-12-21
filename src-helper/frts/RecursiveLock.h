#ifndef FRTS_RECURSIVELOCK_H
#define FRTS_RECURSIVELOCK_H

#ifdef SPIN_LOCK
#include <atomic>
#include <thread>
#endif
#include <mutex>


namespace frts
{
#ifdef SPIN_LOCK
    /**
     * @brief Recursive spin lock based on a simple atomic boolean. Is compatible
     *        with BasicLockable requirement of std::lock_guard.
     * @see http://stackoverflow.com/a/8151506/1931663
     * @see http://preshing.com/20120305/implementing-a-recursive-mutex/
     */
    class RecursiveLock
    {
    public:
        RecursiveLock()
            : lockValue{false}
        {}

        void lock()
        {
            std::thread::id threadId = std::this_thread::get_id();

            if (threadId != owner)
            {
                while(lockValue.exchange(true));
            }

            owner = threadId;
            recursion += 1;
        }

        void unlock()
        {
            assert(owner == std::this_thread::get_id());

            recursion -= 1;
            if (recursion == 0)
            {
                owner = std::thread::id();
                lockValue.store(false);
            }
        }

    private:
        std::atomic<bool> lockValue;
        std::thread::id owner;
        unsigned int recursion = 0;
    };
#else
    using RecursiveLock = std::recursive_mutex;
#endif
}

#endif // FRTS_RECURSIVELOCK_H
