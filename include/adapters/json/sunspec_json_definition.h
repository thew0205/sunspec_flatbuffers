/**
 * @file sunspec_json_definition.h
 * @brief SunspecPointDef/SunspecGroupDef/SunspecModelDef backed entirely by the
 * raw SunSpec model JSON text -- no upfront tree parse, no c_model_definition.h
 * dependency. Each object's *only* real state is a (const char*, length) span
 * into the JSON buffer; every accessor re-parses just that span, on demand,
 * each time it's called. A SunspecGroupDef obtained from group()/points()/
 * groups() is a cheap cursor pointing at the start of its own JSON object --
 * nothing about its children is touched until something asks for them.
 *
 * This is a drop-in alternative selected at build time (SUNSPEC_JSON_IMPLEMENTATION,
 * see sunspec.h): it presents the identical public accessor surface as the
 * hand-authored c_model_definition.h version so that the
 * Sunspec{Model,Point,Group,Device}{Reader,Writer} code, which only ever calls
 * these accessors, needs no changes.
 *
 * Each model's raw JSON text is embedded as a static const char* in
 * src/models/json/model_json_<id>.cpp (see models/generate_model_json_cpp.py).
 * SunspecModelDef::getModelDefinition() looks that text up and wraps it in a
 * SunspecModelDef -- still just a pointer, no parsing happens until an
 * accessor is actually called.
 *
 * Trade-off, deliberately: repeatedly calling the same accessor re-parses the
 * same bytes every time. The one exception is the pointer-returning
 * accessors (points()/groups()/group()/data_as_kXXX()) -- their `mutable
 * ..._cache_` members are populated once and reused for the object's
 * lifetime, both so the returned pointer stays stable and so the one-time
 * allocation lands at SunspecModelDef construction (see its eager warm-up)
 * rather than on whichever call happens to reach it first at runtime. This
 * is safe because json_/json_len_ never change once an object exists.
 */
#pragma once

#include <stdint.h>
#include <cstddef>
#include <vector>
#include <string_view>
#include <variant>
#include <array>

struct kSint16
{
private:
    int16_t value_;

public:
    kSint16(int16_t value) : value_(value) {}
    int16_t value() const { return value_; }
};

struct kSint32
{
private:
    int32_t value_;

public:
    kSint32(int32_t value) : value_(value) {}
    int32_t value() const { return value_; }
};

struct kSint64
{
private:
    int64_t value_;

public:
    kSint64(int64_t value) : value_(value) {}
    int64_t value() const { return value_; }
};

struct kRaw16
{
private:
    uint16_t value_;

public:
    kRaw16(uint16_t value) : value_(value) {}
    uint16_t value() const { return value_; }
};

struct kUint16
{
private:
    uint16_t value_;

public:
    kUint16(uint16_t value) : value_(value) {}
    uint16_t value() const { return value_; }
};

struct kUint32
{
private:
    uint32_t value_;

public:
    kUint32(uint32_t value) : value_(value) {}
    uint32_t value() const { return value_; }
};

struct kUint64
{
private:
    uint64_t value_;

public:
    kUint64(uint64_t value) : value_(value) {}
    uint64_t value() const { return value_; }
};

struct kAcc16
{
private:
    uint16_t value_;

public:
    kAcc16(uint16_t value) : value_(value) {}
    uint16_t value() const { return value_; }
};

struct kAcc32
{
private:
    uint32_t value_;

public:
    kAcc32(uint32_t value) : value_(value) {}
    uint32_t value() const { return value_; }
};

struct kAcc64
{
private:
    uint64_t value_;

public:
    kAcc64(uint64_t value) : value_(value) {}
    uint64_t value() const { return value_; }
};

struct kBitfield16
{
private:
    uint16_t value_;

public:
    kBitfield16(uint16_t value) : value_(value) {}
    uint16_t value() const { return value_; }
};

struct kBitfield32
{
private:
    uint32_t value_;

public:
    kBitfield32(uint32_t value) : value_(value) {}
    uint32_t value() const { return value_; }
};

struct kBitfield64
{
private:
    uint64_t value_;

public:
    kBitfield64(uint64_t value) : value_(value) {}
    uint64_t value() const { return value_; }
};

