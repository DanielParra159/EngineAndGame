return {
  version = "1.1",
  luaversion = "5.1",
  tiledversion = "0.15.1",
  orientation = "orthogonal",
  renderorder = "left-down",
  width = 50,
  height = 50,
  tilewidth = 1,
  tileheight = 1,
  nextobjectid = 10,
  properties = {},
  tilesets = {},
  layers = {
    {
      type = "objectgroup",
      name = "ObjectCap",
      visible = true,
      opacity = 1,
      offsetx = 0,
      offsety = 0,
      properties = {},
      objects = {
        {
          id = 1,
          name = "",
          type = "Wall",
          shape = "rectangle",
          x = 4,
          y = 38,
          width = 34,
          height = 2,
          rotation = 0,
          visible = true,
          properties = {
            ["WallType"] = "1"
          }
        },
        {
          id = 3,
          name = "",
          type = "Player",
          shape = "rectangle",
          x = 7.04348,
          y = 35.6957,
          width = 1,
          height = 1,
          rotation = 0,
          visible = true,
          properties = {}
        },
        {
          id = 4,
          name = "",
          type = "Wall",
          shape = "rectangle",
          x = 38,
          y = 28,
          width = 12,
          height = 2,
          rotation = 0,
          visible = true,
          properties = {
            ["WallType"] = "1"
          }
        },
        {
          id = 5,
          name = "",
          type = "Wall",
          shape = "rectangle",
          x = 38,
          y = 30,
          width = 12,
          height = 10,
          rotation = 0,
          visible = true,
          properties = {
            ["WallType"] = "0"
          }
        },
        {
          id = 6,
          name = "",
          type = "Wall",
          shape = "rectangle",
          x = 4,
          y = 40,
          width = 46,
          height = 10,
          rotation = 0,
          visible = true,
          properties = {
            ["WallType"] = "0"
          }
        },
        {
          id = 7,
          name = "",
          type = "Wall",
          shape = "rectangle",
          x = 0,
          y = 18,
          width = 4,
          height = 32,
          rotation = 0,
          visible = true,
          properties = {
            ["WallType"] = "0"
          }
        },
        {
          id = 8,
          name = "",
          type = "Wall",
          shape = "rectangle",
          x = 0,
          y = 16,
          width = 4,
          height = 2,
          rotation = 0,
          visible = true,
          properties = {
            ["WallType"] = "1"
          }
        }
      }
    }
  }
}
