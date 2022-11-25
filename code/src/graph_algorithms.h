#pragma once
#include "graph.h"
#include <map>
#include <stack>
#include <iostream>

std::vector<int> tarjans(const Graph& g);

void tarjans_(int v, const Graph& g, std::vector<int> & lowlink, std::stack<int> & ll_stack, std::vector<bool> & on_stack, std::vector<bool> &visited);

int average_degree(const Graph& g);

int num_edges(const Graph& g); 