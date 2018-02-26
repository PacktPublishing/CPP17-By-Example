#ifndef NACWIDGET_H
#define NACWIDGET_H

#include "..\\MainWindow\\GameWidget.h"

#define ROWS    26
#define COLUMNS 26

enum Mark {Empty = 0, Nought, Cross};

class NaCWidget : public GameWidget {
  Q_OBJECT

  public:
    NaCWidget(QWidget* parentWidget);

    void mouseMark(int row, int column) override;
    void drawMark(QPainter& painter,
                  const QRect& markRect, int mark) override;

  public slots:
    DEFINE_LISTENER(NaCWidget, isComputerStartsNoughtEnabled);
    DEFINE_LISTENER(NaCWidget, isComputerStartsCrossEnabled);
    DEFINE_LISTENER(NaCWidget, isHumanStartsNoughtEnabled);
    DEFINE_LISTENER(NaCWidget, isHumanStartsCrossEnabled);

    void onComputerStartsNought();
    void onComputerStartsCross();
    void onHumanStartsNought();
    void onHumanStartsCross();

  private:
    bool checkWinner(int row, int column, Mark mark);
    double countMarks(int row, int column, int rowStep,
                 int columnStep, Mark mark);
    void calculateComputerMove(int& row, int &column);
    double calculateMarkValue(int row, int column, Mark mark);
    Mark m_humanMark, m_computerMark;
};

#endif // NACWIDGET_H
