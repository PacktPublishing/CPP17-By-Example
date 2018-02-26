#include "DrawingWindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication application(argc, argv);
  DrawingWindow drawingWindow;
  drawingWindow.show();
  return application.exec();
}
