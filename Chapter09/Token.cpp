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
