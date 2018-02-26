#include <QtWidgets>
#include <QMessageBox>

#include "MainWindow.h"
#include "DocumentWidget.h"

DocumentWidget::DocumentWidget(const QString& name,
                const QString& fileMask, QWidget* parentWidgetPtr)
 :m_applicationName(name),
  m_fileMask(fileMask),
  QWidget(parentWidgetPtr) {
  setMainWindowHeader();
}

DocumentWidget::~DocumentWidget() {
  // Empty.
}

void DocumentWidget::setFilePath(QString filePath) {
  m_filePath = filePath;
  setMainWindowHeader();
}

void DocumentWidget::setModifiedFlag(bool modifiedFlag) {
  m_modifiedFlag = modifiedFlag;
  setMainWindowHeader();
  ((MainWindow*) parentWidget())->onMenuShow();
}

void DocumentWidget::setMainWindowHeader() {
  QString header = m_applicationName +
          (m_filePath.isEmpty() ? "" : (" [" + m_filePath + "]"))+
          (m_modifiedFlag ? " *" : "");
  this->parentWidget()->setWindowTitle(header);
}

bool DocumentWidget::isClearOk(QString title) {
  if (m_modifiedFlag) {
    QMessageBox messageBox(QMessageBox::Warning,
                           title, QString());
    messageBox.setText(tr("The document has been modified."));
    messageBox.setInformativeText(
               tr("Do you want to save your changes?"));
    messageBox.setStandardButtons(QMessageBox::Yes |
                          QMessageBox::No | QMessageBox::Cancel);
    messageBox.setDefaultButton(QMessageBox::Yes);

    switch (messageBox.exec()) {
      case QMessageBox::Yes:
        return onSave();

      case QMessageBox::No:
        return true;

      case QMessageBox::Cancel:
        return false;
    }
  }

  return true;
}

void DocumentWidget::onNew() {
  if (isClearOk(tr("New File"))) {
    newDocument();
    setModifiedFlag(false);
    setFilePath(QString());
    update();
  }
}

void DocumentWidget::onOpen() {
  if (isClearOk(tr("Open File"))) {
    QString file =
      QFileDialog::getOpenFileName(this, tr("Open File"),
                   tr("C:\\Users\\Stefan\\Documents\\"
                      "A A_Cpp_By_Example\\Draw"),
              m_fileMask + tr(";;Text files (*.txt)"));

    if (!file.isEmpty()) {
      if (readFile(file)) {
        setModifiedFlag(false);
        setFilePath(file);
        update();
      }
      else {
        QMessageBox messageBox;
        messageBox.setIcon(QMessageBox::Critical);
        messageBox.setText(tr("Read File"));
        messageBox.setInformativeText(tr("Could not read \"") +
                                      m_filePath  + tr("\""));
        messageBox.setStandardButtons(QMessageBox::Ok);
        messageBox.setDefaultButton(QMessageBox::Ok);
        messageBox.exec();
      }
    }
  }
}

bool DocumentWidget::isSaveEnabled() {
  return m_modifiedFlag;
}

bool DocumentWidget::onSave() {
  if (!m_filePath.isEmpty()) {
    return tryWriteFile(m_filePath);
  }
  else {
    return onSaveAs();
  }
}

bool DocumentWidget::onSaveAs() {
  QString filePath =
          QFileDialog::getSaveFileName(this, tr("Save File"),
               tr("C:\\Users\\Stefan\\Documents\\"
                  "A A_Cpp_By_Example\\Draw"),
            m_fileMask + tr(";;Text files (*.txt)"));

  if (!filePath.isEmpty()) {
    return tryWriteFile(filePath);
  }
  else {
    return false;
  }
}

bool DocumentWidget::tryWriteFile(QString filePath) {
  if (writeFile(filePath)) {
    setModifiedFlag(false);
    setFilePath(filePath);
    return true;
  }
  else {
    QMessageBox messageBox;
    messageBox.setIcon(QMessageBox::Critical);
    messageBox.setText(tr("Write File"));
    messageBox.setInformativeText(tr("Could not write \"") +
                                  filePath  + tr("\""));
    messageBox.setStandardButtons(QMessageBox::Ok);
    messageBox.setDefaultButton(QMessageBox::Ok);
    messageBox.exec();
    return false;
  }
}

void DocumentWidget::onExit() {
  if (isClearOk(tr("Exit"))) {
    qApp->exit(0);
  }
}

bool DocumentWidget::isCutEnabled() {
  return isCopyEnabled();
}

void DocumentWidget::onCut() {
  onCopy();
  onDelete();
}

bool DocumentWidget::isCopyEnabled() {
  return false;
}

void DocumentWidget::onCopy() {
  // Empty.
}

bool DocumentWidget::isPasteEnabled() {
  return false;
}

void DocumentWidget::onPaste() {
  // Empty.
}

bool DocumentWidget::isDeleteEnabled() {
  return isCopyEnabled();
}

void DocumentWidget::onDelete() {
  // Empty.
}

void DocumentWidget::closeEvent(QCloseEvent* eventPtr) {
  if (isClearOk(tr("Close Window"))) {
    eventPtr->accept();
    qApp->exit(0);
  }
  else {
    eventPtr->ignore();
  }
}

QPoint& operator+=(QPoint& point, const QSize& size) {
  point.setX(point.x() + size.width());
  point.setY(point.y() + size.height());
  return point;
}

QPoint& operator-=(QPoint& point, const QSize& size) {
  point.setX(point.x() - size.width());
  point.setY(point.y() - size.height());
  return point;
}

QRect& operator+=(QRect& rect, int size) {
  rect.setLeft(rect.left() - size);
  rect.setTop(rect.top() - size);
  rect.setWidth(rect.width() + size);
  rect.setHeight(rect.height() + size);
  return rect;
}

QRect& operator-=(QRect& rect, int size) {
  rect.setLeft(rect.left() + size);
  rect.setTop(rect.top() + size);
  rect.setWidth(rect.width() - size);
  rect.setHeight(rect.height() - size);
  return rect;
}

void writePoint(ofstream& outStream, const QPoint& point) {
  int x = point.x(), y = point.y();
  outStream.write((char*) &x, sizeof x);
  outStream.write((char*) &y, sizeof y);
}

void readPoint(ifstream& inStream, QPoint& point) {
  int x, y;
  inStream.read((char*) &x, sizeof x);
  inStream.read((char*) &y, sizeof y);
  point = QPoint(x, y);
}

void writeColor(ofstream& outStream, const QColor& color) {
  int red = color.red(), green = color.green(),
      blue = color.blue();
  outStream.write((char*) &red, sizeof red);
  outStream.write((char*) &green, sizeof green);
  outStream.write((char*) &blue, sizeof blue);
}

void readColor(ifstream& inStream, QColor& color) {
  int red, green, blue;
  inStream.read((char*) &red, sizeof red);
  inStream.read((char*) &green, sizeof green);
  inStream.read((char*) &blue, sizeof blue);
  color = QColor(red, green, blue);
}

QRect makeRect(const QPoint& centerPoint, int halfSide) {
  return QRect(centerPoint.x() - halfSide,
               centerPoint.y() - halfSide,
               2 * halfSide, 2 * halfSide);
}
