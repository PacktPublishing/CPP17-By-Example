#include "EditorWidget.h"
#include <QtWidgets>
#include <CAssert>
using namespace std;

const QFont EditorWidget::TextFont("Times New Roman", 12);
const int EditorWidget::FontWidth(QFontMetrics(TextFont).maxWidth());
const int EditorWidget::FontHeight(QFontMetrics(TextFont).height());

EditorWidget::EditorWidget(QWidget* parentWidgetPtr)
 :DocumentWidget(tr("Editor"), tr("Editor files (*.edi)"),
                 parentWidgetPtr),
  m_editIndex(0),
  m_caret(this),
  m_editorText(tr("Hello\nWorld")) {
/*  QFontMetrics metrics(TextFont);
  FontWidth = metrics.maxWidth();
  FontHeight = metrics.height();*/
  calculate();
  setCaret();
  m_caret.show();
}

void EditorWidget::newDocument(void) {
  m_editIndex = 0;
  m_editorText.clear();
  calculate();
  setCaret();
}

bool EditorWidget::writeFile(const QString& filePath) {
  QFile file(filePath);
  if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
    QTextStream outStream(&file);
    outStream << m_editorText;
    return ((bool) outStream.Ok);
  }

  return false;
}

bool EditorWidget::readFile(const QString& filePath) {
  QFile file(filePath);

  if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    QTextStream inStream(&file);
    m_editorText = inStream.readAll();

    calculate();
    setCaret();
    return ((bool) inStream.Ok);
  }

  return false;
}

void EditorWidget::mousePressEvent(QMouseEvent* eventPtr) {
  if (eventPtr->button() == Qt::LeftButton) {
    m_editIndex = mouseToIndex(eventPtr->pos());
    setCaret();
  }
}

void EditorWidget::keyPressEvent(QKeyEvent* eventPtr) {
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
        m_editorText.remove(--m_editIndex, 1);
        setModifiedFlag(true);
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
  QRect charRect = m_rectList[m_editIndex];
  QRect caretRect(charRect.left(), charRect.top(),
                  1, charRect.height());
  m_caret.hide();
  m_caret.set(caretRect);
  m_caret.show();
}

int EditorWidget::mouseToIndex(QPoint mousePoint) {
  int x = mousePoint.x(), y = mousePoint.y();

  if (y > (FontHeight * m_lineList.size())) {
    y = ((FontHeight * m_lineList.size()) - 1);
  }

  int lineIndex = y / FontHeight;
  QPair<int,int> lineInfo = m_lineList[lineIndex];
  int firstIndex = lineInfo.first, lastIndex = lineInfo.second;

  if (x > ((lastIndex - firstIndex + 1) * FontWidth)) {
    return (lineIndex == (m_lineList.size() - 1))
           ? (lineInfo.second + 1) : lineInfo.second;
  }
  else {
    return firstIndex + (x / FontWidth);
  }

  assert(FALSE);
  return 0;
}

void EditorWidget::resizeEvent(QResizeEvent* eventPtr) {
  calculate();
  DocumentWidget::resizeEvent(eventPtr);
}

void EditorWidget::calculate() {
  m_lineList.clear();
  m_rectList.clear();
  int clientWidth = width();

  { int firstIndex = 0, lineWidth = 0;
    for (int charIndex = 0; charIndex < m_editorText.size();
         ++charIndex) {
      QChar c = m_editorText[charIndex];

      if (c == '\n') {
        m_lineList.push_back
                   (QPair<int,int>(firstIndex, charIndex));
        firstIndex = charIndex + 1;
        lineWidth = 0;
      }
      else {
        if ((lineWidth + FontWidth) > clientWidth) {
          if (firstIndex == charIndex) {
            m_lineList.push_back
                       (QPair<int,int>(firstIndex, charIndex));
            firstIndex = charIndex + 1;
          }
          else {
            m_lineList.push_back(QPair<int,int>(firstIndex,
                                                charIndex - 1));
            firstIndex = charIndex;
          }

          lineWidth = 0;
        }
        else {
          lineWidth += FontWidth;
        }
      }
    }

    m_lineList.push_back(QPair<int,int>(firstIndex,
                                        m_editorText.size() - 1));
  }

  { int top = 0;
    for (int lineIndex = 0; lineIndex < m_lineList.size();
         ++lineIndex) {
      QPair<int,int> lineInfo = m_lineList[lineIndex];
      int firstIndex = lineInfo.first,
          lastIndex = lineInfo.second, left = 0;

      for (int charIndex = firstIndex;
           charIndex <= lastIndex; ++charIndex){
        QRect charRect(left, top, FontWidth, FontHeight);
        m_rectList.push_back(charRect);
        left += FontWidth;
      }

      if (lastIndex == (m_editorText.size() - 1)) {
        QRect lastRect(left, top, 1, FontHeight);
        m_rectList.push_back(lastRect);
      }

      top += FontHeight;
    }
  }
}

void EditorWidget::paintEvent(QPaintEvent* /*eventPtr*/) {
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);
  painter.setRenderHint(QPainter::TextAntialiasing);
  painter.setFont(TextFont);
  painter.setPen(Qt::black);
  painter.setBrush(Qt::white);

  for (int index = 0; index < m_editorText.length(); ++index) {
    QChar c = m_editorText[index];

    if (c != '\n') {
      QRect rect = m_rectList[index];
      painter.drawText(rect, c);
    }
  }

  m_caret.paint(painter);
}
