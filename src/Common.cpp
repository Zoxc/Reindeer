#include "Common.hpp"
#include "CanvasFriend.hpp"

namespace Reindeer
{
	template<class Source, class Mask> struct InitMaskDestionation
	{
		static void func(void *, void *)
		{
			CompositeCanvas<Source, Mask>::initialize();
		}
	};

	template<class Source> struct InitSourceDestination
	{
		static void func(void *, void *)
		{
			for(size_t mask = Mask::None; mask < Mask::Count; ++mask)
				CanvasFriend::mask_dispatch<InitMaskDestionation, Source, void *, void *>((Mask::Type)mask, nullptr, nullptr);
		}
	};
	
	void initialize(int width, int height)
	{
		for(size_t source = Source::Solid; source < Source::Count; ++source)
			CanvasFriend::source_dispatch<InitSourceDestination, void *, void *>((Source::Type)source, nullptr, nullptr);
	}
};
