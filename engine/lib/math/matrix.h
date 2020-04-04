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

//until implementation is finished
//#include "tests.h"


#include <array>
#include <iostream>
#include <cmath>
#include <type_traits>
#include <initializer_list>
#include <utility>

#define DBGout(x) ;
//std::cout << x << std::endl;

namespace Engine::Math
{
  typedef float dA_float; // default argument

  template<size_t Rows, size_t Columns, typename T = dA_float>
  class Matrix;

  //template<typename U = dA_float>
  //class mat2_generic;

  //template<size_t Rows, typename V = dA_float>
  //class vec_generic;

  //typedef mat2_generic<dA_float> mat2;
  typedef Matrix<2, 2, dA_float> mat2;
  //typedef vec_generic<2, dA_float> vec2;
  typedef Matrix<2, 1, dA_float> vec2;

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
      : _data{std::array<T, Columns>{}}
    { }

    //template <typename ...e>
    //matrix(e&&... e)
    //  : _data{{std::forward<e>(e)...}}
    //{ }

    #pragma warning( push )
    #pragma warning( disable : 26495 )
    Matrix(std::initializer_list<std::initializer_list<T>> ll)
    //jnl i am not able to initialize the std::Array in the initializer list
    {
      for (auto l : ll)
      {
        for(auto e : l)
          DBGout(e << ",")
        DBGout(";");
      }

      const std::initializer_list<T>* l = ll.begin();
      for (size_t row = 0; row < Rows; row++, l++)
      {
        auto element = l->begin();
        for (size_t col = 0; col < Columns; col++, element++)
        {
          DBGout("next_to_insert:" << *element);
          _data[row][col] = *element;
        }
      }
    }
    #pragma warning( pop )

    Matrix(Matrix const& m)
      : _data{m._data}
    { }

    Matrix(T const& t)
    {
      auto proxy = std::array<T,Columns>{t};
      proxy.fill(t);
      _data.fill(proxy);
      DBGout(__FUNCTION__ " " << t);
      DBGout("and then: " << *this);
      //for (size_t col = 0; col < Columns; col++)
      //{
      //  for (size_t row = 0; row < Rows; row++)
      //  {
      //    _data[row][col] = t;
      //  }
      //}
    }

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
      DBGout("*this:\n" << *this);
      DBGout("    m:\n" << m);
      if(this == &m)
        return true;

      for (size_t col = 0; col < m.cols(); col++)
      {
        for (size_t row = 0; row < m.rows(); row++)
        {
          if( this->_data[row][col] != m._data[row][col] )
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
      Matrix res(*this);
      for (size_t col = 0; col < Columns; col++)
      {
        for (size_t row = 0; row < Rows; row++)
        {
          res._data[row][col] += m._data[row][col];
        }
      }
      return res;
    }

    Matrix operator-(Matrix const& m) const
    {
      BE_CORE_ASSERT(false, "this has not yet been implemented and can thus not be used");
      //TODO
    }

    //TODO create outer class methods for the other commutative order of operands for these four operators
    Matrix operator+(T const& m) const
    {
      BE_CORE_ASSERT(false, "this has not yet been implemented and can thus not be used");
      //TODO
    }

    Matrix operator-(T const& m) const
    {
      BE_CORE_ASSERT(false, "this has not yet been implemented and can thus not be used");
      //TODO
    }

    Matrix operator*(T const& t) const
    {
      Matrix res(*this);
      for (size_t col = 0; col < Columns; col++)
      {
        for (size_t row = 0; row < Rows; row++)
        {
          res._data[row][col] *= t;
        }
      }
      return res;
    }

    Matrix operator/(T const& m) const
    {
      BE_CORE_ASSERT(false, "this has not yet been implemented and can thus not be used");
      //TODO
    }

    template<size_t C>
    Matrix<Rows,C> operator*(Matrix<Columns, C> const& m) const
    {
      Matrix<Rows,C> res;
      for (size_t spalte = 0; spalte < C; spalte++)
      {
        for (size_t zeile = 0; zeile < Rows; zeile++)
        {
          res._data[zeile][spalte] = 0;
          for (size_t along = 0; along < Columns; along++)
          {
            res._data[zeile][spalte] += this->_data[zeile][along] * m._data[along][spalte];
          }
        }
      }
      return res;
    }

    //return a copy which is transposed
    Matrix<Columns, Rows> Transposed() const
    {
      Matrix<Columns,Rows> res;
      for (size_t col = 0; col < Columns; col++)
      {
        for (size_t row = 0; row < Rows; row++)
        {
          res._data[col][row] = this->_data[row][col];
        }
      }
      return res;
    }

    constexpr static Matrix
    Identity()
    {
      Matrix m(0.f);
      DBGout("m(0)" << m);
      for (size_t d = 0; d < std::min(Rows, Columns); d++)
      {
        m._data[d][d] = 1.f;
      }
      DBGout("m(I)" << m);
      return m;
    }

    // this function will only exist (and compile) for a 4x4 Matrix
    template <typename youDidntUseA4x4Matrix = std::enable_if<Rows == 4 && Columns == 4, void*>>
    static Matrix<4,4>
    Ortho(T const& left,
          T const& right,
          T const& bottom,
          T const& top,
          T const& nearVal,
          T const& farVal)
    {
      Matrix<4,4> res(0);
      res._data[0][0] = 2 / (right - left);
      res._data[0][3] = (right + left) / (left - right);
      res._data[1][1] = 2 / (top - bottom);
      res._data[1][3] = (top + bottom) / (bottom - top);
      res._data[2][2] = 2 / (nearVal - farVal);
      res._data[2][3] = (farVal + nearVal) / (nearVal - farVal);
      res._data[3][3] = 1;
      return res;
    }


    const std::array<T,Columns> operator[](size_t index) const
    {
      return this->_data[index];
    }

    friend std::ostream& operator<<(std::ostream& ostr, Matrix const& m)
    {
      for (size_t col = 0; col < m.cols(); col++)
      {
        ostr << '(';
        for (size_t row = 0; row < m.rows(); row++)
        {
          ostr << m._data[row][col];
          if(row < m.rows() -1)
            ostr << ", ";
        }
        ostr << ")\n";
      }
      return ostr;
    }

    //typename = std::is_same<T,double>,
    template<typename = std::enable_if<Rows==1 && Columns==1>>
    explicit operator double() const
    {
      BE_CORE_ASSERT(false, "not implemented");
      //TODO
      return 0.0;
    }

    template<typename onlyForVectors = std::enable_if<Columns == 1>>
    Matrix<1,1> operator*(Matrix<Rows, 1> const& v) const
    {
      return v.Transposed() * *this;
    }

    template<typename onlyForVectors = std::enable_if<Columns == 1>>
    Matrix<1,1> Dot(Matrix<Rows, 1> const& v) const
    {
      return v.Transposed() * *this;
    }


  protected:
    std::array<std::array<T, Columns>, Rows> _data;
  }; // class Matrix


