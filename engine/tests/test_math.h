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

void matTest()
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
  mat2 m2(1);
  std::cout << m1 << std::endl;

  Matrix<2,3> mat2x3;
  Matrix<3,4> mat3x4;

  auto res = mat2x3 * mat3x4; // compiler wont let you do an order of multiplication which is invalid

}

int test_vec2()
{
  Engine::Math::vec2 a(1.0f, 2.0f);
  Engine::Math::vec2 b(1.0f);
  Engine::Math::vec2 c = Engine::Math::vec2();
  // Constructors
  std::cout << "b:" << b << std::endl;
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
  std::cout << "a " << a << std::endl;
  std::cout << "b " << b << std::endl;
  std::cout << "add_1 " << add_1 << std::endl;
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

  return TEST_OK;
}

int test_mat2(){
  Engine::Math::mat2 a(0.0f);
  Engine::Math::mat2 b(0.0f, 0.0f, 0.0f, 0.0f);
  Engine::Math::mat2 e1 = Engine::Math::mat2::Identity();
  Engine::Math::mat2 e2({1.0f, 0.0f}, {0.0f, 1.0f});

  BE_TEST_ASSERT(a == b);
  BE_TEST_ASSERT(a*2 == a);
  BE_TEST_ASSERT(e1 == e2);
  return TEST_OK;
}

void test_math(){
  if(test_mat2() != TEST_OK) BE_TEST_ERROR( "Mat2 not working!");
  else BE_TEST_SUCCESS( "Mat2 is working.");
  if(test_vec2() != TEST_OK) BE_TEST_ERROR( "Vec2 not working!");
  else BE_TEST_SUCCESS( "Vec2 is working.");
}
