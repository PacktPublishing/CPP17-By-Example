#ifndef EDITORWIDGET_H
#define EDITORWIDGET_H

#include <QWidget>
#include <QMap>
#include <QMenu>
#include <QToolBar>
#include <QPair>
#include "Caret.h"

#include "..\\MainWindow\\DocumentWidget.h"

class EditorWidget : public DocumentWidget {
  Q_OBJECT

  public:
    EditorWidget(QWidget* parentWidgetPtr);
    void keyPressEvent(QKeyEvent* eventPtr);
    void mousePressEvent(QMouseEvent* eventPtr) override;

  private:
    int mouseToIndex(QPoint point);

  public:
    void paintEvent(QPaintEvent* eventPtr) override;
    void resizeEvent(QResizeEvent* eventPtr) override;

  private:
    void newDocument(void);
    bool writeFile(const QString& filePath);
    bool readFile(const QString& filePath);

  private:
    void setCaret();
    void simulateMouseClick(int x, int y);

  private:
    void calculate();

    int m_editIndex = 0;
    Caret m_caret;
    QList<QPair<int,int>> m_lineList;
    QString m_editorText;
    QList<QRect> m_rectList;
    static const QFont TextFont;
    int FontWidth, FontHeight;
};

#endif // EDITORWIDGET_H
