# LINUX UBUNTU 18.04.2 LTS Makfile by mdovhopo@student.unit.ua

CFLAGS = -c -Wall -O3

INCLUDE_DIRS = 
FRAMEWORKS = -lglfw3 -lGL -lm -lXrandr -lXi -lX11 -lXxf86vm -lpthread -ldl
STANDARTS = -std=c99

SOURCE_DIR = src

INCLUDES =	

SOURCES = $(addprefix $(SOURCE_DIR)/, 	main.c)

OBJECTS = $(SOURCES:.c=.o)

CC = clang
EXECUTABLE = sad_cat

.PHONY: all multi

multi:
	@$(MAKE) -j8 all

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(STANDARTS) $(FLAGS) $(INCLUDE_DIRS) $(OBJECTS) $(FRAMEWORKS) -o $@ 

.cpp.o: $(INCLUDES)
	$(CC) $(STANDARTS) $(FLAGS) $(INCLUDE_DIRS) $(CFLAGS) $< -o $@

clean:
	@/bin/rm -f $(OBJECTS)

fclean: clean
	@/bin/rm -f $(EXECUTABLE)

re: fclean multi
