#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <sstream>
#include <vector>

/*
BASIC TESTS
//*/
TEST_CASE("no constructors") {
	auto const a1 = comp6771::euclidean_vector();

	auto oss = std::stringstream();
	oss << a1;
	CHECK(oss.str() == "[0]");
}

TEST_CASE("dimension constructor") {
	auto const a1 = comp6771::euclidean_vector(3);

	auto oss = std::ostringstream{};
	oss << a1;
	CHECK(oss.str() == "[0 0 0]");
}

TEST_CASE("dimension constructor v2") {
	int i{3};
	auto a1 = comp6771::euclidean_vector(i);

	auto oss = std::ostringstream{};
	oss << a1;
	CHECK(oss.str() == "[0 0 0]");
}

TEST_CASE("normal constructor") {
	auto const a1 = comp6771::euclidean_vector(3, 3.0);

	auto oss = std::ostringstream{};
	oss << a1;
	CHECK(oss.str() == "[3 3 3]");
}

TEST_CASE("normal constructor v2") {
	auto x = int{3};
	auto y = double{3.24};
	auto a1 = comp6771::euclidean_vector(x, y);

	auto oss = std::ostringstream{};
	oss << a1;
	CHECK(oss.str() == "[3.24 3.24 3.24]");
}

TEST_CASE("start iterator end iterator") {
	auto v = std::vector<double>();
	v.push_back(5.0);
	v.push_back(6.0);
	v.push_back(3.0);
	auto a1 = comp6771::euclidean_vector(v.begin(), v.end());

	auto oss = std::ostringstream{};
	oss << a1;
	CHECK(oss.str() == "[5 6 3]");
}

TEST_CASE("list of doubles") {
	auto a1 = comp6771::euclidean_vector{1.1, 2.2, 3.3, 5.2};

	auto oss = std::ostringstream{};
	oss << a1;
	CHECK(oss.str() == "[1.1 2.2 3.3 5.2]");
}

TEST_CASE("copy constructor") {
	auto a1 = comp6771::euclidean_vector{1.1, 2.2, 3.3, 5.2};
	auto a2 = comp6771::euclidean_vector(a1);

	auto oss = std::ostringstream{};
	oss << a2;
	CHECK(oss.str() == "[1.1 2.2 3.3 5.2]");
}

TEST_CASE("move constructor") {
	auto e = comp6771::euclidean_vector{1.1, 2.2, 3.3, 5.5};
	auto eMove = comp6771::euclidean_vector(std::move(e));

	auto oss = std::ostringstream{};
	oss << e;
	CHECK(oss.str() == "[]");
	auto oss1 = std::ostringstream{};
	oss1 << eMove;
	CHECK(oss1.str() == "[1.1 2.2 3.3 5.5]");
}

TEST_CASE("=") {
	auto a1 = comp6771::euclidean_vector();
	auto a2 = comp6771::euclidean_vector(2, 3.0);
	a1 = a2;

	auto oss = std::ostringstream{};
	oss << a1;
	CHECK(oss.str() == "[3 3]");
}

TEST_CASE("move =") {
	auto f = comp6771::euclidean_vector{1.1, 2.2, 3.3, 5.2};
	auto g = comp6771::euclidean_vector(2, 3.0);
	g = std::move(f);

	auto oss = std::ostringstream{};
	oss << f;
	CHECK(oss.str() == "[]");
	auto oss1 = std::ostringstream{};
	oss1 << g;
	CHECK(oss1.str() == "[1.1 2.2 3.3 5.2]");
}

TEST_CASE("[] no const") {
	auto b = comp6771::euclidean_vector(1);
	b[0] = 3.0;

	CHECK(b.at(0) == 3);
}

TEST_CASE("[] const") {
	auto b = comp6771::euclidean_vector(1);
	b[0] = 3.0;
	double c{b[0]};

	CHECK(c == 3);
}

TEST_CASE("unary +") {
	auto a1 = comp6771::euclidean_vector(2, 3.0);
	auto a2 = +a1;

	auto oss = std::ostringstream{};
	oss << a2;
	CHECK(oss.str() == "[3 3]");
}

TEST_CASE("negation -") {
	auto a1 = comp6771::euclidean_vector(2, 3.0);
	auto a2 = -a1;

	auto oss = std::ostringstream{};
	oss << a2;
	CHECK(oss.str() == "[-3 -3]");
}

TEST_CASE("negation - equality") {
	auto a1 = comp6771::euclidean_vector(2, 3.0);
	auto a2 = comp6771::euclidean_vector(2, -3.0);

	CHECK(a1 == -a2);
}

