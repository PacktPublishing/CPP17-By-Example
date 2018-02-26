#ifndef SCANNER_H
#define SCANNER_H

#include "Token.h"

class Scanner {
  public:
    static void init();
    Scanner(QString& buffer);

  public:
    Token NextToken();
    bool ScanValue(double& value);

  private:
    QString m_buffer;
    static QMap<QString,Value> m_valueMap;
    static QMap<QString,TokenId> m_keywordMap;
    static QList<pair<QString,TokenId>> m_tokenList;
};

#endif // SCANNER_H
