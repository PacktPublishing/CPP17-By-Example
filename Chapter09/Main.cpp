#include <QApplication>
#include <QMessageBox>

#include "Action.h"
#include "Error.h"
#include "Scanner.h"
#include "Parser.h"
#include "ViewerWidget.h"

int main(int argc, char *argv[]) {
  Scanner::init();
  QApplication application(argc, argv);

  try {
    QString path = "C:\\Users\\Stefan\\Documents\\A A_Cpp_By_Example\\DSL_Basic\\Input.dsl";

    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
      error("Cannot open file \"" + path + "\" for reading.");
    }

    QString buffer(file.readAll());
    Scanner scanner(buffer);

    QList<Action> actionList;
    Parser(scanner, actionList);

    ViewerWidget mainWidget(actionList);
    mainWidget.show();
    return application.exec();
  }
  catch (exception e) {
    QMessageBox messageBox(QMessageBox::Information,
                           QString("Error"), QString(e.what()));
    messageBox.exec();
  }
}
