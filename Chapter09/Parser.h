#ifndef PARSER_H
#define PARSER_H

#include "Action.h"
#include "Scanner.h"

class Parser {
  public:
    Parser(Scanner& m_scanner, QList<Action>& actionList);

  private:
    void match(TokenId tokenId);

    void instructionList();
    void instruction();

    Value expression();
    Value expressionRest(Value leftValue);
    Value mulDivExpression();
    Value mulDivExpressionRest(Value leftValue);
    Value primaryExpression();

    void checkType(TokenId operatorId, const Value& value);
    void checkType(TokenId operatorId, const Value& leftValue,
                   const Value& rightValue);
    Value evaluate(TokenId operatorId, const Value& value);
    Value evaluate(TokenId operatorId, const Value& leftValue,
                   const Value& rightValue);

  private:
    Token m_lookAHead;
    Scanner& m_scanner;
    QList<Action>& m_actionList;
    QMap<QString,Value> m_assignMap;                                                                                                                                                                                                            };

#endif // PARSER_H
