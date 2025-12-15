#!/bin/bash
set -e

ROOT_DIR=$1
FLATC_COMPILER=flatc
# if [[ ! -f ${FLATC_COMPILER} ]]; then
#     echo "Error no flatbuffers compiler found"
#     exit 1
# fi

mkdir -p $ROOT_DIR/models/flatbuffers/json
mkdir -p $ROOT_DIR/models/flatbuffers/annotate_binary

${FLATC_COMPILER} --cpp -o $ROOT_DIR/include/adapters/flatbuffers $ROOT_DIR/models/flatbuffers/sunspec_model_definition.fbs 

python3 $ROOT_DIR/models/flatbuffers/model_to_flatbuffers_json.py

for model in {1..65535}
do  
    if [ -f "$ROOT_DIR/models/flatbuffers/json/model_${model}.json" ];
    then    
        ${FLATC_COMPILER} --binary -o $ROOT_DIR/models/flatbuffers/binary $ROOT_DIR/models/flatbuffers/sunspec_model_definition.fbs "$ROOT_DIR/models/flatbuffers/json/model_${model}.json"
        
        xxd -i -n modelDefinition${model} $ROOT_DIR/models/flatbuffers/binary/model_${model}.bin  > $ROOT_DIR/src/models/flatbuffers/flatbuffers_array_model_${model}.cpp

        sed -i 's/unsigned char/const unsigned char/g' "$ROOT_DIR/src/models/flatbuffers/flatbuffers_array_model_${model}.cpp"
        sed -i '1i#include "array_models_externs.h"\n' "$ROOT_DIR/src/models/flatbuffers/flatbuffers_array_model_${model}.cpp"

    fi
done
# ${FLATC_COMPILER} -o $ROOT_DIR/models/flatbuffers/ATT  --annotate  $ROOT_DIR/models/flatbuffers/sunspec_model_definition.fbs $ROOT_DIR/models/flatbuffers/binary/model_1.bin
