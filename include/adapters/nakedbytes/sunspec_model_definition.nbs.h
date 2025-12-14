
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <type_traits>
#include <vector>

#define OFFSET_SIZE 2



struct acc32; 
struct SunspecPointData; 
struct acc64; 
struct pad; 
struct eui48; 
struct ipaddr; 
struct ipv6addr; 
struct SunspecModelDef; 
struct enum16; 
struct enum32; 
struct enum64; 
struct bitfield16; 
struct SunspecGroupPointDef; 
struct bitfield32; 
struct bitfield64; 
struct SunspecPointDef; 
struct sunssf; 
struct acc16; 






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

template<typename T, typename Enable = void>
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

template<typename T>
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

template<typename T> struct is_Offset_Type : std::false_type {};
template<typename T>
struct is_Offset_Type<Offset<T>> : std::true_type {};


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

template<typename T, typename Enable = void>
struct Vector
{
    unsigned char *data;

    bool is_null() const
    {
        return *reinterpret_cast<uint16_t *>(&data[0]) == 0;
    }
    
    uint16_t size() const
    {
        int16_t offset =  *reinterpret_cast<uint16_t *>(&data[0]);
        return *reinterpret_cast<uint16_t *>(&data[offset]);
    }

    T get(size_t index) const
    {
        int16_t offset =  *reinterpret_cast<uint16_t *>(&data[0]) + OFFSET_SIZE + OFFSET_SIZE * index;
       

        return T(&data[offset]);
    }

    Vector(unsigned char *dataPtr)
    {
        data = dataPtr;
    }
};

template<typename T>
struct Vector<T, typename std::enable_if<(std::is_floating_point<T>::value || std::is_integral<T>::value)>::type>
{
    unsigned char *data;

    bool is_null() const
    {
        return *reinterpret_cast<uint16_t *>(&data[0]) == 0;
    }
    
    uint16_t size() const
    {
        int16_t offset =  *reinterpret_cast<uint16_t *>(&data[0]);
        return *reinterpret_cast<uint16_t *>(&data[offset]);
    }

    T get(size_t index) const
    {
        int16_t offset =  *reinterpret_cast<uint16_t *>(&data[0]) + OFFSET_SIZE + OFFSET_SIZE * index;
       

        return static_cast<T>(data[offset]);
    }

    Vector(unsigned char *dataPtr)
    {
        data = dataPtr;
    }
};





struct acc32 {

unsigned char * data_;

acc32(unsigned char * data) : data_(data) {}

#define ACC32_VALUE_OFFSET 0
#define ACC32_ALIGNMENT 4
#define ACC32_SIZE 4


uint32_t value() const {
return *reinterpret_cast<uint32_t*>(&data_[ACC32_VALUE_OFFSET ]);
}

};





