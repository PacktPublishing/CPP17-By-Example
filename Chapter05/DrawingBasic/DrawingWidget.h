#ifndef DRAWINGWIDGET_H
#define DRAWINGWIDGET_H

#include "..\\MainWindow\\MainWindow.h"
#include "..\\MainWindow\\DocumentWidget.h"
#include "Figure.h"

class DrawingWidget : public DocumentWidget {
  Q_OBJECT

  public:
    DrawingWidget(QWidget* parentWidgetPtr);
    ~DrawingWidget();

  public:
    void mousePressEvent(QMouseEvent *eventPtr) override;
    void mouseMoveEvent(QMouseEvent *eventPtr) override;
    void mouseReleaseEvent(QMouseEvent *eventPtr) override;
    void paintEvent(QPaintEvent *eventPtr) override;

  private:
    void newDocument() override;
    bool writeFile(const QString& filePath) override;
    bool readFile(const QString& filePath) override;
    Figure* createFigure(FigureId figureId);

  public slots:
    void onColor(void);

    DEFINE_LISTENER(DrawingWidget, isFillEnabled);
    void onFill(void);

    DEFINE_LISTENER(DrawingWidget, isLineChecked);
    DEFINE_LISTENER(DrawingWidget, isRectangleChecked);
    DEFINE_LISTENER(DrawingWidget, isEllipseChecked);

    void onLine();
    void onRectangle();
    void onEllipse();

  private:    
    enum ApplicationMode {Idle, Create, Move};
    ApplicationMode m_applicationMode = Idle;
    void setApplicationMode(ApplicationMode mode);

    QColor m_currColor = Qt::black;
    bool m_currFilled = false;
    FigureId m_addFigureId = LineId;

    QPoint m_mousePoint;
    QList<Figure*> m_figurePtrList;
};

#endif // DRAWINGWIDGET_H
