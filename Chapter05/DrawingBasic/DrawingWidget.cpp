#include <CAssert>
#include "..\\MainWindow\\DocumentWidget.h"
#include "DrawingWidget.h"
#include "Line.h"
#include "Rectangle.h"
#include "Ellipse.h"

DrawingWidget::DrawingWidget(QWidget* parentWidgetPtr)
 :DocumentWidget(tr("Drawing"), tr("Drawing files (*.drw)"),
                 parentWidgetPtr) {
  // Empty.
}

DrawingWidget::~DrawingWidget() {
  for (Figure* figurePtr : m_figurePtrList) {
    delete figurePtr;
  }
}

void DrawingWidget::setApplicationMode(ApplicationMode mode) {
  m_applicationMode = mode;
  ((MainWindow*) parent())->onMenuShow();
}

void DrawingWidget::newDocument(void) {
  for (Figure* figurePtr : m_figurePtrList) {
    delete figurePtr;
  }

  m_figurePtrList.clear();
  m_currColor = Qt::black;
  m_currFilled = false;
  m_addFigureId = LineId;
}

bool DrawingWidget::writeFile(const QString& filePath) {
  ofstream outStream(filePath.toStdString());

  if (outStream) {
    writeColor(outStream, m_currColor);
    outStream.write((char*) &m_currFilled, sizeof m_currFilled);

    int size = m_figurePtrList.size();
    outStream.write((char*) &size, sizeof size);

    for (Figure* figurePtr : m_figurePtrList) {
      FigureId figureId = figurePtr->getId();
      outStream.write((char*) &figureId, sizeof figureId);
      figurePtr->write(outStream);
    }

    return ((bool) outStream);
  }

  return false;
}

bool DrawingWidget::readFile(const QString& filePath) {
  ifstream inStream(filePath.toStdString());

  if (inStream) {
    readColor(inStream, m_currColor);
    inStream.read((char*) &m_currFilled, sizeof m_currFilled);

    int size;
    inStream.read((char*) &size, sizeof size);

    for (int count = 0; count < size; ++count) {
      FigureId figureId = (FigureId) 0;
      inStream.read((char*) &figureId, sizeof figureId);
      Figure* figurePtr = createFigure(figureId);
      figurePtr->read(inStream);
      m_figurePtrList.push_back(figurePtr);
    }

    return ((bool) inStream);
  }

  return false;
}

Figure* DrawingWidget::createFigure(FigureId figureId) {
  Figure* figurePtr = nullptr;

  switch (figureId) {
    case LineId:
      figurePtr = new Line();
      break;

    case RectangleId:
      figurePtr = new RectangleX();
      break;

    case EllipseId:
      figurePtr = new EllipseX();
      break;
  }

  assert(figurePtr != nullptr);
  return figurePtr;
}

void DrawingWidget::onColor(void) {
  QColor newColor = QColorDialog::getColor(m_currColor, this);

  if (newColor.isValid() && (m_currColor != newColor)) {
    m_currColor = newColor;
    setModifiedFlag(true);
  }
}

bool DrawingWidget::isFillEnabled(void) {
  return (m_addFigureId == RectangleId) ||
         (m_addFigureId == EllipseId);
}

void DrawingWidget::onFill(void) {
  m_currFilled = !m_currFilled;
  setModifiedFlag(true);
}

bool DrawingWidget::isLineChecked(void) {
  return (m_addFigureId == LineId);
}

void DrawingWidget::onLine(void) {
  m_addFigureId = LineId;
}

bool DrawingWidget::isRectangleChecked(void) {
  return (m_addFigureId == RectangleId);
}

void DrawingWidget::onRectangle(void) {
  m_addFigureId = RectangleId;
}

bool DrawingWidget::isEllipseChecked(void) {
  return (m_addFigureId == EllipseId);
}

void DrawingWidget::onEllipse(void) {
  m_addFigureId = EllipseId;
}

void DrawingWidget::mousePressEvent(QMouseEvent* eventPtr) {
  if (eventPtr->button() == Qt::LeftButton) {
    m_mousePoint = eventPtr->pos();

    for (QList<Figure*>::reverse_iterator iterator =
         m_figurePtrList.rbegin();
         iterator != m_figurePtrList.rend(); ++iterator) {
      Figure* figurePtr = *iterator;

      if (figurePtr->isClick(m_mousePoint)) {
        setApplicationMode(Move);
        m_figurePtrList.removeOne(figurePtr);
        m_figurePtrList.push_back(figurePtr);
        break;
      }
    }

    if (m_applicationMode == Idle) {
      setApplicationMode(Create);
      Figure* newFigurePtr = createFigure(m_addFigureId);
      newFigurePtr->color() = m_currColor;
      newFigurePtr->filled() = m_currFilled;
      newFigurePtr->initializePoints(m_mousePoint);
      m_figurePtrList.push_back(newFigurePtr);
      setModifiedFlag(true);
    }
  }
}

void DrawingWidget::mouseMoveEvent(QMouseEvent* eventPtr) {
  if (eventPtr->buttons() == Qt::LeftButton) {
    QPoint newMousePoint = eventPtr->pos();

    switch (m_applicationMode) {
      case Create:
        m_figurePtrList.back()->setLastPoint(m_mousePoint);
        break;

      case Move: {
        QSize distance(newMousePoint.x() - m_mousePoint.x(),
                       newMousePoint.y() - m_mousePoint.y());
          m_figurePtrList.back()->move(distance);
          setModifiedFlag(true);
        }
        break;
    }

    m_mousePoint = newMousePoint;
    update();
  }
}

void DrawingWidget::mouseReleaseEvent(QMouseEvent* eventPtr) {
  if (eventPtr->buttons() == Qt::LeftButton) {
    setApplicationMode(Idle);
  }
}

void DrawingWidget::paintEvent(QPaintEvent* /* eventPtr */) {
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);
  painter.setRenderHint(QPainter::TextAntialiasing);

  for (Figure* figurePtr : m_figurePtrList) {
    figurePtr->draw(painter);
  }
}
