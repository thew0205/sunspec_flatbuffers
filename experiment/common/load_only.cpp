#include "sunspec.h"

// Baseline variant: looks up the model definition (model 160 -- has a
// repeating "module" subgroup, so walk_shallow/walk_deep below have
// something real to traverse) but doesn't touch the group/point tree at
// all. Diffing this against walk_shallow/walk_deep isolates the cost of
// getModelDefinition() itself (and, for the JSON backend, whatever eager
// warm-up its constructor does) from the cost of walking the result.
static volatile uint32_t g_sink = 0;

void walk()
{
    initializeAllModels();
    g_sink = 1;
}
