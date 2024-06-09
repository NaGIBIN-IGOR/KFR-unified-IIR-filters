#ifndef __irr_chebyshev_filter__
#define __irr_chebyshev_filter__

#include "iir_base.h"

namespace Dsp
{

	template <typename T>
	class IIRChebyshevFilter1 : public IIRBase<T>
	{
	public:
		IIRChebyshevFilter1(int filterSize = 128, int order = 8, float ripple = 1);
	};

	template<typename T>
	IIRChebyshevFilter1<T>::IIRChebyshevFilter1(int filterSize, int order, float ripple): IIRBase<T>(filterSize, kfr::chebyshev1<T>(order, ripple))
	{
	}

	template <typename T>
	class IIRChebyshevFilter2 : public IIRBase<T>
	{
	public:
		IIRChebyshevFilter2(int filterSize = 128, int order = 8, float ripple = 1);
	};

	template<typename T>
	IIRChebyshevFilter2<T>::IIRChebyshevFilter2(int filterSize, int order, float ripple) : IIRBase<T>(filterSize, kfr::chebyshev2<T>(order, ripple))
	{
	}
}
#endif // !__irr_chebyshev_filter__