struct kEnum16
{
private:
    uint16_t value_;

public:
    kEnum16(uint16_t value) : value_(value) {}
    uint16_t value() const { return value_; }
};

struct kEnum32
{
private:
    uint32_t value_;

public:
    kEnum32(uint32_t value) : value_(value) {}
    uint32_t value() const { return value_; }
};

struct kFloat32
{
private:
    float value_;

public:
    kFloat32(float value) : value_(value) {}
    float value() const { return value_; }
};

struct kFloat64
{
private:
    double value_;

public:
    kFloat64(double value) : value_(value) {}
    double value() const { return value_; }
};

struct kStringx
{
private:
    std::string_view value_;

public:
    kStringx(std::string_view value) : value_(value) {}
    std::string_view value() const { return value_; }
};

struct kSunsSf
{
private:
    uint16_t value_;

public:
    kSunsSf(uint16_t value) : value_(value) {}
    uint16_t value() const { return value_; }
};

struct kPad16
{
private:
    uint16_t value_;

public:
    kPad16(uint16_t value) : value_(value) {}
    uint16_t value() const { return value_; }
};

struct kIpAddr
{
private:
    uint8_t octet1_;
    uint8_t octet2_;
    uint8_t octet3_;
    uint8_t octet4_;

public:
    kIpAddr(uint8_t octet1, uint8_t octet2, uint8_t octet3, uint8_t octet4)
        : octet1_(octet1), octet2_(octet2), octet3_(octet3), octet4_(octet4) {}
    uint8_t octet1() const { return octet1_; }
    uint8_t octet2() const { return octet2_; }
    uint8_t octet3() const { return octet3_; }
    uint8_t octet4() const { return octet4_; }
};

struct kIpv6Addr
{
private:
    std::array<uint8_t, 24> value_;

public:
    kIpv6Addr(const std::array<uint8_t, 24> &value) : value_(value) {}
    std::array<uint8_t, 24> value() const { return value_; }
};

struct kEui48
{
private:
    std::array<uint8_t, 3> value_;

public:
    kEui48(const std::array<uint8_t, 3> &value) : value_(value) {}
    std::array<uint8_t, 3> value() const { return value_; }
};

enum SunspecPointData
{
    SunspecPointData_NONE = 0,
    SunspecPointData_kSint16,
    SunspecPointData_kSint32,
    SunspecPointData_kSint64,
    SunspecPointData_kRaw16,
    SunspecPointData_kUint16,
    SunspecPointData_kUint32,
    SunspecPointData_kUint64,
    SunspecPointData_kAcc16,
    SunspecPointData_kAcc32,
    SunspecPointData_kAcc64,
    SunspecPointData_kBitfield16,
    SunspecPointData_kBitfield32,
    SunspecPointData_kBitfield64,
    SunspecPointData_kEnum16,
    SunspecPointData_kEnum32,
    SunspecPointData_kFloat32,
    SunspecPointData_kFloat64,
    SunspecPointData_kStringx,
    SunspecPointData_kSunsSf,
    SunspecPointData_kPad16,
    SunspecPointData_kIpAddr,
    SunspecPointData_kIpv6Addr,
    SunspecPointData_kEui48,
};

enum SunspecPointAccessType
{
    SunspecPointAccessType_kR,
    SunspecPointAccessType_kRW,
};

enum SunspecPointMandatoryType
{
    SunspecPointMandatoryType_kM,
    SunspecPointMandatoryType_kO,
};

enum SunspecGroupType
{
    SunspecGroupType_kGroup,
    SunspecGroupType_kSync,
};

typedef std::variant<std::monostate, kSint16, kSint32, kSint64, kRaw16, kUint16, kUint32, kUint64, kAcc16, kAcc32, kAcc64, kBitfield16, kBitfield32, kBitfield64, kEnum16, kEnum32, kFloat32, kFloat64, kStringx, kSunsSf, kPad16, kIpAddr, kIpv6Addr, kEui48> SunspecPointDataVariant;

/**
 * @brief A cursor onto one point object within a model's raw JSON text.
 * Holds nothing but that object's (start, length) span; every accessor
 * re-parses on demand from it.
 */
class SunspecPointDef
{
    using string_view = std::string_view;

public:
    string_view id() const;
    string_view count_point_id() const;
    string_view sf_id() const;
    int16_t sf() const;
    string_view units() const;
    string_view label() const;
    uint16_t count() const;
    SunspecPointData data_type() const;

