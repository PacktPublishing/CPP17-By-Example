#include "EditorWidget.h"
#include <QtWidgets>
#include <CAssert>
using namespace std;

EditorWidget::EditorWidget(QWidget* parentWidgetPtr)
 :DocumentWidget(tr("Editor Advanced"),
                 tr("Editor files (*.edi)"), parentWidgetPtr),
  m_textFont(tr("Times New Roman"), 12),
  m_mode(Edit),
  m_editIndex(0),
  m_alignment(Left),
  m_caret(this) {
    calculate();
  setCaret();
  m_caret.show();
}

void EditorWidget::newDocument(void) {
  m_mode = Edit;
  m_editIndex = 0;
  m_textFont = QFont(tr("Times New Roman"), 12);
  m_editorText.clear();
  calculate();
  setCaret();
}

bool EditorWidget::writeFile(const QString& filePath) {
  QFile file(filePath);
  if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
    QTextStream outStream(&file);
    outStream << m_textFont.toString() << endl << m_editorText;
    return ((bool) outStream.Ok);
  }

  return false;
}

bool EditorWidget::readFile(const QString& filePath) {
  QFile file(filePath);

  if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    QTextStream inStream(&file);
    m_textFont.fromString(inStream.readLine());
    m_editorText = inStream.readAll();

    calculate();
    setCaret();
    return ((bool) inStream.Ok);
  }

  return false;
}

bool EditorWidget::isCopyEnabled() {
  return (m_mode == Mark);
}

void EditorWidget::onCopy(void) {
  int minIndex = qMin(m_firstIndex, m_lastIndex),
      maxIndex = qMax(m_firstIndex, m_lastIndex);

  m_copyText =
    m_editorText.mid(minIndex, maxIndex - minIndex + 1);
}

bool EditorWidget::isPasteEnabled() {
  return !m_copyText.isEmpty();
}

void EditorWidget::onPaste(void) {
  if (m_mode == Mark) {
    onDelete();
  }

  m_editorText.insert(m_editIndex, m_copyText);
  calculate();
  setCaret();
  setModifiedFlag(true);
  update();
}

void EditorWidget::onDelete(void) {
  QKeyEvent event(QEvent::KeyPress, Qt::Key_Delete,
                  Qt::NoModifier);
  keyPressEvent(&event);
}

bool EditorWidget::isFontEnabled() {
  return (m_mode == Edit);
}

void EditorWidget::onFont(void) {
  bool pressedOkButton;
  QFont newFont =
    QFontDialog::getFont(&pressedOkButton, m_textFont, this);

  if (pressedOkButton) {
    m_textFont = newFont;
    setModifiedFlag(true);
    calculate();
    m_caret.set(m_rectList[m_editIndex]);
    update();
  }
}

bool EditorWidget::isLeftChecked(void) {
  return (m_alignment == Left);
}

bool EditorWidget::isCenterChecked(void) {
  return (m_alignment == Center);
}

bool EditorWidget::isRightChecked(void) {
  return (m_alignment == Right);
}

void EditorWidget::onLeft(void) {
  m_alignment = Left;
  setModifiedFlag(true);
  calculate();
  setCaret();
  update();
}

void EditorWidget::onCenter(void) {
  m_alignment = Center;
  setModifiedFlag(true);
  calculate();
  setCaret();
  update();
}

void EditorWidget::onRight(void) {
  m_alignment = Right;
  setModifiedFlag(true);
  calculate();
  setCaret();
  update();
}

void EditorWidget::mousePressEvent(QMouseEvent* eventPtr) {
  if (eventPtr->buttons() == Qt::LeftButton) {
    m_firstIndex = m_lastIndex = mouseToIndex(eventPtr->pos());
    m_mode = Mark;
    m_caret.hide();
  }
}

void EditorWidget::mouseMoveEvent(QMouseEvent* eventPtr) {
  if (eventPtr->buttons() == Qt::LeftButton) {
    m_lastIndex = mouseToIndex(eventPtr->pos());
    update();
  }
}

void EditorWidget::mouseReleaseEvent(QMouseEvent* eventPtr) {
  if (eventPtr->buttons() == Qt::LeftButton) {
    if (m_firstIndex == m_lastIndex) {
      m_mode = Edit;
      m_editIndex = m_firstIndex;
      setCaret();
      m_caret.show();
      update();
    }
  }
}

void EditorWidget::keyPressEvent(QKeyEvent* eventPtr) {
  switch (m_mode) {
    case Edit:
      keyEditPressEvent(eventPtr);
      break;

    case Mark:
      keyMarkPressEvent(eventPtr);
      break;
  }
}

