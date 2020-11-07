cmake_minimum_required(VERSION 3.10)

project(loki)

include_directories(.)

add_library(
    loki
    Lib/String.cpp
	HLSL/Lexer/Lexer.cpp
	HLSL/Lexer/Token.cpp
	HLSL/Parser/AST.cpp
	HLSL/Parser/BaseType.cpp
	HLSL/Parser/Literals.cpp
	HLSL/Parser/PackOffset.cpp
	HLSL/Parser/Parser.cpp
	HLSL/Parser/Profiles.cpp
	HLSL/Parser/Register.cpp
	HLSL/Parser/Semantics.cpp
	HLSL/Parser/Variables.cpp
	HLSL/Parser/InterpolationModifier.cpp
	HLSL/Parser/Expression.cpp
	HLSL/Parser/Function.cpp
	HLSL/Parser/Block.cpp
	HLSL/Parser/Buffer.cpp
	HLSL/Parser/Struct.cpp
	HLSL/Parser/Statement.cpp
	HLSL/Parser/FlowControl.cpp
	HLSL/Parser/FunctionCall.cpp
)

