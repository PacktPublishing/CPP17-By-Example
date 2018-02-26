#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QActionGroup>
#include <QPair>
#include <QMap>

#include "Listener.h"
#include "DocumentWidget.h"

class MainWindow : public QMainWindow {
  Q_OBJECT

  public:
    MainWindow(QWidget *parentWidgetPtr = nullptr);
    ~MainWindow();

  protected:
    void addFileMenu();
    void addEditMenu();

  protected:
/*    void addAction(QMenu* menuPtr, QString text,
            const char* onSelectPtr, QString iconName = QString(),
                   QToolBar* toolBarPtr = nullptr,
                   QString statusTip = QString(),
                   Listener enableListener = nullptr,
                   Listener checkListener = nullptr,
                   QActionGroup* groupPtr = nullptr);
*/
    void addAction(QMenu* menuPtr, QString text,
                   const char* onSelectPtr,
                   QKeySequence acceleratortKey = 0,
                   QString iconName = QString(),
                   QToolBar* toolBarPtr = nullptr,
                   QString statusTip = QString(),
                   Listener enableListener = nullptr,
                   Listener checkListener = nullptr,
                   QActionGroup* groupPtr = nullptr);

    DEFINE_LISTENER(DocumentWidget, isSaveEnabled);
    DEFINE_LISTENER(DocumentWidget, isCutEnabled);
    DEFINE_LISTENER(DocumentWidget, isCopyEnabled);
    DEFINE_LISTENER(DocumentWidget, isPasteEnabled);
    DEFINE_LISTENER(DocumentWidget, isDeleteEnabled);

  public slots:
    void onMenuShow();

  private:
    QMap<QAction*,QPair<QObject*,Listener>> m_enableMap,
                                            m_checkMap;
};

#endif // MAINWINDOW_H
