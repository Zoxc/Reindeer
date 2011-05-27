#pragma once
#include "../include/Canvas.hpp"

namespace Reindeer
{
	template<template<typename> class Source, template<typename> class Mask, bool Conditional> struct ConditionalMap
	{
		typedef typename Source<typename Mask<typename ObjectList>::Type>::Type Type;
	};
	
	template<template<typename> class Source, template<typename> class Mask> struct ConditionalMap<Source, Mask, false>
	{
		typedef typename Mask<typename Source<typename ObjectList>::Type>::Type Type;
	};

	template<class Source, class Mask> class CompositeCanvas
	{
	private:
		typename ConditionalMap<Source::Map, Mask::Map, Source::priority >= Mask::priority>::Type map;

	public:
		CompositeCanvas(RegionAllocator &region) : map(region)
		{
		}
	};
};