  template<typename U>
  class mat2_generic
    : public Matrix<2,2,U>
  {
  public:
    using Matrix<2,2,U>::Matrix;

    mat2_generic(vec2 const& u, vec2 const& v)
    {
      this->_data[0][0] = u[0][0]; this->_data[0][1] = v[0][0];
      this->_data[1][0] = u[1][0]; this->_data[1][1] = v[1][0];
    }

    mat2_generic(Matrix<2,2,U> const& m)
    {
      this->_data = m._data;
    }

    mat2_generic(U const& a, U const& b, U const& c, U const& d)
    {
      this->_data[0][0] = a; this->_data[0][1] = b;
      this->_data[1][0] = c; this->_data[1][1] = d;
    }
  };

  template<size_t Rows, typename U>
  class vec_generic
    : public Matrix<Rows,1,U>
  {
  public:
    using Matrix<Rows,1,U>::Matrix;

    vec_generic(Matrix<Rows,1,U> const& m)
    {
      for (size_t row = 0; row < Rows; row++)
      {
        this->_data[row][0] = m[row][0];
      }
    }

    //template<typename = std::enable_if<Rows==2>>
    //vec_generic(U a, U b)
    //{
    //  _data[0][0] = a;
    //  _data[1][0] = b;
    //}

    //template<typename V>
    //vec_generic<1> operator*(vec_generic<Rows, V> const& v) const
    //{
    //  return v.Transposed() * *this;
    //}

    //static constexpr vec_generic
    //Orthogonal()
    //{
    //  BE_CORE_BE_CORE_ASSERT(false, "this has not yet been implemented and can thus not be used");
    //  //TODO
    //  return vec_generic();
    //}


    size_t magnitude() const
    {
      BE_CORE_ASSERT(false, "this has not yet been implemented and can thus not be used");
      //TODO
    }

    size_t Length() const
    {
      BE_ASSERT(false, "length is deprecated, use magnitude() instead!");
      return 0;
    }

    vec_generic Dot(vec_generic const& v) const
    {
      return this->operator*(v);
    }
  };


  template<size_t Rows, typename U = dA_float>
  vec_generic<Rows, U> Length(vec_generic<Rows, U> const& u)
  {
    Matrix<1, Rows> v = u.Transposed();
    Matrix<Rows, 1> um = *(Matrix<Rows, 1>*)(&u);
    Matrix<1, 1> val = v * um;
    return std::sqrt((double)val);
  }
} // namespace Engine::Math