void EditorWidget::keyEditPressEvent(QKeyEvent* eventPtr) {
  switch (eventPtr->key()) {
    case Qt::Key_Left:
      if (m_editIndex > 0) {
        --m_editIndex;
      }
      break;

    case Qt::Key_Right:
      if (m_editIndex < m_editorText.size()) {
        ++m_editIndex;
      }
      break;

    case Qt::Key_Up: {
        QRect charRect = m_rectList[m_editIndex];

        if (charRect.top() > 0) {
          int x = charRect.left() + (charRect.width() / 2),
              y = charRect.top() - 1;
          simulateMouseClick(x, y);
        }
      }
      break;

    case Qt::Key_Down: {
        QRect charRect = m_rectList[m_editIndex];
        int x = charRect.left() + (charRect.width() / 2),
            y = charRect.bottom() + 1;
        simulateMouseClick(x, y);
      }
      break;

    case Qt::Key_Delete:
      if (m_editIndex < m_editorText.size()) {
        m_editorText.remove(m_editIndex, 1);
        setModifiedFlag(true);
      }
      break;

    case Qt::Key_Backspace:
      if (m_editIndex > 0) {
        --m_editIndex;
        onDelete();
      }
      break;

    case Qt::Key_Return:
      m_editorText.insert(m_editIndex++, '\n');
      setModifiedFlag(true);
      break;

    default: {
        QString text = eventPtr->text();

        if (!text.isEmpty()) {
          m_editorText.insert(m_editIndex++, text[0]);
          setModifiedFlag(true);
        }
      }
      break;
  }

  calculate();
  setCaret();
  update();
}

void EditorWidget::keyMarkPressEvent(QKeyEvent* eventPtr) {
  switch (eventPtr->key()) {
    case Qt::Key_Left: {
        int minIndex = qMin(m_firstIndex, m_lastIndex);

        if (minIndex > 0) {
          m_mode = Edit;
          m_caret.show();
          m_editIndex = minIndex;
        }
      }
      break;

    case Qt::Key_Right: {
        int maxIndex = qMax(m_firstIndex, m_lastIndex);

        if (maxIndex < m_editorText.size()) {
          m_mode = Edit;
          m_caret.show();
          m_editIndex = maxIndex;
        }
      }
      break;

    case Qt::Key_Up: {
        QRect charRect = m_rectList[m_editIndex];

        if (charRect.top() > 0) {
          int x = charRect.left() + (charRect.width() / 2),
              y = charRect.top() - 1;
          simulateMouseClick(x, y);
        }
      }
      break;

    case Qt::Key_Down: {
        QRect charRect = m_rectList[m_editIndex];
        int x = charRect.left() + (charRect.width() / 2),
            y = charRect.bottom() + 1;
        simulateMouseClick(x, y);
      }
      break;

    case Qt::Key_Delete:
    case Qt::Key_Backspace: {
        int minIndex = qMin(m_firstIndex, m_lastIndex),
            maxIndex = qMax(m_firstIndex, m_lastIndex);

        m_editorText.remove(minIndex, maxIndex - minIndex);
        setModifiedFlag(true);
        m_mode = Edit;
        m_caret.show();
        m_editIndex = minIndex;
      }
      break;

    case Qt::Key_Return:
      onDelete();
      m_editorText.insert(m_editIndex++, '\n');
      setModifiedFlag(true);
      break;

    default: {
        QString text = eventPtr->text();

        if (!text.isEmpty()) {
          onDelete();
          m_editorText.insert(m_editIndex++, text[0]);
          setModifiedFlag(true);
        }
      }
      break;
  }

  calculate();
  setCaret();
  update();
}

void EditorWidget::simulateMouseClick(int x, int y) {
  QMouseEvent pressEvent(QEvent::MouseButtonPress, QPointF(x, y),
                   Qt::LeftButton, Qt::NoButton, Qt::NoModifier);
  mousePressEvent(&pressEvent);
  QMouseEvent releaseEvent(QEvent::MouseButtonRelease,
                           QPointF(x, y), Qt::LeftButton,
                           Qt::NoButton, Qt::NoModifier);
  mousePressEvent(&releaseEvent);
}

void EditorWidget::setCaret() {
  if (m_mode == Edit) {
    QRect charRect = m_rectList[m_editIndex];
    QRect caretRect(charRect.left(), charRect.top(),
                    1, charRect.height());
    m_caret.set(caretRect);
  }
}

