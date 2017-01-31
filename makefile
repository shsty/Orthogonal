DIR = bin
BIN = $(DIR)/main
OBJS = $(DIR)/main.o $(DIR)/event.o $(DIR)/loop.o $(DIR)/player.o $(DIR)/map.o $(DIR)/cursor.o $(DIR)/renderer.o
CXX = g++ -std=c++0x -g
LIBS = -lSDL2 -lSDL2_image

.PHONY: all clean test

all: $(BIN)

$(BIN): $(DIR) $(OBJS)
	$(CXX) $(OBJS) $(LIBS) -o$@

$(DIR):
	mkdir $@

$(OBJS): $(DIR)/%.o: %.cpp
	$(CXX) -c $< -o$@

main.h: exception.h cursor.h
	touch $@

$(DIR)/main.o: main.h map.h player.h cursor.h renderer.h
$(DIR)/event.o: main.h map.h player.h cursor.h renderer.h
$(DIR)/loop.o: main.h map.h player.h
$(DIR)/renderer.o: renderer.h exception.h
$(DIR)/map.o: map.h player.h renderer.h
$(DIR)/player.o: player.h renderer.h
$(DIR)/cursor.o: cursor.h renderer.h

test: $(BIN)
	./$(BIN)

debug: $(BIN)
	gdb ./$(BIN)

clean: 
	rm -v $(BIN) $(OBJS)
