#include <stdio.h>
#include <malloc.h>

#include "pico/stdlib.h"

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
// memory-profiling calls (mallinfo() etc.) so sampling overhead never
// pollutes the timing measurement -- see run_heap_test() for that.
TimeTestResult run_time_test()
{

    const long int iterations = 40;
    uint32_t t1 = time_us_32();
    for (long int i = 0; i < iterations; i++)
    {
        walk();
    }
    uint32_t t2 = time_us_32();
    uint32_t us = t2 - t1;

    return TimeTestResult{iterations, us};
}

// Dynamic (heap) memory profiling pass. See research_experiment/power_meter's
// power_meter_main_deserialization.cpp for the sampling rationale: this
// tracks glibc's "bytes currently allocated" counter to get a per-call heap
// delta (heap_peak_call_bytes) and the net heap growth across the whole
// pass (heap_net_growth_bytes).
//
// Deliberately mallinfo() here, not the newer mallinfo2(): mallinfo2() is a
// glibc-only extension and isn't available on the Pico SDK's newlib
// toolchain, which only has the older mallinfo() (same fields, just `int`
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
    long long heap_before_all = (long long)mallinfo().uordblks;

    // Explicit call, right after the malloc setup code above, so
    // initializeAllModels()'s one-time model-list construction is captured
    // by the heap delta below instead of happening invisibly pre-main().
    initializeAllModels();

    const long int mem_iterations = 20;
    long long heap_peak_call_bytes = 0;
    for (long int i = 0; i < mem_iterations; i++)
    {
        long long before = (long long)mallinfo().uordblks;
        walk();
        long long after = (long long)mallinfo().uordblks;
        long long delta = after - before;
        if (delta > heap_peak_call_bytes)
        {
            heap_peak_call_bytes = delta;
        }
    }
    long long heap_after_all = (long long)mallinfo().uordblks;
    long long heap_net_growth_bytes = heap_after_all - heap_before_all;

    return HeapTestResult{heap_peak_call_bytes, heap_net_growth_bytes};
}

int main()
{
    stdio_init_all();
    sleep_ms(20);

    HeapTestResult heap_result = run_heap_test();
    TimeTestResult time_result = run_time_test();

    // Unlike the host harness (a fresh process per capture), this runs once
    // per boot and then has no OS to return to -- so instead of printing
    // once and returning, keep re-printing the same (deterministic, no-OS-
    // jitter) result forever. That way a host-side script driving this over
    // USB serial (picotool to flash, tio to read) doesn't have to win a race
    // against a single post-boot print: it can attach whenever and still
    // see the line within one period.
    while (true)
    {
        printf("{\"iteration\" : %ld, \"time_taken\" : %lld, "
               "\"heap_peak_call_bytes\" : %lld, \"heap_net_growth_bytes\" : %lld}\n",
               time_result.iterations, time_result.time_taken_us,
               heap_result.heap_peak_call_bytes, heap_result.heap_net_growth_bytes);
        sleep_ms(1000);
    }
    return 0;
}
