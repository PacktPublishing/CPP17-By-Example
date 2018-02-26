#ifndef DRAWINGWIDGET_H
#define DRAWINGWIDGET_H

#include "..\\MainWindow\\MainWindow.h"
#include "..\\MainWindow\\DocumentWidget.h"
#include "Figure.h"

class DrawingWidget : public DocumentWidget {
  Q_OBJECT

  public:
    DrawingWidget(QWidget* parentWidget);
    ~DrawingWidget();

  public:
    void mousePressEvent(QMouseEvent *eventPtr) override;
    void mouseMoveEvent(QMouseEvent *eventPtr) override;
    void mouseReleaseEvent(QMouseEvent *eventPtr) override;
    void mouseDoubleClickEvent(QMouseEvent *eventPtr) override;
    void paintEvent(QPaintEvent *eventPtr) override;

  private:
    void newDocument(void);
    bool writeFile(const QString& filePath);
    bool readFile(const QString& filePath);
    Figure* createFigure(FigureId figureId);

  public slots:
    bool isCopyEnabled();
    void onCopy(void);
    bool isPasteEnabled();
    void onPaste(void);
    void onDelete(void);
    void onColor(void);

    DEFINE_LISTENER(DrawingWidget, isFillEnabled);
    void onFill(void);

    DEFINE_LISTENER(DrawingWidget, isModifyChecked);
    void onModify(void);

    DEFINE_LISTENER(DrawingWidget, isLineChecked);
    void onLine(void);

    DEFINE_LISTENER(DrawingWidget, isRectangleChecked);
    void onRectangle(void);

    DEFINE_LISTENER(DrawingWidget, isEllipseChecked);
    void onEllipse(void);

  private:
    enum ApplicationMode {Idle, ModifySingle,
                          /*MoveMultiple, */ModifyRectangle};
    ApplicationMode m_applicationMode = Idle;
    void setApplicationMode(ApplicationMode mode);

    enum ActionMode {Modify, Add};
    ActionMode m_actionMode = Add;

    QColor m_nextColor = Qt::black;
    bool m_nextFilled = false;

    Figure* m_clickedFigurePtr;
    FigureId m_addFigureId = LineId;

    QPoint m_mousePoint;
    QList<Figure*> m_figurePtrList, m_copyPtrList;
    QRect m_insideRectangle;
};

#endif // DRAWINGWIDGET_H
