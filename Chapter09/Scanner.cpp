#include <SStream>
#include <IOStream>
#include <Exception>
using namespace std;

#include "Error.h"
#include "Scanner.h"

QMap<QString,Value> Scanner::m_valueMap;
QMap<QString,TokenId> Scanner::m_keywordMap;
QList<pair<QString, TokenId>> Scanner::m_operatorList;

extern int g_lineNo;

#define ADD_TO_TOKEN_LIST(text, token)                     \
  m_operatorList.push_back(pair<QString,TokenId>(text, token));

#define ADD_TO_KEYWORD_MAP(x) {                       \
  QString s(#x);                                      \
  m_keywordMap[s.toLower().left(s.length() - 2)] = x; }

#define ADD_TO_VALUE_MAP(x) {                          \
  QString s(#x);                                       \
  QString t = s.toLower();                             \
  int i = t.lastIndexOf("::");                         \
  m_valueMap[(i == -1) ? t : t.mid(i + 2)] = Value(x); }

void Scanner::init() {
  ADD_TO_TOKEN_LIST("+", AddId)
  ADD_TO_TOKEN_LIST("-", SubtractId)
  ADD_TO_TOKEN_LIST("*", MultiplyId)
  ADD_TO_TOKEN_LIST("/", DivideId)
  ADD_TO_TOKEN_LIST("(", LeftParenthesisId)
  ADD_TO_TOKEN_LIST(")", RightParenthesisId)
  ADD_TO_TOKEN_LIST("=", AssignId)
  ADD_TO_TOKEN_LIST(",", CommaId)
  ADD_TO_TOKEN_LIST(";", SemicolonId)

  ADD_TO_KEYWORD_MAP(ColorId)
  ADD_TO_KEYWORD_MAP(DrawEllipseId)
  ADD_TO_KEYWORD_MAP(DrawLineId)
  ADD_TO_KEYWORD_MAP(DrawRectangleId)
  ADD_TO_KEYWORD_MAP(DrawTextId)
  ADD_TO_KEYWORD_MAP(FontId)
  ADD_TO_KEYWORD_MAP(PointId)
  ADD_TO_KEYWORD_MAP(SetBrushColorId)
  ADD_TO_KEYWORD_MAP(SetBrushStyleId)
  ADD_TO_KEYWORD_MAP(SetFontId)
  ADD_TO_KEYWORD_MAP(SetHorizontalAlignmentId)
  ADD_TO_KEYWORD_MAP(SetPenColorId)
  ADD_TO_KEYWORD_MAP(SetPenStyleId)
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
 :m_buffer(buffer) {
  m_buffer.append('\0');
}

Token Scanner::nextToken() {
  while (true) {
    if (m_buffer[m_bufferIndex] == '\n') {
      ++g_lineNo;
      ++m_bufferIndex;
    }
    else if (m_buffer[m_bufferIndex].isSpace()) {
      ++m_bufferIndex;
    }
    else if (m_buffer.indexOf("//", m_bufferIndex) ==
             m_bufferIndex) {
      while ((m_buffer[m_bufferIndex] != QChar('\n')) &&
             (m_buffer[m_bufferIndex] != QChar('\0'))) {
        ++m_bufferIndex;
      }
    }
    else {
      break;
    }
  }

  if (m_buffer[m_bufferIndex] == QChar('\0')) {
    return Token(EndOfFileId);
  }

  for (const pair<QString,TokenId>& pair : m_operatorList) {
    const QString& operatorText = pair.first;
    TokenId tokenId = pair.second;

    if (m_buffer.indexOf(operatorText, m_bufferIndex) == m_bufferIndex) {
      m_bufferIndex += operatorText.length();
      return Token(tokenId);
    }
  }

  if (m_buffer[m_bufferIndex].isLetter() ||
      (m_buffer[m_bufferIndex] == '_')) {
    int index = m_bufferIndex;

    while (m_buffer[index].isLetterOrNumber() ||
           (m_buffer[index] == '_')) {
      ++index;
    }

    int size = index - m_bufferIndex;
    QString text = m_buffer.mid(m_bufferIndex, size).toLower();
    m_bufferIndex += size;

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

  if (m_buffer[m_bufferIndex] == '\"') {
    int index = m_bufferIndex + 1;

    while (m_buffer[index] != '\"') {
      if (m_buffer[index] == QChar('\0')) {
        syntaxError("unfinished string");
      }

      ++index;
    }

    int size = index - m_bufferIndex + 1;
    QString text = m_buffer.mid(m_bufferIndex, size);
    m_bufferIndex += size;
    return Token(ValueId, Value(text));
  }

  if (m_buffer[m_bufferIndex].isDigit()) {
    int index = m_bufferIndex;
    
    while (m_buffer[index].isDigit()) {
      ++index;
    }

    if (m_buffer[index] == '.') {
      ++index;

      while (m_buffer[index].isDigit()) {
        ++index;
      }
    }

    int size = index - m_bufferIndex;
    QString text = m_buffer.mid(m_bufferIndex, size);
    m_bufferIndex += size;
    return Token(ValueId, Value(text.toDouble()));
  }

  syntaxError();
  return Token(EndOfFileId);
}
