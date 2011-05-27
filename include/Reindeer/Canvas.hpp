#pragma once
#include <Prelude/Region.hpp>

namespace Reindeer
{
	typedef Prelude::Region<> RegionAllocator;

	class Operator
	{
	public:
		enum Type
		{
			Copy,
			Over
		};

		Operator(Type vaule) : value(value) {}

		operator Type() const
		{
			return value;
		}

	private:
		Type value;
	};
	
	class Source
	{
	public:
		enum Type
		{
			Solid,
			Texture,
			Count
		};

		Source(Type vaule) : value(value) {}

		operator Type() const
		{
			return value;
		}

	private:
		Type value;
	};

	class Mask
	{
	public:
		enum Type
		{
			None,
			Solid,
			Texture,
			Count
		};

		Mask(Type vaule) : value(value) {}

		operator Type() const
		{
			return value;
		}

	private:
		Type value;
	};
	
	class Canvas
	{
	private:
		RegionAllocator &region;

	public:
		Canvas(RegionAllocator &region) : region(region)
		{
		}
	};
};
