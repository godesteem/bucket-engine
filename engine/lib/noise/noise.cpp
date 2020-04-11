#include "noise.h"

namespace Engine::Noise {
  FORCE_INLINE int OpenSimplexNoise::FastFloor(double x) {
    int xi = static_cast<int>(x);
    return x < xi ? xi - 1 : xi;
  }

  OpenSimplexNoise::OpenSimplexNoise(int64_t seed) {
    std::array<char, 256> source;
    for (int i = 0; i < 256; i++) {
      source[i] = i;
    }
    seed = seed * 6364136223846793005L + 1442695040888963407L;
    seed = seed * 6364136223846793005L + 1442695040888963407L;
    seed = seed * 6364136223846793005L + 1442695040888963407L;
    for (int i = 255; i >= 0; i--) {
      seed = seed * 6364136223846793005L + 1442695040888963407L;
      int r = static_cast<int>((seed + 31) % (i + 1));
      if (r < 0) {
        r += (i + 1);
      }
      perm[i] = source[r];
      perm2D[i] = perm[i] & 0x0E;
      perm3D[i] = (perm[i] % 24) * 3;
      perm4D[i] = perm[i] & 0xFC;
      source[r] = source[i];
    }
  }

  double OpenSimplexNoise::Evaluate(double x, double y) {
    double stretchOffset = (x + y) * STRETCH_2D;
    double xs = x + stretchOffset;
    double ys = y + stretchOffset;

    int xsb = FastFloor(xs);
    int ysb = FastFloor(ys);

    double squishOffset = (xsb + ysb) * SQUISH_2D;
    double dx0 = x - (xsb + squishOffset);
    double dy0 = y - (ysb + squishOffset);

    double xins = xs - xsb;
    double yins = ys - ysb;

    double inSum = xins + yins;
    int hash =
        static_cast<int>(xins - yins + 1) |
        static_cast<int>(inSum) << 1 |
        static_cast<int>(inSum + yins) << 2 |
        static_cast<int>(inSum + xins) << 4;

    Contribution2 *c = lookup2D[hash];

    double value = 0.0;
    while (c != nullptr) {
      double dx = dx0 + c->dx;
      double dy = dy0 + c->dy;
      double attn = 2 - dx * dx - dy * dy;
      if (attn > 0) {
        int px = xsb + c->xsb;
        int py = ysb + c->ysb;

        int i = perm2D[(perm[px & 0xFF] + py) & 0xFF];
        double valuePart =
            gradients2D[i] * dx
            + gradients2D[i + 1] * dy;

        attn *= attn;
        value += attn * attn * valuePart;
      }
      c = c->Next;
    }

    return value * NORM_2D;
  }

  double OpenSimplexNoise::Evaluate(double x, double y, double z) {
    double stretchOffset = (x + y + z) * STRETCH_3D;
    double xs = x + stretchOffset;
    double ys = y + stretchOffset;
    double zs = z + stretchOffset;

    int xsb = FastFloor(xs);
    int ysb = FastFloor(ys);
    int zsb = FastFloor(zs);

    double squishOffset = (xsb + ysb + zsb) * SQUISH_3D;
    double dx0 = x - (xsb + squishOffset);
    double dy0 = y - (ysb + squishOffset);
    double dz0 = z - (zsb + squishOffset);

    double xins = xs - xsb;
    double yins = ys - ysb;
    double zins = zs - zsb;

    double inSum = xins + yins + zins;
    int hash =
        static_cast<int>(yins - zins + 1) |
        static_cast<int>(xins - yins + 1) << 1 |
        static_cast<int>(xins - zins + 1) << 2 |
        static_cast<int>(inSum) << 3 |
        static_cast<int>(inSum + zins) << 5 |
        static_cast<int>(inSum + yins) << 7 |
        static_cast<int>(inSum + xins) << 9;

    Contribution3 *c = lookup3D[hash];

    double value = 0.0;
    while (c != nullptr) {
      double dx = dx0 + c->dx;
      double dy = dy0 + c->dy;
      double dz = dz0 + c->dz;

      double attn = 2 - dx * dx - dy * dy - dz * dz;
      if (attn > 0) {
        int px = xsb + c->xsb;
        int py = ysb + c->ysb;
        int pz = zsb + c->zsb;

        int i = perm3D[(perm[(perm[px & 0xFF] + py) & 0xFF] + pz) & 0xFF];
        double valuePart =
            gradients3D[i] * dx
            + gradients3D[i + 1] * dy
            + gradients3D[i + 2] * dz;

        attn *= attn;
        value += attn * attn * valuePart;
      }
      c = c->Next;
    }

    return value * NORM_3D;
  }

