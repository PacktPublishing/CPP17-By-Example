#ifndef VALUE_H
#define VALUE_H

#include <IOStream>
using namespace std;

#include <QtWidgets>

enum TypeId {NumericalTypeId, StringTypeId, ColorTypeId,
             PenStyleTypeId, BrushStyleId, AlignmentTypeId,
             FontTypeId, PointTypeId};

class Value {
  public:
    Value();
    Value(double numericalValue);
    Value(const QString& stringValue);
    Value(const QPoint& pointValue);
    Value(const QColor& colorValue);
    Value(const QFont& fontValue);
    Value(const Qt::PenStyle& penStyleValue);
    Value(const Qt::BrushStyle& brushStyleValue);
    Value(const Qt::AlignmentFlag& alignment);

    Value(const Value& value);
    Value& operator=(const Value& value);

    bool isNumerical() const {return (m_typeId==NumericalTypeId);}
    bool isString() const { return (m_typeId == StringTypeId); }
    bool isColor() const { return (m_typeId == ColorTypeId); }
    bool isFont() const { return (m_typeId == FontTypeId); }
    bool isPoint() const { return (m_typeId == PointTypeId); }
    bool isPenStyle() const {return (m_typeId == PenStyleTypeId);}
    bool isBrushStyle() const {return (m_typeId == BrushStyleId);}
    bool isAlignment() const {return (m_typeId==AlignmentTypeId);}

    double numericalValue() const { return m_numericalValue; }
    const QString& stringValue() const { return m_stringValue; }
    const QColor& colorValue() const { return m_colorValue; }
    const QFont& fontValue() const { return m_fontValue; }
    const QPoint& pointValue() const { return m_pointValue; }
    const Qt::PenStyle& penStyleValue() const
                        { return m_penStyleValue; }
    const Qt::BrushStyle& brushStyleValue() const
                          { return m_brushStyleValue; }
    const Qt::AlignmentFlag& alignmentValue() const
                             { return m_alignmentValue; }

  private:
    TypeId m_typeId;
    double m_numericalValue;
    QString m_stringValue;
    QPoint m_pointValue;
    QColor m_colorValue;
    QFont m_fontValue;
    Qt::PenStyle m_penStyleValue;
    Qt::BrushStyle m_brushStyleValue;
    Qt::AlignmentFlag m_alignmentValue;
};

#endif // VALUE_H
