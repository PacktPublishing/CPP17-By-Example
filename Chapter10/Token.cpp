#include "Token.h"

Token::Token()
 :m_tokenId(EndOfFileId) {
  // Empty.
}

Token::Token(TokenId tokenId)
 :m_tokenId(tokenId) {
  // Empty.
}

Token::Token(TokenId tokenId, const QString& name)
 :m_tokenId(tokenId),
  m_name(name) {
  // Empty.
}

Token::Token(TokenId tokenId, const Value& value)
 :m_tokenId(tokenId),
  m_value(value) {
  // Empty.
}

TokenId m_tokenId;
QString m_name;
Value m_value;

Token::Token(const Token& token)
 :m_tokenId(token.m_tokenId),
  m_name(token.m_name),
  m_value(token.m_value) {
  // Empty.
}

Token Token::operator=(const Token& token) {
  m_tokenId = token.m_tokenId;
  m_name = token.m_name;
  m_value = token.m_value;
  return *this;
}
