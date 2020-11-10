cmake_minimum_required(VERSION 3.10)

project(hlsl)

include_directories(.)

add_library(
    hlsl
	Lib/String.cpp
	Lexer/Lexer.cpp
	Lexer/Token.cpp
	Parser/AST.cpp
	Parser/Types.cpp
	Parser/BuiltInTypes.cpp
	Parser/PackOffset.cpp
	Parser/Parser.cpp
	Parser/Profiles.cpp
	Parser/Register.cpp
	Parser/Semantics.cpp
	Parser/Variables.cpp
	Parser/InterpolationModifier.cpp
	Parser/Expressions.cpp
	Parser/Functions.cpp
	Parser/Scope.cpp
	Parser/Block.cpp
	Parser/Buffer.cpp
	Parser/Struct.cpp
	Parser/Statement.cpp
	Parser/FlowControl.cpp
	Parser/FunctionCall.cpp
)

