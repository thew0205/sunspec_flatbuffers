#pragma once

#include "sunspec_model_definition_generated.h"
#include "generated/model_definitions_generated.h"

#ifdef _INCLUDE_SUNSPEC_MODEL_1_
extern const unsigned char modelDefinition1[];
#endif

#ifdef _INCLUDE_SUNSPEC_MODEL_2_
extern const unsigned char modelDefinition2[];
#endif

#ifdef _INCLUDE_SUNSPEC_MODEL_3_
extern const unsigned char modelDefinition3[];
#endif

#ifdef _INCLUDE_SUNSPEC_MODEL_4_
extern const unsigned char modelDefinition4[];
#endif

#ifdef _INCLUDE_SUNSPEC_MODEL_5_
extern const unsigned char modelDefinition5[];
#endif

#ifdef _INCLUDE_SUNSPEC_MODEL_6_
extern const unsigned char modelDefinition6[];
#endif

#ifdef _INCLUDE_SUNSPEC_MODEL_7_
extern const unsigned char modelDefinition7[];
#endif

#ifdef _INCLUDE_SUNSPEC_MODEL_8_
extern const unsigned char modelDefinition8[];
#endif

#ifdef _INCLUDE_SUNSPEC_MODEL_9_
extern const unsigned char modelDefinition9[];
#endif

#ifdef _INCLUDE_SUNSPEC_MODEL_10_
extern const unsigned char modelDefinition10[];
#endif

#ifdef _INCLUDE_SUNSPEC_MODEL_11_
extern const unsigned char modelDefinition11[];
#endif

#ifdef _INCLUDE_SUNSPEC_MODEL_12_
extern const unsigned char modelDefinition12[];
#endif

#ifdef _INCLUDE_SUNSPEC_MODEL_13_
extern const unsigned char modelDefinition13[];
#endif

#ifdef _INCLUDE_SUNSPEC_MODEL_14_
extern const unsigned char modelDefinition14[];
#endif

#ifdef _INCLUDE_SUNSPEC_MODEL_15_
extern const unsigned char modelDefinition15[];
#endif

#ifdef _INCLUDE_SUNSPEC_MODEL_16_
extern const unsigned char modelDefinition16[];
#endif

#ifdef _INCLUDE_SUNSPEC_MODEL_17_
extern const unsigned char modelDefinition17[];
#endif

#ifdef _INCLUDE_SUNSPEC_MODEL_18_
extern const unsigned char modelDefinition18[];
#endif

#ifdef _INCLUDE_SUNSPEC_MODEL_19_
extern const unsigned char modelDefinition19[];
#endif

#ifdef _INCLUDE_SUNSPEC_MODEL_101_
extern const unsigned char modelDefinition101[];
#endif

#ifdef _INCLUDE_SUNSPEC_MODEL_102_
extern const unsigned char modelDefinition102[];
#endif

#ifdef _INCLUDE_SUNSPEC_MODEL_103_
extern const unsigned char modelDefinition103[];
#endif

#ifdef _INCLUDE_SUNSPEC_MODEL_111_
extern const unsigned char modelDefinition111[];
#endif

#ifdef _INCLUDE_SUNSPEC_MODEL_112_
extern const unsigned char modelDefinition112[];
#endif

#ifdef _INCLUDE_SUNSPEC_MODEL_113_
extern const unsigned char modelDefinition113[];
#endif
#ifdef _INCLUDE_SUNSPEC_MODEL_120_
extern const unsigned char modelDefinition120[];
#endif
#ifdef _INCLUDE_SUNSPEC_MODEL_121_
extern const unsigned char modelDefinition121[];
#endif
#ifdef _INCLUDE_SUNSPEC_MODEL_122_
extern const unsigned char modelDefinition122[];
#endif
#ifdef _INCLUDE_SUNSPEC_MODEL_123_
extern const unsigned char modelDefinition123[];
#endif
#ifdef _INCLUDE_SUNSPEC_MODEL_124_
extern const unsigned char modelDefinition124[];
#endif
#ifdef _INCLUDE_SUNSPEC_MODEL_125_
extern const unsigned char modelDefinition125[];
#endif
#ifdef _INCLUDE_SUNSPEC_MODEL_126_
extern const unsigned char modelDefinition126[];
#endif
#ifdef _INCLUDE_SUNSPEC_MODEL_127_
extern const unsigned char modelDefinition127[];
#endif
#ifdef _INCLUDE_SUNSPEC_MODEL_128_
extern const unsigned char modelDefinition128[];
#endif
#ifdef _INCLUDE_SUNSPEC_MODEL_129_
extern const unsigned char modelDefinition129[];
#endif
#ifdef _INCLUDE_SUNSPEC_MODEL_130_
extern const unsigned char modelDefinition130[];
#endif

#ifdef _INCLUDE_SUNSPEC_MODEL_131_
extern const unsigned char modelDefinition131[];
#endif

#ifdef _INCLUDE_SUNSPEC_MODEL_132_
extern const unsigned char modelDefinition132[];
#endif

#ifdef _INCLUDE_SUNSPEC_MODEL_133_
extern const unsigned char modelDefinition133[];
#endif

#ifdef _INCLUDE_SUNSPEC_MODEL_134_
extern const unsigned char modelDefinition134[];
#endif

#ifdef _INCLUDE_SUNSPEC_MODEL_135_
extern const unsigned char modelDefinition135[];
#endif

#ifdef _INCLUDE_SUNSPEC_MODEL_136_
extern const unsigned char modelDefinition136[];
#endif

#ifdef _INCLUDE_SUNSPEC_MODEL_137_
extern const unsigned char modelDefinition137[];
#endif

#ifdef _INCLUDE_SUNSPEC_MODEL_138_
extern const unsigned char modelDefinition138[];
#endif

#ifdef _INCLUDE_SUNSPEC_MODEL_139_
extern const unsigned char modelDefinition139[];
#endif

#ifdef _INCLUDE_SUNSPEC_MODEL_140_
extern const unsigned char modelDefinition140[];
#endif

#ifdef _INCLUDE_SUNSPEC_MODEL_141_
extern const unsigned char modelDefinition141[];
#endif

#ifdef _INCLUDE_SUNSPEC_MODEL_142_
extern const unsigned char modelDefinition142[];
#endif

#ifdef _INCLUDE_SUNSPEC_MODEL_143_
extern const unsigned char modelDefinition143[];
#endif

#ifdef _INCLUDE_SUNSPEC_MODEL_144_
extern const unsigned char modelDefinition144[];
#endif


#ifdef _INCLUDE_SUNSPEC_MODEL_160_
extern const unsigned char modelDefinition160[];
#endif



namespace Sunspec
{
    /**
     * @brief Retrieves the model definition for a given model ID.
     * This function looks up the model definition based on the provided model ID.
     * @param [in] id The ID of the model to look up.
     * @return A pointer to the SunspecModelDef if found, or nullptr if not supported.
     */
    const SunspecModelDef *getModelDefinition(SunspecModelList id);

} // namespace Sunspec