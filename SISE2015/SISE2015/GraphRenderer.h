#ifndef _GRAOHRENDERER_H_
#define _GRAOHRENDERER_H_

#include "Headers.h"

class GraphRenderer
{
public:
	GraphRenderer();
	~GraphRenderer();

	static void RenderGraph(Graph* const graph);
};

#endif