enum SunspecPointData_enum : uint16_t {

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

const char * SunspecPointData_enum_to_string(SunspecPointData_enum value){
switch (value){
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




struct pad {

unsigned char * data_;

pad(unsigned char * data) : data_(data) {}

#define PAD_VALUE_OFFSET 0
#define PAD_ALIGNMENT 2
#define PAD_SIZE 2


uint16_t value() const {
return *reinterpret_cast<uint16_t*>(&data_[PAD_VALUE_OFFSET ]);
}

};





struct enum16 {

unsigned char * data_;

enum16(unsigned char * data) : data_(data) {}

#define ENUM16_VALUE_OFFSET 0
#define ENUM16_ALIGNMENT 2
#define ENUM16_SIZE 2


uint16_t value() const {
return *reinterpret_cast<uint16_t*>(&data_[ENUM16_VALUE_OFFSET ]);
}

};





struct enum32 {

unsigned char * data_;

enum32(unsigned char * data) : data_(data) {}

#define ENUM32_VALUE_OFFSET 0
#define ENUM32_ALIGNMENT 4
#define ENUM32_SIZE 4


uint32_t value() const {
return *reinterpret_cast<uint32_t*>(&data_[ENUM32_VALUE_OFFSET ]);
}

};





struct enum64 {

unsigned char * data_;

enum64(unsigned char * data) : data_(data) {}

#define ENUM64_VALUE_OFFSET 0
#define ENUM64_ALIGNMENT 8
#define ENUM64_SIZE 8


uint64_t value() const {
return *reinterpret_cast<uint64_t*>(&data_[ENUM64_VALUE_OFFSET ]);
}

};





struct bitfield16 {

unsigned char * data_;

bitfield16(unsigned char * data) : data_(data) {}

#define BITFIELD16_VALUE_OFFSET 0
#define BITFIELD16_ALIGNMENT 2
#define BITFIELD16_SIZE 2


uint16_t value() const {
return *reinterpret_cast<uint16_t*>(&data_[BITFIELD16_VALUE_OFFSET ]);
}

};





struct bitfield32 {

unsigned char * data_;

bitfield32(unsigned char * data) : data_(data) {}

#define BITFIELD32_VALUE_OFFSET 0
#define BITFIELD32_ALIGNMENT 4
#define BITFIELD32_SIZE 4


uint32_t value() const {
return *reinterpret_cast<uint32_t*>(&data_[BITFIELD32_VALUE_OFFSET ]);
}

};





struct bitfield64 {

unsigned char * data_;

bitfield64(unsigned char * data) : data_(data) {}

#define BITFIELD64_VALUE_OFFSET 0
#define BITFIELD64_ALIGNMENT 8
#define BITFIELD64_SIZE 8


uint64_t value() const {
return *reinterpret_cast<uint64_t*>(&data_[BITFIELD64_VALUE_OFFSET ]);
}

};





struct sunssf {

unsigned char * data_;

sunssf(unsigned char * data) : data_(data) {}

#define SUNSSF_VALUE_OFFSET 0
#define SUNSSF_ALIGNMENT 2
#define SUNSSF_SIZE 2


uint16_t value() const {
return *reinterpret_cast<uint16_t*>(&data_[SUNSSF_VALUE_OFFSET ]);
}

};





struct acc16 {

unsigned char * data_;

acc16(unsigned char * data) : data_(data) {}

#define ACC16_VALUE_OFFSET 0
#define ACC16_ALIGNMENT 2
#define ACC16_SIZE 2


uint16_t value() const {
return *reinterpret_cast<uint16_t*>(&data_[ACC16_VALUE_OFFSET ]);
}

};





struct acc64 {

unsigned char * data_;

acc64(unsigned char * data) : data_(data) {}

#define ACC64_VALUE_OFFSET 0
#define ACC64_ALIGNMENT 8
#define ACC64_SIZE 8


uint64_t value() const {
return *reinterpret_cast<uint64_t*>(&data_[ACC64_VALUE_OFFSET ]);
}

};





struct eui48 {

unsigned char * data_;

eui48(unsigned char * data) : data_(data) {}

#define EUI48_VALUE0_OFFSET 0
#define EUI48_VALUE1_OFFSET 2
#define EUI48_VALUE2_OFFSET 4
#define EUI48_ALIGNMENT 2
#define EUI48_SIZE 6


uint16_t value0() const {
return *reinterpret_cast<uint16_t*>(&data_[EUI48_VALUE0_OFFSET ]);
}

uint16_t value1() const {
return *reinterpret_cast<uint16_t*>(&data_[EUI48_VALUE1_OFFSET ]);
}

uint16_t value2() const {
return *reinterpret_cast<uint16_t*>(&data_[EUI48_VALUE2_OFFSET ]);
}

};





struct ipaddr {

unsigned char * data_;

ipaddr(unsigned char * data) : data_(data) {}

#define IPADDR_VALUE0_OFFSET 0
#define IPADDR_VALUE1_OFFSET 2
#define IPADDR_VALUE2_OFFSET 4
#define IPADDR_VALUE3_OFFSET 6
#define IPADDR_ALIGNMENT 2
#define IPADDR_SIZE 8


uint16_t value0() const {
return *reinterpret_cast<uint16_t*>(&data_[IPADDR_VALUE0_OFFSET ]);
}

uint16_t value1() const {
return *reinterpret_cast<uint16_t*>(&data_[IPADDR_VALUE1_OFFSET ]);
}

uint16_t value2() const {
return *reinterpret_cast<uint16_t*>(&data_[IPADDR_VALUE2_OFFSET ]);
}

uint16_t value3() const {
return *reinterpret_cast<uint16_t*>(&data_[IPADDR_VALUE3_OFFSET ]);
}

};





struct ipv6addr {

unsigned char * data_;

ipv6addr(unsigned char * data) : data_(data) {}

#define IPV6ADDR_VALUE0_OFFSET 0
#define IPV6ADDR_VALUE1_OFFSET 2
#define IPV6ADDR_VALUE2_OFFSET 4
#define IPV6ADDR_VALUE3_OFFSET 6
#define IPV6ADDR_VALUE4_OFFSET 8
#define IPV6ADDR_VALUE5_OFFSET 10
#define IPV6ADDR_ALIGNMENT 2
#define IPV6ADDR_SIZE 12


uint16_t value0() const {
return *reinterpret_cast<uint16_t*>(&data_[IPV6ADDR_VALUE0_OFFSET ]);
}

uint16_t value1() const {
return *reinterpret_cast<uint16_t*>(&data_[IPV6ADDR_VALUE1_OFFSET ]);
}

uint16_t value2() const {
return *reinterpret_cast<uint16_t*>(&data_[IPV6ADDR_VALUE2_OFFSET ]);
}

uint16_t value3() const {
return *reinterpret_cast<uint16_t*>(&data_[IPV6ADDR_VALUE3_OFFSET ]);
}

uint16_t value4() const {
return *reinterpret_cast<uint16_t*>(&data_[IPV6ADDR_VALUE4_OFFSET ]);
}

uint16_t value5() const {
return *reinterpret_cast<uint16_t*>(&data_[IPV6ADDR_VALUE5_OFFSET ]);
}

};





struct SunspecPointData{

unsigned char * data_;

SunspecPointData(unsigned char * data) : data_(data) {}

#define SUNSPECPOINTDATA_TYPE_OFFSET 0
#define SUNSPECPOINTDATA_DATA_OFFSET 2
#define SUNSPECPOINTDATA_ALIGNMENT 2
#define SUNSPECPOINTDATA_SIZE 2


bool is_null() const {
return (type() == 0) or (*reinterpret_cast<uint16_t *>(&data_[SUNSPECPOINTDATA_DATA_OFFSET]) == 0);
}

unsigned char *raw_data() const {const int16_t offset = *reinterpret_cast<uint16_t *>(&data_[SUNSPECPOINTDATA_DATA_OFFSET]) + SUNSPECPOINTDATA_DATA_OFFSET;
return (&data_[offset]);
}
SunspecPointData_enum type() const {
return *reinterpret_cast<SunspecPointData_enum *>(&data_[SUNSPECPOINTDATA_TYPE_OFFSET]);
}

Offset<uint16_t> data_as_uint16() const {
return type() == SunspecPointData_enum_uint16 ? Offset<uint16_t>(&data_[SUNSPECPOINTDATA_DATA_OFFSET]) : 0;
}

Offset<int16_t> data_as_int16() const {
return type() == SunspecPointData_enum_int16 ? Offset<int16_t>(&data_[SUNSPECPOINTDATA_DATA_OFFSET]) : 0;
}

Offset<uint32_t> data_as_uint32() const {
return type() == SunspecPointData_enum_uint32 ? Offset<uint32_t>(&data_[SUNSPECPOINTDATA_DATA_OFFSET]) : 0;
}

Offset<int32_t> data_as_int32() const {
return type() == SunspecPointData_enum_int32 ? Offset<int32_t>(&data_[SUNSPECPOINTDATA_DATA_OFFSET]) : 0;
}

Offset<uint64_t> data_as_uint64() const {
return type() == SunspecPointData_enum_uint64 ? Offset<uint64_t>(&data_[SUNSPECPOINTDATA_DATA_OFFSET]) : 0;
}

Offset<int64_t> data_as_int64() const {
return type() == SunspecPointData_enum_int64 ? Offset<int64_t>(&data_[SUNSPECPOINTDATA_DATA_OFFSET]) : 0;
}

Offset<float> data_as_float32() const {
return type() == SunspecPointData_enum_float32 ? Offset<float>(&data_[SUNSPECPOINTDATA_DATA_OFFSET]) : 0;
}

Offset<double> data_as_float64() const {
return type() == SunspecPointData_enum_float64 ? Offset<double>(&data_[SUNSPECPOINTDATA_DATA_OFFSET]) : 0;
}

Offset<String> data_as_string() const {
return type() == SunspecPointData_enum_string ? Offset<String>(&data_[SUNSPECPOINTDATA_DATA_OFFSET]) : 0;
}

Offset<pad> data_as_pad() const {
return type() == SunspecPointData_enum_pad ? Offset<pad>(&data_[SUNSPECPOINTDATA_DATA_OFFSET]) : 0;
}

Offset<enum16> data_as_enum16() const {
return type() == SunspecPointData_enum_enum16 ? Offset<enum16>(&data_[SUNSPECPOINTDATA_DATA_OFFSET]) : 0;
}

Offset<enum32> data_as_enum32() const {
return type() == SunspecPointData_enum_enum32 ? Offset<enum32>(&data_[SUNSPECPOINTDATA_DATA_OFFSET]) : 0;
}

Offset<enum64> data_as_enum64() const {
return type() == SunspecPointData_enum_enum64 ? Offset<enum64>(&data_[SUNSPECPOINTDATA_DATA_OFFSET]) : 0;
}

Offset<bitfield16> data_as_bitfield16() const {
return type() == SunspecPointData_enum_bitfield16 ? Offset<bitfield16>(&data_[SUNSPECPOINTDATA_DATA_OFFSET]) : 0;
}

Offset<bitfield32> data_as_bitfield32() const {
return type() == SunspecPointData_enum_bitfield32 ? Offset<bitfield32>(&data_[SUNSPECPOINTDATA_DATA_OFFSET]) : 0;
}

Offset<bitfield64> data_as_bitfield64() const {
return type() == SunspecPointData_enum_bitfield64 ? Offset<bitfield64>(&data_[SUNSPECPOINTDATA_DATA_OFFSET]) : 0;
}

Offset<sunssf> data_as_sunssf() const {
return type() == SunspecPointData_enum_sunssf ? Offset<sunssf>(&data_[SUNSPECPOINTDATA_DATA_OFFSET]) : 0;
}

Offset<acc16> data_as_acc16() const {
return type() == SunspecPointData_enum_acc16 ? Offset<acc16>(&data_[SUNSPECPOINTDATA_DATA_OFFSET]) : 0;
}

Offset<acc32> data_as_acc32() const {
return type() == SunspecPointData_enum_acc32 ? Offset<acc32>(&data_[SUNSPECPOINTDATA_DATA_OFFSET]) : 0;
}

Offset<acc64> data_as_acc64() const {
return type() == SunspecPointData_enum_acc64 ? Offset<acc64>(&data_[SUNSPECPOINTDATA_DATA_OFFSET]) : 0;
}

Offset<eui48> data_as_eui48() const {
return type() == SunspecPointData_enum_eui48 ? Offset<eui48>(&data_[SUNSPECPOINTDATA_DATA_OFFSET]) : 0;
}

Offset<ipaddr> data_as_ipaddr() const {
return type() == SunspecPointData_enum_ipaddr ? Offset<ipaddr>(&data_[SUNSPECPOINTDATA_DATA_OFFSET]) : 0;
}

Offset<ipv6addr> data_as_ipv6addr() const {
return type() == SunspecPointData_enum_ipv6addr ? Offset<ipv6addr>(&data_[SUNSPECPOINTDATA_DATA_OFFSET]) : 0;
}

};













enum SunspecPointAccessType : uint8_t {

SunspecPointAccessType_kR,
SunspecPointAccessType_kRW,
};

const char * SunspecPointAccessType_to_string(SunspecPointAccessType value){
switch (value){
case SunspecPointAccessType_kR:
return "SunspecPointAccessType_kR";
case SunspecPointAccessType_kRW:
return "SunspecPointAccessType_kRW";
default:
return NULL;
}
}
enum SunspecPointMandatoryType : uint8_t {

SunspecPointMandatoryType_kM,
SunspecPointMandatoryType_kO,
};

const char * SunspecPointMandatoryType_to_string(SunspecPointMandatoryType value){
switch (value){
case SunspecPointMandatoryType_kM:
return "SunspecPointMandatoryType_kM";
case SunspecPointMandatoryType_kO:
return "SunspecPointMandatoryType_kO";
default:
return NULL;
}
}


struct SunspecPointDef {

unsigned char * data_;

SunspecPointDef(unsigned char * data) : data_(data) {}

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
#define SUNSPECPOINTDEF_ALIGNMENT 2
#define SUNSPECPOINTDEF_SIZE 18


Offset<String> id() const {
const int16_t offset = SUNSPECPOINTDEF_ID_OFFSET ;
return Offset<String>(&data_[offset]);
}

Offset<String> sf_id() const {
const int16_t offset = SUNSPECPOINTDEF_SF_ID_OFFSET ;
return Offset<String>(&data_[offset]);
}

Offset<String> units() const {
const int16_t offset = SUNSPECPOINTDEF_UNITS_OFFSET ;
return Offset<String>(&data_[offset]);
}

Offset<String> label() const {
const int16_t offset = SUNSPECPOINTDEF_LABEL_OFFSET ;
return Offset<String>(&data_[offset]);
}

SunspecPointData_enum data_type() const {
return *reinterpret_cast<SunspecPointData_enum*>(&data_[SUNSPECPOINTDEF_DATA_TYPE_OFFSET ]);
}

SunspecPointData data() const {
const int16_t offset = SUNSPECPOINTDEF_DATA_OFFSET - 2 ;
return SunspecPointData(&data_[offset]);
}

uint8_t count() const {
return *reinterpret_cast<uint8_t*>(&data_[SUNSPECPOINTDEF_COUNT_OFFSET ]);
}

uint8_t size() const {
return *reinterpret_cast<uint8_t*>(&data_[SUNSPECPOINTDEF_SIZE_OFFSET ]);
}

int8_t sf() const {
return *reinterpret_cast<int8_t*>(&data_[SUNSPECPOINTDEF_SF_OFFSET ]);
}

SunspecPointAccessType access() const {
return *reinterpret_cast<SunspecPointAccessType*>(&data_[SUNSPECPOINTDEF_ACCESS_OFFSET ]);
}

SunspecPointMandatoryType mandatory() const {
return *reinterpret_cast<SunspecPointMandatoryType*>(&data_[SUNSPECPOINTDEF_MANDATORY_OFFSET ]);
}

};



enum SunspecGroupType : uint8_t {

SunspecGroupType_kGroup,
SunspecGroupType_kSync,
};

const char * SunspecGroupType_to_string(SunspecGroupType value){
switch (value){
case SunspecGroupType_kGroup:
return "SunspecGroupType_kGroup";
case SunspecGroupType_kSync:
return "SunspecGroupType_kSync";
default:
return NULL;
}
}


struct SunspecGroupPointDef {

unsigned char * data_;

SunspecGroupPointDef(unsigned char * data) : data_(data) {}

#define SUNSPECGROUPPOINTDEF_ID_OFFSET 0
#define SUNSPECGROUPPOINTDEF_COUNT_POINT_ID_OFFSET 2
#define SUNSPECGROUPPOINTDEF_POINTS_OFFSET 4
#define SUNSPECGROUPPOINTDEF_GROUPS_OFFSET 6
#define SUNSPECGROUPPOINTDEF_LABEL_OFFSET 8
#define SUNSPECGROUPPOINTDEF_COUNT_OFFSET 10
#define SUNSPECGROUPPOINTDEF_TYPE_OFFSET 11
#define SUNSPECGROUPPOINTDEF_ALIGNMENT 2
#define SUNSPECGROUPPOINTDEF_SIZE 12


Offset<String> id() const {
const int16_t offset = SUNSPECGROUPPOINTDEF_ID_OFFSET ;
return Offset<String>(&data_[offset]);
}

Offset<String> count_point_id() const {
const int16_t offset = SUNSPECGROUPPOINTDEF_COUNT_POINT_ID_OFFSET ;
return Offset<String>(&data_[offset]);
}

Vector<Offset<SunspecPointDef>> points() const {
const int16_t offset = SUNSPECGROUPPOINTDEF_POINTS_OFFSET ;
return Vector<Offset<SunspecPointDef>>(&data_[offset]);
}

Vector<Offset<SunspecGroupPointDef>> groups() const {
const int16_t offset = SUNSPECGROUPPOINTDEF_GROUPS_OFFSET ;
return Vector<Offset<SunspecGroupPointDef>>(&data_[offset]);
}

Offset<String> label() const {
const int16_t offset = SUNSPECGROUPPOINTDEF_LABEL_OFFSET ;
return Offset<String>(&data_[offset]);
}

uint8_t count() const {
return *reinterpret_cast<uint8_t*>(&data_[SUNSPECGROUPPOINTDEF_COUNT_OFFSET ]);
}

SunspecGroupType type() const {
return *reinterpret_cast<SunspecGroupType*>(&data_[SUNSPECGROUPPOINTDEF_TYPE_OFFSET ]);
}

};





struct SunspecModelDef {

unsigned char * data_;

SunspecModelDef(unsigned char * data) : data_(data) {}

#define SUNSPECMODELDEF_ID_OFFSET 0
#define SUNSPECMODELDEF_GROUP_OFFSET 2
#define SUNSPECMODELDEF_ALIGNMENT 2
#define SUNSPECMODELDEF_SIZE 4


uint16_t id() const {
return *reinterpret_cast<uint16_t*>(&data_[SUNSPECMODELDEF_ID_OFFSET ]);
}

Offset<SunspecGroupPointDef> group() const {const int16_t offset =SUNSPECMODELDEF_GROUP_OFFSET ;return Offset<SunspecGroupPointDef>(&data_[offset]);}

};

































struct SunspecModelDefRoot {

unsigned char * data_;

SunspecModelDefRoot(unsigned char * data) : data_(data) {}

#define SUNSPECMODELDEF_ID_OFFSET 0
#define SUNSPECMODELDEF_GROUP_OFFSET 2
#define SUNSPECMODELDEF_ALIGNMENT 2
#define SUNSPECMODELDEF_SIZE 4


uint16_t id() const {
return *reinterpret_cast<uint16_t*>(&data_[SUNSPECMODELDEF_ID_OFFSET + 2* OFFSET_SIZE]);
}

Offset<SunspecGroupPointDef> group() const {const int16_t offset =SUNSPECMODELDEF_GROUP_OFFSET + 2* OFFSET_SIZE;return Offset<SunspecGroupPointDef>(&data_[offset]);}

};





size_t get_padding_size(size_t offset, uint16_t alignment)
{
    return (alignment - (offset % alignment)) % alignment;
}

template <typename T>
struct SerializeOffset
{
    uint16_t offset = 0;

    template<typename U = void>
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

    void init(uint16_t buffer_size)
    {
        _buffer = reinterpret_cast<unsigned char *>(malloc(buffer_size));
        _buffer_size = buffer_size;
        *reinterpret_cast<uint16_t *>(&_buffer[OFFSET_SIZE]) = VERSION;

        _tail_offset = get_padding_size(OFFSET_SIZE * 2, PACKET_ALIGNMENT) + OFFSET_SIZE * 2 + PACKET_SIZE;
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
            *reinterpret_cast<uint16_t*>(&_buffer[_tail_offset]) = data_array[i].offset - _tail_offset;
            _tail_offset += OFFSET_SIZE;
        }
        return data_array_offset;
    }
};




struct acc32Struct {
uint32_t value;
};




struct acc64Struct {
uint64_t value;
};




struct padStruct {
uint16_t value;
};




struct eui48Struct {
uint16_t value0;
uint16_t value1;
uint16_t value2;
};




struct ipaddrStruct {
uint16_t value0;
uint16_t value1;
uint16_t value2;
uint16_t value3;
};




struct ipv6addrStruct {
uint16_t value0;
uint16_t value1;
uint16_t value2;
uint16_t value3;
uint16_t value4;
uint16_t value5;
};




struct SunspecPointData_enumStruct {
};


struct SunspecPointDataStruct {
};


struct SunspecPointAccessTypeStruct {
};


struct SunspecPointMandatoryTypeStruct {
};


struct SunspecPointDefStruct {
SerializeOffset<String> id;
SerializeOffset<String> sf_id;
SerializeOffset<String> units;
SerializeOffset<String> label;
SunspecPointData_enum data_type;
SerializeOffset<void> data;
uint8_t count;
uint8_t size;
int8_t sf;
SunspecPointAccessType access;
SunspecPointMandatoryType mandatory;
};


struct SunspecGroupTypeStruct {
};


struct SunspecGroupPointDefStruct {
SerializeOffset<String> id;
SerializeOffset<String> count_point_id;
SerializeOffset<Vector<SunspecPointDef>> points;
SerializeOffset<Vector<SunspecGroupPointDef>> groups;
SerializeOffset<String> label;
uint8_t count;
SunspecGroupType type;
};


struct SunspecModelDefStruct {
uint16_t id;
SerializeOffset<SunspecGroupPointDef> group;
};




struct enum16Struct {
uint16_t value;
};




struct enum32Struct {
uint32_t value;
};




struct enum64Struct {
uint64_t value;
};




struct bitfield16Struct {
uint16_t value;
};






struct bitfield32Struct {
uint32_t value;
};




struct bitfield64Struct {
uint64_t value;
};






struct sunssfStruct {
uint16_t value;
};




struct acc16Struct {
uint16_t value;
};




SerializeOffset<acc32> serialize_acc32(Serializer *const serializer,
 const uint32_t value){
SerializeOffset<acc32> acc32_offset;
serializer->_tail_offset += get_padding_size(serializer->_tail_offset, ACC32_ALIGNMENT);
serializer->make_buffer_adequate();
acc32_offset.offset = serializer->_tail_offset;

*reinterpret_cast<uint32_t *>(&(serializer->_buffer[serializer->_tail_offset  + ACC32_VALUE_OFFSET])) = value;
serializer->_tail_offset += ACC32_SIZE;
return acc32_offset;
}

SerializeOffset<SunspecPointData> serialize_sunspecpointdata(Serializer *const serializer){
SerializeOffset<SunspecPointData> sunspecpointdata_offset;
serializer->_tail_offset += get_padding_size(serializer->_tail_offset, SUNSPECPOINTDATA_ALIGNMENT);
serializer->make_buffer_adequate();
sunspecpointdata_offset.offset = serializer->_tail_offset;

serializer->_tail_offset += SUNSPECPOINTDATA_SIZE;
return sunspecpointdata_offset;
}

SerializeOffset<acc64> serialize_acc64(Serializer *const serializer,
 const uint64_t value){
SerializeOffset<acc64> acc64_offset;
serializer->_tail_offset += get_padding_size(serializer->_tail_offset, ACC64_ALIGNMENT);
serializer->make_buffer_adequate();
acc64_offset.offset = serializer->_tail_offset;

*reinterpret_cast<uint64_t *>(&(serializer->_buffer[serializer->_tail_offset  + ACC64_VALUE_OFFSET])) = value;
serializer->_tail_offset += ACC64_SIZE;
return acc64_offset;
}

SerializeOffset<pad> serialize_pad(Serializer *const serializer,
 const uint16_t value){
SerializeOffset<pad> pad_offset;
serializer->_tail_offset += get_padding_size(serializer->_tail_offset, PAD_ALIGNMENT);
serializer->make_buffer_adequate();
pad_offset.offset = serializer->_tail_offset;

*reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset  + PAD_VALUE_OFFSET])) = value;
serializer->_tail_offset += PAD_SIZE;
return pad_offset;
}

