#pragma once

const double BETA = 1;

class ActivationFunction {
public:
	virtual double Function(double x) = 0;
	virtual double Derivative(double x, double fun) = 0;
};

class Sigmoid : public ActivationFunction {
public:
	virtual double Function(double x);
	virtual double Derivative(double x, double fun);
};

class Tanh : public ActivationFunction {
public:
	virtual double Function(double x);
	virtual double Derivative(double x, double fun);
};

class ArcTan : public ActivationFunction {
public:
	virtual double Function(double x);
	virtual double Derivative(double x, double fun);
};

class ReLU : public ActivationFunction {
public:
	virtual double Function(double x);
	virtual double Derivative(double x, double fun);
};