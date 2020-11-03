all:
	g++ main.cpp src/Utils/Utils.cpp src/Translator/GLES2Translator.cpp src/Parser/Parser.cpp src/Lexer/Lexer.cpp src/AST/AST.cpp src/AST/Types.cpp -I src -o loki

clean:
	rm *.out loki