/**********************************************************************************************************************************
                                            Monomial's Library by Tiago Fernandes Moherdaui

            The library is meant to make operations with monomials easier by use of indicial notation.
            
            Considering the monomial m_alpha of order k, in d-variables, i.e., belonging to P_k(R^d), the following
            operations are available:

                Dimension of P_k(R^d)                           mnl::Poly<d>::SpaceDim(k);
                Order of m_alpha                                mnl::Poly<d>::MonOrder(alpha);
                Exponent of x_i in m_alpha                      mnl::Poly<d>::Exponent(alpha, i);
                Index of Product                                mnl::Poly<d>::Product(alpha, beta);
                Index of Derivative in x_i                      mnl::Poly<d>::D(alpha, i);
                Index of Antiderivative in x_i                  mnl::Poly<d>::AD(alpha, i);

            All operations are static member functions to class Poly<d>.
            Aliases are available up to d = 10, e.g., Poly<2> = Poly2D.
            So far the limitation is that d+k < 20, but this can be revised with a refactoring of the factorial solution.

            This is produced in C++11 and includes only <array>.

**********************************************************************************************************************************/
#ifndef MNL
#define MNL
#include <array>

namespace mnl {
    /*
        Auxiliar definitions
    */
    using monIndex = int;
    using monOrder = int;

    /*
    *   This solution for factorials can be improved.
    */
    constexpr std::array<int64_t, 21> _factorialTable = { 1,1,2,6,24,120,720,5040,40320,362880,3628800,39916800,479001600,6227020800,87178291200,1307674368000,20922789888000,355687428096000,6402373705728000,121645100408832000,2432902008176640000 };
    constexpr inline int64_t Factorial(const int n) { return _factorialTable[n]; }

    constexpr int _Combination(const int n, const int k) {
        if (k > n) return 0LL;
        if (k == n || k == 0) return 1LL;

        double c = double(n);
        for (int i = 2; i <= (k > (n - k) ? n - k : k); ++i)
            c *= double(n + 1 - i) / double(i);

        return int(c + 0.5);
    }

    template<const int d>
    class Poly {
    public:
        /************************************************************
            Dimension of space P_k(R^d)
        ************************************************************/
        constexpr static int SpaceDim(const monOrder k) {
            //return (k < 0 ? 0 : Factorial(k + d) / (Factorial(k) * Factorial(d)));
            return (k < 0 ? 0 : _Combination(k + d, d));
        }

        /************************************************************
            Returns the order (sum of the exponents) of a given monomial.
        ************************************************************/
        static monOrder MonOrder(const monIndex alpha) {
            // preciso fazer o esquema de ir tirando um de cada vez.
            monOrder k = std::max(0, (int)ceil(pow((double)(Factorial(d) * (alpha + 1)), 1.0 / d) - d));
            while (alpha >= SpaceDim(k)) {
                ++k;
            }
            return k;
        }

        /************************************************************
            Exponent of x_variable of monomial of index alpha.
            variable < d
        ************************************************************/
        constexpr static int Exponent(monIndex alpha, int variable) {
            const monOrder k = MonOrder(alpha);
            const monIndex innerIndex = alpha - (monIndex)SpaceDim(k - 1);
            return (variable == 0 ? (int)(k - Poly<d - 1>::MonOrder(innerIndex)) : Poly<d - 1>::Exponent(innerIndex, variable - 1));
        }

        /************************************************************
            Product of monomials alpha and beta
            m_alpha * m_beta = m_gamma -> Product(alpha, beta) = gamma
        ************************************************************/
        constexpr static monIndex Product(const monIndex alpha, const monIndex beta) {
            if (alpha == -1 || beta == -1)
                return -1;
            const monOrder kalpha = MonOrder(alpha);
            const monOrder kbeta = MonOrder(beta);
            return Poly<d - 1>::Product(alpha - SpaceDim(kalpha - 1), beta - SpaceDim(kbeta - 1)) + SpaceDim(kalpha + kbeta - 1);
        }


        /************************************************************
            Derivative of monomial alpha in the direction of variable
            d/dxi(m_alpha) = C m_beta  -> D(alpha, i) = beta
        ************************************************************/
        constexpr static monIndex D(const monIndex alpha, const int variable) {
            // Kernel for constants
            if (alpha == 0 || alpha == -1)
                return -1;
            const monOrder kalpha = MonOrder(alpha);
            const monIndex innerIndex = alpha - SpaceDim(kalpha - 1);
            const monOrder kInner = Poly<d - 1>::MonOrder(innerIndex);
            // if (kInner == kalpha)
            //     return -1;
            if (variable == 0) {
                if (innerIndex >= Poly<d - 1>::SpaceDim(kalpha - 1))
                    return -1;
                else
                    return innerIndex + SpaceDim(kalpha - 2);
            }

            const monIndex dInner = Poly<d - 1>::D(innerIndex, variable - 1);
            if (dInner == -1)
                return dInner;
            return dInner + SpaceDim(kalpha - 2);
        }

        /************************************************************
            Antiderivative of monomial alpha in the direction of variable
            d/dxi(m_beta) = C m_alpha  -> AD(alpha, i) = beta
        ************************************************************/
        constexpr static monIndex AD(const monIndex alpha, const int variable) {
            if (alpha == -1)
                return 0;
            const monOrder kalpha = MonOrder(alpha);
            return (variable == 0 ? alpha + Poly<d - 1>::SpaceDim(kalpha) : Poly<d - 1>::AD(alpha - SpaceDim(kalpha - 1), variable - 1) + SpaceDim(kalpha));
        }
    };
    template<>
    class Poly<1> {
    public:
        constexpr static int        SpaceDim(const monOrder k) { return (int)k + 1; }
        constexpr static monOrder   MonOrder(const monIndex alpha) { return (monOrder)alpha; }
        constexpr static int        Exponent(const monIndex alpha, const int variable) { return alpha; }
        constexpr static monIndex   Product(const monIndex alpha, const monIndex beta) { return alpha + beta; }
        constexpr static monIndex   D(const monIndex alpha, const int variable) { return alpha - (monIndex)1; }
        constexpr static monIndex   AD(const monIndex alpha, const int variable) { return alpha + 1; }
    };

    #define ALIASPSpace(d) using PSpace ##d ##D = Poly<d>
    ALIASPSpace(1);
    ALIASPSpace(2);
    ALIASPSpace(3);
    ALIASPSpace(4);
    ALIASPSpace(5);
    ALIASPSpace(6);
    ALIASPSpace(7);
    ALIASPSpace(8);
    ALIASPSpace(9);
    ALIASPSpace(10);
    #undef ALIASPSpace
}
#endif