#include "sunspec.h"

// Walks only the top-level group's own points (not nested subgroups),
// reading every accessor on each one. Field values are folded into a
// checksum (rather than marked `volatile` individually, which doesn't
// portably apply to non-trivial return types like string_view) so the
// calls can't be optimized away, and written to a volatile sink at the end
// so the checksum computation itself can't be optimized away either.
static volatile uint32_t g_checksum = 0;

void walk()
{
    const SunspecModelDef *model = getModelDefinition(SunspecModelList_kModel160);
    const SunspecGroupDef *top = model->group();

    uint32_t checksum = 0;
    for (const auto &pointDefRef : *top->points())
    {
        const auto &point = DEREFERENCE_POINTER_FLATBUFFER(pointDefRef);
        checksum += FlatbufferStringToStringView(point.id()).size();
        checksum += FlatbufferStringToStringView(point.label()).size();
        checksum += FlatbufferStringToStringView(point.units()).size();
        checksum += point.size();
        checksum += static_cast<uint32_t>(point.data_type());
        checksum += static_cast<uint32_t>(point.access());
        checksum += static_cast<uint32_t>(point.mandatory());
        checksum += point.count();
    }
    g_checksum = checksum;
}
