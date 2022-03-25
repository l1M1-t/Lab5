#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <vector>
#include "Token.h"
#include "DataLog.h"
#include "Predicate.h"
#include "Rule.h"
using namespace std;

class Parser {
private:
   vector<Token> tokens;
   dataLog datalog;
   Predicate p;
   Parameter pm;
   vector<Parameter> pmv;
   Rule r;
   bool isQuery = false;
public:
   Parser(const vector<Token>& tokens) : tokens(tokens) {}

    // getters

    dataLog getDataLog() const {
        return datalog;
    }

   TokenType tokenType() const {
      return tokens[0].getType();
   }

   void advanceToken() {
      tokens.erase(tokens.begin());
   }

   void throwError() {
      throw tokens[0];
   }

   void match(TokenType t) {
      if (tokenType() == t)
         advanceToken();
      else
         throwError();
   }

   void datalogProgram() {
       if (tokenType() == SCHEMES) {
           match(SCHEMES);
           match(COLON);
           scheme();
           schemeList();
           match(FACTS);
           match(COLON);
           factList();
           match(RULES);
           match(COLON);
           ruleList();
           match(QUERIES);
           match(COLON);
           isQuery = true;
           query();
           queryList();
           match(EOF_TOKEN);
       }
       else {
           throwError();
       }
   }

    void schemeList() {
        if (tokenType() == ID) {
            scheme();
            schemeList();
        } else {
            // lambda
        }
    }

    void factList() {
        if (tokenType() == ID) {
            fact();
            factList();
        } else {
            // lambda
        }
    }

    void ruleList() {
        if (tokenType() == ID) {
            rule();
            ruleList();
        } else {
            // lambda
        }
    }

    void queryList() {
        if (tokenType() == ID) {
            query();
            queryList();
        } else {
            // lambda
        }
    }

   void scheme() {
      if (tokenType() == ID) {
          p.setID(tokens[0].getValue());
          match(ID);
          match(LEFT_PAREN);
          // extract the value of the parameter
          // send the parameter to domain in datalog
          pm.setValue(tokens[0].getValue());
          pmv.push_back(pm);
          match(ID);

          idList();

          match(RIGHT_PAREN);

          // insert all the parameters to the scheme predicate
          for (int i = 0; i < (int)pmv.size(); i++) {
              p.setParameters(pmv[i]);
          }

          datalog.getSchemes().push_back(p);

          // reset p and pm and pmv
          p.clear();
          pm.clear();
          pmv.clear();
      } else {
         throwError();
      }
   }

   void fact() {
       if (tokenType() == ID) {
           p.setID(tokens[0].getValue());
           match(ID);

           match(LEFT_PAREN);
           pm.setValue(tokens[0].getValue());
           pmv.push_back(pm);
           datalog.getDomains().insert(tokens[0].getValue());
           match(STRING);
           stringList();

           match(RIGHT_PAREN);
           match(PERIOD);

           // insert all the parameters to the scheme predicate
           for (int i = 0; i < (int)pmv.size(); i++) {
               p.setParameters(pmv[i]);
           }

           datalog.getFacts().push_back(p);

           // reset p and pm and pmv
           p.clear();
           pm.clear();
           pmv.clear();
       } else {
           throwError();
       }
   }

    void rule() {
        headPredicate();
        match(COLON_DASH);
        predicate();
        predicateList();
        match(PERIOD);
        datalog.getRules().push_back(r);
        // reset r
        r.clear();
    }

   void query() {
       predicate();
       match(Q_MARK);
   }

    // need to differentiate between scheme
    void headPredicate() {
        if (tokenType() == ID) {
            p.setID(tokens[0].getValue());
            match(ID);

            match(LEFT_PAREN);
            // extract the value of the parameter
            // send the parameter to domain in datalog
            pm.setValue(tokens[0].getValue());
            pmv.push_back(pm);
            match(ID);

            idList();

            match(RIGHT_PAREN);

            // insert all the parameters to the scheme predicate
            for (int i = 0; i < (int)pmv.size(); i++) {
                p.setParameters(pmv[i]);
            }

            r.setHeadPred(p);

            // reset p and pm and pmv
            p.clear();
            pm.clear();
            pmv.clear();
        } else {
            throwError();
        }
    }

    void predicate() {
       if (tokenType() == ID) {
           p.addID(tokens[0].getValue());
           match(ID);

           match(LEFT_PAREN);

           parameter();
           parameterList();

           match(RIGHT_PAREN);

           for (int i = 0; i < (int)pmv.size(); i++) {
               p.setParameters(pmv[i]);
           }

           // for queries
           if (isQuery) {
               datalog.getQueries().push_back(p);
           }
           // for rules
           else {
               r.getBody().push_back(p);
           }

           // reset objects used
           p.clear();
           pm.clear();
           pmv.clear();
       }
   }

   void predicateList() {
       if (tokenType() == COMMA) {
           match(COMMA);
           predicate();
           predicateList();
       } else {
           // lambda
       }
   }

    void parameterList() {
        if (tokenType() == COMMA) {
            match(COMMA);
            parameter();
            parameterList();
        } else {
            // lambda
        }
    }

   void stringList() {
       if (tokenType() == COMMA) {
           match(COMMA);
           pm.setValue(tokens[0].getValue());
           pmv.push_back(pm);
           datalog.getDomains().insert(tokens[0].getValue());
           match(STRING);
           stringList();
       } else {
           // lambda
       }
   }

    void idList() {
        if (tokenType() == COMMA) {
            match(COMMA);
            pm.setValue(tokens[0].getValue());
            pmv.push_back(pm);
            match(ID);
            idList();
        } else {
            // lambda
        }
    }

   void parameter() {
       if (tokenType() == STRING) {
           pm.setValue(tokens[0].getValue());
           pmv.push_back(pm);
           match(STRING);
       }
       else if (tokenType() == ID) {
           pm.setValue(tokens[0].getValue());
           pmv.push_back(pm);
           match(ID);
       }
       else {
           throwError();
       }
   }

   void toString() const {
       datalog.schemesToString();
       datalog.factsToString();
       datalog.rulesToString();
       datalog.queriesToString();
       datalog.domainsToString();
   }
};

#endif