SerializeOffset<eui48> serialize_eui48(Serializer *const serializer,
 const uint16_t value0,
 const uint16_t value1,
 const uint16_t value2){
SerializeOffset<eui48> eui48_offset;
serializer->_tail_offset += get_padding_size(serializer->_tail_offset, EUI48_ALIGNMENT);
serializer->make_buffer_adequate();
eui48_offset.offset = serializer->_tail_offset;

*reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset  + EUI48_VALUE0_OFFSET])) = value0;
*reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset  + EUI48_VALUE1_OFFSET])) = value1;
*reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset  + EUI48_VALUE2_OFFSET])) = value2;
serializer->_tail_offset += EUI48_SIZE;
return eui48_offset;
}

SerializeOffset<ipaddr> serialize_ipaddr(Serializer *const serializer,
 const uint16_t value0,
 const uint16_t value1,
 const uint16_t value2,
 const uint16_t value3){
SerializeOffset<ipaddr> ipaddr_offset;
serializer->_tail_offset += get_padding_size(serializer->_tail_offset, IPADDR_ALIGNMENT);
serializer->make_buffer_adequate();
ipaddr_offset.offset = serializer->_tail_offset;

*reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset  + IPADDR_VALUE0_OFFSET])) = value0;
*reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset  + IPADDR_VALUE1_OFFSET])) = value1;
*reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset  + IPADDR_VALUE2_OFFSET])) = value2;
*reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset  + IPADDR_VALUE3_OFFSET])) = value3;
serializer->_tail_offset += IPADDR_SIZE;
return ipaddr_offset;
}

