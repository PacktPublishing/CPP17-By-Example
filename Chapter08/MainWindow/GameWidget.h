#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>

#include "..\\MainWindow\\MainWindow.h"

class GameWidget : public QWidget {
  Q_OBJECT

  public:
    GameWidget(int rows, int columns, QWidget* parentWidget);
    void clearGrid();

    void resizeEvent(QResizeEvent *eventPtr) /*override*/;
    void mousePressEvent(QMouseEvent *eventPtr) /*override*/;
    void paintEvent(QPaintEvent *eventPtr) /*override*/;
    void closeEvent(QCloseEvent *eventPtr) /*override*/;

    virtual void mouseMark(int row, int column) = 0;
    virtual void drawMark(QPainter& painter,
                          const QRect& markRect, int mark) = 0;

  private:
    bool isQuitOk();

  public slots:
    DEFINE_LISTENER(GameWidget, isQuitEnabled);
    void onQuit();
    void onExit();

  protected:
    bool isGameInProgress() const {return m_gameInProgress;}
    void setGameInProgress(bool active)
                          {m_gameInProgress = active;}

  protected:
    int get(int row, int column) const;
    void set(int row, int column, int value);

  private:
    bool m_gameInProgress = false;
    int m_rows, m_columns;
    int m_rowHeight, m_columnWidth;
    int* m_gameGrid;
};

#endif // GAMEWIDGET_H
