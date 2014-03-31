CC = g++
CFLAGS = -std=c++11 -g -I/usr/include/python3.3m -I/Library/boost_1_55_0
LDFLAGS = -L/usr/lib/python3.3/config-3.3m -lpython3.3m -L/usr/local/lib/ -lboost_system -lboost_filesystem

SRC = $(wildcard *.cpp)
OBJS = $(SRC:.cpp=.o)
AOUT = ipd

all : $(AOUT) clean-o

ipd : $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^
%.o : %.cpp
	$(CC) $(CFLAGS) -o $@ -c $<
clean-o :
	@rm -f *.o
clean : clean-o
	@rm -f $(AOUT)
