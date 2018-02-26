#include <CAssert>
#include "..\\MainWindow\\DocumentWidget.h"
#include "DrawingWidget.h"
#include "Line.h"
#include "Rectangle.h"
#include "Ellipse.h"

DrawingWidget::DrawingWidget(QWidget* parentWidget)
 :DocumentWidget(tr("Drawing Advanced"),
                 tr("Drawing files (*.drw)"),
                 parentWidget) {
  // Empty.
}

DrawingWidget::~DrawingWidget() {
  // Empty.
}

void DrawingWidget::setApplicationMode(ApplicationMode mode) {
  m_applicationMode = mode;
  ((MainWindow*) parent())->onMenuShow();
}

void DrawingWidget::newDocument(void) {
  for (Figure* figurePtr : m_figurePtrList) {
    delete figurePtr;
  }

  for (Figure* copyPtr : m_copyPtrList) {
    delete copyPtr;
  }

  m_figurePtrList.clear();
  m_copyPtrList.clear();
  m_nextColor = Qt::black;
  m_nextFilled = false;
  m_actionMode = Add;
  m_addFigureId = LineId;
}

bool DrawingWidget::writeFile(const QString& filePath) {
  ofstream outStream(filePath.toStdString());

  if (outStream) {
    writeColor(outStream, m_nextColor);
    outStream.write((char*) &m_nextFilled, sizeof m_nextFilled);

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
    readColor(inStream, m_nextColor);
    inStream.read((char*) &m_nextFilled, sizeof m_nextFilled);

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

bool DrawingWidget::isCopyEnabled() {
  for (Figure* figurePtr : m_figurePtrList) {
    if (figurePtr->marked()) {
      return true;
    }
  }

  return false;
}

void DrawingWidget::onCopy(void) {
  for (Figure* copyPtr : m_copyPtrList) {
    delete copyPtr;
  }

  m_copyPtrList.clear();

  for (Figure* figurePtr : m_figurePtrList) {
    if (figurePtr->marked()) {
      m_copyPtrList.push_back(figurePtr->clone());
    }
  }
}

bool DrawingWidget::isPasteEnabled() {
  return !m_copyPtrList.isEmpty();
}

void DrawingWidget::onPaste(void) {
  for (Figure* copyPtr : m_copyPtrList) {
    Figure* pastePtr = copyPtr->clone();
    pastePtr->move(QSize(10, 10));
    m_figurePtrList.push_back(pastePtr);
  }

  update();
}

void DrawingWidget::onDelete(void) {
  for (Figure* figurePtr : m_figurePtrList) {
    if (figurePtr->marked()) {
      m_figurePtrList.removeOne(figurePtr);
      delete figurePtr;
    }
  }

  update();
}

void DrawingWidget::onColor(void) {
  QColor newColor = QColorDialog::getColor(m_nextColor, this);

  if (newColor.isValid() && (m_nextColor != newColor)) {
    m_nextColor = newColor;
    setModifiedFlag(true);

    for (Figure* figurePtr : m_figurePtrList) {
      if (figurePtr->marked()) {
        figurePtr->color() = m_nextColor;
        update();
      }
    }
  }
}

bool DrawingWidget::isFillEnabled(void) {
  switch (m_actionMode) {
    case Modify:
      for (Figure* figurePtr : m_figurePtrList) {
        if (figurePtr->marked() &&
            ((figurePtr->getId() == RectangleId) ||
             (figurePtr->getId() == EllipseId))) {
          return true;
        }
      }

      return false;

    case Add:
      return (m_addFigureId == RectangleId) ||
             (m_addFigureId == EllipseId);
  }

  assert(false);
  return true;
}

void DrawingWidget::onFill(void) {
  switch (m_actionMode) {
    case Modify:
      for (Figure* figurePtr : m_figurePtrList) {
        if (figurePtr->marked()) {
          figurePtr->filled() = !figurePtr->filled();
          update();
        }
      }

      m_nextFilled = !m_nextFilled;
      break;

    case Add:
      m_nextFilled = !m_nextFilled;
      break;
  }
}

bool DrawingWidget::isModifyChecked(void) {
  return (m_actionMode == Modify);
}

void DrawingWidget::onModify(void) {
  m_actionMode = Modify;
}

bool DrawingWidget::isLineChecked(void) {
  return (m_actionMode == Add) && (m_addFigureId == LineId);
}

void DrawingWidget::onLine(void) {
  m_actionMode = Add;
  m_addFigureId = LineId;
}

bool DrawingWidget::isRectangleChecked(void) {
  return (m_actionMode == Add) && (m_addFigureId == RectangleId);
}

void DrawingWidget::onRectangle(void) {
  m_actionMode = Add;
  m_addFigureId = RectangleId;
}

bool DrawingWidget::isEllipseChecked(void) {
  return (m_actionMode == Add) && (m_addFigureId == EllipseId);
}

void DrawingWidget::onEllipse(void) {
  m_actionMode = Add;
  m_addFigureId = EllipseId;
}

void DrawingWidget::mousePressEvent(QMouseEvent* eventPtr) {
  if (eventPtr->buttons() == Qt::LeftButton) {
    m_mousePoint = eventPtr->pos();

    switch (m_actionMode) {
      case Modify: {
          for (Figure* figurePtr : m_figurePtrList) {
           figurePtr->marked() = false;
          }

          m_clickedFigurePtr = nullptr;
          for (QList<Figure*>::reverse_iterator iterator =
               m_figurePtrList.rbegin();
               iterator != m_figurePtrList.rend(); ++iterator) {
            Figure* figurePtr = *iterator;

            if (figurePtr->isClick(m_mousePoint)) {
              setApplicationMode(ModifySingle);
              m_clickedFigurePtr = figurePtr;
              figurePtr->marked() = true;
              m_figurePtrList.removeOne(figurePtr);
              m_figurePtrList.push_back(figurePtr);
              break;
            }
          }

          if (m_clickedFigurePtr == nullptr) {
            setApplicationMode(ModifyRectangle);
            m_insideRectangle = QRect(m_mousePoint, m_mousePoint);
          }
        }
        break;

      case Add: {
          Figure* newFigurePtr = createFigure(m_addFigureId);
          newFigurePtr->color() = m_nextColor;
          newFigurePtr->filled() = m_nextFilled;
          newFigurePtr->initializePoints(m_mousePoint);
          m_figurePtrList.push_back(newFigurePtr);
          setApplicationMode(ModifySingle);
          setModifiedFlag(true);
        }
        break;
    }

    update();
  }
}

void DrawingWidget::mouseMoveEvent(QMouseEvent* eventPtr) {
  if (eventPtr->buttons() == Qt::LeftButton) {
    QPoint newMousePoint = eventPtr->pos();
    QSize distance(newMousePoint.x() - m_mousePoint.x(),
                       newMousePoint.y() - m_mousePoint.y());
    m_mousePoint = newMousePoint;

    switch (m_applicationMode) {
      case ModifySingle:
        m_figurePtrList.back()->modify(distance);
        setModifiedFlag(true);
        break;

/*      case MoveMultiple:
        for (Figure* figurePtr : m_figurePtrList) {
          if (figurePtr->marked()) {
            figurePtr->move(distance);
          }
        }

        setModifiedFlag(true);
        break;*/

      case ModifyRectangle:
        m_insideRectangle.setBottomRight(m_mousePoint);
        break;
    }

    update();
  }
}

void DrawingWidget::mouseReleaseEvent(QMouseEvent* eventPtr) {
  if (eventPtr->button() == Qt::LeftButton) {
    switch (m_applicationMode) {
      case ModifyRectangle: {
          QList<Figure*> insidePtrList;

          for (Figure* figurePtr : m_figurePtrList) {
            if (figurePtr->isInside(m_insideRectangle)) {
              figurePtr->marked() = true;
              m_figurePtrList.removeOne(figurePtr);
              insidePtrList.push_back(figurePtr);
            }
          }

          for (Figure* figurePtr : insidePtrList) {
            m_figurePtrList.removeOne(figurePtr);
          }

          m_figurePtrList.append(insidePtrList);
        }
        break;
    }

    setApplicationMode(Idle);
    update();
  }
}

void DrawingWidget::mouseDoubleClickEvent(QMouseEvent *eventPtr) {
  if ((eventPtr->buttons() == Qt::LeftButton) &&
      (m_clickedFigurePtr != nullptr)) {
    m_clickedFigurePtr->doubleClick(eventPtr->pos());
    update();
  }
}

void DrawingWidget::paintEvent(QPaintEvent* /* eventPtr */) {
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);
  painter.setRenderHint(QPainter::TextAntialiasing);

  for (Figure* figurePtr : m_figurePtrList) {
    figurePtr->draw(painter);
  }

  if (m_applicationMode == ModifyRectangle) {
    painter.setPen(Qt::lightGray);
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(m_insideRectangle);
  }
}
