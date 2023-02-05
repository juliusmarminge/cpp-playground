# -----------------------------------------------------------------------------
# HOW TO USE
# -----------------------------------------------------------------------------
# COMMAND:                     INFORMATION:
# -----------------------------------------------------------------------------
# make all                   : Build app
# make clean                 : Removes files created from builds (and ev. old zip file)
# make build                 : Build app only
#
# make lint                  : Use a 'linter' to check for common mistakes in your code.
# -----------------------------------------------------------------------------

INFO_ENVIRONMENT="MacOS"
CC=clang
CXX=clang
ASAN_EXPORT="symbolize=1 ASAN_SYMBOLIZER_PATH=$(shell which llvm-symbolizer)"
CFLAGS=-x c++ -c -Wall  -Wpedantic -Werror -std=c++17 $(INC_PARAMS) -O1
LDFLAGS=-lstdc++ -lm $(MC_FLAGS)
LINTER=clang-tidy


INCLUDE_DIRS= src/include
INC_PARAMS=$(foreach d, $(INCLUDE_DIRS), -I$d)

SRC:=$(find src -name '*.cc')
OBJECTS=$(SRC:.cc=.o)

APP_SRC=src/main.cc
APP_OBJECTS=$(APP_SRC:.cc=.o)
APP_EXECUTABLE=app

all: clean $(SRC) $(APP_SRC) $(APP_EXECUTABLE)

.PHONY: build-app
build-app: clean $(SRC) $(APP_SRC) $(APP_EXECUTABLE)

$(APP_EXECUTABLE): $(APP_OBJECTS) $(OBJECTS)
	@echo "Linking app executables"
	@$(CXX) $(LDFLAGS) $(APP_OBJECTS) $(OBJECTS) -o $@

.cc.o:
	@echo "Compiling object files"
	@$(CC) $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	@echo "Cleaning recreatable files:"
	@echo "  * App executables"
	@-rm -f $(APP_EXECUTABLE)
	@echo "  * Object files"
	@find . -name "*.o" -print0 | xargs -0 rm -f	

.PHONY: lint
lint:
	$(LINTER) --header-filter=".*.hpp" --warnings-as-errors='*' --checks="cppcoreguidelines-*, bugprone*, diagnostic-*, -clang-diagnostic-c++17-extensions, analyzer-*, readability-*, -cppcoreguidelines-pro-bounds-pointer-arithmetic, -cppcoreguidelines-special-member-functions, -cppcoreguidelines-owning-memory" ${SRC} ${APP_SRC} -- ${INC_PARAMS}