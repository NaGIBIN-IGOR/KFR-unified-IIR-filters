#ifndef __iir_butterworth_filter__
#define __iir_butterworth_filter__

#include "iir_base.h"

namespace Dsp
{

	template <typename T>
	class IIRButterworthFilter : public IIRBase<T>
	{
	public:
		IIRButterworthFilter(int filterSize = 128, int order = 8);
	};

	template<typename T>
	IIRButterworthFilter<T>::IIRButterworthFilter(int filterSize, int order) : IIRBase<T>(filterSize, kfr::butterworth<T>(order))
	{
	}
}

#endif // __iir_butterworth_filter__