SerializeOffset<ipv6addr> serialize_ipv6addr(Serializer *const serializer,
 const uint16_t value0,
 const uint16_t value1,
 const uint16_t value2,
 const uint16_t value3,
 const uint16_t value4,
 const uint16_t value5){
SerializeOffset<ipv6addr> ipv6addr_offset;
serializer->_tail_offset += get_padding_size(serializer->_tail_offset, IPV6ADDR_ALIGNMENT);
serializer->make_buffer_adequate();
ipv6addr_offset.offset = serializer->_tail_offset;

*reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset  + IPV6ADDR_VALUE0_OFFSET])) = value0;
*reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset  + IPV6ADDR_VALUE1_OFFSET])) = value1;
*reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset  + IPV6ADDR_VALUE2_OFFSET])) = value2;
*reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset  + IPV6ADDR_VALUE3_OFFSET])) = value3;
*reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset  + IPV6ADDR_VALUE4_OFFSET])) = value4;
*reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset  + IPV6ADDR_VALUE5_OFFSET])) = value5;
serializer->_tail_offset += IPV6ADDR_SIZE;
return ipv6addr_offset;
}

SerializeOffset<SunspecModelDef> serialize_sunspecmodeldef(Serializer *const serializer,
 const uint16_t id,
 const SerializeOffset<SunspecGroupPointDef> group){
SerializeOffset<SunspecModelDef> sunspecmodeldef_offset;
serializer->_tail_offset += get_padding_size(serializer->_tail_offset, SUNSPECMODELDEF_ALIGNMENT);
serializer->make_buffer_adequate();
sunspecmodeldef_offset.offset = serializer->_tail_offset;

*reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset  + SUNSPECMODELDEF_ID_OFFSET])) = id;
*reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset  + SUNSPECMODELDEF_GROUP_OFFSET])) = group.offset - (serializer->_tail_offset  +SUNSPECMODELDEF_GROUP_OFFSET);
serializer->_tail_offset += SUNSPECMODELDEF_SIZE;
return sunspecmodeldef_offset;
}

SerializeOffset<enum16> serialize_enum16(Serializer *const serializer,
 const uint16_t value){
SerializeOffset<enum16> enum16_offset;
serializer->_tail_offset += get_padding_size(serializer->_tail_offset, ENUM16_ALIGNMENT);
serializer->make_buffer_adequate();
enum16_offset.offset = serializer->_tail_offset;

*reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset  + ENUM16_VALUE_OFFSET])) = value;
serializer->_tail_offset += ENUM16_SIZE;
return enum16_offset;
}

SerializeOffset<enum32> serialize_enum32(Serializer *const serializer,
 const uint32_t value){
SerializeOffset<enum32> enum32_offset;
serializer->_tail_offset += get_padding_size(serializer->_tail_offset, ENUM32_ALIGNMENT);
serializer->make_buffer_adequate();
enum32_offset.offset = serializer->_tail_offset;

*reinterpret_cast<uint32_t *>(&(serializer->_buffer[serializer->_tail_offset  + ENUM32_VALUE_OFFSET])) = value;
serializer->_tail_offset += ENUM32_SIZE;
return enum32_offset;
}

SerializeOffset<enum64> serialize_enum64(Serializer *const serializer,
 const uint64_t value){
SerializeOffset<enum64> enum64_offset;
serializer->_tail_offset += get_padding_size(serializer->_tail_offset, ENUM64_ALIGNMENT);
serializer->make_buffer_adequate();
enum64_offset.offset = serializer->_tail_offset;

*reinterpret_cast<uint64_t *>(&(serializer->_buffer[serializer->_tail_offset  + ENUM64_VALUE_OFFSET])) = value;
serializer->_tail_offset += ENUM64_SIZE;
return enum64_offset;
}

SerializeOffset<bitfield16> serialize_bitfield16(Serializer *const serializer,
 const uint16_t value){
SerializeOffset<bitfield16> bitfield16_offset;
serializer->_tail_offset += get_padding_size(serializer->_tail_offset, BITFIELD16_ALIGNMENT);
serializer->make_buffer_adequate();
bitfield16_offset.offset = serializer->_tail_offset;

*reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset  + BITFIELD16_VALUE_OFFSET])) = value;
serializer->_tail_offset += BITFIELD16_SIZE;
return bitfield16_offset;
}

