#include "Function.h"

Function::Function(const QList<QString>& nameList, int address)
 :m_nameList(nameList),
  m_address(address) {
  // Empty.
}

Function::Function(const Function& function)
 :m_nameList(function.m_nameList),
  m_address(function.m_address) {
  // Empty.
}

Function Function::operator=(const Function& function) {
  m_nameList = function.m_nameList;
  m_address = function.m_address;
  return *this;
}
