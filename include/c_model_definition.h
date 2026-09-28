/**
 * @file sunspec/model_definition.h
 * @brief This file defines the data structures and classes used to represent SunspecModels.
 *
 * It includes enumerations for data types, access types, and other characteristics of Sunspec points,
 * as well as classes for defining individual points, groups of points, and entire models.
 *
 * @author Tolulope Matthew Busoye PowerLabs
 */

#pragma once

#include <stdint.h>
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
    // NOTE: 24 bytes carried over from the source listing, but SunspecPointDef::size()
    // computes 6 registers (12 bytes) for kIpv6Addr -- confirm which is right.
    std::array<uint8_t, 24> value_;

public:
    kIpv6Addr(const std::array<uint8_t, 24> &value) : value_(value) {}
    std::array<uint8_t, 24> value() const { return value_; }
};

struct kEui48
{
private:
    // NOTE: 3 bytes carried over from the source listing -- an EUI-48 is 48 bits (6 bytes),
    // and SunspecPointDef::size() already returns 3 *registers* (6 bytes) for kEui48, so
    // this may need to be std::array<uint8_t, 6>.
    std::array<uint8_t, 3> value_;

public:
    kEui48(const std::array<uint8_t, 3> &value) : value_(value) {}
    std::array<uint8_t, 3> value() const { return value_; }
};

/**
 * @brief Enumeration of SunspecPoint data types.
 */
enum SunspecPointData
{
    SunspecPointData_NONE = 0,    /**< Undefined type */
    SunspecPointData_kSint16,      /**< Signed 16-bit integer */
    SunspecPointData_kSint32,      /**< Signed 32-bit integer */
    SunspecPointData_kSint64,      /**< Signed 64-bit integer */
    SunspecPointData_kRaw16,      /**< 16-bit raw value */
    SunspecPointData_kUint16,     /**< Unsigned 16-bit integer */
    SunspecPointData_kUint32,     /**< Unsigned 32-bit integer */
    SunspecPointData_kUint64,     /**< Unsigned 64-bit integer */
    SunspecPointData_kAcc16,      /**< Unsigned 16-bit accumulator(deprecated, in favor of uint16) */
    SunspecPointData_kAcc32,      /**< Unsigned 32-bit accumulator (deprecated in favor of uint32) */
    SunspecPointData_kAcc64,      /**< Unsigned 64-bit accumulator (deprecated in favor of uint64) */
    SunspecPointData_kBitfield16, /**< 16-bit bitfield */
    SunspecPointData_kBitfield32, /**< 32-bit bitfield */
    SunspecPointData_kBitfield64, /**< 64-bit bitfield */
    SunspecPointData_kEnum16,     /**< 16-bit enumeration */
    SunspecPointData_kEnum32,     /**< 32-bit enumeration */
    SunspecPointData_kFloat32,    /**< 32-bit floating-point */
    SunspecPointData_kFloat64,    /**< 64-bit floating-point */
    SunspecPointData_kStringx,     /**< String (UTF-8 encoded) */
    SunspecPointData_kSunsSf,     /**< Scale factor – Signed power of 10 multiplier (+) or divider (-) */
    SunspecPointData_kPad16,        /**< 16-bit pad used for alignment */
    SunspecPointData_kIpAddr,     /**< IP Address as an unsigned 32-bit. */
    SunspecPointData_kIpv6Addr,   /**< 16-byte IP V6 address */
    SunspecPointData_kEui48,      /**< 48-bit MAC address */
};

/**
 * @brief Enumeration of SunspecPoint access types.
 */
enum SunspecPointAccessType
{
    SunspecPointAccessType_kR,  /**< Only access Read supported */
    SunspecPointAccessType_kRW, /**< Read and Write access supported */
};

/**
 * @brief Enumeration of SunspecPoint mandatory types.
 */
enum SunspecPointMandatoryType
{
    SunspecPointMandatoryType_kM, /**< Point must be implemented */
    SunspecPointMandatoryType_kO, /**< Point can be omitted */
};

// /**
//  * @brief Enumeration of sunspec count types.
//  */
// enum SunspecCountType
// {
//     kRepeating = 0, /**< Element can be repeated 0, 1, or N number of times */
//     kFixed,         /**< Element can only be included once */
// };

/**
 * @brief Enumeration of SunspecGroup types.
 */