SerializeOffset<SunspecGroupPointDef> serialize_sunspecgrouppointdef(Serializer *const serializer,
 const SerializeOffset<String> id,
 const SerializeOffset<String> count_point_id,
 const SerializeOffset<Vector<SerializeOffset<SunspecPointDef>>> points,
 const SerializeOffset<Vector<SerializeOffset<SunspecGroupPointDef>>> groups,
 const SerializeOffset<String> label,
 const uint8_t count,
 const SunspecGroupType type){
SerializeOffset<SunspecGroupPointDef> sunspecgrouppointdef_offset;
serializer->_tail_offset += get_padding_size(serializer->_tail_offset, SUNSPECGROUPPOINTDEF_ALIGNMENT);
serializer->make_buffer_adequate();
sunspecgrouppointdef_offset.offset = serializer->_tail_offset;

*reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset  + SUNSPECGROUPPOINTDEF_ID_OFFSET])) = id.offset - (serializer->_tail_offset  +SUNSPECGROUPPOINTDEF_ID_OFFSET);
*reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset  + SUNSPECGROUPPOINTDEF_COUNT_POINT_ID_OFFSET])) = count_point_id.offset - (serializer->_tail_offset  +SUNSPECGROUPPOINTDEF_COUNT_POINT_ID_OFFSET);
*reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset  + SUNSPECGROUPPOINTDEF_POINTS_OFFSET])) = points.offset - (serializer->_tail_offset  +SUNSPECGROUPPOINTDEF_POINTS_OFFSET);
*reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset  + SUNSPECGROUPPOINTDEF_GROUPS_OFFSET])) = groups.offset - (serializer->_tail_offset  +SUNSPECGROUPPOINTDEF_GROUPS_OFFSET);
*reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset  + SUNSPECGROUPPOINTDEF_LABEL_OFFSET])) = label.offset - (serializer->_tail_offset  +SUNSPECGROUPPOINTDEF_LABEL_OFFSET);
*reinterpret_cast<uint8_t *>(&(serializer->_buffer[serializer->_tail_offset  + SUNSPECGROUPPOINTDEF_COUNT_OFFSET])) = count;
*reinterpret_cast<SunspecGroupType *>(&(serializer->_buffer[serializer->_tail_offset  + SUNSPECGROUPPOINTDEF_TYPE_OFFSET])) = type;
serializer->_tail_offset += SUNSPECGROUPPOINTDEF_SIZE;
return sunspecgrouppointdef_offset;
}

SerializeOffset<bitfield32> serialize_bitfield32(Serializer *const serializer,
 const uint32_t value){
SerializeOffset<bitfield32> bitfield32_offset;
serializer->_tail_offset += get_padding_size(serializer->_tail_offset, BITFIELD32_ALIGNMENT);
serializer->make_buffer_adequate();
bitfield32_offset.offset = serializer->_tail_offset;

*reinterpret_cast<uint32_t *>(&(serializer->_buffer[serializer->_tail_offset  + BITFIELD32_VALUE_OFFSET])) = value;
serializer->_tail_offset += BITFIELD32_SIZE;
return bitfield32_offset;
}

SerializeOffset<bitfield64> serialize_bitfield64(Serializer *const serializer,
 const uint64_t value){
SerializeOffset<bitfield64> bitfield64_offset;
serializer->_tail_offset += get_padding_size(serializer->_tail_offset, BITFIELD64_ALIGNMENT);
serializer->make_buffer_adequate();
bitfield64_offset.offset = serializer->_tail_offset;

*reinterpret_cast<uint64_t *>(&(serializer->_buffer[serializer->_tail_offset  + BITFIELD64_VALUE_OFFSET])) = value;
serializer->_tail_offset += BITFIELD64_SIZE;
return bitfield64_offset;
}

SerializeOffset<SunspecPointDef> serialize_sunspecpointdef(Serializer *const serializer,
 const SerializeOffset<String> id,
 const SerializeOffset<String> sf_id,
 const SerializeOffset<String> units,
 const SerializeOffset<String> label,
 const SunspecPointData_enum data_type,
 const SerializeOffset<void> data,
 const uint8_t count,
 const uint8_t size,
 const int8_t sf,
 const SunspecPointAccessType access,
 const SunspecPointMandatoryType mandatory){
SerializeOffset<SunspecPointDef> sunspecpointdef_offset;
serializer->_tail_offset += get_padding_size(serializer->_tail_offset, SUNSPECPOINTDEF_ALIGNMENT);
serializer->make_buffer_adequate();
sunspecpointdef_offset.offset = serializer->_tail_offset;

*reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset  + SUNSPECPOINTDEF_ID_OFFSET])) = id.offset - (serializer->_tail_offset  +SUNSPECPOINTDEF_ID_OFFSET);
*reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset  + SUNSPECPOINTDEF_SF_ID_OFFSET])) = sf_id.offset - (serializer->_tail_offset  +SUNSPECPOINTDEF_SF_ID_OFFSET);
*reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset  + SUNSPECPOINTDEF_UNITS_OFFSET])) = units.offset - (serializer->_tail_offset  +SUNSPECPOINTDEF_UNITS_OFFSET);
*reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset  + SUNSPECPOINTDEF_LABEL_OFFSET])) = label.offset - (serializer->_tail_offset  +SUNSPECPOINTDEF_LABEL_OFFSET);
*reinterpret_cast<SunspecPointData_enum *>(&(serializer->_buffer[serializer->_tail_offset  + SUNSPECPOINTDEF_DATA_TYPE_OFFSET])) = data_type;
*reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset  + SUNSPECPOINTDEF_DATA_OFFSET])) = data.offset - (serializer->_tail_offset  +SUNSPECPOINTDEF_DATA_OFFSET);
*reinterpret_cast<uint8_t *>(&(serializer->_buffer[serializer->_tail_offset  + SUNSPECPOINTDEF_COUNT_OFFSET])) = count;
*reinterpret_cast<uint8_t *>(&(serializer->_buffer[serializer->_tail_offset  + SUNSPECPOINTDEF_SIZE_OFFSET])) = size;
*reinterpret_cast<int8_t *>(&(serializer->_buffer[serializer->_tail_offset  + SUNSPECPOINTDEF_SF_OFFSET])) = sf;
*reinterpret_cast<SunspecPointAccessType *>(&(serializer->_buffer[serializer->_tail_offset  + SUNSPECPOINTDEF_ACCESS_OFFSET])) = access;
*reinterpret_cast<SunspecPointMandatoryType *>(&(serializer->_buffer[serializer->_tail_offset  + SUNSPECPOINTDEF_MANDATORY_OFFSET])) = mandatory;
serializer->_tail_offset += SUNSPECPOINTDEF_SIZE;
return sunspecpointdef_offset;
}

SerializeOffset<sunssf> serialize_sunssf(Serializer *const serializer,
 const uint16_t value){
SerializeOffset<sunssf> sunssf_offset;
serializer->_tail_offset += get_padding_size(serializer->_tail_offset, SUNSSF_ALIGNMENT);
serializer->make_buffer_adequate();
sunssf_offset.offset = serializer->_tail_offset;

*reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset  + SUNSSF_VALUE_OFFSET])) = value;
serializer->_tail_offset += SUNSSF_SIZE;
return sunssf_offset;
}

SerializeOffset<acc16> serialize_acc16(Serializer *const serializer,
 const uint16_t value){
SerializeOffset<acc16> acc16_offset;
serializer->_tail_offset += get_padding_size(serializer->_tail_offset, ACC16_ALIGNMENT);
serializer->make_buffer_adequate();
acc16_offset.offset = serializer->_tail_offset;

*reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset  + ACC16_VALUE_OFFSET])) = value;
serializer->_tail_offset += ACC16_SIZE;
return acc16_offset;
}



SerializeOffset<Vector<acc32Struct>> serialize_vector_acc32_struct(Serializer *const serializer, std::vector<acc32Struct> data_array){
SerializeOffset<Vector<acc32Struct>> data_array_offset;
uint16_t len = data_array.size();
serializer->_tail_offset += get_padding_size(serializer->_tail_offset, OFFSET_SIZE);
serializer->make_buffer_adequate();
data_array_offset.offset = serializer->_tail_offset;
*reinterpret_cast<uint16_t *>(&serializer->_buffer[serializer->_tail_offset]) = len;
serializer->_tail_offset += OFFSET_SIZE;serializer->_tail_offset += get_padding_size(serializer->_tail_offset, ACC32_ALIGNMENT);for (uint16_t i = 0; i < len; i++){*reinterpret_cast<uint32_t *>(&(serializer->_buffer[serializer->_tail_offset  + (ACC32_SIZE * i) + ACC32_VALUE_OFFSET])) = data_array[i].value;
serializer->_tail_offset += (ACC32_SIZE * len);
}return data_array_offset;}

