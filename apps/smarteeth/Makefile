.PHONY: all build clean run

CXXFLAGS += -std=c++17
LDFLAGS += -lpistache -lcrypto -lssl -lpthread -lpaho-mqttpp3 -lpaho-mqtt3a

all: build run

build: smarteeth

clean:
	-rm smarteeth

run:
	./smarteeth

smarteeth: smarteeth.o brushing.o configuration.o mqtt.o health.o statistics.o directions.o
	$(CXX) $^ -o $@ $(CXXFLAGS) $(LDFLAGS)
