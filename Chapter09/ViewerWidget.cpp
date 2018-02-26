#include <QtWidgets>
#include "ViewerWidget.h"

ViewerWidget::ViewerWidget(const QList<Action>& actionList,
                           QWidget *parentTableWidget)
 :QWidget(parentTableWidget),
  m_actionList(actionList) {
  setWindowTitle(tr("Domain Specific Language"));
  resize(500, 300);
}

void ViewerWidget::paintEvent(QPaintEvent* /*event*/) {
  QPainter painter(this);

  for (const Action& action : m_actionList) {
    switch (action.id()) {
    case SetPenColorId: {
        QColor penColor = action.value1().colorValue();
        QPen pen(penColor);
        pen.setStyle(painter.pen().style());
        painter.setPen(pen);
      }
      break;

    case SetPenStyleId: {
        Qt::PenStyle penStyle = action.value1().penStyleValue();
        QPen pen(penStyle);
        pen.setColor(painter.pen().color());
        painter.setPen(pen);
      }
      break;

    case SetBrushColorId: {
        QColor brushColor = action.value1().colorValue();
        QBrush brush(brushColor);
        brush.setStyle(painter.brush().style());
        painter.setBrush(brush);
      }
      break;

    case SetBrushStyleId: {
        Qt::BrushStyle brushStyle =
          action.value1().brushStyleValue();
        QBrush brush(brushStyle);
        brush.setColor(painter.brush().color());
        painter.setBrush(brush);
      }
      break;

    case SetFontId: {
          QFont font = action.value1().fontValue();
          painter.setFont(font);
        }
        break;

      case SetHorizontalAlignmentId:
        m_horizontalAlignment = action.value1().alignmentValue();
        break;

      case SetVerticalAlignmentId:
        m_verticalAlignment = action.value1().alignmentValue();
        break;

      case DrawLineId:
        painter.drawLine(action.value1().pointValue(),
                         action.value2().pointValue());
        break;

      case DrawRectangleId: {
          QRect rect(action.value1().pointValue(),
                     action.value2().pointValue());
          painter.drawRect(rect);
        }
        break;

      case DrawEllipseId: {
          QRect rect(action.value1().pointValue(),
                     action.value2().pointValue());
          painter.drawEllipse(rect);
        }
        break;

      case DrawTextId:  {
          QPoint point = action.value1().pointValue();
          const QString& text = action.value2().stringValue();
          QFontMetrics metrics(painter.font());
          QSize size = metrics.size(0, text);

          switch (m_horizontalAlignment) {
            case Qt::AlignHCenter:
              point.rx() -= size.width() / 2;
              break;

            case Qt::AlignRight:
              point.rx() -= size.width();
              break;
          }

          switch (m_verticalAlignment) {
            case Qt::AlignVCenter:
              point.ry() += size.height() / 2;
              break;

            case Qt::AlignBottom:
              point.ry() += size.height();
              break;
          }

          painter.drawText(point, text);
        }
        break;
    }
  }
}
