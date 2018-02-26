#include <CAssert>
using namespace std;

#include "Error.h"
#include "Evaluator.h"

Evaluator::Evaluator(const QList<Directive>& directiveList,
                     QList<Action>& actionList,
                     QMap<QString,Function> functionMap) {
  int index = 0;
  while (true) {
    Directive directive = directiveList[index];
    TokenId directiveId = directive.directiveId();

    switch (directiveId) {
      case FunctionId: {
          const Function& function = directive.function();
          const QList<QString>& nameList = function.nameList();

          for (int listIndex = ((int) nameList.size() - 1);
               listIndex >= 0; --listIndex) {
            const QString& name = nameList[listIndex];
            m_valueMap[name] = m_valueStack.pop();
          }
        }
        ++index;
        break;

      case CallId: {
          QString name = directive.name();
          check(functionMap.contains(name),
                "missing function: \"" + name + "\"");
          Function function = functionMap[name];
          check(directive.parameters() ==
                function.nameList().size(),
                "invalid number of parameters");

          m_returnAddressStack.push(index + 1);
          m_valueMapStack.push(m_valueMap);
          m_valueMap.clear();
          index = function.address();
        }
        break;

      case ReturnId:
        if (!m_returnAddressStack.empty()) {
          m_valueMap = m_valueMapStack.pop();
          index = m_returnAddressStack.pop();
        }
        else {
          return;
        }
        break;

      case IfNotGotoId: {
          Value value = m_valueStack.pop();
          checkType(IfNotGotoId, value);

          if (!value.booleanValue()) {
            index = directive.address();
          }
          else {
            ++index;
          }
        }
        break;

      case GotoId:
        index = directive.address();
        break;

      case SaveId:
      case RestoreId:
        actionList.push_back(Action(directiveId));
        ++index;
        break;

      case SetPenColorId:
      case SetPenStyleId:
      case SetBrushColorId:
      case SetBrushStyleId:
      case SetFontId:
      case SetHorizontalAlignmentId:
      case SetVerticalAlignmentId:
      case SetScaleId:
      case SetRotateId:
      case SetOriginId: {
          Value value = m_valueStack.pop();
          checkType(directiveId, value);
          actionList.push_back(Action(directiveId, value));
          ++index;
        }
        break;

      case DrawLineId:
      case DrawRectangleId:
      case DrawEllipseId:
      case DrawTextId: {
          Value secondValue = m_valueStack.pop();
          Value firstValue = m_valueStack.pop();
          checkType(directiveId, firstValue, secondValue);
          actionList.push_back(Action(directiveId, firstValue,
                                      secondValue));
          ++index;
        }
        break;

      case AssignId: {
          Value value = m_valueStack.pop();
          m_valueMap[directive.name()] = value;
          ++index;
        }
        break;

      case OrId:
      case AndId:
      case EqualId:
      case NotEqualId:
      case LessThanId:
      case LessThanEqualId:
      case GreaterThanId:
      case GreaterThanEqualId:
      case AddId:
      case SubtractId:
      case MultiplyId:
      case DivideId:
      case ModulusId:
      case PointId: {
          Value rightValue = m_valueStack.pop();
          Value leftValue = m_valueStack.pop();
          checkType(directiveId, leftValue, rightValue);
          Value resultValue =
            evaluate(directiveId, leftValue, rightValue);
          m_valueStack.push(resultValue);
          ++index;
        }
        break;

      case NotId:
      case UnaryAddId:
      case UnarySubtractId:
      case XCoordinateId:
      case YCoordinateId: {
          Value value = m_valueStack.pop();
          checkType(directiveId, value);
          Value resultValue = evaluate(directiveId, value);
          m_valueStack.push(resultValue);
          ++index;
        }
        break;

      case ColorId: {
          Value blueValue = m_valueStack.pop();
          Value greenValue = m_valueStack.pop();
          Value redValue = m_valueStack.pop();
          check(redValue.isNumerical() && greenValue.isNumerical() &&
                blueValue.isNumerical(),
                "non-numerical values in color expression");
          QColor color(redValue.numericalValue(),
                       greenValue.numericalValue(),
                       blueValue.numericalValue());
          m_valueStack.push(Value(color));
          ++index;
        }
        break;

      case FontId: {
          Value italicValue = m_valueStack.pop();
          Value boldValue = m_valueStack.pop();
          Value sizeValue = m_valueStack.pop();
          Value nameValue = m_valueStack.pop();
          check(nameValue.isString() && sizeValue.isNumerical() &&
                boldValue.isBoolean() && italicValue.isBoolean(),
                "invalid values in font expression");
          QFont font(nameValue.stringValue(),
                     sizeValue.numericalValue(),
                     boldValue.booleanValue(),
                     italicValue.booleanValue());
          m_valueStack.push(Value(font));
          ++index;
        }
        break;

      case NameId: {
          QString name = directive.name();
          check(m_valueMap.contains(name),
                "unknown name: \"" + name +"\"");
          m_valueStack.push(m_valueMap[name]);
          ++index;
        }
        break;

      case ValueId:
        m_valueStack.push(directive.value());
        ++index;
        break;
    }
  }
}

