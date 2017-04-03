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
  nextobjectid = 25,
  properties = {},
  tilesets = {
    {
      name = "Detalles",
      firstgid = 1,
      tilewidth = 1,
      tileheight = 1,
      spacing = 0,
      margin = 0,
      tileoffset = {
        x = 0,
        y = 0
      },
      properties = {},
      terrains = {},
      tilecount = 0,
      tiles = {}
    },
    {
      name = "Tree",
      firstgid = 1,
      tilewidth = 256,
      tileheight = 256,
      spacing = 0,
      margin = 0,
      tileoffset = {
        x = 0,
        y = 0
      },
      properties = {},
      terrains = {},
      tilecount = 1,
      tiles = {
        {
          id = 0,
          properties = {
            ["DetailType"] = "1",
            ["z"] = "-1"
          },
          image = "../materials/Tree.png",
          width = 256,
          height = 256
        }
      }
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
        },
        {
          id = 14,
          name = "",
          type = "Detail",
          shape = "rectangle",
          x = 18.1875,
          y = 38,
          width = 6,
          height = 9,
          rotation = 0,
          gid = 1,
          visible = true,
          properties = {
            ["DetailType"] = "1",
            ["z"] = "-1"
          }
        },
        {
          id = 17,
          name = "",
          type = "Detail",
          shape = "rectangle",
          x = 6,
          y = 38,
          width = 6,
          height = 9,
          rotation = 0,
          gid = 1,
          visible = true,
          properties = {
            ["DetailType"] = "1",
            ["z"] = "2"
          }
        },
        {
          id = 18,
          name = "",
          type = "Detail",
          shape = "rectangle",
          x = 30.25,
          y = 38,
          width = 6,
          height = 9,
          rotation = 0,
          gid = 1,
          visible = true,
          properties = {
            ["DetailType"] = "1",
            ["z"] = "-1"
          }
        },
        {
          id = 19,
          name = "",
          type = "Detail",
          shape = "rectangle",
          x = 25.125,
          y = 38,
          width = 6,
          height = 9,
          rotation = 0,
          gid = 1,
          visible = true,
          properties = {
            ["DetailType"] = "1",
            ["z"] = "2"
          }
        },
        {
          id = 20,
          name = "",
          type = "Wall",
          shape = "rectangle",
          x = 14.625,
          y = 28.25,
          width = 2,
          height = 2,
          rotation = 0,
          visible = true,
          properties = {
            ["WallType"] = "2"
          }
        },
        {
          id = 21,
          name = "",
          type = "Wall",
          shape = "rectangle",
          x = 21.1875,
          y = 21.25,
          width = 2,
          height = 2,
          rotation = 0,
          visible = true,
          properties = {
            ["WallType"] = "2"
          }
        },
        {
          id = 22,
          name = "",
          type = "Coin",
          shape = "rectangle",
          x = 14.5,
          y = 24.5625,
          width = 1,
          height = 1,
          rotation = 0,
          visible = true,
          properties = {
            ["CoinType"] = "0"
          }
        }
      }
    }
  }
}
