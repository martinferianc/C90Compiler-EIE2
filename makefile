CPPFLAGS += -std=c++11 -w -Wall -g
CPPFLAGS += -I include
CXX = g++

#LEXER
src/c_lexer/c_lexer.yy.cpp :
		flex -o src/c_lexer/c_lexer.yy.cpp src/c_lexer/c_lexer.flex

bin/c_lexer : src/c_lexer/c_lexer.yy.cpp
		$(CXX) $(CPPFLAGS) -o bin/c_lexer src/c_lexer/c_lexer.yy.cpp



#PARSER
src/c_parser/c_lexer.yy.cpp : src/c_parser/c_lexer.flex src/c_parser/c_parser.tab.hpp
		flex -o src/c_parser/c_lexer.yy.cpp src/c_parser/c_lexer.flex

src/c_parser/c_parser.tab.hpp : src/c_parser/c_parser.y
		bison -v -d src/c_parser/c_parser.y -o src/c_parser/c_parser.tab.cpp

bin/c_parser : src/c_parser/c_lexer.yy.o src/c_parser/c_parser.tab.cpp
		$(CXX) $(CPPFLAGS) -o bin/c_parser $^ src/c_parser/c_parser.cpp src/c_parser/tinyxml2/libtinyxml2.a


#COMPILER
SRCS = $(wildcard src/c_compiler/ast/*.cpp)
OBJS = $(SRCS:.cpp=.o)

$(OBJS): %.o : %.cpp
	  $(CXX) $(CPPFLAGS) -c $< -o $*.o

src/c_compiler/c_lexer.yy.cpp : src/c_compiler/c_lexer.flex src/c_compiler/c_parser.tab.hpp
		flex -w -o src/c_compiler/c_lexer.yy.cpp src/c_compiler/c_lexer.flex

src/c_compiler/c_parser.tab.hpp : src/c_compiler/c_parser.y
		bison -v -d src/c_compiler/c_parser.y -o src/c_compiler/c_parser.tab.cpp

bin/c_compiler : src/c_compiler/c_lexer.yy.cpp src/c_compiler/c_parser.tab.cpp $(OBJS)
		find src/c_compiler -type f -exec touch {} +
		$(CXX) $(CPPFLAGS) -o bin/c_compiler $^ src/c_compiler/c_compiler.cpp src/c_compiler/tinyxml2/libtinyxml2.a

bin/c_compiler_pretty_print : src/c_compiler/c_lexer.yy.o src/c_compiler/c_parser.tab.cpp $(OBJS)
		$(CXX) $(CPPFLAGS) -o bin/c_compiler_pretty_print $^ src/c_compiler/pretty_print.cpp src/c_compiler/tinyxml2/libtinyxml2.a

test : bin/c_compiler
		./test_compiler.sh

clean :
		rm -f src/c_lexer/*.o
		rm -f src/c_lexer/*.tab.cpp
		rm -f src/c_lexer/*.yy.cpp

		rm -f src/c_parser/*.o
		rm -f src/c_parser/*.tab.cpp
		rm -f src/c_parser/*.yy.cpp
		rm -f src/c_parser/*.tab.hpp
		rm -f src/c_parser/*.output

		rm -f src/c_compiler/*.o
		rm -f src/c_compiler/ast/*.o
		rm -f src/c_compiler/*.tab.cpp
		rm -f src/c_compiler/*.yy.cpp
		rm -f src/c_compiler/*.tab.hpp
		rm -f src/c_compiler/*.output

		rm -f bin/*
		rm -rf working
