#include <iostream>
#include <cmath>
#include <iomanip>
#include <functional>

template <typename T>
class functor{
private:
	const double delta = 0.00001;
	const double eps = 0.00001;
	
public:
	auto diff(T f) {
		auto df = [=](double x) ->double { return (f(x + delta) - f(x - delta)) / (2 * delta); };
		return df;
	}

	auto integral(T f) {
		auto f_integral = [=](double r, double l) ->double {
			double sum = 0;
			for (auto i = r; i <= l; i += eps)
			{
				sum += f(i)*eps;
			}
			return sum;
		};

		return f_integral;
	}


};


int main() {

	auto f = [](double x) -> double {return x * std::sin(x); };

	functor<std::function<double(double)>> function;

	auto df = function.diff(f);
	auto f_integral = function.integral(f);

	for (int step = 0; step < 5; step++) {
		double x = 0.0 + step * 0.5;
		std::cout << std::setprecision(4)
			<< "f(" << x << ") = " << f(x)
			<< ", f'(" << x << ") = " << df(x)
			<< ", f_int(" << x << "," << x + 0.5 << ") = " << f_integral(x, x + 0.5)
			<< std::endl;
	}
}