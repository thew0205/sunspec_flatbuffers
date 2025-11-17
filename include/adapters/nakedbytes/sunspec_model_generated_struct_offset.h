
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define OFFSET_SIZE 2

struct enum16;
struct enum32;
struct SunspecModelDef;
struct SunspecModelDefOffset;
struct enum64;
struct bitfield16;
struct bitfield32;
struct SunspecGroupPointDef;
struct SunspecGroupPointDefOffset;
struct bitfield64;
struct sunssf;
struct acc16;
struct SunspecPointData;
struct SunspecPointDataOffset;
struct acc32;
struct pad;
struct acc64;
struct eui48;
struct SunspecPointDef;
struct SunspecPointDefOffset;
struct ipaddr;
struct ipv6addr;

struct String
{
    unsigned char *data;

    String(unsigned char *dataPtr)
    {
        data = dataPtr;
    }
#define STRING_LENGTH_OFFSET 0
    uint16_t length() const
    {
        int16_t offset = STRING_LENGTH_OFFSET;
        return *reinterpret_cast<uint16_t *>(data[offset]);
    }

#define STRING_VALUE_OFFSET 2
    const char *c_str() const
    {
        uint16_t offset = STRING_VALUE_OFFSET;
        return reinterpret_cast<const char *>(&data[offset]);
    }
};

template <typename T>
struct Offset
{
    unsigned char *data;
    Offset(unsigned char *dataPtr)
    {
        data = dataPtr;
    }

    bool is_null() const
    {
        return *reinterpret_cast<uint16_t *>(&data[0]) == 0;
    }

    T value() const
    {
        int16_t offset = *reinterpret_cast<int16_t *>(data);
        return T(&data[offset]);
    }
};

template <typename T>
struct Union
{
    unsigned char *data;
    Union(unsigned char *dataPtr)
    {
        data = dataPtr;
    }

#define UNION_TYPE_OFFSET 0
    uint16_t type() const
    {
        return *reinterpret_cast<uint16_t *>(&data[UNION_TYPE_OFFSET]);
    }

#define DATA_OFFSET 2
    const unsigned char *raw_data() const
    {
        int16_t offset = *reinterpret_cast<uint16_t *>(&data[DATA_OFFSET]) + DATA_OFFSET;

        return (&data[offset]);
    }

    bool is_null() const
    {
        return *reinterpret_cast<uint16_t *>(&data[DATA_OFFSET]) == 0;
    }
};

template <typename T>
struct Vector
{
    unsigned char *data;

    bool is_null() const
    {
        return *reinterpret_cast<uint16_t *>(&data[0]) == 0;
    }

    uint16_t size() const
    {
        int16_t offset = *reinterpret_cast<uint16_t *>(&data[0]);
        return *reinterpret_cast<uint16_t *>(&data[offset]);
    }

    T get(size_t index) const
    {
        int16_t offset = *reinterpret_cast<uint16_t *>(&data[0]) + OFFSET_SIZE + OFFSET_SIZE * index;

        return T(&data[offset]);
    }

    Vector(unsigned char *dataPtr)
    {
        data = dataPtr;
    }
};

struct enum16
{

    unsigned char *data_;

    enum16(unsigned char *data) : data_(data) {}

#define ENUM16_VALUE_OFFSET 0

    uint16_t value() const
    {
        return *reinterpret_cast<uint16_t *>(&data_[ENUM16_VALUE_OFFSET]);
    }
};

enum SunspecPointMandatoryType : uint8_t
{

    SunspecPointMandatoryType_kM,
    SunspecPointMandatoryType_kO,
};

const char *SunspecPointMandatoryType_to_string(SunspecPointMandatoryType value)
{
    switch (value)
    {
    case SunspecPointMandatoryType_kM:
        return "SunspecPointMandatoryType_kM";
    case SunspecPointMandatoryType_kO:
        return "SunspecPointMandatoryType_kO";
    default:
        return NULL;
    }
}

struct enum32
{

    unsigned char *data_;

    enum32(unsigned char *data) : data_(data) {}

#define ENUM32_VALUE_OFFSET 0

    uint32_t value() const
    {
        return *reinterpret_cast<uint32_t *>(&data_[ENUM32_VALUE_OFFSET]);
    }
};

enum SunspecPointData_enum : uint16_t
{

