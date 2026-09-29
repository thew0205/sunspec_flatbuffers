#!/bin/bash
set -e
FLATC_COMPILER="${HOME}/Documents/flatbuffers/build/flatc"
if [[ ! -f ${FLATC_COMPILER} ]]; then
    echo "Error no Flatbuffer compiler found"
    exit 1
fi

mkdir -p models/flatbuffer/json
mkdir -p models/flatbuffer/annotate_binary

${FLATC_COMPILER} --cpp -o include/adapters/flatbuffers sunspec_model_definition.fbs 
python3 models/model_to_flatbuffer_json.py
echo "" > include/adapters/flatbuffers/flatbuffers_model_definition_declaration.h
for model in {1..65535}
do  
    if [ -f "models/flatbuffer/json/model_${model}.json" ];
    then    
        ${FLATC_COMPILER} --binary -o models/flatbuffer/binary sunspec_model_definition.fbs "models/flatbuffer/json/model_${model}.json"
        # xxd -i emits "unsigned char modelDefinitionN[] = {...};" with no
        xxd -i -n modelDefinition${model} models/flatbuffer/binary/model_${model}.bin | sed 's/^unsigned char/extern const unsigned char/' > src/models/flatbuffers/flatbuffers_array_model_${model}.cpp
    fi
    echo "extern const unsigned char modelDefinition${model}[];" >> include/adapters/flatbuffers/flatbuffers_model_definition_declaration.h

done
${FLATC_COMPILER} -o models/flatbuffer/ATT  --annotate  sunspec_model_definition.fbs models/flatbuffer/binary/model_1.bin
