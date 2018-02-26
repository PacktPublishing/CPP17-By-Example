#include "Directive.h"

Directive::Directive(TokenId directiveId)
 :m_directiveId(directiveId) {
  // Empty.
}

Directive::Directive(TokenId directiveId, int address)
 :m_directiveId(directiveId),
  m_address(address) {
  // Empty.
}

Directive::Directive(TokenId directiveId, const QString& name)
 :m_directiveId(directiveId),
  m_name(name) {
  // Empty.
}

Directive::Directive(TokenId directiveId, const QString& name,
                     int parameters)
 :m_directiveId(directiveId),
  m_name(name),
  m_parameters(parameters) {
  // Empty.
}

Directive::Directive(TokenId directiveId, const Value& value)
 :m_directiveId(directiveId),
  m_value(value) {
  // Empty.
}

Directive::Directive(TokenId directiveId,
                     const Function& function)
 :m_directiveId(directiveId),
  m_function(function) {
  // Empty.
}

Directive::Directive(const Directive& directive)
 :m_directiveId(directive.m_directiveId),
  m_name(directive.m_name),
  m_parameters(directive.m_parameters),
  m_address(directive.m_address),
  m_value(directive.m_value),
  m_function(directive.m_function) {
  // Empty.
}

 Directive Directive::operator=(const Directive& directive) {
  m_directiveId = directive.m_directiveId;
  m_name = directive.m_name;
  m_parameters = directive.m_parameters;
  m_address = directive.m_address;
  m_value = directive.m_value;
  m_function = directive.m_function;
  return *this;
}
