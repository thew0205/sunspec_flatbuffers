#include "adapters/c_define/c_model_definition.h"
#include "sunspec.h"

#include <algorithm>

using std::string_view;
using std::vector;

/**
 * @file model_definition.cpp
 *
 */
// std::vector<const SunspecModelDef *> SunspecModelDef::modelDefList{};
// bool SunspecModelDef ::hasInitList{false};

SunspecPointDef::SunspecPointDef(const char *id, uint16_t count, const char *count_point_id, const char *sf_id, const char *units, uint16_t size, SunspecPointData data_type, SunspecPointDataVariant data, SunspecPointAccessType access, SunspecPointMandatoryType mandatory, const char *label) : id_{id}, count_point_id_{count_point_id}, sf_id_{sf_id}, units_{units}, label_{label}, count_{count}, size_{size}, data_{data}, access_{access}, mandatory_{mandatory}
{
    if (this->data_type() != SunspecPointData_NONE)
    {
        // Caller already supplied a real value; don't clobber it with the type's default.
        if (SunspecPointData_kStringx != data_type)
        {
            size_ = this->size();
        }
        return;
    }

    switch (data_type)
    {
    case SunspecPointData_kSint16:
        data_ = kSint16(kSint16UnimplementedValue);
        break;
    case SunspecPointData_kSint32:
        data_ = kSint32(kSint32UnimplementedValue);
        break;
    case SunspecPointData_kSint64:
        data_ = kSint64(kSint64UnimplementedValue);
        break;
    case SunspecPointData_kRaw16:
        data_ = kRaw16(kRaw16UnimplementedValue);
        break;
    case SunspecPointData_kUint16:
        data_ = kUint16(kUint16UnimplementedValue);
        break;
    case SunspecPointData_kUint32:
        data_ = kUint32(kUint32UnimplementedValue);
        break;
    case SunspecPointData_kUint64:
        data_ = kUint64(kUint64UnimplementedValue);
        break;
    case SunspecPointData_kAcc16:
        data_ = kAcc16(kAcc16UnimplementedValue);
        break;
    case SunspecPointData_kAcc32:
        data_ = kAcc32(kAcc32UnimplementedValue);
        break;
    case SunspecPointData_kAcc64:
        data_ = kAcc64(kAcc64UnimplementedValue);
        break;
    case SunspecPointData_kBitfield16:
        data_ = kBitfield16(kBit16UnimplementedValue);
        break;
    case SunspecPointData_kBitfield32:
        data_ = kBitfield32(kBit32UnimplementedValue);
        break;
    case SunspecPointData_kBitfield64:
        data_ = kBitfield64(kBit64UnimplementedValue);
        break;
    case SunspecPointData_kEnum16:
        data_ = kEnum16(kEnum16UnimplementedValue);
        break;
    case SunspecPointData_kEnum32:
        data_ = kEnum32(kEnum32UnimplementedValue);
        break;
    case SunspecPointData_kFloat32:
        data_ = kFloat32(kFloat32UnimplementedValue);
        break;
    case SunspecPointData_kFloat64:
        data_ = kFloat64(kFloat64UnimplementedValue);
        break;
    case SunspecPointData_kStringx:
        data_ = kStringx(kStringUnimplementedValue);
        break;
    case SunspecPointData_kSunsSf:
        data_ = kSunsSf(kSunsSfUnimplementedValue);
        break;
    case SunspecPointData_kPad16:
        data_ = kPad16(kPad16UnimplementedValue);
        break;
    case SunspecPointData_kIpAddr:
        data_ = kIpAddr(kIpAddrUnimplementedValue.octet1, kIpAddrUnimplementedValue.octet2, kIpAddrUnimplementedValue.octet3, kIpAddrUnimplementedValue.octet4);
        break;
    case SunspecPointData_kIpv6Addr:
        // NOTE: sunspec.h has no kIpv6AddrUnimplementedValue constant yet; zero-filled as a placeholder default.
        data_ = kIpv6Addr(std::array<uint8_t, 24>{});
        break;
    case SunspecPointData_kEui48:
        // NOTE: sunspec.h has no kEui48UnimplementedValue constant yet; zero-filled as a placeholder default.
        data_ = kEui48(std::array<uint8_t, 3>{});
        break;
    case SunspecPointData_NONE:
    default:
        break;
    }

    if (SunspecPointData_kStringx != data_type)
    {
        size_ = this->size();
    }
}

