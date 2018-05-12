import pytmx

tmxdata = pytmx.TiledMap("testmap1.tmx")
directory = "./map1/"

with open(directory + "collData.txt", "w") as f:
    output = ""
    for tile_object in tmxdata.objects:
        output += f"{tile_object.name}-{tile_object.x}-{tile_object.y}-{tile_object.width}-{tile_object.height}\n"
        #Obstacle(self, tile_object.x, tile_object.y, tile_object.width, tile_object.height)


    f.write(output)

actual_data = ""
map_data = ""
with open("testmap1.tmx", "r") as f:
    map_data = f.read()
    lines = map_data.split("\n")
    for line in lines:
        if not ("<object" in line or "</object" in line):
            actual_data += line + "\n"

with open(directory + "testmap1.tmx", "w") as f:
    f.write(actual_data)