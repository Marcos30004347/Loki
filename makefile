all:
	g++ main.cpp src/Parser.cpp src/Lexer.cpp src/AST.cpp src/Scope.cpp -o loki

clean:
	rm *.out loki