uint16_t SunspecPointDef::size() const
{
    switch (this->data_type())
    {

    case SunspecPointData_kSint16:
    case SunspecPointData_kSunsSf:
    case SunspecPointData_kPad16:
    case SunspecPointData_kBitfield16:
    case SunspecPointData_kAcc16:
    case SunspecPointData_kEnum16:
    case SunspecPointData_kRaw16:
    case SunspecPointData_kUint16:
        return 1;
        break;

    case SunspecPointData_kSint32:
    case SunspecPointData_kUint32:
    case SunspecPointData_kAcc32:
    case SunspecPointData_kBitfield32:
    case SunspecPointData_kEnum32:
    case SunspecPointData_kIpAddr:
    case SunspecPointData_kFloat32:
        return 2;

    case SunspecPointData_kEui48:
        return 3;

    case SunspecPointData_kSint64:
    case SunspecPointData_kUint64:
    case SunspecPointData_kAcc64:
    case SunspecPointData_kBitfield64:
    case SunspecPointData_kFloat64:

        return 4;

    case SunspecPointData_kIpv6Addr:
        return 6;

    case SunspecPointData_kStringx:
        return size_;

    case SunspecPointData_NONE:
    default:
        return 0;
        break;
    }
}

SunspecGroupDef::SunspecGroupDef(const string_view &id, const string_view &label, uint16_t count, const string_view &count_point_id, SunspecGroupType type, std::vector<SunspecPointDef> &&points, std::vector<SunspecGroupDef> &&groups) : id_{id}, label_{label}, count_{count}, count_point_id_{count_point_id}, type_{type}, points_{std::move(points)}, groups_{std::move(groups)}
{
}


SunspecModelDef::SunspecModelDef(SunspecModelList _id, const string_view &_label, SunspecGroupDef &&_topLevelGroupPoint) : id_{_id}, label_{_label}, topLevelGroupPoint_{std::move(_topLevelGroupPoint)}
{
}

// void SunspecModelDef::initList()
// {

