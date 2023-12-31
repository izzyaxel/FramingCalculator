#include <cmath>
#include <iostream>

struct Vec2
{
  Vec2() = default;
  Vec2(float const x, float const y)
  {
    this->x() = x;
    this->y() = y;
  }
  template <typename U> Vec2 operator*(U val) const
  {
    Vec2 const out{this->x() * val, this->y() * val};
    return out;
  }
  template <typename U> Vec2 operator-(U val) const
  {
    Vec2 const out{this->x() - val, this->y() - val};
    return out;
  }
  Vec2 operator-(Vec2 other) const
  {
    Vec2 const out{this->x() - other.x(), this->y() - other.y()};
    return out;
  }
  template <typename U> Vec2 operator/(U val) const
  {
    Vec2 const out{this->x() / val, this->y() / val};
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

struct Border
{
  Border() = default;
  Border(float t, float b, float l, float r)
  {
    this->top() = t;
    this->bottom() = b;
    this->left() = l;
    this->right() = r;
  }
  template <typename U> Border operator*(U val) const
  {
    Border const out{this->top() * val, this->bottom() * val, this->left() * val, this->right() * val};
    return out;
  }
  Border operator+(Border const &other) const
  {
    Border const out{this->top() + other.top(), this->bottom() + other.bottom(), this->left() + other.left(), this->right() + other.right()};
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

std::string nearestFraction(float const decimal, float &excess)
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
    case 16: { excess = 1; return ""; }
    default: return "";
  }
}

bool checkError(bool const predicate, std::string const &failMessage)
{
  if(!predicate) return false;
  std::cout << failMessage << std::endl;
  std::cin.get();
  std::cout << "Press any key to continue...";
  std::cin.get();
  return true;
}

int main()
{
  float constexpr mmToInch = 0.03937008f;
  Vec2 matSize, printSize;
  Border artBorder;

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

  Vec2 artSize = {printSize.x() - (artBorder.left() + artBorder.right()), printSize.y() - (artBorder.top() + artBorder.bottom())};

  if(checkError(artSize.x() > printSize.x(), "Art width cannot be larger than the print's width!"))
    return -1;
  if(checkError(artSize.y() > printSize.y(), "Art height cannot be larger than the print's height!"))
    return -1;

  if(checkError(artSize.x() + artBorder.left() + artBorder.right() != printSize.x(), "Print width does not match given parameters!"))
    return -1;
  if(checkError(artSize.y() + artBorder.top() + artBorder.bottom() != printSize.y(), "Print height does not match given parameters!"))
    return -1;

  Vec2 const matBorder = (matSize - printSize) / 2.0f;
  Border align = {matBorder.y(), matBorder.y(), matBorder.x(), matBorder.x()};

  if(artBorder.top() == artBorder.bottom()) //Symmetrical
  {
    align.top() = matBorder.y();
    align.bottom() = matBorder.y();
  }
  else //Asymmetrical
  {
    //FIXME produces all zeroes
    float adjust = (align.top() - align.bottom()) / 2.0f;
    if(artBorder.top() > artBorder.bottom())
    {
      align.top() -= adjust;
      align.bottom() += adjust;
    }
    else
    {
      align.top() += adjust;
      align.bottom() -= adjust;
    }
  }

  if(artBorder.left() == artBorder.right()) //Symmetrical
  {
    align.left() = matBorder.x();
    align.right() = matBorder.x();
  }
  else //Asymmetrical
  {
    float adjust = (align.left() - align.right()) / 2.0f;
    if(artBorder.left() > artBorder.right())
    {
      align.left() -= adjust;
      align.right() += adjust;
    }
    else
    {
      align.left() += adjust;
      align.right() -= adjust;
    }
  }

  if(checkError(align.top() < 0 || align.bottom() < 0 || align.left() < 0 || align.right() < 0, "Error: align contained negative number(s)")) return -1;

  Border const cut = align + artBorder;
  
  Border cutInch = cut * mmToInch;
  cutInch.floor();
  Border alignInch = align * mmToInch;
  alignInch.floor();

  float excess = 0;
  
  std::string const alignTopInchFrac = nearestFraction(align.top() * mmToInch - alignInch.top(), excess);
  alignInch.top() += excess;
  excess = 0;

  std::string const alignBottomInchFrac = nearestFraction(align.bottom() * mmToInch - alignInch.bottom(), excess);
  alignInch.bottom() += excess;
  excess = 0;

  std::string const alignLeftInchFrac = nearestFraction(align.left() * mmToInch - alignInch.left(), excess);
  alignInch.left() += excess;
  excess = 0;

  std::string const alignRightInchFrac = nearestFraction(align.right() * mmToInch - alignInch.right(), excess);
  alignInch.right() += excess;
  excess = 0;

  std::string alignTopInchIntegral = alignInch.top() == 0 ? "" : std::to_string((int)alignInch.top());
  if(!alignTopInchFrac.empty()) alignTopInchIntegral += " ";

  std::string alignBottomInchIntegral = alignInch.bottom() == 0 ? "" : std::to_string((int)alignInch.bottom());
  if(!alignBottomInchFrac.empty()) alignBottomInchIntegral += " ";

  std::string alignLeftInchIntegral = alignInch.left() == 0 ? "" : std::to_string((int)alignInch.left());
  if(!alignLeftInchFrac.empty()) alignLeftInchIntegral += " ";

  std::string alignRightInchIntegral = alignInch.right() == 0 ? "" : std::to_string((int)alignInch.right());
  if(!alignRightInchFrac.empty()) alignRightInchIntegral += " ";

  std::string const cutTopInchFrac = nearestFraction(cut.top() * mmToInch - cutInch.top(), excess);
  cutInch.top() += excess;
  excess = 0;

  std::string const cutBottomInchFrac = nearestFraction(cut.bottom() * mmToInch - cutInch.bottom(), excess);
  cutInch.bottom() += excess;
  excess = 0;

  std::string const cutLeftInchFrac = nearestFraction(cut.left() * mmToInch - cutInch.left(), excess);
  cutInch.left() += excess;
  excess = 0;

  std::string const cutRightInchFrac = nearestFraction(cut.right() * mmToInch - cutInch.right(), excess);
  cutInch.right() += excess;
  excess = 0;

  std::string cutTopInchIntegral = cutInch.top() == 0 ? "" : std::to_string((int)cutInch.top());
  if(!cutTopInchFrac.empty()) cutTopInchIntegral += " ";

  std::string cutBottomInchIntegral = cutInch.bottom() == 0 ? "" : std::to_string((int)cutInch.bottom());
  if(!cutBottomInchFrac.empty()) cutBottomInchIntegral += " ";

  std::string cutLeftInchIntegral = cutInch.left() == 0 ? "" : std::to_string((int)cutInch.left());
  if(!cutLeftInchFrac.empty()) cutLeftInchIntegral += " ";

  std::string cutRightInchIntegral = cutInch.right() == 0 ? "" : std::to_string((int)cutInch.right());
  if(!cutRightInchFrac.empty()) cutRightInchIntegral += " ";

  std::cout << "Make alignment lines on the mat board at "
    << align.top() << "mm (" << alignTopInchIntegral << alignTopInchFrac << "\") from the top, "
    << align.bottom() << "mm (" << alignBottomInchIntegral << alignBottomInchFrac << "\") from the bottom, "
    << align.left() << "mm (" << alignLeftInchIntegral << alignLeftInchFrac << "\") from the left, "
    << align.right() << "mm (" << alignRightInchIntegral <<  alignRightInchFrac << "\") from the right." << std::endl << std::endl;

  std::cout << "Make cutout lines on the mat board at "
    << cut.top() << "mm (" << cutTopInchIntegral << cutTopInchFrac << "\") from the top, "
    << cut.bottom() << "mm (" << cutBottomInchIntegral << cutBottomInchFrac << "\") from the bottom, "
    << cut.left() << "mm (" << cutLeftInchIntegral << cutLeftInchFrac << "\") from the left, "
    << cut.right() << "mm (" << cutRightInchIntegral << cutRightInchFrac << "\") from the right." << std::endl;

  std::cin.get();
  std::cout << std::endl << "Press any key to continue...";
  std::cin.get();

  return 0;
}
