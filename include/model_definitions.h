#pragma once

#include "sunspec_model_definition_generated.h"

extern const unsigned char modelDefinition1[];
extern const unsigned char modelDefinition112[];
extern const unsigned char modelDefinition113[];
extern const unsigned char modelDefinition160[];

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