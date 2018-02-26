#ifndef DRAWINGWINDOW_H
#define DRAWINGWINDOW_H

#include <QMainWindow>
#include <QActionGroup>

#include "..\\MainWindow\\MainWindow.h"
#include "DrawingWidget.h"

class DrawingWindow : public MainWindow {
  Q_OBJECT

  public:
    DrawingWindow(QWidget *parentWidgetPtr = nullptr);
    ~DrawingWindow();

  public:
    void closeEvent(QCloseEvent *eventPtr) override
         { m_drawingWidgetPtr->closeEvent(eventPtr); }

  private:
    DrawingWidget* m_drawingWidgetPtr;
    QActionGroup* m_figureGroupPtr;
};

#endif // DRAWINGWINDOW_H
