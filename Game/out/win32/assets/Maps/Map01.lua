return {
  version = "1.1",
  luaversion = "5.1",
  tiledversion = "0.17.0",
  orientation = "orthogonal",
  renderorder = "left-down",
  width = 50,
  height = 50,
  tilewidth = 1,
  tileheight = 1,
  nextobjectid = 9,
  properties = {},
  tilesets = {
    {
      name = "T_BrickTiled",
      firstgid = 1,
      tilewidth = 1,
      tileheight = 1,
      spacing = 0,
      margin = 0,
      image = "../materials/T_BrickTiled.png",
      imagewidth = 64,
      imageheight = 64,
      tileoffset = {
        x = 0,
        y = 0
      },
      properties = {},
      terrains = {},
      tilecount = 4096,
      tiles = {}
    }
  },
  layers = {
    {
      type = "objectgroup",
      name = "ObjectCap",
      visible = true,
      opacity = 1,
      offsetx = 0,
      offsety = 0,
      draworder = "topdown",
      properties = {},
      objects = {
        {
          id = 1,
          name = "",
          type = "Wall",
          shape = "rectangle",
          x = 9,
          y = 50,
          width = 6.5,
          height = 5,
          rotation = 0,
          gid = 2075,
          visible = true,
          properties = {}
        },
        {
          id = 3,
          name = "",
          type = "Wall",
          shape = "rectangle",
          x = 15.5,
          y = 50,
          width = 34.4375,
          height = 8,
          rotation = 0,
          gid = 2075,
          visible = true,
          properties = {}
        },
        {
          id = 4,
          name = "",
          type = "Player",
          shape = "rectangle",
          x = 10.75,
          y = 36.75,
          width = 1,
          height = 1,
          rotation = 0,
          gid = 1198,
          visible = true,
          properties = {}
        },
        {
          id = 5,
          name = "",
          type = "Wall",
          shape = "rectangle",
          x = 22.5,
          y = 42,
          width = 7,
          height = 5,
          rotation = 0,
          gid = 2075,
          visible = true,
          properties = {}
        },
        {
          id = 6,
          name = "",
          type = "Wall",
          shape = "rectangle",
          x = 0,
          y = 50,
          width = 9,
          height = 26.9091,
          rotation = 0,
          gid = 2075,
          visible = true,
          properties = {}
        },
        {
          id = 7,
          name = "",
          type = "Wall",
          shape = "rectangle",
          x = 41,
          y = 42,
          width = 9,
          height = 26.9091,
          rotation = 0,
          gid = 2075,
          visible = true,
          properties = {}
        },
        {
          id = 8,
          name = "",
          type = "Wall",
          shape = "rectangle",
          x = 18,
          y = 40,
          width = 1,
          height = 1,
          rotation = 0,
          gid = 2075,
          visible = true,
          properties = {}
        }
      }
    }
  }
}
