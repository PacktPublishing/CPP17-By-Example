#ifndef CARET_H
#define CARET_H

#include <QObject>
#include <QWidget>
#include <QTimer>

class Caret : public QObject {
  Q_OBJECT

  public:
    Caret(QWidget *parentWidgetPtr = nullptr);

    void show();
    void hide();
    void set(QRect rect);
    void paint(QPainter* painterPtr);

  public slots:
    void onTimer(void);

  private:
    QWidget* m_parentWidgetPtr;
    bool m_visible, m_black;
    QRect m_rect;
    QTimer m_timer;
};

#endif // CARET_H
