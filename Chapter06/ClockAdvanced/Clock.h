#ifndef CLOCK_H
#define CLOCK_H

#include <QWidget>
#include <QTimer>

class Clock : public QWidget {
  Q_OBJECT

  public:
    Clock(QWidget *parentWidget = nullptr);
    void paintEvent(QPaintEvent *eventPtr) override;

  private:
    QTimer m_timer;
};

#endif // CLOCK_H
