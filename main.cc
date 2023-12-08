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
  template <typename U> vec2 operator*(U val) const
  {
    vec2 out{this->x() * val, this->y() * val};
    return out;
  }
  void floor()
  {
    this->x() = std::floor(this->x());
    this->y() = std::floor(this->y());
  }
  T& x() { return this->data[0]; }
  T& y() { return this->data[1]; }

  [[nodiscard]] T x() const { return this->data[0]; }
  [[nodiscard]] T y() const { return this->data[1]; }
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
  template <typename U> border operator*(U val) const
  {
    border out{this->top() * val, this->bottom() * val, this->left() * val, this->right() * val};
    return out;
  }
  void floor()
  {
    this->top() = std::floor(this->top());
    this->bottom() = std::floor(this->bottom());
    this->left() = std::floor(this->left());
    this->right() = std::floor(this->right());
  }
  T& top() { return this->data[0]; }
  T& bottom() { return this->data[1]; }
  T& left() { return this->data[2]; }
  T& right() { return this->data[3]; }

  [[nodiscard]] T top() const { return this->data[0]; }
  [[nodiscard]] T bottom() const { return this->data[1]; }
  [[nodiscard]] T left() const { return this->data[2]; }
  [[nodiscard]] T right() const { return this->data[3]; }
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
    case 16: { return "1"; }
    default: return "";
  }
}

int main()
{
  float constexpr mmToInch = 0.03937008f;
  vec2<float> matSize, printSize;
  border<float> artBorder;
  
  std::cout << "Units: mm" << std::endl;
  std::cout << "Enter mat board width: ";
  std::cin >> matSize.x();
  std::cout << "Enter mat board height: ";
  std::cin >> matSize.y();

  std::cout << "Enter print width: ";
  std::cin >> printSize.x();
  std::cout << "Enter print height: ";
  std::cin >> printSize.y();

  std::cout << "Enter TOP art border width: ";
  std::cin >> artBorder.top();
  std::cout << "Enter BOTTOM art border width: ";
  std::cin >> artBorder.bottom();
  std::cout << "Enter LEFT art border width: ";
  std::cin >> artBorder.left();
  std::cout << "Enter RIGHT art border width: ";
  std::cin >> artBorder.right();
  std::cout << std::endl;
  
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

  vec2 artSize = {printSize.x() - (artBorder.left() + artBorder.right()), printSize.y() - (artBorder.top() + artBorder.bottom())};
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

  //FIXME math is wrong?
  vec2 matCenter = {matSize.x() / 2.0f, matSize.y() / 2.0f};
  
  border const align{
    matCenter.y() - artSize.y() / 2.0f - artBorder.top(),
    matCenter.y() - artSize.y() / 2.0f - artBorder.bottom(),
    matCenter.x() - artSize.x() / 2.0f - artBorder.left(),
    matCenter.x() - artSize.x() / 2.0f - artBorder.right()};
  
  border const cut{
    matCenter.y() - artSize.y() / 2.0f,
    matCenter.y() - artSize.y() / 2.0f,
    matCenter.x() - artSize.x() / 2.0f,
    matCenter.x() - artSize.x() / 2.0f};
  
  border<float> cutInch = cut * mmToInch;
  cutInch.floor();
  border<float> alignInch = align * mmToInch;
  alignInch.floor();

  std::string const alignTopIntegral = alignInch.top() == 0 ? "" : std::to_string((int)alignInch.top()) + " ";
  std::string const alignBottomIntegral = alignInch.bottom() == 0 ? "" : std::to_string((int)alignInch.bottom()) + " ";
  std::string const alignLeftIntegral = alignInch.left() == 0 ? "" : std::to_string((int)alignInch.left()) + " ";
  std::string const alignRightIntegral = alignInch.right() == 0 ? "" : std::to_string((int)alignInch.right()) + " ";
  
  std::string const alignFracTop = alignTopIntegral + nearestFraction(align.top() * mmToInch - alignInch.top());
  std::string const alignFracBottom = alignBottomIntegral + nearestFraction(align.bottom() * mmToInch - alignInch.bottom());
  std::string const alignFracLeft = alignLeftIntegral + nearestFraction(align.left() * mmToInch - alignInch.left());
  std::string const alignFracRight = alignRightIntegral + nearestFraction(align.right() * mmToInch - alignInch.right());

  std::string const cutTopIntegral = cutInch.top() == 0 ? "" : std::to_string((int)cutInch.top()) + " ";
  std::string const cutBottomIntegral = cutInch.bottom() == 0 ? "" : std::to_string((int)cutInch.bottom()) + " ";
  std::string const cutLeftIntegral = cutInch.left() == 0 ? "" : std::to_string((int)cutInch.left()) + " ";
  std::string const cutRightIntegral = cutInch.right() == 0 ? "" : std::to_string((int)cutInch.right()) + " ";
  
  std::string const cutFracTop = cutTopIntegral + nearestFraction(cut.top() * mmToInch - cutInch.top());
  std::string const cutFracBottom = cutBottomIntegral + nearestFraction(cut.bottom() * mmToInch - cutInch.bottom());
  std::string const cutFracLeft = cutLeftIntegral + nearestFraction(cut.left() * mmToInch - cutInch.left());
  std::string const cutFracRight = cutRightIntegral + nearestFraction(cut.right() * mmToInch - cutInch.right());

  std::cout << "Make alignment lines on the mat board at "
    << align.top() << "mm (" << alignFracTop << "\") from the top, "
    << align.bottom() << "mm (" << alignFracBottom << "\") from the bottom, "
    << align.left() << "mm (" << alignFracLeft << "\") from the left, "
    << align.right() << "mm (" <<  alignFracRight << "\") from the right." << std::endl << std::endl;

  std::cout << "Make cutout lines on the mat board at "
    << cut.top() << "mm (" << cutFracTop << "\") from the top, "
    << cut.bottom() << "mm (" << cutFracBottom << "\") from the bottom, "
    << cut.left() << "mm (" << cutFracLeft << "\") from the left, "
    << cut.right() << "mm (" << cutFracRight << "\") from the right." << std::endl;
  
  std::cin.get();
  std::cin.get();

  return 0;
}