void Evaluator::checkType(TokenId directiveId, const Value& value) {
  switch (directiveId) {
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

    case NotId:
      check(value.isBoolean(), "not a boolean value");
      break;

    case UnaryAddId:
    case UnarySubtractId:
    case SetRotateId:
      check(value.isNumerical(), "not a numerical value");
      break;

    case SetOriginId:
    case XCoordinateId:
    case YCoordinateId:
      check(value.isPoint(), "not a point value");
      break;
  }
}

void Evaluator::checkType(TokenId directiveId, const Value& leftValue,
                          const Value& rightValue) {
  switch (directiveId) {
    case OrId:
    case AndId:
      check(leftValue.isBoolean() && rightValue.isBoolean(),
            "non-boolean values in boolean expression");
      break;

    case EqualId:
    case NotEqualId:
    case LessThanId:
    case LessThanEqualId:
    case GreaterThanId:
    case GreaterThanEqualId:
    case AddId:
    case SubtractId:
    case MultiplyId:
    case DivideId:
    case ModulusId:
    case PointId:
    case SetScaleId:
      check(leftValue.isNumerical() && rightValue.isNumerical(),
            "non-numerical values in numerical expression");
      break;

    case DrawLineId:
    case DrawRectangleId:
    case DrawEllipseId:
      check(leftValue.isPoint() && rightValue.isPoint(),
            "non-point values in draw expression");
      break;

    case DrawTextId:
      check(leftValue.isPoint() && rightValue.isString(),
            "non-point values in draw expression");
      break;
  }
}

Value Evaluator::evaluate(TokenId directiveId, const Value& value) {
  switch (directiveId) {
    case NotId:
      return Value(!value.booleanValue());

    case UnaryAddId:
      return Value(+value.numericalValue() );

    case UnarySubtractId:
      return Value(-value.numericalValue() );

    case XCoordinateId:
      return Value((double) value.pointValue().x());

    case YCoordinateId:
      return Value((double) value.pointValue().y());

    default:
      assert(false);
      return false;
  }
}

Value Evaluator::evaluate(TokenId directiveId, const Value& leftValue,
                          const Value& rightValue) {
  bool leftBooleanValue = leftValue.booleanValue(),
       rightBooleanValue = rightValue.booleanValue();
  double leftNumericalValue = leftValue.numericalValue(),
         rightNumericalValue = rightValue.numericalValue();

  switch (directiveId) {
    case OrId:
      return Value(leftBooleanValue || rightBooleanValue);

    case AndId:
      return Value(leftBooleanValue && rightBooleanValue);

    case EqualId:
      return Value(leftNumericalValue == rightNumericalValue);

    case NotEqualId:
      return Value(leftNumericalValue != rightNumericalValue);

    case LessThanId:
      return Value(leftNumericalValue < rightNumericalValue);

    case LessThanEqualId:
      return Value(leftNumericalValue <= rightNumericalValue);

    case GreaterThanId:
      return Value(leftNumericalValue > rightNumericalValue);

    case GreaterThanEqualId:
      return Value(leftNumericalValue >= rightNumericalValue);

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

    case ModulusId:
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
