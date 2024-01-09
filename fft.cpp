#include "fft.h"

#include <fftw3.h>
#include <cmath>
#include <stdexcept>

class DctCalculator::Impl {
public:
	Impl(size_t width, std::vector<double> *input, std::vector<double> *output)
			: n_(width), in_(input), out_(output) {
		if (in_->size() != n_ * n_) {
			throw std::invalid_argument("Incorrect size of input array in DCT Calculator");
		}
		if (out_->size() != n_ * n_) {
			throw std::invalid_argument("Incorrect size of input array in DCT Calculator");
		}
		plan_ = fftw_plan_r2r_2d(n_, n_, in_->data(), out_->data(), FFTW_REDFT01, FFTW_REDFT01, 0);
	}
	void Inverse() {
		(*in_)[0] *= 2;
		for (size_t i = 1; i < n_; ++i) {
			(*in_)[i * n_ + 0] *= std::sqrt(2);
		}
		for (size_t j = 1; j < n_; ++j) {
			(*in_)[0 * n_ + j] *= std::sqrt(2);
		}
		for (size_t i = 0; i < n_ * n_; ++i) {
			(*in_)[i] /= n_ * 2;
		}
		fftw_execute(plan_);
	}

	~Impl() {
		fftw_destroy_plan(plan_);
	}

private:
	size_t n_;
	std::vector<double> *in_;
	std::vector<double> *out_;
	fftw_plan plan_;
};

DctCalculator::DctCalculator(size_t width, std::vector<double> *input, std::vector<double> *output)
		: impl_(new DctCalculator::Impl(width, input, output)) {
}

void DctCalculator::Inverse() {
	impl_->Inverse();
}

DctCalculator::~DctCalculator() = default;
