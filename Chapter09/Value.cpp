#include <CAssert>
using namespace std;

#include "Value.h"

Value::Value() {
  // Empty.
}

Value::Value(double numericalValue)
 :m_typeId(NumericalTypeId),
  m_numericalValue(numericalValue) {
  // Empty.
}

Value::Value(const QString& stringValue)
 :m_typeId(StringTypeId),
  m_stringValue(stringValue) {
 // Empty.
}

Value::Value(const QPoint& pointValue)
 :m_typeId(PointTypeId),
  m_pointValue(pointValue) {
  // Empty.
}

Value::Value(const QColor& colorValue)
 :m_typeId(ColorTypeId),
  m_colorValue(colorValue) {
  // Empty.
}

Value::Value(const QFont& fontValue)
 :m_typeId(FontTypeId),
  m_fontValue(fontValue) {
 // Empty.
}

Value::Value(const Qt::PenStyle& penStyleValue)
 :m_typeId(PenStyleTypeId),
  m_penStyleValue(penStyleValue) {
 // Empty.
}

Value::Value(const Qt::BrushStyle& brushStyleValue)
 :m_typeId(BrushStyleId),
  m_brushStyleValue(brushStyleValue) {
 // Empty.
}

Value::Value(const Qt::AlignmentFlag& alignmentValue)
 :m_typeId(AlignmentTypeId),
  m_alignmentValue(alignmentValue) {
 // Empty.
}

Value::Value(const Value& value)
 :m_typeId(value.m_typeId),
  m_numericalValue(value.m_numericalValue),
  m_stringValue(value.m_stringValue),
  m_pointValue(value.m_pointValue),
  m_colorValue(value.m_colorValue),
  m_fontValue(value.m_fontValue),
  m_penStyleValue(value.m_penStyleValue),
  m_brushStyleValue(value.m_brushStyleValue),
  m_alignmentValue(value.m_alignmentValue) {
  // Empty.
}

Value& Value::operator=(const Value& value) {
  m_typeId = value.m_typeId;
  m_numericalValue = value.m_numericalValue;
  m_stringValue = value.m_stringValue;
  m_pointValue = value.m_pointValue;
  m_colorValue = value.m_colorValue;
  m_fontValue = value.m_fontValue;
  m_penStyleValue = value.m_penStyleValue;
  m_brushStyleValue = value.m_brushStyleValue;
  m_alignmentValue = value.m_alignmentValue;
  return *this;
}
