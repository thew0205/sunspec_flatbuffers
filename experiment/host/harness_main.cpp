#include <stdio.h>
#include <chrono>
#include <malloc.h>

#include "sunspec.h"

// Defined differently per variant (load_only.cpp / walk_shallow.cpp /
// walk_deep.cpp); each does getModelDefinition() plus however much of the
// group/point tree it walks.
void walk();

struct TimeTestResult
{
    long int iterations;
    long long time_taken_us;
};

struct HeapTestResult
{
    long long heap_peak_call_bytes;
    long long heap_net_growth_bytes;
};

// Timed loop: measures walk()'s raw per-call latency. Kept free of any
// memory-profiling calls (mallinfo2() etc.) so sampling overhead never
// pollutes the timing measurement -- see run_heap_test() for that.
TimeTestResult run_time_test()
{
    using std::chrono::duration_cast;
    using std::chrono::microseconds;
    using clock = std::chrono::steady_clock;

    const long int iterations = 1000;
    auto t1 = clock::now();
    for (long int i = 0; i < iterations; i++)
    {
        walk();
    }
    auto t2 = clock::now();
    auto us = duration_cast<microseconds>(t2 - t1);

    return TimeTestResult{iterations, (long long)us.count()};
}

// Dynamic (heap) memory profiling pass. See research_experiment/power_meter's
// power_meter_main_deserialization.cpp for the sampling rationale: this
// tracks glibc's "bytes currently allocated" counter to get a per-call heap
// delta (heap_peak_call_bytes) and the net heap growth across the whole
// pass (heap_net_growth_bytes).
//
// Deliberately mallinfo2() here, not the newer mallinfo22(): mallinfo22() is a
// glibc-only extension and isn't available on the Pico SDK's newlib
// toolchain, which only has the older mallinfo2() (same fields, just `int`
// instead of `size_t`/`unsigned long`). That's a non-issue at these
// allocation sizes, and using the same call on both host and target keeps
// this file identical across the two harnesses.
HeapTestResult run_heap_test()
{
    // Reset backend state first: SunspecModelDef::initializeAllModels() is
    // also triggered eagerly at static-init time (before main()) so
    // CppUTest's per-test leak detector doesn't misattribute it -- see
    // model_definition.cpp / sunspec_json_definition.cpp. Left alone, that
    // means modelDefList is already built by the time this function runs,
    // so the explicit initializeAllModels() call below would be a no-op
    // and its allocation would never show up in the heap delta.
    // Deinitializing first makes that explicit call do real work again, so
    // this test actually captures its cost.
   deinitializeAllModels();

    // Malloc setup code: baseline snapshot before anything under test runs.
    long long heap_before_all = (long long)mallinfo2().uordblks;

    // Explicit call, right after the malloc setup code above, so
    // initializeAllModels()'s one-time model-list construction is captured
    // by the heap delta below instead of happening invisibly pre-main().
    initializeAllModels();

    const long int mem_iterations = 200;
    long long heap_peak_call_bytes = 0;
    for (long int i = 0; i < mem_iterations; i++)
    {
        long long before = (long long)mallinfo2().uordblks;
        walk();
        long long after = (long long)mallinfo2().uordblks;
        long long delta = after - before;
        if (delta > heap_peak_call_bytes)
        {
            heap_peak_call_bytes = delta;
        }
    }
    long long heap_after_all = (long long)mallinfo2().uordblks;
    long long heap_net_growth_bytes = heap_after_all - heap_before_all;

    return HeapTestResult{heap_peak_call_bytes, heap_net_growth_bytes};
}

int main()
{
    TimeTestResult time_result = run_time_test();
    HeapTestResult heap_result = run_heap_test();

    printf("{\"iteration\" : %ld, \"time_taken\" : %lld, "
           "\"heap_peak_call_bytes\" : %lld, \"heap_net_growth_bytes\" : %lld}\n",
           time_result.iterations, time_result.time_taken_us,
           heap_result.heap_peak_call_bytes, heap_result.heap_net_growth_bytes);
    return 0;
}
