#include <QApplication>
#include <QMessageBox>
#include <IOStream>
using namespace std;

#include "Action.h"
#include "Error.h"
#include "Scanner.h"
#include "Parser.h"
#include "Evaluator.h"
#include "ViewerWidget.h"

int main(int argc, char *argv[]) {
  Scanner::init();
  QApplication application(argc, argv);

  try {
    QString path = "C:\\Users\\Stefan\\Documents\\A A_Cpp_By_Example\\DSL_Advanced\\Input.dsl";

    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
      error("Cannot open file \"" + path + "\" for reading.");
    }

    QString buffer(file.readAll());
    Scanner scanner(buffer);

    QList<Directive> directiveList;
    QMap<QString,Function> functionMap;
    Parser(scanner, directiveList, functionMap);

    QList<Action> actionList;
    Evaluator generator(directiveList, actionList, functionMap);

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
