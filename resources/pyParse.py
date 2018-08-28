import pytmx
from sys import argv

if len(argv) == 3:
    path = argv[1]
    outPath = "./" + argv[2] + "/"
else:
    path = "testmap2.txt"

tmxdata = pytmx.TiledMap(path)
terrain_anims = dict()
animation_data = []

with open(outPath + "collData.txt", "w") as f:
    output = ""
    for tile_object in tmxdata.objects:
        output += f"{tile_object.type} {tile_object.x} {tile_object.y} {tile_object.width} {tile_object.height} "
        if tile_object.type == "animated_terrain":
            if tile_object.properties["texture_source"] not in terrain_anims:
                terrain_anims[tile_object.properties["texture_source"]] = len(terrain_anims)
                animation_data.append("")
                for key in tile_object.properties:
                    if key != "texture_source" and key != "scale":
                        animation_data[terrain_anims[tile_object.properties["texture_source"]]] += key + "|" + str(tile_object.properties[key] + " ")
            #for key in tile_object.properties:
                #if key == "texture_source":
                    #output += key + "|" + str(terrain_anims[tile_object.properties[key]])
                #else:
                    # TODO: Add animation data to anim file
                    #output += key + "|" + str(tile_object.properties[key]) + " "
            output += "animIndex|" + str(terrain_anims[tile_object.properties["texture_source"]])
            output += " scale|" + str(tile_object.properties["scale"])
        else:
            for key in tile_object.properties:
                output += key + "|" + tile_object.properties[key] + " "
        output += "\n"
    f.write(output)

print(animation_data)
with open(outPath + "animData.txt", "w") as f:
    output = ""
    for index, key in enumerate(terrain_anims.keys()):
        output += f"{key} "
        output += f"{animation_data[index]} "
        output += "\n"
    f.write(output)

actual_data = ""
map_data = ""
with open(path, "r") as f:
    map_data = f.read()
    lines = map_data.split("\n")
    for line in lines:
        if not ("<object" in line or "</object" in line):
            actual_data += line + "\n"

with open(outPath + "tileData.tmx", "w") as f:
    f.write(actual_data)
