#include <SStream>
#include <IOStream>
#include <Exception>
using namespace std;

#include "Error.h"
#include "Scanner.h"

#include <QtWidgets>

QMap<QString,Value> Scanner::m_valueMap;
QMap<QString,TokenId> Scanner::m_keywordMap;
QList<pair<QString, TokenId>> Scanner::m_tokenList;

extern int g_lineNo;

#define ADD_TO_TOKEN_LIST(text, token) m_tokenList.push_back(pair<QString,TokenId>(text, token));
#define ADD_TO_KEYWORD_MAP(x) { QString s(#x); m_keywordMap[s.toLower().left(s.length() - 2)] = x; }
#define ADD_TO_VALUE_MAP(x) { QString s(#x); QString t = s.toLower(); int i = t.lastIndexOf("::"); m_valueMap[(i == -1) ? t : t.mid(i + 2)] = Value(x); }

void Scanner::init() {
  ADD_TO_TOKEN_LIST("+", AddId)
  ADD_TO_TOKEN_LIST("-", SubtractId)
  ADD_TO_TOKEN_LIST("*", MultiplyId)
  ADD_TO_TOKEN_LIST("/", DivideId)
  ADD_TO_TOKEN_LIST("%", ModulusId)
  ADD_TO_TOKEN_LIST("==", EqualId)
  ADD_TO_TOKEN_LIST("!=", NotEqualId)
  ADD_TO_TOKEN_LIST("<=", LessThanEqualId)
  ADD_TO_TOKEN_LIST("<", LessThanId)
  ADD_TO_TOKEN_LIST(">=", GreaterThanEqualId)
  ADD_TO_TOKEN_LIST(">", GreaterThanId)
  ADD_TO_TOKEN_LIST("(", LeftParenthesisId)
  ADD_TO_TOKEN_LIST(")", RightParenthesisId)
  ADD_TO_TOKEN_LIST("{", LeftBracketId)
  ADD_TO_TOKEN_LIST("}", RightBracketId)
  ADD_TO_TOKEN_LIST("=", AssignId)
  ADD_TO_TOKEN_LIST(",", CommaId)
  ADD_TO_TOKEN_LIST(";", SemicolonId)

  ADD_TO_KEYWORD_MAP(CallId)
  ADD_TO_KEYWORD_MAP(ElseId)
  ADD_TO_KEYWORD_MAP(FunctionId)
  ADD_TO_KEYWORD_MAP(IfId)
  ADD_TO_KEYWORD_MAP(ReturnId)
  ADD_TO_KEYWORD_MAP(WhileId)
  ADD_TO_KEYWORD_MAP(AndId)
  ADD_TO_KEYWORD_MAP(ColorId)
  ADD_TO_KEYWORD_MAP(DrawEllipseId)
  ADD_TO_KEYWORD_MAP(DrawLineId)
  ADD_TO_KEYWORD_MAP(DrawRectangleId)
  ADD_TO_KEYWORD_MAP(DrawTextId)
  ADD_TO_KEYWORD_MAP(FontId)
  ADD_TO_KEYWORD_MAP(NotId)
  ADD_TO_KEYWORD_MAP(OrId)
  ADD_TO_KEYWORD_MAP(PointId)
  ADD_TO_KEYWORD_MAP(RestoreId)
  ADD_TO_KEYWORD_MAP(SaveId)
  ADD_TO_KEYWORD_MAP(SetRotateId)
  ADD_TO_KEYWORD_MAP(SetBrushColorId)
  ADD_TO_KEYWORD_MAP(SetBrushStyleId)
  ADD_TO_KEYWORD_MAP(SetFontId)
  ADD_TO_KEYWORD_MAP(SetHorizontalAlignmentId)
  ADD_TO_KEYWORD_MAP(SetOriginId)
  ADD_TO_KEYWORD_MAP(SetPenColorId)
  ADD_TO_KEYWORD_MAP(SetPenStyleId)
  ADD_TO_KEYWORD_MAP(SetScaleId)
  ADD_TO_KEYWORD_MAP(SetVerticalAlignmentId)
  ADD_TO_KEYWORD_MAP(XCoordinateId)
  ADD_TO_KEYWORD_MAP(YCoordinateId)

  ADD_TO_VALUE_MAP(true)
  ADD_TO_VALUE_MAP(false)

  ADD_TO_VALUE_MAP(Qt::AlignLeft)
  ADD_TO_VALUE_MAP(Qt::AlignHCenter)
  ADD_TO_VALUE_MAP(Qt::AlignRight)
  ADD_TO_VALUE_MAP(Qt::AlignTop)
  ADD_TO_VALUE_MAP(Qt::AlignVCenter)
  ADD_TO_VALUE_MAP(Qt::AlignBottom)

  ADD_TO_VALUE_MAP(Qt::PenStyle::NoPen)
  ADD_TO_VALUE_MAP(Qt::PenStyle::SolidLine)
  ADD_TO_VALUE_MAP(Qt::PenStyle::DashLine)
  ADD_TO_VALUE_MAP(Qt::PenStyle::DotLine)
  ADD_TO_VALUE_MAP(Qt::PenStyle::DashDotLine)
  ADD_TO_VALUE_MAP(Qt::PenStyle::DashDotDotLine)

  ADD_TO_VALUE_MAP(Qt::BrushStyle::NoBrush)
  ADD_TO_VALUE_MAP(Qt::BrushStyle::SolidPattern)
  ADD_TO_VALUE_MAP(Qt::BrushStyle::Dense1Pattern)
  ADD_TO_VALUE_MAP(Qt::BrushStyle::Dense2Pattern)
  ADD_TO_VALUE_MAP(Qt::BrushStyle::Dense3Pattern)
  ADD_TO_VALUE_MAP(Qt::BrushStyle::Dense4Pattern)
  ADD_TO_VALUE_MAP(Qt::BrushStyle::Dense5Pattern)
  ADD_TO_VALUE_MAP(Qt::BrushStyle::Dense6Pattern)
  ADD_TO_VALUE_MAP(Qt::BrushStyle::Dense7Pattern)
  ADD_TO_VALUE_MAP(Qt::BrushStyle::HorPattern)
  ADD_TO_VALUE_MAP(Qt::BrushStyle::VerPattern)
  ADD_TO_VALUE_MAP(Qt::BrushStyle::CrossPattern)
  ADD_TO_VALUE_MAP(Qt::BrushStyle::BDiagPattern)
  ADD_TO_VALUE_MAP(Qt::BrushStyle::FDiagPattern)
  ADD_TO_VALUE_MAP(Qt::BrushStyle::DiagCrossPattern)

  ADD_TO_VALUE_MAP(Aqua)
  ADD_TO_VALUE_MAP(Black)
  ADD_TO_VALUE_MAP(Blue)
  ADD_TO_VALUE_MAP(Brown)
  ADD_TO_VALUE_MAP(Cyan)
  ADD_TO_VALUE_MAP(Gray)
  ADD_TO_VALUE_MAP(Green)
  ADD_TO_VALUE_MAP(Lime)
  ADD_TO_VALUE_MAP(Magenta)
  ADD_TO_VALUE_MAP(Navyblue)
  ADD_TO_VALUE_MAP(Orange)
  ADD_TO_VALUE_MAP(Orchid)
  ADD_TO_VALUE_MAP(Pink)
  ADD_TO_VALUE_MAP(Purple)
  ADD_TO_VALUE_MAP(Red)
  ADD_TO_VALUE_MAP(Silver)
  ADD_TO_VALUE_MAP(Snow)
  ADD_TO_VALUE_MAP(SteelBlue)
  ADD_TO_VALUE_MAP(SystemColor)
  ADD_TO_VALUE_MAP(Turquoise)
  ADD_TO_VALUE_MAP(Violet)
  ADD_TO_VALUE_MAP(White)
  ADD_TO_VALUE_MAP(Yellow)
}

