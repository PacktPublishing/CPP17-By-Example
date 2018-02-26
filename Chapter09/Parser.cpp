#include <CAssert>
using namespace std;

#include "Value.h"
#include "Token.h"
#include "Scanner.h"
#include "Parser.h"
#include "Error.h"

Parser::Parser(Scanner& m_scanner, QList<Action>& actionList)
 :m_scanner(m_scanner),
  m_actionList(actionList) {
  m_lookAHead = m_scanner.nextToken();
  instructionList();
  match(EndOfFileId);
}

extern int g_lineNo;

void Parser::instructionList() {
  while (m_lookAHead.id() != EndOfFileId) {
    instruction();
  }
}

void Parser::match(TokenId tokenId) {
  if (m_lookAHead.id() != tokenId) {
    syntaxError();
  }

  m_lookAHead = m_scanner.nextToken();
}

void Parser::instruction() {
  TokenId tokenId = m_lookAHead.id();

  switch (tokenId) {
    case NameId: {
        QString assignName = m_lookAHead.name();
        match(NameId);
        match(AssignId);
        Value assignValue = expression();
        match(SemicolonId);
        check(!m_assignMap.contains(assignName),
              "the name \"" + assignName + "\" defined twiced");
        m_assignMap[assignName] = assignValue;
      }
      break;

    case SetPenColorId:
    case SetPenStyleId:
    case SetBrushColorId:
    case SetBrushStyleId:
    case SetFontId:
    case SetHorizontalAlignmentId:
    case SetVerticalAlignmentId: {
        match(tokenId);
        match(LeftParenthesisId);
        Value value = expression();
        match(RightParenthesisId);
        match(SemicolonId);
        checkType(tokenId, value);
        m_actionList.push_back(Action(tokenId, value));
      }
      break;

    case DrawLineId:
    case DrawRectangleId:
    case DrawEllipseId:
    case DrawTextId: {
        match(tokenId);
        match(LeftParenthesisId);
        Value firstValue = expression();
        match(CommaId);
        Value secondValue = expression();
        match(RightParenthesisId);
        match(SemicolonId);
        checkType(tokenId, firstValue, secondValue);
        m_actionList.push_back(Action(tokenId, firstValue,
                                      secondValue));
      }
      break;

    default:
      syntaxError();
  }
}

Value Parser::expression() {
  Value leftValue = mulDivExpression ();
  return expressionRest(leftValue);
}

Value Parser::expressionRest(Value leftValue) {
  TokenId tokenId = m_lookAHead.id();

  switch (tokenId) {
    case AddId:
    case SubtractId: {
        match(tokenId);
        Value rightValue = mulDivExpression();
        check(leftValue.isNumerical() && rightValue.isNumerical(),
              "non-numerical values in arithmetic expression");
        Value resultValue =
          evaluate(tokenId, leftValue, rightValue);
        return expressionRest(resultValue);      }

    default:
      return leftValue;
  }
}

Value Parser::mulDivExpression() {
  Value leftValue = primaryExpression();
  return mulDivExpressionRest(leftValue);
}

Value Parser::mulDivExpressionRest(Value leftValue) {
  TokenId tokenId = m_lookAHead.id();

  switch (tokenId) {
    case MultiplyId:
    case DivideId: {
        match(tokenId);
        Value rightValue = primaryExpression();
        check(leftValue.isNumerical() && rightValue.isNumerical(),
              "non-numerical values in arithmetic expression");
        Value resultValue =
          evaluate(tokenId, leftValue, rightValue);
        return mulDivExpressionRest (resultValue);
      }

    default:
      return leftValue;
  }
}

