#include <CMath>
#include <String>
#include <IOStream>
using namespace std;

#include "Cell.h"
#include "Queue.h"

void main() {
  Queue q;
  q.enter(1);
  q.enter(2);
  q.enter(3);
  cout << "first " << q.first() << ", size " << q.size()
       << ", empty " << (q.empty() ? "true" : "false") << endl;

  q.remove();
  q.remove();
  q.enter(4);
  cout << "first " << q.first() << ", size " << q.size()
       << ", empty " << (q.empty() ? "true" : "false") << endl;
}