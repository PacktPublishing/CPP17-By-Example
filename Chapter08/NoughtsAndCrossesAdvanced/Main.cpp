#include "NaCWidget.h"
#include "NaCWindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication application(argc, argv);
  NaCWindow mainWindow;
  mainWindow.show();
  return application.exec();
}
