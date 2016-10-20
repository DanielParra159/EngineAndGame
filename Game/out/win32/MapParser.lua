function ParseMap(mapFile, mapName)
	--print(mapFile)
	--print("hola")
	map = dofile(mapFile)
	--print("ok")

	--print(map["width"])

	width = map["width"]
	height = map["height"]
	tilewidth = map["tilewidth"]
	tileheight = map["tileheight"]

	--print("width "..width)
	--print("height "..height)
	--print("tilewidth "..tilewidth)
	--print("tileheight "..tileheight)


	_map = CMap(mapName, width, height)
	setMap(_map)
	initWallMatrix(width, height)

	tilesets = map["tilesets"]

	tilesAux = {}


	layers = map["layers"]
	
	for layerKey,layer in pairs(layers) do
		layerName = layer["type"]
		if layerName == "objectgroup" then
			objectLayer = layer["objects"]
		end
	end

	ParseObjects()

	
end

function ParseObjects()

	for key, object in pairs(objectLayer) do
        local x = object["x"]
        local y = object["y"]
		local width = object["width"]
		local height = object["height"]

		local type = object["type"]

		if type == "Wall" then
			print("Wall: "..x.." "..y.." "..width.." "..height)
		end
	end
end