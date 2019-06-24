# Makfile by mdovhopo@student.unit.ua
# This Makefile was tested for:
# LINUX UBUNTU 18.04.2 LTS and MacOS 10.13.3 High Sierra

# Get OS name
UNAME_S			= $(shell uname -s)

# Different lib linking for Linux and OSX
ifeq ($(UNAME_S), Linux)
	OS_NAME		= Linux
	FRAMEWORKS	= -lglfw3 -lGL -lm \
				-lXrandr -lXi -lX11 \
				-lXxf86vm -lpthread -ldl
endif
ifeq ($(UNAME_S), Darwin)
	OS_NAME		= OSX
	FRAMEWORKS	= -L ./lib/glfw-3.3-MacOS-10.13/src -lglfw3 \
				-framework Cocoa \
				-framework OpenGL \
				-framework IOKit \
				-framework CoreVideo
	INCLUDE_DIRS+= -I ./lib/glfw-3.3-MacOS-10.13/include
endif

INCLUDE_DIRS   += -I ./lib/glad/include \
				  -I ./inc

GLAD_SRC		= ./lib/glad/src/glad.c

STD 			= -std=c99

SOURCE_DIR			= src
SOURCES			= $(wildcard src/main/*.c)
SOURCES		   += $(wildcard src/utils/*.c)
SOURCES		   += $(wildcard src/shaders/*.c)
SOURCES		   += $(GLAD_SRC)
OBJECTS			= $(SOURCES:.c=.o)

INCLUDES		=

CFLAGS 			= -c -Wall
CC				= clang
EXECUTABLE		= sad_cat

.PHONY: all multi clean

multi:
	@$(MAKE) -s -j8 all

all: $(SOURCES) $(EXECUTABLE)
	@echo "\033[92m[All done]\033[0m"

$(EXECUTABLE): $(OBJECTS) 
	@echo "[Compiling target $@ for $(OS_NAME)]"
	@$(CC) $(STD) $(FLAGS) $(INCLUDE_DIRS) $(OBJECTS) $(FRAMEWORKS) -o $@
	@echo "\033[92m[Target $(EXECUTABLE) Has been created, run ./$@]\033[0m"

%.o: %.c $(INCLUDES)
	@echo "[Compiling] $@"
	@$(CC) $(STD) $(FLAGS) $(INCLUDE_DIRS) $(CFLAGS) $< -o $@

clean:
	@/bin/rm -f $(OBJECTS)
	@echo "\033[92m[all *.o files deleted!]\033[0m"

fclean: clean
	@/bin/rm -f $(EXECUTABLE)
	@echo "\033[92m[$(EXECUTABLE) deleted!]\033[0m"

re: fclean multi

magic:
	clear
	@echo "*making magic*"
	@echo " 	.∧＿∧"
	@echo " 	( ･ω･｡)つ━☆・*。"
	@echo "	⊂　 ノ 　　　・゜+."
	@echo "	しーＪ　　　°。+ *´¨)"
	@echo "                 .· ´¸.·*´¨) ¸.·*¨)"
	@echo "　　　　　　　　(¸.·´ (¸.·'* ☆"
