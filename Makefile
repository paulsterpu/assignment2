CXX=g++ -std=c++11
CXXFLAGS=-Wall

build: problema1 problema2

problema1: problema1.o
	$(CXX) $(CXXFLAGS) -o $@ $^

problema1.o: problema1.cpp

run-p1: problema1
	./problema1

problema2: problema2.o
	$(CXX) $(CXXFLAGS) -o $@ $^

problema2.o: problema2.cpp

run-p2: problema2
	./problema2


clean:
	rm problema1 problema1.o problema2 problema2.o