SerializeOffset<Vector<SunspecPointDataStruct>> serialize_vector_sunspecpointdata_struct(Serializer *const serializer, std::vector<SunspecPointDataStruct> data_array){
SerializeOffset<Vector<SunspecPointDataStruct>> data_array_offset;
uint16_t len = data_array.size();
serializer->_tail_offset += get_padding_size(serializer->_tail_offset, OFFSET_SIZE);
serializer->make_buffer_adequate();
data_array_offset.offset = serializer->_tail_offset;
*reinterpret_cast<uint16_t *>(&serializer->_buffer[serializer->_tail_offset]) = len;
serializer->_tail_offset += OFFSET_SIZE;serializer->_tail_offset += get_padding_size(serializer->_tail_offset, SUNSPECPOINTDATA_ALIGNMENT);for (uint16_t i = 0; i < len; i++){serializer->_tail_offset += (SUNSPECPOINTDATA_SIZE * len);
}return data_array_offset;}

SerializeOffset<Vector<acc64Struct>> serialize_vector_acc64_struct(Serializer *const serializer, std::vector<acc64Struct> data_array){
SerializeOffset<Vector<acc64Struct>> data_array_offset;
uint16_t len = data_array.size();
serializer->_tail_offset += get_padding_size(serializer->_tail_offset, OFFSET_SIZE);
serializer->make_buffer_adequate();
data_array_offset.offset = serializer->_tail_offset;
*reinterpret_cast<uint16_t *>(&serializer->_buffer[serializer->_tail_offset]) = len;
serializer->_tail_offset += OFFSET_SIZE;serializer->_tail_offset += get_padding_size(serializer->_tail_offset, ACC64_ALIGNMENT);for (uint16_t i = 0; i < len; i++){*reinterpret_cast<uint64_t *>(&(serializer->_buffer[serializer->_tail_offset  + (ACC64_SIZE * i) + ACC64_VALUE_OFFSET])) = data_array[i].value;
serializer->_tail_offset += (ACC64_SIZE * len);
}return data_array_offset;}

SerializeOffset<Vector<padStruct>> serialize_vector_pad_struct(Serializer *const serializer, std::vector<padStruct> data_array){
SerializeOffset<Vector<padStruct>> data_array_offset;
uint16_t len = data_array.size();
serializer->_tail_offset += get_padding_size(serializer->_tail_offset, OFFSET_SIZE);
serializer->make_buffer_adequate();
data_array_offset.offset = serializer->_tail_offset;
*reinterpret_cast<uint16_t *>(&serializer->_buffer[serializer->_tail_offset]) = len;
serializer->_tail_offset += OFFSET_SIZE;serializer->_tail_offset += get_padding_size(serializer->_tail_offset, PAD_ALIGNMENT);for (uint16_t i = 0; i < len; i++){*reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset  + (PAD_SIZE * i) + PAD_VALUE_OFFSET])) = data_array[i].value;
serializer->_tail_offset += (PAD_SIZE * len);
}return data_array_offset;}

SerializeOffset<Vector<eui48Struct>> serialize_vector_eui48_struct(Serializer *const serializer, std::vector<eui48Struct> data_array){
SerializeOffset<Vector<eui48Struct>> data_array_offset;
uint16_t len = data_array.size();
serializer->_tail_offset += get_padding_size(serializer->_tail_offset, OFFSET_SIZE);
serializer->make_buffer_adequate();
data_array_offset.offset = serializer->_tail_offset;
*reinterpret_cast<uint16_t *>(&serializer->_buffer[serializer->_tail_offset]) = len;
serializer->_tail_offset += OFFSET_SIZE;serializer->_tail_offset += get_padding_size(serializer->_tail_offset, EUI48_ALIGNMENT);for (uint16_t i = 0; i < len; i++){*reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset  + (EUI48_SIZE * i) + EUI48_VALUE0_OFFSET])) = data_array[i].value0;
*reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset  + (EUI48_SIZE * i) + EUI48_VALUE1_OFFSET])) = data_array[i].value1;
*reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset  + (EUI48_SIZE * i) + EUI48_VALUE2_OFFSET])) = data_array[i].value2;
serializer->_tail_offset += (EUI48_SIZE * len);
}return data_array_offset;}

SerializeOffset<Vector<ipaddrStruct>> serialize_vector_ipaddr_struct(Serializer *const serializer, std::vector<ipaddrStruct> data_array){
SerializeOffset<Vector<ipaddrStruct>> data_array_offset;
uint16_t len = data_array.size();
serializer->_tail_offset += get_padding_size(serializer->_tail_offset, OFFSET_SIZE);
serializer->make_buffer_adequate();
data_array_offset.offset = serializer->_tail_offset;
*reinterpret_cast<uint16_t *>(&serializer->_buffer[serializer->_tail_offset]) = len;
serializer->_tail_offset += OFFSET_SIZE;serializer->_tail_offset += get_padding_size(serializer->_tail_offset, IPADDR_ALIGNMENT);for (uint16_t i = 0; i < len; i++){*reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset  + (IPADDR_SIZE * i) + IPADDR_VALUE0_OFFSET])) = data_array[i].value0;
*reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset  + (IPADDR_SIZE * i) + IPADDR_VALUE1_OFFSET])) = data_array[i].value1;
*reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset  + (IPADDR_SIZE * i) + IPADDR_VALUE2_OFFSET])) = data_array[i].value2;
*reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset  + (IPADDR_SIZE * i) + IPADDR_VALUE3_OFFSET])) = data_array[i].value3;
serializer->_tail_offset += (IPADDR_SIZE * len);
}return data_array_offset;}

SerializeOffset<Vector<ipv6addrStruct>> serialize_vector_ipv6addr_struct(Serializer *const serializer, std::vector<ipv6addrStruct> data_array){
SerializeOffset<Vector<ipv6addrStruct>> data_array_offset;
uint16_t len = data_array.size();
serializer->_tail_offset += get_padding_size(serializer->_tail_offset, OFFSET_SIZE);
serializer->make_buffer_adequate();
data_array_offset.offset = serializer->_tail_offset;
*reinterpret_cast<uint16_t *>(&serializer->_buffer[serializer->_tail_offset]) = len;
serializer->_tail_offset += OFFSET_SIZE;serializer->_tail_offset += get_padding_size(serializer->_tail_offset, IPV6ADDR_ALIGNMENT);for (uint16_t i = 0; i < len; i++){*reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset  + (IPV6ADDR_SIZE * i) + IPV6ADDR_VALUE0_OFFSET])) = data_array[i].value0;
*reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset  + (IPV6ADDR_SIZE * i) + IPV6ADDR_VALUE1_OFFSET])) = data_array[i].value1;
*reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset  + (IPV6ADDR_SIZE * i) + IPV6ADDR_VALUE2_OFFSET])) = data_array[i].value2;
*reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset  + (IPV6ADDR_SIZE * i) + IPV6ADDR_VALUE3_OFFSET])) = data_array[i].value3;
*reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset  + (IPV6ADDR_SIZE * i) + IPV6ADDR_VALUE4_OFFSET])) = data_array[i].value4;
*reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset  + (IPV6ADDR_SIZE * i) + IPV6ADDR_VALUE5_OFFSET])) = data_array[i].value5;
serializer->_tail_offset += (IPV6ADDR_SIZE * len);
}return data_array_offset;}

SerializeOffset<Vector<SunspecModelDefStruct>> serialize_vector_sunspecmodeldef_struct(Serializer *const serializer, std::vector<SunspecModelDefStruct> data_array){
SerializeOffset<Vector<SunspecModelDefStruct>> data_array_offset;
uint16_t len = data_array.size();
serializer->_tail_offset += get_padding_size(serializer->_tail_offset, OFFSET_SIZE);
serializer->make_buffer_adequate();
data_array_offset.offset = serializer->_tail_offset;
*reinterpret_cast<uint16_t *>(&serializer->_buffer[serializer->_tail_offset]) = len;
serializer->_tail_offset += OFFSET_SIZE;serializer->_tail_offset += get_padding_size(serializer->_tail_offset, SUNSPECMODELDEF_ALIGNMENT);for (uint16_t i = 0; i < len; i++){*reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset  + (SUNSPECMODELDEF_SIZE * i) + SUNSPECMODELDEF_ID_OFFSET])) = data_array[i].id;
*reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset  + (SUNSPECMODELDEF_SIZE * i) + SUNSPECMODELDEF_GROUP_OFFSET])) = data_array[i].group.offset - (serializer->_tail_offset  + (SUNSPECMODELDEF_SIZE * i) +SUNSPECMODELDEF_GROUP_OFFSET);
serializer->_tail_offset += (SUNSPECMODELDEF_SIZE * len);
}return data_array_offset;}

