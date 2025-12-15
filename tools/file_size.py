import os
from pathlib import Path
import csv

i = 0
sum = 0
model_ids = [id for id in range(0xffff)]


protobuf_dir = "/home/busoye_tm/Documents/matthew/projects/sunspec_flatbuffer/models/protobuf/binary"
nakedbytes_dir = "/home/busoye_tm/Documents/matthew/projects/sunspec_flatbuffer/models/nakedbytes/binary"
flatbuffers_dir = "/home/busoye_tm/Documents/matthew/projects/sunspec_flatbuffer/models/flatbuffers/binary"


with open(Path(f"{__file__}.result.txt"), "w") as file:
    csv_writer = csv.writer(file)
    csv_writer.writerow(["s_n", "model_no", "protobuf_size", "nakedbytes_size", "flatbuffer_size", "proto_naked", "proto_flat"])
    
    for id in model_ids:
        try:
            model_file_name = Path(nakedbytes_dir).joinpath(f"model_{id}.bin")
            open(model_file_name, 'r')
        except:
            continue
        i += 1
        nakedbytes_size = os.path.getsize(Path(nakedbytes_dir).joinpath(f"model_{id}.bin"))
        flatbuffer_size = os.path.getsize(Path(flatbuffers_dir).joinpath(f"model_{id}.bin"))
        protobuf_size = os.path.getsize(Path(protobuf_dir).joinpath(f"model_{id}.bin"))
        print(f" {protobuf_size}\t {nakedbytes_size}\t {flatbuffer_size}")
        csv_writer.writerow([i, id, protobuf_size, nakedbytes_size, flatbuffer_size, nakedbytes_size-protobuf_size, flatbuffer_size-protobuf_size])
        # print(f"model {id}: nakedbytes: {nakedbytes_size}\t flatbuffer: {flatbuffer_size}\t difference: {flatbuffer_size - nakedbytes_size}\t %decrement: {int((flatbuffer_size - nakedbytes_size)/ flatbuffer_size * 100)}%\t  %increment: {int((flatbuffer_size - nakedbytes_size)/ nakedbytes_size * 100)}%")
        # sum += ((flatbuffer_size - nakedbytes_size)/ flatbuffer_size * 100)   
print("model count is ", i, "mean reduction", sum/i)