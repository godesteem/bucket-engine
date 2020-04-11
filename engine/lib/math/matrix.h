#pragma once

#include <glm/glm.hpp>
//TODO: cast constructor from glm stuff

#include <array>
#include <cmath>
#include <initializer_list>
#include <iostream>
#include <type_traits>
#include <utility>

namespace Engine::Math
{
  typedef float dA_float; // default argument

  template<size_t Rows, size_t Columns, typename T = dA_float>
  class Matrix;

  typedef Matrix<2, 2, dA_float> mat2;
  typedef Matrix<2, 1, dA_float> vec2;
  typedef Matrix<3, 3, dA_float> mat3;
  typedef Matrix<3, 1, dA_float> vec3;
  typedef Matrix<4, 4, dA_float> mat4;
  typedef Matrix<4, 1, dA_float> vec4;

  template<size_t Rows, size_t Columns, typename T>
  class Matrix
  {
    //jnl maybe this allows for access between different types of matrices,
    //    that could be avoided, but one can also be careful, since this only
    //    applies to the implementation of Matrix, not when using it
    template<size_t R, size_t C, typename t>
    friend class Matrix;

    template<typename u>
    friend class mat2_generic;

  public:
    // empty constructor fills with 0
    Matrix()
      : _data{ std::array<T, Columns>{} }
    { }

#pragma warning(push)
#pragma warning(disable : 26495)
    Matrix(std::initializer_list<std::initializer_list<T>> ll)
    //jnl i am not able to initialize the std::Array in the initializer list
    {
      const std::initializer_list<T>* l = ll.begin();
      for(size_t row = 0; row < Rows; ++row, ++l)
      {
        auto element = l->begin();
        for(size_t col = 0; col < Columns; ++col, ++element) { _data[row][col] = *element; }
      }
    }
#pragma warning(pop)

    Matrix(Matrix const& m)
      : _data{ m._data }
    { }

    Matrix(T const& t)
    {
      auto proxy = std::array<T, Columns>{ t };
      proxy.fill(t);
      _data.fill(proxy);
    }

    ~Matrix() = default;

    constexpr size_t cols() const { return Columns; }

    constexpr size_t rows() const { return Rows; }

    bool operator==(Matrix const& m) const
    {
      if(this == &m) return true;

      for(size_t col = 0; col < m.cols(); col++)
      {
        for(size_t row = 0; row < m.rows(); row++)
        {
          if(this->_data[row][col] != m._data[row][col]) return false;
        }
      }
      return true;
    }

    bool operator!=(Matrix const& m) const { return !this->operator==(m); }

    Matrix operator+(Matrix const& m) const
    {
      Matrix res(*this);
      for(size_t col = 0; col < Columns; col++)
      {
        for(size_t row = 0; row < Rows; row++) { res._data[row][col] += m._data[row][col]; }
      }
      return res;
    }

    Matrix operator-(Matrix const& m) const
    {
      Matrix res(*this);
      for(size_t col = 0; col < Columns; col++)
      {
        for(size_t row = 0; row < Rows; row++) { res._data[row][col] -= m._data[row][col]; }
      }
      return res;
    }

    Matrix operator+(T const& m) const
    {
      Matrix res(*this);
      for(size_t col = 0; col < Columns; col++)
      {
        for(size_t row = 0; row < Rows; row++) { res._data[row][col] += m; }
      }
      return res;
    }

    Matrix operator-(T const& m) const
    {
      Matrix res(*this);
      for(size_t col = 0; col < Columns; col++)
      {
        for(size_t row = 0; row < Rows; row++) { res._data[row][col] -= m; }
      }
      return res;
    }

    Matrix operator*(T const& t) const
    {
      Matrix res(*this);
      for(size_t col = 0; col < Columns; col++)
      {
        for(size_t row = 0; row < Rows; row++) { res._data[row][col] *= t; }
      }
      return res;
    }

    Matrix operator/(T const& m) const
    {
      Matrix res(*this);
      for(size_t col = 0; col < Columns; col++)
      {
        for(size_t row = 0; row < Rows; row++) { res._data[row][col] /= m; }
      }
      return res;
    }

    template<size_t C>
    Matrix<Rows, C, T> operator*(Matrix<Columns, C, T> const& m) const
    {
      Matrix<Rows, C, T> res;
      for(size_t spalte = 0; spalte < C; spalte++)
      {
        for(size_t zeile = 0; zeile < Rows; zeile++)
        {
          res._data[zeile][spalte] = 0;
          for(size_t along = 0; along < Columns; along++) { res._data[zeile][spalte] += this->_data[zeile][along] * m._data[along][spalte]; }
        }
      }
      return res;
    }

    //return a copy which is transposed
    Matrix<Columns, Rows, T> Transposed() const
    {
      Matrix<Columns, Rows, T> res;
      for(size_t col = 0; col < Columns; col++)
      {
        for(size_t row = 0; row < Rows; row++) { res._data[col][row] = this->_data[row][col]; }
      }
      return res;
    }

    constexpr static Matrix Identity()
    {
      Matrix m(0.f);
      for(size_t d = 0; d < std::min(Rows, Columns); d++) { m._data[d][d] = 1.f; }
      return m;
    }

