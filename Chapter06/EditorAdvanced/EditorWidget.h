#ifndef EDITORWIDGET_H
#define EDITORWIDGET_H

#include <QWidget>
#include <QMap>
#include <QMenu>
#include <QToolBar>
#include <QPair>
#include "Caret.h"

#include "..\\MainWindow\\Listener.h"
#include "..\\MainWindow\\DocumentWidget.h"

class EditorWidget : public DocumentWidget {
  Q_OBJECT

  public:
    EditorWidget(QWidget* parentWidgetPtr);
    void keyPressEvent(QKeyEvent* eventPtr) override;

  private:
    void keyEditPressEvent(QKeyEvent* eventPtr);
    void keyMarkPressEvent(QKeyEvent* eventPtr);

  public:
    void mousePressEvent(QMouseEvent* eventPtr) override;
    void mouseMoveEvent(QMouseEvent* eventPtr) override;
    void mouseReleaseEvent(QMouseEvent* eventPtr) override;

  private:
    int mouseToIndex(QPoint point);

  public:
    void paintEvent(QPaintEvent* eventPtr) override;
    void resizeEvent(QResizeEvent* eventPtr) override;

  private:
    void newDocument(void) override;
    bool writeFile(const QString& filePath) override;
    bool readFile(const QString& filePath) override;

  public slots:
    bool isCopyEnabled() override;
    void onCopy(void) override;
    bool isPasteEnabled()override;
    void onPaste(void) override;
    void onDelete(void) override;

    DEFINE_LISTENER(EditorWidget, isFontEnabled);
    void onFont(void);

    DEFINE_LISTENER(EditorWidget, isLeftChecked);
    void onLeft(void);
    DEFINE_LISTENER(EditorWidget, isCenterChecked);
    void onCenter(void);
    DEFINE_LISTENER(EditorWidget, isRightChecked);
    void onRight(void);

  private:
    void setCaret();
    void simulateMouseClick(int x, int y);

  private:
    enum Mode {Edit, Mark} m_mode;
    enum Alignment {Left, Center, Right} m_alignment;
    int m_editIndex, m_firstIndex, m_lastIndex;
    Caret m_caret;
    void calculate();
    QList<QPair<int,int>> m_lineList;
    QString m_editorText, m_copyText;
    QList<QRect> m_rectList;
    int m_fontHeight;
    QFont m_textFont;
    Qt::MouseButton m_button;
};

#endif // EDITORWIDGET_H