    const kSint16 *data_as_kSint16() const;
    const kSint32 *data_as_kSint32() const;
    const kSint64 *data_as_kSint64() const;
    const kRaw16 *data_as_kRaw16() const;
    const kUint16 *data_as_kUint16() const;
    const kUint32 *data_as_kUint32() const;
    const kUint64 *data_as_kUint64() const;
    const kAcc16 *data_as_kAcc16() const;
    const kAcc32 *data_as_kAcc32() const;
    const kAcc64 *data_as_kAcc64() const;
    const kBitfield16 *data_as_kBitfield16() const;
    const kBitfield32 *data_as_kBitfield32() const;
    const kBitfield64 *data_as_kBitfield64() const;
    const kEnum16 *data_as_kEnum16() const;
    const kEnum32 *data_as_kEnum32() const;
    const kFloat32 *data_as_kFloat32() const;
    const kFloat64 *data_as_kFloat64() const;
    const kStringx *data_as_kStringx() const;
    const kSunsSf *data_as_kSunsSf() const;
    const kPad16 *data_as_kPad16() const;
    const kIpAddr *data_as_kIpAddr() const;
    const kIpv6Addr *data_as_kIpv6Addr() const;
    const kEui48 *data_as_kEui48() const;

    SunspecPointAccessType access() const;
    SunspecPointMandatoryType mandatory() const;
    uint16_t size() const;

    /**
     * @brief Wraps a point object's JSON span. `json` need not be
     * NUL-terminated at `json_len` -- every internal parse is explicitly
     * bounded to [json, json + json_len).
     */
    SunspecPointDef(const char *json, size_t json_len);

    SunspecPointDef(SunspecPointDef &&point) noexcept = default;
    SunspecPointDef(const SunspecPointDef &point) noexcept = default;

private:
    const char *json_;
    size_t json_len_;

    SunspecPointDataVariant data_cache_;

    // void refresh_data_cache() const;

    SunspecPointDef &operator=(const SunspecPointDef &point) = delete;
    SunspecPointDef &operator=(SunspecPointDef &&other) = delete;
};

/**
 * @brief A cursor onto one group object (top-level or nested) within a
 * model's raw JSON text. Holds nothing but that object's (start, length)
 * span; points()/groups() build cursors for each child on demand -- nothing
 * below this group is touched until asked for.
 */
class SunspecGroupDef
{
    using string_view = std::string_view;

public:
    const std::vector<SunspecGroupDef> *groups() const;
    const std::vector<SunspecPointDef> *points() const;
    string_view label() const;
    string_view count_point_id() const;
    string_view id() const;
    uint16_t count() const;
    SunspecGroupType type() const;

    SunspecGroupDef(const char *json, size_t json_len);

    SunspecGroupDef(const SunspecGroupDef &group) = default;
    SunspecGroupDef(SunspecGroupDef &&group) noexcept = default;

private:
    const char *json_;
    size_t json_len_;

    std::vector<SunspecPointDef> points_cache_;
    std::vector<SunspecGroupDef> groups_cache_;

    SunspecGroupDef &operator=(const SunspecGroupDef &group) = delete;
    SunspecGroupDef &operator=(SunspecGroupDef &&group) = delete;
};

