#ifndef LISTENER_H
#define LISTENER_H

#include <QObject>

#define DEFINE_LISTENER(BaseClass, Listener)         \
  friend bool Listener(QObject* baseObjectPtr) {     \
    return ((BaseClass*) baseObjectPtr)->Listener(); \
  }                                                  \
  bool Listener()                                    \

#define LISTENER(Listener) (&::Listener)
typedef bool (*Listener)(QObject*);

#endif // LISTENER_H
