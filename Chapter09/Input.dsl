  topLeft = point(100, 100);
  left = xCoordinate(topleft);
  top = yCoordinate(topLeft);
  bottomRight = point(left + 100, top + 100);
  SetPenStyle(DashLine);
  SetBrushStyle(CrossPattern);
  SetPenColor(Black);
  purpleColor = color(128, 0, 128);
  SetBrushColor(purpleColor);
  DrawRectangle(topLeft, bottomRight);

  SetFont(font("Times New Roman", 12));
  SetHorizontalAlignment(AlignLeft);
  SetVerticalAlignment(AlignTop);
  DrawText(point(300, 150), "Hello, DSL!");