    SunspecPointData_enum_uint16,
    SunspecPointData_enum_int16,
    SunspecPointData_enum_uint32,
    SunspecPointData_enum_int32,
    SunspecPointData_enum_uint64,
    SunspecPointData_enum_int64,
    SunspecPointData_enum_float32,
    SunspecPointData_enum_float64,
    SunspecPointData_enum_string,
    SunspecPointData_enum_pad,
    SunspecPointData_enum_enum16,
    SunspecPointData_enum_enum32,
    SunspecPointData_enum_enum64,
    SunspecPointData_enum_bitfield16,
    SunspecPointData_enum_bitfield32,
    SunspecPointData_enum_bitfield64,
    SunspecPointData_enum_sunssf,
    SunspecPointData_enum_acc16,
    SunspecPointData_enum_acc32,
    SunspecPointData_enum_acc64,
    SunspecPointData_enum_eui48,
    SunspecPointData_enum_ipaddr,
    SunspecPointData_enum_ipv6addr,
};

const char *SunspecPointData_enum_to_string(SunspecPointData_enum value)
{
    switch (value)
    {
    case SunspecPointData_enum_uint16:
        return "SunspecPointData_enum_uint16";
    case SunspecPointData_enum_int16:
        return "SunspecPointData_enum_int16";
    case SunspecPointData_enum_uint32:
        return "SunspecPointData_enum_uint32";
    case SunspecPointData_enum_int32:
        return "SunspecPointData_enum_int32";
    case SunspecPointData_enum_uint64:
        return "SunspecPointData_enum_uint64";
    case SunspecPointData_enum_int64:
        return "SunspecPointData_enum_int64";
    case SunspecPointData_enum_float32:
        return "SunspecPointData_enum_float32";
    case SunspecPointData_enum_float64:
        return "SunspecPointData_enum_float64";
    case SunspecPointData_enum_string:
        return "SunspecPointData_enum_string";
    case SunspecPointData_enum_pad:
        return "SunspecPointData_enum_pad";
    case SunspecPointData_enum_enum16:
        return "SunspecPointData_enum_enum16";
    case SunspecPointData_enum_enum32:
        return "SunspecPointData_enum_enum32";
    case SunspecPointData_enum_enum64:
        return "SunspecPointData_enum_enum64";
    case SunspecPointData_enum_bitfield16:
        return "SunspecPointData_enum_bitfield16";
    case SunspecPointData_enum_bitfield32:
        return "SunspecPointData_enum_bitfield32";
    case SunspecPointData_enum_bitfield64:
        return "SunspecPointData_enum_bitfield64";
    case SunspecPointData_enum_sunssf:
        return "SunspecPointData_enum_sunssf";
    case SunspecPointData_enum_acc16:
        return "SunspecPointData_enum_acc16";
    case SunspecPointData_enum_acc32:
        return "SunspecPointData_enum_acc32";
    case SunspecPointData_enum_acc64:
        return "SunspecPointData_enum_acc64";
    case SunspecPointData_enum_eui48:
        return "SunspecPointData_enum_eui48";
    case SunspecPointData_enum_ipaddr:
        return "SunspecPointData_enum_ipaddr";
    case SunspecPointData_enum_ipv6addr:
        return "SunspecPointData_enum_ipv6addr";
    default:
        return NULL;
    }
}

struct pad
{

    unsigned char *data_;

    pad(unsigned char *data) : data_(data) {}

#define PAD_VALUE_OFFSET 0

    uint16_t value() const
    {
        return *reinterpret_cast<uint16_t *>(&data_[PAD_VALUE_OFFSET]);
    }
};

struct enum64
{

    unsigned char *data_;

    enum64(unsigned char *data) : data_(data) {}

#define ENUM64_VALUE_OFFSET 0

    uint64_t value() const
    {
        return *reinterpret_cast<uint64_t *>(&data_[ENUM64_VALUE_OFFSET]);
    }
};

struct bitfield16
{

    unsigned char *data_;

    bitfield16(unsigned char *data) : data_(data) {}

#define BITFIELD16_VALUE_OFFSET 0

    uint16_t value() const
    {
        return *reinterpret_cast<uint16_t *>(&data_[BITFIELD16_VALUE_OFFSET]);
    }
};

struct bitfield32
{

    unsigned char *data_;

    bitfield32(unsigned char *data) : data_(data) {}

#define BITFIELD32_VALUE_OFFSET 0

    uint32_t value() const
    {
        return *reinterpret_cast<uint32_t *>(&data_[BITFIELD32_VALUE_OFFSET]);
    }
};

