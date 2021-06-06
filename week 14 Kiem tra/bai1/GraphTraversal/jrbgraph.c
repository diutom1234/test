#include "jrbgraph.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
Graph createGraph()
{
	Graph newGraph = make_jrb();
	return newGraph;
}

void addEdge_int(Graph graph, int v1, int v2)
{
	// do thi vo huong nen can co (v1 v2) va (v2 v1)
	// them canh v1 v2
	// check xem da co dinh tren cay chua
	JRB bn = jrb_find_int(graph, v1);
	if(bn==NULL) // neu chua co thi them vao
	{		
		JRB tree = make_jrb(); 
		jrb_insert_int(tree, v2, new_jval_i(1));
		jrb_insert_int(graph, v1, new_jval_v(tree));
	}
	else // dinh v1 da co tren cay
	{
		//node = jrb_find_int(g, v1);
		// them canh v1 v2
		JRB tree = (JRB) jval_v(bn->val);
		jrb_insert_int(tree, v2, new_jval_i(1));			
	}
	
	// them canh v2 v1
	bn = jrb_find_int(graph, v2);
	if(bn==NULL) // neu chua co thi them vao
	{
		JRB tree = make_jrb();
		jrb_insert_int(tree, v1, new_jval_i(1));
		jrb_insert_int(graph, v2, new_jval_v(tree));
	}
	else  // da co dinh v2 thi chi them canh v2 v1
	{
		JRB tree = (JRB) jval_v(bn->val);
		jrb_insert_int(tree, v1, new_jval_i(1));
	}
}

void addEdge_str(Graph graph, char* v1, char* v2)
{
	// do thi vo huong nen can co (v1 v2) va (v2 v1)
	// them canh v1 v2
	// check xem da co dinh tren cay chua
	JRB bn = jrb_find_str(graph, v1);
	if(bn==NULL) // neu chua co thi them vao
	{		
		JRB tree = make_jrb(); 
		jrb_insert_str(tree, strdup(v2), new_jval_i(1));
		jrb_insert_str(graph, strdup(v1), new_jval_v(tree));
	}
	else // dinh v1 da co tren cay
	{
		//node = jrb_find_int(g, v1);
		// them canh v1 v2
		JRB tree = (JRB) jval_v(bn->val);
		jrb_insert_str(tree, strdup(v2), new_jval_i(1));			
	}
	
}

int getAdjacentVertices_str (Graph graph, char* v, char output[10][10])
{
	JRB node = jrb_find_str(graph, v);
	JRB tree = (JRB) jval_v(node->val);
	int total = 0;   
	jrb_traverse(node, tree)
	{
		//output[total] = (char*)malloc(20*sizeof(char));
		//printf("key: %s\n", jval_s(node->key));
		strcpy(output[total],jval_s(node->key));
		total++;
	}    
	return total;
}

int getAdjacentVertices_int (Graph graph, int v, int* output)
{
	JRB node = jrb_find_int(graph, v);
	JRB tree = (JRB) jval_v(node->val);
	int total = 0;   
	jrb_traverse(node, tree)
	{
		output[total++] = jval_i(node->key);
	}    
	return total;
}

void dropGraph(Graph graph)
{
	JRB node;
	jrb_traverse(node, graph)
	{
		jrb_free_tree( jval_v(node->val) );
	}
    
}
