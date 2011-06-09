#pragma once

namespace Reindeer
{
	class ContentWalker;

	class Layer
	{
	public:
		class Content
		{
			public:
				virtual void render(ContentWalker &walker) = 0;
				virtual void deallocate(ContentWalker &walker) = 0;
		};

	private:
		void *serialized;
		Content *serialized_end;

	public:
		Layer(void *serialized, size_t size);
		~Layer();
		
		void append(Content *content);
		void render();
	};
};
