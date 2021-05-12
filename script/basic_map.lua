return {
  version = "1.5",
  luaversion = "5.1",
  tiledversion = "1.6.0",
  orientation = "orthogonal",
  renderorder = "right-down",
  width = 16,
  height = 16,
  tilewidth = 24,
  tileheight = 24,
  nextlayerid = 8,
  nextobjectid = 3,
  properties = {},
  tilesets = {
    {
      name = "oryx_fan",
      firstgid = 1,
      filename = "../oryx_fan.tsx"
    },
    {
      name = "colors",
      firstgid = 2297,
      filename = "../colors.tsx"
    }
  },
  layers = {
    {
      type = "group",
      id = 7,
      name = "Decoration",
      visible = true,
      opacity = 1,
      offsetx = 0,
      offsety = 0,
      parallaxx = 1,
      parallaxy = 1,
      properties = {},
      layers = {
        {
          type = "tilelayer",
          x = 0,
          y = 0,
          width = 16,
          height = 16,
          id = 1,
          name = "Base",
          visible = true,
          opacity = 1,
          offsetx = 0,
          offsety = 0,
          parallaxx = 1,
          parallaxy = 1,
          properties = {},
          encoding = "lua",
          data = {
            1150, 1150, 1150, 1150, 1150, 1150, 1150, 1150, 1150, 1150, 1150, 1150, 1150, 1151, 1150, 1150,
            1150, 1150, 1150, 1150, 1150, 1150, 1150, 1150, 1150, 1150, 1150, 1150, 1150, 1151, 1150, 1151,
            1150, 1150, 1150, 1150, 1150, 1150, 1150, 1150, 1150, 1150, 1150, 1150, 1150, 1151, 1150, 1150,
            1150, 1150, 1150, 1150, 1150, 1150, 1150, 1150, 1150, 1150, 1150, 1151, 1151, 1150, 1150, 1151,
            1150, 1150, 1150, 1150, 1150, 1150, 1150, 1150, 1150, 1150, 1150, 1150, 1150, 1150, 1150, 1151,
            1150, 1150, 1150, 1150, 1150, 1150, 1150, 1150, 1150, 1150, 1150, 1151, 1150, 1151, 1151, 1150,
            1150, 1150, 1150, 1150, 1150, 1150, 1150, 1150, 1150, 1151, 1151, 1150, 1150, 1151, 1150, 1150,
            1150, 1150, 1150, 1151, 1150, 1151, 1150, 1150, 1150, 1151, 1150, 1151, 1150, 1151, 1151, 1151,
            1151, 1150, 1151, 1151, 1150, 1150, 1151, 1151, 1151, 1150, 1150, 1151, 1151, 1151, 1150, 1151,
            1151, 1151, 1150, 1151, 1151, 1150, 1151, 1150, 1150, 1151, 1150, 1151, 1150, 1150, 1150, 1151,
            1151, 1150, 1151, 1150, 1151, 1150, 1151, 1151, 1151, 1151, 1151, 1151, 1150, 1150, 1151, 1150,
            1151, 1150, 1151, 1150, 1151, 1150, 1151, 1150, 1151, 1150, 1150, 1151, 1151, 1151, 1151, 1150,
            1151, 1150, 1151, 1150, 1151, 1151, 1151, 1151, 1151, 1151, 1151, 1150, 1150, 1151, 1151, 1151,
            1151, 1150, 1151, 1151, 1151, 1151, 1151, 1150, 1150, 1151, 1151, 1150, 1151, 1151, 1150, 1151,
            1151, 1150, 1150, 1150, 1150, 1151, 1150, 1151, 1150, 1150, 1151, 1150, 1150, 1151, 1151, 1150,
            1151, 1150, 1150, 1151, 1151, 1150, 1150, 1151, 1150, 1150, 1150, 1151, 1150, 1151, 1151, 1150
          }
        },
        {
          type = "tilelayer",
          x = 0,
          y = 0,
          width = 16,
          height = 16,
          id = 2,
          name = "Grass",
          visible = true,
          opacity = 1,
          offsetx = 0,
          offsety = 0,
          parallaxx = 1,
          parallaxy = 1,
          properties = {},
          encoding = "lua",
          data = {
            903, 902, 901, 904, 904, 927, 926, 926, 927, 926, 926, 927, 927, 927, 927, 926,
            902, 904, 901, 902, 904, 926, 926, 926, 926, 926, 926, 926, 926, 927, 927, 927,
            901, 903, 901, 904, 904, 926, 927, 926, 927, 926, 926, 926, 926, 926, 927, 927,
            927, 927, 926, 927, 926, 926, 927, 926, 926, 926, 926, 927, 927, 926, 926, 927,
            927, 927, 926, 927, 926, 926, 926, 927, 926, 927, 927, 927, 927, 927, 926, 927,
            926, 926, 927, 926, 926, 927, 926, 927, 926, 927, 927, 927, 926, 926, 927, 927,
            937, 926, 927, 927, 927, 926, 927, 927, 927, 926, 926, 927, 944, 927, 927, 927,
            0, 937, 927, 926, 927, 926, 926, 927, 927, 927, 926, 926, 926, 926, 936, 945,
            0, 0, 991, 926, 927, 927, 926, 926, 926, 926, 927, 927, 936, 988, 0, 0,
            0, 0, 0, 937, 926, 926, 927, 927, 927, 927, 927, 935, 0, 0, 611, 612,
            0, 0, 0, 0, 945, 945, 934, 930, 930, 935, 945, 0, 0, 611, 668, 668,
            612, 613, 0, 0, 0, 0, 0, 0, 0, 0, 0, 611, 612, 668, 668, 668,
            668, 668, 612, 612, 612, 613, 0, 0, 0, 611, 612, 668, 668, 668, 668, 668,
            668, 668, 668, 668, 668, 669, 0, 0, 0, 667, 668, 668, 668, 668, 668, 668,
            668, 668, 668, 668, 668, 669, 0, 0, 0, 667, 668, 668, 668, 668, 668, 668,
            668, 668, 668, 668, 668, 669, 0, 0, 0, 667, 668, 668, 668, 668, 668, 668
          }
        },
        {
          type = "tilelayer",
          x = 0,
          y = 0,
          width = 16,
          height = 16,
          id = 3,
          name = "Trees",
          visible = true,
          opacity = 1,
          offsetx = 0,
          offsety = 0,
          parallaxx = 1,
          parallaxy = 1,
          properties = {},
          encoding = "lua",
          data = {
            1073742561, 0, 0, 0, 0, 1192, 0, 0, 0, 0, 0, 158, 158, 156, 156, 159,
            0, 0, 95, 0, 0, 1192, 0, 0, 0, 0, 159, 159, 159, 157, 157, 156,
            0, 0, 0, 0, 0, 1193, 0, 0, 0, 0, 158, 159, 156, 157, 159, 159,
            1189, 1189, 1189, 1190, 1184, 2147484832, 0, 0, 1183, 0, 156, 156, 157, 159, 156, 159,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 274, 0,
            0, 0, 0, 0, 0, 0, 0, 1180, 0, 0, 0, 0, 0, 274, 0, 0,
            0, 0, 274, 0, 0, 0, 0, 0, 1179, 0, 0, 274, 274, 0, 0, 0,
            0, 0, 0, 274, 0, 0, 0, 0, 0, 0, 274, 0, 0, 274, 0, 0,
            274, 0, 274, 0, 274, 0, 0, 1178, 0, 0, 0, 274, 0, 0, 0, 0,
            0, 0, 0, 274, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 274, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
          }
        }
      }
    },
    {
      type = "tilelayer",
      x = 0,
      y = 0,
      width = 16,
      height = 16,
      id = 5,
      name = "$terrain",
      visible = true,
      opacity = 0.5,
      offsetx = 0,
      offsety = 0,
      parallaxx = 1,
      parallaxy = 1,
      properties = {},
      encoding = "lua",
      data = {
        0, 0, 0, 0, 0, 2297, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 2297, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 2297, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        2297, 2297, 2297, 2297, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2351, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2351, 0, 0,
        0, 0, 2351, 0, 0, 0, 0, 0, 0, 0, 0, 2351, 2351, 0, 0, 0,
        0, 0, 0, 2351, 0, 0, 0, 0, 0, 0, 2351, 0, 0, 2351, 0, 0,
        2351, 0, 2351, 0, 2351, 0, 0, 0, 0, 0, 0, 2351, 0, 0, 0, 0,
        0, 0, 0, 2351, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2297, 2297,
        0, 0, 0, 2351, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2297, 2297, 2297,
        2297, 2297, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2297, 2297, 2297, 2297, 2297,
        2297, 2297, 2297, 2297, 2297, 2297, 0, 0, 0, 2297, 2297, 2297, 2297, 2297, 2297, 2297,
        2297, 2297, 2297, 2297, 2297, 2297, 0, 0, 0, 2297, 2297, 2297, 2297, 2297, 2297, 2297,
        2297, 2297, 2297, 2297, 2297, 2297, 0, 0, 0, 2297, 2297, 2297, 2297, 2297, 2297, 2297,
        2297, 2297, 2297, 2297, 2297, 2297, 0, 0, 0, 2297, 2297, 2297, 2297, 2297, 2297, 2297
      }
    },
    {
      type = "objectgroup",
      draworder = "topdown",
      id = 6,
      name = "$triggers",
      visible = true,
      opacity = 1,
      offsetx = 0,
      offsety = 0,
      parallaxx = 1,
      parallaxy = 1,
      properties = {},
      objects = {
        {
          id = 1,
          name = "goal",
          type = "goal",
          shape = "point",
          x = 12.7273,
          y = 11.8182,
          width = 0,
          height = 0,
          rotation = 0,
          visible = true,
          properties = {}
        },
        {
          id = 2,
          name = "player-spawn",
          type = "",
          shape = "point",
          x = 178.182,
          y = 321.818,
          width = 0,
          height = 0,
          rotation = 0,
          visible = true,
          properties = {}
        }
      }
    }
  }
}