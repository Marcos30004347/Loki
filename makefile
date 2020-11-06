all:
	g++ main.cpp \
	-I./Loki \
	Loki/Lib/String.cpp \
	Loki/HLSL/Lexer/Lexer.cpp \
	Loki/HLSL/Lexer/Token.cpp \
	Loki/HLSL/Parser/BaseType.cpp \
	Loki/HLSL/Parser/Literals.cpp \
	Loki/HLSL/Parser/PackOffset.cpp \
	Loki/HLSL/Parser/Parser.cpp \
	Loki/HLSL/Parser/Profiles.cpp \
	Loki/HLSL/Parser/Register.cpp \
	Loki/HLSL/Parser/Semantics.cpp \
	Loki/HLSL/Parser/Variables.cpp \
	Loki/HLSL/Parser/Buffer.cpp \
	-o loki

clean:
	rm *.out loki