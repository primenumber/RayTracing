CXXFLAGS:=-std=c++17 -Og -Wall -Wextra
TARGET:=rtiow
SRCS:=main.cpp sphere.cpp hittable_list.cpp
OBJS:=$(SRCS:%.cpp=%.o)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

main.o: vec3.hpp color.hpp ray.hpp hittable.hpp sphere.hpp hittable_list.hpp
sphere.o: vec3.hpp ray.hpp hittable.hpp sphere.hpp
hittable_list.o: vec3.hpp ray.hpp hittable.hpp hittable_list.hpp
