#include <cmath>
#include <iostream>

template <typename T> struct vec2
{
  vec2() = default;
  vec2(T x, T y)
  {
    this->x() = x;
    this->y() = y;
  }
  template <typename U> vec2<T> operator*(U val)
  {
    vec2<T> out{this->x() * val, this->y() * val};
    return out;
  }
  void floor()
  {
    std::floor(this->x());
    std::floor(this->y());
  }
  T& x() { return this->data[0]; }
  T& y() { return this->data[1]; }
  T data[2]{0};
};

template <typename T> struct border
{
  border() = default;
  border(T t, T b, T l, T r)
  {
    this->top() = t;
    this->bottom() = b;
    this->left() = l;
    this->right() = r;
  }
  template <typename U> border<T> operator*(U val)
  {
    border<T> out{this->top() * val, this->bottom() * val, this->left() * val, this->right() * val};
    return out;
  }
  void floor()
  {
    std::floor(this->top());
    std::floor(this->bottom());
    std::floor(this->left());
    std::floor(this->right());
  }
  T& top() { return this->data[0]; }
  T& bottom() { return this->data[1]; }
  T& left() { return this->data[2]; }
  T& right() { return this->data[3]; }
  T data[4]{0};
};

std::string nearestFraction(float const decimal)
{
  switch((int)std::round(decimal * 16.0f))
  {
    case 1: { return "1/16"; }
    case 2: { return "1/8"; }
    case 3: { return "3/16"; }
    case 4: { return "1/4"; }
    case 5: { return "5/16";}
    case 6: { return "3/8";}
    case 7: { return "7/16"; }
    case 8: { return "1/2"; }
    case 9: { return "9/16"; }
    case 10: { return "5/8"; }
    case 11: { return "11/16"; }
    case 12: { return "3/4"; }
    case 13: { return "13/16"; }
    case 14: { return "7/8"; }
    case 15: { return "15/16"; }
    default: return "";
  }
}

int main()
{
  float constexpr mmToInch = 0.03937008f;
  vec2<float> matSize, printSize, artSize, artCenter, centeringOffset, cutLine, cutLineInch;
  border<float> artBorder, alignBorder, alignBorderInch;
  
  std::cout << "Units: mm" << std::endl;
  std::cout << "Enter mat board WIDTH: ";
  std::cin >> matSize.x();
  std::cout << "Enter mat board HEIGHT: ";
  std::cin >> matSize.y();

  std::cout << "Enter print WIDTH: ";
  std::cin >> printSize.x();
  std::cout << "Enter print HEIGHT: ";
  std::cin >> printSize.y();

  std::cout << "Enter TOP art border width: ";
  std::cin >> artBorder.top();
  std::cout << "Enter BOTTOM art border width: ";
  std::cin >> artBorder.bottom();
  std::cout << "Enter LEFT art border width: ";
  std::cin >> artBorder.left();
  std::cout << "Enter RIGHT art border width: ";
  std::cin >> artBorder.right();

  //Sanity check
  if(matSize.x() == 0 || matSize.y() == 0 || printSize.x() == 0 || printSize.y() == 0 || artBorder.top() == 0 || artBorder.bottom() == 0 || artBorder.left() == 0 || artBorder.right() == 0)
  {
    std::cout << "No dimensions may be zero" << std::endl;
    return -1;
  }
  if(matSize.x() <= printSize.x())
  {
    std::cout << "Mat width cannot be smaller or equal to the print's width" << std::endl;
    return -1;
  }
  if(matSize.y() <= printSize.y())
  {
    std::cout << "Mat height cannot be smaller or equal to the print's height" << std::endl;
    return -1;
  }

  artSize = {std::max(artBorder.left(), artBorder.right()) - std::min(artBorder.left(), artBorder.right()), std::max(artBorder.top(), artBorder.bottom()) - std::min(artBorder.top(), artBorder.bottom())};
  if(artSize.x() > printSize.x())
  {
    std::cout << "Art width cannot be larger than the print's width" << std::endl;
    return -1;
  }
  if(artSize.y() > printSize.y())
  {
    std::cout << "Art height cannot be larger than the print's height" << std::endl;
    return -1;
  }

  artCenter = {artSize.x() / 2.0f, artSize.y() / 2.0f};
  centeringOffset = {matSize.x() / 2.0f - artCenter.x(), matSize.y() / 2.0f - artCenter.y()};

  cutLine = {centeringOffset.x() + artCenter.x(), centeringOffset.y() + artCenter.y()};
  cutLineInch = cutLine * mmToInch;
  cutLineInch.floor();

  alignBorder = {cutLine.y() + artBorder.top(), cutLine.y() + artBorder.bottom(), cutLine.x() + artBorder.left(), cutLine.x() + artBorder.right()};
  alignBorderInch = alignBorder * mmToInch;
  alignBorderInch.floor();

  std::string const alignFracTop = nearestFraction(alignBorderInch.top() - std::floor(alignBorderInch.top()));
  std::string const alignFracBottom = nearestFraction(alignBorderInch.bottom() - std::floor(alignBorderInch.bottom()));
  std::string const alignFracLeft = nearestFraction(alignBorderInch.left() - std::floor(alignBorderInch.left()));
  std::string const alignFracRight = nearestFraction(alignBorderInch.right() - std::floor(alignBorderInch.right()));

  std::string const cutFracX = nearestFraction(cutLine.x() - std::floor(cutLine.x()));
  std::string const cutFracY = nearestFraction(cutLine.y() - std::floor(cutLine.y()));

  std::cout << "Make alignment lines on the mat board at " << alignBorder.top() << "mm (" << alignBorderInch.top() << " " << alignFracTop << "\") from the top, "
    << alignBorder.bottom() << "mm (" << alignBorderInch.bottom() << " " << alignFracBottom << "\") from the bottom, "
    << alignBorder.left() << "mm (" << alignBorderInch.left() << " " << alignFracLeft << "\") from the left, "
    << alignBorder.right() << "mm (" << alignBorderInch.right() << " " << alignFracRight << "\") from the right." << std::endl;

  std::cout << "Make cutout lines on the mat board at " << cutLine.y() << "mm (" << cutLineInch.y() << " " << cutFracY << "\") from the top, "
    << cutLine.y() << "mm (" << cutLineInch.y() << " " << cutFracY << "\") from the bottom, "
    << cutLine.x() << "mm (" << cutLineInch.x() << " " << cutFracX << "\") from the left, "
    << cutLine.x() << "mm (" << cutLineInch.x() << " " << cutFracX << "\") from the right." << std::endl;
  std::cin.get();

  return 0;
}
