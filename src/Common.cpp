#include "Common.hpp"
#include "CanvasFriend.hpp"
#include "Buffer.hpp"

namespace Reindeer
{
	template<class Source, class Mask> struct InitMaskDestionation
	{
		static void func(size_t width, size_t height)
		{
			CompositeCanvas<Source, Mask>::initialize(width, height);
		}
	};

	template<class Source> struct InitSourceDestination
	{
		static void func(size_t width, size_t height)
		{
			for(size_t mask = Mask::None; mask < Mask::Count; ++mask)
				CanvasFriend::mask_dispatch<InitMaskDestionation, Source, size_t, size_t>((Mask::Type)mask, width, height);
		}
	};
	
	void initialize(size_t width, size_t height)
	{
		glViewport(0, 0, width, height);

		BufferUtils::initialize();

		for(size_t source = Source::Solid; source < Source::Count; ++source)
			CanvasFriend::source_dispatch<InitSourceDestination, size_t, size_t>((Source::Type)source, width, height);
	}
};
