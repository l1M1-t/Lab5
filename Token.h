#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

enum TokenType {
COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, MULTIPLY, ADD,
SCHEMES, FACTS, RULES, QUERIES, ID, STRING, COMMENT, UNDEFINED, EOF_TOKEN, SND
};

class Token {
private:
   TokenType type;
   string value;
   int line;
public:
   Token() {
      type = COMMA;
      value = "";
      line = 0;
   }

   Token(TokenType type, string value, int line) : type(type), value(value), line(line) {}

   // getters
   TokenType getType() const {
       return type;
   }

   string getValue() const {
       return value;
   }

   int getLine() const {
       return line;
   }

   // setters
   void setType(TokenType type) {
       this->type = type;
   }

   void setValue(string value) {
       this->value = value;
   }

   void setLine(int line) {
       this->line = line;
   }

   void toString() const {
       cout << "(" << typeName(type) << "," << "\"" << value << "\"" << "," << line << ")" << endl;
   }

   string typeName(TokenType type) const {
      switch (type) {
      case COMMA:
         return "COMMA";
      case PERIOD:
         return "PERIOD";
      case Q_MARK:
         return "Q_MARK";
      case LEFT_PAREN:
         return "LEFT_PAREN";
      case RIGHT_PAREN:
         return "RIGHT_PAREN";
      case COLON:
         return "COLON";
      case COLON_DASH:
         return "COLON_DASH";
      case MULTIPLY:
         return "MULTIPLY";
      case ADD:
         return "ADD";
      case SCHEMES:
         return "SCHEMES";
      case FACTS:
         return "FACTS";
      case RULES:
         return "RULES";
      case QUERIES:
         return "QUERIES";
      case ID:
         return "ID";
      case STRING:
         return "STRING";
      case COMMENT:
         return "COMMENT";
      case UNDEFINED:
         return "UNDEFINED";
      case EOF_TOKEN:
         return "EOF";
      default:
         return "BAD TOKEN";
         break;
      }
   }
};

#endif