TEST_CASE("+= valid") {
	auto c = comp6771::euclidean_vector(2, 3.0);
	auto d = comp6771::euclidean_vector(2, 4.2);
	c += d;

	auto oss = std::ostringstream{};
	oss << c;
	CHECK(oss.str() == "[7.2 7.2]");
}

TEST_CASE("+= invalid") {
	auto c = comp6771::euclidean_vector(2, 3.0);
	auto d = comp6771::euclidean_vector(3, 4.2);

	CHECK_THROWS_MATCHES(
	   c += d,
	   std::logic_error,
	   Catch::Matchers::Message("Dimensions of LHS(" + std::to_string(c.dimensions()) + ") and RHS("
	                            + std::to_string(d.dimensions()) + ") do not match"));
}

TEST_CASE("-= valid") {
	auto c = comp6771::euclidean_vector(2, 3.0);
	auto d = comp6771::euclidean_vector(2, 4.2);
	c -= d;

	auto oss = std::ostringstream{};
	oss << c;
	CHECK(oss.str() == "[-1.2 -1.2]");
}

TEST_CASE("-= invalid") {
	auto c = comp6771::euclidean_vector(2, 3.0);
	auto d = comp6771::euclidean_vector(3, 4.2);

	CHECK_THROWS_MATCHES(
	   c -= d,
	   std::logic_error,
	   Catch::Matchers::Message("Dimensions of LHS(" + std::to_string(c.dimensions()) + ") and RHS("
	                            + std::to_string(d.dimensions()) + ") do not match"));
}

TEST_CASE("*=") {
	auto c = comp6771::euclidean_vector(2, 3.0);
	c *= 1.5;

	auto oss = std::ostringstream{};
	oss << c;
	CHECK(oss.str() == "[4.5 4.5]");
}

TEST_CASE("/= valid") {
	auto c = comp6771::euclidean_vector(2, 5.0);
	c /= 2;

	auto oss = std::ostringstream{};
	oss << c;
	CHECK(oss.str() == "[2.5 2.5]");
}

TEST_CASE("/= invalid") {
	auto c = comp6771::euclidean_vector(2, 3.0);

	CHECK_THROWS_MATCHES(c /= 0,
	                     std::logic_error,
	                     Catch::Matchers::Message("Invalid vector division by 0"));
}

TEST_CASE("vector type conversion") {
	auto a = comp6771::euclidean_vector{0.0, 1.0, 2.0};
	auto vf = static_cast<std::vector<double>>(a);

	CHECK(vf[0] == 0);
	CHECK(vf[1] == 1);
	CHECK(vf[2] == 2);
}

TEST_CASE("vector type conversion const") {
	auto a = comp6771::euclidean_vector{0.0, 1.0, 2.0};
	auto const vf = static_cast<std::vector<double>>(a);

	CHECK(vf[0] == 0);
	CHECK(vf[1] == 1);
	CHECK(vf[2] == 2);
}

TEST_CASE("list type conversion") {
	auto a = comp6771::euclidean_vector{0.0, 1.0, 2.0};
	auto vf = static_cast<std::list<double>>(a);
	std::list<double>::iterator it = vf.begin();

	CHECK(vf.size() == 3);
	CHECK(*it == 0);
}

TEST_CASE("list type conversion const") {
	auto a = comp6771::euclidean_vector{0.0, 1.0, 2.0};
	auto const vf = static_cast<std::list<double>>(a);

	auto oss = std::ostringstream{};
	oss << vf.size();

	CHECK(oss.str() == "3");
}

// friends
TEST_CASE("== valid") {
	auto e = comp6771::euclidean_vector{1.1, 2.2, 3.3, 5.2};
	auto g = comp6771::euclidean_vector{1.1, 2.2, 3.3, 5.2};
	auto result = (e == g);
	CHECK(result == true);
}

TEST_CASE("== invalid") {
	auto e = comp6771::euclidean_vector{1.1, 2.2, 3.3, 5.2};
	auto g = comp6771::euclidean_vector{1.1, 2.2, 3.3, 10};
	auto result = (e == g);
	CHECK(result == false);
}

TEST_CASE("!= valid") {
	auto e = comp6771::euclidean_vector{1.1, 2.2, 3.3, 5.2};
	auto g = comp6771::euclidean_vector{1.1, 2.2, 3.3, 5.2};
	auto result = (e != g);
	CHECK(result == false);
}

