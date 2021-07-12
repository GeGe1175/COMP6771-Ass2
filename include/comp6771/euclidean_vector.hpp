#ifndef COMP6771_EUCLIDEAN_VECTOR_HPP
#define COMP6771_EUCLIDEAN_VECTOR_HPP

#include <iostream>
#include <memory>
#include <exception>
#include <stdexcept>
#include <string>
#include <vector>
#include <math.h>
#include <list>

namespace comp6771 {
	class euclidean_vector_error : public std::runtime_error {
	public:
		explicit euclidean_vector_error(std::string const& what)
		: std::runtime_error(what) {}
	};

	class euclidean_vector {
	public:
		// constructors
		euclidean_vector()
		: euclidean_vector(1, 0.0){};
		euclidean_vector(int dim);
		euclidean_vector(int dim, double mag);
		euclidean_vector(std::vector<double>::const_iterator begin,
		                 std::vector<double>::const_iterator end);
		euclidean_vector(std::initializer_list<double> list);
		euclidean_vector(euclidean_vector const& vec);
		euclidean_vector(euclidean_vector&& moved_vec);

		// destructor
		~euclidean_vector() = default;

		// members
		auto at(int pos) const -> double {
			if(pos < 0 || pos >= dimension_)
				throw std::out_of_range("Index " + std::to_string(pos) + " is not valid for this euclidean_vector object");
			return magnitude_[static_cast<std::size_t>(pos)];
		}
		auto at(int pos) -> double& {
			if(pos < 0 || pos >= dimension_)
				throw std::out_of_range("Index " + std::to_string(pos) + " is not valid for this euclidean_vector object");
			return magnitude_[static_cast<std::size_t>(pos)];
		}
		auto dimensions() const noexcept -> int {
			return dimension_;
		}

		// operators
		auto operator=(euclidean_vector const& target) noexcept -> euclidean_vector&;
		auto operator=(euclidean_vector&& target) noexcept -> euclidean_vector&;
		auto operator[](int pos) noexcept -> double&;
		auto operator[](int pos) const noexcept -> double;
		auto operator+() noexcept -> euclidean_vector;
		auto operator-() noexcept -> euclidean_vector;
		auto operator+=(euclidean_vector const& target) -> euclidean_vector&;
		auto operator-=(euclidean_vector const& target) -> euclidean_vector&;
		auto operator*=(double num) noexcept -> euclidean_vector&;
		auto operator/=(double num) -> euclidean_vector&;
		explicit operator std::vector<double>() noexcept;
		explicit operator std::vector<double>() const noexcept;
		explicit operator std::list<double>() noexcept;
		explicit operator std::list<double>() const noexcept;

		// friends
		friend auto operator==(euclidean_vector const& lhs, euclidean_vector const& rhs) -> bool {
			// TODO
			for (std::size_t(i) = 0; i < static_cast<std::size_t>(lhs.dimension_); i++) {
				if(lhs.magnitude_[i] != rhs.magnitude_[i]) {
					return false;
				}
			}
			if (lhs.dimension_ != rhs.dimension_) {
				return false;
			}
			return true;
		}
		friend auto operator!=(euclidean_vector const& lhs, euclidean_vector const& rhs) -> bool {
			return !(lhs == rhs);
		}
		friend auto operator+(euclidean_vector const& lhs, euclidean_vector const& rhs) -> euclidean_vector {
			if (lhs.dimension_ != rhs.dimension_) {
				throw std::logic_error("Dimensions of LHS(" + std::to_string(lhs.dimension_) + ") and RHS("
				                       + std::to_string(rhs.dimension_) + ") do not match");
			}
			std::transform(lhs.magnitude_.get(), lhs.magnitude_.get() + lhs.dimension_, rhs.magnitude_.get(), lhs.magnitude_.get(), [](double x, double y) -> double { return x + y; });
			return lhs;
		}
		friend auto operator-(euclidean_vector const& lhs, euclidean_vector const& rhs) -> euclidean_vector {
			if (lhs.dimension_ != rhs.dimension_) {
				throw std::logic_error("Dimensions of LHS(" + std::to_string(lhs.dimension_) + ") and RHS("
				                       + std::to_string(rhs.dimension_) + ") do not match");
			}
			std::transform(lhs.magnitude_.get(), lhs.magnitude_.get() + lhs.dimension_, rhs.magnitude_.get(), lhs.magnitude_.get(), [](double x, double y) -> double { return x - y; });
			return lhs;
		}
		friend auto operator*(euclidean_vector const& lhs, double num) -> euclidean_vector {
			std::transform(lhs.magnitude_.get(), lhs.magnitude_.get() + lhs.dimension_, lhs.magnitude_.get(), [&num](double x) -> double { return x * num; });
			return lhs;
		}
		friend auto operator*(double num, euclidean_vector const& rhs) -> euclidean_vector {
			std::transform(rhs.magnitude_.get(), rhs.magnitude_.get() + rhs.dimension_, rhs.magnitude_.get(), [&num](double x) -> double { return x * num; });
			return rhs;
		}
		friend auto operator/(euclidean_vector const& lhs, double num) -> euclidean_vector {
			if (num == 0) {
				throw std::logic_error("Invalid vector division by 0");
			}
			std::transform(lhs.magnitude_.get(), lhs.magnitude_.get() + lhs.dimension_, lhs.magnitude_.get(), [&num](double x) -> double { return x / num; });
			return lhs;
		}
		friend auto operator<<(std::ostream& os, euclidean_vector const& vec) -> std::ostream& {
			os << "[";
			// TODO
			for (std::size_t(i) = 0; i < static_cast<std::size_t>(vec.dimension_); i++) {
				if (i == static_cast<std::size_t>(vec.dimension_ - 1)) {
					os << vec.magnitude_[i];
				}
				else {
					os << vec.magnitude_[i] << " ";
				}
			}
			os << "]";
			return os;
		}

	private:
		int dimension_;
		std::unique_ptr<double[]> magnitude_;
	};

	auto euclidean_norm(euclidean_vector const& v) noexcept -> double;
	auto unit(euclidean_vector const& v) -> euclidean_vector;
	auto dot(euclidean_vector const& x, euclidean_vector const& y) -> double;

} // namespace comp6771
#endif // COMP6771_EUCLIDEAN_VECTOR_HPP
