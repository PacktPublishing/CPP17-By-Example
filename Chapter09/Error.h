#ifndef ERROR_H
#define ERROR_H

#include <QString>

void error(const QString& message);
void syntaxError();
void syntaxError(const QString& message);
void semanticError(const QString& message);
void check(bool condition, const QString& message);

#endif // ERROR_H
