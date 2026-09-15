include_directories(${hw_INCDIR})

### Translation Tests
add_executable(test_addr test_addr.cpp)
target_link_libraries(test_addr homework )
add_test(TestAddr ./test_addr)

add_executable(test_offset test_offset.cpp)
target_link_libraries(test_offset homework )
add_test(TestOffset ./test_offset)

add_executable(test_pfn test_pfn.cpp)
target_link_libraries(test_pfn homework )
add_test(TestPFN ./test_pfn)

add_executable(test_table test_table.cpp)
target_link_libraries(test_table homework )
add_test(TestTable ./test_table)

add_executable(test_table_page test_table_page.cpp)
target_link_libraries(test_table_page homework )
add_test(TestTablePage ./test_table_page)

add_executable(test_table_pfn test_table_pfn.cpp)
target_link_libraries(test_table_pfn homework )
add_test(TestTablePFN ./test_table_pfn)

add_executable(test_table_protect test_table_protect.cpp)
target_link_libraries(test_table_protect homework )
add_test(TestTableProtect ./test_table_protect)

add_executable(test_table_seg test_table_seg.cpp)
target_link_libraries(test_table_seg homework )
add_test(TestTableSeg ./test_table_seg)

add_executable(test_table_to_tlb test_table_to_tlb.cpp)
target_link_libraries(test_table_to_tlb homework )
add_test(TestTableTLB ./test_table_to_tlb)

add_executable(test_tlb test_tlb.cpp)
target_link_libraries(test_tlb homework )
add_test(TestTLB ./test_tlb)

add_executable(test_tlb_index test_tlb_index.cpp)
target_link_libraries(test_tlb_index homework )
add_test(TestTLBIndex ./test_tlb_index)

add_executable(test_tlb_miss test_tlb_miss.cpp)
target_link_libraries(test_tlb_miss homework )
add_test(TestTLBMiss ./test_tlb_miss)

add_executable(test_tlb_pfn test_tlb_pfn.cpp)
target_link_libraries(test_tlb_pfn homework )
add_test(TestTLBPFN ./test_tlb_pfn)

add_executable(test_tlb_protection test_tlb_protection.cpp)
target_link_libraries(test_tlb_protection homework )
add_test(TestTLBProtect ./test_tlb_protection)

add_executable(test_tlb_tag test_tlb_tag.cpp)
target_link_libraries(test_tlb_tag homework )
add_test(TestTLBTag ./test_tlb_tag)

add_executable(test_vpn test_vpn.cpp)
target_link_libraries(test_vpn homework )
add_test(TestVPN ./test_vpn)

add_executable(test_virtual_to_physical1 test_virtual_to_physical1.cpp)
target_link_libraries(test_virtual_to_physical1 homework )
add_test(TestVirtualToPhysical1 ./test_virtual_to_physical1)

add_executable(test_virtual_to_physical2 test_virtual_to_physical2.cpp)
target_link_libraries(test_virtual_to_physical2 homework )
add_test(TestVirtualToPhysical2 ./test_virtual_to_physical2)

add_executable(test_virtual_to_physical3 test_virtual_to_physical3.cpp)
target_link_libraries(test_virtual_to_physical3 homework )
add_test(TestVirtualToPhysical3 ./test_virtual_to_physical3)

add_executable(test_virtual_to_physical4 test_virtual_to_physical4.cpp)
target_link_libraries(test_virtual_to_physical4 homework )
add_test(TestVirtualToPhysical4 ./test_virtual_to_physical4)

add_executable(test_virtual_to_physical5 test_virtual_to_physical5.cpp)
target_link_libraries(test_virtual_to_physical5 homework )
add_test(TestVirtualToPhysical5 ./test_virtual_to_physical5)


### Replacement Tests
add_executable(test_fifo test_fifo.cpp)
target_link_libraries(test_fifo homework )
add_test(TestFifo ./test_fifo)

add_executable(test_fifo_steps test_fifo_steps.cpp)
target_link_libraries(test_fifo_steps homework )
add_test(TestFifoSteps ./test_fifo_steps)

add_executable(test_lru test_lru.cpp)
target_link_libraries(test_lru homework )
add_test(TestLRU ./test_lru)

add_executable(test_lru_steps test_lru_steps.cpp)
target_link_libraries(test_lru_steps homework )
add_test(TestLRUSteps ./test_lru_steps)

add_executable(test_clock_lru test_clock_lru.cpp)
target_link_libraries(test_clock_lru homework )
add_test(TestClockLRU ./test_clock_lru)

add_executable(test_clock_lru_steps test_clock_lru_steps.cpp)
target_link_libraries(test_clock_lru_steps homework )
add_test(TestClockLRUSteps ./test_clock_lru_steps)

