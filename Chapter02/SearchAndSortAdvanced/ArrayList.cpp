#include <IOStream>
#include <CStdLib>
#include <CAssert>
using namespace std;

#include "ArrayList.h"

const ArrayList::Iterator ArrayList::EndPosition((ArrayList*) nullptr, -1);

ArrayList::Iterator::Iterator()
 :m_listPtr(nullptr),
  m_listPtrConst(nullptr),
  m_index(0) {
  // Empty.
} 

ArrayList::Iterator::Iterator(ArrayList* listPtr, int index)
 :m_listPtr(listPtr),
  m_listPtrConst(listPtr),
  m_index(index) {
  // Empty.
} 

ArrayList::Iterator::Iterator(const ArrayList* listPtrConst, int index)
 :m_listPtr((ArrayList*) listPtrConst),
  m_listPtrConst(listPtrConst),
  m_index(index) {
  // Empty.
} 

ArrayList::Iterator::Iterator(const Iterator& position)
 :m_listPtr(position.m_listPtr),
  m_listPtrConst(position.m_listPtrConst),
  m_index(position.m_index) {
  // Empty.
}

ArrayList::Iterator& ArrayList::Iterator::operator=(const ArrayList::Iterator& position) {
  m_listPtr = position.m_listPtr;
  m_listPtrConst = position.m_listPtrConst;
  m_index = position.m_index;
  return *this;
}

bool ArrayList::Iterator::operator==(const Iterator& position) {
  return (m_listPtr == position.m_listPtr) &&
         (m_listPtrConst == position.m_listPtrConst) &&
         (m_index == position.m_index);
}

bool ArrayList::Iterator::operator!=(const Iterator& position) {
  return !(*this == position);
}

bool ArrayList::Iterator::hasPrevious() const {
  return (m_index > 0);
}

ArrayList::Iterator& ArrayList::Iterator::previous() {
  --m_index;
  return *this;
}

ArrayList::Iterator& ArrayList::Iterator::eraseAndPrevious() {
  assert(m_listPtr != nullptr);
  m_listPtr->erase(m_index--);
  return *this;
}

bool ArrayList::Iterator::hasNext() const {
  int size = (m_listPtr != nullptr) ? m_listPtr->size()
                                    : m_listPtrConst->size();
  return (m_index < size);
}

ArrayList::Iterator& ArrayList::Iterator::next() {
  ++m_index;
  return *this;
}

ArrayList::Iterator& ArrayList::Iterator::eraseAndNext() {
  assert(m_listPtr != nullptr);
  m_listPtr->erase(m_index++);
  return *this;
}

ArrayList::ArrayList()
 :m_size(0),
  m_buffer(nullptr) {
  // Empty.
}

ArrayList::ArrayList(const ArrayList& list) {
  copy(list, *this, 0, list.m_size);
}

ArrayList& ArrayList::operator=(const ArrayList& list) {
  delete[] m_buffer;
  copy(list, *this, 0, list.m_size);
  return *this;
}

void ArrayList::copy(const ArrayList& list, ArrayList& result,
                     int startIndex, int size) {
  result.m_size = size;
  result.m_buffer = new double[size];
  assert(result.m_buffer != nullptr);

  for (int index = 0; index < size; ++index) {
    result.m_buffer[index] = list.m_buffer[startIndex + index];
  }
}

ArrayList::~ArrayList() {
  delete [] m_buffer;
}

double ArrayList::operator[](int index) const {
  assert((index >= 0) && (index < m_size));
  return m_buffer[index];
}

double& ArrayList::operator[](int index) {
  assert((index >= 0) && (index < m_size));
  return m_buffer[index];
}

bool ArrayList::operator==(const ArrayList& list) const {
  if (m_size == list.m_size) {
    for (int index = 0; index < m_size; ++index) {
      if (m_buffer[index] != list.m_buffer[index]) {
        return false;
      }
    }

    return true;
  }

  return false;
}

bool ArrayList::operator!=(const ArrayList& list) const {
  return !(*this == list);
}

bool ArrayList::operator<(const ArrayList& list) const {
  int minSize = min(m_size, list.m_size);

  for (int index = 0; index < minSize; ++index) {
    if (m_buffer[index] < list.m_buffer[index]) {
      return true;
    }
    else if (m_buffer[index] > list.m_buffer[index]) {
      return false;
    }
  }

  return (m_size < list.m_size);
}

