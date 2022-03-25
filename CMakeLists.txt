cmake_minimum_required(VERSION 3.21)
project(lab5)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab5 main.cpp DataLog.h Database.h Interpreter.h Parameter.h Parser.h Predicate.h Relation.h Rule.h Scanner.h
        Scheme.h Token.h Tuple.h Node.h Graph.h)
