HEADERS = markovRule.h
OBJECTS = project5.o markovRule.o
EXEC = project5

CFLAGS = -std=c++11 -g -Wall

#build executable program
$(EXEC): $(OBJECTS)
	g++ $^ -o $@
#build objective files from source files
%.o: %.cpp $(HEADERS)
	g++ -c $< -o $@
#clean up the mess
clean:
	rm -i `find ./ -type f -executable`
	rm -i *.o
#run the executable	
run: $(EXEC)
	./$(EXEC)

