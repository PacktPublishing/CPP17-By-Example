#include "..\\MainWindow\\DocumentWidget.h"
#include "DrawingWindow.h"

DrawingWindow::DrawingWindow(QWidget
                             *parentWidgetPtr /* = nullptr */)
 :MainWindow(parentWidgetPtr) {
  resize(1000, 500);

  m_drawingWidgetPtr = new DrawingWidget(this);
  setCentralWidget(m_drawingWidgetPtr);
  addFileMenu();

  { QMenu* formatMenuPtr = menuBar()->addMenu(tr("F&ormat"));
    connect(formatMenuPtr, SIGNAL(aboutToShow()),
            this, SLOT(onMenuShow()));

    addAction(formatMenuPtr, tr("&Color"),
              SLOT(onColor()), QKeySequence(Qt::ALT + Qt::Key_C),
              QString(), nullptr, tr("Figure Color"));

    addAction(formatMenuPtr, tr("&Fill"),
              SLOT(onFill()), QKeySequence(Qt::CTRL + Qt::Key_F),
              QString(), nullptr, tr("Figure Fill"),
              LISTENER(isFillEnabled));
  }

  { m_figureGroupPtr = new QActionGroup(this);

    QMenu* figureMenuPtr = menuBar()->addMenu(tr("F&igure"));
    connect(figureMenuPtr, SIGNAL(aboutToShow()),
            this, SLOT(onMenuShow()));

    addAction(figureMenuPtr, tr("&Line"),
              SLOT(onLine()), QKeySequence(Qt::CTRL + Qt::Key_L),
              QString(), nullptr, tr("Line Figure"), nullptr,
              LISTENER(isLineChecked), m_figureGroupPtr);
    addAction(figureMenuPtr, tr("&Rectangle"),
              SLOT(onRectangle()),
              QKeySequence(Qt::CTRL + Qt::Key_R),
              QString(), nullptr, tr("Rectangle Figure"), nullptr,
              LISTENER(isRectangleChecked), m_figureGroupPtr);
    addAction(figureMenuPtr, tr("&Ellipse"),
              SLOT(onEllipse()),
              QKeySequence(Qt::CTRL + Qt::Key_E),
              QString(), nullptr, tr("Ellipse Figure"), nullptr,
              LISTENER(isEllipseChecked), m_figureGroupPtr);
  }
}

DrawingWindow::~DrawingWindow() {
  delete m_figureGroupPtr;
}
