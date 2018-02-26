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
  m_black = !m_black;
  m_parentWidgetPtr->update(m_rect);
}

void Caret::paint(QPainter* painterPtr) {
  if (m_visible && m_black) {
    painterPtr->save();
    painterPtr->setPen(Qt::NoPen);
    painterPtr->setBrush(Qt::black);
    painterPtr->drawRect(m_rect);
    painterPtr->restore();
  }
}
