#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <sstream>
#include <vector>

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
	int i {3};
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
	auto v =std::vector<double>();
	v.push_back(5.0);
	v.push_back(6.0);
	v.push_back(3.0);
	auto a1 = comp6771::euclidean_vector(v.begin(),v.end());

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

	try {
		c += d;
	} catch (std::logic_error& error) {
			CHECK(error.what() == "Dimensions of LHS(" + std::to_string(c.dimensions()) + ") and RHS("
			                       + std::to_string(d.dimensions()) + ") do not match");
	}
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

	try {
		c -= d;
	} catch (std::logic_error& error) {
		CHECK(error.what() == "Dimensions of LHS(" + std::to_string(c.dimensions()) + ") and RHS("
		                       + std::to_string(d.dimensions()) + ") do not match");
	}
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

	CHECK_THROWS_MATCHES(c /= 0, std::logic_error, Catch::Matchers::Message("Invalid vector division by 0"));
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
	// need to change
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

	try {
		auto h = e + g;
	} catch (std::logic_error& error) {
		CHECK(error.what() == "Dimensions of LHS(" + std::to_string(e.dimensions()) + ") and RHS("
			                       + std::to_string(g.dimensions()) + ") do not match");;
	}
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

	try {
		auto h = e - g;
	} catch (std::logic_error& error) {
		CHECK(error.what() == "Dimensions of LHS(" + std::to_string(e.dimensions()) + ") and RHS("
			                       + std::to_string(g.dimensions()) + ") do not match");
	}
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

	CHECK_THROWS_MATCHES(c / 0, std::logic_error, Catch::Matchers::Message("Invalid vector division by 0"));
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

	CHECK_THROWS_MATCHES(e.at(-1), std::logic_error, Catch::Matchers::Message("Index -1 is not valid for this euclidean_vector object"));
}

TEST_CASE("dimensions") {
	auto e = comp6771::euclidean_vector{1.1, 2.2, 3.3, 5.2};

	CHECK(e.dimensions() == 4);
}

// utility
TEST_CASE("norm") {
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

TEST_CASE("unit invalid") {
	auto a = comp6771::euclidean_vector(0);

	CHECK_THROWS_MATCHES(comp6771::unit(a), std::logic_error, Catch::Matchers::Message("euclidean_vector with no dimensions does not have a unit vector"));
}

TEST_CASE("unit norm invalid") {
	auto a = comp6771::euclidean_vector(25, 0);

	CHECK_THROWS_MATCHES(comp6771::unit(a), std::logic_error, Catch::Matchers::Message("euclidean_vector with zero euclidean normal does not have a unit vector"));
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
	try {
		auto f = double{comp6771::dot(e, g)};
		(void)f;
	} catch(std::logic_error& error) {
		CHECK(error.what() == "Dimensions of LHS(" + std::to_string(e.dimensions()) + ") and RHS("
			                       + std::to_string(g.dimensions()) + ") do not match");
	}
}