struct bitfield64
{

    unsigned char *data_;

    bitfield64(unsigned char *data) : data_(data) {}

#define BITFIELD64_VALUE_OFFSET 0

    uint64_t value() const
    {
        return *reinterpret_cast<uint64_t *>(&data_[BITFIELD64_VALUE_OFFSET]);
    }
};

struct sunssf
{

    unsigned char *data_;

    sunssf(unsigned char *data) : data_(data) {}

#define SUNSSF_VALUE_OFFSET 0

    uint16_t value() const
    {
        return *reinterpret_cast<uint16_t *>(&data_[SUNSSF_VALUE_OFFSET]);
    }
};

struct acc16
{

    unsigned char *data_;

    acc16(unsigned char *data) : data_(data) {}

#define ACC16_VALUE_OFFSET 0

    uint16_t value() const
    {
        return *reinterpret_cast<uint16_t *>(&data_[ACC16_VALUE_OFFSET]);
    }
};

struct acc32
{

    unsigned char *data_;

    acc32(unsigned char *data) : data_(data) {}

#define ACC32_VALUE_OFFSET 0

    uint32_t value() const
    {
        return *reinterpret_cast<uint32_t *>(&data_[ACC32_VALUE_OFFSET]);
    }
};

struct acc64
{

    unsigned char *data_;

    acc64(unsigned char *data) : data_(data) {}

#define ACC64_VALUE_OFFSET 0

    uint64_t value() const
    {
        return *reinterpret_cast<uint64_t *>(&data_[ACC64_VALUE_OFFSET]);
    }
};

struct eui48
{

    unsigned char *data_;

    eui48(unsigned char *data) : data_(data) {}

#define EUI48_VALUE0_OFFSET 0
#define EUI48_VALUE1_OFFSET 2
#define EUI48_VALUE2_OFFSET 4

    uint16_t value0() const
    {
        return *reinterpret_cast<uint16_t *>(&data_[EUI48_VALUE0_OFFSET]);
    }

    uint16_t value1() const
    {
        return *reinterpret_cast<uint16_t *>(&data_[EUI48_VALUE1_OFFSET]);
    }

    uint16_t value2() const
    {
        return *reinterpret_cast<uint16_t *>(&data_[EUI48_VALUE2_OFFSET]);
    }
};

struct ipaddr
{

    unsigned char *data_;

    ipaddr(unsigned char *data) : data_(data) {}

#define IPADDR_VALUE0_OFFSET 0
#define IPADDR_VALUE1_OFFSET 2
#define IPADDR_VALUE2_OFFSET 4
#define IPADDR_VALUE3_OFFSET 6

    uint16_t value0() const
    {
        return *reinterpret_cast<uint16_t *>(&data_[IPADDR_VALUE0_OFFSET]);
    }

    uint16_t value1() const
    {
        return *reinterpret_cast<uint16_t *>(&data_[IPADDR_VALUE1_OFFSET]);
    }

    uint16_t value2() const
    {
        return *reinterpret_cast<uint16_t *>(&data_[IPADDR_VALUE2_OFFSET]);
    }

    uint16_t value3() const
    {
        return *reinterpret_cast<uint16_t *>(&data_[IPADDR_VALUE3_OFFSET]);
    }
};

struct ipv6addr
{

    unsigned char *data_;

    ipv6addr(unsigned char *data) : data_(data) {}

#define IPV6ADDR_VALUE0_OFFSET 0
#define IPV6ADDR_VALUE1_OFFSET 2
#define IPV6ADDR_VALUE2_OFFSET 4
#define IPV6ADDR_VALUE3_OFFSET 6
#define IPV6ADDR_VALUE4_OFFSET 8
#define IPV6ADDR_VALUE5_OFFSET 10

    uint16_t value0() const
    {
        return *reinterpret_cast<uint16_t *>(&data_[IPV6ADDR_VALUE0_OFFSET]);
    }

    uint16_t value1() const
    {
        return *reinterpret_cast<uint16_t *>(&data_[IPV6ADDR_VALUE1_OFFSET]);
    }

    uint16_t value2() const
    {
        return *reinterpret_cast<uint16_t *>(&data_[IPV6ADDR_VALUE2_OFFSET]);
    }

    uint16_t value3() const
    {
        return *reinterpret_cast<uint16_t *>(&data_[IPV6ADDR_VALUE3_OFFSET]);
    }

