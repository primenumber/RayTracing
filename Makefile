CXXFLAGS:=-std=c++17 -Og -Wall -Wextra
TARGET:=rtiow
SRCS:=main.cpp
OBJS:=$(SRCS:%.cpp=%.o)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

main.o: vec3.hpp color.hpp ray.hpp hittable.hpp
