all:
	g++ main.cpp \
	src/Utils.cpp \
	src/GLSLWritter.cpp \
	src/Parser.cpp \
	src/Lexer.cpp \
	src/AST.cpp \
	src/Types.cpp \
	src/Shader.cpp \
	src/Visitor.cpp \
	src/Scope.cpp \
	-o loki

clean:
	rm *.out loki