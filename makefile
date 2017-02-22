DIR = bin
BIN = $(DIR)/main
LNK = game
SOURCES = $(wildcard *.cpp)
HEADERS = $(wildcard *.h)
OBJS = $(SOURCES:%.cpp=$(DIR)/%.o)
DEP = makefile.dep
CXX = g++ -std=c++0x -g
LIBS = -lSDL2 -lSDL2_image -ljsoncpp

.PHONY: all clean test

all: $(BIN) $(LNK)

$(LNK): $(BIN)
	ln -sf $< $@

$(BIN): $(DIR) $(OBJS) $(DEP)
	$(CXX) $(OBJS) $(LIBS) -o$@

$(DEP): $(SOURCES) $(HEADERS)
	@g++ -MM $(SOURCES) | sed "s/^.*\.o/$(DIR)\/&/" > $(DEP)

$(DIR):
	mkdir $@

$(OBJS): $(DIR)/%.o: %.cpp
	$(CXX) -c $< -o$@

include $(DEP)

test: $(BIN)
	./$(BIN)

debug: $(BIN)
	gdb ./$(BIN)

clean: 
	rm -v $(BIN) $(OBJS)

