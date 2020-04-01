//
// Created by phil on 10.03.20.
//

#include <iostream>
#include <math/math.h> // NOLINT(modernize-deprecated-headers)
#include <sstream>
#include "tests.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <math\matrix.h>

test_status matTest()
{
  //auto eye = glm::vec3{0,0,0};
  //auto center = glm::vec3{1,1,0};
  //auto up = glm::vec3{0,0,1};
  //auto a = glm::lookAt(eye, center, up);
  //for (size_t i = 0; i < 4; i++)
  //{
  //  std::cout << a.operator[](i).x << '\t' << a.operator[](i).y << '\t' << a.operator[](i).z << '\t' << a.operator[](i).w << std::endl;
  //}

  using namespace Engine::Math;

  mat2 m1;
  mat2 m2(1.f);
//  std::cout << m1 << std::endl;

  Matrix<2,3> mat2x3;
  Matrix<3,4> mat3x4;

  auto res = mat2x3 * mat3x4; // compiler wont let you do an order of multiplication which is invalid

  const Matrix<2,3> L{{1.f,2.f,3.f},{4.f,5.f,6.f}};
  const Matrix<3,2> R{{7.f,8.f},{9.f,10.f},{11.f,12.f}};
  const mat2 S{{58.f,64.f},{139.f,154.f}};
  {
    Matrix<2,2> E = L*R;
    BE_TEST_ASSERT(E == S);
  }

  {
    Matrix<3,3> three(42);
    BE_TEST_ASSERT(three[0][0] == 42);
    BE_TEST_ASSERT(three[1][0] == 42);
    BE_TEST_ASSERT(three[2][0] == 42);

    BE_TEST_ASSERT(three[0][1] == 42);
    BE_TEST_ASSERT(three[1][1] == 42);
    BE_TEST_ASSERT(three[2][1] == 42);

    BE_TEST_ASSERT(three[0][2] == 42);
    BE_TEST_ASSERT(three[1][2] == 42);
    BE_TEST_ASSERT(three[2][2] == 42);
  }

  return test_status::TEST_OK;
}

test_status test_vec2()
{
  Engine::Math::vec2 a(1.0f, 2.0f);
  Engine::Math::vec2 b(1.0f);
  Engine::Math::vec2 c = Engine::Math::vec2();
  // Constructors
  //std::cout << "b:" << b << std::endl;
  BE_TEST_ASSERT(b == Engine::Math::vec2(1.0f, 1.0f));
  BE_TEST_ASSERT(c == Engine::Math::vec2(0.0f, 0.0f));
  BE_TEST_ASSERT(a != b);
  BE_TEST_ASSERT(!(a == b));
  BE_TEST_ASSERT(a==a);
  BE_TEST_ASSERT(a==Engine::Math::vec2(1.0f, 2.0f));

  // ---- Operators -----
  // Addition
  Engine::Math::vec2 add_1 = a+b;
  Engine::Math::vec2 add_2 = b+a;
  //std::cout << "a " << a << std::endl;
  //std::cout << "b " << b << std::endl;
  //std::cout << "add_1 " << add_1 << std::endl;
  BE_TEST_ASSERT(add_1 == Engine::Math::vec2(2.0f, 3.0f));
  BE_TEST_ASSERT(add_2 == Engine::Math::vec2(2.0f, 3.0f));
  BE_TEST_ASSERT(add_2 == add_1);

  // Multiplication
  BE_TEST_ASSERT((a*b) == 3.0f);
  BE_TEST_ASSERT(Engine::Math::Dot(a, b) == 3.0f);
  BE_TEST_ASSERT(Engine::Math::Dot(a, c) == 0.0f);

  // Vector only:
  Engine::Math::vec2 orthogonal = Engine::Math::vec2::Orthogonal();
  BE_TEST_ASSERT(orthogonal == Engine::Math::vec2(0.0f, 1.0f));
  BE_TEST_ASSERT(Engine::Math::Length(orthogonal) == 1.0f);

  std::stringbuf buf;
  std::ostream s(&buf);
  s << a;
  BE_TEST_ASSERT(buf.str() == "(1, 2)\n");

  return test_status::TEST_OK;
}

test_status test_mat2(){
  {
    Engine::Math::mat2 a(0.0f);
    Engine::Math::mat2 b(0.0f, 0.0f, 0.0f, 0.0f);
    BE_TEST_ASSERT(a == b);
    BE_TEST_ASSERT(a*2.f == a);
  }
  {
    Engine::Math::mat2 e1 = Engine::Math::mat2::Identity();
    Engine::Math::mat2 e2({1.0f, 0.0f, 0.0f, 1.0f});
    //std::cout << "e1" << e1 << std::endl;
    //std::cout << "e2" << e2 << std::endl;
    BE_TEST_ASSERT(e1 == e2);
  }

  return test_status::TEST_OK;
}
