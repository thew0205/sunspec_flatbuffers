
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <type_traits>
#include <vector>

#define OFFSET_SIZE 2

struct Uint64;
struct Stringx;
struct Acc32;
struct Bitfield16;
struct Enum16;
struct Bitfield32;
struct Acc16;
struct Eui48;
struct Sint16;
struct SunspecGroupDef;
struct Sint64;
struct Pad16;
struct Bitfield64;
struct Sint32;
struct IpAddr;
struct Ipv6Addr;
struct SunspecPointData;
struct SunspecPointDef;
struct Raw16;
struct Uint16;
struct SunspecModelDef;
struct Uint32;
struct Enum32;
struct Float32;
struct Acc64;
struct SunsSf;
struct Enum64;
struct Float64;

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
        return *reinterpret_cast<uint16_t *>(&data[offset]);
    }

#define STRING_VALUE_OFFSET 2
    const char *c_str() const
    {
        uint16_t offset = STRING_VALUE_OFFSET;
        return reinterpret_cast<const char *>(&data[offset]);
    }
};

template <typename T, typename Enable = void>
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
        int16_t offset = *reinterpret_cast<int16_t *>(&data[0]);
        return T(&data[offset]);
    }
};

template <typename T>
struct Offset<T, typename std::enable_if<(std::is_integral<T>::value || std::is_floating_point<T>::value)>::type>
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
        int16_t offset = *reinterpret_cast<int16_t *>(&data[0]);
        return static_cast<T>(data[offset]);
    }
};

template <typename T>
struct is_Offset_Type : std::false_type
{
};
template <typename T>
struct is_Offset_Type<Offset<T>> : std::true_type
{
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

template <typename T, typename Enable = void>
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
        int16_t offset = *reinterpret_cast<uint16_t *>(&data[0]) + OFFSET_SIZE + T::nakedbytes_sizeof * index;

        return T(&data[offset]);
    }

    Vector(unsigned char *dataPtr)
    {
        data = dataPtr;
    }
};

template <typename T>
struct Vector<T, typename std::enable_if<(std::is_floating_point<T>::value || std::is_integral<T>::value)>::type>
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

        return static_cast<T>(data[offset]);
    }

    Vector(unsigned char *dataPtr)
    {
        data = dataPtr;
    }
};

struct Uint64
{

    static constexpr size_t nakedbytes_sizeof = 8;

    unsigned char *data_;

    Uint64(unsigned char *data) : data_(data) {}

#define UINT64_VALUE_OFFSET 0
#define UINT64_ALIGNMENT 8
#define UINT64_SIZE 8

    uint64_t value() const
    {
        return *reinterpret_cast<uint64_t *>(&data_[UINT64_VALUE_OFFSET]);
    }
};

struct Stringx
{

    static constexpr size_t nakedbytes_sizeof = 2;

    unsigned char *data_;

    Stringx(unsigned char *data) : data_(data) {}

#define STRINGX_VALUE_OFFSET 0
#define STRINGX_ALIGNMENT 2
#define STRINGX_SIZE 2

    Offset<String> value() const
    {
        const int16_t offset = STRINGX_VALUE_OFFSET;
        return Offset<String>(&data_[offset]);
    }
};

struct Acc32
{

    static constexpr size_t nakedbytes_sizeof = 4;

    unsigned char *data_;

    Acc32(unsigned char *data) : data_(data) {}

#define ACC32_VALUE_OFFSET 0
#define ACC32_ALIGNMENT 4
#define ACC32_SIZE 4

    uint32_t value() const
    {
        return *reinterpret_cast<uint32_t *>(&data_[ACC32_VALUE_OFFSET]);
    }
};

struct Bitfield16
{

    static constexpr size_t nakedbytes_sizeof = 2;

    unsigned char *data_;

    Bitfield16(unsigned char *data) : data_(data) {}

#define BITFIELD16_VALUE_OFFSET 0
#define BITFIELD16_ALIGNMENT 2
#define BITFIELD16_SIZE 2

    uint16_t value() const
    {
        return *reinterpret_cast<uint16_t *>(&data_[BITFIELD16_VALUE_OFFSET]);
    }
};

enum SunspecPointAccess : uint8_t
{

    SunspecPointAccess_kR,
    SunspecPointAccess_kRW,
};

inline const char *SunspecPointAccess_to_string(SunspecPointAccess value)
{
    switch (value)
    {
    case SunspecPointAccess_kR:
        return "SunspecPointAccess_kR";
    case SunspecPointAccess_kRW:
        return "SunspecPointAccess_kRW";
    default:
        return NULL;
    }
}

struct Enum16
{

    static constexpr size_t nakedbytes_sizeof = 2;

    unsigned char *data_;

    Enum16(unsigned char *data) : data_(data) {}

#define ENUM16_VALUE_OFFSET 0
#define ENUM16_ALIGNMENT 2
#define ENUM16_SIZE 2

    uint16_t value() const
    {
        return *reinterpret_cast<uint16_t *>(&data_[ENUM16_VALUE_OFFSET]);
    }
};

struct Bitfield32
{

    static constexpr size_t nakedbytes_sizeof = 4;

    unsigned char *data_;

    Bitfield32(unsigned char *data) : data_(data) {}

#define BITFIELD32_VALUE_OFFSET 0
#define BITFIELD32_ALIGNMENT 4
#define BITFIELD32_SIZE 4

    uint32_t value() const
    {
        return *reinterpret_cast<uint32_t *>(&data_[BITFIELD32_VALUE_OFFSET]);
    }
};

struct Acc16
{

    static constexpr size_t nakedbytes_sizeof = 2;

    unsigned char *data_;

    Acc16(unsigned char *data) : data_(data) {}

#define ACC16_VALUE_OFFSET 0
#define ACC16_ALIGNMENT 2
#define ACC16_SIZE 2

    uint16_t value() const
    {
        return *reinterpret_cast<uint16_t *>(&data_[ACC16_VALUE_OFFSET]);
    }
};

struct Eui48
{

    static constexpr size_t nakedbytes_sizeof = 6;

    unsigned char *data_;

    Eui48(unsigned char *data) : data_(data) {}

#define EUI48_VALUE0_OFFSET 0
#define EUI48_VALUE1_OFFSET 2
#define EUI48_VALUE2_OFFSET 4
#define EUI48_ALIGNMENT 2
#define EUI48_SIZE 6

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

struct Sint16
{

    static constexpr size_t nakedbytes_sizeof = 2;

    unsigned char *data_;

    Sint16(unsigned char *data) : data_(data) {}

#define SINT16_VALUE_OFFSET 0
#define SINT16_ALIGNMENT 2
#define SINT16_SIZE 2

    int16_t value() const
    {
        return *reinterpret_cast<int16_t *>(&data_[SINT16_VALUE_OFFSET]);
    }
};

enum SunspecPointData_enum : uint16_t
{

    SunspecPointData_enum_Uint16,
    SunspecPointData_enum_Sint16,
    SunspecPointData_enum_Uint32,
    SunspecPointData_enum_Sint32,
    SunspecPointData_enum_Uint64,
    SunspecPointData_enum_Sint64,
    SunspecPointData_enum_Float32,
    SunspecPointData_enum_Float64,
    SunspecPointData_enum_Stringx,
    SunspecPointData_enum_Pad16,
    SunspecPointData_enum_Raw16,
    SunspecPointData_enum_Enum16,
    SunspecPointData_enum_Enum32,
    SunspecPointData_enum_Enum64,
    SunspecPointData_enum_Bitfield16,
    SunspecPointData_enum_Bitfield32,
    SunspecPointData_enum_Bitfield64,
    SunspecPointData_enum_SunsSf,
    SunspecPointData_enum_Acc16,
    SunspecPointData_enum_Acc32,
    SunspecPointData_enum_Acc64,
    SunspecPointData_enum_Eui48,
    SunspecPointData_enum_IpAddr,
    SunspecPointData_enum_Ipv6Addr,
};

inline const char *SunspecPointData_enum_to_string(SunspecPointData_enum value)
{
    switch (value)
    {
    case SunspecPointData_enum_Uint16:
        return "SunspecPointData_enum_Uint16";
    case SunspecPointData_enum_Sint16:
        return "SunspecPointData_enum_Sint16";
    case SunspecPointData_enum_Uint32:
        return "SunspecPointData_enum_Uint32";
    case SunspecPointData_enum_Sint32:
        return "SunspecPointData_enum_Sint32";
    case SunspecPointData_enum_Uint64:
        return "SunspecPointData_enum_Uint64";
    case SunspecPointData_enum_Sint64:
        return "SunspecPointData_enum_Sint64";
    case SunspecPointData_enum_Float32:
        return "SunspecPointData_enum_Float32";
    case SunspecPointData_enum_Float64:
        return "SunspecPointData_enum_Float64";
    case SunspecPointData_enum_Stringx:
        return "SunspecPointData_enum_Stringx";
    case SunspecPointData_enum_Pad16:
        return "SunspecPointData_enum_Pad16";
    case SunspecPointData_enum_Raw16:
        return "SunspecPointData_enum_Raw16";
    case SunspecPointData_enum_Enum16:
        return "SunspecPointData_enum_Enum16";
    case SunspecPointData_enum_Enum32:
        return "SunspecPointData_enum_Enum32";
    case SunspecPointData_enum_Enum64:
        return "SunspecPointData_enum_Enum64";
    case SunspecPointData_enum_Bitfield16:
        return "SunspecPointData_enum_Bitfield16";
    case SunspecPointData_enum_Bitfield32:
        return "SunspecPointData_enum_Bitfield32";
    case SunspecPointData_enum_Bitfield64:
        return "SunspecPointData_enum_Bitfield64";
    case SunspecPointData_enum_SunsSf:
        return "SunspecPointData_enum_SunsSf";
    case SunspecPointData_enum_Acc16:
        return "SunspecPointData_enum_Acc16";
    case SunspecPointData_enum_Acc32:
        return "SunspecPointData_enum_Acc32";
    case SunspecPointData_enum_Acc64:
        return "SunspecPointData_enum_Acc64";
    case SunspecPointData_enum_Eui48:
        return "SunspecPointData_enum_Eui48";
    case SunspecPointData_enum_IpAddr:
        return "SunspecPointData_enum_IpAddr";
    case SunspecPointData_enum_Ipv6Addr:
        return "SunspecPointData_enum_Ipv6Addr";
    default:
        return NULL;
    }
}

struct Uint16
{

    static constexpr size_t nakedbytes_sizeof = 2;

    unsigned char *data_;

    Uint16(unsigned char *data) : data_(data) {}

#define UINT16_VALUE_OFFSET 0
#define UINT16_ALIGNMENT 2
#define UINT16_SIZE 2

    uint16_t value() const
    {
        return *reinterpret_cast<uint16_t *>(&data_[UINT16_VALUE_OFFSET]);
    }
};

struct Uint32
{

    static constexpr size_t nakedbytes_sizeof = 4;

    unsigned char *data_;

    Uint32(unsigned char *data) : data_(data) {}

#define UINT32_VALUE_OFFSET 0
#define UINT32_ALIGNMENT 4
#define UINT32_SIZE 4

    uint32_t value() const
    {
        return *reinterpret_cast<uint32_t *>(&data_[UINT32_VALUE_OFFSET]);
    }
};

struct Sint32
{

    static constexpr size_t nakedbytes_sizeof = 4;

    unsigned char *data_;

    Sint32(unsigned char *data) : data_(data) {}

#define SINT32_VALUE_OFFSET 0
#define SINT32_ALIGNMENT 4
#define SINT32_SIZE 4

    int32_t value() const
    {
        return *reinterpret_cast<int32_t *>(&data_[SINT32_VALUE_OFFSET]);
    }
};

struct Sint64
{

    static constexpr size_t nakedbytes_sizeof = 8;

    unsigned char *data_;

    Sint64(unsigned char *data) : data_(data) {}

#define SINT64_VALUE_OFFSET 0
#define SINT64_ALIGNMENT 8
#define SINT64_SIZE 8

    int64_t value() const
    {
        return *reinterpret_cast<int64_t *>(&data_[SINT64_VALUE_OFFSET]);
    }
};

struct Float32
{

    static constexpr size_t nakedbytes_sizeof = 4;

    unsigned char *data_;

    Float32(unsigned char *data) : data_(data) {}

#define FLOAT32_VALUE_OFFSET 0
#define FLOAT32_ALIGNMENT 4
#define FLOAT32_SIZE 4

    float value() const
    {
        return *reinterpret_cast<float *>(&data_[FLOAT32_VALUE_OFFSET]);
    }
};

struct Float64
{

    static constexpr size_t nakedbytes_sizeof = 8;

    unsigned char *data_;

    Float64(unsigned char *data) : data_(data) {}

#define FLOAT64_VALUE_OFFSET 0
#define FLOAT64_ALIGNMENT 8
#define FLOAT64_SIZE 8

