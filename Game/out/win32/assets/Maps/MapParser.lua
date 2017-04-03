function ParseMap(mapFile, mapName)
	map = dofile(mapFile)
	
	--print("mapFile "..mapFile)
	--print("mapName "..mapName)

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
        local y = (heightMap-(object["y"]+height))+height/2
		local properties = object["properties"]
		

		local type = object["type"]

		if type == "Wall" then
			platformmerWall = PlatformmerWall()
			local wallType = tonumber(properties["WallType"])
			
			AddWall(platformmerWall)
			platformmerWall:Init(x,y,width,height, wallType)
		elseif type == "Player" then
			platformmerPlayer = PlatformmerPlayer()
			
			AddPlayer(platformmerPlayer)
			platformmerPlayer:Init(x,y)
		elseif type == "Detail" then
			y = (heightMap-(object["y"]))+height/2;
			local detailType = tonumber(properties["DetailType"])
			local z = tonumber(object["properties"]["z"])
			AddDetail(x, y, z, detailType)
		elseif type == "Coin" then
			platformmerCoin = PlatformmerCoin()
			local coinType = tonumber(properties["CoinType"])
			AddCoin(platformmerCoin)
			platformmerCoin:Init(x,y,coinType )
		end
		
		--print(type.." "..x.." "..y.." "..width.." "..height)
	end
end