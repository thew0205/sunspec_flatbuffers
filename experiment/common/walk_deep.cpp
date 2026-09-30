#include "sunspec.h"

// Recursively walks the whole group/point tree (top-level points plus every
// nested subgroup's points), reading every accessor on each point and
// group. See walk_shallow.cpp for why field values are folded into a
// checksum instead of individually marked volatile.
static volatile uint32_t g_checksum = 0;

static void walk_group(const SunspecGroupDef &group, size_t &checksum)
{
    checksum += FlatbufferStringToStringView(group.id()).size();
    checksum += FlatbufferStringToStringView(group.label()).size();
    checksum += group.count();

    for (const auto &pointDefRef : *group.points())
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

    for (const auto &groupDefRef : *group.groups())
    {
        const auto &subgroup = DEREFERENCE_POINTER_FLATBUFFER(groupDefRef);
        walk_group(subgroup, checksum);
    }
}

void walk()
{
    const SunspecModelDef *model = getModelDefinition(SunspecModelList_kModel160);
    const SunspecGroupDef *top = model->group();

    size_t checksum = 0;
    walk_group(*top, checksum);
    g_checksum = checksum;
}
