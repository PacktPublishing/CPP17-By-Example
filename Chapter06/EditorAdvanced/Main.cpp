#include "EditorWindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication application(argc, argv);
  EditorWindow editorWindow;
  editorWindow.show();
  return application.exec();
}
