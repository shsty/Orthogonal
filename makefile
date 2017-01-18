DIR = bin
BIN = $(DIR)/main
OBJS = $(DIR)/main.o $(DIR)/event.o $(DIR)/render.o $(DIR)/loop.o $(DIR)/player.o $(DIR)/map.o 
CXX = g++ -std=c++0x -g
LIBS = -lSDL2 -lSDL2_image

.PHONY: all clean test

all: $(BIN)

$(BIN): $(DIR) $(OBJS)
	$(CXX) $(OBJS) $(LIBS) -o$@

$(DIR):
	mkdir $(DIR)

$(OBJS): $(DIR)/%.o: %.cpp
	$(CXX) -c $< -o$@

main.h: exception.h player.h map.h
	touch $@

$(DIR)/main.o $(DIR)/event.o $(DIR)/render.o $(DIR)/loop.o: main.h

$(DIR)/player.o: player.h

$(DIR)/map.o: map.h

test: $(BIN)
	./$(BIN)

debug: $(BIN)
	gdb ./$(BIN)

clean: 
	rm -v $(BIN) $(OBJS)