SerializeOffset<Vector<enum16Struct>> serialize_vector_enum16_struct(Serializer *const serializer, std::vector<enum16Struct> data_array){
SerializeOffset<Vector<enum16Struct>> data_array_offset;
uint16_t len = data_array.size();
serializer->_tail_offset += get_padding_size(serializer->_tail_offset, OFFSET_SIZE);
serializer->make_buffer_adequate();
data_array_offset.offset = serializer->_tail_offset;
*reinterpret_cast<uint16_t *>(&serializer->_buffer[serializer->_tail_offset]) = len;
serializer->_tail_offset += OFFSET_SIZE;serializer->_tail_offset += get_padding_size(serializer->_tail_offset, ENUM16_ALIGNMENT);for (uint16_t i = 0; i < len; i++){*reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset  + (ENUM16_SIZE * i) + ENUM16_VALUE_OFFSET])) = data_array[i].value;
serializer->_tail_offset += (ENUM16_SIZE * len);
}return data_array_offset;}

SerializeOffset<Vector<enum32Struct>> serialize_vector_enum32_struct(Serializer *const serializer, std::vector<enum32Struct> data_array){
SerializeOffset<Vector<enum32Struct>> data_array_offset;
uint16_t len = data_array.size();
serializer->_tail_offset += get_padding_size(serializer->_tail_offset, OFFSET_SIZE);
serializer->make_buffer_adequate();
data_array_offset.offset = serializer->_tail_offset;
*reinterpret_cast<uint16_t *>(&serializer->_buffer[serializer->_tail_offset]) = len;
serializer->_tail_offset += OFFSET_SIZE;serializer->_tail_offset += get_padding_size(serializer->_tail_offset, ENUM32_ALIGNMENT);for (uint16_t i = 0; i < len; i++){*reinterpret_cast<uint32_t *>(&(serializer->_buffer[serializer->_tail_offset  + (ENUM32_SIZE * i) + ENUM32_VALUE_OFFSET])) = data_array[i].value;
serializer->_tail_offset += (ENUM32_SIZE * len);
}return data_array_offset;}

SerializeOffset<Vector<enum64Struct>> serialize_vector_enum64_struct(Serializer *const serializer, std::vector<enum64Struct> data_array){
SerializeOffset<Vector<enum64Struct>> data_array_offset;
uint16_t len = data_array.size();
serializer->_tail_offset += get_padding_size(serializer->_tail_offset, OFFSET_SIZE);
serializer->make_buffer_adequate();
data_array_offset.offset = serializer->_tail_offset;
*reinterpret_cast<uint16_t *>(&serializer->_buffer[serializer->_tail_offset]) = len;
serializer->_tail_offset += OFFSET_SIZE;serializer->_tail_offset += get_padding_size(serializer->_tail_offset, ENUM64_ALIGNMENT);for (uint16_t i = 0; i < len; i++){*reinterpret_cast<uint64_t *>(&(serializer->_buffer[serializer->_tail_offset  + (ENUM64_SIZE * i) + ENUM64_VALUE_OFFSET])) = data_array[i].value;
serializer->_tail_offset += (ENUM64_SIZE * len);
}return data_array_offset;}

SerializeOffset<Vector<bitfield16Struct>> serialize_vector_bitfield16_struct(Serializer *const serializer, std::vector<bitfield16Struct> data_array){
SerializeOffset<Vector<bitfield16Struct>> data_array_offset;
uint16_t len = data_array.size();
serializer->_tail_offset += get_padding_size(serializer->_tail_offset, OFFSET_SIZE);
serializer->make_buffer_adequate();
data_array_offset.offset = serializer->_tail_offset;
*reinterpret_cast<uint16_t *>(&serializer->_buffer[serializer->_tail_offset]) = len;
serializer->_tail_offset += OFFSET_SIZE;serializer->_tail_offset += get_padding_size(serializer->_tail_offset, BITFIELD16_ALIGNMENT);for (uint16_t i = 0; i < len; i++){*reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset  + (BITFIELD16_SIZE * i) + BITFIELD16_VALUE_OFFSET])) = data_array[i].value;
serializer->_tail_offset += (BITFIELD16_SIZE * len);
}return data_array_offset;}

SerializeOffset<Vector<SunspecGroupPointDefStruct>> serialize_vector_sunspecgrouppointdef_struct(Serializer *const serializer, std::vector<SunspecGroupPointDefStruct> data_array){
SerializeOffset<Vector<SunspecGroupPointDefStruct>> data_array_offset;
uint16_t len = data_array.size();
serializer->_tail_offset += get_padding_size(serializer->_tail_offset, OFFSET_SIZE);
serializer->make_buffer_adequate();
data_array_offset.offset = serializer->_tail_offset;
*reinterpret_cast<uint16_t *>(&serializer->_buffer[serializer->_tail_offset]) = len;
serializer->_tail_offset += OFFSET_SIZE;serializer->_tail_offset += get_padding_size(serializer->_tail_offset, SUNSPECGROUPPOINTDEF_ALIGNMENT);for (uint16_t i = 0; i < len; i++){*reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset  + (SUNSPECGROUPPOINTDEF_SIZE * i) + SUNSPECGROUPPOINTDEF_ID_OFFSET])) = data_array[i].id.offset - (serializer->_tail_offset  + (SUNSPECGROUPPOINTDEF_SIZE * i) +SUNSPECGROUPPOINTDEF_ID_OFFSET);
*reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset  + (SUNSPECGROUPPOINTDEF_SIZE * i) + SUNSPECGROUPPOINTDEF_COUNT_POINT_ID_OFFSET])) = data_array[i].count_point_id.offset - (serializer->_tail_offset  + (SUNSPECGROUPPOINTDEF_SIZE * i) +SUNSPECGROUPPOINTDEF_COUNT_POINT_ID_OFFSET);
*reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset  + (SUNSPECGROUPPOINTDEF_SIZE * i) + SUNSPECGROUPPOINTDEF_POINTS_OFFSET])) = data_array[i].points.offset - (serializer->_tail_offset  + (SUNSPECGROUPPOINTDEF_SIZE * i) +SUNSPECGROUPPOINTDEF_POINTS_OFFSET);
*reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset  + (SUNSPECGROUPPOINTDEF_SIZE * i) + SUNSPECGROUPPOINTDEF_GROUPS_OFFSET])) = data_array[i].groups.offset - (serializer->_tail_offset  + (SUNSPECGROUPPOINTDEF_SIZE * i) +SUNSPECGROUPPOINTDEF_GROUPS_OFFSET);
*reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset  + (SUNSPECGROUPPOINTDEF_SIZE * i) + SUNSPECGROUPPOINTDEF_LABEL_OFFSET])) = data_array[i].label.offset - (serializer->_tail_offset  + (SUNSPECGROUPPOINTDEF_SIZE * i) +SUNSPECGROUPPOINTDEF_LABEL_OFFSET);
*reinterpret_cast<uint8_t *>(&(serializer->_buffer[serializer->_tail_offset  + (SUNSPECGROUPPOINTDEF_SIZE * i) + SUNSPECGROUPPOINTDEF_COUNT_OFFSET])) = data_array[i].count;
*reinterpret_cast<SunspecGroupType *>(&(serializer->_buffer[serializer->_tail_offset  + (SUNSPECGROUPPOINTDEF_SIZE * i) + SUNSPECGROUPPOINTDEF_TYPE_OFFSET])) = data_array[i].type;
serializer->_tail_offset += (SUNSPECGROUPPOINTDEF_SIZE * len);
}return data_array_offset;}

SerializeOffset<Vector<bitfield32Struct>> serialize_vector_bitfield32_struct(Serializer *const serializer, std::vector<bitfield32Struct> data_array){
SerializeOffset<Vector<bitfield32Struct>> data_array_offset;
uint16_t len = data_array.size();
serializer->_tail_offset += get_padding_size(serializer->_tail_offset, OFFSET_SIZE);
serializer->make_buffer_adequate();
data_array_offset.offset = serializer->_tail_offset;
*reinterpret_cast<uint16_t *>(&serializer->_buffer[serializer->_tail_offset]) = len;
serializer->_tail_offset += OFFSET_SIZE;serializer->_tail_offset += get_padding_size(serializer->_tail_offset, BITFIELD32_ALIGNMENT);for (uint16_t i = 0; i < len; i++){*reinterpret_cast<uint32_t *>(&(serializer->_buffer[serializer->_tail_offset  + (BITFIELD32_SIZE * i) + BITFIELD32_VALUE_OFFSET])) = data_array[i].value;
serializer->_tail_offset += (BITFIELD32_SIZE * len);
}return data_array_offset;}