    double value() const
    {
        return *reinterpret_cast<double *>(&data_[FLOAT64_VALUE_OFFSET]);
    }
};

struct Pad16
{

    static constexpr size_t nakedbytes_sizeof = 2;

    unsigned char *data_;

    Pad16(unsigned char *data) : data_(data) {}

#define PAD16_VALUE_OFFSET 0
#define PAD16_ALIGNMENT 2
#define PAD16_SIZE 2

    uint16_t value() const
    {
        return *reinterpret_cast<uint16_t *>(&data_[PAD16_VALUE_OFFSET]);
    }
};

struct Raw16
{

    static constexpr size_t nakedbytes_sizeof = 2;

    unsigned char *data_;

    Raw16(unsigned char *data) : data_(data) {}

#define RAW16_VALUE_OFFSET 0
#define RAW16_ALIGNMENT 2
#define RAW16_SIZE 2

    uint16_t value() const
    {
        return *reinterpret_cast<uint16_t *>(&data_[RAW16_VALUE_OFFSET]);
    }
};

struct Enum32
{

    static constexpr size_t nakedbytes_sizeof = 4;

    unsigned char *data_;

    Enum32(unsigned char *data) : data_(data) {}

#define ENUM32_VALUE_OFFSET 0
#define ENUM32_ALIGNMENT 4
#define ENUM32_SIZE 4

    uint32_t value() const
    {
        return *reinterpret_cast<uint32_t *>(&data_[ENUM32_VALUE_OFFSET]);
    }
};

struct Enum64
{

    static constexpr size_t nakedbytes_sizeof = 8;

    unsigned char *data_;

    Enum64(unsigned char *data) : data_(data) {}

#define ENUM64_VALUE_OFFSET 0
#define ENUM64_ALIGNMENT 8
#define ENUM64_SIZE 8

    uint64_t value() const
    {
        return *reinterpret_cast<uint64_t *>(&data_[ENUM64_VALUE_OFFSET]);
    }
};

struct Bitfield64
{

    static constexpr size_t nakedbytes_sizeof = 8;

    unsigned char *data_;

    Bitfield64(unsigned char *data) : data_(data) {}

#define BITFIELD64_VALUE_OFFSET 0
#define BITFIELD64_ALIGNMENT 8
#define BITFIELD64_SIZE 8

    uint64_t value() const
    {
        return *reinterpret_cast<uint64_t *>(&data_[BITFIELD64_VALUE_OFFSET]);
    }
};

struct SunsSf
{

    static constexpr size_t nakedbytes_sizeof = 2;

    unsigned char *data_;

    SunsSf(unsigned char *data) : data_(data) {}

#define SUNSSF_VALUE_OFFSET 0
#define SUNSSF_ALIGNMENT 2
#define SUNSSF_SIZE 2

    uint16_t value() const
    {
        return *reinterpret_cast<uint16_t *>(&data_[SUNSSF_VALUE_OFFSET]);
    }
};

struct Acc64
{

    static constexpr size_t nakedbytes_sizeof = 8;

    unsigned char *data_;

    Acc64(unsigned char *data) : data_(data) {}

#define ACC64_VALUE_OFFSET 0
#define ACC64_ALIGNMENT 8
#define ACC64_SIZE 8

    uint64_t value() const
    {
        return *reinterpret_cast<uint64_t *>(&data_[ACC64_VALUE_OFFSET]);
    }
};

struct IpAddr
{

    static constexpr size_t nakedbytes_sizeof = 4;

    unsigned char *data_;

    IpAddr(unsigned char *data) : data_(data) {}

#define IPADDR_OCTET1_OFFSET 0
#define IPADDR_OCTET2_OFFSET 1
#define IPADDR_OCTET3_OFFSET 2
#define IPADDR_OCTET4_OFFSET 3
#define IPADDR_ALIGNMENT 1
#define IPADDR_SIZE 4

    uint8_t octet1() const
    {
        return *reinterpret_cast<uint8_t *>(&data_[IPADDR_OCTET1_OFFSET]);
    }

    uint8_t octet2() const
    {
        return *reinterpret_cast<uint8_t *>(&data_[IPADDR_OCTET2_OFFSET]);
    }

    uint8_t octet3() const
    {
        return *reinterpret_cast<uint8_t *>(&data_[IPADDR_OCTET3_OFFSET]);
    }

    uint8_t octet4() const
    {
        return *reinterpret_cast<uint8_t *>(&data_[IPADDR_OCTET4_OFFSET]);
    }
};

struct Ipv6Addr
{

    static constexpr size_t nakedbytes_sizeof = 6;

    unsigned char *data_;

    Ipv6Addr(unsigned char *data) : data_(data) {}

#define IPV6ADDR_OCTET0_OFFSET 0
#define IPV6ADDR_OCTET1_OFFSET 1
#define IPV6ADDR_OCTET2_OFFSET 2
#define IPV6ADDR_OCTET3_OFFSET 3
#define IPV6ADDR_OCTET4_OFFSET 4
#define IPV6ADDR_OCTET5_OFFSET 5
#define IPV6ADDR_ALIGNMENT 1
#define IPV6ADDR_SIZE 6

    uint8_t octet0() const
    {
        return *reinterpret_cast<uint8_t *>(&data_[IPV6ADDR_OCTET0_OFFSET]);
    }

    uint8_t octet1() const
    {
        return *reinterpret_cast<uint8_t *>(&data_[IPV6ADDR_OCTET1_OFFSET]);
    }

    uint8_t octet2() const
    {
        return *reinterpret_cast<uint8_t *>(&data_[IPV6ADDR_OCTET2_OFFSET]);
    }

    uint8_t octet3() const
    {
        return *reinterpret_cast<uint8_t *>(&data_[IPV6ADDR_OCTET3_OFFSET]);
    }

    uint8_t octet4() const
    {
        return *reinterpret_cast<uint8_t *>(&data_[IPV6ADDR_OCTET4_OFFSET]);
    }

    uint8_t octet5() const
    {
        return *reinterpret_cast<uint8_t *>(&data_[IPV6ADDR_OCTET5_OFFSET]);
    }
};

struct SunspecPointData
{

    unsigned char *data_;

    SunspecPointData(unsigned char *data) : data_(data) {}

#define SUNSPECPOINTDATA_TYPE_OFFSET 0
#define SUNSPECPOINTDATA_DATA_OFFSET 2
#define SUNSPECPOINTDATA_ALIGNMENT 2
#define SUNSPECPOINTDATA_SIZE 2

    bool is_null() const
    {
        return (type() == 0) or (*reinterpret_cast<uint16_t *>(&data_[SUNSPECPOINTDATA_DATA_OFFSET]) == 0);
    }

    unsigned char *raw_data() const
    {
        const int16_t offset = *reinterpret_cast<uint16_t *>(&data_[SUNSPECPOINTDATA_DATA_OFFSET]) + SUNSPECPOINTDATA_DATA_OFFSET;
        return (&data_[offset]);
    }
    SunspecPointData_enum type() const
    {
        return *reinterpret_cast<SunspecPointData_enum *>(&data_[SUNSPECPOINTDATA_TYPE_OFFSET]);
    }

    Offset<Uint16> data_as_Uint16() const
    {
        return type() == SunspecPointData_enum_Uint16 ? Offset<Uint16>(&data_[SUNSPECPOINTDATA_DATA_OFFSET]) : 0;
    }

    Offset<Sint16> data_as_Sint16() const
    {
        return type() == SunspecPointData_enum_Sint16 ? Offset<Sint16>(&data_[SUNSPECPOINTDATA_DATA_OFFSET]) : 0;
    }

    Offset<Uint32> data_as_Uint32() const
    {
        return type() == SunspecPointData_enum_Uint32 ? Offset<Uint32>(&data_[SUNSPECPOINTDATA_DATA_OFFSET]) : 0;
    }

    Offset<Sint32> data_as_Sint32() const
    {
        return type() == SunspecPointData_enum_Sint32 ? Offset<Sint32>(&data_[SUNSPECPOINTDATA_DATA_OFFSET]) : 0;
    }

    Offset<Uint64> data_as_Uint64() const
    {
        return type() == SunspecPointData_enum_Uint64 ? Offset<Uint64>(&data_[SUNSPECPOINTDATA_DATA_OFFSET]) : 0;
    }

    Offset<Sint64> data_as_Sint64() const
    {
        return type() == SunspecPointData_enum_Sint64 ? Offset<Sint64>(&data_[SUNSPECPOINTDATA_DATA_OFFSET]) : 0;
    }

    Offset<Float32> data_as_Float32() const
    {
        return type() == SunspecPointData_enum_Float32 ? Offset<Float32>(&data_[SUNSPECPOINTDATA_DATA_OFFSET]) : 0;
    }

    Offset<Float64> data_as_Float64() const
    {
        return type() == SunspecPointData_enum_Float64 ? Offset<Float64>(&data_[SUNSPECPOINTDATA_DATA_OFFSET]) : 0;
    }

    Offset<Stringx> data_as_Stringx() const
    {
        return type() == SunspecPointData_enum_Stringx ? Offset<Stringx>(&data_[SUNSPECPOINTDATA_DATA_OFFSET]) : 0;
    }

    Offset<Pad16> data_as_Pad16() const
    {
        return type() == SunspecPointData_enum_Pad16 ? Offset<Pad16>(&data_[SUNSPECPOINTDATA_DATA_OFFSET]) : 0;
    }

    Offset<Raw16> data_as_Raw16() const
    {
        return type() == SunspecPointData_enum_Raw16 ? Offset<Raw16>(&data_[SUNSPECPOINTDATA_DATA_OFFSET]) : 0;
    }

    Offset<Enum16> data_as_Enum16() const
    {
        return type() == SunspecPointData_enum_Enum16 ? Offset<Enum16>(&data_[SUNSPECPOINTDATA_DATA_OFFSET]) : 0;
    }

    Offset<Enum32> data_as_Enum32() const
    {
        return type() == SunspecPointData_enum_Enum32 ? Offset<Enum32>(&data_[SUNSPECPOINTDATA_DATA_OFFSET]) : 0;
    }

    Offset<Enum64> data_as_Enum64() const
    {
        return type() == SunspecPointData_enum_Enum64 ? Offset<Enum64>(&data_[SUNSPECPOINTDATA_DATA_OFFSET]) : 0;
    }

    Offset<Bitfield16> data_as_Bitfield16() const
    {
        return type() == SunspecPointData_enum_Bitfield16 ? Offset<Bitfield16>(&data_[SUNSPECPOINTDATA_DATA_OFFSET]) : 0;
    }

    Offset<Bitfield32> data_as_Bitfield32() const
    {
        return type() == SunspecPointData_enum_Bitfield32 ? Offset<Bitfield32>(&data_[SUNSPECPOINTDATA_DATA_OFFSET]) : 0;
    }

    Offset<Bitfield64> data_as_Bitfield64() const
    {
        return type() == SunspecPointData_enum_Bitfield64 ? Offset<Bitfield64>(&data_[SUNSPECPOINTDATA_DATA_OFFSET]) : 0;
    }

    Offset<SunsSf> data_as_SunsSf() const
    {
        return type() == SunspecPointData_enum_SunsSf ? Offset<SunsSf>(&data_[SUNSPECPOINTDATA_DATA_OFFSET]) : 0;
    }

    Offset<Acc16> data_as_Acc16() const
    {
        return type() == SunspecPointData_enum_Acc16 ? Offset<Acc16>(&data_[SUNSPECPOINTDATA_DATA_OFFSET]) : 0;
    }

    Offset<Acc32> data_as_Acc32() const
    {
        return type() == SunspecPointData_enum_Acc32 ? Offset<Acc32>(&data_[SUNSPECPOINTDATA_DATA_OFFSET]) : 0;
    }

    Offset<Acc64> data_as_Acc64() const
    {
        return type() == SunspecPointData_enum_Acc64 ? Offset<Acc64>(&data_[SUNSPECPOINTDATA_DATA_OFFSET]) : 0;
    }

    Offset<Eui48> data_as_Eui48() const
    {
        return type() == SunspecPointData_enum_Eui48 ? Offset<Eui48>(&data_[SUNSPECPOINTDATA_DATA_OFFSET]) : 0;
    }

    Offset<IpAddr> data_as_IpAddr() const
    {
        return type() == SunspecPointData_enum_IpAddr ? Offset<IpAddr>(&data_[SUNSPECPOINTDATA_DATA_OFFSET]) : 0;
    }

    Offset<Ipv6Addr> data_as_Ipv6Addr() const
    {
        return type() == SunspecPointData_enum_Ipv6Addr ? Offset<Ipv6Addr>(&data_[SUNSPECPOINTDATA_DATA_OFFSET]) : 0;
    }
};

enum SunspecPointMandatory : uint8_t
{

