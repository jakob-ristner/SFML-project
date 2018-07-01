import pytmx
from sys import argv

if len(argv) == 3:
    path = argv[1]
    outPath = "./" + argv[2] + "/"
else:
    path = "testmap2.txt"

tmxdata = pytmx.TiledMap(path)

with open(outPath + "collData.txt", "w") as f:
    output = ""
    for tile_object in tmxdata.objects:
        output += f"{tile_object.name} {tile_object.x} {tile_object.y} {tile_object.width} {tile_object.height} "
        for key in tile_object.properties:
            output += key + "|" + tile_object.properties[key] + " "
        output += "\n"
        print(output)
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