SerializeOffset<Vector<bitfield64Struct>> serialize_vector_bitfield64_struct(Serializer *const serializer, std::vector<bitfield64Struct> data_array){
SerializeOffset<Vector<bitfield64Struct>> data_array_offset;
uint16_t len = data_array.size();
serializer->_tail_offset += get_padding_size(serializer->_tail_offset, OFFSET_SIZE);
serializer->make_buffer_adequate();
data_array_offset.offset = serializer->_tail_offset;
*reinterpret_cast<uint16_t *>(&serializer->_buffer[serializer->_tail_offset]) = len;
serializer->_tail_offset += OFFSET_SIZE;serializer->_tail_offset += get_padding_size(serializer->_tail_offset, BITFIELD64_ALIGNMENT);for (uint16_t i = 0; i < len; i++){*reinterpret_cast<uint64_t *>(&(serializer->_buffer[serializer->_tail_offset  + (BITFIELD64_SIZE * i) + BITFIELD64_VALUE_OFFSET])) = data_array[i].value;
serializer->_tail_offset += (BITFIELD64_SIZE * len);
}return data_array_offset;}

SerializeOffset<Vector<SunspecPointDefStruct>> serialize_vector_sunspecpointdef_struct(Serializer *const serializer, std::vector<SunspecPointDefStruct> data_array){
SerializeOffset<Vector<SunspecPointDefStruct>> data_array_offset;
uint16_t len = data_array.size();
serializer->_tail_offset += get_padding_size(serializer->_tail_offset, OFFSET_SIZE);
serializer->make_buffer_adequate();
data_array_offset.offset = serializer->_tail_offset;
*reinterpret_cast<uint16_t *>(&serializer->_buffer[serializer->_tail_offset]) = len;
serializer->_tail_offset += OFFSET_SIZE;serializer->_tail_offset += get_padding_size(serializer->_tail_offset, SUNSPECPOINTDEF_ALIGNMENT);for (uint16_t i = 0; i < len; i++){*reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset  + (SUNSPECPOINTDEF_SIZE * i) + SUNSPECPOINTDEF_ID_OFFSET])) = data_array[i].id.offset - (serializer->_tail_offset  + (SUNSPECPOINTDEF_SIZE * i) +SUNSPECPOINTDEF_ID_OFFSET);
*reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset  + (SUNSPECPOINTDEF_SIZE * i) + SUNSPECPOINTDEF_SF_ID_OFFSET])) = data_array[i].sf_id.offset - (serializer->_tail_offset  + (SUNSPECPOINTDEF_SIZE * i) +SUNSPECPOINTDEF_SF_ID_OFFSET);
*reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset  + (SUNSPECPOINTDEF_SIZE * i) + SUNSPECPOINTDEF_UNITS_OFFSET])) = data_array[i].units.offset - (serializer->_tail_offset  + (SUNSPECPOINTDEF_SIZE * i) +SUNSPECPOINTDEF_UNITS_OFFSET);
*reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset  + (SUNSPECPOINTDEF_SIZE * i) + SUNSPECPOINTDEF_LABEL_OFFSET])) = data_array[i].label.offset - (serializer->_tail_offset  + (SUNSPECPOINTDEF_SIZE * i) +SUNSPECPOINTDEF_LABEL_OFFSET);
*reinterpret_cast<SunspecPointData_enum *>(&(serializer->_buffer[serializer->_tail_offset  + (SUNSPECPOINTDEF_SIZE * i) + SUNSPECPOINTDEF_DATA_TYPE_OFFSET])) = data_array[i].data_type;
*reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset  + (SUNSPECPOINTDEF_SIZE * i) + SUNSPECPOINTDEF_DATA_OFFSET])) = data_array[i].data.offset - (serializer->_tail_offset  + (SUNSPECPOINTDEF_SIZE * i) +SUNSPECPOINTDEF_DATA_OFFSET);
*reinterpret_cast<uint8_t *>(&(serializer->_buffer[serializer->_tail_offset  + (SUNSPECPOINTDEF_SIZE * i) + SUNSPECPOINTDEF_COUNT_OFFSET])) = data_array[i].count;
*reinterpret_cast<uint8_t *>(&(serializer->_buffer[serializer->_tail_offset  + (SUNSPECPOINTDEF_SIZE * i) + SUNSPECPOINTDEF_SIZE_OFFSET])) = data_array[i].size;
*reinterpret_cast<int8_t *>(&(serializer->_buffer[serializer->_tail_offset  + (SUNSPECPOINTDEF_SIZE * i) + SUNSPECPOINTDEF_SF_OFFSET])) = data_array[i].sf;
*reinterpret_cast<SunspecPointAccessType *>(&(serializer->_buffer[serializer->_tail_offset  + (SUNSPECPOINTDEF_SIZE * i) + SUNSPECPOINTDEF_ACCESS_OFFSET])) = data_array[i].access;
*reinterpret_cast<SunspecPointMandatoryType *>(&(serializer->_buffer[serializer->_tail_offset  + (SUNSPECPOINTDEF_SIZE * i) + SUNSPECPOINTDEF_MANDATORY_OFFSET])) = data_array[i].mandatory;
serializer->_tail_offset += (SUNSPECPOINTDEF_SIZE * len);
}return data_array_offset;}

SerializeOffset<Vector<sunssfStruct>> serialize_vector_sunssf_struct(Serializer *const serializer, std::vector<sunssfStruct> data_array){
SerializeOffset<Vector<sunssfStruct>> data_array_offset;
uint16_t len = data_array.size();
serializer->_tail_offset += get_padding_size(serializer->_tail_offset, OFFSET_SIZE);
serializer->make_buffer_adequate();
data_array_offset.offset = serializer->_tail_offset;
*reinterpret_cast<uint16_t *>(&serializer->_buffer[serializer->_tail_offset]) = len;
serializer->_tail_offset += OFFSET_SIZE;serializer->_tail_offset += get_padding_size(serializer->_tail_offset, SUNSSF_ALIGNMENT);for (uint16_t i = 0; i < len; i++){*reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset  + (SUNSSF_SIZE * i) + SUNSSF_VALUE_OFFSET])) = data_array[i].value;
serializer->_tail_offset += (SUNSSF_SIZE * len);
}return data_array_offset;}

SerializeOffset<Vector<acc16Struct>> serialize_vector_acc16_struct(Serializer *const serializer, std::vector<acc16Struct> data_array){
SerializeOffset<Vector<acc16Struct>> data_array_offset;
uint16_t len = data_array.size();
serializer->_tail_offset += get_padding_size(serializer->_tail_offset, OFFSET_SIZE);
serializer->make_buffer_adequate();
data_array_offset.offset = serializer->_tail_offset;
*reinterpret_cast<uint16_t *>(&serializer->_buffer[serializer->_tail_offset]) = len;
serializer->_tail_offset += OFFSET_SIZE;serializer->_tail_offset += get_padding_size(serializer->_tail_offset, ACC16_ALIGNMENT);for (uint16_t i = 0; i < len; i++){*reinterpret_cast<uint16_t *>(&(serializer->_buffer[serializer->_tail_offset  + (ACC16_SIZE * i) + ACC16_VALUE_OFFSET])) = data_array[i].value;
serializer->_tail_offset += (ACC16_SIZE * len);
}return data_array_offset;}



unsigned char *serialize_sunspecmodeldef_root(Serializer *const serializer,
 const uint16_t id,
 const SerializeOffset<SunspecGroupPointDef> group){
uint16_t current_offset = OFFSET_SIZE * 2 + get_padding_size(OFFSET_SIZE * 2, SUNSPECMODELDEF_ALIGNMENT);


*reinterpret_cast<uint16_t *>(&(serializer->_buffer[current_offset  + SUNSPECMODELDEF_ID_OFFSET])) = id;
*reinterpret_cast<uint16_t *>(&(serializer->_buffer[current_offset  + SUNSPECMODELDEF_GROUP_OFFSET])) = group.offset - (current_offset  +SUNSPECMODELDEF_GROUP_OFFSET);

return serializer->_buffer;
}