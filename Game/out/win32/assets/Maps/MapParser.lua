function Test()
	print("test")
end

function Test2(mapFile)
	print("test2")
	print(mapFile)
end

function Test3(mapFile, mapName)
	print("test3")
	print(mapFile)
	print(mapName)
end

function ParseMap(mapFile, mapName)
	print(mapFile)
	--print("hola")
	map = dofile(mapFile)
	--print("ok")

	--print(map["width"])

	width = map["width"]
	heightMap = map["height"]
	tilewidth = map["tilewidth"]
	tileheight = map["tileheight"]

	--print("width "..width)
	--print("height "..height)
	--print("tilewidth "..tilewidth)
	--print("tileheight "..tileheight)


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
        local width = object["width"]
		local height = object["height"]
		local x = object["x"] + width/2
        local y = (heightMap-object["y"])+height/2
		

		local type = object["type"]

		if type == "Wall" then
			platformmerWall = PlatformmerWall()
			
			AddWall(platformmerWall)
			platformmerWall:Init(x,y,width,height)
		elseif type == "Player" then
			platformmerPlayer = PlatformmerPlayer()
			
			AddPlayer(platformmerPlayer)
			platformmerPlayer:Init(x,y)
		end
		print(type.." "..x.." "..y.." "..width.." "..height)
	end
end