    SunspecPointMandatory_kM,
    SunspecPointMandatory_kO,
};

inline const char *SunspecPointMandatory_to_string(SunspecPointMandatory value)
{
    switch (value)
    {
    case SunspecPointMandatory_kM:
        return "SunspecPointMandatory_kM";
    case SunspecPointMandatory_kO:
        return "SunspecPointMandatory_kO";
    default:
        return NULL;
    }
}

struct SunspecPointDef
{

    static constexpr size_t nakedbytes_sizeof = 20;

    unsigned char *data_;

    SunspecPointDef(unsigned char *data) : data_(data) {}

#define SUNSPECPOINTDEF_ID_OFFSET 0
#define SUNSPECPOINTDEF_SF_ID_OFFSET 2
#define SUNSPECPOINTDEF_UNITS_OFFSET 4
#define SUNSPECPOINTDEF_LABEL_OFFSET 6
#define SUNSPECPOINTDEF_DATA_TYPE_OFFSET 8
#define SUNSPECPOINTDEF_DATA_OFFSET 10
#define SUNSPECPOINTDEF_COUNT_OFFSET 12
#define SUNSPECPOINTDEF_PAD13_OFFSET 13
#define SUNSPECPOINTDEF_COUNT_POINT_ID_OFFSET 14
#define SUNSPECPOINTDEF_SIZE_OFFSET 16
#define SUNSPECPOINTDEF_SF_OFFSET 17
#define SUNSPECPOINTDEF_ACCESS_OFFSET 18
#define SUNSPECPOINTDEF_MANDATORY_OFFSET 19
#define SUNSPECPOINTDEF_ALIGNMENT 2
#define SUNSPECPOINTDEF_SIZE 20

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

    Offset<String> count_point_id() const
    {
        const int16_t offset = SUNSPECPOINTDEF_COUNT_POINT_ID_OFFSET;
        return Offset<String>(&data_[offset]);
    }

    uint8_t size() const
    {
        return *reinterpret_cast<uint8_t *>(&data_[SUNSPECPOINTDEF_SIZE_OFFSET]);
    }

    int8_t sf() const
    {
        return *reinterpret_cast<int8_t *>(&data_[SUNSPECPOINTDEF_SF_OFFSET]);
    }

    SunspecPointAccess access() const
    {
        return *reinterpret_cast<SunspecPointAccess *>(&data_[SUNSPECPOINTDEF_ACCESS_OFFSET]);
    }

    SunspecPointMandatory mandatory() const
    {
        return *reinterpret_cast<SunspecPointMandatory *>(&data_[SUNSPECPOINTDEF_MANDATORY_OFFSET]);
    }
};

enum SunspecGroupType : uint8_t
{

    SunspecGroupType_kGroup,
    SunspecGroupType_kSync,
};

inline const char *SunspecGroupType_to_string(SunspecGroupType value)
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

struct SunspecGroupDef
{

    static constexpr size_t nakedbytes_sizeof = 12;

    unsigned char *data_;

    SunspecGroupDef(unsigned char *data) : data_(data) {}

#define SUNSPECGROUPDEF_ID_OFFSET 0
#define SUNSPECGROUPDEF_COUNT_POINT_ID_OFFSET 2
#define SUNSPECGROUPDEF_POINTS_OFFSET 4
#define SUNSPECGROUPDEF_GROUPS_OFFSET 6
#define SUNSPECGROUPDEF_LABEL_OFFSET 8
#define SUNSPECGROUPDEF_COUNT_OFFSET 10
#define SUNSPECGROUPDEF_TYPE_OFFSET 11
#define SUNSPECGROUPDEF_ALIGNMENT 2
#define SUNSPECGROUPDEF_SIZE 12

    Offset<String> id() const
    {
        const int16_t offset = SUNSPECGROUPDEF_ID_OFFSET;
        return Offset<String>(&data_[offset]);
    }

    Offset<String> count_point_id() const
    {
        const int16_t offset = SUNSPECGROUPDEF_COUNT_POINT_ID_OFFSET;
        return Offset<String>(&data_[offset]);
    }

    Vector<SunspecPointDef> points() const
    {
        const int16_t offset = SUNSPECGROUPDEF_POINTS_OFFSET;
        return Vector<SunspecPointDef>(&data_[offset]);
    }

    Vector<SunspecGroupDef> groups() const
    {
        const int16_t offset = SUNSPECGROUPDEF_GROUPS_OFFSET;
        return Vector<SunspecGroupDef>(&data_[offset]);
    }

    Offset<String> label() const
    {
        const int16_t offset = SUNSPECGROUPDEF_LABEL_OFFSET;
        return Offset<String>(&data_[offset]);
    }

    uint8_t count() const
    {
        return *reinterpret_cast<uint8_t *>(&data_[SUNSPECGROUPDEF_COUNT_OFFSET]);
    }

    SunspecGroupType type() const
    {
        return *reinterpret_cast<SunspecGroupType *>(&data_[SUNSPECGROUPDEF_TYPE_OFFSET]);
    }
};

struct SunspecModelDef
{

    static constexpr size_t nakedbytes_sizeof = 14;

    unsigned char *data_;

    SunspecModelDef(unsigned char *data) : data_(data) {}

#define SUNSPECMODELDEF_ID_OFFSET 0
#define SUNSPECMODELDEF_GROUP_OFFSET 2
#define SUNSPECMODELDEF_ALIGNMENT 2
#define SUNSPECMODELDEF_SIZE 14

    uint16_t id() const
    {
        return *reinterpret_cast<uint16_t *>(&data_[SUNSPECMODELDEF_ID_OFFSET]);
    }

    SunspecGroupDef group() const
    {
        return SunspecGroupDef(&data_[SUNSPECMODELDEF_GROUP_OFFSET]);
    }
};

struct SunspecModelDefRoot
{

    unsigned char *data_;

    SunspecModelDefRoot(unsigned char *data) : data_(data) {}

#define SUNSPECMODELDEF_ID_OFFSET 0
#define SUNSPECMODELDEF_GROUP_OFFSET 2
#define SUNSPECMODELDEF_ALIGNMENT 2
#define SUNSPECMODELDEF_SIZE 14

    uint16_t id() const
    {
        return *reinterpret_cast<uint16_t *>(&data_[SUNSPECMODELDEF_ID_OFFSET + 2 * OFFSET_SIZE]);
    }

    SunspecGroupDef group() const
    {
        return SunspecGroupDef(&data_[SUNSPECMODELDEF_GROUP_OFFSET + 2 * OFFSET_SIZE]);
    }
};

inline size_t get_padding_size(size_t offset, uint16_t alignment)
{
    return (alignment - (offset % alignment)) % alignment;
}

template <typename T>
struct SerializeOffset
{
    uint16_t offset = 0;

    template <typename U = void>
    operator SerializeOffset<U>() const
    {
        SerializeOffset<U> ret;
        ret.offset = this->offset;
        return ret;
    }
};

template <typename T>
struct is_serializable_offset_Type : std::false_type
{
};
template <typename T>
struct is_serializable_offset_Type<SerializeOffset<T>> : std::true_type
{
};

struct Serializer
{

#define VERSION 1
#define OFFSET_SIZE 2

    unsigned char *_buffer = nullptr;
    uint16_t _buffer_size = 0;
    // uint16_t _current_offset = 0;
    uint16_t _tail_offset = 0;

    void init(uint16_t buffer_size, const uint16_t root_type_size, uint16_t root_type_alignment)
    {
        _buffer = reinterpret_cast<unsigned char *>(malloc(buffer_size));
        _buffer_size = buffer_size;
        *reinterpret_cast<uint16_t *>(&_buffer[OFFSET_SIZE]) = VERSION;

        _tail_offset = get_padding_size(OFFSET_SIZE * 2, root_type_alignment) + OFFSET_SIZE * 2 + root_type_size;
        make_buffer_adequate();
    }

    inline void make_buffer_adequate()
    {
        while (_buffer_size < _tail_offset)
        {
            _buffer = reinterpret_cast<unsigned char *>(realloc(_buffer, _buffer_size * 2));
            _buffer_size = _buffer_size * 2;
        }
    }

    SerializeOffset<String> serialize_string(const char *str)
    {
        SerializeOffset<String> str_offset;

        if (str == nullptr)
        {
            str_offset.offset = 0;
        }
        else
        {
            size_t len = strlen(str);
            _tail_offset += get_padding_size(_tail_offset, OFFSET_SIZE);

            make_buffer_adequate();
            str_offset.offset = _tail_offset;

            *reinterpret_cast<uint16_t *>(&_buffer[_tail_offset]) = len;
            _tail_offset += OFFSET_SIZE;
            memcpy(&_buffer[_tail_offset], str, len);
            *reinterpret_cast<unsigned char *>(&(((unsigned char *)_buffer)[_tail_offset + len])) = 0;
            _tail_offset += len + 1;
        }
        return str_offset;
    }

    template <typename T>
    typename std::enable_if<(std::is_integral<T>::value || std::is_floating_point<T>::value || std::is_enum<T>::value), SerializeOffset<T>>::type serialize_primitive(T data)
    {
        SerializeOffset<T> data_offset;
        _tail_offset += get_padding_size(_tail_offset, sizeof(T));

        make_buffer_adequate();
        data_offset.offset = _tail_offset;

        *reinterpret_cast<T *>(&_buffer[_tail_offset]) = data;

        return data_offset;
    }

    template <typename>
    struct extract_vector_type
    {
    };

    template <typename T, typename Alloc>
    struct extract_vector_type<std::vector<T, Alloc>>
    {
        using type = T;
    };

    template <typename Vec>
    using vec_inner_t = typename extract_vector_type<Vec>::type;

    template <typename T>
    typename std::enable_if<(std::is_integral<vec_inner_t<T>>::value || std::is_floating_point<vec_inner_t<T>>::value || std::is_enum<vec_inner_t<T>>::value), SerializeOffset<Vector<vec_inner_t<T>>>>::type serialize_vector(T data_array)
    {
        SerializeOffset<Vector<vec_inner_t<T>>> data_array_offset;
        size_t len = data_array.size();
        _tail_offset += get_padding_size(_tail_offset, OFFSET_SIZE);

        make_buffer_adequate();
        data_array_offset.offset = _tail_offset;

        *reinterpret_cast<uint16_t *>(&_buffer[_tail_offset]) = len;
        _tail_offset += OFFSET_SIZE;
        memcpy(&_buffer[_tail_offset], data_array.data(), len * sizeof(vec_inner_t<T>));
        _tail_offset += len * sizeof(vec_inner_t<T>);
        return data_array_offset;
    }

    template <typename T>
    typename std::enable_if<(is_serializable_offset_Type<vec_inner_t<T>>::value), SerializeOffset<Vector<vec_inner_t<T>>>>::type serialize_vector(T data_array)
    {
        SerializeOffset<Vector<vec_inner_t<T>>> data_array_offset;
        size_t len = data_array.size();
        _tail_offset += get_padding_size(_tail_offset, OFFSET_SIZE);

        make_buffer_adequate();
        data_array_offset.offset = _tail_offset;

        *reinterpret_cast<uint16_t *>(&_buffer[_tail_offset]) = len;
        _tail_offset += OFFSET_SIZE;

        for (uint16_t i = 0; i < len; i++)
        {
            *reinterpret_cast<uint16_t *>(&_buffer[_tail_offset]) = data_array[i].offset - _tail_offset;
            _tail_offset += OFFSET_SIZE;
        }
        return data_array_offset;
    }
};

struct Uint64Struct
{
    uint64_t value;
};

struct StringxStruct
{
    SerializeOffset<String> value;
};

struct Acc32Struct
{
    uint32_t value;
};

struct Bitfield16Struct
{
    uint16_t value;
};

struct Enum16Struct
{
    uint16_t value;
};

struct Bitfield32Struct
{
    uint32_t value;
};

struct Acc16Struct
{
    uint16_t value;
};

struct Eui48Struct
{
    uint16_t value0;
    uint16_t value1;
    uint16_t value2;
};

struct Sint16Struct
{
    int16_t value;
};

struct SunspecPointData_enumStruct
{
};

struct SunspecPointDataStruct
{
};

struct SunspecPointAccessStruct
{
};

struct SunspecPointMandatoryStruct
{
};

struct SunspecPointDefStruct
{
    SerializeOffset<String> id;
    SerializeOffset<String> sf_id;
    SerializeOffset<String> units;
    SerializeOffset<String> label;
    SunspecPointData_enum data_type;
    SerializeOffset<void> data;
    uint8_t count;
    SerializeOffset<String> count_point_id;
    uint8_t size;
    int8_t sf;
    SunspecPointAccess access;
    SunspecPointMandatory mandatory;
};

struct SunspecGroupTypeStruct
{
};

struct SunspecGroupDefStruct
{
    SerializeOffset<String> id;
    SerializeOffset<String> count_point_id;
    SerializeOffset<Vector<SunspecPointDefStruct>> points;
    SerializeOffset<Vector<SunspecGroupDefStruct>> groups;
    SerializeOffset<String> label;
    uint8_t count;
    SunspecGroupType type;
};

struct Sint64Struct
{
    int64_t value;
};

struct Pad16Struct
{
    uint16_t value;
};

struct Bitfield64Struct
{
    uint64_t value;
};

struct Sint32Struct
{
    int32_t value;
};

struct IpAddrStruct
{
    uint8_t octet1;
    uint8_t octet2;
    uint8_t octet3;
    uint8_t octet4;
};

struct Ipv6AddrStruct
{
    uint8_t octet0;
    uint8_t octet1;
    uint8_t octet2;
    uint8_t octet3;
    uint8_t octet4;
    uint8_t octet5;
};

struct Raw16Struct
{
    uint16_t value;
};

struct Uint16Struct
{
    uint16_t value;
};

struct SunspecModelDefStruct
{
    uint16_t id;
    SunspecGroupDefStruct group;
};

struct Uint32Struct
{
    uint32_t value;
};

struct Enum32Struct
{
    uint32_t value;
};

struct Float32Struct
{
    float value;
};

struct Acc64Struct
{
    uint64_t value;
};

struct SunsSfStruct
{
    uint16_t value;
};

struct Enum64Struct
{
    uint64_t value;
};

struct Float64Struct
{
    double value;
};

inline SerializeOffset<Uint64> serialize_uint64(Serializer *const serializer,
                                                const uint64_t value)
{
    SerializeOffset<Uint64> uint64_offset;
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, UINT64_ALIGNMENT);
    serializer->make_buffer_adequate();
    uint64_offset.offset = serializer->_tail_offset;

