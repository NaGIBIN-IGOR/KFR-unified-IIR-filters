#ifndef __irr_base__
#define __irr_base__

#include <kfr/all.hpp>
#include <algorithm>
#include <vector>
#include <functional>

namespace Dsp
{
	template <typename T>
	class IIRBase {
	public:
		IIRBase(int filterSize, kfr::zpk<T> filter);

		virtual ~IIRBase() = default;

		//! Задает полосу фильтрации при частоте дискретизации.
		void setLowpass(int freq, int sampleRate);
		//! Задает полосу фильтрации при частоте дискретизации.
		void setHighpass(int freq, int sampleRate);
		//! Задает полосу фильтрации при частоте дискретизации.
		void setBandpass(int lowFreq, int highFreq, int sampleRate);
		//! Задает полосу фильтрации при частоте дискретизации.
		void setBandstop(int lowFreq, int highFreq, int sampleRate);
		//! Задает тип окна при генерации фильтра
		void setWin(kfr::univector<kfr::fbase>& window);

		//! Сбрасывает состояние фильтра.
		void reset();
		//! Фильтрует в другой массив.
		void run(const T* in, T* out, int size);
		//! Фильтрует в тот же массив.
		void run(T* inOut, int size);

		int lowpassBand() const { return _lowpassFreq; }
		int sampleRate() const { return _sampleRate; }
		int filterSize() const { return _filterSize; }

	private:	
		kfr::zpk<T> _filter;
		std::vector<kfr::biquad_params<T>> _biquadParams;
		kfr::univector<kfr::fbase> _window;
		int _filterSize;
		int _lowpassFreq;
		int _highpassFreq;
		int _sampleRate;
	};

	template <typename T>
	IIRBase<T>::IIRBase(int filterSize, kfr::zpk<T> filter) :
		_filter(filter),
		_biquadParams(),
		_window(),
		_filterSize(filterSize),
		_lowpassFreq(0),
		_highpassFreq(0),
		_sampleRate(0) {}

	template <typename T>
	void IIRBase<T>::setLowpass(int freq, int sampleRate) {
		_lowpassFreq = freq;
		_sampleRate = sampleRate;
		kfr::zpk<T> filt = kfr::iir_lowpass(_filter, _lowpassFreq, _sampleRate);
		_biquadParams = kfr::to_sos(filt);

	}

	template <typename T>
	void IIRBase<T>::setHighpass(int freq, int sampleRate) {
		_highpassFreq = freq;
		_sampleRate = sampleRate;
		kfr::zpk<T> filt = kfr::iir_highpass(_filter, _highpassFreq, _sampleRate);
		_biquadParams = kfr::to_sos(filt);
	}

	template <typename T>
	void IIRBase<T>::setBandpass(int lowFreq, int highFreq, int sampleRate) {
		_lowpassFreq = lowFreq;
		_highpassFreq = highFreq;
		_sampleRate = sampleRate;
		kfr::zpk<T> filt = kfr::iir_bandpass(_filter, _lowpassFreq, _highpassFreq, _sampleRate);
		_biquadParams = kfr::to_sos(filt);
	}

	template <typename T>
	void IIRBase<T>::setBandstop(int lowFreq, int highFreq, int sampleRate) {
		_lowpassFreq = lowFreq;
		_highpassFreq = highFreq;
		_sampleRate = sampleRate;
		kfr::zpk<T> filt = kfr::iir_bandstop(_filter, _lowpassFreq, _highpassFreq, _sampleRate);
		_biquadParams = kfr::to_sos(filt);
	}

	template<typename T>
	void IIRBase<T>::setWin(kfr::univector<kfr::fbase>& window)
	{
		_window = window;
	}

	template<typename T>
	void IIRBase<T>::reset()
	{
		_lowpassFreq = 0;
		_highpassFreq = 0;
		_sampleRate = 0;
		_biquadParams.clear();
	}

	template <typename T>
	void IIRBase<T>::run(const T* in, T* out, int size) {
		if (_biquadParams.empty()) {
			std::copy_n(in, size, out);
			return;
		}
		kfr::univector<T> input = kfr::make_univector(in, size);
		if (!_window.empty()) {
			input *= _window;
		}
		constexpr size_t maxorder = 32;
		kfr::univector < T > kfrOutput = kfr::biquad<maxorder>(_biquadParams, input);
		std::copy_n(kfrOutput.begin(), size, out);
	}
	template<typename T>
	void IIRBase<T>::run(T* inOut, int size)
	{
		run(inOut, inOut, size);
	}
}
#endif // __irr_base__
