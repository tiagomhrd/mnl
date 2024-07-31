# MNL (monomial)

MNL (monomial) is an index-based approach to represent monomials of arbitrary order $k$, over an arbitrary number of variables $d$:

$m_\alpha \in P_k(\mathbb{R}^d)$

This project consists in a lightweight framework for the representation of canonical basis monomials.

## Table of Contents

1. [Motivation](#motivation)
2. [Organization and Features](#organization-and-features)
3. [Installation Instruction](#installation-instructions)
4. [Usage and Examples](#usage-and-examples)

## Motivation

The motivation came from implementing the Virtual Element Method (VEM), more specifically from the notation briefly introduced in the [Hitchhiker's Guide to the Virtual Element Method (HHGTVEM)](http://arturo.imati.cnr.it/brezzi/papers/hitchhikers-preprint.pdf) for the 2D case.

Although the notation was used only to enumerate the monomials, it is here extended in a way one can find other useful information for the computation of the method while using only integers, such as the order of a given monomial, its derivatives and anti-derivatives, the monomial resulting from product of monomials, etc.

This approach has also been extended to arbitrary number of variabels, mostly because it was possible, although no use is proposed for them so far.

## Organization and Features

The project is organized into three files: `mnl.hpp`, `pnl.hpp` and `glq.hpp`.
These files can be found in the `include` directory.

The focus of this project is on treating monomials individually and sequentially, as this is how the matrices for the VEM projections are usually computed.
This is the core usage of the project, which is contained in the file `mnl.hpp`.
It allows certain information to be extracted based on these indices, e.g., for the monomial of index $\alpha$ ($m_\alpha$):
- Dimension of the polynomial space of given order;
- Order of the monomial;
- Exponent for each variable;
- Index for monomial resulting from the product of two other monomials;
- Index of the monomial which is the derivative of $m_\alpha$ with respect to one of the variables;
- Index of the monomial which is the antiderivative of $m_\alpha$ with respect to one of the variables.

There are some cases in which polynomials have to be employed.
For this, a simple framework for sparse polynomial representation based on these indices and hash tables (`std::unordered_map`) has been implemented in `pnl.hpp`.
This is not the best approach for more polynomial-heavy approaches, and I would suggest looking up other frameworks if this is the case for you.
Features for this framework include:
- Defining polynomials as collections of pairs of scalar and monomial index;
- Multiplying and adding polynomials.

As the use of monomials is usually associated with their integration over some domain, this project also contains Gauss-Legendre quadrature rules for the line up to order $k=61$, which are hardcoded compactly but can be retrieved using the functions in file `glq.hpp`.
- Rule retrieval is available for the rules based on the intervals $[-1,1]$ and $[0,1]$.

The choice to restrict the quadrature rules to the 1D ones is motivated by the use of [Homogeneous Numerical Integration](https://www.sciencedirect.com/science/article/pii/S0167839620301011) on general polytopes, which is currently being implemented in the sibling project [PTP](https://github.com/tiagomhrd/ptp) for two and three dimensions.
This integration scheme is aimed at the sequential integration of monomials by performing successive applications of the [Generalized Stokes Theorem](https://en.wikipedia.org/wiki/Generalized_Stokes_theorem) along with the leveraging [Euler's Theorem for Homogeneous Functions](https://en.wikipedia.org/wiki/Homogeneous_function#Euler's_theorem) to ultimately performs these integrations in the edges of the polytope without increase of the integrand's order, requiring only that the integrals of lesser orders are known.

## Installation Instructions

So far, the code is implemented only in C++, and uses only `.hpp` files which can be included directly into the user's code.

One can either copy them directly from github, or clone it.
```bash
git clone https://github.com/tiagomhrd/mnl.git
```

As a design decision, the main code has been implemented in `C++11`, to reach wider audiences.
The testing project has been implemented in `C++23`.

### Dependencies

Internal dependencies: `pnl.hpp` and `glq.hpp` include `mnl.hpp`.

External dependencies: 
- `mnl.hpp` includes `<array>`;
- `pnl.hpp` includes `mnl.hpp` (`<array>`) and `<unordered_map>`;
- `glq.hpp` includes `mnl.hpp` (`<array>`) and `<vector>`;

The dependency on `<array>` is associated with the use of lookup tables.
It can be substituted in the case of `mnl.hpp` and `pnl.hpp` by providing another way of computing factorials for the computation of Monomial Orders.
It is required for `glq.hpp` as the whole thing basically consists on a big lookup table.

### Development

For development, the project also supports two build systems: [CMake](https://cmake.org/) and [Premake](https://premake.github.io/).
The latter with its executable included in the project files inside the `third_party` directory along with its license.

These build systems will set the `tests` project as the main project, this uses the [Catch2](https://github.com/catchorg/Catch2) framework for testing.
The code for Catch2 is also included in its amalgamated version inside `third_party` (along with its License).
The version used is `v3.6.0`.

These tests can be useful for learning purposes.

To generate project files using Premake, just edit `GenerateProjects.bat` to your editor of choice using the [options provided](https://premake.github.io/docs/Using-Premake#using-premake-to-generate-project-files) and run it.
To avoid run a `.bat` file, you can also run the command directly on you command prompt:
```bash
\mnl> third_party\premake5.exe [action]
```

To generate them with CMake, do the following:
```bash
\mnl> mkdir build
\mnl> cd build
\mnl\build> cmake ..
```

## Usage and Examples

This section introduces some notation and examples that can help understand the intended use and workflow of the project.

In a general sense, monomials can be thought of products of powers of variables, i.e., for $m_\alpha\in P_k(\mathbb{R}^d)$ we have

$m_\alpha=\prod_{i=0}^{d-1} x_i^{e_i}$

where $x_i$ is the variable and $e_i$ its corresponding exponent with $\sum_{i=0}^{d-1}e_i\leq k$ because it is of order at most $k$.

Obs: Zero-based indexing is used in the code.


### mnl

### pnl

### glq