    *reinterpret_cast<uint64_t *>(&(serializer->_buffer[serializer->_tail_offset + UINT64_VALUE_OFFSET])) = value;
    serializer->_tail_offset += UINT64_SIZE;
    return uint64_offset;
}

inline SerializeOffset<Stringx> serialize_stringx(Serializer *const serializer,
                                                  const SerializeOffset<String> value)
{
    SerializeOffset<Stringx> stringx_offset;
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, STRINGX_ALIGNMENT);
    serializer->make_buffer_adequate();
    stringx_offset.offset = serializer->_tail_offset;

    *reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset + STRINGX_VALUE_OFFSET])) = value.offset - (serializer->_tail_offset + STRINGX_VALUE_OFFSET);
    serializer->_tail_offset += STRINGX_SIZE;
    return stringx_offset;
}

inline SerializeOffset<Acc32> serialize_acc32(Serializer *const serializer,
                                              const uint32_t value)
{
    SerializeOffset<Acc32> acc32_offset;
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, ACC32_ALIGNMENT);
    serializer->make_buffer_adequate();
    acc32_offset.offset = serializer->_tail_offset;

    *reinterpret_cast<uint32_t *>(&(serializer->_buffer[serializer->_tail_offset + ACC32_VALUE_OFFSET])) = value;
    serializer->_tail_offset += ACC32_SIZE;
    return acc32_offset;
}

inline SerializeOffset<Bitfield16> serialize_bitfield16(Serializer *const serializer,
                                                        const uint16_t value)
{
    SerializeOffset<Bitfield16> bitfield16_offset;
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, BITFIELD16_ALIGNMENT);
    serializer->make_buffer_adequate();
    bitfield16_offset.offset = serializer->_tail_offset;

    *reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset + BITFIELD16_VALUE_OFFSET])) = value;
    serializer->_tail_offset += BITFIELD16_SIZE;
    return bitfield16_offset;
}

inline SerializeOffset<Enum16> serialize_enum16(Serializer *const serializer,
                                                const uint16_t value)
{
    SerializeOffset<Enum16> enum16_offset;
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, ENUM16_ALIGNMENT);
    serializer->make_buffer_adequate();
    enum16_offset.offset = serializer->_tail_offset;

    *reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset + ENUM16_VALUE_OFFSET])) = value;
    serializer->_tail_offset += ENUM16_SIZE;
    return enum16_offset;
}

inline SerializeOffset<Bitfield32> serialize_bitfield32(Serializer *const serializer,
                                                        const uint32_t value)
{
    SerializeOffset<Bitfield32> bitfield32_offset;
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, BITFIELD32_ALIGNMENT);
    serializer->make_buffer_adequate();
    bitfield32_offset.offset = serializer->_tail_offset;

    *reinterpret_cast<uint32_t *>(&(serializer->_buffer[serializer->_tail_offset + BITFIELD32_VALUE_OFFSET])) = value;
    serializer->_tail_offset += BITFIELD32_SIZE;
    return bitfield32_offset;
}

inline SerializeOffset<Acc16> serialize_acc16(Serializer *const serializer,
                                              const uint16_t value)
{
    SerializeOffset<Acc16> acc16_offset;
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, ACC16_ALIGNMENT);
    serializer->make_buffer_adequate();
    acc16_offset.offset = serializer->_tail_offset;

    *reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset + ACC16_VALUE_OFFSET])) = value;
    serializer->_tail_offset += ACC16_SIZE;
    return acc16_offset;
}

inline SerializeOffset<Eui48> serialize_eui48(Serializer *const serializer,
                                              const uint16_t value0,
                                              const uint16_t value1,
                                              const uint16_t value2)
{
    SerializeOffset<Eui48> eui48_offset;
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, EUI48_ALIGNMENT);
    serializer->make_buffer_adequate();
    eui48_offset.offset = serializer->_tail_offset;

    *reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset + EUI48_VALUE0_OFFSET])) = value0;
    *reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset + EUI48_VALUE1_OFFSET])) = value1;
    *reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset + EUI48_VALUE2_OFFSET])) = value2;
    serializer->_tail_offset += EUI48_SIZE;
    return eui48_offset;
}

inline SerializeOffset<Sint16> serialize_sint16(Serializer *const serializer,
                                                const int16_t value)
{
    SerializeOffset<Sint16> sint16_offset;
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, SINT16_ALIGNMENT);
    serializer->make_buffer_adequate();
    sint16_offset.offset = serializer->_tail_offset;

    *reinterpret_cast<int16_t *>(&(serializer->_buffer[serializer->_tail_offset + SINT16_VALUE_OFFSET])) = value;
    serializer->_tail_offset += SINT16_SIZE;
    return sint16_offset;
}

inline SerializeOffset<SunspecGroupDef> serialize_sunspecgroupdef(Serializer *const serializer,
                                                                  const SerializeOffset<String> id,
                                                                  const SerializeOffset<String> count_point_id,
                                                                  const SerializeOffset<Vector<SunspecPointDefStruct>> points,
                                                                  const SerializeOffset<Vector<SunspecGroupDefStruct>> groups,
                                                                  const SerializeOffset<String> label,
                                                                  const uint8_t count,
                                                                  const SunspecGroupType type)
{
    SerializeOffset<SunspecGroupDef> sunspecgroupdef_offset;
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, SUNSPECGROUPDEF_ALIGNMENT);
    serializer->make_buffer_adequate();
    sunspecgroupdef_offset.offset = serializer->_tail_offset;

    *reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset + SUNSPECGROUPDEF_ID_OFFSET])) = id.offset - (serializer->_tail_offset + SUNSPECGROUPDEF_ID_OFFSET);
    *reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset + SUNSPECGROUPDEF_COUNT_POINT_ID_OFFSET])) = count_point_id.offset - (serializer->_tail_offset + SUNSPECGROUPDEF_COUNT_POINT_ID_OFFSET);
    *reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset + SUNSPECGROUPDEF_POINTS_OFFSET])) = points.offset - (serializer->_tail_offset + SUNSPECGROUPDEF_POINTS_OFFSET);
    *reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset + SUNSPECGROUPDEF_GROUPS_OFFSET])) = groups.offset - (serializer->_tail_offset + SUNSPECGROUPDEF_GROUPS_OFFSET);
    *reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset + SUNSPECGROUPDEF_LABEL_OFFSET])) = label.offset - (serializer->_tail_offset + SUNSPECGROUPDEF_LABEL_OFFSET);
    *reinterpret_cast<uint8_t *>(&(serializer->_buffer[serializer->_tail_offset + SUNSPECGROUPDEF_COUNT_OFFSET])) = count;
    *reinterpret_cast<SunspecGroupType *>(&(serializer->_buffer[serializer->_tail_offset + SUNSPECGROUPDEF_TYPE_OFFSET])) = type;
    serializer->_tail_offset += SUNSPECGROUPDEF_SIZE;
    return sunspecgroupdef_offset;
}

inline SerializeOffset<Sint64> serialize_sint64(Serializer *const serializer,
                                                const int64_t value)
{
    SerializeOffset<Sint64> sint64_offset;
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, SINT64_ALIGNMENT);
    serializer->make_buffer_adequate();
    sint64_offset.offset = serializer->_tail_offset;

    *reinterpret_cast<int64_t *>(&(serializer->_buffer[serializer->_tail_offset + SINT64_VALUE_OFFSET])) = value;
    serializer->_tail_offset += SINT64_SIZE;
    return sint64_offset;
}

inline SerializeOffset<Pad16> serialize_pad16(Serializer *const serializer,
                                              const uint16_t value)
{
    SerializeOffset<Pad16> pad16_offset;
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, PAD16_ALIGNMENT);
    serializer->make_buffer_adequate();
    pad16_offset.offset = serializer->_tail_offset;

    *reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset + PAD16_VALUE_OFFSET])) = value;
    serializer->_tail_offset += PAD16_SIZE;
    return pad16_offset;
}

inline SerializeOffset<Bitfield64> serialize_bitfield64(Serializer *const serializer,
                                                        const uint64_t value)
{
    SerializeOffset<Bitfield64> bitfield64_offset;
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, BITFIELD64_ALIGNMENT);
    serializer->make_buffer_adequate();
    bitfield64_offset.offset = serializer->_tail_offset;

    *reinterpret_cast<uint64_t *>(&(serializer->_buffer[serializer->_tail_offset + BITFIELD64_VALUE_OFFSET])) = value;
    serializer->_tail_offset += BITFIELD64_SIZE;
    return bitfield64_offset;
}

inline SerializeOffset<Sint32> serialize_sint32(Serializer *const serializer,
                                                const int32_t value)
{
    SerializeOffset<Sint32> sint32_offset;
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, SINT32_ALIGNMENT);
    serializer->make_buffer_adequate();
    sint32_offset.offset = serializer->_tail_offset;

    *reinterpret_cast<int32_t *>(&(serializer->_buffer[serializer->_tail_offset + SINT32_VALUE_OFFSET])) = value;
    serializer->_tail_offset += SINT32_SIZE;
    return sint32_offset;
}

inline SerializeOffset<IpAddr> serialize_ipaddr(Serializer *const serializer,
                                                const uint8_t octet1,
                                                const uint8_t octet2,
                                                const uint8_t octet3,
                                                const uint8_t octet4)
{
    SerializeOffset<IpAddr> ipaddr_offset;
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, IPADDR_ALIGNMENT);
    serializer->make_buffer_adequate();
    ipaddr_offset.offset = serializer->_tail_offset;

    *reinterpret_cast<uint8_t *>(&(serializer->_buffer[serializer->_tail_offset + IPADDR_OCTET1_OFFSET])) = octet1;
    *reinterpret_cast<uint8_t *>(&(serializer->_buffer[serializer->_tail_offset + IPADDR_OCTET2_OFFSET])) = octet2;
    *reinterpret_cast<uint8_t *>(&(serializer->_buffer[serializer->_tail_offset + IPADDR_OCTET3_OFFSET])) = octet3;
    *reinterpret_cast<uint8_t *>(&(serializer->_buffer[serializer->_tail_offset + IPADDR_OCTET4_OFFSET])) = octet4;
    serializer->_tail_offset += IPADDR_SIZE;
    return ipaddr_offset;
}

inline SerializeOffset<Ipv6Addr> serialize_ipv6addr(Serializer *const serializer,
                                                    const uint8_t octet0,
                                                    const uint8_t octet1,
                                                    const uint8_t octet2,
                                                    const uint8_t octet3,
                                                    const uint8_t octet4,
                                                    const uint8_t octet5)
{
    SerializeOffset<Ipv6Addr> ipv6addr_offset;
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, IPV6ADDR_ALIGNMENT);
    serializer->make_buffer_adequate();
    ipv6addr_offset.offset = serializer->_tail_offset;

    *reinterpret_cast<uint8_t *>(&(serializer->_buffer[serializer->_tail_offset + IPV6ADDR_OCTET0_OFFSET])) = octet0;
    *reinterpret_cast<uint8_t *>(&(serializer->_buffer[serializer->_tail_offset + IPV6ADDR_OCTET1_OFFSET])) = octet1;
    *reinterpret_cast<uint8_t *>(&(serializer->_buffer[serializer->_tail_offset + IPV6ADDR_OCTET2_OFFSET])) = octet2;
    *reinterpret_cast<uint8_t *>(&(serializer->_buffer[serializer->_tail_offset + IPV6ADDR_OCTET3_OFFSET])) = octet3;
    *reinterpret_cast<uint8_t *>(&(serializer->_buffer[serializer->_tail_offset + IPV6ADDR_OCTET4_OFFSET])) = octet4;
    *reinterpret_cast<uint8_t *>(&(serializer->_buffer[serializer->_tail_offset + IPV6ADDR_OCTET5_OFFSET])) = octet5;
    serializer->_tail_offset += IPV6ADDR_SIZE;
    return ipv6addr_offset;
}

