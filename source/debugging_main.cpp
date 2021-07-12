#include <iostream>
#include <vector>
#include "comp6771/euclidean_vector.hpp"

// Please note: it's not good practice to test your code via a main function that does
//  printing. Instead, you should be using your test folder. This file should only really
//  be used for more "primitive" debugging as we know that working solely with test
//  frameworks might be overwhelming for some.

auto main() -> int {
	// auto a = comp6771::euclidean_vector();
	// std::cout << a.dimensions() << std::endl;
	// auto b = comp6771::euclidean_vector(1);
	// std::cout << b << std::endl;
	// auto c = comp6771::euclidean_vector(2, 3.0);
	// std::cout << c << std::endl;

	// std::vector<double> v;
	// v.push_back(5.0);
	// v.push_back(6.0);
	// v.push_back(3.0);
	// auto d = comp6771::euclidean_vector(v.begin(),v.end());
	// std::cout << d.dimensions() << std::endl;

	// auto e = comp6771::euclidean_vector{1.1, 2.2, 3.3, 5.5};
	//std::cout << e.dimensions() << std::endl;

	// auto e = comp6771::euclidean_vector{1.1, 2.2, 3.3, 5.5};
	// auto f = comp6771::euclidean_vector(e);
	// std::cout << f << std::endl;

	// move constructor
	// auto e = comp6771::euclidean_vector{1.1, 2.2, 3.3, 5.5};
	// std::cout << e.dimensions() << std::endl;
	// auto eMove = comp6771::euclidean_vector(std::move(e));
	// std::cout << eMove.dimensions() << std::endl;
	// std::cout << e.dimensions() << std::endl;

	// // copy assignment =
	// auto e = comp6771::euclidean_vector{1.1, 2.2, 3.3, 5.2};
	// auto g = comp6771::euclidean_vector(2, 3.0);
	// g = e;
	// std::cout << g << std::endl;

	// // move assignment =
	// auto f = comp6771::euclidean_vector{1.1, 2.2, 3.3, 5.2};
	// auto g = comp6771::euclidean_vector(2, 3.0);
	// g = std::move(f);
	// std::cout << g << std::endl;
	// std::cout << f << std::endl;

	// // []
	// auto b = comp6771::euclidean_vector(1);
	// b[0] = 3.0;
	// std::cout << b[0] << std::endl;
	// double c{b[0]};
	// std::cout << c << std::endl;
	// b[1] = 3.0;

	// // unary +
	// auto e = comp6771::euclidean_vector{1.1, 2.2, 3.3, 5.2};
	// auto g = +e;
	// std::cout << g << std::endl;

	// // negation -
	// auto e = comp6771::euclidean_vector{6, -1};
	// std::cout << e << std::endl;
	// auto a = -e;
	// std::cout << a << std::endl;

	// // +=
	// auto c = comp6771::euclidean_vector(2, 3.0);
	// auto d = comp6771::euclidean_vector(3, 4.2);
	// c += d;
	// auto f = comp6771::euclidean_vector(2, 3.0);
	// auto g = comp6771::euclidean_vector(2, 4.2);
	// f += g;
	// std::cout << f.dimensions() << std::endl;

	// // -=
	// auto c = comp6771::euclidean_vector(2, 3.0);
	// auto d = comp6771::euclidean_vector(3, 4.2);
	// c -= d;
	// auto f = comp6771::euclidean_vector(2, 3.0);
	// auto g = comp6771::euclidean_vector(2, 4.2);
	// f -= g;

	// // *=
	// auto c = comp6771::euclidean_vector(2, 3.0);
	// c *= 1.5;
	// std::cout << c.dimensions() << std::endl;
	// c *= 1.5;
	// std::cout << c.dimensions() << std::endl;

	// // /=
	// auto c = comp6771::euclidean_vector(2, 5.0);
	// c /= 2;
	// std::cout << c.dimensions() << std::endl;
	// c /= 0.5;
	// std::cout << c.dimensions() << std::endl;
	// c /= 0;

	// auto a = comp6771::euclidean_vector{0.0, 1.0, 2.0};
	// auto const vf = static_cast<std::vector<double>>(a);
	// std::cout << vf[1] << std::endl;

	// auto a1 = comp6771::euclidean_vector{0.0, 1.0, 2.0};
	// auto vf1 = static_cast<std::vector<double>>(a);
	// std::cout << vf1[1] << std::endl;

	// auto const a = comp6771::euclidean_vector{0.0, 1.0, 2.0};
	// auto lf = static_cast<std::list<double>>(a);
	// for (auto const &i: lf) {
    //     std::cout << i << std::endl;
    // }

    // auto const a = comp6771::euclidean_vector{0.0, 1.0, 2.0};
	// auto const lf = static_cast<std::list<double>>(a);
	// for (auto const &i: lf) {
    //     std::cout << i << std::endl;
    // }

	// auto e = comp6771::euclidean_vector{1.1, 2.2, 3.3, 5.2};
	// auto g = comp6771::euclidean_vector{1.1, 2.2, 3.3, 5.2};
	// if(e == g) {
	// 	std::cout << "true" << std::endl;
	// }
	// auto f = comp6771::euclidean_vector{1.1, 2.2, 3.3};
	// if(e != f) {
	// 	std::cout << "true" << std::endl;
	// }

	// +
	// auto e = comp6771::euclidean_vector{1.1, 2.2, 3.3, 5.2};
	// auto g = comp6771::euclidean_vector{1, 2, 3, 5};
	// auto h = e + g;
	// auto f = comp6771::euclidean_vector{1.1, 2.2, 3.3};
	// h = f + h;
	// std::cout << h << std::endl;
	// h = h + e;
	// std::cout << h << std::endl;

	// // -
	// auto e = comp6771::euclidean_vector{3.1, 4.2, 6.3, 10.2};
	// auto g = comp6771::euclidean_vector{1.1, 2.2, 3.3, 5.2};
	// auto h = e - g;
	// auto f = comp6771::euclidean_vector{1.1, 2.2, 3.3};
	// h = f - h;
	// std::cout << h << std::endl;
	// h = e - h;
	// std::cout << h << std::endl;
	// h = h-g;
	// std::cout << h << std::endl;

	// // *
	// auto c = comp6771::euclidean_vector(2, 3.0);
	// auto a = c * 1.5;
	// a = a * 1.5;
	// a = 2 * a;

	// // /
	// auto c = comp6771::euclidean_vector(2, 5.0);
	// c = c / 2;
	// std::cout << c.dimensions() << std::endl;
	// c = c / 0.5;
	// std::cout << c.dimensions() << std::endl;
	// c = c / 0;

	// print
	// auto e = comp6771::euclidean_vector{1.1, 2.2, 3.3, 5.2};
	// std::cout << e << std::endl;
	// std::cout << e.at(0) << std::endl;
	// std::cout << e.at(-1) << std::endl;
	// std::cout << e.at(4) << std::endl;

	// comp6771::euclidean_norm(a)
	// auto g = comp6771::euclidean_vector{1, 2, 3};
	// auto result = comp6771::euclidean_norm(g);
	// std::cout << result << std::endl;
	// auto h = comp6771::euclidean_vector{0};
	// std::cout << comp6771::euclidean_norm(h) << std::endl;

	// auto unit(euclidean_vector const& v) -> euclidean_vector
	// auto g = comp6771::euclidean_vector{1, 2, 3};
	// auto j = comp6771::unit(g);
	// std::cout << j << std::endl;
	// auto a = comp6771::euclidean_vector(0);
	// auto n = comp6771::unit(a);

	// auto c = double{comp6771::dot(a, b)}
	// auto e = comp6771::euclidean_vector{3, 4, 6, 10};
	// auto g = comp6771::euclidean_vector{1, 2, 3, 5, 6};
	// auto c = double{comp6771::dot(e, g)};
	// std::cout << c << std::endl;

	// auto e = comp6771::euclidean_vector{1, 2};
	// auto f = comp6771::euclidean_vector{3, 4};
	// auto c = double{comp6771::dot(e, f)};
	// std::cout << c << std::endl;
}