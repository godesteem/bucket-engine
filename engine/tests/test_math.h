//
// Created by phil on 10.03.20.
//

#pragma once

#include <iostream>
#include <math/math.h> // NOLINT(modernize-deprecated-headers)
#include <sstream>
#include "tests.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <math/matrix.h>

//#include <functional>

void TestMath()
{
  // guard against adding tests twice
  static bool alreadyRan = false;
  if(alreadyRan) return;
  alreadyRan = true;

  using namespace Engine::Math;
  Tester::addTest([=]()
  {
    //auto eye = glm::vec3{0,0,0};
    //auto center = glm::vec3{1,1,0};
    //auto up = glm::vec3{0,0,1};
    //auto a = glm::lookAt(eye, center, up);
    //for (size_t i = 0; i < 4; i++)
    //{
    //  std::cout << a.operator[](i).x << '\t' << a.operator[](i).y << '\t' << a.operator[](i).z << '\t' << a.operator[](i).w << std::endl;
    //}
    BE_TEST_ONCE(true);
  });

  Tester::addTest([=]()
  {
    mat2 m1;
    mat2 m2(1.f);
    //  std::cout << m1 << std::endl;

    Matrix<2,3> _mat2x3;
    Matrix<3,4> _mat3x4;

    Matrix<2,4> res = _mat2x3 * _mat3x4; // compiler wont let you do an order of multiplication which is invalid, even if the result is declared as auto type
    BE_TEST_ONCE(true); // if this compiles this test is successful, i cant negatively test for compilation
  });

  Tester::addTest([=]()
  {
    Matrix<2,3,double> m1;
    Matrix<2,3,double> m2(1.f);

    Matrix<2,3,double> _mat2x3;
    Matrix<3,4,double> _mat3x4;

    Matrix<2,4,double> res = _mat2x3 * _mat3x4;
    BE_TEST_ONCE(true); // if this compiles this test is successful, i cant negatively test for compilation
  });

  Tester::addTest([=]()
  {
    vec2 v({{3},
      {4}});
    BE_TEST_ONCE(v.Magnitude() == 5);
  });

  Tester::addTest([=]()
  {
    Matrix<2,1,double> v({{3},
                          {4}});
    BE_TEST_ONCE(v.Magnitude() == 5);
  });

  Tester::addTest([=]()
  {
    vec2 v({{5},
            {12}});
    BE_TEST_ONCE(v.Magnitude() == 13);
  });

  Tester::addTest([=]()
  {
    Matrix<2,3> L{{1.f, 2.f, 3.f},
                  {4.f, 5.f, 6.f}};
    Matrix<3,2> R{{7.f,8.f},{9.f,10.f},{11.f,12.f}};
    Matrix<2,2> S{{58.f,64.f},{139.f,154.f}};
    BE_TEST_ONCE(L*R == S);
  });

  Tester::addTest([=]()
  {
    Matrix<3,3> three(42);
    BE_TEST_MULTI(three[0][0] == 42);
    BE_TEST_MULTI(three[1][0] == 42);
    BE_TEST_MULTI(three[2][0] == 42);

    BE_TEST_MULTI(three[0][1] == 42);
    BE_TEST_MULTI(three[1][1] == 42);
    BE_TEST_MULTI(three[2][1] == 42);

    BE_TEST_MULTI(three[0][2] == 42);
    BE_TEST_MULTI(three[1][2] == 42);
    BE_TEST_ONCE(three[2][2] == 42);
  });

  Tester::addTest([=]()
  {
    //auto ortho23 = Matrix<2,3>::Ortho(); // this line shall not compile
    // arguments are some consecutive primes
    auto ortho44 = Matrix<4,4>::Ortho(23, 29, 31, 37, 41, 43);
    auto glOrtho44 = glm::ortho<Engine::Math::dA_float>(23, 29, 31, 37, 41, 43);

    //std::cout << glOrtho44[3][0] << std::endl;
    for (size_t c = 0; c < 4; c++)
    {
      for (size_t r = 0; r < 4; r++)
      {
        //std::cout << glOrtho44[c][r] << ",\t" << ortho44[r][c];
        BE_TEST_MULTI(ortho44[r][c] == glOrtho44[c][r]);
      }
      //std::cout << '\n';
    }

    return test_status::TEST_OK;
  });

  const Engine::Math::vec2 vec2_1(1.0f);
  const Engine::Math::vec2 vec2_1_2({{1.0f},
                                      {2.0f}});
  const Engine::Math::vec2 vec2_2_3({{2.0f}, {3.0f}});
  const Engine::Math::vec2 vec2_1_2_otherObj{{1.0f},{2.0f}};
  Tester::addTest([=]()
  {
    BE_TEST_ONCE(vec2_1 == Engine::Math::vec2({{1.0f}, {1.0f}}));
  });

  Tester::addTest([=]()
  {
    Engine::Math::vec2 c = Engine::Math::vec2();
    BE_TEST_ONCE(c == Engine::Math::vec2({{0.0f}, {0.0f}}));
  });

  Tester::addTest([=]()
  {
    BE_TEST_ONCE(vec2_1_2 != vec2_1);
  });

  Tester::addTest([=]()
  {
    Engine::Math::vec2 a({{1.0f}, {2.0f}});
    BE_TEST_ONCE(!(a == vec2_1));
  });

  Tester::addTest([=]()
  {
    BE_TEST_ONCE(vec2_1_2==vec2_1_2);
  });

  Tester::addTest([=]()
  {
    BE_TEST_ONCE(vec2_1_2 == vec2_1_2_otherObj);
  });

  Tester::addTest([=]()
  {
    Engine::Math::vec2 add_1 = vec2_1_2 + vec2_1;
    BE_TEST_ONCE(add_1 == vec2_2_3);
  });

  Tester::addTest([=]()
  {
    Engine::Math::vec2 add_2 = vec2_1 + vec2_1_2;
    BE_TEST_ONCE(add_2 == vec2_2_3);
  });

  Tester::addTest([=]()
  {
    Engine::Math::vec2 add_1 = vec2_1_2 + vec2_1;
    Engine::Math::vec2 add_2 = vec2_1 + vec2_1_2;
    BE_TEST_ONCE(add_2 == add_1);
  });

  Tester::addTest([=]()
  {
    // the 3 is cast to a Matrix<1,1> and compared at the matrix level
    BE_TEST_ONCE((vec2_1_2*vec2_1) == 3.0f);
  });

  Tester::addTest([=]()
  {
    // the left hand side is cast to a float and compared at the float level
    BE_TEST_ONCE(float(vec2_1_2*vec2_1) == 3.0f);
  });

  Tester::addTest([=]()
  {
    //BE_TEST_ONCE(3.0f == (vec2_1_2*vec2_1)); // can not compile, implicit cast is not allowed because of confusion which == to take
    BE_TEST_ONCE(3.0f == float(vec2_1_2*vec2_1));
  });

  Tester::addTest([=]()
  {
    BE_TEST_ONCE(vec2_1_2.Dot(vec2_1) == 3.0f);
  });

  Tester::addTest([=]()
  {
    Engine::Math::vec2 c = Engine::Math::vec2();
    BE_TEST_ONCE(vec2_1_2.Dot(c) == 0.0f);
  });

  Tester::addTest([=]()
  {
    std::stringbuf buf;
    std::ostream s(&buf);
    s << vec2_1_2;
    //std::cout << buf.str() << "#";
    //for(auto c : buf.str())
    //  std::cout << c << ":" << (int)c << std::endl;
    BE_TEST_ONCE(buf.str() == "(1, 2)\n");
  });

  const Engine::Math::mat2 mat2_0(0.0f);
  const Engine::Math::mat2 mat2_0_0_0_0({{0.0f, 0.0f}, {0.0f, 0.0f}});
  Tester::addTest([=]()
  {
    BE_TEST_ONCE(mat2_0 == mat2_0_0_0_0);
  });

  Tester::addTest([=]()
  {
    Engine::Math::mat2 a(0.0f);
    BE_TEST_ONCE(a*2.f == a);
  });

  Tester::addTest([=]()
  {
    Matrix<2,2> S{{58.f,64.f},{139.f,154.f}};
    Matrix SS(S);
    BE_TEST_MULTI(SS[0][0] == 58);
    BE_TEST_MULTI(SS[0][1] == 64);
    BE_TEST_MULTI(SS[1][0] == 139);
    BE_TEST_MULTI(SS[1][1] == 154);
    return test_status::TEST_OK;
  });

  Tester::addTest([=]()
  {
    Engine::Math::mat2 e1 = Engine::Math::mat2::Identity();
    Engine::Math::mat2 e2({{1.0f, 0.0f}, {0.0f, 1.0f}});
    //std::cout << "e1" << e1 << std::endl;
    //std::cout << "e2" << e2 << std::endl;
    BE_TEST_ONCE(e1 == e2);
  });

  Tester::addTest([=]()
  {
    mat2 m(5);
    mat2 n(2);
    mat2 r = m-n;
    float resValue = 3;
    BE_TEST_MULTI(r[0][0] == resValue);
    BE_TEST_MULTI(r[0][1] == resValue);
    BE_TEST_MULTI(r[1][0] == resValue);
    BE_TEST_MULTI(r[1][1] == resValue);
    return test_status::TEST_OK;
  });

  Tester::addTest([=]()
  {
    mat2 m(5);
    mat2 n(2);
    mat2 r = n-m;
    float resValue = -3;
    BE_TEST_MULTI(r[0][0] == resValue);
    BE_TEST_MULTI(r[0][1] == resValue);
    BE_TEST_MULTI(r[1][0] == resValue);
    BE_TEST_MULTI(r[1][1] == resValue);
    return test_status::TEST_OK;
  });

  Tester::addTest([=]()
  {
    mat2 m(5);
    mat2 n(2);
    mat2 r = m+n;
    float resValue = 7;
    BE_TEST_MULTI(r[0][0] == resValue);
    BE_TEST_MULTI(r[0][1] == resValue);
    BE_TEST_MULTI(r[1][0] == resValue);
    BE_TEST_MULTI(r[1][1] == resValue);
    return test_status::TEST_OK;
  });

  Tester::addTest([=]()
  {
    mat2 m(5);
    mat2 n(2);
    mat2 r = n+m;
    float resValue = 7;
    BE_TEST_MULTI(r[0][0] == resValue);
    BE_TEST_MULTI(r[0][1] == resValue);
    BE_TEST_MULTI(r[1][0] == resValue);
    BE_TEST_MULTI(r[1][1] == resValue);
    return test_status::TEST_OK;
  });

  Tester::addTest([=]()
  {
    mat2 m(5);
    float n(2);
    mat2 r = m+n;
    float resValue = 7;
    BE_TEST_MULTI(r[0][0] == resValue);
    BE_TEST_MULTI(r[0][1] == resValue);
    BE_TEST_MULTI(r[1][0] == resValue);
    BE_TEST_MULTI(r[1][1] == resValue);
    return test_status::TEST_OK;
  });

  Tester::addTest([=]()
  {
    mat2 m(5);
    float n(2);
    mat2 r = n+m;
    float resValue = 7;
    BE_TEST_MULTI(r[0][0] == resValue);
    BE_TEST_MULTI(r[0][1] == resValue);
    BE_TEST_MULTI(r[1][0] == resValue);
    BE_TEST_MULTI(r[1][1] == resValue);
    return test_status::TEST_OK;
  });

  Tester::addTest([=]()
  {
    mat2 m(5);
    float n(2);
    mat2 r = m-n;
    float resValue = 3;
    BE_TEST_MULTI(r[0][0] == resValue);
    BE_TEST_MULTI(r[0][1] == resValue);
    BE_TEST_MULTI(r[1][0] == resValue);
    BE_TEST_MULTI(r[1][1] == resValue);
    return test_status::TEST_OK;
  });

  Tester::addTest([=]()
  {
    mat2 m(5);
    float n(2);
    mat2 r = n-m;
    float resValue = -3;
    BE_TEST_MULTI(r[0][0] == resValue);
    BE_TEST_MULTI(r[0][1] == resValue);
    BE_TEST_MULTI(r[1][0] == resValue);
    BE_TEST_MULTI(r[1][1] == resValue);
    return test_status::TEST_OK;
  });

  Tester::addTest([=]()
  {
    mat2 m(5);
    float n(2);
    mat2 r = m*n;
    float resValue = 10;
    BE_TEST_MULTI(r[0][0] == resValue);
    BE_TEST_MULTI(r[0][1] == resValue);
    BE_TEST_MULTI(r[1][0] == resValue);
    BE_TEST_MULTI(r[1][1] == resValue);
    return test_status::TEST_OK;
  });

  Tester::addTest([=]()
  {
    mat2 m(5);
    float n(2);
    mat2 r = n*m;
    float resValue = 10;
    BE_TEST_MULTI(r[0][0] == resValue);
    BE_TEST_MULTI(r[0][1] == resValue);
    BE_TEST_MULTI(r[1][0] == resValue);
    BE_TEST_MULTI(r[1][1] == resValue);
    return test_status::TEST_OK;
  });

  Tester::addTest([=]()
  {
    mat2 m(5);
    float n(2);
    mat2 r = m/n;
    float resValue = 5/2.;
    BE_TEST_MULTI(r[0][0] == resValue);
    BE_TEST_MULTI(r[0][1] == resValue);
    BE_TEST_MULTI(r[1][0] == resValue);
    BE_TEST_MULTI(r[1][1] == resValue);
    return test_status::TEST_OK;
  });

  Tester::addTest([=]()
  {
    mat2 m(5);
    mat2 n(2);
    m += n;
    float resValueM = 7;
    BE_TEST_MULTI(m[0][0] == resValueM);
    BE_TEST_MULTI(m[0][1] == resValueM);
    BE_TEST_MULTI(m[1][0] == resValueM);
    BE_TEST_MULTI(m[1][1] == resValueM);
    float resValueN = 2;
    BE_TEST_MULTI(n[0][0] == resValueN);
    BE_TEST_MULTI(n[0][1] == resValueN);
    BE_TEST_MULTI(n[1][0] == resValueN);
    BE_TEST_MULTI(n[1][1] == resValueN);
    return test_status::TEST_OK;
  });

  Tester::addTest([=]()
  {
    mat2 m(5);
    float n(2);
    m += n;
    float resValueM = 7;
    BE_TEST_MULTI(m[0][0] == resValueM);
    BE_TEST_MULTI(m[0][1] == resValueM);
    BE_TEST_MULTI(m[1][0] == resValueM);
    BE_TEST_MULTI(m[1][1] == resValueM);
    return test_status::TEST_OK;
  });

  Tester::addTest([=]()
  {
    mat2 m(5);
    mat2 n(2);
    m -= n;
    float resValueM = 3;
    BE_TEST_MULTI(m[0][0] == resValueM);
    BE_TEST_MULTI(m[0][1] == resValueM);
    BE_TEST_MULTI(m[1][0] == resValueM);
    BE_TEST_MULTI(m[1][1] == resValueM);
    float resValueN = 2;
    BE_TEST_MULTI(n[0][0] == resValueN);
    BE_TEST_MULTI(n[0][1] == resValueN);
    BE_TEST_MULTI(n[1][0] == resValueN);
    BE_TEST_MULTI(n[1][1] == resValueN);
    return test_status::TEST_OK;
  });

  Tester::addTest([=]()
  {
    mat2 m(5);
    float n(2);
    m -= n;
    float resValueM = 3;
    BE_TEST_MULTI(m[0][0] == resValueM);
    BE_TEST_MULTI(m[0][1] == resValueM);
    BE_TEST_MULTI(m[1][0] == resValueM);
    BE_TEST_MULTI(m[1][1] == resValueM);
    return test_status::TEST_OK;
  });

  Tester::addTest([=]()
  {
    mat2 m(5);
    mat2 n(2);
    m *= n;
    float resValueM = 20;
    BE_TEST_MULTI(m[0][0] == resValueM);
    BE_TEST_MULTI(m[0][1] == resValueM);
    BE_TEST_MULTI(m[1][0] == resValueM);
    BE_TEST_MULTI(m[1][1] == resValueM);
    float resValueN = 2;
    BE_TEST_MULTI(n[0][0] == resValueN);
    BE_TEST_MULTI(n[0][1] == resValueN);
    BE_TEST_MULTI(n[1][0] == resValueN);
    BE_TEST_MULTI(n[1][1] == resValueN);
    return test_status::TEST_OK;
  });

  Tester::addTest([=]()
  {
    mat2 m(5);
    float n(2);
    m *= n;
    float resValueM = 10;
    BE_TEST_MULTI(m[0][0] == resValueM);
    BE_TEST_MULTI(m[0][1] == resValueM);
    BE_TEST_MULTI(m[1][0] == resValueM);
    BE_TEST_MULTI(m[1][1] == resValueM);
    return test_status::TEST_OK;
  });

  Tester::addTest([=]()
  {
    mat2 m(5);
    float n(2);
    m /= n;
    float resValueM = 2.5;
    BE_TEST_MULTI(m[0][0] == resValueM);
    BE_TEST_MULTI(m[0][1] == resValueM);
    BE_TEST_MULTI(m[1][0] == resValueM);
    BE_TEST_MULTI(m[1][1] == resValueM);
    return test_status::TEST_OK;
  });

  Tester::addTest([=]()
  {
    mat2 m;
    float resValueM = 0;
    BE_TEST_MULTI(m[0][0] == resValueM);
    BE_TEST_MULTI(m[0][1] == resValueM);
    BE_TEST_MULTI(m[1][0] == resValueM);
    BE_TEST_MULTI(m[1][1] == resValueM);
    return test_status::TEST_OK;
  });

  Tester::addTest([=]()
  {
    mat2 m{{ 2,  5},
           { 1,  3}};
    mat2 i{{ 3, -5},
           {-1,  2}};
    auto r = m*i;
    auto I = mat2::Identity();
    BE_TEST_MULTI(r[0][0] == I[0][0]);
    BE_TEST_MULTI(r[0][1] == I[0][1]);
    BE_TEST_MULTI(r[1][0] == I[1][0]);
    BE_TEST_MULTI(r[1][1] == I[1][1]);
    return test_status::TEST_OK;
  });
}
