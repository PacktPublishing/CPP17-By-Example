#include <CAssert>
#include <IOStream>
using namespace std;

#include "Cell.h"
#include "Iterator.h"
#include "List.h"

LinkedList::LinkedList()
 :m_size(0),
  m_firstCellPtr(nullptr),
  m_lastCellPtr(nullptr) {
  // Empty.
}

LinkedList::LinkedList(const LinkedList& list) {
  assign(list);
}

void LinkedList::assign(const LinkedList& list) {
  m_size = 0;
  m_firstCellPtr = nullptr;
  m_lastCellPtr = nullptr;
  Cell *listCellPtr = list.m_firstCellPtr;

  while (listCellPtr != nullptr) {
    double value = listCellPtr->getValue();
    Cell *newCellPtr = new Cell(value, m_lastCellPtr, nullptr);
    assert(newCellPtr != nullptr);

    if (m_firstCellPtr == nullptr) {
      m_firstCellPtr = newCellPtr;
    }
    else {
      m_lastCellPtr->setNext(newCellPtr);
    }

    m_lastCellPtr = newCellPtr;
    ++m_size;

    listCellPtr = listCellPtr->getNext();
  }
}

LinkedList::~LinkedList() {
  clear();
}

void LinkedList::clear() {
  Cell *currCellPtr = m_firstCellPtr;

  while (currCellPtr != nullptr) {
    Cell *deleteCellPtr = currCellPtr;
    currCellPtr = currCellPtr->getNext();
    delete deleteCellPtr;
  }

  m_firstCellPtr = nullptr;
  m_lastCellPtr = nullptr;
  m_size = 0;
}

bool LinkedList::find(double value, Iterator& findIterator) {
  Iterator iterator = first();

  while (iterator.hasNext()) {
    if (value == iterator.getValue()) {
      findIterator = iterator;
      return true;
    }

    iterator.next();
  }

  return false;
}

bool LinkedList::equal(const LinkedList& list) const {
  if (m_size != list.m_size) {
    return false;
  }

  Iterator thisIterator = first(), listIterator = list.first();

  while (thisIterator.hasNext()) {
    if (thisIterator.getValue() != listIterator.getValue()) {
      return false;
    }

    thisIterator.next();
    listIterator.next();
  }

  return true;
}

bool LinkedList::notEqual(const LinkedList& list) const {
  return !equal(list);
}

void LinkedList::add(double value) {
  Cell *newCellPtr = new Cell(value, m_lastCellPtr, nullptr);
  assert(newCellPtr != nullptr);

  if (m_firstCellPtr == nullptr) {
    m_firstCellPtr = newCellPtr;
    m_lastCellPtr = newCellPtr;
  }
  else {
    m_lastCellPtr->setNext(newCellPtr);
    m_lastCellPtr = newCellPtr;
  }

  ++m_size;
}

void LinkedList::add(const LinkedList& list) {
  Cell *listCellPtr = list.m_firstCellPtr;

  while (listCellPtr != nullptr) {
    double value = listCellPtr->getValue();
    Cell *newCellPtr = new Cell(value, m_lastCellPtr, nullptr);

    if (m_firstCellPtr == nullptr) {
      m_firstCellPtr = newCellPtr;
    }
    else {      
      m_lastCellPtr->setNext(newCellPtr);
    }

    m_lastCellPtr = newCellPtr;
    listCellPtr = listCellPtr->getNext();
  }

  m_size += list.m_size;
}

void LinkedList::insert(const Iterator& insertPosition,
                        double value) {
  Cell *insertCellPtr = insertPosition.m_cellPtr;
  Cell *newCellPtr =
    new Cell(value, insertCellPtr->getPrevious(), insertCellPtr);
  assert(newCellPtr != nullptr);
  insertCellPtr->setPrevious(newCellPtr);

  if (insertCellPtr == m_firstCellPtr) {
    m_firstCellPtr = newCellPtr;
  }
  else {
    newCellPtr->getPrevious()->setNext(newCellPtr);
  }

  ++m_size;
}

void LinkedList::insert(const Iterator& insertPosition,
                        const LinkedList& list) {
  Cell *insertCellPtr = insertPosition.m_cellPtr;

  if (insertCellPtr == nullptr) {
    add(list);
  }
  else {
    Cell *firstInsertCellPtr = nullptr,
         *lastInsertCellPtr = nullptr,
         *listCellPtr = list.m_firstCellPtr;

    while (listCellPtr != nullptr) {
      Cell *newCellPtr = new Cell(listCellPtr->getValue(),
                                  lastInsertCellPtr, nullptr);

      if (firstInsertCellPtr == nullptr) {
        firstInsertCellPtr = newCellPtr;
      }
      else {
        lastInsertCellPtr->setNext(newCellPtr);
      }

      lastInsertCellPtr = newCellPtr;
      listCellPtr = listCellPtr->getNext();
    }

    if (firstInsertCellPtr != nullptr) {
      if (insertCellPtr->getPrevious() != nullptr) {
        insertCellPtr->getPrevious()->setNext(firstInsertCellPtr);
        firstInsertCellPtr->
          setPrevious(insertCellPtr->getPrevious());
      }
      else {
        m_firstCellPtr = firstInsertCellPtr;
      }
    }

    if (lastInsertCellPtr != nullptr) {
      lastInsertCellPtr->setNext(insertCellPtr);
      insertCellPtr->setPrevious(lastInsertCellPtr);
    }

    m_size += list.m_size;
  }
}

void LinkedList::erase(const Iterator& removePosition) {
  remove(removePosition, removePosition);
}

void LinkedList::remove(const Iterator& firstPosition,
           const Iterator& lastPosition /*= Iterator(nullptr)*/) {
  Cell *firstCellPtr = firstPosition.m_cellPtr,
       *lastCellPtr = lastPosition.m_cellPtr;
  lastCellPtr = (lastCellPtr == nullptr)
                ? m_lastCellPtr : lastCellPtr;

  Cell *previousCellPtr = firstCellPtr->getPrevious(),
       *nextCellPtr = lastCellPtr->getNext();

  Cell *currCellPtr = firstCellPtr;
  while (currCellPtr != nextCellPtr) {
    Cell *deleteCellPtr = currCellPtr;
    currCellPtr = currCellPtr->getNext();
    delete deleteCellPtr;
    --m_size;
  }

  if (previousCellPtr != nullptr) {
    previousCellPtr->setNext(nextCellPtr);
  }
  else {
    m_firstCellPtr = nextCellPtr;
  }

  if (nextCellPtr != nullptr) {
    nextCellPtr->setPrevious(previousCellPtr);
  }
  else {
    m_lastCellPtr = previousCellPtr;
  }
}

void LinkedList::read(istream& inStream) {
  int size;
  inStream >> size;

  int count = 0;
  while (count < size) {
    double value;
    inStream >> value;
    add(value);
    ++count;
  }
}

void LinkedList::write(ostream& outStream) {
  outStream << "[";
  bool firstValue = true;

  Iterator iterator = first();
  while (iterator.hasNext()) {
    outStream << (firstValue ? "" : ",") << iterator.getValue();
    firstValue = false;
    iterator.next();
  }

  outStream << "]";
}