enum SunspecGroupType
{
    SunspecGroupType_kGroup,
    SunspecGroupType_kSync,
};
typedef std::variant<std::monostate, kSint16, kSint32, kSint64, kRaw16, kUint16, kUint32, kUint64, kAcc16, kAcc32, kAcc64, kBitfield16, kBitfield32, kBitfield64, kEnum16, kEnum32, kFloat32, kFloat64, kStringx, kSunsSf, kPad16, kIpAddr, kIpv6Addr, kEui48> SunspecPointDataVariant;
/**
 * @brief This class holds the point encoding used for the instantiation of a SunspecPoint of a SunspecModel.
 */
class SunspecPointDef
{
    using string_view = std::string_view;

public:
    /**
     *@brief Returns the id of the point.
     * @return The id of the point.
     */
    const string_view *id() const
    {
        return &id_;
    }

    /**
     *@brief Returns the id of the point that hold the count of this point.
     * @return The count_point_id of the point.
     */
    const string_view *count_point_id() const
    {
        return &count_point_id_;
    }

    /**
     *@brief Returns the id of the point.
     * @return The name of the point.
     */
    const string_view *sf_id() const
    {
        return &sf_id_;
    }
    
    /**
     *@brief Returns the id of the point.
     * @return The name of the point.
     */
    int16_t sf() const
    {
        return sf_;
    }

    /**
     *@brief Returns the uint of the point.
     * @return The uint of the point.
     */
    const string_view *units() const
    {
        return &units_;
    }

    /**
     *@brief Returns the label of the point.
     * @return The label of the point.
     */
    const string_view *label() const
    {
        return &label_;
    }

    /**
     *@brief Returns the  count type (fixed or repeating) of the point.
     * @return The count_type of the point.
     */
    uint16_t count() const
    {
        return count_;
    }

    /**
     *@brief Returns the data type of the point.
     * @return The data_type of the point.
     */
    SunspecPointData data_type() const
    {
        return data_.index() == 0 ? SunspecPointData_NONE : static_cast<SunspecPointData>(data_.index());
    }

    const kSint16 *data_as_kSint16() const
    {
        return std::get_if<kSint16>(&data_);
    }
    const kSint32 *data_as_kSint32() const
    {
        return std::get_if<kSint32>(&data_);
    }
    const kSint64 *data_as_kSint64() const
    {
        return std::get_if<kSint64>(&data_);
    }
    const kRaw16 *data_as_kRaw16() const
    {
        return std::get_if<kRaw16>(&data_);
    }
    const kUint16 *data_as_kUint16() const
    {
        return std::get_if<kUint16>(&data_);
    }
    const kUint32 *data_as_kUint32() const
    {
        return std::get_if<kUint32>(&data_);
    }
    const kUint64 *data_as_kUint64() const
    {
        return std::get_if<kUint64>(&data_);
    }
    const kAcc16 *data_as_kAcc16() const
    {
        return std::get_if<kAcc16>(&data_);
    }
    const kAcc32 *data_as_kAcc32() const
    {
        return std::get_if<kAcc32>(&data_);
    }
    const kAcc64 *data_as_kAcc64() const
    {
        return std::get_if<kAcc64>(&data_);
    }
    const kBitfield16 *data_as_kBitfield16() const
    {
        return std::get_if<kBitfield16>(&data_);
    }
    const kBitfield32 *data_as_kBitfield32() const
    {
        return std::get_if<kBitfield32>(&data_);
    }
    const kBitfield64 *data_as_kBitfield64() const
    {
        return std::get_if<kBitfield64>(&data_);
    }
    const kEnum16 *data_as_kEnum16() const
    {
        return std::get_if<kEnum16>(&data_);
    }
    const kEnum32 *data_as_kEnum32() const
    {
        return std::get_if<kEnum32>(&data_);
    }
    const kFloat32 *data_as_kFloat32() const
    {
        return std::get_if<kFloat32>(&data_);
    }
    const kFloat64 *data_as_kFloat64() const
    {
        return std::get_if<kFloat64>(&data_);
    }
    const kStringx *data_as_kStringx() const
    {
        return std::get_if<kStringx>(&data_);
    }
    const kSunsSf *data_as_kSunsSf() const
    {
        return std::get_if<kSunsSf>(&data_);
    }
    const kPad16 *data_as_kPad16() const
    {
        return std::get_if<kPad16>(&data_);
    }
    const kIpAddr *data_as_kIpAddr() const
    {
        return std::get_if<kIpAddr>(&data_);
    }
    const kIpv6Addr *data_as_kIpv6Addr() const
    {
        return std::get_if<kIpv6Addr>(&data_);
    }
    const kEui48 *data_as_kEui48() const
    {
        return std::get_if<kEui48>(&data_);
    }
    /**
     *@brief Returns the access type of the point.
     * @return The access of the point.
     */
    SunspecPointAccessType access() const
    {
        return access_;
    }

