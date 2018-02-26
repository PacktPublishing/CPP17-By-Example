#ifndef NACWINDOW_H
#define NACWINDOW_H

#include "..\\MainWindow\\MainWindow.h"
#include "NaCWidget.h"

class NaCWindow : public MainWindow {
  Q_OBJECT

  public:
    NaCWindow(QWidget *parentWidget = nullptr);
    ~NaCWindow();

  public:
    void closeEvent(QCloseEvent *eventPtr) override
                   {m_nacWidgetPtr->closeEvent(eventPtr);}

  private:
    NaCWidget* m_nacWidgetPtr;
};

#endif // NACWINDOW_H
