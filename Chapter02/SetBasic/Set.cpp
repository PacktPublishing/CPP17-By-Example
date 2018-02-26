#include <CAssert>
#include <IOStream>
using namespace std;

#include "..\\ListBasic\\Cell.h"
#include "..\\ListBasic\\Iterator.h"
#include "..\\ListBasic\\List.h"
#include "Set.h"

Set::Set() {
  // Empty.
}

Set::Set(double value) {
  add(value);
}

Set::Set(const Set& set)
 :LinkedList(set) {
  // Empty.
}

Set::~Set() {
  // Empty.
}

void Set::assign(const Set& set) {
  clear();
  add(set);
}

bool Set::equal(const Set& set) const {
  if (size() != set.size()) {
    return false;
  }

  Iterator iterator = first();
  while (iterator.hasNext()) {
    if (!set.exists(iterator.getValue())) {
      return false;
    }

    iterator.next();
  }
  
  return true;         
}

bool Set::notEqual(const Set& set) const {
  return !equal(set);
}

bool Set::exists(double value) const {
  Iterator iterator = first();

  while (iterator.hasNext()) {
    if (value == iterator.getValue()) {
      return true;
    }

    iterator.next();
  }

  return false;
}

bool Set::exists(const Set& set) const {
  Iterator iterator = set.first();

  while (iterator.hasNext()) {
    if (!exists(iterator.getValue())) {
      return false;
    }

    iterator.next();
  }

  return true;
}

bool Set::insert(double value) {
  if (!exists(value)) {
    add(value);
    return true;
  }

  return false;
}

bool Set::insert(const Set& set) {
  bool inserted = false;
  Iterator iterator = set.first();

  while (iterator.hasNext()) {
    double value = iterator.getValue();

    if (insert(value)) {
      inserted = true;
    }

    iterator.next();
  }

  return inserted;
}

bool Set::remove(double value) {
  Iterator iterator;
  
  if (find(value, iterator)) {
    erase(iterator);
    return true;
  }

  return false;
}

bool Set::remove(const Set& set) {
  bool removed = false;
  Iterator iterator = set.first();

  while (iterator.hasNext()) {
    double value = iterator.getValue();

    if (remove(value)) {
      removed = true;
    }

    iterator.next();
  }

  return removed;
}

Set unionSet(const Set& leftSet, const Set& rightSet) {
  Set result(leftSet);
  result.insert(rightSet);
  return result;
}

Set intersection(const Set& leftSet, const Set& rightSet) {
  return difference(difference(unionSet(leftSet, rightSet),
                               difference(leftSet, rightSet)),
                    difference(rightSet, leftSet));
}

Set difference(const Set& leftSet, const Set& rightSet) {
  Set result(leftSet);
  result.remove(rightSet);
  return result;
}

void Set::read(istream& inStream) {
  int size;
  inStream >> size;

  int count = 0;
  while (count < size) {
    double value;
    inStream >> value;
    insert(value);
    ++count;
  }
}

void Set::write(ostream& outStream) {
  outStream << "{";
  bool firstValue = true;
  Iterator iterator = first();

  while (iterator.hasNext()) {
    outStream << (firstValue ? "" : ",") << iterator.getValue();
    firstValue = false;
    iterator.next();
  }

  outStream << "}";
}