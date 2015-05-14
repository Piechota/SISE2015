# this is a simple makefile
CXX = g++
#CXXLAGS = -Wall -std=c++11
CXXLAGS = -std=c++11

# rules

EXEC_NAME = sise

SOURCES = main.cpp Audio.cpp Color.cpp DanceMat.cpp ExamplePlayer.cpp Globals.cpp GraphRenderer.cpp HumanPlayer.cpp Keyboard.cpp Renderer.cpp Stats.cpp GameController.cpp Graph.cpp Node.cpp Pawn.cpp Player.cpp

SOURCE_FOLDER = SISE2015

SRCS = $(addprefix $(SOURCE_FOLDER)/, $(SOURCES))

OBJECTS = $(SOURCES:.cpp=.o)

INCLUDES = -I/$(SOURCE_FOLDER) -I../libs/include

LIB_FOLDERS = -L../libs -L../libs/lib

LIB_FOLDER_STATIC = ../libs/lib
LIBRARIES = SDL2.lib SDL2main.lib SDL2_mixer.lib
LIBRARIES_BASENAME = $(basename $(LIBRARIES))
#LIBRARIES_WITH_PREFIX = $(addprefix -l,$(basename $(LIBRARIES)))
LIBRARIES_AFTER_CONVERT = $(addprefix lib,$(LIBRARIES:.lib=.a))
LIBRARIES_AFTER_CONVERT_IN_FOLDER = $(addprefix $(LIB_FOLDER_STATIC)/,$(LIBRARIES_AFTER_CONVERT))
LIBRARIES_WITH_PREFIX = $(addprefix -l,$(LIBRARIES_BASENAME))
#LIBRARIES_WITH_PREFIX = $(addsufix lib,$(addprefix -l,$(basename $(LIBRARIES))))

ADDITIONAL_LIBS = SDL2.dll SDL2_mixer.dll
ADDITIONAL_LIBS_IN_FOLDER = $(addprefix ../libs/, $(ADDITIONAL_LIBS))

EXEC_FOLDER = MakeFileBuild

OBJS = $(addprefix $(EXEC_FOLDER)/, $(OBJECTS))

default: $(EXEC_NAME) AdditionalLibs
	@echo Compilation Succesful...
#@echo $(SRCS)
#@echo $(SOURCE_FOLDER)/%.cpp
#@echo $(OBJS)
#@echo $(EXEC_FOLDER)/%.o

run: $(EXEC_NAME)
	@echo Compilation Succesful...
	@echo Launch program...
	@./$(EXEC_FOLDER)/$(EXEC_NAME).exe

$(EXEC_NAME): $(OBJS) $(LIBRARIES_AFTER_CONVERT_IN_FOLDER)
	$(CXX) $(CXXLAGS) $(INCLUDES) -o $(EXEC_FOLDER)/$(EXEC_NAME) $(OBJS) $(LIB_FOLDERS) $(LIBRARIES_WITH_PREFIX)

$(EXEC_FOLDER)/%.o: $(SOURCE_FOLDER)/%.cpp
	$(CXX) $(CXXLAGS) $(INCLUDES) -c  $< -o $@

$(LIB_FOLDER_STATIC)/lib%.a: $(LIB_FOLDER_STATIC)/%.lib
	cp $< $@

test:
	@echo $(LIBRARIES)
	@echo $(LIBRARIES_BASENAME)
	@echo $(LIBRARIES_AFTER_CONVERT)
	@echo $(addprefix $(LIB_FOLDER_STATIC)/,$(LIBRARIES_AFTER_CONVERT))
	@echo $(LIBRARIES_AFTER_CONVERT_IN_FOLDER)
AdditionalLibs:
	@echo Copying additional libraries...
	@cp $(ADDITIONAL_LIBS_IN_FOLDER) $(EXEC_FOLDER)/

#$(SOURCE_FOLDER).cpp$(EXEC_FOLDER).o:
# $(CXX) $(CXXLAGS) $(INCLUDES) -c $< -o $@

#clean:
# @echo $(wildcard $(EXEC_FOLDER)/*)

clean:
ifneq ("$(wildcard $(EXEC_FOLDER)/*)","")
	@rm $(EXEC_FOLDER)/*
else
	
endif
	@echo Build cleanned...

#	@echo No files to clean...

#g++ -I/src -Wall -c src/foo.cpp -o exec/foo.o - works
