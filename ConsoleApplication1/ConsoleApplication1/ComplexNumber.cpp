#include <stdlib.h>

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
			double real, imaginary;
			real = (this->real * other.getReal()) - (this->imaginary * other.getImaginary());
			imaginary = (this->real * other.getImaginary()) + (this->imaginary * other.getReal());
			ComplexNumber * result =  new ComplexNumber(real, imaginary);

			return result;
		}

		ComplexNumber * add(ComplexNumber other) {
			ComplexNumber * result = new ComplexNumber(other.getReal() + this->real, other.getImaginary() + this->imaginary);
			return result;
		}

		ComplexNumber * subtract(ComplexNumber other) {
			ComplexNumber * result = new ComplexNumber(this->real - other.getReal(), this->imaginary - other.getImaginary());
			return result;
		}

		ComplexNumber * conjugate() {
			ComplexNumber * result = new ComplexNumber(this->real, -1.0 * this->imaginary);
			return result;
		}

		ComplexNumber * multiply(double scalar) {
			ComplexNumber * result = new ComplexNumber(this->real * scalar, this->imaginary * scalar);
			return result;
		}

		double getReal() {
			return real;
		}

		double getImaginary() {
			return imaginary;
		}
		~ComplexNumber() {}
};