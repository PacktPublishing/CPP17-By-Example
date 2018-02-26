#include "MainWindow.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parentWidgetPtr /*= nullptr*/)
 :QMainWindow(parentWidgetPtr) {
}

MainWindow::~MainWindow() {
  for (QAction* actionPtr : menuBar()->actions()) {
    delete actionPtr;
  }
}

void MainWindow::addFileMenu() {
  QMenu* fileMenuPtr = menuBar()->addMenu(tr("&File"));
  connect(fileMenuPtr, SIGNAL(aboutToShow()), this,
          SLOT(onMenuShow()));
  QToolBar *fileToolBarPtr = addToolBar(tr("File"));

  addAction(fileMenuPtr, tr("&New"), SLOT(onNew()),
            QKeySequence::New, tr("new"), fileToolBarPtr,
            tr("Create a new file"));
  addAction(fileMenuPtr, tr("&Open"), SLOT(onOpen()),
            QKeySequence::Open, tr("open"), fileToolBarPtr,
            tr("Open an existing file"));
  addAction(fileMenuPtr, tr("&Save"), SLOT(onSave()),
            QKeySequence::Save, tr("save"), fileToolBarPtr,
            tr("Save the document to disk"),
            LISTENER(isSaveEnabled));
  addAction(fileMenuPtr, tr("Save &As"), SLOT(onSaveAs()),
            0, QString(), nullptr, QString(),
            LISTENER(isSaveEnabled));
  fileMenuPtr->addSeparator();

  addAction(fileMenuPtr, tr("E&xit"),
            SLOT(onExit()), QKeySequence::Quit);
}

void MainWindow::addEditMenu() {
  QMenu* editMenuPtr = menuBar()->addMenu(tr("Edit"));
  QToolBar* editToolBarPtr = addToolBar(tr("Edit"));
  connect(editMenuPtr, SIGNAL(aboutToShow()),
          this, SLOT(onMenuShow()));

  addAction(editMenuPtr, tr("&Cut"), SLOT(onCut()),
            QKeySequence::Cut, tr("cut"), editToolBarPtr,
      tr("Cut the current selection's contents to the clipboard"),
            LISTENER(isCutEnabled));

  addAction(editMenuPtr, tr("&Copy"), SLOT(onCopy()),
            QKeySequence::Copy, tr("copy"), editToolBarPtr,
     tr("Copy the current selection's contents to the clipboard"),
            LISTENER(isCopyEnabled));

  addAction(editMenuPtr, tr("&Paste"), SLOT(onPaste()),
            QKeySequence::Paste, tr("paste"), editToolBarPtr,
    tr("Paste the current selection's contents to the clipboard"),
            LISTENER(isPasteEnabled));

  editMenuPtr->addSeparator();
  addAction(editMenuPtr, tr("&Delete"), SLOT(onDelete()),
            QKeySequence::Delete, tr("delete"), editToolBarPtr,
            tr("Delete the current selection"),
            LISTENER(isDeleteEnabled));
}

void MainWindow::addAction(QMenu* menuPtr, QString itemText,
                           const char* onSelectPtr,
                           QKeySequence acceleratorKey /* = 0 */,
                           QString iconName /*= QString()*/,
                           QToolBar* toolBarPtr /*= nullptr*/,
                           QString statusTip /*= QString()*/,
                           Listener enableListener /*= nullptr*/,
                           Listener checkListener /*= nullptr*/,
                           QActionGroup* groupPtr /*= nullptr*/) {
  QAction* actionPtr;

  if (!iconName.isEmpty()) {
    const QIcon icon = QIcon::fromTheme("document-" + iconName,
                       QIcon(":/images/" + iconName + ".png"));
    actionPtr = new QAction(icon, itemText, this);
  }
  else {
    actionPtr = new QAction(itemText, this);
  }

  connect(actionPtr, SIGNAL(triggered()),
          centralWidget(), onSelectPtr);

  if (acceleratorKey != 0) {
    actionPtr->setShortcut(acceleratorKey);
  }

  menuPtr->addAction(actionPtr);

  if (toolBarPtr != nullptr) {
    toolBarPtr->addAction(actionPtr);
  }

  if (!statusTip.isEmpty()) {
      actionPtr->setToolTip(statusTip);
      actionPtr->setStatusTip(statusTip);
  }

  if (enableListener != nullptr) {
    QWidget* widgetPtr = centralWidget();
    m_enableMap[actionPtr] =
      QPair<QObject*,Listener>(widgetPtr, enableListener);
    actionPtr->setEnabled(enableListener(widgetPtr));
  }

  if (checkListener != nullptr) {
    actionPtr->setCheckable(true);
    QWidget* widgetPtr = centralWidget();
    m_checkMap[actionPtr] =
      QPair<QObject*,Listener>(widgetPtr, checkListener);
    actionPtr->setChecked(checkListener(widgetPtr));
  }

  if (groupPtr != nullptr) {
    groupPtr->addAction(actionPtr);
  }
}

void MainWindow::onMenuShow() {
  for (QMap<QAction*,QPair<QObject*,Listener>>::iterator i =
       m_enableMap.begin(); i != m_enableMap.end(); ++i) {
    QAction* actionPtr = i.key();
    QPair<QObject*,Listener> pair = i.value();
    QObject* baseObjectPtr = pair.first;
    Listener enableFunction = pair.second;
    actionPtr->setEnabled(enableFunction(baseObjectPtr));
  }

  for (QMap<QAction*,QPair<QObject*,Listener>>::iterator i =
       m_checkMap.begin(); i != m_checkMap.end(); ++i) {
    QAction* actionPtr = i.key();
    QPair<QObject*,Listener> pair = i.value();
    QObject* baseObjectPtr = pair.first;
    Listener checkFunction = pair.second;
    actionPtr->setCheckable(true);
    actionPtr->setChecked(checkFunction(baseObjectPtr));
  }
}
