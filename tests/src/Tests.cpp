#include <ranges>
#include <algorithm>
#include "catch_amalgamated.hpp"

#include "mnl.hpp"
#include "pnl.hpp"

using namespace mnl;

const int dim(const int d, const int k) {
	if (k == -1) return 0;
	if (k == 0) return 1;
	return std::ranges::fold_left(std::views::iota((k > d ? k : d) + 1, k + d + 1), 1LL, std::multiplies<int64_t>()) /
		std::ranges::fold_left(std::views::iota(1, (k > d ? d : k) + 1), 1LL, std::multiplies<int64_t>());
}

TEST_CASE("Space Dimensions") {
	SECTION("2D Monomials") {
		const int d = 2;
		for (int k = 0; k < 5; ++k)
			REQUIRE(Poly<d>::SpaceDim(k) == dim(d, k));
	}
	SECTION("3D Monomials") {
		const int d = 3;
		for (int k = 0; k < 5; ++k)
			REQUIRE(Poly<d>::SpaceDim(k) == dim(d, k));
	}
	SECTION("4D Monomials") {
		const int d = 4;
		for (int k = 0; k < 5; ++k)
			REQUIRE(Poly<d>::SpaceDim(k) == dim(d, k));
	}
	SECTION("5D Monomials") {
		const int d = 5;
		for (int k = 0; k < 5; ++k)
			REQUIRE(Poly<d>::SpaceDim(k) == dim(d, k));
	}
	SECTION("6D Monomials") {
		const int d = 6;
		for (int k = 0; k < 5; ++k)
			REQUIRE(Poly<d>::SpaceDim(k) == dim(d, k));
	}
}

TEST_CASE("Monomial Order") {
	SECTION("2D Monomials") {
		const int d = 2;
		for (monOrder k = 0; k < 5; ++k)
			for (monIndex alpha = dim(d, k - 1); alpha < dim(d, k); ++alpha)
				REQUIRE(Poly<d>::MonOrder(alpha) == k);
	}
	SECTION("3D Monomials") {
		const int d = 3;
		for (monOrder k = 0; k < 5; ++k)
			for (monIndex alpha = dim(d, k - 1); alpha < dim(d, k); ++alpha)
				REQUIRE(Poly<d>::MonOrder(alpha) == k);
	}
	SECTION("4D Monomials") {
		const int d = 4;
		for (monOrder k = 0; k < 5; ++k)
			for (monIndex alpha = dim(d, k - 1); alpha < dim(d, k); ++alpha)
				REQUIRE(Poly<d>::MonOrder(alpha) == k);
	}
	SECTION("5D Monomials") {
		const int d = 5;
		for (monOrder k = 0; k < 5; ++k)
			for (monIndex alpha = dim(d, k - 1); alpha < dim(d, k); ++alpha)
				REQUIRE(Poly<d>::MonOrder(alpha) == k);
	}
	SECTION("6D Monomials") {
		const int d = 6;
		for (monOrder k = 0; k < 5; ++k)
			for (monIndex alpha = dim(d, k - 1); alpha < dim(d, k); ++alpha)
				REQUIRE(Poly<d>::MonOrder(alpha) == k);
	}
}

TEST_CASE("Sum of Exponents = Order") {
	
	SECTION("2D Monomials") {
		const int d = 2;
		for (monOrder k = 0; k < 5; ++k) {
			for (monIndex alpha = dim(d, k - 1); alpha < dim(d, k); ++alpha) {
				int expSum = 0;
				for (int x = 0; x < d; ++x)
					expSum += Poly<d>::Exponent(alpha, x);
				REQUIRE(expSum == k);
			}
		}
	}
	SECTION("3D Monomials") {
		const int d = 3;
		for (monOrder k = 0; k < 5; ++k) {
			for (monIndex alpha = dim(d, k - 1); alpha < dim(d, k); ++alpha) {
				int expSum = 0;
				for (int x = 0; x < d; ++x)
					expSum += Poly<d>::Exponent(alpha, x);
				REQUIRE(expSum == k);
			}
		}
	}
	SECTION("4D Monomials") {
		const int d = 4;
		for (monOrder k = 0; k < 5; ++k) {
			for (monIndex alpha = dim(d, k - 1); alpha < dim(d, k); ++alpha) {
				int expSum = 0;
				for (int x = 0; x < d; ++x)
					expSum += Poly<d>::Exponent(alpha, x);
				REQUIRE(expSum == k);
			}
		}
	}
	SECTION("5D Monomials") {
		const int d = 5;
		for (monOrder k = 0; k < 5; ++k) {
			for (monIndex alpha = dim(d, k - 1); alpha < dim(d, k); ++alpha) {
				int expSum = 0;
				for (int x = 0; x < d; ++x)
					expSum += Poly<d>::Exponent(alpha, x);
				REQUIRE(expSum == k);
			}
		}
	}
	SECTION("6D Monomials") {
		const int d = 6;
		for (monOrder k = 0; k < 5; ++k) {
			for (monIndex alpha = dim(d, k - 1); alpha < dim(d, k); ++alpha) {
				int expSum = 0;
				for (int x = 0; x < d; ++x)
					expSum += Poly<d>::Exponent(alpha, x);
				REQUIRE(expSum == k);
			}
		}
	}
}

