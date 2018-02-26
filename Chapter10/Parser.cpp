#include <CAssert>
using namespace std;

#include "Value.h"
#include "Token.h"
#include "Scanner.h"
#include "Parser.h"
#include "Error.h"

Parser::Parser(Scanner& m_scanner, QList<Directive>& directiveList,
               QMap<QString,Function>& functionMap)
 :m_scanner(m_scanner),
  m_directiveList(directiveList),
  m_functionMap(functionMap) {
  m_lookAHead = m_scanner.NextToken();
  m_directiveList.push_back(Directive(GotoId, 0));
  functionDefinitionList();
  match(EndOfFileId);
  check(m_functionMap.contains("main"),
        "function \"main\" is missing");
  m_directiveList[0].setAddress(m_functionMap["main"].address());
}

extern int g_lineNo;

void Parser::match(TokenId tokenId) {
  if (m_lookAHead.id() != tokenId) {
    syntaxError();
  }

  m_lookAHead = m_scanner.NextToken();
}

void Parser::functionDefinitionList() {
  while (m_lookAHead.id() != EndOfFileId) {
    functionDefinition();
  }
}

void Parser::functionDefinition() {
  match(FunctionId);
  QString name = m_lookAHead.name();
  match(NameId);
  match(LeftParenthesisId);
  QList<QString> nList = nameList();
  match(RightParenthesisId);
  int startAddress = (int) m_directiveList.size();
  Function function(nList, startAddress);
  m_directiveList.push_back(Directive(FunctionId, function));
  match(LeftBracketId);
  instructionList();
  match(RightBracketId);
  m_directiveList.push_back(Directive(ReturnId));
  check(!m_functionMap.contains(name),
        "function \"" + name + "\" already defined");
  check(!((name == "main") && (nList.size() > 0)),
        "function \"main\" cannot have parameters");
  m_functionMap[name] = function;
}

QList<QString> Parser::nameList() {
  QList <QString> nameList;

  while (m_lookAHead.id() != RightParenthesisId) {
    QString name = m_lookAHead.name();
    nameList.push_back(name);
    match(NameId);

    if (m_lookAHead.id() == RightParenthesisId) {
      break;
    }

    match(CommaId);
  }

  QSet<QString> nameSet;
  for (const QString& name : nameList) {
    if (nameSet.contains(name)) {
      semanticError("parameter \"" + name + "\" defined twice");
    }

    nameSet.insert(name);
  }

  return nameList;
}

/*void Parser::blockInstruction() {
  match(LeftBracketId);
  instructionList();
  match(RightBracketId);
}*/

void Parser::instructionList() {
  while (m_lookAHead.id() != RightBracketId) {
    instruction();
  }
}

