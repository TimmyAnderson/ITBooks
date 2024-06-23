//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#define CODE_TEST_IRQL 0x801
#define CODE_TEST_DPC 0x802
#define CODE_TEST_TIMER 0x803
#define CODE_TEST_CRITICAL_REGION 0x804
#define CODE_TEST_GUARDED_REGION 0x805
#define CODE_TEST_SEH_1 0x806
#define CODE_TEST_SEH_2 0x807
#define CODE_TEST_SEH_3 0x808
#define CODE_TEST_SEH_4 0x809
#define CODE_TEST_SEH_5 0x80A
#define CODE_TEST_SEH_6 0x80B
#define CODE_TEST_RAII_1 0x80C
#define CODE_TEST_RAII_2 0x80D
#define CODE_TEST_UNIQUE_POINTER 0x80E
#define CODE_SYSTEM_CRASH 0x80F
#define CODE_SYSTEM_THREADS 0x810
#define CODE_INTERLOCKED 0x811
#define CODE_INTERLOCKED_LOCK_FREE 0x812
#define CODE_WAIT_FOR_SINGLE_OBJECT 0x813
#define CODE_WAIT_FOR_MULTIPLE_OBJECTS 0x814
#define CODE_MUTEXES 0x815
#define CODE_MUTEXES_RECURSIVE 0x816
#define CODE_MUTEXES_LOCKER 0x817
#define CODE_MUTEXES_ABANDONED 0x818
#define CODE_MUTEXES_STATE 0x819
#define CODE_FAST_MUTEXES 0x81A
#define CODE_SEMAPHORES 0x81B
#define CODE_MANUAL_RESET_EVENTS 0x81C
#define CODE_AUTO_RESET_EVENTS 0x81D
#define CODE_NAMED_MANUAL_RESET_EVENTS 0x81E
#define CODE_NAMED_AUTO_RESET_EVENTS 0x81F
#define CODE_EXECUTIVE_RESOURCES_READERS_FIRST 0x820
#define CODE_EXECUTIVE_RESOURCES_WRITERS_FIRST 0x821
#define CODE_EXECUTIVE_RESOURCES_AUTO_READERS_FIRST 0x822
#define CODE_EXECUTIVE_RESOURCES_AUTO_WRITERS_FIRST 0x823
#define CODE_SPIN_LOCKS 0x824
#define CODE_SPIN_LOCKS_IRQL 0x825
#define CODE_QUEUED_SPIN_LOCKS 0x826
#define CODE_WORK_ITEMS_STATIC 0x827
#define CODE_WORK_ITEMS_DYNAMIC 0x828
//----------------------------------------------------------------------------------------------------------------------