inline SerializeOffset<SunspecPointData> serialize_sunspecpointdata(Serializer *const serializer)
{
    SerializeOffset<SunspecPointData> sunspecpointdata_offset;
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, SUNSPECPOINTDATA_ALIGNMENT);
    serializer->make_buffer_adequate();
    sunspecpointdata_offset.offset = serializer->_tail_offset;

    serializer->_tail_offset += SUNSPECPOINTDATA_SIZE;
    return sunspecpointdata_offset;
}

inline SerializeOffset<SunspecPointDef> serialize_sunspecpointdef(Serializer *const serializer,
                                                                  const SerializeOffset<String> id,
                                                                  const SerializeOffset<String> sf_id,
                                                                  const SerializeOffset<String> units,
                                                                  const SerializeOffset<String> label,
                                                                  const SunspecPointData_enum data_type,
                                                                  const SerializeOffset<void> data,
                                                                  const uint8_t count,
                                                                  const SerializeOffset<String> count_point_id,
                                                                  const uint8_t size,
                                                                  const int8_t sf,
                                                                  const SunspecPointAccess access,
                                                                  const SunspecPointMandatory mandatory)
{
    SerializeOffset<SunspecPointDef> sunspecpointdef_offset;
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, SUNSPECPOINTDEF_ALIGNMENT);
    serializer->make_buffer_adequate();
    sunspecpointdef_offset.offset = serializer->_tail_offset;

    *reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset + SUNSPECPOINTDEF_ID_OFFSET])) = id.offset - (serializer->_tail_offset + SUNSPECPOINTDEF_ID_OFFSET);
    *reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset + SUNSPECPOINTDEF_SF_ID_OFFSET])) = sf_id.offset - (serializer->_tail_offset + SUNSPECPOINTDEF_SF_ID_OFFSET);
    *reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset + SUNSPECPOINTDEF_UNITS_OFFSET])) = units.offset - (serializer->_tail_offset + SUNSPECPOINTDEF_UNITS_OFFSET);
    *reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset + SUNSPECPOINTDEF_LABEL_OFFSET])) = label.offset - (serializer->_tail_offset + SUNSPECPOINTDEF_LABEL_OFFSET);
    *reinterpret_cast<SunspecPointData_enum *>(&(serializer->_buffer[serializer->_tail_offset + SUNSPECPOINTDEF_DATA_TYPE_OFFSET])) = data_type;
    *reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset + SUNSPECPOINTDEF_DATA_OFFSET])) = data.offset - (serializer->_tail_offset + SUNSPECPOINTDEF_DATA_OFFSET);
    *reinterpret_cast<uint8_t *>(&(serializer->_buffer[serializer->_tail_offset + SUNSPECPOINTDEF_COUNT_OFFSET])) = count;
    *reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset + SUNSPECPOINTDEF_COUNT_POINT_ID_OFFSET])) = count_point_id.offset - (serializer->_tail_offset + SUNSPECPOINTDEF_COUNT_POINT_ID_OFFSET);
    *reinterpret_cast<uint8_t *>(&(serializer->_buffer[serializer->_tail_offset + SUNSPECPOINTDEF_SIZE_OFFSET])) = size;
    *reinterpret_cast<int8_t *>(&(serializer->_buffer[serializer->_tail_offset + SUNSPECPOINTDEF_SF_OFFSET])) = sf;
    *reinterpret_cast<SunspecPointAccess *>(&(serializer->_buffer[serializer->_tail_offset + SUNSPECPOINTDEF_ACCESS_OFFSET])) = access;
    *reinterpret_cast<SunspecPointMandatory *>(&(serializer->_buffer[serializer->_tail_offset + SUNSPECPOINTDEF_MANDATORY_OFFSET])) = mandatory;
    serializer->_tail_offset += SUNSPECPOINTDEF_SIZE;
    return sunspecpointdef_offset;
}

inline SerializeOffset<Raw16> serialize_raw16(Serializer *const serializer,
                                              const uint16_t value)
{
    SerializeOffset<Raw16> raw16_offset;
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, RAW16_ALIGNMENT);
    serializer->make_buffer_adequate();
    raw16_offset.offset = serializer->_tail_offset;

    *reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset + RAW16_VALUE_OFFSET])) = value;
    serializer->_tail_offset += RAW16_SIZE;
    return raw16_offset;
}

inline SerializeOffset<Uint16> serialize_uint16(Serializer *const serializer,
                                                const uint16_t value)
{
    SerializeOffset<Uint16> uint16_offset;
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, UINT16_ALIGNMENT);
    serializer->make_buffer_adequate();
    uint16_offset.offset = serializer->_tail_offset;

    *reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset + UINT16_VALUE_OFFSET])) = value;
    serializer->_tail_offset += UINT16_SIZE;
    return uint16_offset;
}

inline SerializeOffset<SunspecModelDef> serialize_sunspecmodeldef(Serializer *const serializer,
                                                                  const uint16_t id,
                                                                  const SunspecGroupDefStruct group)
{
    SerializeOffset<SunspecModelDef> sunspecmodeldef_offset;
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, SUNSPECMODELDEF_ALIGNMENT);
    serializer->make_buffer_adequate();
    sunspecmodeldef_offset.offset = serializer->_tail_offset;

    *reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset + SUNSPECMODELDEF_ID_OFFSET])) = id;

    *reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset + SUNSPECMODELDEF_GROUP_OFFSET + SUNSPECGROUPDEF_ID_OFFSET])) = group.id.offset - (serializer->_tail_offset + SUNSPECMODELDEF_GROUP_OFFSET + SUNSPECGROUPDEF_ID_OFFSET);
    *reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset + SUNSPECMODELDEF_GROUP_OFFSET + SUNSPECGROUPDEF_COUNT_POINT_ID_OFFSET])) = group.count_point_id.offset - (serializer->_tail_offset + SUNSPECMODELDEF_GROUP_OFFSET + SUNSPECGROUPDEF_COUNT_POINT_ID_OFFSET);
    *reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset + SUNSPECMODELDEF_GROUP_OFFSET + SUNSPECGROUPDEF_POINTS_OFFSET])) = group.points.offset - (serializer->_tail_offset + SUNSPECMODELDEF_GROUP_OFFSET + SUNSPECGROUPDEF_POINTS_OFFSET);
    *reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset + SUNSPECMODELDEF_GROUP_OFFSET + SUNSPECGROUPDEF_GROUPS_OFFSET])) = group.groups.offset - (serializer->_tail_offset + SUNSPECMODELDEF_GROUP_OFFSET + SUNSPECGROUPDEF_GROUPS_OFFSET);
    *reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset + SUNSPECMODELDEF_GROUP_OFFSET + SUNSPECGROUPDEF_LABEL_OFFSET])) = group.label.offset - (serializer->_tail_offset + SUNSPECMODELDEF_GROUP_OFFSET + SUNSPECGROUPDEF_LABEL_OFFSET);
    *reinterpret_cast<uint8_t *>(&(serializer->_buffer[serializer->_tail_offset + SUNSPECMODELDEF_GROUP_OFFSET + SUNSPECGROUPDEF_COUNT_OFFSET])) = group.count;
    *reinterpret_cast<SunspecGroupType *>(&(serializer->_buffer[serializer->_tail_offset + SUNSPECMODELDEF_GROUP_OFFSET + SUNSPECGROUPDEF_TYPE_OFFSET])) = group.type;
    serializer->_tail_offset += SUNSPECMODELDEF_SIZE;
    return sunspecmodeldef_offset;
}

inline SerializeOffset<Uint32> serialize_uint32(Serializer *const serializer,
                                                const uint32_t value)
{
    SerializeOffset<Uint32> uint32_offset;
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, UINT32_ALIGNMENT);
    serializer->make_buffer_adequate();
    uint32_offset.offset = serializer->_tail_offset;

    *reinterpret_cast<uint32_t *>(&(serializer->_buffer[serializer->_tail_offset + UINT32_VALUE_OFFSET])) = value;
    serializer->_tail_offset += UINT32_SIZE;
    return uint32_offset;
}

inline SerializeOffset<Enum32> serialize_enum32(Serializer *const serializer,
                                                const uint32_t value)
{
    SerializeOffset<Enum32> enum32_offset;
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, ENUM32_ALIGNMENT);
    serializer->make_buffer_adequate();
    enum32_offset.offset = serializer->_tail_offset;

    *reinterpret_cast<uint32_t *>(&(serializer->_buffer[serializer->_tail_offset + ENUM32_VALUE_OFFSET])) = value;
    serializer->_tail_offset += ENUM32_SIZE;
    return enum32_offset;
}

inline SerializeOffset<Float32> serialize_float32(Serializer *const serializer,
                                                  const float value)
{
    SerializeOffset<Float32> float32_offset;
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, FLOAT32_ALIGNMENT);
    serializer->make_buffer_adequate();
    float32_offset.offset = serializer->_tail_offset;

    *reinterpret_cast<float *>(&(serializer->_buffer[serializer->_tail_offset + FLOAT32_VALUE_OFFSET])) = value;
    serializer->_tail_offset += FLOAT32_SIZE;
    return float32_offset;
}

inline SerializeOffset<Acc64> serialize_acc64(Serializer *const serializer,
                                              const uint64_t value)
{
    SerializeOffset<Acc64> acc64_offset;
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, ACC64_ALIGNMENT);
    serializer->make_buffer_adequate();
    acc64_offset.offset = serializer->_tail_offset;

    *reinterpret_cast<uint64_t *>(&(serializer->_buffer[serializer->_tail_offset + ACC64_VALUE_OFFSET])) = value;
    serializer->_tail_offset += ACC64_SIZE;
    return acc64_offset;
}

inline SerializeOffset<SunsSf> serialize_sunssf(Serializer *const serializer,
                                                const uint16_t value)
{
    SerializeOffset<SunsSf> sunssf_offset;
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, SUNSSF_ALIGNMENT);
    serializer->make_buffer_adequate();
    sunssf_offset.offset = serializer->_tail_offset;

    *reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset + SUNSSF_VALUE_OFFSET])) = value;
    serializer->_tail_offset += SUNSSF_SIZE;
    return sunssf_offset;
}

inline SerializeOffset<Enum64> serialize_enum64(Serializer *const serializer,
                                                const uint64_t value)
{
    SerializeOffset<Enum64> enum64_offset;
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, ENUM64_ALIGNMENT);
    serializer->make_buffer_adequate();
    enum64_offset.offset = serializer->_tail_offset;

    *reinterpret_cast<uint64_t *>(&(serializer->_buffer[serializer->_tail_offset + ENUM64_VALUE_OFFSET])) = value;
    serializer->_tail_offset += ENUM64_SIZE;
    return enum64_offset;
}

inline SerializeOffset<Float64> serialize_float64(Serializer *const serializer,
                                                  const double value)
{
    SerializeOffset<Float64> float64_offset;
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, FLOAT64_ALIGNMENT);
    serializer->make_buffer_adequate();
    float64_offset.offset = serializer->_tail_offset;

    *reinterpret_cast<double *>(&(serializer->_buffer[serializer->_tail_offset + FLOAT64_VALUE_OFFSET])) = value;
    serializer->_tail_offset += FLOAT64_SIZE;
    return float64_offset;
}

inline SerializeOffset<Vector<Uint64Struct>> serialize_vector_uint64_struct(Serializer *const serializer, std::vector<Uint64Struct> data_array)
{
    SerializeOffset<Vector<Uint64Struct>> data_array_offset;
    uint16_t len = data_array.size();
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, OFFSET_SIZE);
    serializer->make_buffer_adequate();
    data_array_offset.offset = serializer->_tail_offset;
    *reinterpret_cast<uint16_t *>(&serializer->_buffer[serializer->_tail_offset]) = len;
    serializer->_tail_offset += OFFSET_SIZE;
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, UINT64_ALIGNMENT);
    for (uint16_t i = 0; i < len; i++)
    {
        *reinterpret_cast<uint64_t *>(&(serializer->_buffer[serializer->_tail_offset + (UINT64_SIZE * i) + UINT64_VALUE_OFFSET])) = data_array[i].value;
        serializer->_tail_offset += (UINT64_SIZE * len);
    }
    return data_array_offset;
}

