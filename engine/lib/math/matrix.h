/**
 * File              : matrix.h
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 10.03.2020
 * Last Modified Date: 10.03.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#pragma once

#include <glm/glm.hpp>
//TODO: cast constructor from glm stuff
//TODO mat3x3
//TODO mat4x4
//TODO vec4


#include <array>
#include <iostream>
#include <cmath>
#include <type_traits>

namespace Engine::Math
{
  typedef float dA; // default argument

  template<size_t Rows, size_t Columns, typename T = dA>
  class Matrix;

  template<typename U = dA>
  class mat2_generic;

  template<size_t Rows, typename V = dA>
  class vec_generic;

  typedef mat2_generic<dA> mat2;
  typedef vec_generic<2, dA> vec2;

  template<size_t Rows, size_t Columns, typename T>
  class Matrix
  {
  public:
    Matrix() = default;

    Matrix(T const& t)
      : _data{t}
    { }

    ~Matrix() = default;

    constexpr size_t cols() const
    {
      return Columns;
    }

    constexpr size_t rows() const
    {
      return Rows;
    }

    bool operator==(Matrix const& m) const
    {
      if(this == &m)
        return true;

      for (size_t i = 0; i < m.cols(); i++)
      {
        for (size_t j = 0; j < m.rows(); j++)
        {
          if( this->_data[i][j] != m._data[i][j] )
            return false;
        }
      }
      return true;
    }

    bool operator!=(Matrix const& m) const
    {
      return !this->operator==(m);
    }

    Matrix operator+(Matrix const& m) const
    {
      //TODO
      return Matrix();
    }

    Matrix operator-(Matrix const& m) const
    {
      //TODO
    }

    //TODO create outer class methods for the other commutative order of operands for these four operators
    Matrix operator+(T const& m) const
    {
      //TODO
    }

    Matrix operator-(T const& m) const
    {
      //TODO
    }

    Matrix operator*(T const& m) const
    {
      //TODO
      return Matrix();
    }

    Matrix operator/(T const& m) const
    {
      //TODO
    }

    template<size_t C>
    Matrix<Rows,C> operator*(Matrix<Columns, C> const& m) const
    {
      //TODO
      return Matrix<Rows,C>();
    }

    //return a copy which is transposed
    Matrix<Columns, Rows> Transposed() const
    {
      //TODO
      return Matrix<Columns,Rows>();
    }

    constexpr static Matrix
    Identity()
    {
      Matrix m;
      for (size_t d = 0; d < std::min(Rows, Columns); d++)
      {
        m._data[d][d] = 1;
      }
      return m;
    }

    friend std::ostream& operator<<(std::ostream& ostr, Matrix const& m)
    {
      for (size_t i = 0; i < m.cols(); i++)
      {
        for (size_t j = 0; j < m.rows(); j++)
        {
          ostr << m._data[i][j] << ' ';
        }
        ostr << '\n';
      }
      return ostr;
    }

    //typename = std::is_same<T,double>,
    template<typename = std::enable_if<Rows==1 && Columns==1>>
    explicit operator double() const
    {
      //TODO
      return 0.0;
    }


  protected:
    std::array<std::array<T, Columns>, Rows> _data;
  }; // class Matrix

  template<typename U>
  class mat2_generic
    : public Matrix<2,2,U>
  {
  public:
    using Matrix::Matrix;

    mat2_generic(vec2 const& u, vec2 const& v)
    {
      //TODO
    }

    mat2_generic(Matrix<2,2,U> const& m)
    {
      //TODO
    }

    mat2_generic(U a, U b, U c, U d)
    {
      //TODO
    }
  };

  template<size_t Rows, typename U>
  class vec_generic
    : public Matrix<Rows,1,U>
  {
  public:
    using Matrix::Matrix;

    vec_generic(Matrix<Rows,1,U> const& m)
    {
      //TODO
    }

    vec_generic(U a, U b)
    {
      //TODO
    }

    template<typename V>
    vec_generic<1> operator*(vec_generic<Rows, V> const& v) const
    {
      //TODO
      return vec_generic<1>();
    }

    static constexpr vec_generic
    Orthogonal()
    {
      //TODO
      return vec_generic();
    }

    size_t magnitude() const
    {
      //TODO
    }

    size_t Length() const
    {
      BE_ASSERT(false, "length is deprecated, use magnitude() instead!");
      return 0;
    }

    vec_generic Dot(vec_generic const& v) const
    {
      return this->operator*(m):
    }
  };

  template<size_t Rows, typename U>
  vec_generic<1, U> Dot(vec_generic<Rows, U> const& u, vec_generic<Rows, U> const& v)
  {
    return u * v;
  }

  template<size_t Rows, typename U = dA>
  vec_generic<Rows, U> Length(vec_generic<Rows, U> const& u)
  {
    Matrix<1, Rows> v = u.Transposed();
    Matrix<Rows, 1> um = *(Matrix<Rows, 1>*)(&u);
    Matrix<1, 1> val = v * um;
    return std::sqrt((double)val);
  }

  //template<typename T>
  //Matrix<2,2, T>(T a11, T a12,
  //  T a21, T a22)
  //{
  //  std::cout << "foo!!!" << std::endl;
  //}

  //class mat2
  //  : public Matrix<2, 2, dA>
  //{
  //  mat2(dA const& a11,
  //       dA const& a12,
  //       dA const& a21,
  //       dA const& a22)
  //    : Matrix{{a11, a12}, {a21, a22}}
  //  { }
  //};
}


#if 0
namespace Engine::Math
{
  struct mat2 {
  inline mat2(float a11, float a12, float a21, float a22): u({a11, a12}), v({a21, a22}){};
  inline mat2(vec2 _u, vec2 _v): u(_u), v(_v){};
  inline explicit mat2(float x): u(x), v(x){};

  inline static mat2 Identity() {return {1.0f, 0.0f, 0.0f, 1.0f};}

  // dimension is always given, minimum requirement is equality of elements
  inline bool operator==(const mat2& other){return u == other.u && v == other.v;};
  // A * x = b
  inline mat2 operator*(float other){return {u.x * other, u.y * other, v.x * other, v.y * other};};
  inline mat2 operator*(const mat2& other){return {u.x * other.u.x + u.y * other.v.x, u.x * other.u.y + u.y * other.v.y,v.x * other.u.x + v.y * other.v.x, v.x * other.u.y + v.y * other.v.y};};
  friend inline vec2 operator*(const mat2 &a, const vec2 &b) { return {a.u.x*b.x + a.u.y*b.y,a.v.x*b.x + a.v.y*b.y};}
  vec2 u;
  vec2 v;
}; // struct mat2
} // namespace Engine::Math
#endif
