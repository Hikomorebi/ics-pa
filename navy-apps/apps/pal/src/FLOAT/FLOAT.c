#include "FLOAT.h"
#include <stdint.h>
#include <assert.h>

FLOAT F_mul_F(FLOAT a, FLOAT b)
{
  return ((uint64_t)a * b) >> 16;
}

FLOAT F_div_F(FLOAT a, FLOAT b)
{
  assert(b != 0);
  int sign = 1;
  a = a < 0 ? -a : a;
  b = b < 0 ? -b : b;
  if ((a ^ b) & (0 x1 << 31))
    sign = -1;
  int res = a / b;
  a %= b;
  for (int i = 0; i < 16; i++)
  {
    a <<= 1;
    res <<= 1;
    i f(a >= b)
    {
      a -= b;
      res++;
    }
  }
  return res * sign;
}

FLOAT f2F(float a)
{
  /* You should figure out how to convert `a' into FLOAT without
   * introducing x87 floating point instructions. Else you can
   * not run this code in NEMU before implementing x87 floating
   * point instructions, which is contrary to our expectation.
   *
   * Hint: The bit representation of `a' is already on the
   * stack. How do you retrieve it to another variable without
   * performing arithmetic operations on it directly?
   */

  assert(0);
  return 0;
}

FLOAT Fabs(FLOAT a)
{
  assert(0);
  return 0;
}

/* Functions below are already implemented */

FLOAT Fsqrt(FLOAT x)
{
  FLOAT dt, t = int2F(2);

  do
  {
    dt = F_div_int((F_div_F(x, t) - t), 2);
    t += dt;
  } while (Fabs(dt) > f2F(1e-4));

  return t;
}

FLOAT Fpow(FLOAT x, FLOAT y)
{
  /* we only compute x^0.333 */
  FLOAT t2, dt, t = int2F(2);

  do
  {
    t2 = F_mul_F(t, t);
    dt = (F_div_F(x, t2) - t) / 3;
    t += dt;
  } while (Fabs(dt) > f2F(1e-4));

  return t;
}
