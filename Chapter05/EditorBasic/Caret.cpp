#include "Caret.h"
#include <QPainter>

Caret::Caret(QWidget *parentWidgetPtr)
 :m_parentWidgetPtr(parentWidgetPtr) {
  m_timer.setParent(this);
  connect(&m_timer, SIGNAL(timeout()), this, SLOT(onTimer()));
  m_timer.start(500);
}

void Caret::show() {
  m_visible = true;
  m_parentWidgetPtr->update(m_rect);
}

void Caret::hide() {
  m_visible = false;
  m_parentWidgetPtr->update(m_rect);
}

void Caret::set(QRect rect) {
  m_rect = rect;
  m_rect.setWidth(1);
  m_parentWidgetPtr->update(m_rect);
}

void Caret::onTimer(void) {
  m_blink = !m_blink;
  m_parentWidgetPtr->update(m_rect);
}

void Caret::paint(QPainter& painter) {
  if (m_visible && m_blink) {
    painter.save();
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::black);
    painter.drawRect(m_rect);
    painter.restore();
  }
}
