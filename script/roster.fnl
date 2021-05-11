(roster:add "bob" { :strength 20 })
(roster:add "jimmy" { :strength 10 })

(print (. (roster:get "bob") :name))