CXXFLAGS:=-std=c++17 -O3 -march=native -Wall -Wextra -fopenmp
TARGET:=rtiow
SRCS:=main.cpp sphere.cpp hittable_list.cpp material.cpp
OBJS:=$(SRCS:%.cpp=%.o)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

main.o: vec3.hpp color.hpp ray.hpp hittable.hpp sphere.hpp hittable_list.hpp rtweekend.hpp camera.hpp utils.hpp material.hpp
sphere.o: vec3.hpp ray.hpp hittable.hpp sphere.hpp utils.hpp material.hpp
hittable_list.o: vec3.hpp ray.hpp hittable.hpp hittable_list.hpp utils.hpp
material.o: vec3.hpp ray.hpp hittable.hpp utils.hpp material.hpp