TEST_CASE("Product") {
	SECTION("2D Monomials") {
		const int d = 2;
		SECTION("Product with Zero") {
			for (monOrder k = 0; k < 5; ++k) {
				for (monIndex alpha = dim(d, k - 1); alpha < dim(d, k); ++alpha) {
					REQUIRE(Poly<d>::Product(-1, alpha) == -1);
					REQUIRE(Poly<d>::Product(alpha, -1) == -1);
				}
			}
		}
		SECTION("Product with 1") {
			for (monOrder k = 0; k < 5; ++k) {
				for (monIndex alpha = dim(d, k - 1); alpha < dim(d, k); ++alpha) {
					REQUIRE(Poly<d>::Product(0, alpha) == alpha);
					REQUIRE(Poly<d>::Product(alpha, 0) == alpha);
				}
			}
		}
		SECTION("Recover monomial from products of variables") {
			for (monOrder k = 0; k < 5; ++k) {
				for (monIndex alpha = dim(d, k - 1); alpha < dim(d, k); ++alpha) {
					monIndex Product = 0;
					for (int x = 0; x < d; ++x)
						for (int exp = 1; exp <= Poly<d>::Exponent(alpha, x); ++exp)
							Product = Poly<d>::Product(Product, x + 1);
					REQUIRE(Product == alpha);
				}
			}
		}
	}
	SECTION("3D Monomials") {
		const int d = 3;
		SECTION("Product with Zero") {
			for (monOrder k = 0; k < 5; ++k) {
				for (monIndex alpha = dim(d, k - 1); alpha < dim(d, k); ++alpha) {
					REQUIRE(Poly<d>::Product(-1, alpha) == -1);
					REQUIRE(Poly<d>::Product(alpha, -1) == -1);
				}
			}
		}
		SECTION("Product with 1") {
			for (monOrder k = 0; k < 5; ++k) {
				for (monIndex alpha = dim(d, k - 1); alpha < dim(d, k); ++alpha) {
					REQUIRE(Poly<d>::Product(0, alpha) == alpha);
					REQUIRE(Poly<d>::Product(alpha, 0) == alpha);
				}
			}
		}
		SECTION("Recover monomial from products of variables") {
			for (monOrder k = 0; k < 5; ++k) {
				for (monIndex alpha = dim(d, k - 1); alpha < dim(d, k); ++alpha) {
					monIndex Product = 0;
					for (int x = 0; x < d; ++x)
						for (int exp = 1; exp <= Poly<d>::Exponent(alpha, x); ++exp)
							Product = Poly<d>::Product(Product, x + 1);
					REQUIRE(Product == alpha);
				}
			}
		}
	}
	SECTION("4D Monomials") {
		const int d = 4;
		SECTION("Product with Zero") {
			for (monOrder k = 0; k < 5; ++k) {
				for (monIndex alpha = dim(d, k - 1); alpha < dim(d, k); ++alpha) {
					REQUIRE(Poly<d>::Product(-1, alpha) == -1);
					REQUIRE(Poly<d>::Product(alpha, -1) == -1);
				}
			}
		}
		SECTION("Product with 1") {
			for (monOrder k = 0; k < 5; ++k) {
				for (monIndex alpha = dim(d, k - 1); alpha < dim(d, k); ++alpha) {
					REQUIRE(Poly<d>::Product(0, alpha) == alpha);
					REQUIRE(Poly<d>::Product(alpha, 0) == alpha);
				}
			}
		}
		SECTION("Recover monomial from products of variables") {
			for (monOrder k = 0; k < 5; ++k) {
				for (monIndex alpha = dim(d, k - 1); alpha < dim(d, k); ++alpha) {
					monIndex Product = 0;
					for (int x = 0; x < d; ++x)
						for (int exp = 1; exp <= Poly<d>::Exponent(alpha, x); ++exp)
							Product = Poly<d>::Product(Product, x + 1);
					REQUIRE(Product == alpha);
				}
			}
		}
	}
	SECTION("5D Monomials") {
		const int d = 5;
		SECTION("Product with Zero") {
			for (monOrder k = 0; k < 5; ++k) {
				for (monIndex alpha = dim(d, k - 1); alpha < dim(d, k); ++alpha) {
					REQUIRE(Poly<d>::Product(-1, alpha) == -1);
					REQUIRE(Poly<d>::Product(alpha, -1) == -1);
				}
			}
		}
		SECTION("Product with 1") {
			for (monOrder k = 0; k < 5; ++k) {
				for (monIndex alpha = dim(d, k - 1); alpha < dim(d, k); ++alpha) {
					REQUIRE(Poly<d>::Product(0, alpha) == alpha);
					REQUIRE(Poly<d>::Product(alpha, 0) == alpha);
				}
			}
		}
		SECTION("Recover monomial from products of variables") {
			for (monOrder k = 0; k < 5; ++k) {
				for (monIndex alpha = dim(d, k - 1); alpha < dim(d, k); ++alpha) {
					monIndex Product = 0;
					for (int x = 0; x < d; ++x)
						for (int exp = 1; exp <= Poly<d>::Exponent(alpha, x); ++exp)
							Product = Poly<d>::Product(Product, x + 1);
					REQUIRE(Product == alpha);
				}
			}
		}
	}
	SECTION("6D Monomials") {
		const int d = 6;
		SECTION("Product with Zero") {
			for (monOrder k = 0; k < 5; ++k) {
				for (monIndex alpha = dim(d, k - 1); alpha < dim(d, k); ++alpha) {
					REQUIRE(Poly<d>::Product(-1, alpha) == -1);
					REQUIRE(Poly<d>::Product(alpha, -1) == -1);
				}
			}
		}
		SECTION("Product with 1") {
			for (monOrder k = 0; k < 5; ++k) {
				for (monIndex alpha = dim(d, k - 1); alpha < dim(d, k); ++alpha) {
					REQUIRE(Poly<d>::Product(0, alpha) == alpha);
					REQUIRE(Poly<d>::Product(alpha, 0) == alpha);
				}
			}
		}
		SECTION("Recover monomial from products of variables") {
			for (monOrder k = 0; k < 5; ++k) {
				for (monIndex alpha = dim(d, k - 1); alpha < dim(d, k); ++alpha) {
					monIndex Product = 0;
					for (int x = 0; x < d; ++x)
						for (int exp = 1; exp <= Poly<d>::Exponent(alpha, x); ++exp)
							Product = Poly<d>::Product(Product, x + 1);
					REQUIRE(Product == alpha);
				}
			}
		}
	}
}