enum SunspecModelList : uint16_t
{
    SunspecModelList_kModelInvalid = 0,
    SunspecModelList_kModel1 = 1,
    SunspecModelList_kModel2 = 2,
    SunspecModelList_kModel3 = 3,
    SunspecModelList_kModel4 = 4,
    SunspecModelList_kModel5 = 5,
    SunspecModelList_kModel6 = 6,
    SunspecModelList_kModel7 = 7,
    SunspecModelList_kModel8 = 8,
    SunspecModelList_kModel9 = 9,
    SunspecModelList_kModel10 = 10,
    SunspecModelList_kModel11 = 11,
    SunspecModelList_kModel12 = 12,
    SunspecModelList_kModel13 = 13,
    SunspecModelList_kModel14 = 14,
    SunspecModelList_kModel15 = 15,
    SunspecModelList_kModel16 = 16,
    SunspecModelList_kModel17 = 17,
    SunspecModelList_kModel18 = 18,
    SunspecModelList_kModel19 = 19,
    SunspecModelList_kModel101 = 101,
    SunspecModelList_kModel102 = 102,
    SunspecModelList_kModel103 = 103,
    SunspecModelList_kModel111 = 111,
    SunspecModelList_kModel112 = 112,
    SunspecModelList_kModel113 = 113,
    SunspecModelList_kModel120 = 120,
    SunspecModelList_kModel121 = 121,
    SunspecModelList_kModel122 = 122,
    SunspecModelList_kModel123 = 123,
    SunspecModelList_kModel124 = 124,
    SunspecModelList_kModel125 = 125,
    SunspecModelList_kModel126 = 126,
    SunspecModelList_kModel127 = 127,
    SunspecModelList_kModel128 = 128,
    SunspecModelList_kModel129 = 129,
    SunspecModelList_kModel130 = 130,
    SunspecModelList_kModel131 = 131,
    SunspecModelList_kModel132 = 132,
    SunspecModelList_kModel133 = 133,
    SunspecModelList_kModel134 = 134,
    SunspecModelList_kModel135 = 135,
    SunspecModelList_kModel136 = 136,
    SunspecModelList_kModel137 = 137,
    SunspecModelList_kModel138 = 138,
    SunspecModelList_kModel139 = 139,
    SunspecModelList_kModel140 = 140,
    SunspecModelList_kModel141 = 141,
    SunspecModelList_kModel142 = 142,
    SunspecModelList_kModel143 = 143,
    SunspecModelList_kModel144 = 144,
    SunspecModelList_kModel145 = 145,
    SunspecModelList_kModel160 = 160,
    SunspecModelList_kModel201 = 201,
    SunspecModelList_kModel202 = 202,
    SunspecModelList_kModel203 = 203,
    SunspecModelList_kModel204 = 204,
    SunspecModelList_kModel211 = 211,
    SunspecModelList_kModel212 = 212,
    SunspecModelList_kModel213 = 213,
    SunspecModelList_kModel214 = 214,
    SunspecModelList_kModel220 = 220,
    SunspecModelList_kModel302 = 302,
    SunspecModelList_kModel303 = 303,
    SunspecModelList_kModel304 = 304,
    SunspecModelList_kModel305 = 305,
    SunspecModelList_kModel306 = 306,
    SunspecModelList_kModel307 = 307,
    SunspecModelList_kModel308 = 308,
    SunspecModelList_kModel401 = 401,
    SunspecModelList_kModel402 = 402,
    SunspecModelList_kModel403 = 403,
    SunspecModelList_kModel404 = 404,
    SunspecModelList_kModel501 = 501,
    SunspecModelList_kModel502 = 502,
    SunspecModelList_kModel601 = 601,
    SunspecModelList_kModel701 = 701,
    SunspecModelList_kModel702 = 702,
    SunspecModelList_kModel703 = 703,
    SunspecModelList_kModel704 = 704,
    SunspecModelList_kModel705 = 705,
    SunspecModelList_kModel706 = 706,
    SunspecModelList_kModel707 = 707,
    SunspecModelList_kModel708 = 708,
    SunspecModelList_kModel709 = 709,
    SunspecModelList_kModel710 = 710,
    SunspecModelList_kModel711 = 711,
    SunspecModelList_kModel712 = 712,
    SunspecModelList_kModel713 = 713,
    SunspecModelList_kModel714 = 714,
    SunspecModelList_kModel715 = 715,
    SunspecModelList_kModel801 = 801,
    SunspecModelList_kModel802 = 802,
    SunspecModelList_kModel803 = 803,
    SunspecModelList_kModel804 = 804,
    SunspecModelList_kModel805 = 805,
    SunspecModelList_kModel806 = 806,
    SunspecModelList_kModel807 = 807,
    SunspecModelList_kModel808 = 808,
    SunspecModelList_kModel809 = 809,
    SunspecModelList_kModel63001 = 63001,
    SunspecModelList_kModel63002 = 63002,
    SunspecModelList_kModel64001 = 64001,
    SunspecModelList_kModel64020 = 64020,
    SunspecModelList_kModel64101 = 64101,
    SunspecModelList_kModel64111 = 64111,
    SunspecModelList_kModel64112 = 64112,
    SunspecModelList_kModel64410 = 64410,
    SunspecModelList_kModel64411 = 64411,
    SunspecModelList_kModel64412 = 64412,
    SunspecModelList_kModel64413 = 64413,
    SunspecModelList_kModel64414 = 64414,
    SunspecModelList_kModel64415 = 64415,
    SunspecModelList_kModelEnd = 0xFFFF,
};