inline SerializeOffset<Vector<StringxStruct>> serialize_vector_stringx_struct(Serializer *const serializer, std::vector<StringxStruct> data_array)
{
    SerializeOffset<Vector<StringxStruct>> data_array_offset;
    uint16_t len = data_array.size();
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, OFFSET_SIZE);
    serializer->make_buffer_adequate();
    data_array_offset.offset = serializer->_tail_offset;
    *reinterpret_cast<uint16_t *>(&serializer->_buffer[serializer->_tail_offset]) = len;
    serializer->_tail_offset += OFFSET_SIZE;
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, STRINGX_ALIGNMENT);
    for (uint16_t i = 0; i < len; i++)
    {
        *reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset + (STRINGX_SIZE * i) + STRINGX_VALUE_OFFSET])) = data_array[i].value.offset - (serializer->_tail_offset + (STRINGX_SIZE * i) + STRINGX_VALUE_OFFSET);
        serializer->_tail_offset += (STRINGX_SIZE * len);
    }
    return data_array_offset;
}

inline SerializeOffset<Vector<Acc32Struct>> serialize_vector_acc32_struct(Serializer *const serializer, std::vector<Acc32Struct> data_array)
{
    SerializeOffset<Vector<Acc32Struct>> data_array_offset;
    uint16_t len = data_array.size();
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, OFFSET_SIZE);
    serializer->make_buffer_adequate();
    data_array_offset.offset = serializer->_tail_offset;
    *reinterpret_cast<uint16_t *>(&serializer->_buffer[serializer->_tail_offset]) = len;
    serializer->_tail_offset += OFFSET_SIZE;
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, ACC32_ALIGNMENT);
    for (uint16_t i = 0; i < len; i++)
    {
        *reinterpret_cast<uint32_t *>(&(serializer->_buffer[serializer->_tail_offset + (ACC32_SIZE * i) + ACC32_VALUE_OFFSET])) = data_array[i].value;
        serializer->_tail_offset += (ACC32_SIZE * len);
    }
    return data_array_offset;
}

inline SerializeOffset<Vector<Bitfield16Struct>> serialize_vector_bitfield16_struct(Serializer *const serializer, std::vector<Bitfield16Struct> data_array)
{
    SerializeOffset<Vector<Bitfield16Struct>> data_array_offset;
    uint16_t len = data_array.size();
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, OFFSET_SIZE);
    serializer->make_buffer_adequate();
    data_array_offset.offset = serializer->_tail_offset;
    *reinterpret_cast<uint16_t *>(&serializer->_buffer[serializer->_tail_offset]) = len;
    serializer->_tail_offset += OFFSET_SIZE;
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, BITFIELD16_ALIGNMENT);
    for (uint16_t i = 0; i < len; i++)
    {
        *reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset + (BITFIELD16_SIZE * i) + BITFIELD16_VALUE_OFFSET])) = data_array[i].value;
        serializer->_tail_offset += (BITFIELD16_SIZE * len);
    }
    return data_array_offset;
}

inline SerializeOffset<Vector<Enum16Struct>> serialize_vector_enum16_struct(Serializer *const serializer, std::vector<Enum16Struct> data_array)
{
    SerializeOffset<Vector<Enum16Struct>> data_array_offset;
    uint16_t len = data_array.size();
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, OFFSET_SIZE);
    serializer->make_buffer_adequate();
    data_array_offset.offset = serializer->_tail_offset;
    *reinterpret_cast<uint16_t *>(&serializer->_buffer[serializer->_tail_offset]) = len;
    serializer->_tail_offset += OFFSET_SIZE;
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, ENUM16_ALIGNMENT);
    for (uint16_t i = 0; i < len; i++)
    {
        *reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset + (ENUM16_SIZE * i) + ENUM16_VALUE_OFFSET])) = data_array[i].value;
        serializer->_tail_offset += (ENUM16_SIZE * len);
    }
    return data_array_offset;
}

inline SerializeOffset<Vector<Bitfield32Struct>> serialize_vector_bitfield32_struct(Serializer *const serializer, std::vector<Bitfield32Struct> data_array)
{
    SerializeOffset<Vector<Bitfield32Struct>> data_array_offset;
    uint16_t len = data_array.size();
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, OFFSET_SIZE);
    serializer->make_buffer_adequate();
    data_array_offset.offset = serializer->_tail_offset;
    *reinterpret_cast<uint16_t *>(&serializer->_buffer[serializer->_tail_offset]) = len;
    serializer->_tail_offset += OFFSET_SIZE;
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, BITFIELD32_ALIGNMENT);
    for (uint16_t i = 0; i < len; i++)
    {
        *reinterpret_cast<uint32_t *>(&(serializer->_buffer[serializer->_tail_offset + (BITFIELD32_SIZE * i) + BITFIELD32_VALUE_OFFSET])) = data_array[i].value;
        serializer->_tail_offset += (BITFIELD32_SIZE * len);
    }
    return data_array_offset;
}

inline SerializeOffset<Vector<Acc16Struct>> serialize_vector_acc16_struct(Serializer *const serializer, std::vector<Acc16Struct> data_array)
{
    SerializeOffset<Vector<Acc16Struct>> data_array_offset;
    uint16_t len = data_array.size();
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, OFFSET_SIZE);
    serializer->make_buffer_adequate();
    data_array_offset.offset = serializer->_tail_offset;
    *reinterpret_cast<uint16_t *>(&serializer->_buffer[serializer->_tail_offset]) = len;
    serializer->_tail_offset += OFFSET_SIZE;
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, ACC16_ALIGNMENT);
    for (uint16_t i = 0; i < len; i++)
    {
        *reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset + (ACC16_SIZE * i) + ACC16_VALUE_OFFSET])) = data_array[i].value;
        serializer->_tail_offset += (ACC16_SIZE * len);
    }
    return data_array_offset;
}

inline SerializeOffset<Vector<Eui48Struct>> serialize_vector_eui48_struct(Serializer *const serializer, std::vector<Eui48Struct> data_array)
{
    SerializeOffset<Vector<Eui48Struct>> data_array_offset;
    uint16_t len = data_array.size();
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, OFFSET_SIZE);
    serializer->make_buffer_adequate();
    data_array_offset.offset = serializer->_tail_offset;
    *reinterpret_cast<uint16_t *>(&serializer->_buffer[serializer->_tail_offset]) = len;
    serializer->_tail_offset += OFFSET_SIZE;
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, EUI48_ALIGNMENT);
    for (uint16_t i = 0; i < len; i++)
    {
        *reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset + (EUI48_SIZE * i) + EUI48_VALUE0_OFFSET])) = data_array[i].value0;
        *reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset + (EUI48_SIZE * i) + EUI48_VALUE1_OFFSET])) = data_array[i].value1;
        *reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset + (EUI48_SIZE * i) + EUI48_VALUE2_OFFSET])) = data_array[i].value2;
        serializer->_tail_offset += (EUI48_SIZE * len);
    }
    return data_array_offset;
}

inline SerializeOffset<Vector<Sint16Struct>> serialize_vector_sint16_struct(Serializer *const serializer, std::vector<Sint16Struct> data_array)
{
    SerializeOffset<Vector<Sint16Struct>> data_array_offset;
    uint16_t len = data_array.size();
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, OFFSET_SIZE);
    serializer->make_buffer_adequate();
    data_array_offset.offset = serializer->_tail_offset;
    *reinterpret_cast<uint16_t *>(&serializer->_buffer[serializer->_tail_offset]) = len;
    serializer->_tail_offset += OFFSET_SIZE;
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, SINT16_ALIGNMENT);
    for (uint16_t i = 0; i < len; i++)
    {
        *reinterpret_cast<int16_t *>(&(serializer->_buffer[serializer->_tail_offset + (SINT16_SIZE * i) + SINT16_VALUE_OFFSET])) = data_array[i].value;
        serializer->_tail_offset += (SINT16_SIZE * len);
    }
    return data_array_offset;
}

inline SerializeOffset<Vector<SunspecGroupDefStruct>> serialize_vector_sunspecgroupdef_struct(Serializer *const serializer, std::vector<SunspecGroupDefStruct> data_array)
{
    SerializeOffset<Vector<SunspecGroupDefStruct>> data_array_offset;
    uint16_t len = data_array.size();
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, OFFSET_SIZE);
    serializer->make_buffer_adequate();
    data_array_offset.offset = serializer->_tail_offset;
    *reinterpret_cast<uint16_t *>(&serializer->_buffer[serializer->_tail_offset]) = len;
    serializer->_tail_offset += OFFSET_SIZE;
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, SUNSPECGROUPDEF_ALIGNMENT);
    for (uint16_t i = 0; i < len; i++)
    {
        *reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset + (SUNSPECGROUPDEF_SIZE * i) + SUNSPECGROUPDEF_ID_OFFSET])) = data_array[i].id.offset - (serializer->_tail_offset + (SUNSPECGROUPDEF_SIZE * i) + SUNSPECGROUPDEF_ID_OFFSET);
        *reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset + (SUNSPECGROUPDEF_SIZE * i) + SUNSPECGROUPDEF_COUNT_POINT_ID_OFFSET])) = data_array[i].count_point_id.offset - (serializer->_tail_offset + (SUNSPECGROUPDEF_SIZE * i) + SUNSPECGROUPDEF_COUNT_POINT_ID_OFFSET);
        *reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset + (SUNSPECGROUPDEF_SIZE * i) + SUNSPECGROUPDEF_POINTS_OFFSET])) = data_array[i].points.offset - (serializer->_tail_offset + (SUNSPECGROUPDEF_SIZE * i) + SUNSPECGROUPDEF_POINTS_OFFSET);
        *reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset + (SUNSPECGROUPDEF_SIZE * i) + SUNSPECGROUPDEF_GROUPS_OFFSET])) = data_array[i].groups.offset - (serializer->_tail_offset + (SUNSPECGROUPDEF_SIZE * i) + SUNSPECGROUPDEF_GROUPS_OFFSET);
        *reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset + (SUNSPECGROUPDEF_SIZE * i) + SUNSPECGROUPDEF_LABEL_OFFSET])) = data_array[i].label.offset - (serializer->_tail_offset + (SUNSPECGROUPDEF_SIZE * i) + SUNSPECGROUPDEF_LABEL_OFFSET);
        *reinterpret_cast<uint8_t *>(&(serializer->_buffer[serializer->_tail_offset + (SUNSPECGROUPDEF_SIZE * i) + SUNSPECGROUPDEF_COUNT_OFFSET])) = data_array[i].count;
        *reinterpret_cast<SunspecGroupType *>(&(serializer->_buffer[serializer->_tail_offset + (SUNSPECGROUPDEF_SIZE * i) + SUNSPECGROUPDEF_TYPE_OFFSET])) = data_array[i].type;
        serializer->_tail_offset += (SUNSPECGROUPDEF_SIZE * len);
    }
    return data_array_offset;
}

inline SerializeOffset<Vector<Sint64Struct>> serialize_vector_sint64_struct(Serializer *const serializer, std::vector<Sint64Struct> data_array)
{
    SerializeOffset<Vector<Sint64Struct>> data_array_offset;
    uint16_t len = data_array.size();
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, OFFSET_SIZE);
    serializer->make_buffer_adequate();
    data_array_offset.offset = serializer->_tail_offset;
    *reinterpret_cast<uint16_t *>(&serializer->_buffer[serializer->_tail_offset]) = len;
    serializer->_tail_offset += OFFSET_SIZE;
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, SINT64_ALIGNMENT);
    for (uint16_t i = 0; i < len; i++)
    {
        *reinterpret_cast<int64_t *>(&(serializer->_buffer[serializer->_tail_offset + (SINT64_SIZE * i) + SINT64_VALUE_OFFSET])) = data_array[i].value;
        serializer->_tail_offset += (SINT64_SIZE * len);
    }
    return data_array_offset;
}

inline SerializeOffset<Vector<Pad16Struct>> serialize_vector_pad16_struct(Serializer *const serializer, std::vector<Pad16Struct> data_array)
{
    SerializeOffset<Vector<Pad16Struct>> data_array_offset;
    uint16_t len = data_array.size();
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, OFFSET_SIZE);
    serializer->make_buffer_adequate();
    data_array_offset.offset = serializer->_tail_offset;
    *reinterpret_cast<uint16_t *>(&serializer->_buffer[serializer->_tail_offset]) = len;
    serializer->_tail_offset += OFFSET_SIZE;
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, PAD16_ALIGNMENT);
    for (uint16_t i = 0; i < len; i++)
    {
        *reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset + (PAD16_SIZE * i) + PAD16_VALUE_OFFSET])) = data_array[i].value;
        serializer->_tail_offset += (PAD16_SIZE * len);
    }
    return data_array_offset;
}

inline SerializeOffset<Vector<Bitfield64Struct>> serialize_vector_bitfield64_struct(Serializer *const serializer, std::vector<Bitfield64Struct> data_array)
{
    SerializeOffset<Vector<Bitfield64Struct>> data_array_offset;
    uint16_t len = data_array.size();
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, OFFSET_SIZE);
    serializer->make_buffer_adequate();
    data_array_offset.offset = serializer->_tail_offset;
    *reinterpret_cast<uint16_t *>(&serializer->_buffer[serializer->_tail_offset]) = len;
    serializer->_tail_offset += OFFSET_SIZE;
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, BITFIELD64_ALIGNMENT);
    for (uint16_t i = 0; i < len; i++)
    {
        *reinterpret_cast<uint64_t *>(&(serializer->_buffer[serializer->_tail_offset + (BITFIELD64_SIZE * i) + BITFIELD64_VALUE_OFFSET])) = data_array[i].value;
        serializer->_tail_offset += (BITFIELD64_SIZE * len);
    }
    return data_array_offset;
}