TEST_CASE("!= invalid") {
	auto e = comp6771::euclidean_vector{1.1, 2.2, 3.3, 5.2};
	auto g = comp6771::euclidean_vector{1.1, 2.2, 3.3, 10};
	auto result = (e != g);
	CHECK(result == true);
}

TEST_CASE("+ valid") {
	auto e = comp6771::euclidean_vector{1.1, 2.2, 3.3, 5.2};
	auto g = comp6771::euclidean_vector{1, 2, 3, 5};
	auto h = e + g;

	auto oss = std::ostringstream{};
	oss << h;
	CHECK(oss.str() == "[2.1 4.2 6.3 10.2]");
}

TEST_CASE("+ invalid") {
	auto e = comp6771::euclidean_vector{1.1, 2.2, 3.3, 5.2};
	auto g = comp6771::euclidean_vector{1, 2, 3, 5, 8};

	CHECK_THROWS_MATCHES(
	   e + g,
	   std::logic_error,
	   Catch::Matchers::Message("Dimensions of LHS(" + std::to_string(e.dimensions()) + ") and RHS("
	                            + std::to_string(g.dimensions()) + ") do not match"));
}

TEST_CASE("- valid") {
	auto e = comp6771::euclidean_vector{1.1, 2.2, 3.3, 5.2};
	auto g = comp6771::euclidean_vector{1, 2, 3, 5};
	auto h = e - g;

	auto oss = std::ostringstream{};
	oss << h;
	CHECK(oss.str() == "[0.1 0.2 0.3 0.2]");
}

TEST_CASE("- invalid") {
	auto e = comp6771::euclidean_vector{1.1, 2.2, 3.3, 5.2};
	auto g = comp6771::euclidean_vector{1, 2, 3, 5, 8};

	CHECK_THROWS_MATCHES(
	   e - g,
	   std::logic_error,
	   Catch::Matchers::Message("Dimensions of LHS(" + std::to_string(e.dimensions()) + ") and RHS("
	                            + std::to_string(g.dimensions()) + ") do not match"));
}

TEST_CASE("* valid") {
	auto c = comp6771::euclidean_vector(2, 3.0);
	auto a = c * 1.5;
	a = a * 1.5;

	auto oss = std::ostringstream{};
	oss << a;
	CHECK(oss.str() == "[6.75 6.75]");
}

TEST_CASE("/ valid") {
	auto c = comp6771::euclidean_vector(2, 3.0);
	c = c / 2;

	auto oss = std::ostringstream{};
	oss << c;
	CHECK(oss.str() == "[1.5 1.5]");
}

TEST_CASE("/ invalid") {
	auto c = comp6771::euclidean_vector(2, 3.0);

	CHECK_THROWS_MATCHES(c / 0,
	                     std::logic_error,
	                     Catch::Matchers::Message("Invalid vector division by 0"));
}

// member functions
TEST_CASE("at valid") {
	auto e = comp6771::euclidean_vector{1.1, 2.2, 3.3, 5.2};

	CHECK(e.at(0) == 1.1);
	CHECK(e.at(1) == 2.2);
	CHECK(e.at(2) == 3.3);
	CHECK(e.at(3) == 5.2);
}

TEST_CASE("at invalid") {
	auto e = comp6771::euclidean_vector{1.1, 2.2, 3.3, 5.2};

	CHECK_THROWS_MATCHES(e.at(-1),
	                     std::logic_error,
	                     Catch::Matchers::Message("Index -1 is not valid for this euclidean_vector "
	                                              "object"));
}

TEST_CASE("get dimensions") {
	auto e = comp6771::euclidean_vector{1.1, 2.2, 3.3, 5.2};

	CHECK(e.dimensions() == 4);
}

// utility
TEST_CASE("calculate normal") {
	auto a = comp6771::euclidean_vector{3.1, 4.2, 6.3, 10.2};
	auto result = comp6771::euclidean_norm(a);

	CHECK(abs(result - 13.0759320891) < 0.0001);
}

TEST_CASE("unit valid") {
	auto g = comp6771::euclidean_vector{1, 2, 3};
	auto j = comp6771::unit(g);

	auto oss = std::ostringstream{};
	oss << j;
	CHECK(oss.str() == "[0.267261 0.534522 0.801784]");
}

TEST_CASE("unit no dimensions invalid") {
	auto a = comp6771::euclidean_vector(0);

	CHECK_THROWS_MATCHES(comp6771::unit(a),
	                     std::logic_error,
	                     Catch::Matchers::Message("euclidean_vector with no dimensions does not "
	                                              "have a unit vector"));
}

