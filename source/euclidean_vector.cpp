// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "comp6771/euclidean_vector.hpp"
#include <exception>
#include <iostream>
#include <vector>
#include <iterator>
#include <assert.h>
#include <list>

namespace comp6771 {
	// constructors
	euclidean_vector::euclidean_vector(int dim) {
		dimension_ = dim;
		magnitude_ = std::make_unique<double[]>(std::size_t(dim));
		std::fill(magnitude_.get(), magnitude_.get() + dim, 0);
	}
	euclidean_vector::euclidean_vector(int dim, double mag) {
		dimension_ = dim;
		magnitude_ = std::make_unique<double[]>(std::size_t(dim));
		std::fill(magnitude_.get(), magnitude_.get() + dim, mag);
	};
	euclidean_vector::euclidean_vector(std::vector<double>::const_iterator begin,
	                                   std::vector<double>::const_iterator end) {
		dimension_ = static_cast<int>((std::distance(begin, end)));
		magnitude_ = std::make_unique<double[]>(std::size_t(dimension_));
		std::transform(begin, end, magnitude_.get(), [](double x) -> double { return x; });
	}
	euclidean_vector::euclidean_vector(std::initializer_list<double> list) {
		dimension_ = static_cast<int>(list.size());
		magnitude_ = std::make_unique<double[]>(std::size_t(list.size()));
		auto begin = list.begin();
		auto end = list.end();
		std::transform(begin, end, magnitude_.get(), [](double x) -> double { return x; });
	}
	euclidean_vector::euclidean_vector(euclidean_vector const& vec) {
		dimension_ = vec.dimension_;
		magnitude_ = std::make_unique<double[]>(std::size_t(vec.dimension_));
		std::copy(vec.magnitude_.get(), vec.magnitude_.get() + vec.dimension_, magnitude_.get());
	}
	euclidean_vector::euclidean_vector(euclidean_vector&& moved_vec) {
		if(this != &moved_vec) {
			magnitude_.reset(moved_vec.magnitude_.get());
			dimension_ = moved_vec.dimension_;
			moved_vec.magnitude_.release();
			moved_vec.dimension_ = 0;
		}
	}

