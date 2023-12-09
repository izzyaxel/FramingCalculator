#include <cmath>
#include <iostream>

struct vec2
{
  vec2() = default;
  vec2(float x, float y)
  {
    this->x() = x;
    this->y() = y;
  }
  template <typename U> vec2 operator*(U val) const
  {
    vec2 const out{this->x() * val, this->y() * val};
    return out;
  }
  void floor()
  {
    this->x() = std::floor(this->x());
    this->y() = std::floor(this->y());
  }
  float& x() { return this->data[0]; }
  float& y() { return this->data[1]; }
  [[nodiscard]] float x() const { return this->data[0]; }
  [[nodiscard]] float y() const { return this->data[1]; }
  void print() const
  {
    printf("%f %f\n", this->x(), this->y());
  }
  float data[2]{0};
};

struct border
{
  border() = default;
  border(float t, float b, float l, float r)
  {
    this->top() = t;
    this->bottom() = b;
    this->left() = l;
    this->right() = r;
  }
  template <typename U> border operator*(U val) const
  {
    border const out{this->top() * val, this->bottom() * val, this->left() * val, this->right() * val};
    return out;
  }
  void floor()
  {
    this->top() = std::floor(this->top());
    this->bottom() = std::floor(this->bottom());
    this->left() = std::floor(this->left());
    this->right() = std::floor(this->right());
  }
  float& top() { return this->data[0]; }
  float& bottom() { return this->data[1]; }
  float& left() { return this->data[2]; }
  float& right() { return this->data[3]; }
  [[nodiscard]] float top() const { return this->data[0]; }
  [[nodiscard]] float bottom() const { return this->data[1]; }
  [[nodiscard]] float left() const { return this->data[2]; }
  [[nodiscard]] float right() const { return this->data[3]; }
  void print() const
  {
    printf("%f %f %f %f\n", this->top(), this->bottom(), this->left(), this->right());
  }
  float data[4]{0};
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

bool checkError(bool const predicate, std::string const &failMessage)
{
  if(!predicate) return false;
  std::cout << failMessage << std::endl;
  std::cin.get();
  std::cin.get();
  return true;
}

int main()
{
  float constexpr mmToInch = 0.03937008f;
  vec2 matSize, printSize;
  border artBorder;
  
  std::cout << "Units: mm" << std::endl << std::endl;
  std::cout << "Mat board dimensions:" << std::endl;
  std::cout << "Width: ";
  std::cin >> matSize.x();
  std::cout << "Height: ";
  std::cin >> matSize.y();
  std::cout << std::endl;

  if(checkError(matSize.x() == 0 || matSize.y() == 0, "The mat board cannot have zero width or height!"))
    return -1;

  std::cout << "Print dimensions:" << std::endl;
  std::cout << "Width: ";
  std::cin >> printSize.x();
  std::cout << "Height: ";
  std::cin >> printSize.y();
  std::cout << std::endl;

  if(checkError(printSize.x() == 0 || printSize.y() == 0, "The print cannot have zero width or height!"))
    return -1;
  if(checkError(matSize.x() < printSize.x(), "The mat board width cannot be smaller than the print's width!"))
    return -1;
  if(checkError(matSize.y() < printSize.y(), "The mat board height cannot be smaller than the print's height!"))
    return -1;

  std::cout << "Borders: (the width of the blank border between the given edge of the print, and where the art begins on that side)" << std::endl;
  std::cout << "Top border: ";
  std::cin >> artBorder.top();
  std::cout << "Bottom border: ";
  std::cin >> artBorder.bottom();
  std::cout << "Left border: ";
  std::cin >> artBorder.left();
  std::cout << "Right border: ";
  std::cin >> artBorder.right();
  std::cout << std::endl;

  if(checkError(artBorder.top() == 0 || artBorder.bottom() == 0 || artBorder.left() == 0 || artBorder.right() == 0, "No borders may be zero!"))
    return -1;
  if(checkError(artBorder.top() >= printSize.y(), "The top border cannot be greater than or equal to the print's height!"))
    return -1;
  if(checkError(artBorder.bottom() >= printSize.y(), "The bottom border cannot be greater than or equal to the print's height!"))
    return -1;
  if(checkError(artBorder.left() >= printSize.x(), "The left border cannot be greater than or equal to the print's width!"))
    return -1;
  if(checkError(artBorder.right() >= printSize.x(), "The right border cannot be greater than or equal to the print's width!"))
    return -1;
  if(checkError(artBorder.top() + artBorder.bottom() >= printSize.y(), "The top and bottom borders cannot add up to greater than or equal to the print's height!"))
    return -1;
  if(checkError(artBorder.left() + artBorder.right() >= printSize.x(), "The left and right borders cannot add up to greater than or equal to the print's width!"))
    return -1;

  vec2 artSize = {printSize.x() - (artBorder.left() + artBorder.right()), printSize.y() - (artBorder.top() + artBorder.bottom())};
  
  if(checkError(artSize.x() > printSize.x(), "Art width cannot be larger than the print's width!"))
    return -1;
  if(checkError(artSize.y() > printSize.y(), "Art height cannot be larger than the print's height!"))
    return -1;
  
  vec2 matCenter = {matSize.x() / 2.0f, matSize.y() / 2.0f};
  if(checkError(artSize.x() + artBorder.left() + artBorder.right() != printSize.x(), "Print width does not match given parameters!"))
    return -1;
  if(checkError(artSize.y() + artBorder.top() + artBorder.bottom() != printSize.y(), "Print height does not match given parameters!"))
    return -1;
  
  border const align{
    matCenter.y() - (artSize.y() / 2.0f - artBorder.top()),
    matCenter.y() - (artSize.y() / 2.0f - artBorder.bottom()),
    matCenter.x() - (artSize.x() / 2.0f - artBorder.left()),
    matCenter.x() - (artSize.x() / 2.0f - artBorder.right())};
  
  border const cut{
    matCenter.y() - (artSize.y() / 2.0f),
    matCenter.y() - (artSize.y() / 2.0f),
    matCenter.x() - (artSize.x() / 2.0f),
    matCenter.x() - (artSize.x() / 2.0f)};
  
  border cutInch = cut * mmToInch;
  cutInch.floor();
  border alignInch = align * mmToInch;
  alignInch.floor();

  std::string const alignTopInchIntegral = alignInch.top() == 0 ? "" : std::to_string((int)alignInch.top()) + " ";
  std::string const alignBottomInchIntegral = alignInch.bottom() == 0 ? "" : std::to_string((int)alignInch.bottom()) + " ";
  std::string const alignLeftInchIntegral = alignInch.left() == 0 ? "" : std::to_string((int)alignInch.left()) + " ";
  std::string const alignRightInchIntegral = alignInch.right() == 0 ? "" : std::to_string((int)alignInch.right()) + " ";
  
  std::string const alignTopInchFrac = alignTopInchIntegral + nearestFraction(align.top() * mmToInch - alignInch.top());
  std::string const alignBottomInchFrac = alignBottomInchIntegral + nearestFraction(align.bottom() * mmToInch - alignInch.bottom());
  std::string const alignLeftInchFrac = alignLeftInchIntegral + nearestFraction(align.left() * mmToInch - alignInch.left());
  std::string const alignRightInchFrac = alignRightInchIntegral + nearestFraction(align.right() * mmToInch - alignInch.right());

  std::string const cutTopInchIntegral = cutInch.top() == 0 ? "" : std::to_string((int)cutInch.top()) + " ";
  std::string const cutBottomInchIntegral = cutInch.bottom() == 0 ? "" : std::to_string((int)cutInch.bottom()) + " ";
  std::string const cutLeftInchIntegral = cutInch.left() == 0 ? "" : std::to_string((int)cutInch.left()) + " ";
  std::string const cutRightInchIntegral = cutInch.right() == 0 ? "" : std::to_string((int)cutInch.right()) + " ";
  
  std::string const cutTopInchFrac = cutTopInchIntegral + nearestFraction(cut.top() * mmToInch - cutInch.top());
  std::string const cutBottomInchFrac = cutBottomInchIntegral + nearestFraction(cut.bottom() * mmToInch - cutInch.bottom());
  std::string const cutLeftInchFrac = cutLeftInchIntegral + nearestFraction(cut.left() * mmToInch - cutInch.left());
  std::string const cutRightInchFrac = cutRightInchIntegral + nearestFraction(cut.right() * mmToInch - cutInch.right());

  std::cout << "Make alignment lines on the mat board at "
    << align.top() << "mm (" << alignTopInchFrac << "\") from the top, "
    << align.bottom() << "mm (" << alignBottomInchFrac << "\") from the bottom, "
    << align.left() << "mm (" << alignLeftInchFrac << "\") from the left, "
    << align.right() << "mm (" <<  alignRightInchFrac << "\") from the right." << std::endl << std::endl;

  std::cout << "Make cutout lines on the mat board at "
    << cut.top() << "mm (" << cutTopInchFrac << "\") from the top, "
    << cut.bottom() << "mm (" << cutBottomInchFrac << "\") from the bottom, "
    << cut.left() << "mm (" << cutLeftInchFrac << "\") from the left, "
    << cut.right() << "mm (" << cutRightInchFrac << "\") from the right." << std::endl;
  
  std::cin.get();
  std::cin.get();

  return 0;
}