TEST_CASE("unit normal 0 invalid") {
	auto a = comp6771::euclidean_vector(25, 0);

	CHECK_THROWS_MATCHES(comp6771::unit(a),
	                     std::logic_error,
	                     Catch::Matchers::Message("euclidean_vector with zero euclidean normal does "
	                                              "not have a unit vector"));
}

TEST_CASE("dot valid") {
	auto e = comp6771::euclidean_vector{3, 4, 6, 10};
	auto g = comp6771::euclidean_vector{1, 2, 3, 5};
	auto c = double{comp6771::dot(e, g)};

	auto oss = std::ostringstream{};
	oss << c;
	CHECK(oss.str() == "79");
}

TEST_CASE("dot invalid") {
	auto e = comp6771::euclidean_vector{3, 4, 6, 10};
	auto g = comp6771::euclidean_vector{1, 2, 3, 5, 20};

	CHECK_THROWS_MATCHES(
	   double{comp6771::dot(e, g)},
	   std::logic_error,
	   Catch::Matchers::Message("Dimensions of LHS(" + std::to_string(e.dimensions()) + ") and RHS("
	                            + std::to_string(g.dimensions()) + ") do not match"));
}

/*
HARDER TESTS
//*/
TEST_CASE("constructors") {
	SECTION("copy constructor with dimensions acquired from a different vector") {
		auto b = comp6771::euclidean_vector{3, 8, 12};
		auto a = comp6771::euclidean_vector(b.dimensions());

		CHECK(a.dimensions() == 3);
	}
	SECTION("copy constructor with a newly created vector with default constructor") {
		auto a = comp6771::euclidean_vector(comp6771::euclidean_vector());

		CHECK(a[0] == 0);
	}
	SECTION("copy constructor with a newly created vector with default constructor") {
		auto a = comp6771::euclidean_vector(comp6771::euclidean_vector(2));

		CHECK(a.dimensions() == 2);
	}
	SECTION("copy constructor with a newly created vector with initialiser list") {
		auto a = comp6771::euclidean_vector(comp6771::euclidean_vector{3, 4, 6, 10});

		CHECK(a[0] == 3);
		CHECK(a[1] == 4);
		CHECK(a[2] == 6);
		CHECK(a[3] == 10);
	}
	SECTION("copy constructor with a newly created vector with normal constructor") {
		auto a = comp6771::euclidean_vector(comp6771::euclidean_vector(2, 5));

		CHECK(a.dimensions() == 2);
		CHECK(a[0] == 5);
		CHECK(a[1] == 5);
	}
	SECTION("copy constructor with a newly created vector with start and end iterator") {
		auto v = std::vector<double>();
		v.push_back(1.2);
		v.push_back(3.2);
		v.push_back(6.9);
		auto a = comp6771::euclidean_vector(v.begin(), v.end());

		CHECK(a.dimensions() == 3);
		CHECK(a[0] == 1.2);
		CHECK(a[1] == 3.2);
		CHECK(a[2] == 6.9);
	}
	SECTION("copy constructor with a newly created vector with a moved vector") {
		auto f = comp6771::euclidean_vector{1.1, 2.2, 3.3, 5.2};
		auto g = std::move(f);

		CHECK(g.dimensions() == 4);
		CHECK(g[0] == 1.1);
		CHECK(g[1] == 2.2);
		CHECK(g[2] == 3.3);
		CHECK(g[3] == 5.2);
		CHECK(f.dimensions() == 0);
	}
}

