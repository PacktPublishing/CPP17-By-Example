#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

#include <QMainWindow>
#include <QActionGroup>
#include <QPair>
#include <QMap>

#include "..\\MainWindow\\MainWindow.h"
#include "EditorWidget.h"

class EditorWindow : public MainWindow {
  Q_OBJECT

  public:
    EditorWindow(QWidget *parentWidgetPtr = nullptr);
    ~EditorWindow();

  protected:
    void keyPressEvent(QKeyEvent* eventPtr) override;
    void closeEvent(QCloseEvent* eventPtr) override;

  private:
    EditorWidget* m_editorWidgetPtr;
};

#endif // EDITORWINDOW_H