TEST_CASE("Derivatives and AntiDerivatives") {
	SECTION("2D Monomials") {
		const int d = 2;
		SECTION("Derivative of AntiDerivative recovers monomial") {
			for (monOrder k = 0; k < 5; ++k) {
				for (monIndex alpha = dim(d, k - 1); alpha < dim(d, k); ++alpha) {
					for (int x = 0; x < d; ++x) {
						REQUIRE(Poly<d>::D(Poly<d>::AD(alpha, x), x) == alpha);
					}
				}
			}
		}
	}
	SECTION("3D Monomials") {
		const int d = 3;
		SECTION("Derivative of AntiDerivative recovers monomial") {
			for (monOrder k = 0; k < 5; ++k) {
				for (monIndex alpha = dim(d, k - 1); alpha < dim(d, k); ++alpha) {
					for (int x = 0; x < d; ++x) {
						REQUIRE(Poly<d>::D(Poly<d>::AD(alpha, x), x) == alpha);
					}
				}
			}
		}
	}
	SECTION("4D Monomials") {
		const int d = 4;
		SECTION("Derivative of AntiDerivative recovers monomial") {
			for (monOrder k = 0; k < 5; ++k) {
				for (monIndex alpha = dim(d, k - 1); alpha < dim(d, k); ++alpha) {
					for (int x = 0; x < d; ++x) {
						REQUIRE(Poly<d>::D(Poly<d>::AD(alpha, x), x) == alpha);
					}
				}
			}
		}
	}
	SECTION("5D Monomials") {
		const int d = 5;
		SECTION("Derivative of AntiDerivative recovers monomial") {
			for (monOrder k = 0; k < 5; ++k) {
				for (monIndex alpha = dim(d, k - 1); alpha < dim(d, k); ++alpha) {
					for (int x = 0; x < d; ++x) {
						REQUIRE(Poly<d>::D(Poly<d>::AD(alpha, x), x) == alpha);
					}
				}
			}
		}
	}
	SECTION("6D Monomials") {
		const int d = 6;
		SECTION("Derivative of AntiDerivative recovers monomial") {
			for (monOrder k = 0; k < 5; ++k) {
				for (monIndex alpha = dim(d, k - 1); alpha < dim(d, k); ++alpha) {
					for (int x = 0; x < d; ++x) {
						REQUIRE(Poly<d>::D(Poly<d>::AD(alpha, x), x) == alpha);
					}
				}
			}
		}
	}
}

