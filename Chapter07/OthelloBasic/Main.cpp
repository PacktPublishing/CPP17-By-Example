#include "OthelloWidget.h"
#include "OthelloWindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication application(argc, argv);
  OthelloWindow othelloWindow;
  othelloWindow.show();
  return application.exec();
}
