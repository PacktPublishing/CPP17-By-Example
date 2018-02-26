#ifndef DOCUMENTWIDGET_H
#define DOCUMENTWIDGET_H

#include "Listener.h"
#include <QWidget>
#include <QtWidgets>
#include <FStream>
using namespace std;

class DocumentWidget : public QWidget {
  Q_OBJECT

  public:
    DocumentWidget(const QString& name, const QString& fileMask,
                   QWidget* parentWidgetPtr);
    ~DocumentWidget();

  protected:
    void setFilePath(QString filePath);

  public:
    void setModifiedFlag(bool flag);

  private:
    void setMainWindowHeader();

  public:
    virtual void closeEvent(QCloseEvent* eventPtr) /*override*/;

  private:
    bool isClearOk(QString title);

  public slots:
    virtual void onNew();
    virtual void onOpen();
    virtual bool onSave();
    virtual bool isSaveEnabled();
    virtual bool onSaveAs();
    virtual void onExit();

  private:
    bool tryWriteFile(QString filePath);

  public:
    virtual bool isCutEnabled();
    virtual bool isCopyEnabled();
    virtual bool isPasteEnabled();
    virtual bool isDeleteEnabled();

  protected:
    virtual void newDocument() = 0;
    virtual bool writeFile(const QString& filePath) = 0;
    virtual bool readFile(const QString& filePath) = 0;

  public slots:
    virtual void onCut();
    virtual void onCopy();
    virtual void onPaste();
    virtual void onDelete();

  private:
    QString m_applicationName, m_fileMask, m_filePath;
    bool m_modifiedFlag = false;
};

QPoint& operator+=(QPoint& point, const QSize& size);
QPoint& operator-=(QPoint& point, const QSize& size);

QRect& operator+=(QRect& rect, int size);
QRect& operator-=(QRect& rect, int size);

void writePoint(ofstream& outStream, const QPoint& point);
void readPoint(ifstream& inStream, QPoint& point);

void writeColor(ofstream& outStream, const QColor& color);
void readColor(ifstream& inStream, QColor& color);

QRect makeRect(const QPoint& centerPoint, int halfSide);
#endif // DOCUMENTWIDGET_H
