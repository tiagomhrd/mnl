#include <ranges>
#include <algorithm>
#include "catch_amalgamated.hpp"

#include "mnl.hpp"

using namespace mnl;

const int dim(const int d, const int k) {
	if (k == -1) return 0;
	if (k == 0) return 1;
	return std::ranges::fold_left(std::views::iota((k > d ? k : d) + 1, k + d + 1), 1LL, std::multiplies<int64_t>()) /
		std::ranges::fold_left(std::views::iota(1, (k > d ? d : k) + 1), 1LL, std::multiplies<int64_t>());
}



TEST_CASE("Space Dimensions") {
	SECTION("2D Monomials") {
		constexpr int d = 2;
		for (int k = 0; k < 5; ++k)
			REQUIRE(Poly<d>::SpaceDim(k) == dim(d, k));
	}
	SECTION("3D Monomials") {
		constexpr int d = 3;
		for (int k = 0; k < 5; ++k)
			REQUIRE(Poly<d>::SpaceDim(k) == dim(d, k));
	}
	SECTION("4D Monomials") {
		constexpr int d = 4;
		for (int k = 0; k < 5; ++k)
			REQUIRE(Poly<d>::SpaceDim(k) == dim(d, k));
	}
	SECTION("5D Monomials") {
		constexpr int d = 5;
		for (int k = 0; k < 5; ++k)
			REQUIRE(Poly<d>::SpaceDim(k) == dim(d, k));
	}
	SECTION("6D Monomials") {
		constexpr int d = 6;
		for (int k = 0; k < 5; ++k)
			REQUIRE(Poly<d>::SpaceDim(k) == dim(d, k));
	}
}

TEST_CASE("Monomial Order") {
	SECTION("2D Monomials") {
		constexpr int d = 2;
		for (monOrder k = 0; k < 5; ++k)
			for (monIndex alpha = dim(d, k - 1); alpha < dim(d, k); ++alpha)
				REQUIRE(Poly<d>::MonOrder(alpha) == k);
	}
	SECTION("3D Monomials") {
		constexpr int d = 3;
		for (monOrder k = 0; k < 5; ++k)
			for (monIndex alpha = dim(d, k - 1); alpha < dim(d, k); ++alpha)
				REQUIRE(Poly<d>::MonOrder(alpha) == k);
	}
	SECTION("4D Monomials") {
		constexpr int d = 4;
		for (monOrder k = 0; k < 5; ++k)
			for (monIndex alpha = dim(d, k - 1); alpha < dim(d, k); ++alpha)
				REQUIRE(Poly<d>::MonOrder(alpha) == k);
	}
	SECTION("5D Monomials") {
		constexpr int d = 5;
		for (monOrder k = 0; k < 5; ++k)
			for (monIndex alpha = dim(d, k - 1); alpha < dim(d, k); ++alpha)
				REQUIRE(Poly<d>::MonOrder(alpha) == k);
	}
	SECTION("6D Monomials") {
		constexpr int d = 6;
		for (monOrder k = 0; k < 5; ++k)
			for (monIndex alpha = dim(d, k - 1); alpha < dim(d, k); ++alpha)
				REQUIRE(Poly<d>::MonOrder(alpha) == k);
	}
}

TEST_CASE("Sum of Exponents = Order") {
	

	SECTION("2D Monomials") {
		constexpr int d = 2;
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
		constexpr int d = 3;
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
		constexpr int d = 4;
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
		constexpr int d = 5;
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
		constexpr int d = 6;
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
		constexpr int d = 2;
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
		constexpr int d = 3;
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
		constexpr int d = 4;
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
		constexpr int d = 5;
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
		constexpr int d = 6;
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
		constexpr int d = 2;
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
		constexpr int d = 3;
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
		constexpr int d = 4;
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
		constexpr int d = 5;
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
		constexpr int d = 6;
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
		constexpr int d = 2;
		SECTION("AntiDerivative is product with variable") {
			for (monOrder k = 0; k < 5; ++k)
				for (monIndex alpha = dim(d, k - 1); alpha < dim(d, k); ++alpha)
					for (int x = 0; x < d; ++x)
						REQUIRE(Poly<d>::AD(alpha, x) == Poly<d>::Product(alpha, x + 1));
		}
	}
	SECTION("3D Monomials") {
		constexpr int d = 3;
		SECTION("AntiDerivative is product with variable") {
			for (monOrder k = 0; k < 5; ++k)
				for (monIndex alpha = dim(d, k - 1); alpha < dim(d, k); ++alpha)
					for (int x = 0; x < d; ++x)
						REQUIRE(Poly<d>::AD(alpha, x) == Poly<d>::Product(alpha, x + 1));
		}
	}
	SECTION("4D Monomials") {
		constexpr int d = 4;
		SECTION("AntiDerivative is product with variable") {
			for (monOrder k = 0; k < 5; ++k)
				for (monIndex alpha = dim(d, k - 1); alpha < dim(d, k); ++alpha)
					for (int x = 0; x < d; ++x)
						REQUIRE(Poly<d>::AD(alpha, x) == Poly<d>::Product(alpha, x + 1));
		}
	}
	SECTION("5D Monomials") {
		constexpr int d = 5;
		SECTION("AntiDerivative is product with variable") {
			for (monOrder k = 0; k < 5; ++k)
				for (monIndex alpha = dim(d, k - 1); alpha < dim(d, k); ++alpha)
					for (int x = 0; x < d; ++x)
						REQUIRE(Poly<d>::AD(alpha, x) == Poly<d>::Product(alpha, x + 1));
		}
	}
	SECTION("6D Monomials") {
		constexpr int d = 6;
		SECTION("AntiDerivative is product with variable") {
			for (monOrder k = 0; k < 5; ++k)
				for (monIndex alpha = dim(d, k - 1); alpha < dim(d, k); ++alpha)
					for (int x = 0; x < d; ++x)
						REQUIRE(Poly<d>::AD(alpha, x) == Poly<d>::Product(alpha, x + 1));
		}
	}
}

int main(int argc, char* argv[]) {
	int result = Catch::Session().run(argc, argv);
	return result;
}