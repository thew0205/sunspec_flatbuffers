#include "adapters/c_define/c_model_definition.h"
#include "sunspec.h"

#include <algorithm>

using std::string_view;
using std::vector;

/**
 * @file model_definition.cpp
 *
 */
std::vector<SunspecModelDef> modelDefList{};
bool hasInitList{false};

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


void initializeAllModels()
{
    if (!hasInitList)
    {
        // Reserve up front so populating the list doesn't trigger
        // reallocation (and therefore move-construction) of the models
        // already inserted; not required for correctness (SunspecModelDef
        // is movable), just avoids redoing that work on every growth step.
        modelDefList.reserve(112);

        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef1()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef2()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef3()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef4()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef5()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef6()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef7()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef8()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef9()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef10()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef11()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef12()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef13()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef14()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef15()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef16()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef17()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef18()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef19()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef101()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef102()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef103()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef111()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef112()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef113()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef120()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef121()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef122()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef123()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef124()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef125()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef126()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef127()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef128()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef129()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef130()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef131()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef132()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef133()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef134()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef135()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef136()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef137()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef138()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef139()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef140()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef141()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef142()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef143()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef144()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef145()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef160()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef201()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef202()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef203()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef204()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef211()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef212()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef213()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef214()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef220()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef302()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef303()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef304()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef305()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef306()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef307()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef308()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef401()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef402()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef403()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef404()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef501()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef502()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef601()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef701()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef702()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef703()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef704()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef705()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef706()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef707()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef708()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef709()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef710()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef711()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef712()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef713()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef714()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef715()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef801()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef802()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef803()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef804()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef805()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef806()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef807()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef808()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef809()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef63001()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef63002()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef64001()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef64020()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef64101()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef64111()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef64112()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef64410()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef64411()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef64412()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef64413()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef64414()));
        modelDefList.emplace_back(std::move(SunspecModelDef::modelDef64415()));

        hasInitList = true;
    }
}

void deinitializeAllModels(){
    modelDefList.clear();
    modelDefList.shrink_to_fit(); 
    hasInitList = false;
}

const SunspecModelDef *getModelDefinition(SunspecModelList id)
{
    initializeAllModels();

    auto modelDefIte = std::find_if(modelDefList.cbegin(), modelDefList.cend(), [id](const SunspecModelDef &modelDef)
                                     { return modelDef.id() == id; });
    return modelDefIte == modelDefList.cend() ? nullptr : &(*modelDefIte);
}
