# compiler and flags
CXX = g++
CXXFLAGS = -Wall -Werror -std=c++17 -Iinclude

# define targets
all: loadbalancer

loadbalancer: main.o Request.o RequestQueue.o WebServer.o LoadBalancer.o Config.o
	$(CXX) $(CXXFLAGS) -o loadbalancer main.o Request.o RequestQueue.o WebServer.o LoadBalancer.o Config.o

# rules for object files
main.o: src/main.cpp
	$(CXX) $(CXXFLAGS) -c src/main.cpp

Request.o: src/Request.cpp
	$(CXX) $(CXXFLAGS) -c src/Request.cpp

RequestQueue.o: src/RequestQueue.cpp
	$(CXX) $(CXXFLAGS) -c src/RequestQueue.cpp

WebServer.o: src/WebServer.cpp
	$(CXX) $(CXXFLAGS) -c src/WebServer.cpp

LoadBalancer.o: src/LoadBalancer.cpp
	$(CXX) $(CXXFLAGS) -c src/LoadBalancer.cpp

Config.o: src/Config.cpp include/Config.h
	$(CXX) $(CXXFLAGS) -c src/Config.cpp

# clean target
clean:
	rm -f loadbalancer *.o