CXXFLAGS:=-std=c++17 -O3 -g -march=native -Wall -Wextra -fopenmp -MMD -MP
TARGET:=rtiow
SRCS:=main.cpp sphere.cpp hittable_list.cpp material.cpp moving_sphere.cpp aabb.cpp bvh.cpp
OBJS:=$(SRCS:%.cpp=%.o)
DEPS:=$(SRCS:%.cpp=%.d)

all: $(TARGET)

-include $(DEPS)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.PHONY: clean

clean:
	rm -f $(TARGET) $(OBJS) $(DEPS)
