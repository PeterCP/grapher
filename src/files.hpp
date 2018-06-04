#pragma once

#include <string>
#include "Graph.hpp"

void SaveToFile(const Graph & graph, const std::string & path);

Graph LoadFromFile(const std::string & path);
