# MacOS 10.13 High Sierra Makfile by mdovhopo@student.unit.ua

CFLAGS 			= -c -Wall

INCLUDE_DIRS	= -I ./lib/glad/include \
				  -I ./lib/glfw-3.3-MacOS-10.13/include \
				  -I ./inc

FRAMEWORKS		= -L ./lib/glfw-3.3-MacOS-10.13/src \
				  -lglfw3 \
				  -framework Cocoa \
				  -framework OpenGL \
				  -framework IOKit \
				  -framework CoreVideo
				  
GLAD			= ./lib/glad/src/glad.c

STD 			= -std=c99

SOURCE_DIR			= src
SOURCES			= $(wildcard src/main/*.c)
SOURCES		   += $(wildcard src/utils/*.c)
SOURCES		   += $(wildcard src/shaders/*.c)
SOURCES		   += $(GLAD)

OBJECTS			= $(SOURCES:.c=.o)

INCLUDES		=

CC				= clang
EXECUTABLE		= sad_cat

# .PHONY: all multi

# multi:
# 	@$(MAKE) -j8 all

all: $(SOURCES) $(EXECUTABLE) 

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(STD) $(FLAGS) $(INCLUDE_DIRS) $(OBJECTS) $(FRAMEWORKS) -o $@

%.o: %.c $(INCLUDES)
	$(CC) $(STD) $(FLAGS) $(INCLUDE_DIRS) $(CFLAGS) $< -o $@

clean:
	@/bin/rm -f $(OBJECTS)

fclean: clean
	@/bin/rm -f $(EXECUTABLE)

re: fclean all
