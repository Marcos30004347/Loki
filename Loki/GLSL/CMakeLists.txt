cmake_minimum_required(VERSION 3.10)

project(glsl)

include_directories(.)

add_library(
    glsl
	Lib/String.cpp
	Lexer/Lexer.cpp
	Lexer/Token.cpp
	Parser/AST.cpp
	Parser/Block.cpp
	Parser/Buffer.cpp
	Parser/BuiltInTypes.cpp
	Parser/Expressions.cpp
	Parser/InterpolationModifier.cpp
	Parser/LayoutQualifier.cpp
	Parser/Parser.cpp
	Parser/PrecisionQualifier.cpp
	Parser/Scope.cpp
	Parser/InterpolationModifier.cpp
	Parser/StorageQualifiers.cpp
	Parser/StorageQualifiers.cpp
	Parser/Structs.cpp
	Parser/Types.cpp
	Parser/Declarations.cpp
	Parser/Statement.cpp
	Parser/FunctionCall.cpp
	Parser/Expressions.cpp
	Parser/FlowControl.cpp
)

