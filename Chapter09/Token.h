#ifndef TOKEN_H
#define TOKEN_H

#include <QWidget>
#include "Value.h"

enum TokenId {ColorId, DrawEllipseId, DrawLineId,
              DrawRectangleId, DrawTextId, FontId,
              PointId, SetBrushColorId, SetBrushStyleId,
              SetFontId, SetHorizontalAlignmentId,
              SetPenColorId, SetPenStyleId,
              SetVerticalAlignmentId,
              XCoordinateId, YCoordinateId,
              AddId, SubtractId, MultiplyId, DivideId,
              LeftParenthesisId, RightParenthesisId,
              AssignId, CommaId, SemicolonId,
              NameId, ValueId, EndOfFileId};

class Token{
  public:
    Token();
    Token(TokenId tokenId);
    Token(TokenId tokenId, const QString& name);
    Token(TokenId tokenId, const Value& value);

    TokenId id() const {return m_tokenId;}
    const QString& name() const { return m_name; }
    const Value& value() const { return m_value; }

  private:
    TokenId m_tokenId;
    QString m_name;
    Value m_value;
};

#endif // TOKEN_H
