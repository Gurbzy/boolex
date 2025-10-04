CFLAGS = -std=c++17 -Wall -Werror -MMD -MP
INCFLAGS = -I ./include

SRC = $(wildcard src/*.cpp)
OBJDIR = obj
OBJ = $(SRC:src/%.cpp=$(OBJDIR)/%.o)
DEP = $(OBJ:.o=.d)

boolex: $(OBJ)
	g++ $(OBJ) -o $@

run: boolex
	./boolex

$(OBJDIR)/%.o: src/%.cpp | $(OBJDIR)
	g++ -c $< $(CFLAGS) $(INCFLAGS) -o $@

$(OBJDIR):
	mkdir $(OBJDIR)

clean:
	rm -rf boolex $(OBJDIR)

-include $(DEP)
