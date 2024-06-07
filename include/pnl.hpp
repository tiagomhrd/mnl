/**********************************************************************************************************************************
                                            Monomial's Library by Tiago Fernandes Moherdaui

            The library is meant to make operations with monomials easier by use of indicial notation.

            This file provides a class representing polynomials in d-dimensions.
            Each polynomial stores a set of pairs of monomial indices and scalar.
            The following operations are available for polynomials mnl::Polynomial<d> p1, p2, p3:

                Order of polynomial                             p1.Order();
                Addition                                        p3 = p1 + p2; p1 += p2;
                Multiplication                                  p3 = p1*p2; p1 *= p2;
            
            Terms in the monomial are stored in an unordered map with a monIndex as key and double as value.
            The map is directly exposed as: p.Terms;
            Typical procedures can be used to loop through the terms:

            C++11
            for (const auto& it : p.Terms) {
                monIndex    index = it.first;
                double      scalar = it.second;
                // Do work...
            }

            C++17
            for (const auto& [index, scalar] : p.Terms) {
                // Do work...
            }

            Aliases are available for the Polynomial<d> struct as pnldD up to d = 10, e.g., Polynomial<2> = pnl2D.

            This is produced in C++11 and includes only <array> and <unordered_map>.

**********************************************************************************************************************************/

#ifndef PNL
#define PNL
#include "mnl.hpp"
#include <unordered_map>

namespace mnl {
    template <int d>
    struct Polynomial {
        std::unordered_map<monIndex, double> Terms;

        monOrder Order() const {
            monIndex maxIndex = -1;
            for (const auto& it : Terms) {
                if (it.first > maxIndex)
                    maxIndex = it.first;
            }
            return Poly<d>::MonOrder(maxIndex);
        }

        Polynomial<d>& operator*=(const Polynomial<d>& p) {
            Polynomial<d> aux;
            for (const auto& it1 : Terms)
                for (const auto& it2 : p.Terms)
                    aux.Terms[Poly<d>::Product(it1.first, it2.first)] += it1.second * it2.second;
            Terms = aux.Terms;
            CheckZeroes();
            return *this;
        }
        Polynomial<d>& operator+=(const Polynomial<d>& p) {
            for (const auto& it : p.Terms)
                Terms[it.first] += it.second;
            CheckZeroes();
            return *this;
        }
        void CheckZeroes() {
            for (auto it = Terms.begin(); it != Terms.end();)
            {
                if (abs(it->second) < 1e-10)
                    it = Terms.erase(it);
                else
                    ++it;
            }
        }
    };

    template<int d>
    Polynomial<d> operator*(const Polynomial<d>& p1, const Polynomial<d>& p2) {
        Polynomial<d> result;
        for (const auto& it1 : p1.Terms)
            for (const auto& it2 : p2.Terms)
                result.Terms[Poly<d>::Product(it1.first, it2.first)] += it1.second * it2.second;
        result.CheckZeroes();
        return result;
    }

#define ALIASpnl(d) using pnl ##d ##D = Polynomial<d>
    ALIASpnl(1);
    ALIASpnl(2);
    ALIASpnl(3);
    ALIASpnl(4);
    ALIASpnl(5);
    ALIASpnl(6);
    ALIASpnl(7);
    ALIASpnl(8);
    ALIASpnl(9);
    ALIASpnl(10);
#undef ALIASpnl

}
#endif