//     if (!hasInitList)
//     {
//         modelDefList.push_back(&modelDef1);
//         modelDefList.push_back(&modelDef2);
//         modelDefList.push_back(&modelDef3);
//         modelDefList.push_back(&modelDef4);
//         modelDefList.push_back(&modelDef5);
//         modelDefList.push_back(&modelDef6);
//         modelDefList.push_back(&modelDef7);
//         modelDefList.push_back(&modelDef8);
//         modelDefList.push_back(&modelDef9);
//         modelDefList.push_back(&modelDef10);
//         modelDefList.push_back(&modelDef11);
//         modelDefList.push_back(&modelDef12);
//         modelDefList.push_back(&modelDef13);
//         modelDefList.push_back(&modelDef14);
//         modelDefList.push_back(&modelDef15);
//         modelDefList.push_back(&modelDef16);
//         modelDefList.push_back(&modelDef17);
//         modelDefList.push_back(&modelDef18);
//         modelDefList.push_back(&modelDef19);
//         modelDefList.push_back(&modelDef101);
//         modelDefList.push_back(&modelDef102);
//         modelDefList.push_back(&modelDef103);
//         modelDefList.push_back(&modelDef111);
//         modelDefList.push_back(&modelDef112);
//         modelDefList.push_back(&modelDef113);
//         modelDefList.push_back(&modelDef120);
//         modelDefList.push_back(&modelDef121);
//         modelDefList.push_back(&modelDef122);
//         modelDefList.push_back(&modelDef123);
//         modelDefList.push_back(&modelDef124);
//         modelDefList.push_back(&modelDef125);
//         modelDefList.push_back(&modelDef126);
//         modelDefList.push_back(&modelDef127);
//         modelDefList.push_back(&modelDef128);
//         modelDefList.push_back(&modelDef129);
//         modelDefList.push_back(&modelDef130);
//         modelDefList.push_back(&modelDef131);
//         modelDefList.push_back(&modelDef132);
//         modelDefList.push_back(&modelDef133);
//         modelDefList.push_back(&modelDef134);
//         modelDefList.push_back(&modelDef135);
//         modelDefList.push_back(&modelDef136);
//         modelDefList.push_back(&modelDef137);
//         modelDefList.push_back(&modelDef138);
//         modelDefList.push_back(&modelDef139);
//         modelDefList.push_back(&modelDef140);
//         modelDefList.push_back(&modelDef141);
//         modelDefList.push_back(&modelDef142);
//         modelDefList.push_back(&modelDef143);
//         modelDefList.push_back(&modelDef144);
//         modelDefList.push_back(&modelDef145);
//         modelDefList.push_back(&modelDef160);
//         modelDefList.push_back(&modelDef201);
//         modelDefList.push_back(&modelDef202);
//         modelDefList.push_back(&modelDef203);
//         modelDefList.push_back(&modelDef204);
//         modelDefList.push_back(&modelDef211);
//         modelDefList.push_back(&modelDef212);
//         modelDefList.push_back(&modelDef213);
//         modelDefList.push_back(&modelDef214);
//         modelDefList.push_back(&modelDef220);
//         modelDefList.push_back(&modelDef302);
//         modelDefList.push_back(&modelDef303);
//         modelDefList.push_back(&modelDef304);
//         modelDefList.push_back(&modelDef305);
//         modelDefList.push_back(&modelDef306);
//         modelDefList.push_back(&modelDef307);
//         modelDefList.push_back(&modelDef308);
//         modelDefList.push_back(&modelDef401);
//         modelDefList.push_back(&modelDef402);
//         modelDefList.push_back(&modelDef403);
//         modelDefList.push_back(&modelDef404);
//         modelDefList.push_back(&modelDef501);
//         modelDefList.push_back(&modelDef502);
//         modelDefList.push_back(&modelDef601);
//         modelDefList.push_back(&modelDef701);
//         modelDefList.push_back(&modelDef702);
//         modelDefList.push_back(&modelDef703);
//         modelDefList.push_back(&modelDef704);
//         modelDefList.push_back(&modelDef705);
//         modelDefList.push_back(&modelDef706);
//         modelDefList.push_back(&modelDef707);
//         modelDefList.push_back(&modelDef708);
//         modelDefList.push_back(&modelDef709);
//         modelDefList.push_back(&modelDef710);
//         modelDefList.push_back(&modelDef711);
//         modelDefList.push_back(&modelDef712);
//         modelDefList.push_back(&modelDef713);
//         modelDefList.push_back(&modelDef714);
//         modelDefList.push_back(&modelDef715);
//         modelDefList.push_back(&modelDef801);
//         modelDefList.push_back(&modelDef802);
//         modelDefList.push_back(&modelDef803);
//         modelDefList.push_back(&modelDef804);
//         modelDefList.push_back(&modelDef805);
//         modelDefList.push_back(&modelDef806);
//         modelDefList.push_back(&modelDef807);
//         modelDefList.push_back(&modelDef808);
//         modelDefList.push_back(&modelDef809);
//         modelDefList.push_back(&modelDef63001);
//         modelDefList.push_back(&modelDef63002);
//         modelDefList.push_back(&modelDef64001);
//         modelDefList.push_back(&modelDef64020);
//         modelDefList.push_back(&modelDef64101);
//         modelDefList.push_back(&modelDef64111);
//         modelDefList.push_back(&modelDef64112);
//         modelDefList.push_back(&modelDef64410);
//         modelDefList.push_back(&modelDef64411);
//         modelDefList.push_back(&modelDef64412);
//         modelDefList.push_back(&modelDef64413);
//         modelDefList.push_back(&modelDef64414);
//         modelDefList.push_back(&modelDef64415);

//         // hasInitList = true;
//     }
// }

// void SunspecModelDef::deinitList()
// {
//     if (hasInitList)
//     {
//         // NOTE: modelDefList now holds addresses of static SunspecModelDef::modelDef<id>
//         // member variables (static storage duration), not heap allocations, so they must
//         // not be deleted here -- only the bookkeeping vector itself is cleared.
//         modelDefList.clear();
//         // Hack to make sure that the memory for the vector is dealloced even thought there is no need for it to be deallocated since it is a global variable. This is needed for the test to check for memory leaks.
//         vector<const SunspecModelDef *>().swap(modelDefList);
//         hasInitList = false;
//     }
// }
// const SunspecModelDef *SunspecModelDef::getModelDefinition(SunspecModelList id)
// {

//     auto modelDefIte = std::find_if(modelDefList.cbegin(), modelDefList.cend(), [id](const SunspecModelDef *pModelDef)
//                                     { return pModelDef->id() == id; });
//     return modelDefIte == modelDefList.cend() ? nullptr : *modelDefIte;
// }