TEST_CASE("operators") {
	SECTION("test negation returns a copy of opposite magnitudes") {
		auto const actual = comp6771::euclidean_vector{-6, 1};
		auto const expected = comp6771::euclidean_vector{6, -1};

		CHECK(expected == -actual);
	}
	SECTION("test unary plus returns a copy of opposite magnitudes") {
		auto const actual = comp6771::euclidean_vector{6, 1};
		auto const expected = comp6771::euclidean_vector{6, 1};

		CHECK(expected == +actual);
	}
	SECTION("mixed compound equations") {
		auto c = comp6771::euclidean_vector(2, 3.0);
		auto d = comp6771::euclidean_vector(2, 4.2);
		auto e = comp6771::euclidean_vector{3, 5};
		c -= d;
		c += d;
		c *= 5;
		c /= 3.5;

		auto oss = std::ostringstream{};
		oss << c;
		CHECK(oss.str() == "[4.28571 4.28571]");
	}
	SECTION("mixed compound equations but try dividing by 0") {
		auto c = comp6771::euclidean_vector(2, 3.0);
		auto d = comp6771::euclidean_vector(2, 4.2);
		auto e = comp6771::euclidean_vector{3, 5};
		c -= d;
		c += e;
		c *= 5;

		CHECK_THROWS_MATCHES(c /= 0,
		                     std::logic_error,
		                     Catch::Matchers::Message("Invalid vector division by 0"));
	}
	SECTION("mixed compound equations, then cast to vector") {
		auto c = comp6771::euclidean_vector(2, 3.0);
		auto d = comp6771::euclidean_vector(2, 4.2);
		auto e = comp6771::euclidean_vector{3, 5};
		c -= d;
		c += e;
		c *= 5;
		c /= 3.5;

		auto vf = static_cast<std::vector<double>>(c);

		CHECK(vf.size() == 2);
		CHECK(abs(vf[0] - 2.5714285714) < 0.0001);
		CHECK(abs(vf[1] - 5.4285714286) < 0.0001);
	}
	SECTION("mixed compound equations, then cast to list") {
		auto c = comp6771::euclidean_vector(2, 3.0);
		auto d = comp6771::euclidean_vector(2, 4.2);
		auto e = comp6771::euclidean_vector{3, 5};
		c -= d;
		c += e;
		c *= 5;
		c /= 3.5;

		auto vf = static_cast<std::list<double>>(c);

		CHECK(vf.size() == 2);
	}
}

TEST_CASE("friends") {
	SECTION("changing vector values and checking if it is still equal") {
		auto e = comp6771::euclidean_vector{3, 5};
		auto f = comp6771::euclidean_vector{3, 5};

		CHECK(e == f);

		f = f * 2.5;

		CHECK(e != f);
	}
	SECTION("mixed binary equations but try dividing by 0") {
		auto c = comp6771::euclidean_vector(2, 3.0);
		auto d = comp6771::euclidean_vector(2, 4.2);
		auto e = comp6771::euclidean_vector{3, 5};
		c = c - d;
		c = c + e;
		auto x = c * 5;

		auto oss = std::ostringstream{};
		oss << x;
		CHECK(oss.str() == "[9 19]");

		CHECK_THROWS_MATCHES(x /= 0,
		                     std::logic_error,
		                     Catch::Matchers::Message("Invalid vector division by 0"));
	}
}

TEST_CASE("utility") {
	SECTION("check if recently calculted normal is saved") {
		auto a = comp6771::euclidean_vector{1, 2, 3};
		auto result = comp6771::euclidean_norm(a);

		CHECK(abs(result - 3.7416573868) < 0.0001);

		auto unit = comp6771::unit(a);

		auto oss = std::ostringstream{};
		oss << unit;
		CHECK(oss.str() == "[0.267261 0.534522 0.801784]");
	}
	SECTION("dot product of 0") {
		auto d = comp6771::euclidean_vector{0, 0};
		auto e = comp6771::euclidean_vector{3, 5};
		auto c = double{comp6771::dot(d, e)};

		auto oss = std::ostringstream{};
		oss << c;
		CHECK(oss.str() == "0");
	}
	SECTION("dot product of newly constructed vector") {
		auto c =
		   double{comp6771::dot(comp6771::euclidean_vector{0, 0}, comp6771::euclidean_vector{3, 5})};

		auto oss = std::ostringstream{};
		oss << c;
		CHECK(oss.str() == "0");
	}
}

TEST_CASE("tests using different operations and functions") {
	SECTION("construct a vector using at()") {
		auto a = comp6771::euclidean_vector{1, 2, 3, 4, 5};
		auto b = comp6771::euclidean_vector(3, a.at(4));

		auto oss = std::ostringstream{};
		oss << b;
		CHECK(oss.str() == "[5 5 5]");
	}
	SECTION("unit of 2 identical vectors") {
		auto a = comp6771::euclidean_vector(2);
		a[0] = 1;
		a[1] = 2;
		auto b = comp6771::euclidean_vector(2);
		b[0] = 1;
		b[1] = 2;

		auto c = comp6771::unit(a);
		auto d = comp6771::unit(b);
		CHECK(c == d);
	}
	SECTION("using operations then finding the dot product") {
		auto a = comp6771::euclidean_vector{3, 5, 8.3, 9.9, 123};
		auto b = comp6771::euclidean_vector(5, 5);
		a /= 3;
		a = a * 4;
		a = a - b;
		a += b;
		auto result = double{comp6771::dot(a, b)};

		CHECK(result == 994);
	}
}
