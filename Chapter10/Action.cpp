#include "Action.h"

Action::Action(TokenId actionId,
               const Value& value1 /*= Value()*/,
               const Value& value2 /*= Value()*/ )
  :m_actionId(actionId),
   m_value1(value1),
   m_value2(value2) {
  // Empty.
}

Action::Action(const Action& action)
 :m_actionId(action.m_actionId),
  m_value1(action.m_value1),
  m_value2(action.m_value2) {
  // Empty.
}

Action Action::operator=(const Action& action) {
  m_actionId = action.m_actionId;
  m_value1 = action.m_value1;
  m_value2 = action.m_value2;
  return *this;
}
