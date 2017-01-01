TESTCONNECTION	= TestConnection

CXX		= g++

CXXFLAGS	+= -W -Wall -Wextra
CXXFLAGS	+= -I ../inc/client/ -I ../inc/shared/ -I ../inc/server/
CXXFLAGS	+= -g3

LDFLAGS		+= -lpthread -lgtest

SRCS_TEST_CONNECTION	+= ../src/server/Connection.cpp
SRCS_TEST_CONNECTION	+= server/Connection/TestConnection.cpp

SHARED_SRCS		+= gtester.cpp
SHARED_SRCS		+= ../src/shared/ASocket.cpp
SHARED_SRCS		+= ../src/shared/BaseNet.cpp
SHARED_SRCS		+= ../src/shared/DataBaseEntity.cpp
SHARED_SRCS		+= ../src/shared/IdentifierFound.cpp
SHARED_SRCS		+= ../src/shared/IdentifierNotFound.cpp
SHARED_SRCS		+= ../src/shared/RTEntity.cpp

OBJS_TEST_CONNECTION	= $(SRCS_TEST_CONNECTION:.cpp=.o)
SHARED_OBJS		= $(SHARED_SRCS:.cpp=.o)

all: $(TESTCONNECTION)

$(TESTCONNECTION): $(SHARED_OBJS) $(OBJS_TEST_CONNECTION)
	$(CXX) $(SHARED_OBJS) $(OBJS_TEST_CONNECTION) -o $@ $(LDFLAGS)

clean:
	rm -f $(OBJS_TEST_CONNECTION) $(SHARED_OBJS)

fclean: clean
	rm -f $(TESTCONNECTION)

re: fclean all

.PHONY: all clean fclean re