    uint16_t value4() const
    {
        return *reinterpret_cast<uint16_t *>(&data_[IPV6ADDR_VALUE4_OFFSET]);
    }

    uint16_t value5() const
    {
        return *reinterpret_cast<uint16_t *>(&data_[IPV6ADDR_VALUE5_OFFSET]);
    }
};

struct SunspecPointData
{

    unsigned char *data_;

    SunspecPointData(unsigned char *data) : data_(data) {}

#define SUNSPECPOINTDATA_TYPE_OFFSET 0
#define SUNSPECPOINTDATA_DATA_OFFSET 2
    SunspecPointData_enum type() const
    {
        return *reinterpret_cast<SunspecPointData_enum *>(&data_[SUNSPECPOINTDATA_TYPE_OFFSET]);
    }

    bool is_null() const
    {
        return (type() == 0) or (*reinterpret_cast<uint16_t *>(&data_[SUNSPECPOINTDATA_DATA_OFFSET]) == 0);
    }

    unsigned char *raw_data() const
    {
        const int16_t offset = *reinterpret_cast<uint16_t *>(&data_[SUNSPECPOINTDATA_DATA_OFFSET]) + SUNSPECPOINTDATA_DATA_OFFSET;
        return (&data_[offset]);
    }
    uint16_t data_as_uint16() const
    {
        return type() == SunspecPointData_enum_uint16 ? *reinterpret_cast<uint16_t *>(raw_data()) : 0;
    }

    int16_t data_as_int16() const
    {
        return type() == SunspecPointData_enum_int16 ? *reinterpret_cast<int16_t *>(raw_data()) : 0;
    }

    uint32_t data_as_uint32() const
    {
        return type() == SunspecPointData_enum_uint32 ? *reinterpret_cast<uint32_t *>(raw_data()) : 0;
    }

    int32_t data_as_int32() const
    {
        return type() == SunspecPointData_enum_int32 ? *reinterpret_cast<int32_t *>(raw_data()) : 0;
    }

    uint64_t data_as_uint64() const
    {
        return type() == SunspecPointData_enum_uint64 ? *reinterpret_cast<uint64_t *>(raw_data()) : 0;
    }

    int64_t data_as_int64() const
    {
        return type() == SunspecPointData_enum_int64 ? *reinterpret_cast<int64_t *>(raw_data()) : 0;
    }

    float data_as_float32() const
    {
        return type() == SunspecPointData_enum_float32 ? *reinterpret_cast<float *>(raw_data()) : 0;
    }

    double data_as_float64() const
    {
        return type() == SunspecPointData_enum_float64 ? *reinterpret_cast<double *>(raw_data()) : 0;
    }

    Offset<String> data_as_string() const
    {
        return type() == SunspecPointData_enum_string ? Offset<String>(raw_data()) : 0;
    }

    pad data_as_pad() const
    {
        return type() == SunspecPointData_enum_pad ? pad(raw_data()) : 0;
    }

    enum16 data_as_enum16() const
    {
        return type() == SunspecPointData_enum_enum16 ? enum16(raw_data()) : 0;
    }

    enum32 data_as_enum32() const
    {
        return type() == SunspecPointData_enum_enum32 ? enum32(raw_data()) : 0;
    }

    enum64 data_as_enum64() const
    {
        return type() == SunspecPointData_enum_enum64 ? enum64(raw_data()) : 0;
    }

    bitfield16 data_as_bitfield16() const
    {
        return type() == SunspecPointData_enum_bitfield16 ? bitfield16(raw_data()) : 0;
    }

    bitfield32 data_as_bitfield32() const
    {
        return type() == SunspecPointData_enum_bitfield32 ? bitfield32(raw_data()) : 0;
    }

    bitfield64 data_as_bitfield64() const
    {
        return type() == SunspecPointData_enum_bitfield64 ? bitfield64(raw_data()) : 0;
    }

    sunssf data_as_sunssf() const
    {
        return type() == SunspecPointData_enum_sunssf ? sunssf(raw_data()) : 0;
    }

    acc16 data_as_acc16() const
    {
        return type() == SunspecPointData_enum_acc16 ? acc16(raw_data()) : 0;
    }

    acc32 data_as_acc32() const
    {
        return type() == SunspecPointData_enum_acc32 ? acc32(raw_data()) : 0;
    }