/**
 * @brief A cursor onto one model's whole raw JSON text. Constructing one just
 * remembers the pointer -- id()/label()/group() each parse on demand.
 *
 * Every registered model gets a `static const SunspecModelDef modelDef<id>`
 * member, initialized at program startup (same as include/c_model_definition.h) --
 * cheap here because construction never parses anything, it just stores the
 * JSON pointer.
 */
class SunspecModelDef
{
    using string_view = std::string_view;

public:
    const SunspecGroupDef *group() const;
    SunspecModelList id() const;
    string_view label() const;

private:
    explicit SunspecModelDef(const char *json);

    SunspecModelDef(const SunspecModelDef &model) = delete;
    SunspecModelDef &operator=(const SunspecModelDef &model) = delete;
    SunspecModelDef &operator=(SunspecModelDef &&model) = delete;

    const char *json_;
    size_t json_len_;
    std::vector<SunspecGroupDef> group_cache_; // holds 0 or 1 element; vector purely so it's default-constructible and movable without SunspecGroupDef needing one

public:

    SunspecModelDef(SunspecModelDef &&model) = default;

    /**
     * @brief Static definition for Model 1.
     */
    static SunspecModelDef modelDef1();

    /**
     * @brief Static definition for Model 2.
     */
    static SunspecModelDef modelDef2();

    /**
     * @brief Static definition for Model 3.
     */
    static SunspecModelDef modelDef3();

    /**
     * @brief Static definition for Model 4.
     */
    static SunspecModelDef modelDef4();

    /**
     * @brief Static definition for Model 5.
     */
    static SunspecModelDef modelDef5();

    /**
     * @brief Static definition for Model 6.
     */
    static SunspecModelDef modelDef6();

    /**
     * @brief Static definition for Model 7.
     */
    static SunspecModelDef modelDef7();

    /**
     * @brief Static definition for Model 8.
     */
    static SunspecModelDef modelDef8();

    /**
     * @brief Static definition for Model 9.
     */
    static SunspecModelDef modelDef9();

    /**
     * @brief Static definition for Model 10.
     */
    static SunspecModelDef modelDef10();

    /**
     * @brief Static definition for Model 11.
     */
    static SunspecModelDef modelDef11();

    /**
     * @brief Static definition for Model 12.
     */
    static SunspecModelDef modelDef12();

    /**
     * @brief Static definition for Model 13.
     */
    static SunspecModelDef modelDef13();

    /**
     * @brief Static definition for Model 14.
     */
    static SunspecModelDef modelDef14();

    /**
     * @brief Static definition for Model 15.
     */
    static SunspecModelDef modelDef15();

    /**
     * @brief Static definition for Model 16.
     */
    static SunspecModelDef modelDef16();

    /**
     * @brief Static definition for Model 17.
     */
    static SunspecModelDef modelDef17();

    /**
     * @brief Static definition for Model 18.
     */
    static SunspecModelDef modelDef18();

    /**
     * @brief Static definition for Model 19.
     */
    static SunspecModelDef modelDef19();

    /**
     * @brief Static definition for Model 101.
     */
    static SunspecModelDef modelDef101();

    /**
     * @brief Static definition for Model 102.
     */
    static SunspecModelDef modelDef102();

    /**
     * @brief Static definition for Model 103.
     */
    static SunspecModelDef modelDef103();

    /**
     * @brief Static definition for Model 111.
     */
    static SunspecModelDef modelDef111();

    /**
     * @brief Static definition for Model 112.
     */
    static SunspecModelDef modelDef112();

    /**
     * @brief Static definition for Model 113.
     */
    static SunspecModelDef modelDef113();

    /**
     * @brief Static definition for Model 120.
     */
    static SunspecModelDef modelDef120();

    /**
     * @brief Static definition for Model 121.
     */
    static SunspecModelDef modelDef121();

    /**
     * @brief Static definition for Model 122.
     */
    static SunspecModelDef modelDef122();

