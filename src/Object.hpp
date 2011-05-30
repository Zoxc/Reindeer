#pragma once
#include <Prelude/CountedList.hpp>
#include "../include/Reindeer/Canvas.hpp"

namespace Reindeer
{
	template<class Source, class Mask> class Object
	{
	public:
		Rect rect;
		Prelude::ListEntry<Object> entry;
		typename Source::ObjectData source_data;
		typename Mask::ObjectData mask_data;

		Object(typename Source::ArgumentType source, typename Mask::ArgumentType mask, Rect &rect) : rect(rect), source_data(source), mask_data(mask)
		{
		}
	};

	template<class Source, class Mask> class ObjectList:
		public Prelude::CountedList<Object<Source, Mask>>
	{
	public:
		ObjectList(RegionAllocator::ReferenceProvider::Reference allocator = RegionAllocator::ReferenceProvider::DefaultReference::reference)
		{
		}
	};
};
