#pragma once
#include "../include/Reindeer/Canvas.hpp"
#include "Common.hpp"

namespace Reindeer
{
	template<class Source, class Mask, bool Conditional> struct ConditionalCanvas
	{
		typedef typename Mask::template Map<ObjectList<Source, Mask> > MaskMap;
		typedef typename Source::template Map<typename MaskMap::Type> SourceMap;
		typedef typename SourceMap::Type Map;
		
		static ObjectList<Source, Mask> &get_list(Map &map, typename Source::ArgumentType source, typename Mask::ArgumentType mask)
		{
			return MaskMap::resolve(SourceMap::resolve(map, source), mask);
		};
	};
	
	template<class Source, class Mask> struct ConditionalCanvas<Source, Mask, false>
	{
		typedef typename Source::template Map<ObjectList<Source, Mask> > SourceMap;
		typedef typename Mask::template Map<typename SourceMap::Type> MaskMap;
		typedef typename MaskMap::Type Map;

		static ObjectList<Source, Mask> &get_list(Map &map, typename Source::ArgumentType source, typename Mask::ArgumentType mask)
		{
			return SourceMap::resolve(MaskMap::resolve(map, mask), source);
		};
	};

	template<class Source, class Mask> class CompositeCanvas
	{
	private:
		typedef ConditionalCanvas<Source, Mask, Source::priority <= Mask::priority> Conditional;

		typename Conditional::Map map;

	public:
		CompositeCanvas(RegionAllocator &region) : map(region)
		{
		}

		ObjectList<Source, Mask> &get_list(typename Source::ArgumentType source, typename Mask::ArgumentType mask)
		{
			return Conditional::get_list(map, source, mask);
		};
	};
};