    /**
     *@brief Returns the mandatory type of the point.
     * @return The mandatory of the point.
     */
    SunspecPointMandatoryType mandatory() const
    {
        return mandatory_;
    }

    /**
     *@brief Returns the  size of the data of the point as a multiple  (sizeof(uint16_t) = size of a holding register) .
     * @return The size of the point.
     */
    uint16_t size() const;

    /**
     * @brief Class constructor.
     * @param [in] id The id of this point.
     * @param [in] count_type The count_type of this point.
     * @param [in] count_point_id The count_point_id of this point.
     * @param [in] sf_id The sf_id of this point.
     * @param [in] units The units of this point.
     * @param [in] size The size of this point.
     * @param [in] data_type The data_type of this point.
     * @param [in] access The access of this point.
     * @param [in] mandatory The mandatory of this point.
     * @param [in] label The label of this point.
     * @param [in] powerLabsId The powerLabsId of this point (This is optional).
     */
    SunspecPointDef(const char *id, uint16_t count, const char *count_point_id, const char *sf_id, const char *units, uint16_t size, SunspecPointData data_type, SunspecPointDataVariant data, SunspecPointAccessType access, SunspecPointMandatoryType mandatory, const char *label);

    /**
     * Copy constructor.
     */
    SunspecPointDef(SunspecPointDef &&point) noexcept = default;

    /**
     * Move constructor
     */
    SunspecPointDef(const SunspecPointDef &point) noexcept = default;

private:
    string_view id_;
    string_view count_point_id_;
    string_view sf_id_;
    string_view units_;
    string_view label_;
    int16_t sf_ = 0;
    uint16_t count_ = 1;
    uint16_t size_;

    // SunspecPointData data_type_ = SunspecPointData_NONE;
    SunspecPointDataVariant data_;

    SunspecPointAccessType access_ = SunspecPointAccessType_kR;

    SunspecPointMandatoryType mandatory_ = SunspecPointMandatoryType_kO;

    /**
     * Copy assignment operator.
     */
    SunspecPointDef &operator=(const SunspecPointDef &point) = delete;
    /**
     * Move assignment operator.
     */
    SunspecPointDef &operator=(SunspecPointDef &&other) = delete;
};

/**
 * @brief Represents a SunspecGroup definition.
 * This class contains parameters for the instantiation of SunspecGroup.
 */
class SunspecGroupDef
{
    using string_view = std::string_view;

public:
    /**
     * @brief Returns a reference to the vector of nested group definitions.
     * @return A const reference to the vector of SunspecGroupDef objects.
     */
    const std::vector<SunspecGroupDef> *groups() const
    {
        return &groups_;
    }

    /**
     * @brief Returns a reference to the vector of point definitions within this group.
     * @return A const reference to the vector of SunspecPointDef objects.
     */
    const std::vector<SunspecPointDef> *points() const
    {
        return &points_;
    }

    /**
     * @brief Returns the label of the group.
     * @return The label of the group.
     */
    const string_view *label() const
    {
        return &label_;
    }

    /**
     * @brief Returns the ID of the point that contains the count for this group.
     * @return The count ID of the group.
     */
    const string_view *count_point_id() const
    {
        return &count_point_id_;
    }

    /**
     * @brief Returns the name of the group.
     * @return The name of the group.
     */
    const string_view *id() const
    {
        return &id_;
    }

    /**
     * @brief Returns the count type (fixed or repeating) of the group.
     * @return The count type of the group.
     */
    uint16_t count() const
    {
        return count_;
    }

    /**
     * @brief Returns the type of the group (group or sync).
     * @return The group type.
     */
    SunspecGroupType type() const
    {
        return type_;
    }

    /**
     * @brief Class constructor for a SunspecGroupDef.
     * @param [in] id The id of the group.
     * @param [in] label The label of the group.
     * @param [in] count The count type of the group.
     * @param [in] count_point_id The ID of the point holding the count.
     * @param [in] type The type of the group (group or sync).
     * @param [in] pointsDef A vector of point definitions within the group.
     * @param [in] groupsDef A vector of nested group definitions.
     */
    SunspecGroupDef(const string_view &id, const string_view &label, uint16_t count, const string_view &count_point_id, SunspecGroupType type, std::vector<SunspecPointDef> &&pointsDef, std::vector<SunspecGroupDef> &&groupsDef);

    /**
     * @brief Copy constructor.
     */
    SunspecGroupDef(const SunspecGroupDef &point) = default;

