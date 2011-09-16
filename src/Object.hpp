#pragma once
#include <Prelude/CountedList.hpp>
#include "../include/Reindeer/Canvas.hpp"
#include "Buffer.hpp"
#include "ContentSerializer.hpp"

namespace Reindeer
{
	template<typename T> static T *buffer_quad(T *buffer, int x, int y, int x2, int y2)
	{
		*buffer++ = x;
		*buffer++ = y;

		*buffer++ = x2;
		*buffer++ = y;

		*buffer++ = x;
		*buffer++ = y2;

		*buffer++ = x2;
		*buffer++ = y;

		*buffer++ = x;
		*buffer++ = y2;

		*buffer++ = x2;
		*buffer++ = y2;

		return buffer;
	}
	
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

		GLshort *buffer_vertices(GLshort *buffer)
		{
			return buffer_quad(buffer, rect.x, rect.y, rect.x + rect.width, rect.y + rect.height);
		}
	};

	template<class Source, class Mask> class ObjectList:
		public Prelude::CountedList<Object<Source, Mask>>
	{
	public:
		typedef ObjectList Type;

		struct ListContent
		{
			size_t indices;
			Buffer<GL_ARRAY_BUFFER, GLshort> vertex_buffer;
		};

		ObjectList(RegionAllocator::ReferenceProvider::Reference allocator = RegionAllocator::ReferenceProvider::DefaultReference::reference)
		{
		}

		static void measure(Type &list, ContentMeasurer &measurer)
		{
			measurer.count_objects<ListContent>(1);
		}

		static void serialize(Type &list, ContentSerializer &serializer)
		{
			ListContent &content = serializer.write_object<ListContent>();

			content.indices = list.size * 6;
			
			GLshort *vertex_map = content.vertex_buffer.setup(content.indices * 2);
			
			for(auto i = list.begin(); i != list.end(); ++i)
			{
				auto &object = i();

				vertex_map = object.buffer_vertices(vertex_map);
			}

			content.vertex_buffer.unmap();

			gluRaiseErrors();
		}
		
		template<class T> static void render(ContentWalker &walker, T &static_data)
		{
			ListContent &content = walker.read_object<ListContent>();
			
			content.vertex_buffer.bind();
			glVertexAttribPointer(0, 2, GL_SHORT, GL_FALSE, 0, 0);

			glDrawArrays(GL_TRIANGLES, 0, content.indices);

			gluRaiseErrors();
		}
		
		static void deallocate(ContentWalker &walker)
		{
			ListContent &content = walker.read_object<ListContent>();

			content.~ListContent();
		}
	};
};