    /**
     * @brief Static definition for Model 123.
     */
    static SunspecModelDef modelDef123();

    /**
     * @brief Static definition for Model 124.
     */
    static SunspecModelDef modelDef124();

    /**
     * @brief Static definition for Model 125.
     */
    static SunspecModelDef modelDef125();

    /**
     * @brief Static definition for Model 126.
     */
    static SunspecModelDef modelDef126();

    /**
     * @brief Static definition for Model 127.
     */
    static SunspecModelDef modelDef127();

    /**
     * @brief Static definition for Model 128.
     */
    static SunspecModelDef modelDef128();

    /**
     * @brief Static definition for Model 129.
     */
    static SunspecModelDef modelDef129();

    /**
     * @brief Static definition for Model 130.
     */
    static SunspecModelDef modelDef130();

    /**
     * @brief Static definition for Model 131.
     */
    static SunspecModelDef modelDef131();

    /**
     * @brief Static definition for Model 132.
     */
    static SunspecModelDef modelDef132();

    /**
     * @brief Static definition for Model 133.
     */
    static SunspecModelDef modelDef133();

    /**
     * @brief Static definition for Model 134.
     */
    static SunspecModelDef modelDef134();

    /**
     * @brief Static definition for Model 135.
     */
    static SunspecModelDef modelDef135();

    /**
     * @brief Static definition for Model 136.
     */
    static SunspecModelDef modelDef136();

    /**
     * @brief Static definition for Model 137.
     */
    static SunspecModelDef modelDef137();

    /**
     * @brief Static definition for Model 138.
     */
    static SunspecModelDef modelDef138();

    /**
     * @brief Static definition for Model 139.
     */
    static SunspecModelDef modelDef139();

    /**
     * @brief Static definition for Model 140.
     */
    static SunspecModelDef modelDef140();

    /**
     * @brief Static definition for Model 141.
     */
    static SunspecModelDef modelDef141();

    /**
     * @brief Static definition for Model 142.
     */
    static SunspecModelDef modelDef142();

    /**
     * @brief Static definition for Model 143.
     */
    static SunspecModelDef modelDef143();

    /**
     * @brief Static definition for Model 144.
     */
    static SunspecModelDef modelDef144();

    /**
     * @brief Static definition for Model 145.
     */
    static SunspecModelDef modelDef145();

    /**
     * @brief Static definition for Model 160.
     */
    static SunspecModelDef modelDef160();

    /**
     * @brief Static definition for Model 201.
     */
    static SunspecModelDef modelDef201();

    /**
     * @brief Static definition for Model 202.
     */
    static SunspecModelDef modelDef202();

    /**
     * @brief Static definition for Model 203.
     */
    static SunspecModelDef modelDef203();

    /**
     * @brief Static definition for Model 204.
     */
    static SunspecModelDef modelDef204();

    /**
     * @brief Static definition for Model 211.
     */
    static SunspecModelDef modelDef211();

    /**
     * @brief Static definition for Model 212.
     */
    static SunspecModelDef modelDef212();

    /**
     * @brief Static definition for Model 213.
     */
    static SunspecModelDef modelDef213();

    /**
     * @brief Static definition for Model 214.
     */
    static SunspecModelDef modelDef214();

    /**
     * @brief Static definition for Model 220.
     */
    static SunspecModelDef modelDef220();

    /**
     * @brief Static definition for Model 302.
     */
    static SunspecModelDef modelDef302();

    /**
     * @brief Static definition for Model 303.
     */
    static SunspecModelDef modelDef303();

    /**
     * @brief Static definition for Model 304.
     */
    static SunspecModelDef modelDef304();

    /**
     * @brief Static definition for Model 305.
     */
    static SunspecModelDef modelDef305();

    /**
     * @brief Static definition for Model 306.
     */
    static SunspecModelDef modelDef306();

    /**
     * @brief Static definition for Model 307.
     */
    static SunspecModelDef modelDef307();

    /**
     * @brief Static definition for Model 308.
     */
    static SunspecModelDef modelDef308();

    /**
     * @brief Static definition for Model 401.
     */
    static SunspecModelDef modelDef401();

    /**
     * @brief Static definition for Model 402.
     */
    static SunspecModelDef modelDef402();

    /**
     * @brief Static definition for Model 403.
     */
    static SunspecModelDef modelDef403();