    /**
     * @brief Move constructor.
     */
    SunspecGroupDef(SunspecGroupDef &&group) noexcept = default;

private:
    string_view id_;
    string_view label_;
    uint16_t count_ = 1;
    SunspecGroupType type_ = SunspecGroupType_kGroup;
    string_view count_point_id_;

    std::vector<SunspecPointDef> points_;
    std::vector<SunspecGroupDef> groups_;

    SunspecGroupDef &operator=(const SunspecGroupDef &point) = delete;

    SunspecGroupDef &operator=(SunspecGroupDef &&group) = delete;
};

/**
 * @brief Enumeration of SunspecModels supported.
 */
enum SunspecModelList : uint16_t
{
    SunspecModelList_kModelInvalid = 0, /**< Invalid Model Id */

    SunspecModelList_kModel1 = 1, /**< Definition for model1 */
    SunspecModelList_kModel2 = 2, /**< Definition for model2 */
    SunspecModelList_kModel3 = 3, /**< Definition for model3 */
    SunspecModelList_kModel4 = 4, /**< Definition for model4 */
    SunspecModelList_kModel5 = 5, /**< Definition for model5 */
    SunspecModelList_kModel6 = 6, /**< Definition for model6 */
    SunspecModelList_kModel7 = 7, /**< Definition for model7 */
    SunspecModelList_kModel8 = 8, /**< Definition for model8 */
    SunspecModelList_kModel9 = 9, /**< Definition for model9 */
    SunspecModelList_kModel10 = 10, /**< Definition for model10 */
    SunspecModelList_kModel11 = 11, /**< Definition for model11 */
    SunspecModelList_kModel12 = 12, /**< Definition for model12 */
    SunspecModelList_kModel13 = 13, /**< Definition for model13 */
    SunspecModelList_kModel14 = 14, /**< Definition for model14 */
    SunspecModelList_kModel15 = 15, /**< Definition for model15 */
    SunspecModelList_kModel16 = 16, /**< Definition for model16 */
    SunspecModelList_kModel17 = 17, /**< Definition for model17 */
    SunspecModelList_kModel18 = 18, /**< Definition for model18 */
    SunspecModelList_kModel19 = 19, /**< Definition for model19 */
    SunspecModelList_kModel101 = 101, /**< Definition for model101 */
    SunspecModelList_kModel102 = 102, /**< Definition for model102 */
    SunspecModelList_kModel103 = 103, /**< Definition for model103 */
    SunspecModelList_kModel111 = 111, /**< Definition for model111 */
    SunspecModelList_kModel112 = 112, /**< Definition for model112 */
    SunspecModelList_kModel113 = 113, /**< Definition for model113 */
    SunspecModelList_kModel120 = 120, /**< Definition for model120 */
    SunspecModelList_kModel121 = 121, /**< Definition for model121 */
    SunspecModelList_kModel122 = 122, /**< Definition for model122 */
    SunspecModelList_kModel123 = 123, /**< Definition for model123 */
    SunspecModelList_kModel124 = 124, /**< Definition for model124 */
    SunspecModelList_kModel125 = 125, /**< Definition for model125 */
    SunspecModelList_kModel126 = 126, /**< Definition for model126 */
    SunspecModelList_kModel127 = 127, /**< Definition for model127 */
    SunspecModelList_kModel128 = 128, /**< Definition for model128 */
    SunspecModelList_kModel129 = 129, /**< Definition for model129 */
    SunspecModelList_kModel130 = 130, /**< Definition for model130 */
    SunspecModelList_kModel131 = 131, /**< Definition for model131 */
    SunspecModelList_kModel132 = 132, /**< Definition for model132 */
    SunspecModelList_kModel133 = 133, /**< Definition for model133 */
    SunspecModelList_kModel134 = 134, /**< Definition for model134 */
    SunspecModelList_kModel135 = 135, /**< Definition for model135 */
    SunspecModelList_kModel136 = 136, /**< Definition for model136 */
    SunspecModelList_kModel137 = 137, /**< Definition for model137 */
    SunspecModelList_kModel138 = 138, /**< Definition for model138 */
    SunspecModelList_kModel139 = 139, /**< Definition for model139 */
    SunspecModelList_kModel140 = 140, /**< Definition for model140 */
    SunspecModelList_kModel141 = 141, /**< Definition for model141 */
    SunspecModelList_kModel142 = 142, /**< Definition for model142 */
    SunspecModelList_kModel143 = 143, /**< Definition for model143 */
    SunspecModelList_kModel144 = 144, /**< Definition for model144 */
    SunspecModelList_kModel145 = 145, /**< Definition for model145 */
    SunspecModelList_kModel160 = 160, /**< Definition for model160 */
    SunspecModelList_kModel201 = 201, /**< Definition for model201 */
    SunspecModelList_kModel202 = 202, /**< Definition for model202 */
    SunspecModelList_kModel203 = 203, /**< Definition for model203 */
    SunspecModelList_kModel204 = 204, /**< Definition for model204 */
    SunspecModelList_kModel211 = 211, /**< Definition for model211 */
    SunspecModelList_kModel212 = 212, /**< Definition for model212 */
    SunspecModelList_kModel213 = 213, /**< Definition for model213 */
    SunspecModelList_kModel214 = 214, /**< Definition for model214 */
    SunspecModelList_kModel220 = 220, /**< Definition for model220 */
    SunspecModelList_kModel302 = 302, /**< Definition for model302 */
    SunspecModelList_kModel303 = 303, /**< Definition for model303 */
    SunspecModelList_kModel304 = 304, /**< Definition for model304 */
    SunspecModelList_kModel305 = 305, /**< Definition for model305 */
    SunspecModelList_kModel306 = 306, /**< Definition for model306 */
    SunspecModelList_kModel307 = 307, /**< Definition for model307 */
    SunspecModelList_kModel308 = 308, /**< Definition for model308 */
    SunspecModelList_kModel401 = 401, /**< Definition for model401 */
    SunspecModelList_kModel402 = 402, /**< Definition for model402 */
    SunspecModelList_kModel403 = 403, /**< Definition for model403 */
    SunspecModelList_kModel404 = 404, /**< Definition for model404 */
    SunspecModelList_kModel501 = 501, /**< Definition for model501 */
    SunspecModelList_kModel502 = 502, /**< Definition for model502 */
    SunspecModelList_kModel601 = 601, /**< Definition for model601 */
    SunspecModelList_kModel701 = 701, /**< Definition for model701 */
    SunspecModelList_kModel702 = 702, /**< Definition for model702 */
    SunspecModelList_kModel703 = 703, /**< Definition for model703 */
    SunspecModelList_kModel704 = 704, /**< Definition for model704 */
    SunspecModelList_kModel705 = 705, /**< Definition for model705 */
    SunspecModelList_kModel706 = 706, /**< Definition for model706 */
    SunspecModelList_kModel707 = 707, /**< Definition for model707 */
    SunspecModelList_kModel708 = 708, /**< Definition for model708 */
    SunspecModelList_kModel709 = 709, /**< Definition for model709 */
    SunspecModelList_kModel710 = 710, /**< Definition for model710 */
    SunspecModelList_kModel711 = 711, /**< Definition for model711 */
    SunspecModelList_kModel712 = 712, /**< Definition for model712 */
    SunspecModelList_kModel713 = 713, /**< Definition for model713 */
    SunspecModelList_kModel714 = 714, /**< Definition for model714 */
    SunspecModelList_kModel715 = 715, /**< Definition for model715 */
    SunspecModelList_kModel801 = 801, /**< Definition for model801 */
    SunspecModelList_kModel802 = 802, /**< Definition for model802 */
    SunspecModelList_kModel803 = 803, /**< Definition for model803 */
    SunspecModelList_kModel804 = 804, /**< Definition for model804 */
    SunspecModelList_kModel805 = 805, /**< Definition for model805 */
    SunspecModelList_kModel806 = 806, /**< Definition for model806 */
    SunspecModelList_kModel807 = 807, /**< Definition for model807 */
    SunspecModelList_kModel808 = 808, /**< Definition for model808 */
    SunspecModelList_kModel809 = 809, /**< Definition for model809 */
    SunspecModelList_kModel63001 = 63001, /**< Definition for model63001 */
    SunspecModelList_kModel63002 = 63002, /**< Definition for model63002 */
    SunspecModelList_kModel64001 = 64001, /**< Definition for model64001 */
    SunspecModelList_kModel64020 = 64020, /**< Definition for model64020 */
    SunspecModelList_kModel64101 = 64101, /**< Definition for model64101 */
    SunspecModelList_kModel64111 = 64111, /**< Definition for model64111 */
    SunspecModelList_kModel64112 = 64112, /**< Definition for model64112 */
    SunspecModelList_kModel64410 = 64410, /**< Definition for model64410 */
    SunspecModelList_kModel64411 = 64411, /**< Definition for model64411 */
    SunspecModelList_kModel64412 = 64412, /**< Definition for model64412 */
    SunspecModelList_kModel64413 = 64413, /**< Definition for model64413 */
    SunspecModelList_kModel64414 = 64414, /**< Definition for model64414 */
    SunspecModelList_kModel64415 = 64415, /**< Definition for model64415 */

