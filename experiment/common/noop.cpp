// True no-op baseline: doesn't reference anything from the sunspec library,
// so the linker pulls in none of libsunspec.a's object files. Gives a
// harness-only (loop + mallinfo2 profiling pass + printf) flash/RAM/timing
// floor to net the other variants against -- identical in theory across all
// three backend configs, since none of them link any sunspec code here.
static volatile int g_sink = 0;

void walk()
{
    g_sink = 1;
}