    acc64 data_as_acc64() const
    {
        return type() == SunspecPointData_enum_acc64 ? acc64(raw_data()) : 0;
    }

    eui48 data_as_eui48() const
    {
        return type() == SunspecPointData_enum_eui48 ? eui48(raw_data()) : 0;
    }

    ipaddr data_as_ipaddr() const
    {
        return type() == SunspecPointData_enum_ipaddr ? ipaddr(raw_data()) : 0;
    }

    ipv6addr data_as_ipv6addr() const
    {
        return type() == SunspecPointData_enum_ipv6addr ? ipv6addr(raw_data()) : 0;
    }
};

enum SunspecPointAccessType : uint8_t
{

    SunspecPointAccessType_kR,
    SunspecPointAccessType_kRW,
};

const char *SunspecPointAccessType_to_string(SunspecPointAccessType value)
{
    switch (value)
    {
    case SunspecPointAccessType_kR:
        return "SunspecPointAccessType_kR";
    case SunspecPointAccessType_kRW:
        return "SunspecPointAccessType_kRW";
    default:
        return NULL;
    }
}

struct SunspecPointDef
{

    unsigned char *data_;

    SunspecPointDef(unsigned char *data) : data_(data) {}

#define SUNSPECPOINTDEF_ID_OFFSET 0
#define SUNSPECPOINTDEF_SF_ID_OFFSET 2
#define SUNSPECPOINTDEF_UNITS_OFFSET 4
#define SUNSPECPOINTDEF_LABEL_OFFSET 6
#define SUNSPECPOINTDEF_DATA_TYPE_OFFSET 8
#define SUNSPECPOINTDEF_DATA_OFFSET 10
#define SUNSPECPOINTDEF_COUNT_OFFSET 12
#define SUNSPECPOINTDEF_SIZE_OFFSET 13
#define SUNSPECPOINTDEF_SF_OFFSET 14
#define SUNSPECPOINTDEF_ACCESS_OFFSET 15
#define SUNSPECPOINTDEF_MANDATORY_OFFSET 16
#define SUNSPECPOINTDEF_PAD17_OFFSET 17

    Offset<String> id() const
    {
        const int16_t offset = SUNSPECPOINTDEF_ID_OFFSET;
        return Offset<String>(&data_[offset]);
    }

    Offset<String> sf_id() const
    {
        const int16_t offset = SUNSPECPOINTDEF_SF_ID_OFFSET;
        return Offset<String>(&data_[offset]);
    }

    Offset<String> units() const
    {
        const int16_t offset = SUNSPECPOINTDEF_UNITS_OFFSET;
        return Offset<String>(&data_[offset]);
    }

    Offset<String> label() const
    {
        const int16_t offset = SUNSPECPOINTDEF_LABEL_OFFSET;
        return Offset<String>(&data_[offset]);
    }

    SunspecPointData_enum data_type() const
    {
        return *reinterpret_cast<SunspecPointData_enum *>(&data_[SUNSPECPOINTDEF_DATA_TYPE_OFFSET]);
    }

    SunspecPointData data() const
    {
        const int16_t offset = SUNSPECPOINTDEF_DATA_OFFSET - 2;
        return SunspecPointData(&data_[offset]);
    }

    uint8_t count() const
    {
        return *reinterpret_cast<uint8_t *>(&data_[SUNSPECPOINTDEF_COUNT_OFFSET]);
    }

    uint8_t size() const
    {
        return *reinterpret_cast<uint8_t *>(&data_[SUNSPECPOINTDEF_SIZE_OFFSET]);
    }

    int8_t sf() const
    {
        return *reinterpret_cast<int8_t *>(&data_[SUNSPECPOINTDEF_SF_OFFSET]);
    }

    SunspecPointAccessType access() const
    {
        return *reinterpret_cast<SunspecPointAccessType *>(&data_[SUNSPECPOINTDEF_ACCESS_OFFSET]);
    }

    SunspecPointMandatoryType mandatory() const
    {
        return *reinterpret_cast<SunspecPointMandatoryType *>(&data_[SUNSPECPOINTDEF_MANDATORY_OFFSET]);
    }
};

struct SunspecPointDefOffset
{

    unsigned char *data_;

    SunspecPointDefOffset(unsigned char *data) : data_(data) {}

    bool is_null()
    {
        return *reinterpret_cast<uint16_t *>(data_) == 0;
    }