    /**
     * @brief Static definition for Model 404.
     */
    static SunspecModelDef modelDef404();

    /**
     * @brief Static definition for Model 501.
     */
    static SunspecModelDef modelDef501();

    /**
     * @brief Static definition for Model 502.
     */
    static SunspecModelDef modelDef502();

    /**
     * @brief Static definition for Model 601.
     */
    static SunspecModelDef modelDef601();

    /**
     * @brief Static definition for Model 701.
     */
    static SunspecModelDef modelDef701();

    /**
     * @brief Static definition for Model 702.
     */
    static SunspecModelDef modelDef702();

    /**
     * @brief Static definition for Model 703.
     */
    static SunspecModelDef modelDef703();

    /**
     * @brief Static definition for Model 704.
     */
    static SunspecModelDef modelDef704();

    /**
     * @brief Static definition for Model 705.
     */
    static SunspecModelDef modelDef705();

    /**
     * @brief Static definition for Model 706.
     */
    static SunspecModelDef modelDef706();

    /**
     * @brief Static definition for Model 707.
     */
    static SunspecModelDef modelDef707();

    /**
     * @brief Static definition for Model 708.
     */
    static SunspecModelDef modelDef708();

    /**
     * @brief Static definition for Model 709.
     */
    static SunspecModelDef modelDef709();

    /**
     * @brief Static definition for Model 710.
     */
    static SunspecModelDef modelDef710();

    /**
     * @brief Static definition for Model 711.
     */
    static SunspecModelDef modelDef711();

    /**
     * @brief Static definition for Model 712.
     */
    static SunspecModelDef modelDef712();

    /**
     * @brief Static definition for Model 713.
     */
    static SunspecModelDef modelDef713();

    /**
     * @brief Static definition for Model 714.
     */
    static SunspecModelDef modelDef714();

    /**
     * @brief Static definition for Model 715.
     */
    static SunspecModelDef modelDef715();

    /**
     * @brief Static definition for Model 801.
     */
    static SunspecModelDef modelDef801();

    /**
     * @brief Static definition for Model 802.
     */
    static SunspecModelDef modelDef802();

    /**
     * @brief Static definition for Model 803.
     */
    static SunspecModelDef modelDef803();

    /**
     * @brief Static definition for Model 804.
     */
    static SunspecModelDef modelDef804();

    /**
     * @brief Static definition for Model 805.
     */
    static SunspecModelDef modelDef805();

    /**
     * @brief Static definition for Model 806.
     */
    static SunspecModelDef modelDef806();

    /**
     * @brief Static definition for Model 807.
     */
    static SunspecModelDef modelDef807();

    /**
     * @brief Static definition for Model 808.
     */
    static SunspecModelDef modelDef808();

    /**
     * @brief Static definition for Model 809.
     */
    static SunspecModelDef modelDef809();

    /**
     * @brief Static definition for Model 63001.
     */
    static SunspecModelDef modelDef63001();

    /**
     * @brief Static definition for Model 63002.
     */
    static SunspecModelDef modelDef63002();

    /**
     * @brief Static definition for Model 64001.
     */
    static SunspecModelDef modelDef64001();

    /**
     * @brief Static definition for Model 64020.
     */
    static SunspecModelDef modelDef64020();

    /**
     * @brief Static definition for Model 64101.
     */
    static SunspecModelDef modelDef64101();

    /**
     * @brief Static definition for Model 64111.
     */
    static SunspecModelDef modelDef64111();

    /**
     * @brief Static definition for Model 64112.
     */
    static SunspecModelDef modelDef64112();

    /**
     * @brief Static definition for Model 64410.
     */
    static SunspecModelDef modelDef64410();

    /**
     * @brief Static definition for Model 64411.
     */
    static SunspecModelDef modelDef64411();

    /**
     * @brief Static definition for Model 64412.
     */
    static SunspecModelDef modelDef64412();

    /**
     * @brief Static definition for Model 64413.
     */
    static SunspecModelDef modelDef64413();

    /**
     * @brief Static definition for Model 64414.
     */
    static SunspecModelDef modelDef64414();

    /**
     * @brief Static definition for Model 64415.
     */
    static SunspecModelDef modelDef64415();
};

void initializeAllModels();
void deinitializeAllModels();


