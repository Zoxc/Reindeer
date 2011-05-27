#pragma once
#include <Prelude/CountedList.hpp>
#include <Prelude/Region.hpp>
#include "../include/Canvas.hpp"

namespace Reindeer
{
	class Texture;

	class Object
	{
	public:
		Prelude::ListEntry<Object> entry;
	};

	class ObjectList:
		public Prelude::CountedList<Object>
	{
	public:
		ObjectList(RegionAllocator::ReferenceProvider::Reference allocator = RegionAllocator::ReferenceProvider::DefaultReference::reference)
		{
		}
	};

	enum Priority
	{
		PriorityTexture,
		PriorityRecord,
		PriorityUniform,
	};

	template<class K, class V, class T = Prelude::MapFunctions<K ,V>> class Map:
		public Prelude::Map<K, V *, RegionAllocator, T>
	{
	public:
		typedef typename Prelude::Map<K, V *, RegionAllocator, T> Parent;

		Map(typename RegionAllocator::ReferenceProvider::Reference allocator = RegionAllocator::ReferenceProvider::DefaultReference::reference) : Parent(2, allocator)
		{
		}
		
		V *get_create(K key)
		{
			return Parent::get_create(key, [&]() -> V * {
				RegionAllocator::ReferenceProvider::ReferenceClass region(get_allocator());
				return new (region.allocate(sizeof(V))) V(get_allocator());
			});
		}
			
	};
};
