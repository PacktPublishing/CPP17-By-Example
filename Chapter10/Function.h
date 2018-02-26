#ifndef FUNCTION_H
#define FUNCTION_H

#include <QtWidgets>

#include "Value.h"
#include "Action.h"

class Function {
  public:
    Function() {}
    Function(const QList<QString>& nameList, int address);
    const QList<QString>& nameList() const {return m_nameList;}
    int address() {return m_address;}

    Function(const Function& function);
    Function operator=(const Function& function);

  private:
    QList<QString> m_nameList;
    int m_address;
};

#endif // FUNCTION_H
