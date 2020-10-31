all:
	g++ src/main.cpp src/Parser.cpp src/Lexer.cpp src/AST.cpp src/Scope.cpp -o program.out

clean:
	rm *.out