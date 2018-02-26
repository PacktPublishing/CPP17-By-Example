#ifndef OTHELLOWINDOW_H
#define OTHELLOWINDOW_H

#include "..\\MainWindow\\MainWindow.h"
#include "OthelloWidget.h"

class OthelloWindow : public MainWindow {
  Q_OBJECT

  public:
    OthelloWindow(QWidget *parentWidget = nullptr);
    ~OthelloWindow();

    void closeEvent(QCloseEvent *eventPtr) override
                   {m_othelloWidgetPtr->closeEvent(eventPtr);}

  private:
    OthelloWidget* m_othelloWidgetPtr;
};

#endif // OTHELLOWINDOW_H
