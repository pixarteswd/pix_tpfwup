APP = pixtpfwup
OUT := out
SRC := $(wildcard src/*.cpp)
OBJS := $(patsubst %.cpp,$(OUT)/%.o,$(notdir $(SRC)))

CXXFLAGS ?= -g -O1
CXXFLAGS += -std=c++11 -Wall
LDFLAGS ?= -g
#LIBS = 

all: dir $(APP)

dir:
	mkdir -p $(OUT)

$(APP): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ $(LIBS) -o $(APP)

$(OBJS): $(OUT)/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(APP)
