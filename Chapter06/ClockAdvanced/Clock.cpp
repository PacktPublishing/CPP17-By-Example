#include <QtWidgets>
#include "Clock.h"

Clock::Clock(QWidget *parentWidget /*= nullptr*/)
 :QWidget(parentWidget) {
  setWindowTitle(tr("Clock Advanced"));
  resize(1000, 500);

  m_timer.setParent(this);
  connect(&m_timer, SIGNAL(timeout()), this, SLOT(update()));
  m_timer.start(100);
}

void Clock::paintEvent(QPaintEvent* /*event*/) {
  int side = qMin(width(), height());
  QTime time = QTime::currentTime();

  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);
  painter.setRenderHint(QPainter::TextAntialiasing);
  painter.translate(width() / 2, height() / 2);
  painter.scale(side / 200.0, side / 200.0);

  painter.setFont(QFont(tr("Times New Roman"), 12));

  for (int hour = 1; hour <= 12; ++hour) {
    QString text;
    text.setNum(hour);
    double angle = (30.0 * hour) - 90;
    double length = 90.0;

    double x = length * qCos(qDegreesToRadians(angle)),
           y = length * qSin(qDegreesToRadians(angle));
    QRect rect(x - 100, y - 100, 200, 200);
    painter.drawText(rect, Qt::AlignHCenter |
                           Qt::AlignVCenter, text);
  }

  double hours = time.hour(), minutes = time.minute(),
         seconds = time.second(), milliseconds = time.msec();

  painter.setPen(Qt::black);
  painter.setBrush(Qt::gray);

  { static const QPoint hourHand[3] =
      {QPoint(8, 8), QPoint(-8, 8), QPoint(0, -60)};

    painter.save();
    double hour = hours + (minutes / 60.0) + (seconds / 3600.0) +
                  (milliseconds / 3600000.0);
    painter.rotate(30.0 * hour);
    painter.drawConvexPolygon(hourHand, 3);
    painter.restore();
  }

  { static const QPoint minuteHand[3] =
      {QPoint(6, 8), QPoint(-6, 8), QPoint(0, -70)};

    painter.save();
    double minute = minutes + (seconds / 60.0) +
                    (milliseconds / 60000.0);
    painter.rotate(6.0 * minute);
    painter.drawConvexPolygon(minuteHand, 3);
    painter.restore();
  }

  { static const QPoint secondHand[3] =
      {QPoint(4, 8), QPoint(-4, 8), QPoint(0, -80)};

    painter.save();
    double second = seconds + (milliseconds / 1000);
    painter.rotate(6.0 * second);
    painter.drawConvexPolygon(secondHand, 3);
    painter.restore();
  }
}

#if 0
void AnalogClock::paintEventX(QPaintEvent* /*event*/) {
  int side = qMin(width(), height());
  QTime time = QTime::currentTime();

  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);
  painter.setRenderHint(QPainter::TextAntialiasing);
  painter.translate(width() / 2, height() / 2);
  painter.scale(side / 200.0, side / 200.0);

  for (int second = 0; second <= 60; ++second) {
    if ((second % 5) == 0) {
      painter.drawLine(QPoint(0, 81), QPoint(0, 98));
    }
    else {
      painter.drawLine(QPoint(0, 90), QPoint(0, 98));
    }

    painter.rotate(6);
  }

  double hours = time.hour(), minutes = time.minute(),
         seconds = time.second(), milliseconds = time.msec();

  painter.setPen(Qt::black);
  painter.setBrush(Qt::gray);

  { static const QPoint hourHand[3] =
      {QPoint(8, 8), QPoint(-8, 8), QPoint(0, -60)};

    painter.save();
    double hour = hours + (minutes / 60.0) + (seconds / 3600.0) +
                  (milliseconds / 3600000.0);
    painter.rotate(30.0 * hour);
    painter.drawConvexPolygon(hourHand, 3);
    painter.restore();
  }

  { static const QPoint minuteHand[3] =
      {QPoint(6, 8), QPoint(-6, 8), QPoint(0, -70)};

    painter.save();
    double minute = minutes + (seconds / 60.0) +
                    (milliseconds / 60000.0);
    painter.rotate(6.0 * minute);
    painter.drawConvexPolygon(minuteHand, 3);
    painter.restore();
  }

  { static const QPoint secondHand[3] =
      {QPoint(4, 8), QPoint(-4, 8), QPoint(0, -80)};

    painter.save();
    double second = seconds + (milliseconds / 1000);
    painter.rotate(6.0 * second);
    painter.drawConvexPolygon(secondHand, 3);
    painter.restore();
  }
}
#endif