void Parser::instruction() {
  switch (m_lookAHead.id()) {
    case CallId:
      callExpression();
      match(SemicolonId);
      break;

    case ReturnId:
      match(ReturnId);

      if (m_lookAHead.id() != SemicolonId) {
        expression();
      }

      m_directiveList.push_back(Directive(ReturnId));
      match(SemicolonId);
      break;

    case IfId: {
        match(IfId);
        match(LeftParenthesisId);
        expression();
        match(RightParenthesisId);

        int ifNotIndex = (int) m_directiveList.size();
        m_directiveList.push_back(Directive(IfNotGotoId, 0));
        instruction();

        if (m_lookAHead.id() == ElseId) {
          match(ElseId);
          int elseIndex = (int) m_directiveList.size();
          m_directiveList.push_back(Directive(GotoId, 0));
          m_directiveList[ifNotIndex].setAddress((int) m_directiveList.size());
          instruction();
          m_directiveList[elseIndex].setAddress((int) m_directiveList.size());
        }
        else {
          m_directiveList[ifNotIndex].setAddress((int) m_directiveList.size());
        }
      }
      break;

    case WhileId: {
        match(WhileId);
        int whileIndex = (int) m_directiveList.size();
        match(LeftParenthesisId);
        expression();
        match(RightParenthesisId);
        int ifNotIndex = (int) m_directiveList.size();
        m_directiveList.push_back(Directive(IfNotGotoId, 0));
        instruction();
        m_directiveList.push_back(Directive(GotoId, whileIndex));
        m_directiveList[ifNotIndex].setAddress((int) m_directiveList.size());
      }
      break;

    case LeftBracketId:
      match(LeftBracketId);
      instructionList();
      match(RightBracketId);
      break;

    case NameId: {
        QString name = m_lookAHead.name();
        match(NameId);
        match(AssignId);
        expression();
        match(SemicolonId);
        m_directiveList.push_back(Directive(AssignId, name));
      }
      break;

    case SaveId:
      saveInstruction();
      break;

    case RestoreId:
      restoreInstruction();
      break;

    case SetPenColorId:
      setPenColorInstruction();
      break;

    case SetPenStyleId:
      setPenStyleInstruction();
      break;

    case SetBrushColorId:
      setBrushColorInstruction();
      break;

    case SetBrushStyleId:
      setBrushStyleInstruction();
      break;

    case SetFontId:
      setFontInstruction();
      break;

    case SetHorizontalAlignmentId:
      setHorizontalAlignmentInstruction();
      break;

    case SetVerticalAlignmentId:
      setVerticalAlignmentInstruction();
      break;

    case SetScaleId:
      setScaleInstruction();
      break;

    case SetRotateId:
      setRotateInstruction();
      break;

    case SetOriginId:
      setOriginInstruction();
      break;

    case DrawLineId:
      drawLineInstruction();
      break;

    case DrawRectangleId:
      drawRectangleInstruction();
      break;

    case DrawEllipseId:
      drawEllipseInstruction();
      break;

    case DrawTextId:
      drawTextInstruction();
      break;

    default:
      syntaxError();
      break;
  }
}

void Parser::callInstruction() {
  callExpression();
  match(SemicolonId);
}

/*void Parser::returnInstruction() {
  match(ReturnId);

  if (m_lookAHead.id() != SemicolonId) {
    expression();
  }

  m_directiveList.push_back(Directive(ReturnId));
  match(SemicolonId);
}

void Parser::ifInstruction() {
  match(IfId);
  match(LeftParenthesisId);
  expression();
  match(RightParenthesisId);

  int ifNotIndex = (int) m_directiveList.size();
  m_directiveList.push_back(Directive(IfNotGotoId, 0));
  instruction();

  if (m_lookAHead.id() == ElseId) {
    match(ElseId);
    int elseIndex = (int) m_directiveList.size();
    m_directiveList.push_back(Directive(GotoId, 0));
    m_directiveList[ifNotIndex].setAddress((int) m_directiveList.size());
    instruction();
    m_directiveList[elseIndex].setAddress((int) m_directiveList.size());
  }
  else {
    m_directiveList[ifNotIndex].setAddress((int) m_directiveList.size());
  }
}

void Parser::whileInstruction() {
  match(WhileId);
  int whileIndex = (int) m_directiveList.size();
  match(LeftParenthesisId);
  expression();
  match(RightParenthesisId);
  int ifNotIndex = (int) m_directiveList.size();
  m_directiveList.push_back(Directive(IfNotGotoId, 0));
  instruction();
  m_directiveList.push_back(Directive(GotoId, whileIndex));
  m_directiveList[ifNotIndex].setAddress((int) m_directiveList.size());
}
*/

void Parser::saveInstruction() {
  match(SaveId);
  match(LeftParenthesisId);
  match(RightParenthesisId);
  match(SemicolonId);
  m_directiveList.push_back(Directive(SaveId));
}

void Parser::restoreInstruction() {
  match(RestoreId);
  match(LeftParenthesisId);
  match(RightParenthesisId);
  match(SemicolonId);
  m_directiveList.push_back(Directive(RestoreId));
}

void Parser::setPenColorInstruction() {
  match(SetPenColorId);
  match(LeftParenthesisId);
  expression();
  match(RightParenthesisId);
  match(SemicolonId);
  m_directiveList.push_back(Directive(SetPenColorId));
}

void Parser::setPenStyleInstruction() {
  match(SetPenStyleId);
  match(LeftParenthesisId);
  expression();
  match(RightParenthesisId);
  match(SemicolonId);
  m_directiveList.push_back(Directive(SetPenStyleId));
}

