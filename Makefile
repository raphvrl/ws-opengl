cc = g++

source_dir = src
include_dir = include
bin_dir = bin
libdir = libs

target = $(bin_dir)/main.out

source = $(wildcard $(source_dir)/*.cpp) $(wildcard $(source_dir)/*/*.cpp)
object = $(patsubst %.cpp, $(bin_dir)/%.o, $(source))
header = $(wildcard $(include_dir)/*.hpp) $(wildcard $(include_dir)/*/*.hpp)

flags += -I$(include_dir) -Wall -Wextra -Werror -std=c++20
flags += -L$(libdir) -lglfw3 -lglad -lwinmm -lgdi32 -lopengl32
del = rm -f
mkdir = mkdir -p
print = echo

file_nbr = $(words $(source))
file_count = 0

default: run

$(bin_dir):
	@$(mkdir) $@

$(target): $(object)
	@$(print) "[$(file_count)/$(file_nbr)] Linking $@"
	@$(cc) $(flags) $^ -o $@

$(bin_dir)/%.o: %.cpp $(header)
	@$(mkdir) $(dir $@)
	@$(print) "[$(file_count)/$(file_nbr)] Compiling $<"
	@$(cc) $(flags) -c $< -o $@
	@$(eval file_count = $(shell expr $(file_count) + 1))

build:
	@$(cc) -c $(source_dir)/glad.c -o glad.o $(flags)
	@ar rcs $(libdir)/libglad.a glad.o
	@$(del) glad.o
	@$(del) $(source_dir)/glad.c

clean:
	@$(del) $(object) $(target)

re: clean run

run: $(target)
	@$<

.PHNOY: clean run re
