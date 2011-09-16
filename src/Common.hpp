#pragma once
#include <Prelude/Region.hpp>
#include <Prelude/Map.hpp>
#include "GL.hpp"
#include "../include/Reindeer/Canvas.hpp"

namespace Reindeer
{
	class Texture;

	enum Priority
	{
		PriorityTexture,
		PriorityRecord,
		PriorityUniform,
		PriorityNone
	};
	
	struct Rect
	{
		int x;
		int y;
		int width;
		int height;
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

	void initialize(size_t width, size_t height);
};