Scanner::Scanner(QString& buffer)
 :m_buffer(buffer.toLower()) {
  m_buffer.append('\0');
}

Token Scanner::NextToken() {
  while (true) {
    if (m_buffer[0] == '\n') {
      ++g_lineNo;
      m_buffer.remove(0, 1);
    }
    else if (m_buffer[0].isSpace()) {
      m_buffer.remove(0, 1);
    }
    else if (m_buffer.indexOf("//") == 0) {
      m_buffer.remove(0, 2);

      while ((m_buffer[0] != QChar('\n')) &&
             (m_buffer[0] != QChar('\0'))) {
        m_buffer.remove(0, 1);
      }
    }
    else {
      break;
    }
  }

  if (m_buffer[0] == QChar('\0')) {
    return Token(EndOfFileId);
  }

  for (const pair<QString,TokenId>& pair : m_tokenList) {
    const QString& operatorText = pair.first;
    TokenId tokenId = pair.second;

    if (m_buffer.indexOf(operatorText) == 0) {
      m_buffer.remove(0, operatorText.length());
      return Token(tokenId);
    }
  }

  if (m_buffer[0].isLetter() || (m_buffer[0] == '_')) {
    int index = 0;
    while (m_buffer[index].isLetterOrNumber() ||
           (m_buffer[index] == '_')) {
      ++index;
    }

    QString text = m_buffer.left(index);
    m_buffer.remove(0, index);

    if (m_keywordMap.contains(text)) {
      return Token(m_keywordMap[text]);
    }
    else if (m_valueMap.contains(text)) {
      return Token(ValueId, m_valueMap[text]);
    }
    else {
      return Token(NameId, text);
    }
  }

  if (m_buffer[0] == '\"') {
    m_buffer.remove(0, 1);
    
    int index = 0;
    while (m_buffer[index] != '\"') {
      if (m_buffer[index] == QChar('\0')) {
        syntaxError("unfinished string");
      }

      ++index;
    }

    QString text = m_buffer.left(index);
    m_buffer.remove(0, index + 1);
    return Token(ValueId, Value(text));
  }

  if (m_buffer[0].isDigit()) {
    int index = 0;
    
    while (m_buffer[index].isDigit()) {
      ++index;
    }

    if (m_buffer[index] == '.') {
      ++index;

      while (m_buffer[index].isDigit()) {
        ++index;
      }
    }

    QString text = m_buffer.left(index);
    m_buffer.remove(0, index);
    return Token(ValueId, Value(text.toDouble()));
  }

  QString s = m_buffer;
  syntaxError();
  return Token(EndOfFileId);
}