    SunspecModelList_kModelEnd = 0xFFFF, /**< Definition for end model Id */
};

/**
 * @brief Represents a SunspecModel definition.
 * This class contains parameters for the instantiation of SunspecModel.
 */
class SunspecModelDef
{
    using string_view = std::string_view;

public:
    /**
     * @brief Returns the top-level group definition for the model.
     * @return A const reference to the top-level group definition.
     */
    const SunspecGroupDef *group() const
    {
        return &topLevelGroupPoint_;
    }
    /**
     * @brief Returns the ID of the Sunspec model.
     * @return The model's ID.
     */
    SunspecModelList id() const
    {
        return id_;
    }
    /**
     * @brief Returns the label of the Sunspec model.
     * @return The label of the model.
     */
    const string_view *label() const
    {
        return &label_;
    }
    /**
     * @brief Retrieves a static model definition by its ID.
     * @param [in] id The ID of the Sunspec model to retrieve.
     * @return A pointer to the requested SunspecModelDef, or nullptr if not found.
     */
    static const SunspecModelDef *getModelDefinition(SunspecModelList id);

    // /**
    //  * @brief Initializes the static list of all supported model definitions.
    //  */
    // static void initList();

    // /**
    //  * @brief De-initializes the static list of models.
    //  *
    //  * This is intended to be called only in test code for cleanup.
    //  */
    // static void deinitList();

private:
    // static bool hasInitList;
    /**
     * @brief Private constructor for SunspecModelDef.
     * @param [in] _id The ID of the model.
     * @param [in] _label The label of the model.
     * @param [in] _topLevelGroupPoint The top-level group definition for the model.
     */
    SunspecModelDef(SunspecModelList _id, const string_view &_label, SunspecGroupDef &&_topLevelGroupPoint);