inline SerializeOffset<Vector<Sint32Struct>> serialize_vector_sint32_struct(Serializer *const serializer, std::vector<Sint32Struct> data_array)
{
    SerializeOffset<Vector<Sint32Struct>> data_array_offset;
    uint16_t len = data_array.size();
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, OFFSET_SIZE);
    serializer->make_buffer_adequate();
    data_array_offset.offset = serializer->_tail_offset;
    *reinterpret_cast<uint16_t *>(&serializer->_buffer[serializer->_tail_offset]) = len;
    serializer->_tail_offset += OFFSET_SIZE;
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, SINT32_ALIGNMENT);
    for (uint16_t i = 0; i < len; i++)
    {
        *reinterpret_cast<int32_t *>(&(serializer->_buffer[serializer->_tail_offset + (SINT32_SIZE * i) + SINT32_VALUE_OFFSET])) = data_array[i].value;
        serializer->_tail_offset += (SINT32_SIZE * len);
    }
    return data_array_offset;
}

inline SerializeOffset<Vector<IpAddrStruct>> serialize_vector_ipaddr_struct(Serializer *const serializer, std::vector<IpAddrStruct> data_array)
{
    SerializeOffset<Vector<IpAddrStruct>> data_array_offset;
    uint16_t len = data_array.size();
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, OFFSET_SIZE);
    serializer->make_buffer_adequate();
    data_array_offset.offset = serializer->_tail_offset;
    *reinterpret_cast<uint16_t *>(&serializer->_buffer[serializer->_tail_offset]) = len;
    serializer->_tail_offset += OFFSET_SIZE;
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, IPADDR_ALIGNMENT);
    for (uint16_t i = 0; i < len; i++)
    {
        *reinterpret_cast<uint8_t *>(&(serializer->_buffer[serializer->_tail_offset + (IPADDR_SIZE * i) + IPADDR_OCTET1_OFFSET])) = data_array[i].octet1;
        *reinterpret_cast<uint8_t *>(&(serializer->_buffer[serializer->_tail_offset + (IPADDR_SIZE * i) + IPADDR_OCTET2_OFFSET])) = data_array[i].octet2;
        *reinterpret_cast<uint8_t *>(&(serializer->_buffer[serializer->_tail_offset + (IPADDR_SIZE * i) + IPADDR_OCTET3_OFFSET])) = data_array[i].octet3;
        *reinterpret_cast<uint8_t *>(&(serializer->_buffer[serializer->_tail_offset + (IPADDR_SIZE * i) + IPADDR_OCTET4_OFFSET])) = data_array[i].octet4;
        serializer->_tail_offset += (IPADDR_SIZE * len);
    }
    return data_array_offset;
}

inline SerializeOffset<Vector<Ipv6AddrStruct>> serialize_vector_ipv6addr_struct(Serializer *const serializer, std::vector<Ipv6AddrStruct> data_array)
{
    SerializeOffset<Vector<Ipv6AddrStruct>> data_array_offset;
    uint16_t len = data_array.size();
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, OFFSET_SIZE);
    serializer->make_buffer_adequate();
    data_array_offset.offset = serializer->_tail_offset;
    *reinterpret_cast<uint16_t *>(&serializer->_buffer[serializer->_tail_offset]) = len;
    serializer->_tail_offset += OFFSET_SIZE;
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, IPV6ADDR_ALIGNMENT);
    for (uint16_t i = 0; i < len; i++)
    {
        *reinterpret_cast<uint8_t *>(&(serializer->_buffer[serializer->_tail_offset + (IPV6ADDR_SIZE * i) + IPV6ADDR_OCTET0_OFFSET])) = data_array[i].octet0;
        *reinterpret_cast<uint8_t *>(&(serializer->_buffer[serializer->_tail_offset + (IPV6ADDR_SIZE * i) + IPV6ADDR_OCTET1_OFFSET])) = data_array[i].octet1;
        *reinterpret_cast<uint8_t *>(&(serializer->_buffer[serializer->_tail_offset + (IPV6ADDR_SIZE * i) + IPV6ADDR_OCTET2_OFFSET])) = data_array[i].octet2;
        *reinterpret_cast<uint8_t *>(&(serializer->_buffer[serializer->_tail_offset + (IPV6ADDR_SIZE * i) + IPV6ADDR_OCTET3_OFFSET])) = data_array[i].octet3;
        *reinterpret_cast<uint8_t *>(&(serializer->_buffer[serializer->_tail_offset + (IPV6ADDR_SIZE * i) + IPV6ADDR_OCTET4_OFFSET])) = data_array[i].octet4;
        *reinterpret_cast<uint8_t *>(&(serializer->_buffer[serializer->_tail_offset + (IPV6ADDR_SIZE * i) + IPV6ADDR_OCTET5_OFFSET])) = data_array[i].octet5;
        serializer->_tail_offset += (IPV6ADDR_SIZE * len);
    }
    return data_array_offset;
}

inline SerializeOffset<Vector<SunspecPointDataStruct>> serialize_vector_sunspecpointdata_struct(Serializer *const serializer, std::vector<SunspecPointDataStruct> data_array)
{
    SerializeOffset<Vector<SunspecPointDataStruct>> data_array_offset;
    uint16_t len = data_array.size();
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, OFFSET_SIZE);
    serializer->make_buffer_adequate();
    data_array_offset.offset = serializer->_tail_offset;
    *reinterpret_cast<uint16_t *>(&serializer->_buffer[serializer->_tail_offset]) = len;
    serializer->_tail_offset += OFFSET_SIZE;
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, SUNSPECPOINTDATA_ALIGNMENT);
    for (uint16_t i = 0; i < len; i++)
    {
        serializer->_tail_offset += (SUNSPECPOINTDATA_SIZE * len);
    }
    return data_array_offset;
}

inline SerializeOffset<Vector<SunspecPointDefStruct>> serialize_vector_sunspecpointdef_struct(Serializer *const serializer, std::vector<SunspecPointDefStruct> data_array)
{
    SerializeOffset<Vector<SunspecPointDefStruct>> data_array_offset;
    uint16_t len = data_array.size();
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, OFFSET_SIZE);
    serializer->make_buffer_adequate();
    data_array_offset.offset = serializer->_tail_offset;
    *reinterpret_cast<uint16_t *>(&serializer->_buffer[serializer->_tail_offset]) = len;
    serializer->_tail_offset += OFFSET_SIZE;
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, SUNSPECPOINTDEF_ALIGNMENT);
    for (uint16_t i = 0; i < len; i++)
    {
        *reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset + (SUNSPECPOINTDEF_SIZE * i) + SUNSPECPOINTDEF_ID_OFFSET])) = data_array[i].id.offset - (serializer->_tail_offset + (SUNSPECPOINTDEF_SIZE * i) + SUNSPECPOINTDEF_ID_OFFSET);
        *reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset + (SUNSPECPOINTDEF_SIZE * i) + SUNSPECPOINTDEF_SF_ID_OFFSET])) = data_array[i].sf_id.offset - (serializer->_tail_offset + (SUNSPECPOINTDEF_SIZE * i) + SUNSPECPOINTDEF_SF_ID_OFFSET);
        *reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset + (SUNSPECPOINTDEF_SIZE * i) + SUNSPECPOINTDEF_UNITS_OFFSET])) = data_array[i].units.offset - (serializer->_tail_offset + (SUNSPECPOINTDEF_SIZE * i) + SUNSPECPOINTDEF_UNITS_OFFSET);
        *reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset + (SUNSPECPOINTDEF_SIZE * i) + SUNSPECPOINTDEF_LABEL_OFFSET])) = data_array[i].label.offset - (serializer->_tail_offset + (SUNSPECPOINTDEF_SIZE * i) + SUNSPECPOINTDEF_LABEL_OFFSET);
        *reinterpret_cast<SunspecPointData_enum *>(&(serializer->_buffer[serializer->_tail_offset + (SUNSPECPOINTDEF_SIZE * i) + SUNSPECPOINTDEF_DATA_TYPE_OFFSET])) = data_array[i].data_type;
        *reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset + (SUNSPECPOINTDEF_SIZE * i) + SUNSPECPOINTDEF_DATA_OFFSET])) = data_array[i].data.offset - (serializer->_tail_offset + (SUNSPECPOINTDEF_SIZE * i) + SUNSPECPOINTDEF_DATA_OFFSET);
        *reinterpret_cast<uint8_t *>(&(serializer->_buffer[serializer->_tail_offset + (SUNSPECPOINTDEF_SIZE * i) + SUNSPECPOINTDEF_COUNT_OFFSET])) = data_array[i].count;
        *reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset + (SUNSPECPOINTDEF_SIZE * i) + SUNSPECPOINTDEF_COUNT_POINT_ID_OFFSET])) = data_array[i].count_point_id.offset - (serializer->_tail_offset + (SUNSPECPOINTDEF_SIZE * i) + SUNSPECPOINTDEF_COUNT_POINT_ID_OFFSET);
        *reinterpret_cast<uint8_t *>(&(serializer->_buffer[serializer->_tail_offset + (SUNSPECPOINTDEF_SIZE * i) + SUNSPECPOINTDEF_SIZE_OFFSET])) = data_array[i].size;
        *reinterpret_cast<int8_t *>(&(serializer->_buffer[serializer->_tail_offset + (SUNSPECPOINTDEF_SIZE * i) + SUNSPECPOINTDEF_SF_OFFSET])) = data_array[i].sf;
        *reinterpret_cast<SunspecPointAccess *>(&(serializer->_buffer[serializer->_tail_offset + (SUNSPECPOINTDEF_SIZE * i) + SUNSPECPOINTDEF_ACCESS_OFFSET])) = data_array[i].access;
        *reinterpret_cast<SunspecPointMandatory *>(&(serializer->_buffer[serializer->_tail_offset + (SUNSPECPOINTDEF_SIZE * i) + SUNSPECPOINTDEF_MANDATORY_OFFSET])) = data_array[i].mandatory;
        serializer->_tail_offset += (SUNSPECPOINTDEF_SIZE * len);
    }
    return data_array_offset;
}

inline SerializeOffset<Vector<Raw16Struct>> serialize_vector_raw16_struct(Serializer *const serializer, std::vector<Raw16Struct> data_array)
{
    SerializeOffset<Vector<Raw16Struct>> data_array_offset;
    uint16_t len = data_array.size();
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, OFFSET_SIZE);
    serializer->make_buffer_adequate();
    data_array_offset.offset = serializer->_tail_offset;
    *reinterpret_cast<uint16_t *>(&serializer->_buffer[serializer->_tail_offset]) = len;
    serializer->_tail_offset += OFFSET_SIZE;
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, RAW16_ALIGNMENT);
    for (uint16_t i = 0; i < len; i++)
    {
        *reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset + (RAW16_SIZE * i) + RAW16_VALUE_OFFSET])) = data_array[i].value;
        serializer->_tail_offset += (RAW16_SIZE * len);
    }
    return data_array_offset;
}

inline SerializeOffset<Vector<Uint16Struct>> serialize_vector_uint16_struct(Serializer *const serializer, std::vector<Uint16Struct> data_array)
{
    SerializeOffset<Vector<Uint16Struct>> data_array_offset;
    uint16_t len = data_array.size();
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, OFFSET_SIZE);
    serializer->make_buffer_adequate();
    data_array_offset.offset = serializer->_tail_offset;
    *reinterpret_cast<uint16_t *>(&serializer->_buffer[serializer->_tail_offset]) = len;
    serializer->_tail_offset += OFFSET_SIZE;
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, UINT16_ALIGNMENT);
    for (uint16_t i = 0; i < len; i++)
    {
        *reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset + (UINT16_SIZE * i) + UINT16_VALUE_OFFSET])) = data_array[i].value;
        serializer->_tail_offset += (UINT16_SIZE * len);
    }
    return data_array_offset;
}

