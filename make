CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O3
TARGET = conf

.PHONY: all clean install

all: $(TARGET)

$(TARGET): conf.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f $(TARGET)

install: $(TARGET)
	install -m 0755 $(TARGET) /usr/local/bin/$(TARGET)
