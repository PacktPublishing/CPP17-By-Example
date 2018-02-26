#include <QApplication>
#include "Clock.h"

int main(int argc, char *argv[]) {
  QApplication application(argc, argv);
  Clock Clock;
  Clock.show();
  return application.exec();
}
