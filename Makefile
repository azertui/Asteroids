PWD=./
B_FOLD=$(PWD)build/
SRC_FOLD=$(PWD)src/
INC_FOLD=$(PWD)include/
CMAKE_CACHE=$(B_FOLD)CMakeCache.txt

SRC_FILE=$(wildcard $(SRC_FOLD)*.cpp)
INC_FILE=$(wildcard $(INC_FOLD)*.h)

BIN_FILE=$(B_FOLD)asteroid


all: $(B_FOLD) $(CMAKE_CACHE) $(BIN_FILE)
	

$(BIN_FILE): $(CMAKE_CACHE) $(SRC_FILE) $(INC_FILE)
	cmake --build $(B_FOLD) --target asteroid -- -j 6

gdb: $(CMAKE_CACHE) $(SRC_FILE) $(INC_FILE)
	cmake --build $(B_FOLD) --config Debug --target asteroid -- -j 6

$(CMAKE_CACHE): $(B_FOLD)
	cd $(B_FOLD); cmake ..

$(B_FOLD):
	mkdir $@

clean:
	rm $(BIN_FILE)
	
destroy:
	rm -r $(B_FOLD)