  double OpenSimplexNoise::Evaluate(double x, double y, double z, double w) {
    double stretchOffset = (x + y + z + w) * STRETCH_4D;
    double xs = x + stretchOffset;
    double ys = y + stretchOffset;
    double zs = z + stretchOffset;
    double ws = w + stretchOffset;

    int xsb = FastFloor(xs);
    int ysb = FastFloor(ys);
    int zsb = FastFloor(zs);
    int wsb = FastFloor(ws);

    double squishOffset = (xsb + ysb + zsb + wsb) * SQUISH_4D;
    double dx0 = x - (xsb + squishOffset);
    double dy0 = y - (ysb + squishOffset);
    double dz0 = z - (zsb + squishOffset);
    double dw0 = w - (wsb + squishOffset);

    double xins = xs - xsb;
    double yins = ys - ysb;
    double zins = zs - zsb;
    double wins = ws - wsb;

    double inSum = xins + yins + zins + wins;

    int hash =
        static_cast<int>(zins - wins + 1) |
        static_cast<int>(yins - zins + 1) << 1 |
        static_cast<int>(yins - wins + 1) << 2 |
        static_cast<int>(xins - yins + 1) << 3 |
        static_cast<int>(xins - zins + 1) << 4 |
        static_cast<int>(xins - wins + 1) << 5 |
        static_cast<int>(inSum) << 6 |
        static_cast<int>(inSum + wins) << 8 |
        static_cast<int>(inSum + zins) << 11 |
        static_cast<int>(inSum + yins) << 14 |
        static_cast<int>(inSum + xins) << 17;

    Contribution4 *c = lookup4D[hash];

    double value = 0.0;
    while (c != nullptr) {
      double dx = dx0 + c->dx;
      double dy = dy0 + c->dy;
      double dz = dz0 + c->dz;
      double dw = dw0 + c->dw;

      double attn = 2 - dx * dx - dy * dy - dz * dz - dw * dw;
      if (attn > 0) {
        int px = xsb + c->xsb;
        int py = ysb + c->ysb;
        int pz = zsb + c->zsb;
        int pw = wsb + c->wsb;

        int i = perm4D[(
                           perm[(
                                    perm[(
                                             perm[px & 0xFF] + py) & 0xFF]
                                    + pz) & 0xFF]
                           + pw) & 0xFF];
        double valuePart =
            gradients4D[i] * dx
            + gradients4D[i + 1] * dy
            + gradients4D[i + 2] * dz
            + gradients4D[i + 3] * dw;

        attn *= attn;
        value += attn * attn * valuePart;
      }
      c = c->Next;
    }

    return value * NORM_4D;
  }

  const double OpenSimplexNoise::STRETCH_2D = -0.211324865405187;
  const double OpenSimplexNoise::STRETCH_3D = -1.0 / 6.0;
  const double OpenSimplexNoise::STRETCH_4D = -0.138196601125011;
  const double OpenSimplexNoise::SQUISH_2D = 0.366025403784439;
  const double OpenSimplexNoise::SQUISH_3D = 1.0 / 3.0;
  const double OpenSimplexNoise::SQUISH_4D = 0.309016994374947;
  const double OpenSimplexNoise::NORM_2D = 1.0 / 47.0;
  const double OpenSimplexNoise::NORM_3D = 1.0 / 103.0;
  const double OpenSimplexNoise::NORM_4D = 1.0 / 30.0;

  std::array<double, 16> OpenSimplexNoise::gradients2D;
  std::array<double, 72> OpenSimplexNoise::gradients3D;
  std::array<double, 256> OpenSimplexNoise::gradients4D;

  std::vector<OpenSimplexNoise::Contribution2 *> OpenSimplexNoise::lookup2D;
  std::vector<OpenSimplexNoise::Contribution3 *> OpenSimplexNoise::lookup3D;
  std::vector<OpenSimplexNoise::Contribution4 *> OpenSimplexNoise::lookup4D;

  std::vector<OpenSimplexNoise::pContribution2> OpenSimplexNoise::contributions2D;
  std::vector<OpenSimplexNoise::pContribution3> OpenSimplexNoise::contributions3D;
  std::vector<OpenSimplexNoise::pContribution4> OpenSimplexNoise::contributions4D;

// Initialise our static tables
  OpenSimplexNoise::StaticConstructor OpenSimplexNoise::staticConstructor;
}