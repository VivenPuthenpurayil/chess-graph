#pragma once
#include "graph.h"
#include <map>
#include <stack>
#include <iostream>
#include <algorithm>

std::vector<int> tarjans(const Graph& g);

void tarjans_(int v, const Graph& g, std::vector<int> & lowlink, std::stack<int> & ll_stack, std::vector<bool> & on_stack, std::vector<bool> &visited, int & id, std::vector<int> & ids);

int num_scc(std::vector<int> lowlink);

int num_large_scc(std::vector<int> lowlink, int size);

int max_size_scc(std::vector<int> lowlink);

int average_degree(const Graph& g);

int num_edges(const Graph& g); 