void Parser::setBrushColorInstruction() {
  match(SetBrushColorId);
  match(LeftParenthesisId);
  expression();
  match(RightParenthesisId);
  match(SemicolonId);
  m_directiveList.push_back(Directive(SetBrushColorId));
}

void Parser::setBrushStyleInstruction() {
  match(SetBrushStyleId);
  match(LeftParenthesisId);
  expression();
  match(RightParenthesisId);
  match(SemicolonId);
  m_directiveList.push_back(Directive(SetBrushStyleId));
}

void Parser::setFontInstruction() {
  match(SetFontId);
  match(LeftParenthesisId);
  expression();
  match(RightParenthesisId);
  match(SemicolonId);
  m_directiveList.push_back(Directive(SetFontId));
}

void Parser::setHorizontalAlignmentInstruction() {
  match(SetHorizontalAlignmentId);
  match(LeftParenthesisId);
  expression();
  match(RightParenthesisId);
  match(SemicolonId);
  m_directiveList.push_back(Directive(SetHorizontalAlignmentId));
}

void Parser::setVerticalAlignmentInstruction() {
  match(SetVerticalAlignmentId);
  match(LeftParenthesisId);
  expression();
  match(RightParenthesisId);
  match(SemicolonId);
  m_directiveList.push_back(Directive(SetVerticalAlignmentId));
}

void Parser::setScaleInstruction() {
  match(SetScaleId);
  match(LeftParenthesisId);
  expression();
  match(CommaId);
  expression();
  match(RightParenthesisId);
  match(SemicolonId);
  m_directiveList.push_back(Directive(SetScaleId));
}

void Parser::setRotateInstruction() {
  match(SetRotateId);
  match(LeftParenthesisId);
  expression();
  match(RightParenthesisId);
  match(SemicolonId);
  m_directiveList.push_back(Directive(SetRotateId));
}

void Parser::setOriginInstruction() {
  match(SetOriginId);
  match(LeftParenthesisId);
  expression();
  match(RightParenthesisId);
  match(SemicolonId);
  m_directiveList.push_back(Directive(SetOriginId));
}

void Parser::drawLineInstruction() {
  match(DrawLineId);
  match(LeftParenthesisId);
  expression();
  match(CommaId);
  expression();
  match(RightParenthesisId);
  match(SemicolonId);
  m_directiveList.push_back(Directive(DrawLineId));
}

void Parser::drawRectangleInstruction() {
  match(DrawRectangleId);
  match(LeftParenthesisId);
  expression();
  match(CommaId);
  expression();
  match(RightParenthesisId);
  match(SemicolonId);
  m_directiveList.push_back(Directive(DrawRectangleId));
}

void Parser::drawEllipseInstruction() {
  match(DrawEllipseId);
  match(LeftParenthesisId);
  expression();
  match(CommaId);
  expression();
  match(RightParenthesisId);
  match(SemicolonId);
  m_directiveList.push_back(Directive(DrawEllipseId));
}

void Parser::drawTextInstruction() {
  match(DrawTextId);
  match(LeftParenthesisId);
  expression();
  match(CommaId);
  expression();
  match(RightParenthesisId);
  match(SemicolonId);
  m_directiveList.push_back(Directive(DrawTextId));
}

/*void Parser::assignInstruction() {
  QString name = m_lookAHead.name();
  match(NameId);
  match(AssignId);
  expression();
  match(SemicolonId);
  m_directiveList.push_back(Directive(AssignId, name));
}*/

void Parser::expression() {
  andExpression();
  expressionRest();
}

void Parser::expressionRest() {
  switch (m_lookAHead.id()) {
    case OrId: {
        match(OrId);
        andExpression();
        m_directiveList.push_back(Directive(OrId));
        expressionRest();
      }
      break;
  }
}

void Parser::andExpression() {
  relationExpression();
  andExpressionRest();
}

void Parser::andExpressionRest() {
  switch (m_lookAHead.id()) {
    case AndId: {
        match(AndId);
        relationExpression();
        m_directiveList.push_back(Directive(AndId));
        andExpressionRest();
      }
      break;
  }
}

void Parser::relationExpression() {
  termExpression();
  relationExpressionRest();
}