bool ArrayList::operator<=(const ArrayList& list) const {
  return (*this < list) || (*this == list);
}

bool ArrayList::operator>(const ArrayList& list) const {
  return !(*this <= list);
}

bool ArrayList::operator>=(const ArrayList& list) const {
  return !(*this < list);
}

void ArrayList::add(const double& value) {
  double* newBuffer = new double[m_size + 1];
  assert(newBuffer != nullptr);

  for (int index = 0; index < m_size; ++index) {
    newBuffer[index]= m_buffer[index];
  }

  newBuffer[m_size++] = value;
  delete [] m_buffer;
  m_buffer = newBuffer;
}

void ArrayList::add(const ArrayList& list) {
  double* newBuffer = new double[m_size + list.m_size];
  assert(newBuffer != nullptr);

  for (int index = 0; index < m_size; ++index) {
    newBuffer[index]= m_buffer[index];
  }

  for (int index = 0; index < list.m_size; ++index) {
    newBuffer[index + m_size]= list.m_buffer[index];
  }

  delete [] m_buffer;
  m_buffer = newBuffer;
  m_size += list.m_size;
}

void ArrayList::insert(int insertIndex, const double& value) {
  if (insertIndex == m_size) {
    add(value);
  }
  else {
    assert((insertIndex >= 0) && (insertIndex < m_size));
    double* newBuffer = new double[m_size + 1];
    assert(newBuffer != nullptr);

    for (int index = 0; index < insertIndex; ++index) {
      newBuffer[index]= m_buffer[index];
    }

    newBuffer[insertIndex] = value;

    for (int index = insertIndex; index < m_size; ++index) {
      newBuffer[index + 1]= m_buffer[index];
    }

    delete[] m_buffer;
    m_buffer = newBuffer;
    ++m_size;
  }
}

void ArrayList::insert(int insertIndex, const ArrayList& list) {
  if (insertIndex == m_size) {
    add(list);
  }
  else {
    assert((insertIndex >= 0) && (insertIndex < m_size));
    double* newBuffer = new double[list.m_size];
    assert(newBuffer != nullptr);

    for (int index = 0; index < insertIndex; ++index) {
      newBuffer[index] = m_buffer[index];
    }

    for (int index = 0; index < list.m_size; ++index) {
      newBuffer[insertIndex + index] = list.m_buffer[index];
    }

    for (int index = insertIndex; index < m_size; ++index) {
      newBuffer[index + list.m_size] = m_buffer[index];
    }

    delete [] m_buffer;
    m_buffer = newBuffer;
    m_size += list.m_size;
  }
}

void ArrayList::erase(int eraseIndex) {
  remove(eraseIndex, eraseIndex);
}

void ArrayList::remove(int firstIndex, int lastIndex /*= -1*/) {
  lastIndex = (lastIndex == -1) ? (m_size - 1) : lastIndex;
  assert((firstIndex >= 0) && (lastIndex < m_size) &&
         (firstIndex <= lastIndex));
  int removeSize = lastIndex - firstIndex + 1;

  double* newBuffer = new double[m_size - removeSize];
  assert(newBuffer != nullptr);

  for (int index = 0; index < firstIndex; ++index) {
    newBuffer[index] = m_buffer[index];
  }

  for (int index = firstIndex; index < (m_size - removeSize); ++index) {
    newBuffer[index] = m_buffer[index + removeSize];
  }

  delete [] m_buffer;
  m_buffer = newBuffer;
  m_size -= removeSize;
}

ArrayList ArrayList::slice(int firstIndex, int lastIndex /*= -1*/) const {
  lastIndex = (lastIndex == -1) ? (m_size - 1) : lastIndex;
  assert((firstIndex >= 0) && (lastIndex < m_size) &&
         (firstIndex <= lastIndex));

  ArrayList result;
  copy(*this, result, firstIndex, lastIndex - firstIndex + 1);
  return result;
}

void ArrayList::split(ArrayList& left, int index, ArrayList& right) const {
  copy(*this, left, 0, index);
  copy(*this, right, index, m_size - index);
}

ostream& operator<<(ostream& out, const ArrayList& list) {
  out << "[";

  for (int index = 0; index < list.m_size; ++index) {
    out << ((index > 0) ? "," : "") << list.m_buffer[index];
  }

  out << "]";
  return out;
}
