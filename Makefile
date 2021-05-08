CXXFLAGS=`pkg-config --cflags raylib lua`
CXXFLAGS+=-std=c++2a
CXXFLAGS+=-I.
LDFLAGS=`pkg-config --libs raylib lua`

game: game.o
	$(CXX) $(LDFLAGS) $< -o $@

run: clean game
	./game

clean:
	-rm game *.o

.PHONY: clean run