    SunspecPointDef value()
    {
        const int16_t offset = *reinterpret_cast<int16_t *>(data_);
        return SunspecPointDef(&data_[offset]);
    }
};
enum SunspecGroupType : uint8_t
{

    SunspecGroupType_kGroup,
    SunspecGroupType_kSync,
};

const char *SunspecGroupType_to_string(SunspecGroupType value)
{
    switch (value)
    {
    case SunspecGroupType_kGroup:
        return "SunspecGroupType_kGroup";
    case SunspecGroupType_kSync:
        return "SunspecGroupType_kSync";
    default:
        return NULL;
    }
}

struct SunspecGroupPointDef
{

    unsigned char *data_;

    SunspecGroupPointDef(unsigned char *data) : data_(data) {}

#define SUNSPECGROUPPOINTDEF_ID_OFFSET 0
#define SUNSPECGROUPPOINTDEF_COUNT_POINT_ID_OFFSET 2
#define SUNSPECGROUPPOINTDEF_POINTS_OFFSET 4
#define SUNSPECGROUPPOINTDEF_GROUPS_OFFSET 6
#define SUNSPECGROUPPOINTDEF_LABEL_OFFSET 8
#define SUNSPECGROUPPOINTDEF_COUNT_OFFSET 10
#define SUNSPECGROUPPOINTDEF_TYPE_OFFSET 11

    Offset<String> id() const
    {
        const int16_t offset = SUNSPECGROUPPOINTDEF_ID_OFFSET;
        return Offset<String>(&data_[offset]);
    }

    Offset<String> count_point_id() const
    {
        const int16_t offset = SUNSPECGROUPPOINTDEF_COUNT_POINT_ID_OFFSET;
        return Offset<String>(&data_[offset]);
    }

    Vector<Offset<SunspecPointDef>> points() const
    {
        const int16_t offset = SUNSPECGROUPPOINTDEF_POINTS_OFFSET;
        return Vector<Offset<SunspecPointDef>>(&data_[offset]);
    }

    Vector<Offset<SunspecGroupPointDef>> groups() const
    {
        const int16_t offset = SUNSPECGROUPPOINTDEF_GROUPS_OFFSET;
        return Vector<Offset<SunspecGroupPointDef>>(&data_[offset]);
    }

    Offset<String> label() const
    {
        const int16_t offset = SUNSPECGROUPPOINTDEF_LABEL_OFFSET;
        return Offset<String>(&data_[offset]);
    }

    uint8_t count() const
    {
        return *reinterpret_cast<uint8_t *>(&data_[SUNSPECGROUPPOINTDEF_COUNT_OFFSET]);
    }

    SunspecGroupType type() const
    {
        return *reinterpret_cast<SunspecGroupType *>(&data_[SUNSPECGROUPPOINTDEF_TYPE_OFFSET]);
    }
};

struct SunspecGroupPointDefOffset
{

    unsigned char *data_;

    SunspecGroupPointDefOffset(unsigned char *data) : data_(data) {}

    bool is_null()
    {
        return *reinterpret_cast<uint16_t *>(data_) == 0;
    }

    SunspecGroupPointDef value()
    {
        const int16_t offset = *reinterpret_cast<int16_t *>(data_);
        return SunspecGroupPointDef(&data_[offset]);
    }
};

struct SunspecModelDef
{

    unsigned char *data_;

    SunspecModelDef(unsigned char *data) : data_(data) {}

#define SUNSPECMODELDEF_ID_OFFSET 0
#define SUNSPECMODELDEF_GROUP_OFFSET 2

    uint16_t id() const
    {
        return *reinterpret_cast<uint16_t *>(&data_[SUNSPECMODELDEF_ID_OFFSET + 2 * OFFSET_SIZE]);
    }

    Offset<SunspecGroupPointDef> group() const
    {
        const int16_t offset = SUNSPECMODELDEF_GROUP_OFFSET + 2 * OFFSET_SIZE;
        return Offset<SunspecGroupPointDef>(&data_[offset]);
    }
};

struct SunspecModelDefOffset
{

    unsigned char *data_;

    SunspecModelDefOffset(unsigned char *data) : data_(data) {}

    bool is_null()
    {
        return *reinterpret_cast<uint16_t *>(data_) == 0;
    }

    SunspecModelDef value()
    {
        const int16_t offset = *reinterpret_cast<int16_t *>(data_);
        return SunspecModelDef(&data_[offset]);
    }
};
