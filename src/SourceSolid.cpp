#include "SourceSolid.hpp"

namespace Reindeer
{
	const char *SourceSolid::vertex_code = "";
	const char *SourceSolid::vertex_main = "";

	const char *SourceSolid::fragment_code = "uniform vec4 source_color;";
	const char *SourceSolid::fragment_main = "gl_FragColor = source_color;";
};
