#ifndef SCANNER_H
#define SCANNER_H

#include "Token.h"
#include "Colors.h"

class Scanner {
  public:
    static void init();
    Scanner(QString& buffer);

  public:
    Token nextToken();

  private:
    QString m_buffer;
    int m_bufferIndex = 0;

    static QMap<QString,Value> m_valueMap;
    static QMap<QString,TokenId> m_keywordMap;
    static QList<pair<QString,TokenId>> m_operatorList;
};

#endif // SCANNER_H
