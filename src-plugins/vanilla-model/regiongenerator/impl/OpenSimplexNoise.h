#ifndef FRTS_OPENSIMPLEXNOISE_H
#define FRTS_OPENSIMPLEXNOISE_H

#include <array>


namespace frts
{
    /**
     * @brief Implementation of the OpenSimplex noise algorithm
     *        by KdotJPG.
     * @see https://github.com/KdotJPG
     * @see http://uniblock.tumblr.com/
     * @see https://gist.github.com/KdotJPG/b1270127455a94ac5d19
     */
    class OpenSimplexNoise
    {
    public:
        const static int ARRAY_SIZE = 256;
        using PermutationArray = std::array<short, ARRAY_SIZE>;

    public:
        OpenSimplexNoise(long long seed = 0);
        OpenSimplexNoise(const PermutationArray& perm);
        ~OpenSimplexNoise();

        /**
         * @brief Evaluate noise value at 2D position.
         * @param x The x coordinate.
         * @param y The y coordinate.
         * @return The noise value.
         */
        double eval(double x, double y) const;

        /**
         * @brief Evaluate noise value at 3D position.
         * @param x The x coordinate.
         * @param y The y coordinate.
         * @param z The z coordinate.
         * @return The noise value.
         */
        double eval(double x, double y, double z) const;

        /**
         * @brief Evaluate noise value at 4D position.
         * @param x The x coordinate.
         * @param y The y coordinate.
         * @param z The z coordinate.
         * @param w The w coordinate.
         * @return The noise value.
         */
        double eval(double x, double y, double z, double w) const;

    private:
        const double STRETCH_CONSTANT_2D = -0.211324865405187;  // (1/sqrt(2+1)-1)/2;
        const double SQUISH_CONSTANT_2D = 0.366025403784439;    // (sqrt(2+1)-1)/2;
        const double STRETCH_CONSTANT_3D = -1.0 / 6;            // (1/sqrt(3+1)-1)/3;
        const double SQUISH_CONSTANT_3D = 1.0 / 3;              // (sqrt(3+1)-1)/3;
        const double STRETCH_CONSTANT_4D = -0.138196601125011;  // (1/sqrt(4+1)-1)/4;
        const double SQUISH_CONSTANT_4D = 0.309016994374947;    // (sqrt(4+1)-1)/4;
        const double NORM_CONSTANT_2D = 47;
        const double NORM_CONSTANT_3D = 103;
        const double NORM_CONSTANT_4D = 30;

        /**
         * @brief Gradients for 2D. They approximate the directions to the
         *        vertices of an octagon from the center.
         */
        const std::array<char, 16> gradients2D {{
             5,  2,    2,  5,
            -5,  2,   -2,  5,
             5, -2,    2, -5,
            -5, -2,   -2, -5
        }};

        /**
         * @brief Gradients for 3D. They approximate the directions to the
         *        vertices of a rhombicuboctahedron from the center, skewed so
         *        that the triangular and square facets can be inscribed inside
         *        circles of the same radius.
         */
        const std::array<char, 72> gradients3D {{
            -11,  4,  4,   -4,  11,  4,   -4,  4,  11,
             11,  4,  4,    4,  11,  4,    4,  4,  11,
            -11, -4,  4,   -4, -11,  4,   -4, -4,  11,
             11, -4,  4,    4, -11,  4,    4, -4,  11,
            -11,  4, -4,   -4,  11, -4,   -4,  4, -11,
             11,  4, -4,    4,  11, -4,    4,  4, -11,
            -11, -4, -4,   -4, -11, -4,   -4, -4, -11,
             11, -4, -4,    4, -11, -4,    4, -4, -11
        }};

        /**
         * @brief Gradients for 4D. They approximate the directions to the
         *        vertices of a disprismatotesseractihexadecachoron from the center,
         *        skewed so that the tetrahedral and cubic facets can be inscribed inside
         *        spheres of the same radius.
         */
        const std::array<char, 256>  gradients4D {{
             3,  1,  1,  1,    1,  3,  1,  1,    1,  1,  3,  1,    1,  1,  1,  3,
            -3,  1,  1,  1,   -1,  3,  1,  1,   -1,  1,  3,  1,   -1,  1,  1,  3,
             3, -1,  1,  1,    1, -3,  1,  1,    1, -1,  3,  1,    1, -1,  1,  3,
            -3, -1,  1,  1,   -1, -3,  1,  1,   -1, -1,  3,  1,   -1, -1,  1,  3,
             3,  1, -1,  1,    1,  3, -1,  1,    1,  1, -3,  1,    1,  1, -1,  3,
            -3,  1, -1,  1,   -1,  3, -1,  1,   -1,  1, -3,  1,   -1,  1, -1,  3,
             3, -1, -1,  1,    1, -3, -1,  1,    1, -1, -3,  1,    1, -1, -1,  3,
            -3, -1, -1,  1,   -1, -3, -1,  1,   -1, -1, -3,  1,   -1, -1, -1,  3,
             3,  1,  1, -1,    1,  3,  1, -1,    1,  1,  3, -1,    1,  1,  1, -3,
            -3,  1,  1, -1,   -1,  3,  1, -1,   -1,  1,  3, -1,   -1,  1,  1, -3,
             3, -1,  1, -1,    1, -3,  1, -1,    1, -1,  3, -1,    1, -1,  1, -3,
            -3, -1,  1, -1,   -1, -3,  1, -1,   -1, -1,  3, -1,   -1, -1,  1, -3,
             3,  1, -1, -1,    1,  3, -1, -1,    1,  1, -3, -1,    1,  1, -1, -3,
            -3,  1, -1, -1,   -1,  3, -1, -1,   -1,  1, -3, -1,   -1,  1, -1, -3,
             3, -1, -1, -1,    1, -3, -1, -1,    1, -1, -3, -1,    1, -1, -1, -3,
            -3, -1, -1, -1,   -1, -3, -1, -1,   -1, -1, -3, -1,   -1, -1, -1, -3
        }};

    private:
        PermutationArray perm;
        PermutationArray permGradIndex3D;

    private:
        double extrapolate(int xsb, int ysb, double dx, double dy) const;
        double extrapolate(int xsb, int ysb, int zsb, double dx, double dy, double dz) const;
        double extrapolate(int xsb, int ysb, int zsb, int wsb, double dx, double dy, double dz, double dw) const;
        int fastFloor(double x) const;
    };
}

#endif // FRTS_OPENSIMPLEXNOISE_H
