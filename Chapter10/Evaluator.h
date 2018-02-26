#ifndef GENERATOR_H
#define GENERATOR_H

#include <QtWidgets>

#include "Error.h"
#include "Directive.h"
#include "Action.h"
#include "Function.h"

class Evaluator {
  public:
    Evaluator(const QList<Directive>& directiveList,
              QList<Action>& actionList,
              QMap<QString,Function> functionMap);
  private:
    void checkType(TokenId tokenId, const Value& value);
    void checkType(TokenId tokenId, const Value& leftValue,
                   const Value& rightValue);

    Value evaluate(TokenId tokenId, const Value& value);
    Value evaluate(TokenId tokenId, const Value& leftValue,
                   const Value& rightValue);

    QStack<Value> m_valueStack;
    QMap<QString,Value> m_valueMap;
    QStack<QMap<QString,Value>> m_valueMapStack;
    QStack<int> m_returnAddressStack;
};

#endif // GENERATOR_H
