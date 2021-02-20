CXXFLAGS:=-std=c++17 -Og -Wall -Wextra
TARGET:=rtiow
SRCS:=main.cpp sphere.cpp
OBJS:=$(SRCS:%.cpp=%.o)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

main.o: vec3.hpp color.hpp ray.hpp hittable.hpp sphere.hpp
sphere.o: vec3.hpp ray.hpp hittable.hpp sphere.hpp
