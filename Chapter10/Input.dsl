function main() {
  index = 0;
  left = 50;
  length = 50;

  while (index < 4) {
    if ((index % 2) == 0) {
      SetPenStyle(SolidLine);
    }
    else {
      SetPenStyle(DashLine);
    }

    topLeft = point(left, 25);
    call drawTriangle(topLeft, length);

    length = length + 25;
    left = left + length;
    index = index + 1;
  }
}

function drawTriangle(topLeft, length) {
  topRight = call getTopRight(topLeft, length);
  bottomMiddle = call getBottomMiddle(topLeft, length);

  drawLine(topLeft, topRight);
  drawLine(topRight, bottomMiddle);
  drawLine(bottomMiddle, topLeft);
}

function getTopRight(topLeft, length) {
  return point(xCoordinate(topLeft) + length,
               yCoordinate(topLeft));
}

function getBottomMiddle(topLeft, length) {
  left = xCoordinate(topLeft);
  top = yCoordinate(topLeft);
  middle = left + length / 2;
  bottom = top + length;
  return point(middle, bottom);
}
