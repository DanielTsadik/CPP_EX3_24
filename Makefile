# Compiler and flags
CXX = clang++
CXXFLAGS = -std=c++11 -Wall -Wextra -Werror -Iinclude

# Source files
SRCS = main.cpp \
       src/Catan.cpp \
       src/Player.cpp \
       src/Board.cpp \
       src/City.cpp \
       src/Plot.cpp \
       src/DevelopmentCard.cpp \
       src/Road.cpp \
       src/Settlement.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
EXEC = catan_game

# Build rule
all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -f $(OBJS) $(EXEC)
