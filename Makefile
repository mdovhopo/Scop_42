# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tryckylake <tryckylake@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/29 15:11:01 by mdovhopo          #+#    #+#              #
#    Updated: 2019/08/03 00:53:30 by tryckylake       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# This Makefile was tested for:
# LINUX UBUNTU 18.04.2 LTS and MacOS 10.13.3 High Sierra

# Get OS name
UNAME_S			= $(shell uname -s)
LIB_DIR			= ./lib

# Different lib linking for Linux and OSX
ifeq ($(UNAME_S), Linux)
	OS_NAME		= Linux
	LIBS	= -lglfw3 -lGL -lm \
				-lXrandr -lXi -lX11 \
				-lXxf86vm -lpthread -ldl
endif
ifeq ($(UNAME_S), Darwin)
	OS_NAME		= OSX
	GLFW_DIR = $(LIB_DIR)/glfw-3.3-MacOS-10.13-Compiled
	LIBS	= -L $(GLFW_DIR)/src -lglfw3 \
				-framework Cocoa \
				-framework OpenGL \
				-framework IOKit \
				-framework CoreVideo
	INCLUDE_DIRS+= -I $(GLFW_DIR)/include
endif

LIBFT_PATH		= $(LIB_DIR)/libft
LIBFT_BIN		= $(LIBFT_PATH)/libft.a

LIBS		   += -L $(LIBFT_PATH) -lft

INCLUDE_DIRS   += -I $(LIB_DIR)/glad/include \
				  -I ./inc \
				  -I $(LIBFT_PATH)/inc \
				  -I $(LIB_DIR)/cglm/include

GLAD_SRC		= $(LIB_DIR)/glad/src/glad.c

STD 			= -std=c99 

SOURCE_DIR			= src
SOURCES			= $(wildcard src/main/*.c)
SOURCES		   += $(wildcard src/utils/*.c)
SOURCES		   += $(wildcard src/shaders/*.c)
SOURCES		   += $(wildcard src/camera/*.c)
SOURCES		   += $(wildcard src/obj_parser/*.c)
SOURCES		   += $(GLAD_SRC)
OBJECTS			= $(SOURCES:.c=.o)

INCLUDES		=

CFLAGS 			= -c -Wall -pedantic
CC				= clang -g
EXECUTABLE		= sad_cat

.PHONY: all clean


all: $(EXECUTABLE)
	@echo "\033[92m[$(EXECUTABLE) done]\033[0m"

$(LIBFT_BIN):
	@$(MAKE) -s -C $(LIBFT_PATH)

$(EXECUTABLE): $(OBJECTS) $(LIBFT_BIN)
	@echo "[Compiling target $@ for $(OS_NAME)]"
	@$(CC) $(STD) $(FLAGS) $(INCLUDE_DIRS) $(OBJECTS) $(LIBS) -o $@
	@echo "\033[92m[Target $(EXECUTABLE) Has been created, run ./$@]\033[0m"
	@echo "\033[92m[Starting $(EXECUTABLE) ...]\033[0m"
	@./$(EXECUTABLE)

%.o: %.c $(INCLUDES)
	@echo "[Compiling] $@"
	@$(CC) $(STD) $(FLAGS) $(INCLUDE_DIRS) $(CFLAGS) $< -o $@

clean:
	@/bin/rm -f $(OBJECTS)
	@$(MAKE) -s -C $(LIBFT_PATH) clean
	@echo "\033[92m[all *.o files deleted!]\033[0m"

test:
	clang++ -o test test_main.c

fclean: clean
	@/bin/rm -f $(EXECUTABLE)
	@/bin/rm -f $(LIBFT_BIN)
	@echo "\033[92m[$(EXECUTABLE) deleted!]\033[0m"

re: fclean all

magic:
	clear
	@echo "*making magic*"
	@echo " 	.∧＿∧"
	@echo " 	( ･ω･｡)つ━☆・*。"
	@echo "	⊂　 ノ 　　　・゜+."
	@echo "	しーＪ　　　°。+ *´¨)"
	@echo "                 .· ´¸.·*´¨) ¸.·*¨)"
	@echo "　　　　　　　　(¸.·´ (¸.·'* ☆"
