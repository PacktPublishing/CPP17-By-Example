#ifndef DIRECTIVE_H
#define DIRECTIVE_H

#include <QtWidgets>

#include "Token.h"
#include "Value.h"
#include "Function.h"

class Directive {
  public:
    Directive(TokenId tokenId);
    Directive(TokenId tokenId, int address);
    Directive(TokenId tokenId, const QString& name);
    Directive(TokenId tokenId, const QString& name,
              int parameters);
    Directive(TokenId tokenId, const Value& value);
    Directive(TokenId tokenId, const Function& function);

    Directive(const Directive& directive);
    Directive operator=(const Directive& directive);

    TokenId directiveId() {return m_directiveId;}
    const QString& name() {return m_name;}
    const Value& value() {return m_value;}
    const Function& function() {return m_function;}

    int parameters() const {return m_parameters;}
    int address() const {return m_address;}
    void setAddress(int address) {m_address = address;}

  private:
    TokenId m_directiveId;
    QString m_name;
    int m_parameters, m_address;
    Value m_value;
    Function m_function;
};

#endif // DIRECTIVE_H
