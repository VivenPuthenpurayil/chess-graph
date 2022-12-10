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

std::vector<int> purge_small_ll(std::vector<int> lowlink, int size);

float average_degree(const Graph& g);

int max_degree(const Graph& g);

int num_edges(const Graph& g); 

std::vector<std::vector<int>> weaklyconnected(const Graph& g);
void findConnected(int node, std::vector<bool>& visited, std::vector<int>& component, Graph g);