Value Parser::primaryExpression() {
  TokenId tokenId = m_lookAHead.id();

  switch (tokenId) {
    case XCoordinateId:
    case YCoordinateId: {
        match(tokenId);
        match(LeftParenthesisId);
        Value value = expression();
        match(RightParenthesisId);
        check(value.isPoint(),
              "not a point in coordinate expression");
        checkType(tokenId, value);
        return evaluate(tokenId, value);
      }
      break;

    case PointId: {
        match(PointId);
        match(LeftParenthesisId);
        Value xValue = expression();
        match(CommaId);
        Value yValue = expression();
        match(RightParenthesisId);
        check(xValue.isNumerical() && yValue.isNumerical(),
              "non-numerical values in point expression");
        return Value(QPoint(xValue.numericalValue(),
                            yValue.numericalValue()));
    }

    case ColorId: {
        match(ColorId);
        match(LeftParenthesisId);
        Value redValue = expression();
        match(CommaId);
        Value greenValue = expression();
        match(CommaId);
        Value blueValue = expression();
        match(RightParenthesisId);
        check(redValue.isNumerical() && greenValue.isNumerical()
              && blueValue.isNumerical(),
              "non-numerical values in color expression");
        return Value(QColor(redValue.numericalValue(),
                            greenValue.numericalValue(),
                            blueValue.numericalValue()));
      }

    case FontId: {
        match(FontId);
        match(LeftParenthesisId);
        Value nameValue = expression();
        match(CommaId);
        Value sizeValue = expression();
        match(RightParenthesisId);
        check(nameValue.isString() && sizeValue.isNumerical(),
              "invalid types in font expression");
        return Value(QFont(nameValue.stringValue(),
                           sizeValue.numericalValue()));
      }

    case LeftParenthesisId: {
        match(LeftParenthesisId);
        Value value = expression();
        match(RightParenthesisId);
        return value;
      }

    case NameId: {
        QString lookupName = m_lookAHead.name();
        match(NameId);
        check(m_assignMap.contains(lookupName ),
              "unknown name: \"" + lookupName + "\".");
        return m_assignMap[lookupName ];
      }

    case ValueId: {
        Value value = m_lookAHead.value();
        match(ValueId);
        return value;
      }

    default:
      syntaxError();
      return Value();
  }
}

void Parser::checkType(TokenId codeId, const Value& value) {
  switch (codeId) {
    case SetPenStyleId:
      check(value.isPenStyle(), "not a pen-style value");
      break;

    case SetBrushStyleId:
      check(value.isBrushStyle(), "not a brush-style value");
      break;

    case SetPenColorId:
    case SetBrushColorId:
      check(value.isColor(), "not a color value");
      break;

    case SetFontId:
      check(value.isFont(), "not a font value");
      break;

    case SetHorizontalAlignmentId:
    case SetVerticalAlignmentId:
      check(value.isAlignment(), "not an alignment value");
      break;

    case XCoordinateId:
    case YCoordinateId:
      check(value.isPoint(), "not a point value");
      break;
  }
}

void Parser::checkType(TokenId codeId, const Value& leftValue,
                       const Value& rightValue) {
  switch (codeId) {
    case DrawLineId:
    case DrawRectangleId:
    case DrawEllipseId:
      check(leftValue.isPoint() && rightValue.isPoint(),
            "non-point values in draw expression");
      break;

    case DrawTextId:
      check(leftValue.isPoint() && rightValue.isString(),
            "invalid values in text-drawing expression");
      break;
  }
}

Value Parser::evaluate(TokenId codeId, const Value& value) {
  switch (codeId) {
    case XCoordinateId:
      return Value((double) value.pointValue().x());

    case YCoordinateId:
      return Value((double) value.pointValue().y());

    default:
      assert(false);
      return false;
  }
}

Value Parser::evaluate(TokenId codeId, const Value& leftValue,
                          const Value& rightValue) {
  double leftNumericalValue = leftValue.numericalValue(),
         rightNumericalValue = rightValue.numericalValue();

  switch (codeId) {
    case AddId:
      return Value(leftNumericalValue + rightNumericalValue);

    case SubtractId:
      return Value(leftNumericalValue - rightNumericalValue);

    case MultiplyId:
      return Value(leftNumericalValue * rightNumericalValue);

    case DivideId:
      if (rightNumericalValue == 0) {
        semanticError("division by zero");
      }

      return Value(leftNumericalValue / rightNumericalValue);

    case PointId:
      return Value(QPoint(leftNumericalValue,
                          rightNumericalValue));

    default:
      assert(false);
      return Value();
  }
}
