#ifndef OTHELLOWIDGET_H
#define OTHELLOWIDGET_H

#include "..\\MainWindow\\GameWidget.h"

#define ROWS    8
#define COLUMNS 8

enum Mark {Empty = 0, Black, White};

class OthelloWidget : public GameWidget {
  Q_OBJECT

  public:
    OthelloWidget(QWidget* parentWidget);

    void mouseMark(int row, int column);
    void drawMark(QPainter& painter,
                  const QRect& markRect, int mark);

  public slots:
    DEFINE_LISTENER(OthelloWidget, isComputerStartsBlackEnabled);
    DEFINE_LISTENER(OthelloWidget, isComputerStartsWhiteEnabled);
    DEFINE_LISTENER(OthelloWidget, isHumanStartsBlackEnabled);
    DEFINE_LISTENER(OthelloWidget, isHumanStartsWhiteEnabled);

    void onComputerStartsBlack();
    void onComputerStartsWhite();
    void onHumanStartsBlack();
    void onHumanStartsWhite();

  private:
    bool checkWinner();
    void turn(int row, int column, Mark mark);
    void calculateComputerMove();
    void calculateTurns(int row, int column, Mark mark,
                        QSet<QPair<int,int>>& totalSet,
                        int& neighbours);
    Mark m_humanMark, m_computerMark;
};

#endif // OTHELLOWIDGET_H