int EditorWidget::mouseToIndex(QPoint point) {
  int x = point.x(), y = point.y();

  if (y > (m_fontHeight * m_lineList.size())) {
    return m_editorText.size();
  }
  else {
    int lineIndex = y / m_fontHeight;
    QPair<int,int> lineInfo = m_lineList[lineIndex];
    int firstIndex = lineInfo.first, lastIndex = lineInfo.second;

    if (x < m_rectList[firstIndex].left()) {
      return firstIndex;
    }
    else if (x >= m_rectList[lastIndex].right()) {
      return (lastIndex + 1);
    }
    else {
      for (int charIndex = firstIndex + 1;
           charIndex <= lastIndex; ++charIndex){
        int left = m_rectList[charIndex].left();

        if (x < left) {
          int last = m_rectList[charIndex - 1].left();
          int leftSize = x - last, rightSize = left - x;
          return (leftSize < rightSize) ? (charIndex - 1)
                                        : charIndex;
        }
      }
    }
  }

  assert(false);
  return 0;
}

void EditorWidget::resizeEvent(QResizeEvent* eventPtr) {
  calculate();
  DocumentWidget::resizeEvent(eventPtr);
}

void EditorWidget::calculate() {
  m_lineList.clear();
  m_rectList.clear();
  QFontMetrics metrics(m_textFont);
  m_fontHeight = metrics.height();
  QList<int> charWidthList, lineWidthList;
  int windowWidth = width();

  { int firstIndex = 0, lineWidth = 0;
    for (int charIndex = 0; charIndex < m_editorText.size();
         ++charIndex) {
      QChar c = m_editorText[charIndex];

      if (c == '\n') {
        charWidthList.push_back(1);
        lineWidthList.push_back(lineWidth);
        m_lineList.push_back
                   (QPair<int,int>(firstIndex, charIndex));
        firstIndex = charIndex + 1;
        lineWidth = 0;
      }
      else {
        int charWidth = metrics.width(c);
        charWidthList.push_back(charWidth);

        if ((lineWidth + charWidth) > windowWidth) {
          if (firstIndex == charIndex) {
            lineWidthList.push_back(windowWidth);
            m_lineList.push_back
                       (QPair<int,int>(firstIndex, charIndex));
            firstIndex = charIndex + 1;
          }
          else {
            lineWidthList.push_back(lineWidth);
            m_lineList.push_back(QPair<int,int>(firstIndex,
                                                charIndex - 1));
            firstIndex = charIndex;
          }

          lineWidth = 0;
        }
        else {
          lineWidth += charWidth;
        }
      }
    }

    m_lineList.push_back(QPair<int,int>(firstIndex,
                                        m_editorText.size() - 1));
    lineWidthList.push_back(lineWidth);
  }

  { int top = 0, left;
    for (int lineIndex = 0; lineIndex < m_lineList.size();
         ++lineIndex) {
      QPair<int,int> lineInfo = m_lineList[lineIndex];
      int lineWidth = lineWidthList[lineIndex];
      int firstIndex = lineInfo.first,
          lastIndex = lineInfo.second;

      switch (m_alignment) {
        case Left:
          left = 0;
          break;

        case Center:
          left = (windowWidth - lineWidth) / 2;
          break;

        case Right:
          left = windowWidth - lineWidth;
          break;
      }

      for (int charIndex = firstIndex;
           charIndex <= lastIndex;++charIndex){
        int charWidth = charWidthList[charIndex];
        QRect charRect(left, top, charWidth, m_fontHeight);
        m_rectList.push_back(charRect);
        left += charWidth;
      }

      if (lastIndex == (m_editorText.size() - 1)) {
        QRect lastRect(left, top, 1, m_fontHeight);
        m_rectList.push_back(lastRect);
      }

      top += m_fontHeight;
    }
  }
}

void EditorWidget::paintEvent(QPaintEvent* /*eventPtr*/) {
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);
  painter.setRenderHint(QPainter::TextAntialiasing);
  painter.setFont(m_textFont);

  int minIndex = qMin(m_firstIndex, m_lastIndex),
      maxIndex = qMax(m_firstIndex, m_lastIndex);

  for (int index = 0; index < m_editorText.length(); ++index) {
    QChar c = m_editorText[index];

    if (c != '\n') {
      if ((m_mode == Mark) &&
          (index >= minIndex) && (index < maxIndex)) {
        painter.setPen(Qt::white);
        painter.setBackground(Qt::black);
      }
      else {
        painter.setPen(Qt::black);
        painter.setBrush(Qt::white);
      }

      QRect rect = m_rectList[index];
      painter.drawText(rect, c);
    }
  }

  m_caret.paint(&painter);
}