    SunspecModelDef(const SunspecModelDef &model) = delete;
    SunspecModelDef &operator=(const SunspecModelDef &model) = delete;
    SunspecModelDef(SunspecModelDef &&model) = delete;
    SunspecModelDef &operator=(SunspecModelDef &&model) = delete;

    SunspecModelList id_;
    string_view label_;
    SunspecGroupDef topLevelGroupPoint_;
public:
                /**
     * @brief Static definition for Model 1.
     */
    static const SunspecModelDef modelDef1;

    /**
     * @brief Static definition for Model 2.
     */
    static const SunspecModelDef modelDef2;

    /**
     * @brief Static definition for Model 3.
     */
    static const SunspecModelDef modelDef3;

    /**
     * @brief Static definition for Model 4.
     */
    static const SunspecModelDef modelDef4;

    /**
     * @brief Static definition for Model 5.
     */
    static const SunspecModelDef modelDef5;

    /**
     * @brief Static definition for Model 6.
     */
    static const SunspecModelDef modelDef6;

    /**
     * @brief Static definition for Model 7.
     */
    static const SunspecModelDef modelDef7;

    /**
     * @brief Static definition for Model 8.
     */
    static const SunspecModelDef modelDef8;

    /**
     * @brief Static definition for Model 9.
     */
    static const SunspecModelDef modelDef9;

    /**
     * @brief Static definition for Model 10.
     */
    static const SunspecModelDef modelDef10;

    /**
     * @brief Static definition for Model 11.
     */
    static const SunspecModelDef modelDef11;

    /**
     * @brief Static definition for Model 12.
     */
    static const SunspecModelDef modelDef12;

    /**
     * @brief Static definition for Model 13.
     */
    static const SunspecModelDef modelDef13;

    /**
     * @brief Static definition for Model 14.
     */
    static const SunspecModelDef modelDef14;

    /**
     * @brief Static definition for Model 15.
     */
    static const SunspecModelDef modelDef15;

    /**
     * @brief Static definition for Model 16.
     */
    static const SunspecModelDef modelDef16;

    /**
     * @brief Static definition for Model 17.
     */
    static const SunspecModelDef modelDef17;

    /**
     * @brief Static definition for Model 18.
     */
    static const SunspecModelDef modelDef18;

    /**
     * @brief Static definition for Model 19.
     */
    static const SunspecModelDef modelDef19;

    /**
     * @brief Static definition for Model 101.
     */
    static const SunspecModelDef modelDef101;

    /**
     * @brief Static definition for Model 102.
     */
    static const SunspecModelDef modelDef102;

    /**
     * @brief Static definition for Model 103.
     */
    static const SunspecModelDef modelDef103;

    /**
     * @brief Static definition for Model 111.
     */
    static const SunspecModelDef modelDef111;