TEST_CASE("Product and AntiDerivatives") {

	SECTION("2D Monomials") {
		const int d = 2;
		SECTION("AntiDerivative is product with variable") {
			for (monOrder k = 0; k < 5; ++k)
				for (monIndex alpha = dim(d, k - 1); alpha < dim(d, k); ++alpha)
					for (int x = 0; x < d; ++x)
						REQUIRE(Poly<d>::AD(alpha, x) == Poly<d>::Product(alpha, x + 1));
		}
	}
	SECTION("3D Monomials") {
		const int d = 3;
		SECTION("AntiDerivative is product with variable") {
			for (monOrder k = 0; k < 5; ++k)
				for (monIndex alpha = dim(d, k - 1); alpha < dim(d, k); ++alpha)
					for (int x = 0; x < d; ++x)
						REQUIRE(Poly<d>::AD(alpha, x) == Poly<d>::Product(alpha, x + 1));
		}
	}
	SECTION("4D Monomials") {
		const int d = 4;
		SECTION("AntiDerivative is product with variable") {
			for (monOrder k = 0; k < 5; ++k)
				for (monIndex alpha = dim(d, k - 1); alpha < dim(d, k); ++alpha)
					for (int x = 0; x < d; ++x)
						REQUIRE(Poly<d>::AD(alpha, x) == Poly<d>::Product(alpha, x + 1));
		}
	}
	SECTION("5D Monomials") {
		const int d = 5;
		SECTION("AntiDerivative is product with variable") {
			for (monOrder k = 0; k < 5; ++k)
				for (monIndex alpha = dim(d, k - 1); alpha < dim(d, k); ++alpha)
					for (int x = 0; x < d; ++x)
						REQUIRE(Poly<d>::AD(alpha, x) == Poly<d>::Product(alpha, x + 1));
		}
	}
	SECTION("6D Monomials") {
		const int d = 6;
		SECTION("AntiDerivative is product with variable") {
			for (monOrder k = 0; k < 5; ++k)
				for (monIndex alpha = dim(d, k - 1); alpha < dim(d, k); ++alpha)
					for (int x = 0; x < d; ++x)
						REQUIRE(Poly<d>::AD(alpha, x) == Poly<d>::Product(alpha, x + 1));
		}
	}
}

