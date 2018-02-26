#ifndef TOKEN_H
#define TOKEN_H

#include <QWidget>
#include "Value.h"

enum TokenId {BlockId, CallId, ElseId, FunctionId, GotoId,
              IfId, IfNotGotoId, ReturnId, WhileId,
              ColorId, DrawEllipseId,
              DrawLineId, DrawRectangleId, DrawTextId,
              FontId, PointId, RestoreId,
              SaveId, SetRotateId, SetBrushColorId,
              SetBrushStyleId, SetFontId,
              SetHorizontalAlignmentId, SetOriginId,
              SetPenColorId, SetPenStyleId, SetScaleId,
              SetVerticalAlignmentId,
              XCoordinateId, YCoordinateId,
              AndId, OrId, NotId,
              AddId, UnaryAddId, SubtractId, UnarySubtractId,
              MultiplyId, DivideId, ModulusId,
              EqualId, NotEqualId, LessThanId, LessThanEqualId,
              GreaterThanId, GreaterThanEqualId,
              LeftParenthesisId, RightParenthesisId,
              LeftBracketId, RightBracketId,
              AssignId, CommaId, SemicolonId,
              NameId, ValueId, EndOfFileId};

class Token{
  public:
    Token();
    Token(TokenId tokenId);
    Token(TokenId tokenId, const QString& name);
    Token(TokenId tokenId, const Value& value);

    Token(const Token& token);
    Token operator=(const Token& token);

    TokenId id() const {return m_tokenId;}
    const QString& name() const { return m_name; }
    const Value& value() const { return m_value; }

  private:
    TokenId m_tokenId;
    QString m_name;
    Value m_value;
};

#endif // TOKEN_H