    /**
     * @brief Static definition for Model 112.
     */
    static const SunspecModelDef modelDef112;

    /**
     * @brief Static definition for Model 113.
     */
    static const SunspecModelDef modelDef113;

    /**
     * @brief Static definition for Model 120.
     */
    static const SunspecModelDef modelDef120;

    /**
     * @brief Static definition for Model 121.
     */
    static const SunspecModelDef modelDef121;

    /**
     * @brief Static definition for Model 122.
     */
    static const SunspecModelDef modelDef122;

    /**
     * @brief Static definition for Model 123.
     */
    static const SunspecModelDef modelDef123;

    /**
     * @brief Static definition for Model 124.
     */
    static const SunspecModelDef modelDef124;

    /**
     * @brief Static definition for Model 125.
     */
    static const SunspecModelDef modelDef125;

    /**
     * @brief Static definition for Model 126.
     */
    static const SunspecModelDef modelDef126;

    /**
     * @brief Static definition for Model 127.
     */
    static const SunspecModelDef modelDef127;

    /**
     * @brief Static definition for Model 128.
     */
    static const SunspecModelDef modelDef128;

    /**
     * @brief Static definition for Model 129.
     */
    static const SunspecModelDef modelDef129;

    /**
     * @brief Static definition for Model 130.
     */
    static const SunspecModelDef modelDef130;

    /**
     * @brief Static definition for Model 131.
     */
    static const SunspecModelDef modelDef131;

    /**
     * @brief Static definition for Model 132.
     */
    static const SunspecModelDef modelDef132;

    /**
     * @brief Static definition for Model 133.
     */
    static const SunspecModelDef modelDef133;

    /**
     * @brief Static definition for Model 134.
     */
    static const SunspecModelDef modelDef134;

    /**
     * @brief Static definition for Model 135.
     */
    static const SunspecModelDef modelDef135;

    /**
     * @brief Static definition for Model 136.
     */
    static const SunspecModelDef modelDef136;

    /**
     * @brief Static definition for Model 137.
     */
    static const SunspecModelDef modelDef137;

    /**
     * @brief Static definition for Model 138.
     */
    static const SunspecModelDef modelDef138;

    /**
     * @brief Static definition for Model 139.
     */
    static const SunspecModelDef modelDef139;

    /**
     * @brief Static definition for Model 140.
     */
    static const SunspecModelDef modelDef140;

    /**
     * @brief Static definition for Model 141.
     */
    static const SunspecModelDef modelDef141;

    /**
     * @brief Static definition for Model 142.
     */
    static const SunspecModelDef modelDef142;

    /**
     * @brief Static definition for Model 143.
     */
    static const SunspecModelDef modelDef143;

    /**
     * @brief Static definition for Model 144.
     */
    static const SunspecModelDef modelDef144;

    /**
     * @brief Static definition for Model 145.
     */
    static const SunspecModelDef modelDef145;

    /**
     * @brief Static definition for Model 160.
     */
    static const SunspecModelDef modelDef160;

    /**
     * @brief Static definition for Model 201.
     */
    static const SunspecModelDef modelDef201;

    /**
     * @brief Static definition for Model 202.
     */
    static const SunspecModelDef modelDef202;

    /**
     * @brief Static definition for Model 203.
     */
    static const SunspecModelDef modelDef203;

    /**
     * @brief Static definition for Model 204.
     */
    static const SunspecModelDef modelDef204;

    /**
     * @brief Static definition for Model 211.
     */
    static const SunspecModelDef modelDef211;

    /**
     * @brief Static definition for Model 212.
     */
    static const SunspecModelDef modelDef212;

    /**
     * @brief Static definition for Model 213.
     */
    static const SunspecModelDef modelDef213;

    /**
     * @brief Static definition for Model 214.
     */
    static const SunspecModelDef modelDef214;

    /**
     * @brief Static definition for Model 220.
     */
    static const SunspecModelDef modelDef220;

    /**
     * @brief Static definition for Model 302.
     */
    static const SunspecModelDef modelDef302;

    /**
     * @brief Static definition for Model 303.
     */
    static const SunspecModelDef modelDef303;

    /**
     * @brief Static definition for Model 304.
     */
    static const SunspecModelDef modelDef304;

    /**
     * @brief Static definition for Model 305.
     */
    static const SunspecModelDef modelDef305;

    /**
     * @brief Static definition for Model 306.
     */
    static const SunspecModelDef modelDef306;

    /**
     * @brief Static definition for Model 307.
     */
    static const SunspecModelDef modelDef307;

    /**
     * @brief Static definition for Model 308.
     */
    static const SunspecModelDef modelDef308;