	// operators
	auto euclidean_vector::operator=(euclidean_vector const& target) noexcept -> euclidean_vector& {
		dimension_ = target.dimension_;
		magnitude_ = std::make_unique<double[]>(std::size_t(target.dimension_));
		std::copy(target.magnitude_.get(), target.magnitude_.get() + target.dimension_, magnitude_.get());
		return *this;
	}
	auto euclidean_vector::operator=(euclidean_vector&& moved_vec) noexcept -> euclidean_vector& {
		if(this != &moved_vec) {
			magnitude_.reset(moved_vec.magnitude_.get());
			dimension_ = moved_vec.dimension_;
			moved_vec.magnitude_.release();
			moved_vec.dimension_ = 0;
		}
		return *this;
	}
	auto euclidean_vector::operator[](int pos) noexcept -> double& {
		assert(pos >= 0 and this->dimension_ > pos);
		return 	this->magnitude_[std::size_t(pos)];
	}
	auto euclidean_vector::operator[](int pos) const noexcept -> double {
		assert(pos >= 0 and this->dimension_ > pos);
		return 	this->magnitude_[std::size_t(pos)];
	}
	auto euclidean_vector::operator+() noexcept -> euclidean_vector {
		return *this;
	}
	auto euclidean_vector::operator-() noexcept -> euclidean_vector {
		auto copy = euclidean_vector(dimension_);
		copy.magnitude_ = std::make_unique<double[]>(std::size_t(dimension_));
		std::transform(this->magnitude_.get(), this->magnitude_.get() + dimension_, copy.magnitude_.get(), [](double x) -> double { return -x; });
		return copy;
	}
	auto euclidean_vector::operator+=(euclidean_vector const& target) -> euclidean_vector& {
		if (this->dimension_ != target.dimension_) {
			throw std::logic_error("Dimensions of LHS(" + std::to_string(this->dimension_) + ") and RHS("
			                       + std::to_string(target.dimension_) + ") do not match");
		}
		std::transform(this->magnitude_.get(), this->magnitude_.get() + dimension_, target.magnitude_.get(), this->magnitude_.get(), [](double x, double y) -> double { return x + y; });
		return *this;
	}
	auto euclidean_vector::operator-=(euclidean_vector const& target) -> euclidean_vector& {
		if (this->dimension_ != target.dimension_) {
			throw std::logic_error("Dimensions of LHS(" + std::to_string(this->dimension_) + ") and RHS("
			                       + std::to_string(target.dimension_) + ") do not match");
		}
		std::transform(this->magnitude_.get(), this->magnitude_.get() + dimension_, target.magnitude_.get(), this->magnitude_.get(), [](double x, double y) -> double { return x - y; });
		return *this;
	}
	auto euclidean_vector::operator*=(double num) noexcept -> euclidean_vector& {
		std::transform(this->magnitude_.get(), this->magnitude_.get() + dimension_, this->magnitude_.get(), [&num](double x) -> double { return x * num; });
		return *this;
	}
	auto euclidean_vector::operator/=(double num) -> euclidean_vector& {
		if (num == 0) {
			throw std::logic_error("Invalid vector division by 0");
		}
		std::transform(this->magnitude_.get(), this->magnitude_.get() + dimension_, this->magnitude_.get(), [&num](double x) -> double { return x / num; });
		return *this;
	}
	euclidean_vector::operator std::vector<double>() noexcept {
		auto vec = std::vector<double>(std::size_t(this->dimension_));
	    std::transform(this->magnitude_.get(), this->magnitude_.get() + dimension_, vec.begin(), [](double x) -> double { return x; });
	    return vec;
	}
	euclidean_vector::operator std::vector<double>() const noexcept {
		auto vec = std::vector<double>(std::size_t(this->dimension_));
		std::transform(this->magnitude_.get(), this->magnitude_.get() + dimension_, vec.begin(), [](double x) -> double { return x; });
	    return vec;
	}
	euclidean_vector::operator std::list<double>() noexcept {
		auto li = std::list<double>(std::size_t(this->dimension_));
	    std::transform(this->magnitude_.get(), this->magnitude_.get() + dimension_, li.begin(), [](double x) -> double { return x; });
	    return li;
	}
	euclidean_vector::operator std::list<double>() const noexcept {
		auto li = std::list<double>(std::size_t(this->dimension_));
	    std::transform(this->magnitude_.get(), this->magnitude_.get() + dimension_, li.begin(), [](double x) -> double { return x; });
	    return li;
	}

	struct Sum
{
    void operator()(int n) { sum += n; }
    int sum{0};
};

	// utilities
	auto euclidean_norm(euclidean_vector const& v) noexcept -> double {
		//auto total = 0.0;
		//std::remove_const<euclidean_vector const&>::type v;
		auto vec = std::const_cast<int>(v);
		// auto end = &v.at(v.dimensions());
		// Sum s = std::for_each(begin, end, Sum());
		return 2;
	}

	auto unit(euclidean_vector const& v) -> euclidean_vector {
		if(v.dimensions() == 0) {
			throw std::out_of_range("euclidean_vector with no dimensions does not have a unit vector");
		}
		auto vec = euclidean_vector(v.dimensions());
		auto norm = euclidean_norm(v);
		if(norm == 0) {
			throw std::out_of_range("euclidean_vector with zero euclidean normal does not have a unit vector");
		}// TODO
		for (std::size_t(i) = 0; i < static_cast<std::size_t>(v.dimensions()); i++) {
			auto add = &vec.at(int(i));
			*add = v.at(int(i)) / norm;
		}
		return vec;
	}

	auto dot(euclidean_vector const& x, euclidean_vector const& y) -> double {
		if(x.dimensions() != y.dimensions()) {
			throw std::out_of_range("Dimensions of LHS(" + std::to_string(x.dimensions()) + ") and RHS("
					                       + std::to_string(y.dimensions()) + ") do not match");
		}
		auto product = 0.0;
		// TODO
		for (std::size_t(i) = 0; i < static_cast<std::size_t>(x.dimensions()); i++) {
			product += x.at(int(i)) * y.at(int(i));
		}
		return product;
	}

} // namespace comp6771
