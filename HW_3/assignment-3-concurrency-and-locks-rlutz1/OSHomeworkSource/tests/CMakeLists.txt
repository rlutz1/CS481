include_directories(${hw_INCDIR})

### Ticket Tests
add_executable(test_spin_lock test_spin_lock.cpp)
target_link_libraries(test_spin_lock ticket_spin )
add_test(SpinLockTest ./test_spin_lock)

add_executable(test_yield_lock test_yield_lock.cpp)
target_link_libraries(test_yield_lock ticket_yield )
add_test(YieldLockTest ./test_yield_lock)

### Semaphore Tests
add_executable(test_semaphore test_semaphore.cpp)
target_link_libraries(test_semaphore semaphore )
add_test(SemaphoreTest ./test_semaphore)

add_executable(test_semaphore_lock test_semaphore_lock.cpp)
target_link_libraries(test_semaphore_lock semaphore )
add_test(SemaphoreLockTest ./test_semaphore_lock)


### Queue Tests
add_executable(test_queue_lock test_queue_lock.cpp)
target_link_libraries(test_queue_lock queue )
add_test(QueueLockTest ./test_queue_lock)

add_executable(test_queue_guard test_queue_guard.cpp)
target_link_libraries(test_queue_guard queue )
add_test(QueueGuardTest ./test_queue_guard)

add_executable(test_no_queue test_no_queue.cpp)
target_link_libraries(test_no_queue queue )
add_test(NoQueueTest ./test_no_queue)

add_executable(test_queue test_queue.cpp)
target_link_libraries(test_queue queue )
add_test(QueueTest ./test_queue)

### Mutual Exclusion Tests
add_executable(spin_mutual_exclusion test_mutual_exclusion.cpp)
target_link_libraries(spin_mutual_exclusion ticket_spin )
add_test(TicketSpinMutualExclusion ./spin_mutual_exclusion)

add_executable(yield_mutual_exclusion test_mutual_exclusion.cpp)
target_link_libraries(yield_mutual_exclusion ticket_yield )
add_test(TicketYieldMutualExclusion ./yield_mutual_exclusion)

add_executable(semaphore_mutual_exclusion test_mutual_exclusion.cpp)
target_link_libraries(semaphore_mutual_exclusion semaphore )
add_test(SemaphoreMutualExclusion ./semaphore_mutual_exclusion)

add_executable(queue_mutual_exclusion test_mutual_exclusion.cpp)
target_link_libraries(queue_mutual_exclusion queue )
add_test(QueueMutualExclusion ./queue_mutual_exclusion)


### PI Tests
add_executable(test_pi test_pi.cpp)
target_link_libraries(test_pi mutex )
add_test(PITest ./test_pi)

add_executable(test_pi_ticket_spin test_pi.cpp)
target_link_libraries(test_pi_ticket_spin ticket_spin )
add_test(PITicketSpinTest ./test_pi_ticket_spin)

add_executable(test_pi_ticket_yield test_pi.cpp)
target_link_libraries(test_pi_ticket_yield ticket_yield )
add_test(PITicketYieldTest ./test_pi_ticket_yield)

add_executable(test_pi_queue test_pi.cpp)
target_link_libraries(test_pi_queue queue )
add_test(PIQueueTest ./test_pi_queue)

add_executable(test_pi_semaphore test_pi.cpp)
target_link_libraries(test_pi_semaphore semaphore )
add_test(PISemaphoreTest ./test_pi_semaphore)



