//
// Created by phil on 10.03.20.
//

#include <iostream>
#include <cassert>
#include <math/vector.h>
#include <math/matrix.h>
#include <sstream>
#include "tests.h"


int test_vec2(){
  Engine::Math::vec2 a(1.0f, 2.0f);
  Engine::Math::vec2 b(1.0f);
  Engine::Math::vec2 c = Engine::Math::vec2();

  // Constructors
  assert(b == Engine::Math::vec2(1.0f, 1.0f));
  assert(c == Engine::Math::vec2(0.0f, 0.0f));
  assert(a != b);
  assert(!(a == b));
  assert(a==a);
  assert(a==Engine::Math::vec2(1.0f, 2.0f));

  // ---- Operators -----
  // Addition
  Engine::Math::vec2 add_1 = a+b;
  Engine::Math::vec2 add_2 = b+a;
  assert(add_1 == Engine::Math::vec2(2.0f, 3.0f));
  assert(add_2 == Engine::Math::vec2(2.0f, 3.0f));
  assert(add_2 == add_1);

  // Multiplication
  assert((a*b) == 3.0f);
  assert(Engine::Math::Dot(a, b) == 3.0f);
  assert(Engine::Math::Dot(a, c) == 0.0f);

  // Vector only:
  Engine::Math::vec2 orthogonal = Engine::Math::vec2::Orthogonal();
  assert(orthogonal == Engine::Math::vec2(0.0f, 1.0f));
  assert(Engine::Math::Length(orthogonal) == 1.0f);

  std::stringbuf buf;
  std::ostream s(&buf);
  s << a;
  assert(buf.str() == "(1, 2)\n");

  return TEST_OK;
}

int test_mat2(){
  Engine::Math::mat2 a(0.0f);
  Engine::Math::mat2 b(0.0f, 0.0f, 0.0f, 0.0f);
  Engine::Math::mat2 e1 = Engine::Math::mat2::Entity();
  Engine::Math::mat2 e2({1.0f, 0.0f}, {0.0f, 1.0f});

  assert(a == b);
  assert(a*2 == a);
  assert(e1 == e2);
  return TEST_OK;
}

void test_math(){
  if(test_vec2() != TEST_OK) fprintf(stderr, "Vec2 not working!\n");
  else fprintf(stdout, "Vec2 is working.\n");
  if(test_mat2() != TEST_OK) fprintf(stderr, "Mat2 not working!\n");
  else fprintf(stdout, "Mat2 is working.\n");
}
