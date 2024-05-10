#include <sstream>
#include <string>
#include "Monomials.hpp"

namespace mnl {
    template<int d>
    const std::string PrintMonomial(const mnl::monIndex alpha) {
        if (alpha < 0)
            return "0";
        if (alpha == 0)
            return "1";
        std::string result{};
        for (int variable = 0; variable < d; ++variable) {
            int exp = mnl::Poly<d>::Exponent(alpha, variable);
            if (exp < 1)
                continue;
            result += "x" + std::to_string(variable);
            if (exp > 1)
                result += "^" + std::to_string(exp);
        }
        return result;
    }
    template<>
    const std::string PrintMonomial<1>(const mnl::monIndex alpha) {
        return alpha == 0 ? "1" : "x^" + std::to_string(alpha);
    }
    template<>
    const std::string PrintMonomial<2>(const mnl::monIndex alpha) {
        if (alpha < 0)
            return "0";
        if (alpha == 0)
            return "1";
        std::string result;
        int expX = mnl::Poly2D::Exponent(alpha, 0);
        if (expX != 0)
            result = "x^" + std::to_string(expX);
        int expY = mnl::Poly2D::Exponent(alpha, 1);
        if (expY != 0)
            result += "y^" + std::to_string(expY);
        return result;
    }
    template<>
    const std::string PrintMonomial<3>(const mnl::monIndex alpha) {
        if (alpha < (mnl::monIndex)0)
            return "0";
        if (alpha == (mnl::monIndex)0)
            return "1";
        std::string result;
        int expX = mnl::Poly3D::Exponent(alpha, 0);
        if (expX != 0)
            result = "x^" + std::to_string(expX);
        int expY = mnl::Poly3D::Exponent(alpha, 1);
        if (expY != 0)
            result += "y^" + std::to_string(expY);
        int expZ = mnl::Poly3D::Exponent(alpha, 2);
        if (expZ != 0)
            result += "z^" + std::to_string(expZ);
        return result;
    }

    template<>
    const std::string PrintMonomial<4>(const mnl::monIndex alpha) {
        if (alpha < (mnl::monIndex)0)
            return "0";
        if (alpha == (mnl::monIndex)0)
            return "1";
        std::string result;
        int expX = mnl::Poly<4>::Exponent(alpha, 0);
        if (expX != 0)
            result = "x^" + std::to_string(expX);
        int expY = mnl::Poly<4>::Exponent(alpha, 1);
        if (expY != 0)
            result += "y^" + std::to_string(expY);
        int expZ = mnl::Poly<4>::Exponent(alpha, 2);
        if (expZ != 0)
            result += "z^" + std::to_string(expZ);
        int expW = mnl::Poly<4>::Exponent(alpha, 3);
        if (expW != 0)
            result += "w^" + std::to_string(expW);
        return result;
    }

    template <int d>
    const std::string ListingTest(const int kMax) {
        std::stringstream ss;
        ss << "---------------------------------------------------\n";
        ss << "\t" << d << "D monomials up to order " << kMax << "\n";
        ss << "---------------------------------------------------\n";
        for (mnl::monOrder k = 0; k < kMax; ++k) {
            for (mnl::monIndex alpha = mnl::Poly<d>::SpaceDim(k - 1); alpha < mnl::Poly<d>::SpaceDim(k); ++alpha) {
                ss << "m" << alpha << "=\t" << PrintMonomial<d>(alpha) << "\t";
                for (int i = 0; i < d; ++i)
                    ss << "D_{x_" << i << "}=\t" << PrintMonomial<d>(mnl::Poly<d>::D(alpha, i)) << "\tAD_{x_" << i << "}=\t" << PrintMonomial<d>(mnl::Poly<d>::AD(alpha, i)) << "\t";
                ss << "\n";
            }
        }
        return ss.str();
    }
}