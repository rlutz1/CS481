include_directories(${hw_INCDIR})

## Producer Consumer with Condition Variables
add_executable(test_producer_consumer_cond test_producer_consumer.cpp)
target_link_libraries(test_producer_consumer_cond cond_var  )
add_test(TestCondProducerConsumer ./test_producer_consumer_cond)

add_executable(test_producer_consumer_cond2 test_producer_consumer2.cpp)
target_link_libraries(test_producer_consumer_cond2 cond_var  )
add_test(TestCondProducerConsumer2 ./test_producer_consumer_cond2)

add_executable(test_consumer_while test_consumer_while.cpp)
target_link_libraries(test_consumer_while cond_var )
add_test(TestCondConsumerWhile ./test_consumer_while)

add_executable(test_producer_while test_producer_while.cpp)
target_link_libraries(test_producer_while cond_var )
add_test(TestCondProducerWhile ./test_producer_while)


## Producer Consumer with Semaphore
add_executable(test_producer_consumer_sem test_producer_consumer.cpp)
target_link_libraries(test_producer_consumer_sem semaphore  )
add_test(TestSemProducerConsumer ./test_producer_consumer_sem)

add_executable(test_producer_consumer_sem2 test_producer_consumer2.cpp)
target_link_libraries(test_producer_consumer_sem2 semaphore  )
add_test(TestSemProducerConsumer2 ./test_producer_consumer_sem2)


## Dining Philosophers no Circular Wait
add_executable(test_philosopher_circ test_philosopher.cpp)
target_link_libraries(test_philosopher_circ circular  )
add_test(TestCircPhilosopher ./test_philosopher_circ)


## Dining Philosophers no Hold and Wait
add_executable(test_philosopher_hold test_philosopher.cpp)
target_link_libraries(test_philosopher_hold hold_and_wait  )
add_test(TestHoldPhilosopher ./test_philosopher_hold)



