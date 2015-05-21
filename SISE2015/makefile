# this is a simple makefile
CXX = g++
#CXXLAGS = -Wall -std=c++11
CXXLAGS = -std=c++11 -O3

# rules

EXEC_NAME = sise
EXEC_FOLDER = MakeFileBuild

SOURCES = Audio.cpp Colour.cpp DanceMat.cpp ExamplePlayer.cpp Globals.cpp GraphRenderer.cpp HumanPlayer.cpp Keyboard.cpp main.cpp Renderer.cpp Stats.cpp GameController.cpp Graph.cpp Node.cpp Pawn.cpp Player.cpp

SOURCE_FOLDER = SISE2015

SRCS = $(addprefix $(SOURCE_FOLDER)/, $(SOURCES))

OBJECTS = $(SOURCES:.cpp=.o)

INCLUDES = -I/$(SOURCE_FOLDER) -I../libs_linux/include -I../SDL2-2.0.3/include -I../SDL2_mixer-2.0.0

LIB_FOLDERS = -L../libs_linux/lib -L../SDL2-2.0.3/build

LIBRARIES = SDL2 SDL2main SDL2_mixer
LIBRARIES_BASENAME = $(basename $(LIBRARIES))

LIBRARIES_WITH_PREFIX = $(addprefix -l,$(LIBRARIES_BASENAME))

OBJS = $(addprefix $(EXEC_FOLDER)/, $(OBJECTS))

default: $(EXEC_NAME) AdditionalLibs
	@echo Compilation Succesful...

run: $(EXEC_NAME)
	@echo Compilation Succesful...
	@echo Launch program...
	@./$(EXEC_FOLDER)/$(EXEC_NAME).exe

$(EXEC_NAME): $(OBJS)
	$(CXX) $(CXXLAGS) $(INCLUDES) -o $(EXEC_FOLDER)/$(EXEC_NAME) $(OBJS) $(LIB_FOLDERS) $(LIBRARIES_WITH_PREFIX) -Wl,-rpath=/usr/local/lib

$(EXEC_FOLDER)/%.o: $(SOURCE_FOLDER)/%.cpp
	$(CXX) $(CXXLAGS) $(INCLUDES) -c  $< -o $@

#$(LIB_FOLDER_STATIC)/lib%.a: $(LIB_FOLDER_STATIC)/%.lib
#	cp $< $@

test:
	@echo $(LIBRARIES)
	@echo $(LIBRARIES_BASENAME)
	@echo $(LIBRARIES_AFTER_CONVERT)
	@echo $(addprefix $(LIB_FOLDER_STATIC)/,$(LIBRARIES_AFTER_CONVERT))
	@echo $(LIBRARIES_AFTER_CONVERT_IN_FOLDER)
AdditionalLibs:
	@echo Copying additional libraries...
	@cp $(LIB_FOLDERS)/*so* $(EXEC_FOLDER)/

clean:
ifneq ("$(wildcard $(EXEC_FOLDER)/*)","")
	@rm $(EXEC_FOLDER)/*
else
	
endif
	@echo Build cleanned...

