CFLAGS = -std=c++17 -Wall -Werror
INCFLAGS = -I ./include

SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)
HEADERS = $(wildcard ../include/*.hpp)

boolex: $(OBJ)
	g++ $(OBJ) -o $@

%.o: %.cpp $(HEADERS)
	g++ -c $< $(CFLAGS) $(INCFLAGS) -o $@

clean:
	rm -f boolex src/*.o
