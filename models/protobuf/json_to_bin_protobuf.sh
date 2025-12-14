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

python3 $ROOT_DIR/models/protobuf/model_to_protobuf_json.py

${PROTOBUF_COMPILER} --python_out="$ROOT_DIR/models/protobuf" -I=$ROOT_DIR/models/protobuf $ROOT_DIR/models/protobuf/sunspec_model_definition.proto
source $ROOT_DIR/models/protobuf/protobuf/bin/activate
mkdir -p $ROOT_DIR/models/protobuf/binary
for model in {1..65535}
do  
    if [ -f "$ROOT_DIR/models/protobuf/json/model_${model}.json" ];
    then    
        python3 $ROOT_DIR/models/protobuf/sunspec_protobuf_json_to_binary.py "$ROOT_DIR/models/protobuf/json/model_${model}.json" $ROOT_DIR/models/protobuf/binary/model_${model}.bin
        # ${PROTOBUF_COMPILER} --binary -o models/protobuf/binary sunspec_model_definition.fbs "models/protobuf/json/model_${model}.json"
        xxd -i -n modelDefinition${model} models/protobuf/binary/model_${model}.bin  > src/models/protobuf/protobuf_array_model_${model}.cpp
    fi
done
# ${PROTOBUF_COMPILER} -o models/protobuf/ATT  --annotate  sunspec_model_definition.fbs models/protobuf/binary/model_1.bin
