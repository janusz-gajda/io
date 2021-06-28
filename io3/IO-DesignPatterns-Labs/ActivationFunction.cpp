#include "ActivationFunction.h"
#include <cmath>

double Sigmoid::Function(double x) {
	return 1 / (1 + exp(-BETA * x));
}

double Sigmoid::Derivative(double x, double fun) {
	return BETA * (1 - fun) * fun;
}

double Tanh::Function(double x) {
	return tanh(BETA * x);
}

double Tanh::Derivative(double x, double fun) {
	return BETA * (1 - pow(fun, 2));
}

double ArcTan::Function(double x) {
	return atan(x);
}

double ArcTan::Derivative(double x, double fun) {
	return 1 / (pow(x, 2) + 1);
}

double ReLU::Function(double x) {
	if (x < 0) return 0;
	return x;
}

double ReLU::Derivative(double x, double fun) {
	if (x < 0) return 0;
	return 1;
}