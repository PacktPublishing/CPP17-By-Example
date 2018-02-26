#include "..\\MainWindow\\DocumentWidget.h"
#include "Figure.h"

const int Figure::Tolerance(6);

Figure::Figure() {
  // Empty.
}

bool Figure::write(ofstream& outStream) const {
  writeColor(outStream, m_color);
  outStream.write((char*) &m_filled, sizeof m_filled);
  return ((bool) outStream);
}

bool Figure::read(ifstream& inStream) {
  readColor(inStream, m_color);
  inStream.read((char*) &m_filled, sizeof m_filled);
  return ((bool) inStream);
}
