(lume.map [
  ["grass" true]
  ["wall" false]
] (fn [t] (terrains:add (Terrain:new (table.unpack t)))))

(print "done")