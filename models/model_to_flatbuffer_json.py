import json
import ctypes

def get_flatbuffer_data_type(type):
    match type:
        case "int16":
            return "kSint16"
        case "int32" :
            return  "kSint32"
        case "int64" :
            return "kSint64"
        case "raw16" :
            return "kRaw16"
        case "uint16" :
            return "kUint16"
        case "uint32" :
            return "kUint32"
        case "uint64" :
            return "kUint64"
        case "acc16" :
            return "kAcc16"
        case "acc32" :
            return "KAcc32"
        case "acc64" :
            return "kAcc64"
        case "bitfield16" :
            return "kBitfield16"
        case "bitfield32" :
            return "kBitfield32"
        case "bitfield64" :
            return "kBitfield64"
        case "enum16" :
            return "kEnum16"
        case "enum32" :
            return "kEnum32"
        case "float32" :
            return "kFloat32"
        case "float64" :
            return "kFloat64"
        case "string" :
            return "kStringx"
        case "sunssf" :
            return "kSunsSf"
        case "pad" :
            return "kPad16"
        case "ipaddr" :
            return "kIpAddr"
        case "ipv6addr" :
            return "kIpv6Addr"
        case "eui48" :
            return "kEui48" 
        case _:
            raise ValueError("Invalid Type")
        
def get_unimplemented_value(type):
    match type:
        case "int16":
            return ctypes.c_int16(0x8000).value
        case "int32" :
            return  ctypes.c_int16(0x80000000).value
        case "int64" :
            return ctypes.c_int16(0x8000000000000000).value
        case "raw16" :
            return 0x0000
        case "uint16" :
            return 0xFFFF
        case "uint32" :
            return 0xFFFFFFFF
        case "uint64" :
            return 0xFFFFFFFFFFFFFFFF 
        case "acc16" :
            return 0x0000
        case "acc32" :
            return 0x00000000
        case "acc64" :
            return 0x0000000000000000
        case "bitfield16" :
            return 0xFFFF
        case "bitfield32" :
            return 0xFFFFFFFF
        case "bitfield64" :
            return 0xFFFFFFFFFFFFFFFF
        case "enum16" :
            return 0xFFFF
        case "enum32" :
            return 0xFFFFFFFF
        case "float32" :
            return 0x7FC00000
        case "float64" :
            return ctypes.c_float(0x7FF8000000000000).value
        case "string" :
            return None
        case "sunssf" :
            return 0x8000
        case "pad" :
            return 0x8000
        case "ipaddr" :
            return 0x00000000
        case "ipv6addr" :
            return "kIpv6Addr"
        case "eui48" :
            return "kEui48" 
        case _:
            raise ValueError("Invalid Type")
        
def get_flatbuffer_data(type, value):
    if value == None:
        return None
        # value = get_unimplemented_value(type)
        # IpAddr and Ipv6Addr and Eui48 are not implemented here
    data = {}
    data["value"] = value
    return data
   
            
def get_flatbuffer_size(size, type):
    match type:
        case "int16":
            return 1
        case "int32" :
            return  2
        case "int64" :
            return 4
        case "raw16" :
            return 1
        case "uint16" :
            return 1
        case "uint32" :
            return 2
        case "uint64" :
            return 4
        case "acc16" :
            return 1
        case "acc32" :
            return 2
        case "acc64" :
            return 4
        case "bitfield16" :
            return 1
        case "bitfield32" :
            return 2
        case "bitfield64" :
            return 4
        case "enum16" :
            return 1
        case "enum32" :
            return 2
        case "float32" :
            return 2
        case "float64" :
            return 4
        case "string" :
            return size
        case "sunssf" :
            return 1
        case "pad" :
            return 1
        case "ipaddr" :
            return 2
        case "ipv6addr" :
            return 8
        case "eui48" :
            return 3
        case _:
            raise ValueError("Invalid Type")
    
def get_flatbuffer_access(access):
    match access:
        case "RW":
            return "kRW"
        case "R" | None:
            return "kR"
        case _:
            raise ValueError("Invalid Access")
            
def get_flatbuffer_mandatory(mandatory):
    match mandatory:
        case "M":
            return "kM"
        case "O" | None:
            return "kO"
        case _:
            raise ValueError("Invalid Mandatory")      
            
def get_flatbuffer_sf(sf):
    if(isinstance(sf, int)):
        return sf
    else:
        return 0

def get_flatbuffer_sf_id(sf_id):
    if(isinstance(sf_id, str)):
        return sf_id
    else:
        return None
    
def get_flatbuffer_count(count):
    if(isinstance(count, str)):
        return 0
    elif count == None:
        return 1
    else:
        raise ValueError("Invalid Count")
    
def get_flatbuffer_count_id(count_id):
    if(isinstance(count_id, str)):
        return count_id
    elif count_id == None:
        return None
    else:
        raise ValueError("Invalid Count_id")
    
def get_flatbuffer_point(point):
    new_point = {}
    new_point["id"] = point["name"]
    new_point["data_type"] =get_flatbuffer_data_type( point["type"])
    new_point["data"] =get_flatbuffer_data( point["type"], point["value"] if "value" in  point else None)
    new_point["count"] =get_flatbuffer_count(point["count"] if "count" in  point else None)
    new_point["count_point_id"] = get_flatbuffer_count_id(point["count"] if "count" in  point else None)
    new_point["size"] =get_flatbuffer_size(point["size"], point["type"]) 
    new_point["sf"] = get_flatbuffer_sf(point["sf"] if "sf" in point  else None )
    new_point["sf_id"] =  get_flatbuffer_sf_id(point["sf"] if "sf" in point  else None)
    new_point["units"] = point["units"] if "units" in point else None
    new_point["access"] = get_flatbuffer_access(point["access"] if "access" in point else None )
    new_point["mandatory"] = get_flatbuffer_mandatory(point["mandatory"] if "mandatory" in point else None) 
    new_point["label"] =point["label"] if "label" in point else None
    
    return new_point

def get_flatbuffer_group_type(type):
    match type:
        case "group":
            return "kGroup"
        case "sync":
            return "kSync"
        case _:
            raise ValueError("Invalid Group Type")      
 
    
def get_flatbuffer_group(group):
    new_group = {}
    new_group["id"] = group["name"]
    new_group["type"] = get_flatbuffer_group_type( group["type"])
    new_group["count"] = get_flatbuffer_count(group["count"] if "count" in  group else None)
    new_group["count_point_id"] =get_flatbuffer_count_id(group["count"] if "count" in  group else None)
    new_group["points"] = []
    for point in group["points"]:
        new_group["points"].append(get_flatbuffer_point(point))
    new_group["groups"] = []
    if("groups" in group):
        for group in group["groups"]:
            new_group["groups"].append(get_flatbuffer_group(group))
    new_group["label"] = group["label"] if "label" in  group else None
    return new_group
        
    

# model_ids = [1, 101, 102, 103, 111, 112, 113, 120, 126, 160]
model_ids = [id for id in range(0xffff)]
for model_id in model_ids:
    new_model = {}
    
    try:
        open(f"models/json/model_{model_id}.json", 'rt') 
    except:
        print(f"Error opening file model_{model_id}.json")
        continue
        
    print(f"Model {model_id}")
    with open(f"models/json/model_{model_id}.json", 'rt') as file:
        model = json.load(file)
        
    new_model["id"] = model["id"]
    new_model["group"] = get_flatbuffer_group(model["group"])

    with open(f"models/flatbuffer/json/model_{model_id}.json", "wt") as file:
        json.dump(new_model, file, indent= 4)