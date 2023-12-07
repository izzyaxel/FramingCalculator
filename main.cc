#include <iostream>

template <typename T> struct vec2
{
  vec2() = default;
  vec2(T x, T y)
  {
    this->x() = x;
    this->y() = y;
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
  T& top() { return this->data[0]; }
  T& bottom() { return this->data[1]; }
  T& left() { return this->data[2]; }
  T& right() { return this->data[3]; }
  T data[4]{0};
};

int main()
{
  double constexpr mmToInch = 0.03937008;
  vec2<float> matSize, printSize, artSize, artCenter, centeringOffset, cutLine;
  border<float> artBorder, alignBorder;
  
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
  alignBorder = {cutLine.y() + artBorder.top(), cutLine.y() + artBorder.bottom(), cutLine.x() + artBorder.left(), cutLine.x() + artBorder.right()};

  std::cout << "Make alignment lines on the mat board at " << alignBorder.top() << "mm (" << alignBorder.top() * mmToInch << "\") from the top, "
    << alignBorder.bottom() << "mm (" << alignBorder.bottom() * mmToInch << "\") from the bottom, "
    << alignBorder.left() << "mm (" << alignBorder.left() * mmToInch << "\") from the left, "
    << alignBorder.right() << "mm (" << alignBorder.right() * mmToInch << "\") from the right." << std::endl;

  std::cout << "Make cutout lines on the mat board at " << cutLine.y() << "mm (" << cutLine.y() * mmToInch << "\") from the top, "
    << cutLine.y() << "mm (" << cutLine.y() * mmToInch << "\") from the bottom, "
    << cutLine.x() << "mm (" << cutLine.x() * mmToInch << "\") from the left, "
    << cutLine.x() << "mm (" << cutLine.x() * mmToInch << "\") from the right." << std::endl;
  std::cin.get();

  return 0;
}
