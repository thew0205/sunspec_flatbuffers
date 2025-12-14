#!/bin/bash
set -e

ROOT_DIR=$1

NAKEDBYTES_SCRIPT=/home/busoye_tm/Documents/matthew/projects/nakedbytes/code_implementation/nakedbytes.py

mkdir -p $ROOT_DIR/models/nakedbytes/json
mkdir -p $ROOT_DIR/models/nakedbytes/annotate_binary

python3 $ROOT_DIR/models/nakedbytes/model_to_nakedbytes_json.py

python3 $NAKEDBYTES_SCRIPT $ROOT_DIR/models/nakedbytes/sunspec_model_definition.json --cpp $ROOT_DIR/include/adapters/nakedbytes

for model in {1..65535}
do  
    if [ -f "$ROOT_DIR/models/nakedbytes/json/model_${model}.json"  ]
    then
        python3 $NAKEDBYTES_SCRIPT $ROOT_DIR/models/nakedbytes/sunspec_model_definition.json --binary "$ROOT_DIR/models/nakedbytes/json/model_${model}.json" --outbin $ROOT_DIR/models/nakedbytes/binary 
        xxd -i -n modelDefinition${model} $ROOT_DIR/models/nakedbytes/binary/model_${model}.bin   > $ROOT_DIR/src/models/nakedbytes/nakedbytes_array_model_${model}.cpp
    fi
done