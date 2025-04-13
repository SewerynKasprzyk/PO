#pragma once
#include "ObiektSISO.h"
#include <vector>
#include <queue>
class ModelARX :
    public ObiektSISO
{
	std::vector<double> a; // wspó³czynniki a
	std::vector<double> b; // wspó³czynniki b

	std::queue<double> x; // bufor wejœciowy
	std::queue<double> y; // bufor wyjœciowy

	unsigned k; // rzêd opóŸnienia
};

