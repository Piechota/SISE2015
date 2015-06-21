#ifndef _GRAOHRENDERER_H_
#define _GRAOHRENDERER_H_

class Graph;

class GraphRenderer
{
public:
	GraphRenderer();
	~GraphRenderer();

	static void RenderBackground();
	static void RenderGraph(Graph* const graph);
};

#endif