TEST_CASE("README Tests") {
	SECTION("mnl.hpp"){
		// Space Dimension
		REQUIRE(mnl::PSpace2D::SpaceDim(0) == 1);  // {1}
		REQUIRE(mnl::PSpace2D::SpaceDim(1) == 3);  // {1, x, y}
		REQUIRE(mnl::PSpace2D::SpaceDim(2) == 6);  // {1, x, y, x^2, xy, y^2}
		REQUIRE(mnl::PSpace2D::SpaceDim(3) == 10); // {1, x, y, x^2, xy, y^2, x^3, x^2y, xy^2, y^3}

		// Monomial Order
		REQUIRE(mnl::PSpace2D::MonOrder(0) == 0);  // m_0 = 1
		REQUIRE(mnl::PSpace2D::MonOrder(1) == 1);  // m_1 = x
		REQUIRE(mnl::PSpace2D::MonOrder(5) == 2);  // m_5 = y^2
		REQUIRE(mnl::PSpace2D::MonOrder(7) == 3);  // m_7 = x^2y

		// Exponents
		// x is direction 0, y is direction 1
		// m_0 = 1 = x^0 * y^0
		REQUIRE(mnl::PSpace2D::Exponent(0, 0) == 0);
		REQUIRE(mnl::PSpace2D::Exponent(0, 1) == 0);
		// m_1 = x = x^1 * y^0
		REQUIRE(mnl::PSpace2D::Exponent(1, 0) == 1);
		REQUIRE(mnl::PSpace2D::Exponent(1, 1) == 0);
		// m_7 = x^2y = x^2 * y^1
		REQUIRE(mnl::PSpace2D::Exponent(7, 0) == 2);
		REQUIRE(mnl::PSpace2D::Exponent(7, 1) == 1);

		// Product
		// m_5 * m_7 = y^2 * x^2y = x^2y^3 = m_18
		REQUIRE(mnl::PSpace2D::Product(5, 7) == 18);

		// Derivative
		// m_0 = 1 = x^0 * y^0
		REQUIRE(mnl::PSpace2D::D(0, 0) == -1); // d/dx(1) = 0 = m_-1
		REQUIRE(mnl::PSpace2D::D(0, 1) == -1); // d/dy(1) = 0 = m_-1

		// m_1 = x = x^1 * y^0
		REQUIRE(mnl::PSpace2D::D(1, 0) == 0);  // d/dx(x) = 1 = m_0
		REQUIRE(mnl::PSpace2D::D(1, 1) == -1); // d/dy(x) = 0 = m_-1

		// m_7 = x^2y = x^2 * y^1
		REQUIRE(mnl::PSpace2D::D(7, 0) == 4);  // d/dx(x^2y) ~ xy = m_4
		REQUIRE(mnl::PSpace2D::D(7, 1) == 3);  // d/dy(x^2y) ~ x^2 = m_3

		// Antiderivative
		// m_0 = 1 = x^0 * y^0
		REQUIRE(mnl::PSpace2D::AD(0, 0) == 1); // ADx(1) = x = m_1
		REQUIRE(mnl::PSpace2D::AD(0, 1) == 2); // ADy(1) = y = m_2

		// m_1 = x = x^1 * y^0
		REQUIRE(mnl::PSpace2D::AD(1, 0) == 3);  // ADx(x) ~ x^2 = m_3
		REQUIRE(mnl::PSpace2D::AD(1, 1) == 4);  // ADy(x) ~ xy  = m_4

		// m_7 = x^2y = x^2 * y^1
		REQUIRE(mnl::PSpace2D::AD(7, 0) == 11);  // ADx(x^2y) ~ x^3y   = m_11
		REQUIRE(mnl::PSpace2D::AD(7, 1) == 12);  // ADy(x^2y) ~ x^2y^2 = m_12
	}
	SECTION("pnl.hpp"){
		mnl::pnl2D p, q;
		// p is x^2 + y^2
		p.Terms[3] = 1.0;
		p.Terms[5] = 1.0;
		// q is 2 * x^3 + 3 * y^3
		q.Terms[6] = 2.0;
		q.Terms[9] = 3.0;

		mnl::pnl2D prod = p * q;
		// prod = 2 * x^5 + 3 * x^2y^3 + 2 * x^3y^2 + 3 * y^5
		REQUIRE(prod.Terms[15] == 2.0); // 2 * x^5     = 2 * m_15
		REQUIRE(prod.Terms[18] == 3.0); // 3 * x^2y^3  = 3 * m_18
		REQUIRE(prod.Terms[17] == 2.0); // 2 * x^3y^2  = 2 * m_17
		REQUIRE(prod.Terms[20] == 3.0); // 3 * y^5     = 3 * m_20

		// p^2 = x^4 + 2 * x^2y^2 + y^4
		p *= p;
		REQUIRE(p.Terms[10] == 1.0); // 1 * x^4     = 1 * m_10
		REQUIRE(p.Terms[12] == 2.0); // 2 * x^2y^2  = 2 * m_12
		REQUIRE(p.Terms[14] == 1.0); // 1 * y^4     = 1 * m_14

		// p^2 + q = x^4 + 2 * x^2y^2 + y^4 + 2 * x^3 + 3 * y^3
		p += q;
		REQUIRE(p.Terms[10] == 1.0); // 1 * x^4     = 1 * m_10
		REQUIRE(p.Terms[12] == 2.0); // 2 * x^2y^2  = 2 * m_12
		REQUIRE(p.Terms[14] == 1.0); // 1 * y^4     = 1 * m_14
		REQUIRE(p.Terms[6]  == 2.0); // 2 * x^3     = 2 * m_6
		REQUIRE(p.Terms[9]  == 3.0); // 3 * y^3     = 3 * m_9
	}
}

