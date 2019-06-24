# LINUX UBUNTU 18.04.2 LTS Makfile by mdovhopo@student.unit.ua

CFLAGS 			= -c -Wall

INCLUDE_DIRS	= -I ./lib/glad/include \
				  -I ./inc

FRAMEWORKS		= -lglfw3 -lGL -lm -lXrandr -lXi -lX11 -lXxf86vm -lpthread -ldl
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
