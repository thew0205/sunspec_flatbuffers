#!/bin/bash
set -e

ROOT_DIR=$1

PROTOBUF_COMPILER="protoc"
# if [[ ! -f ${PROTOBUF_COMPILER} ]]; then
#     echo "Error no Protobuf compiler found"
#     exit 1
# fi

mkdir -p $ROOT_DIR/models/protobuf/json
mkdir -p $ROOT_DIR/models/protobuf/annotate_binary

${PROTOBUF_COMPILER} --cpp_out="$ROOT_DIR/include/adapters/protobuf" -I=$ROOT_DIR/models/protobuf $ROOT_DIR/models/protobuf/sunspec_model_definition.proto

source $ROOT_DIR/models/protobuf/protobuf/bin/activate 

${PROTOBUF_COMPILER} --plugin=protoc-gen-nanopb=$ROOT_DIR/third_party/nanopb/generator/protoc-gen-nanopb --nanopb_out=$ROOT_DIR/include/adapters/nanopb -I=$ROOT_DIR/models/protobuf $ROOT_DIR/models/protobuf/sunspec_model_definition.proto

deactivate

python3 $ROOT_DIR/models/protobuf/model_to_protobuf_json.py

${PROTOBUF_COMPILER} --python_out="$ROOT_DIR/models/protobuf" -I=$ROOT_DIR/models/protobuf $ROOT_DIR/models/protobuf/sunspec_model_definition.proto
source $ROOT_DIR/models/protobuf/protobuf/bin/activate
mkdir -p $ROOT_DIR/models/protobuf/binary
for model in {1..65535}
do  
    if [ -f "$ROOT_DIR/models/protobuf/json/model_${model}.json" ];
    then    
        python3 $ROOT_DIR/models/protobuf/sunspec_protobuf_json_to_binary.py "$ROOT_DIR/models/protobuf/json/model_${model}.json" $ROOT_DIR/models/protobuf/binary/model_${model}.bin

        xxd -i -n modelDefinition${model} $ROOT_DIR/models/protobuf/binary/model_${model}.bin  > $ROOT_DIR/src/models/protobuf/protobuf_array_model_${model}.cpp

        sed -i 's/unsigned char/const unsigned char/g' "$ROOT_DIR/src/models/protobuf/protobuf_array_model_${model}.cpp"

        sed -i '1i#include "array_models_externs.h"\n' "$ROOT_DIR/src/models/protobuf/protobuf_array_model_${model}.cpp"


    fi
done
