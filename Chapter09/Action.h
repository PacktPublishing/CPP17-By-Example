#ifndef ACTION_H
#define ACTION_H

#include "Token.h"
#include "Value.h"

class Action {
  public:
    Action(TokenId actionId, const Value& value1 = Value(),
           const Value& value2 = Value());

    Action(const Action& action);
    Action operator=(const Action& action);

    TokenId id() const {return m_actionId;}
    const Value& value1() const {return m_value1;}
    const Value& value2() const {return m_value2;}

  private:
    TokenId m_actionId;
    Value m_value1, m_value2;
};

#endif // ACTION_H
