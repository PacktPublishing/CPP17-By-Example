#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QtWidgets>
#include "Value.h"
#include "Colors.h"
#include "Action.h"

class ViewerWidget : public QWidget {
  Q_OBJECT

  public:
    ViewerWidget(const QList<Action>& actionList,
                 QWidget *parentTableWidget = nullptr);

    void paintEvent(QPaintEvent *eventPtr) /*override*/;

  private:
    Qt::Alignment m_horizontalAlignment = Qt::AlignHCenter,
                  m_verticalAlignment = Qt::AlignVCenter;
    const QList<Action>& m_actionList;
};

#endif // MAINWIDGET_H
