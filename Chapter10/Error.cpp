#include <SStream>
#include <Exception>
using namespace std;

#include "Error.h"

extern int g_lineNo = 1;

void error(const QString& message) {
  throw exception(message.toStdString().c_str());
}

void syntaxError() {
  stringstream stringStream;
  stringStream << "Syntax error at line "
               << g_lineNo << ".";
  error(stringStream.str().c_str());
}

void syntaxError(const QString& message) {
  stringstream stringStream;
  stringStream << "Syntax error at line " << g_lineNo
               << ": " << message.toStdString() << ".";
  error(stringStream.str().c_str());
}

void semanticError(const QString& message) {
  stringstream stringStream;
  stringStream << "Sematic error: " << message.toStdString() << ".";
  error(stringStream.str().c_str());
}

void check(bool condition, const QString& message) {
  if (!condition) {
    semanticError(message);
  }
}
