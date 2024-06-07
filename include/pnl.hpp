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