void Parser::relationExpressionRest() {
  TokenId tokenId = m_lookAHead.id();

  switch (tokenId) {
    case EqualId:
    case NotEqualId:
    case LessThanId:
    case LessThanEqualId:
    case GreaterThanId:
    case GreaterThanEqualId: {
        match(tokenId);
        termExpression();
        m_directiveList.push_back(Directive(tokenId));
        relationExpressionRest();
      }
  }
}

void Parser::termExpression() {
  factorExpression();
  termExpressionRest();
}

void Parser::termExpressionRest() {
  TokenId tokenId = m_lookAHead.id();

  switch (tokenId) {
    case AddId:
    case SubtractId: {
          match(tokenId);
          factorExpression();
          m_directiveList.push_back(Directive(tokenId));
          termExpressionRest();
        }
  }
}

void Parser::factorExpression() {
  prefixExpression();
  factorExpressionRest();
}

void Parser::factorExpressionRest() {
  TokenId tokenId = m_lookAHead.id();

  switch (tokenId) {
    case MultiplyId:
    case DivideId:
    case ModulusId: {
          match(tokenId);
          prefixExpression();
          m_directiveList.push_back(Directive(tokenId));
          factorExpressionRest();
        }
  }
}

void Parser::prefixExpression() {
  switch (m_lookAHead.id()) {
    case AddId: {
        match(AddId);
        prefixExpression();
        m_directiveList.push_back(Directive(UnaryAddId));
      }
      break;

    case SubtractId: {
        match(SubtractId);
        prefixExpression();
        m_directiveList.push_back(Directive(UnarySubtractId));
      }
      break;

    case NotId: {
        match(NotId);
        prefixExpression();
        m_directiveList.push_back(Directive(NotId));
      }
      break;

    default:
      primaryExpression();
  }
}

void Parser::primaryExpression() {
  TokenId tokenId = m_lookAHead.id();

  switch (tokenId) {
    case PointId:
      pointExpression();
      break;

    case XCoordinateId:
    case YCoordinateId:
      coordinateExpression(tokenId);
      break;

    case ColorId:
      colorExpression();
      break;

    case FontId:
      fontExpression();
      break;

    case LeftParenthesisId: {
        match(LeftParenthesisId);
        expression();
        match(RightParenthesisId);
      }
      break;

    case ValueId: {
        Value value = m_lookAHead.value();
        match(ValueId);
        m_directiveList.push_back(Directive(ValueId, value));
      }
      break;

    case NameId: {
        QString name = m_lookAHead.name();
        match(NameId);
        m_directiveList.push_back(Directive(NameId, name));
      }
      break;

    case CallId:
      callExpression();
      break;

    default:
      syntaxError();
      break;
  }
}

void Parser::callExpression() {
  match(CallId);
  QString name = m_lookAHead.name();
  match(NameId);
  match(LeftParenthesisId);
  int size = expressionList();
  match(RightParenthesisId);
  m_directiveList.push_back(Directive(CallId, name, size));
}

int Parser::expressionList() {
  int size = 0;

  while (m_lookAHead.id() != RightParenthesisId) {
    expression();
    ++size;

    if (m_lookAHead.id() == RightParenthesisId) {
      break;
    }

    match(CommaId);
  }

  return size;
}

void Parser::pointExpression() {
  match(PointId);
  match(LeftParenthesisId);
  expression();
  match(CommaId);
  expression();
  match(RightParenthesisId);
  m_directiveList.push_back(Directive(PointId));
}

void Parser::coordinateExpression(TokenId tokenId) {
  match(tokenId);
  match(LeftParenthesisId);
  expression();
  match(RightParenthesisId);
  m_directiveList.push_back(Directive(tokenId));
}

void Parser::colorExpression() {
  match(ColorId);
  match(LeftParenthesisId);
  expression();
  match(CommaId);
  expression();
  match(CommaId);
  expression();
  match(RightParenthesisId);
  m_directiveList.push_back(Directive(ColorId));
}

void Parser::fontExpression() {
  match(FontId);
  match(LeftParenthesisId);
  expression();
  match(CommaId);
  expression();
  match(CommaId);
  expression();
  match(CommaId);
  expression();
  match(RightParenthesisId);
  m_directiveList.push_back(Directive(FontId));
}