TEST_CASE("2D Polynomials") {
	const int d = 2;
	SECTION("(x+y)^2") {
		pnl2D p1;
		p1.Terms[1] = 1.;
		p1.Terms[2] = 1.;
		p1 *= p1;
		REQUIRE(p1.Terms[3] == 1.0);
		REQUIRE(p1.Terms[4] == 2.0);
		REQUIRE(p1.Terms[5] == 1.0);
		REQUIRE(p1.Terms.size() == 3);
		REQUIRE(p1.Order() == 2);
	}
	SECTION("(x+y)^3") {
		pnl2D p1, res;
		p1.Terms[1] = 1.;
		p1.Terms[2] = 1.;
		res = p1 * p1 * p1;
		
		REQUIRE(res.Terms[6] == 1.0);
		REQUIRE(res.Terms[7] == 3.0);
		REQUIRE(res.Terms[8] == 3.0);
		REQUIRE(res.Terms[9] == 1.0);
		REQUIRE(res.Terms.size() == 4);
		REQUIRE(res.Order() == 3);
	}
	SECTION("(x+1)^2") {
		pnl2D p1;
		p1.Terms[1] = 1.;
		p1.Terms[0] = 1.;
		p1 *= p1;
		REQUIRE(p1.Terms[3] == 1.0);
		REQUIRE(p1.Terms[1] == 2.0);
		REQUIRE(p1.Terms[0] == 1.0);
		REQUIRE(p1.Terms.size() == 3);
		REQUIRE(p1.Order() == 2);
	}
	SECTION("(x+1)(x-1)") {
		pnl2D p1, p2;
		p1.Terms[1] = 1.;
		p1.Terms[0] = 1.;
		p2.Terms[1] = 1.;
		p2.Terms[0] = -1.;
		p1 *= p2;
		REQUIRE(p1.Terms[3] == 1.0);
		REQUIRE(p1.Terms[0] == -1.0);
		REQUIRE(p1.Terms.size() == 2);
		REQUIRE(p1.Order() == 2);
	}
}

TEST_CASE("3D Polynomials") {
	const int d = 3;
	SECTION("(x+y)^2") {
		pnl3D p1;
		p1.Terms[1] = 1.;
		p1.Terms[2] = 1.;
		p1 *= p1;
		REQUIRE(p1.Terms[4] == 1.0);
		REQUIRE(p1.Terms[5] == 2.0);
		REQUIRE(p1.Terms[7] == 1.0);
		REQUIRE(p1.Terms.size() == 3);
		REQUIRE(p1.Order() == 2);
	}
	SECTION("(x+y+z)^2") {
		pnl3D p1;
		p1.Terms[1] = 1.;
		p1.Terms[2] = 1.;
		p1.Terms[3] = 1.;
		p1 *= p1;
		REQUIRE(p1.Terms[4] == 1.0);
		REQUIRE(p1.Terms[7] == 1.0);
		REQUIRE(p1.Terms[9] == 1.0);
		REQUIRE(p1.Terms[5] == 2.0);
		REQUIRE(p1.Terms[6] == 2.0);
		REQUIRE(p1.Terms[8] == 2.0);
		REQUIRE(p1.Terms.size() == 6);
		REQUIRE(p1.Order() == 2);
	}
	SECTION("(x+y+z)^3") {
		pnl3D p1, res;
		p1.Terms[1] = 1.;
		p1.Terms[2] = 1.;
		p1.Terms[3] = 1.;
		res = p1 * p1 * p1;

		REQUIRE(res.Terms[10] == 1.0);
		REQUIRE(res.Terms[16] == 1.0);
		REQUIRE(res.Terms[19] == 1.0);
		REQUIRE(res.Terms[11] == 3.0);
		REQUIRE(res.Terms[12] == 3.0);
		REQUIRE(res.Terms[13] == 3.0);
		REQUIRE(res.Terms[14] == 6.0);
		REQUIRE(res.Terms[15] == 3.0);
		REQUIRE(res.Terms[17] == 3.0);
		REQUIRE(res.Terms[18] == 3.0);
		REQUIRE(res.Terms.size() == 10);
		REQUIRE(res.Order() == 3);
	}
}

int main(int argc, char* argv[]) {
	int result = Catch::Session().run(argc, argv);
	return result;
}