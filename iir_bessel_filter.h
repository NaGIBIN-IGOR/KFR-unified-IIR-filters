#ifndef __iir_bessel_filter__
#define __iir_bessel_filter__

#include "iir_base.h"

namespace Dsp
{

	template <typename T>
	class IIRBesselFilter : public IIRBase<T>
	{
	public:
		IIRBesselFilter(int filterSize = 128, int order = 8);
	};

	template<typename T>
	IIRBesselFilter<T>::IIRBesselFilter(int filterSize, int order) : IIRBase<T>(filterSize, kfr::bessel<T>(order))
	{
	}
}

#endif // __iir_bessel_filter__