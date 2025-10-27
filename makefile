SRC = engine.cpp primitiveRenderer.cpp primitives.cpp
LIBS = $$(pkg-config allegro-5 allegro_font-5 allegro_primitives-5 --libs --cflags)

all: compileEngine

compileEngine: $(SRC)
	g++ -o engine $(SRC) $(LIBS)

clear:
	rm *.o
