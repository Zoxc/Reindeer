#pragma once
#include "CanvasFriend.hpp"

namespace Reindeer
{
	template<> static typename SourceSolid::ArgumentType CanvasFriend::get_source_state<SourceSolid>(Canvas &canvas)
	{
		return canvas.source_color;
	}

	template<> static typename SourceTexture::ArgumentType CanvasFriend::get_source_state<SourceTexture>(Canvas &canvas)
	{
		return canvas.source_texture;
	}
	
	template<> static typename MaskNone::ArgumentType CanvasFriend::get_mask_state<MaskNone>(Canvas &canvas)
	{
		return nullptr;
	}
		
	template<> static typename MaskSolid::ArgumentType CanvasFriend::get_mask_state<MaskSolid>(Canvas &canvas)
	{
		return canvas.mask_color;
	}

	template<> static typename MaskTexture::ArgumentType CanvasFriend::get_mask_state<MaskTexture>(Canvas &canvas)
	{
		return canvas.mask_texture;
	}
};
