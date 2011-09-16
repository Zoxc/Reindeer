#include "CanvasFriend.hpp"

namespace Reindeer
{
	template<> typename SourceSolid::ArgumentType CanvasFriend::get_source_state<SourceSolid>(Canvas &canvas)
	{
		return canvas.source_color;
	}

	template<> typename SourceTexture::ArgumentType CanvasFriend::get_source_state<SourceTexture>(Canvas &canvas)
	{
		return canvas.source_texture;
	}
	
	template<> typename MaskNone::ArgumentType CanvasFriend::get_mask_state<MaskNone>(Canvas &canvas)
	{
		return nullptr;
	}
		
	template<> typename MaskSolid::ArgumentType CanvasFriend::get_mask_state<MaskSolid>(Canvas &canvas)
	{
		return canvas.mask_color;
	}

	template<> typename MaskTexture::ArgumentType CanvasFriend::get_mask_state<MaskTexture>(Canvas &canvas)
	{
		return canvas.mask_texture;
	}
};
