#include <CTime>
#include <CStdLib>
#include <IOStream>
using namespace std;

void main() {
  srand((int) time(nullptr));
  int dice = (rand() % 6 ) + 1;
  cout << "Dice: " << dice << endl;
}