(lume.map [
  ["grass" true "fan_world@33,13"]
  ["wall" false "fan_world@1,1"]
] (fn [t] (terrains:add (Terrain:new (table.unpack t)))))

(print "done")