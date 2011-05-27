#pragma once
#include <Prelude/CountedList.hpp>
#include <Prelude/Region.hpp>
#include <Prelude/Map.hpp>
#include "../include/Reindeer/Canvas.hpp"

namespace Reindeer
{
	class Texture;

	template<class Source, class Mask> class Object
	{
	public:
		Prelude::ListEntry<Object> entry;
	};

	template<class Source, class Mask> class ObjectList:
		public Prelude::CountedList<Object<Source, Mask>>
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
		PriorityNone
	};

	template<class K, class V, class T = Prelude::MapFunctions<K ,V>> class Map:
		public Prelude::Map<K, V *, RegionAllocator, T>
	{
	public:
		typedef typename Prelude::Map<K, V *, RegionAllocator, T> Parent;

		Map(typename RegionAllocator::ReferenceProvider::Reference allocator = RegionAllocator::ReferenceProvider::DefaultReference::reference) : Parent(2, allocator)
		{
		}
		
		V &get_create(K key)
		{
			return *Parent::get_create(key, [&]() -> V * {
				RegionAllocator::ReferenceProvider::ReferenceClass region(this->Parent::get_allocator());
				return new (region.allocate(sizeof(V))) V(this->Parent::get_allocator());
			});
		}
			
	};
};
