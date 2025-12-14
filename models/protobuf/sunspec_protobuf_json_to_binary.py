from google.protobuf import json_format
import sunspec_model_definition_pb2

import sys

input_file_name = sys.argv[1]
output_file_name = sys.argv[2]

msg = sunspec_model_definition_pb2.SunspecModelDef()
json_format.Parse(open(input_file_name).read(), msg)
open(output_file_name, "w")
open(output_file_name, "wb").write(msg.SerializeToString())
