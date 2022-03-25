#ifndef SCANNER_H
#define SCANNER_H

#include <iostream>
#include <string>
#include <cctype>
#include "Token.h"
using namespace std;

class Scanner {
private:
   string input;
   int line = 1;
    // line counter for incomplete string
   int linePassed = 0;
public:
   Scanner(const string& input) : input(input) {}

   Token scanToken() {
       TokenType type = SND;
       int size = 1;

       // checking for empty space
       while (input.size() > 0 && isspace(input.at(0))) {
           // check if it's newline
           if (input.size() > 0) {
               if (input[0] == '\n') {
                   line++;
                   input = input.substr(1);
               } else
                   input = input.substr(1);
           } else { break; }
       }

       if (input.size() == 0) {
           type = EOF_TOKEN;
           size = 0;

           if (linePassed > 0)
               return Token(EOF_TOKEN, "", (line + linePassed));
           else
               return Token(EOF_TOKEN, "", line);
       }

       do {
           if (input[0] == '#') {
               int s = 0;
               while (input[s] != '\n') {
                   s++;
               }
               size = s;
               input = input.substr(size);

               while (input.size() > 0 && isspace(input.at(0))) {
                   // check if it's newline
                   if (input.size() > 0) {
                       if (input[0] == '\n') {
                           line++;
                           input = input.substr(1);
                       } else
                           input = input.substr(1);
                   } else { break; }
               }
           }
       } while (input[0] == '#');

       if ((input.find("Queries") == 0 && input[7] == '\n') ||
       (input.find("Queries") == 0 && int(char(input[7])) >= 32 && int(char(input[7] <= 64)))) {
           type = QUERIES;
           size = 7;
       } else if ((input.find("Rule") == 0 && input[5] == '\n') ||
                  (input.find("Rule") == 0 && int(char(input[5])) >= 32 && int(char(input[5] <= 64)))) {
           type = RULES;
           size = 5;
       } else if ((input.find("Facts") == 0 && input[5] == '\n') ||
                  (input.find("Facts") == 0 && int(char(input[5])) >= 32 && int(char(input[5] <= 64)))) {
           type = FACTS;
           size = 5;
       } else if ((input.find("Schemes") == 0 && input[7] == '\n') ||
                  (input.find("Schemes") == 0 && int(char(input[7])) >= 32 && int(char(input[7] <= 64)))) {
           type = SCHEMES;
           size = 7;
       } else if (input[0] == '\'') {
           type = STRING;
           int s = 1;

           while (input[s] != '\'' && s < int(input.size())) {
               if (input.at(s) == '\n') {
                   linePassed++;
               }
               // check if the string doesn't end
               if (input[s] != '\'' && s == int(input.size() - 1)) {
                   type = UNDEFINED;
                   break;
               }
               else {
                   s++;
               }
           }
           if (type == STRING) {
               size = s + 1;
           }
           else {
               size = s + 1;
           }
       }
       else if (isalpha(input[0])) {
           type = ID;
           int s = 0;
           while ((input[s] != '\n' && isalpha(input[s])) ||
           (int(char((input.at(s)))) > 47 && int(char(input.at(s))) < 58)) {
               s++;
           }
           size = s;
       }
       else {
           if (input[0] != '\n') {
               type = UNDEFINED;
               size = 1;
           }
       }

       switch (input.at(0)) {
           case ',':
               type = COMMA;
               size = 1;
               break;
           case '.':
               type = PERIOD;
               size = 1;
               break;
           case '?':
               type = Q_MARK;
               size = 1;
               break;
           case '(':
               type = LEFT_PAREN;
               size = 1;
               break;
           case ')':
               type = RIGHT_PAREN;
               size = 1;
               break;
           case ':':
               if (input.at(1) == '-') {
                   type = COLON_DASH;
                   size = 2;
                   break;
               } else {
                   type = COLON;
                   size = 1;
                   break;
               }
           case '*':
               type = MULTIPLY;
               size = 1;
               break;
           case '+':
               type = ADD;
               size = 1;
               break;
           case '!':
               type = UNDEFINED;
               size = 1;
               break;
           case '@':
               type = UNDEFINED;
               size = 1;
               break;
           case '$':
               type = UNDEFINED;
               size = 1;
               break;
           case '%':
               type = UNDEFINED;
               size = 1;
               break;
           case '^':
               type = UNDEFINED;
               size = 1;
               break;
           case '&':
               type = UNDEFINED;
               size = 1;
           case '-':
               type = UNDEFINED;
               size = 1;
               break;
       }

      string value = input.substr(0, size);
      input = input.substr(size);

      return Token(type, value, line);
   }
};

#endif