    // this function will only exist (and compile) for a 4x4 Matrix
    template<size_t R = Rows, size_t C = Columns, typename youDidntUseA4x4Matrix = std::enable_if<R == 4 && C == 4>>
    static Matrix<4, 4> // clang-format off
    Ortho(T const& left,
          T const& right,
          T const& bottom,
          T const& top,
          T const& nearVal,
          T const& farVal) // clang-format on
    {
      Matrix<4, 4> res(0);
      res._data[0][0] = 2 / (right - left);
      res._data[0][3] = (right + left) / (left - right);
      res._data[1][1] = 2 / (top - bottom);
      res._data[1][3] = (top + bottom) / (bottom - top);
      res._data[2][2] = 2 / (nearVal - farVal);
      res._data[2][3] = (farVal + nearVal) / (nearVal - farVal);
      res._data[3][3] = 1;
      return res;
    }


    const std::array<T, Columns>& operator[](size_t index) const { return this->_data[index]; }

    friend std::ostream& operator<<(std::ostream& ostr, Matrix const& m)
    {
      for(size_t col = 0; col < m.cols(); col++)
      {
        ostr << '(';
        for(size_t row = 0; row < m.rows(); row++)
        {
          ostr << m._data[row][col];
          if(row < m.rows() - 1) ostr << ", ";
        }
        ostr << ")\n";
      }
      return ostr;
    }

    // explicit cast to underlying template type T
    template<size_t R = Rows, size_t C = Columns, typename size_is_1_1 = std::enable_if<R == 1 && C == 1>>
    explicit operator T() const
    {
      return _data[0][0];
    }

    template<size_t C = Columns, typename onlyForVectors = std::enable_if<C == 1>>
    Matrix<1, 1> operator*(Matrix<Rows, 1> const& v) const
    {
      return v.Transposed() * *this;
    }

    template<size_t C = Columns, typename onlyForVectors = std::enable_if<C == 1>>
    Matrix<1, 1, T> Dot(Matrix<Rows, 1> const& v) const
    {
      return v.Transposed() * *this;
    }

    template<size_t C = Columns, typename onlyForVectors = std::enable_if<C == 1>>
    T Magnitude() const
    {
      return std::sqrt((this->Transposed() * (*this)).operator T());
    }

    Matrix operator-() const { return *this * -1; }

    Matrix operator+() const { return *this; }

    Matrix& operator+=(T const& t)
    {
      for(size_t col = 0; col < Columns; col++)
      {
        for(size_t row = 0; row < Rows; row++) { this->_data[row][col] += t; }
      }
      return *this;
    }

    Matrix& operator+=(Matrix const& m)
    {
      for(size_t col = 0; col < Columns; col++)
      {
        for(size_t row = 0; row < Rows; row++) { this->_data[row][col] += m._data[row][col]; }
      }
      return *this;
    }

    Matrix& operator-=(T const& t)
    {
      for(size_t col = 0; col < Columns; col++)
      {
        for(size_t row = 0; row < Rows; row++) { this->_data[row][col] -= t; }
      }
      return *this;
    }

    Matrix& operator-=(Matrix const& m)
    {
      for(size_t col = 0; col < Columns; col++)
      {
        for(size_t row = 0; row < Rows; row++) { this->_data[row][col] -= m._data[row][col]; }
      }
      return *this;
    }

    Matrix& operator*=(T const& t)
    {
      for(size_t col = 0; col < Columns; col++)
      {
        for(size_t row = 0; row < Rows; row++) { this->_data[row][col] *= t; }
      }
      return *this;
    }

    template<size_t R = Rows, size_t C = Columns, typename onlyForSquareMatrices = std::enable_if<R == C>>
    Matrix& operator*=(Matrix const& m)
    {
      Matrix temp = this->operator*(m);
      for(size_t col = 0; col < Columns; col++)
      {
        for(size_t row = 0; row < Rows; row++) { this->_data[row][col] = temp[row][col]; }
      }
      return *this;
    }

    Matrix& operator/=(T const& t)
    {
      for(size_t col = 0; col < Columns; col++)
      {
        for(size_t row = 0; row < Rows; row++) { this->_data[row][col] /= t; }
      }
      return *this;
    }

    template<size_t C = Columns, size_t R = Rows, typename onlyForVectors = std::enable_if<C == 1 && (R > 0) && R <= 4>>
    T const& x() const
    {
      return _data[0][0];
    }

    template<size_t C = Columns, size_t R = Rows, typename onlyForVectors = std::enable_if<C == 1 && (R > 1) && R <= 4>>
    T const& y() const
    {
      return _data[1][0];
    }

    template<size_t C = Columns, size_t R = Rows, typename onlyForVectors = std::enable_if<C == 1 && (R > 2) && R <= 4>>
    T const& z() const
    {
      return _data[2][0];
    }

    template<size_t C = Columns, size_t R = Rows, typename onlyForVectors = std::enable_if<C == 1 && (R > 3) && R <= 4>>
    T const& w() const
    {
      return _data[3][0];
    }

  private:
    std::array<std::array<T, Columns>, Rows> _data;
  }; // class Matrix

  // commutative operator order
  template<size_t Rows, size_t Columns, typename T>
  Matrix<Rows, Columns, T> operator+(T const& t, Matrix<Rows, Columns, T> const& m)
  {
    return m + t;
  }

  // commutative operator order
  template<size_t Rows, size_t Columns, typename T>
  Matrix<Rows, Columns, T> operator-(T const& t, Matrix<Rows, Columns, T> const& m)
  {
    return -(m - t);
  }

  // commutative operator order
  template<size_t Rows, size_t Columns, typename T>
  Matrix<Rows, Columns, T> operator*(T const& t, Matrix<Rows, Columns, T> const& m)
  {
    return m * t;
  }
} // namespace Engine::Math