    /**
     * @brief Static definition for Model 401.
     */
    static const SunspecModelDef modelDef401;

    /**
     * @brief Static definition for Model 402.
     */
    static const SunspecModelDef modelDef402;

    /**
     * @brief Static definition for Model 403.
     */
    static const SunspecModelDef modelDef403;

    /**
     * @brief Static definition for Model 404.
     */
    static const SunspecModelDef modelDef404;

    /**
     * @brief Static definition for Model 501.
     */
    static const SunspecModelDef modelDef501;

    /**
     * @brief Static definition for Model 502.
     */
    static const SunspecModelDef modelDef502;

    /**
     * @brief Static definition for Model 601.
     */
    static const SunspecModelDef modelDef601;

    /**
     * @brief Static definition for Model 701.
     */
    static const SunspecModelDef modelDef701;

    /**
     * @brief Static definition for Model 702.
     */
    static const SunspecModelDef modelDef702;

    /**
     * @brief Static definition for Model 703.
     */
    static const SunspecModelDef modelDef703;

    /**
     * @brief Static definition for Model 704.
     */
    static const SunspecModelDef modelDef704;

    /**
     * @brief Static definition for Model 705.
     */
    static const SunspecModelDef modelDef705;

    /**
     * @brief Static definition for Model 706.
     */
    static const SunspecModelDef modelDef706;

    /**
     * @brief Static definition for Model 707.
     */
    static const SunspecModelDef modelDef707;

    /**
     * @brief Static definition for Model 708.
     */
    static const SunspecModelDef modelDef708;

    /**
     * @brief Static definition for Model 709.
     */
    static const SunspecModelDef modelDef709;

    /**
     * @brief Static definition for Model 710.
     */
    static const SunspecModelDef modelDef710;

    /**
     * @brief Static definition for Model 711.
     */
    static const SunspecModelDef modelDef711;

    /**
     * @brief Static definition for Model 712.
     */
    static const SunspecModelDef modelDef712;

    /**
     * @brief Static definition for Model 713.
     */
    static const SunspecModelDef modelDef713;

    /**
     * @brief Static definition for Model 714.
     */
    static const SunspecModelDef modelDef714;

    /**
     * @brief Static definition for Model 715.
     */
    static const SunspecModelDef modelDef715;

    /**
     * @brief Static definition for Model 801.
     */
    static const SunspecModelDef modelDef801;

    /**
     * @brief Static definition for Model 802.
     */
    static const SunspecModelDef modelDef802;

    /**
     * @brief Static definition for Model 803.
     */
    static const SunspecModelDef modelDef803;

    /**
     * @brief Static definition for Model 804.
     */
    static const SunspecModelDef modelDef804;

    /**
     * @brief Static definition for Model 805.
     */
    static const SunspecModelDef modelDef805;

    /**
     * @brief Static definition for Model 806.
     */
    static const SunspecModelDef modelDef806;

    /**
     * @brief Static definition for Model 807.
     */
    static const SunspecModelDef modelDef807;

    /**
     * @brief Static definition for Model 808.
     */
    static const SunspecModelDef modelDef808;

    /**
     * @brief Static definition for Model 809.
     */
    static const SunspecModelDef modelDef809;

    /**
     * @brief Static definition for Model 63001.
     */
    static const SunspecModelDef modelDef63001;

    /**
     * @brief Static definition for Model 63002.
     */
    static const SunspecModelDef modelDef63002;

    /**
     * @brief Static definition for Model 64001.
     */
    static const SunspecModelDef modelDef64001;

    /**
     * @brief Static definition for Model 64020.
     */
    static const SunspecModelDef modelDef64020;

    /**
     * @brief Static definition for Model 64101.
     */
    static const SunspecModelDef modelDef64101;

    /**
     * @brief Static definition for Model 64111.
     */
    static const SunspecModelDef modelDef64111;

    /**
     * @brief Static definition for Model 64112.
     */
    static const SunspecModelDef modelDef64112;

    /**
     * @brief Static definition for Model 64410.
     */
    static const SunspecModelDef modelDef64410;

    /**
     * @brief Static definition for Model 64411.
     */
    static const SunspecModelDef modelDef64411;

    /**
     * @brief Static definition for Model 64412.
     */
    static const SunspecModelDef modelDef64412;

    /**
     * @brief Static definition for Model 64413.
     */
    static const SunspecModelDef modelDef64413;

    /**
     * @brief Static definition for Model 64414.
     */
    static const SunspecModelDef modelDef64414;

    /**
     * @brief Static definition for Model 64415.
     */
    static const SunspecModelDef modelDef64415;
};