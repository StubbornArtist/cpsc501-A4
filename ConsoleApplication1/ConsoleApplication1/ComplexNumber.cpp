#include "stdafx.h"

class ComplexNumber {

	private:
		double real;
		double imaginary;

	public:
		ComplexNumber(double real, double imaginary) {
			this->real = real;
			this->imaginary = imaginary;
		}
		ComplexNumber(double real) : ComplexNumber(real, 0.0){}
		ComplexNumber() : ComplexNumber(0.0){}

		ComplexNumber * multiply(ComplexNumber other) {
			double real = (this->real * other.getReal()) - (this->imaginary * other.getImaginary());
			double imaginary = (this->real * other.getImaginary()) + (this->imaginary * other.getReal());
			return new ComplexNumber(real, imaginary);
		}

		ComplexNumber * add(ComplexNumber other) {
			return new ComplexNumber(other.getReal() + this->real, other.getImaginary() + this->imaginary);
		}

		ComplexNumber * subtract(ComplexNumber other) {
			return new ComplexNumber(this->real - other.getReal(), this->imaginary - other.getImaginary());
		}

		ComplexNumber * conjugate() {
			return new ComplexNumber(this->real, -1.0 * this->imaginary);
		}

		ComplexNumber * multiply(double scalar) {
			return new ComplexNumber(this->real * scalar, this->imaginary * scalar);
		}

		double getReal() {
			return real;
		}

		double getImaginary() {
			return imaginary;
		}
};