inline SerializeOffset<Vector<SunspecModelDefStruct>> serialize_vector_sunspecmodeldef_struct(Serializer *const serializer, std::vector<SunspecModelDefStruct> data_array)
{
    SerializeOffset<Vector<SunspecModelDefStruct>> data_array_offset;
    uint16_t len = data_array.size();
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, OFFSET_SIZE);
    serializer->make_buffer_adequate();
    data_array_offset.offset = serializer->_tail_offset;
    *reinterpret_cast<uint16_t *>(&serializer->_buffer[serializer->_tail_offset]) = len;
    serializer->_tail_offset += OFFSET_SIZE;
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, SUNSPECMODELDEF_ALIGNMENT);
    for (uint16_t i = 0; i < len; i++)
    {
        *reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset + (SUNSPECMODELDEF_SIZE * i) + SUNSPECMODELDEF_ID_OFFSET])) = data_array[i].id;

        *reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset + (SUNSPECMODELDEF_SIZE * i) + SUNSPECMODELDEF_GROUP_OFFSET + SUNSPECGROUPDEF_ID_OFFSET])) = data_array[i].group.id.offset - (serializer->_tail_offset + (SUNSPECMODELDEF_SIZE * i) + SUNSPECMODELDEF_GROUP_OFFSET + SUNSPECGROUPDEF_ID_OFFSET);
        *reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset + (SUNSPECMODELDEF_SIZE * i) + SUNSPECMODELDEF_GROUP_OFFSET + SUNSPECGROUPDEF_COUNT_POINT_ID_OFFSET])) = data_array[i].group.count_point_id.offset - (serializer->_tail_offset + (SUNSPECMODELDEF_SIZE * i) + SUNSPECMODELDEF_GROUP_OFFSET + SUNSPECGROUPDEF_COUNT_POINT_ID_OFFSET);
        *reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset + (SUNSPECMODELDEF_SIZE * i) + SUNSPECMODELDEF_GROUP_OFFSET + SUNSPECGROUPDEF_POINTS_OFFSET])) = data_array[i].group.points.offset - (serializer->_tail_offset + (SUNSPECMODELDEF_SIZE * i) + SUNSPECMODELDEF_GROUP_OFFSET + SUNSPECGROUPDEF_POINTS_OFFSET);
        *reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset + (SUNSPECMODELDEF_SIZE * i) + SUNSPECMODELDEF_GROUP_OFFSET + SUNSPECGROUPDEF_GROUPS_OFFSET])) = data_array[i].group.groups.offset - (serializer->_tail_offset + (SUNSPECMODELDEF_SIZE * i) + SUNSPECMODELDEF_GROUP_OFFSET + SUNSPECGROUPDEF_GROUPS_OFFSET);
        *reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset + (SUNSPECMODELDEF_SIZE * i) + SUNSPECMODELDEF_GROUP_OFFSET + SUNSPECGROUPDEF_LABEL_OFFSET])) = data_array[i].group.label.offset - (serializer->_tail_offset + (SUNSPECMODELDEF_SIZE * i) + SUNSPECMODELDEF_GROUP_OFFSET + SUNSPECGROUPDEF_LABEL_OFFSET);
        *reinterpret_cast<uint8_t *>(&(serializer->_buffer[serializer->_tail_offset + (SUNSPECMODELDEF_SIZE * i) + SUNSPECMODELDEF_GROUP_OFFSET + SUNSPECGROUPDEF_COUNT_OFFSET])) = data_array[i].group.count;
        *reinterpret_cast<SunspecGroupType *>(&(serializer->_buffer[serializer->_tail_offset + (SUNSPECMODELDEF_SIZE * i) + SUNSPECMODELDEF_GROUP_OFFSET + SUNSPECGROUPDEF_TYPE_OFFSET])) = data_array[i].group.type;
        serializer->_tail_offset += (SUNSPECMODELDEF_SIZE * len);
    }
    return data_array_offset;
}

inline SerializeOffset<Vector<Uint32Struct>> serialize_vector_uint32_struct(Serializer *const serializer, std::vector<Uint32Struct> data_array)
{
    SerializeOffset<Vector<Uint32Struct>> data_array_offset;
    uint16_t len = data_array.size();
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, OFFSET_SIZE);
    serializer->make_buffer_adequate();
    data_array_offset.offset = serializer->_tail_offset;
    *reinterpret_cast<uint16_t *>(&serializer->_buffer[serializer->_tail_offset]) = len;
    serializer->_tail_offset += OFFSET_SIZE;
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, UINT32_ALIGNMENT);
    for (uint16_t i = 0; i < len; i++)
    {
        *reinterpret_cast<uint32_t *>(&(serializer->_buffer[serializer->_tail_offset + (UINT32_SIZE * i) + UINT32_VALUE_OFFSET])) = data_array[i].value;
        serializer->_tail_offset += (UINT32_SIZE * len);
    }
    return data_array_offset;
}

inline SerializeOffset<Vector<Enum32Struct>> serialize_vector_enum32_struct(Serializer *const serializer, std::vector<Enum32Struct> data_array)
{
    SerializeOffset<Vector<Enum32Struct>> data_array_offset;
    uint16_t len = data_array.size();
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, OFFSET_SIZE);
    serializer->make_buffer_adequate();
    data_array_offset.offset = serializer->_tail_offset;
    *reinterpret_cast<uint16_t *>(&serializer->_buffer[serializer->_tail_offset]) = len;
    serializer->_tail_offset += OFFSET_SIZE;
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, ENUM32_ALIGNMENT);
    for (uint16_t i = 0; i < len; i++)
    {
        *reinterpret_cast<uint32_t *>(&(serializer->_buffer[serializer->_tail_offset + (ENUM32_SIZE * i) + ENUM32_VALUE_OFFSET])) = data_array[i].value;
        serializer->_tail_offset += (ENUM32_SIZE * len);
    }
    return data_array_offset;
}

inline SerializeOffset<Vector<Float32Struct>> serialize_vector_float32_struct(Serializer *const serializer, std::vector<Float32Struct> data_array)
{
    SerializeOffset<Vector<Float32Struct>> data_array_offset;
    uint16_t len = data_array.size();
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, OFFSET_SIZE);
    serializer->make_buffer_adequate();
    data_array_offset.offset = serializer->_tail_offset;
    *reinterpret_cast<uint16_t *>(&serializer->_buffer[serializer->_tail_offset]) = len;
    serializer->_tail_offset += OFFSET_SIZE;
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, FLOAT32_ALIGNMENT);
    for (uint16_t i = 0; i < len; i++)
    {
        *reinterpret_cast<float *>(&(serializer->_buffer[serializer->_tail_offset + (FLOAT32_SIZE * i) + FLOAT32_VALUE_OFFSET])) = data_array[i].value;
        serializer->_tail_offset += (FLOAT32_SIZE * len);
    }
    return data_array_offset;
}

inline SerializeOffset<Vector<Acc64Struct>> serialize_vector_acc64_struct(Serializer *const serializer, std::vector<Acc64Struct> data_array)
{
    SerializeOffset<Vector<Acc64Struct>> data_array_offset;
    uint16_t len = data_array.size();
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, OFFSET_SIZE);
    serializer->make_buffer_adequate();
    data_array_offset.offset = serializer->_tail_offset;
    *reinterpret_cast<uint16_t *>(&serializer->_buffer[serializer->_tail_offset]) = len;
    serializer->_tail_offset += OFFSET_SIZE;
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, ACC64_ALIGNMENT);
    for (uint16_t i = 0; i < len; i++)
    {
        *reinterpret_cast<uint64_t *>(&(serializer->_buffer[serializer->_tail_offset + (ACC64_SIZE * i) + ACC64_VALUE_OFFSET])) = data_array[i].value;
        serializer->_tail_offset += (ACC64_SIZE * len);
    }
    return data_array_offset;
}

inline SerializeOffset<Vector<SunsSfStruct>> serialize_vector_sunssf_struct(Serializer *const serializer, std::vector<SunsSfStruct> data_array)
{
    SerializeOffset<Vector<SunsSfStruct>> data_array_offset;
    uint16_t len = data_array.size();
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, OFFSET_SIZE);
    serializer->make_buffer_adequate();
    data_array_offset.offset = serializer->_tail_offset;
    *reinterpret_cast<uint16_t *>(&serializer->_buffer[serializer->_tail_offset]) = len;
    serializer->_tail_offset += OFFSET_SIZE;
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, SUNSSF_ALIGNMENT);
    for (uint16_t i = 0; i < len; i++)
    {
        *reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset + (SUNSSF_SIZE * i) + SUNSSF_VALUE_OFFSET])) = data_array[i].value;
        serializer->_tail_offset += (SUNSSF_SIZE * len);
    }
    return data_array_offset;
}

inline SerializeOffset<Vector<Enum64Struct>> serialize_vector_enum64_struct(Serializer *const serializer, std::vector<Enum64Struct> data_array)
{
    SerializeOffset<Vector<Enum64Struct>> data_array_offset;
    uint16_t len = data_array.size();
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, OFFSET_SIZE);
    serializer->make_buffer_adequate();
    data_array_offset.offset = serializer->_tail_offset;
    *reinterpret_cast<uint16_t *>(&serializer->_buffer[serializer->_tail_offset]) = len;
    serializer->_tail_offset += OFFSET_SIZE;
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, ENUM64_ALIGNMENT);
    for (uint16_t i = 0; i < len; i++)
    {
        *reinterpret_cast<uint64_t *>(&(serializer->_buffer[serializer->_tail_offset + (ENUM64_SIZE * i) + ENUM64_VALUE_OFFSET])) = data_array[i].value;
        serializer->_tail_offset += (ENUM64_SIZE * len);
    }
    return data_array_offset;
}

inline SerializeOffset<Vector<Float64Struct>> serialize_vector_float64_struct(Serializer *const serializer, std::vector<Float64Struct> data_array)
{
    SerializeOffset<Vector<Float64Struct>> data_array_offset;
    uint16_t len = data_array.size();
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, OFFSET_SIZE);
    serializer->make_buffer_adequate();
    data_array_offset.offset = serializer->_tail_offset;
    *reinterpret_cast<uint16_t *>(&serializer->_buffer[serializer->_tail_offset]) = len;
    serializer->_tail_offset += OFFSET_SIZE;
    serializer->_tail_offset += get_padding_size(serializer->_tail_offset, FLOAT64_ALIGNMENT);
    for (uint16_t i = 0; i < len; i++)
    {
        *reinterpret_cast<double *>(&(serializer->_buffer[serializer->_tail_offset + (FLOAT64_SIZE * i) + FLOAT64_VALUE_OFFSET])) = data_array[i].value;
        serializer->_tail_offset += (FLOAT64_SIZE * len);
    }
    return data_array_offset;
}

inline unsigned char *serialize_sunspecmodeldef_root(Serializer *const serializer,
                                                     const uint16_t id,
                                                     const SunspecGroupDefStruct group)
{
    uint16_t current_offset = OFFSET_SIZE * 2 + get_padding_size(OFFSET_SIZE * 2, SUNSPECMODELDEF_ALIGNMENT);

    *reinterpret_cast<uint16_t *>(&(serializer->_buffer[current_offset + SUNSPECMODELDEF_ID_OFFSET])) = id;

    *reinterpret_cast<uint16_t *>(&(serializer->_buffer[current_offset + SUNSPECMODELDEF_GROUP_OFFSET + SUNSPECGROUPDEF_ID_OFFSET])) = group.id.offset - (current_offset + SUNSPECMODELDEF_GROUP_OFFSET + SUNSPECGROUPDEF_ID_OFFSET);
    *reinterpret_cast<uint16_t *>(&(serializer->_buffer[current_offset + SUNSPECMODELDEF_GROUP_OFFSET + SUNSPECGROUPDEF_COUNT_POINT_ID_OFFSET])) = group.count_point_id.offset - (current_offset + SUNSPECMODELDEF_GROUP_OFFSET + SUNSPECGROUPDEF_COUNT_POINT_ID_OFFSET);
    *reinterpret_cast<uint16_t *>(&(serializer->_buffer[current_offset + SUNSPECMODELDEF_GROUP_OFFSET + SUNSPECGROUPDEF_POINTS_OFFSET])) = group.points.offset - (current_offset + SUNSPECMODELDEF_GROUP_OFFSET + SUNSPECGROUPDEF_POINTS_OFFSET);
    *reinterpret_cast<uint16_t *>(&(serializer->_buffer[current_offset + SUNSPECMODELDEF_GROUP_OFFSET + SUNSPECGROUPDEF_GROUPS_OFFSET])) = group.groups.offset - (current_offset + SUNSPECMODELDEF_GROUP_OFFSET + SUNSPECGROUPDEF_GROUPS_OFFSET);
    *reinterpret_cast<uint16_t *>(&(serializer->_buffer[current_offset + SUNSPECMODELDEF_GROUP_OFFSET + SUNSPECGROUPDEF_LABEL_OFFSET])) = group.label.offset - (current_offset + SUNSPECMODELDEF_GROUP_OFFSET + SUNSPECGROUPDEF_LABEL_OFFSET);
    *reinterpret_cast<uint8_t *>(&(serializer->_buffer[current_offset + SUNSPECMODELDEF_GROUP_OFFSET + SUNSPECGROUPDEF_COUNT_OFFSET])) = group.count;
    *reinterpret_cast<SunspecGroupType *>(&(serializer->_buffer[current_offset + SUNSPECMODELDEF_GROUP_OFFSET + SUNSPECGROUPDEF_TYPE_OFFSET])) = group.type;

    return serializer->_buffer;
}