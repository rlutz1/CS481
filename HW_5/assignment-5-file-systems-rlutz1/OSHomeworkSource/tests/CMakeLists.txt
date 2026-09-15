include_directories(${hw_INCDIR})

add_executable(test_journal test_journal.cpp)
target_link_libraries(test_journal homework  )
add_test(TestJournal ./test_journal)

add_executable(test_checkpoint test_checkpoint.cpp)
target_link_libraries(test_checkpoint homework  )
add_test(TestCheckpoint ./test_checkpoint)

add_executable(test_checkpoint2 test_checkpoint2.cpp)
target_link_libraries(test_checkpoint2 homework  )
add_test(TestCheckpoint2 ./test_checkpoint2)

add_executable(test_fail_checkpoint test_fail_checkpoint.cpp)
target_link_libraries(test_fail_checkpoint homework  )
add_test(TestFailCheckpoint ./test_fail_checkpoint)

