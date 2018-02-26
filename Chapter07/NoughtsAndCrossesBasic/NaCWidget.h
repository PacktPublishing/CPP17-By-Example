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
                  const QRect& markRect, int mark);

  public slots:
    DEFINE_LISTENER(NaCWidget, isNoughtStartsEnabled);
    void onNoughtStarts();

    DEFINE_LISTENER(NaCWidget, isCrossStartsEnabled);
    void onCrossStarts();

  private:
    void checkWinner(int row, int column, Mark mark);
    int countMarks(int row, int column, int rowStep,
                   int columnStep, Mark mark);

    Mark m_nextMark;
};

#endif // NACWIDGET_H
