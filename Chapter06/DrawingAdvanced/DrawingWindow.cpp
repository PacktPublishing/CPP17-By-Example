#include "..\\MainWindow\\DocumentWidget.h"
#include "DrawingWindow.h"

DrawingWindow::DrawingWindow(QWidget *parentWidget /*= nullptr*/)
 :MainWindow(parentWidget) {
  resize(1000, 500);

  m_drawingWidgetPtr = new DrawingWidget(this);
  setCentralWidget(m_drawingWidgetPtr);
  addFileMenu();
  addEditMenu();

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

    m_figureGroupPtr = new QActionGroup(this);
    addAction(formatMenuPtr, tr("&Modify"),
              SLOT(onModify()),
              QKeySequence(Qt::CTRL + Qt::Key_M),
              QString(), nullptr, tr("Modify Figure"), nullptr,
              LISTENER(isModifyChecked), m_figureGroupPtr);

    { QMenu* alignmentMenuPtr =
               formatMenuPtr->addMenu(tr("&Figure"));
      connect(alignmentMenuPtr, SIGNAL(aboutToShow()),
              this, SLOT(onMenuShow()));

      addAction(alignmentMenuPtr, tr("&Line"),
                SLOT(onLine()),
                QKeySequence(Qt::CTRL + Qt::Key_L),
                QString(), nullptr, tr("Line Figure"), nullptr,
                LISTENER(isLineChecked), m_figureGroupPtr);

      addAction(alignmentMenuPtr, tr("&Rectangle"),
                SLOT(onRectangle()),
                QKeySequence(Qt::CTRL + Qt::Key_R),
                QString(), nullptr, tr("Rectangle Figure"),
                nullptr, LISTENER(isRectangleChecked),
                m_figureGroupPtr);

      addAction(alignmentMenuPtr, tr("&Ellipse"),
                SLOT(onEllipse()),
                QKeySequence(Qt::CTRL + Qt::Key_E),
                QString(), nullptr, tr("Ellipse Figure"), nullptr,
                LISTENER(isEllipseChecked), m_figureGroupPtr);
    }
  }
}

DrawingWindow::~DrawingWindow() {
  delete m_figureGroupPtr;
}
