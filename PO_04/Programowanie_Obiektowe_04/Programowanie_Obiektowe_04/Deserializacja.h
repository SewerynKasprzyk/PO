#pragma once
#include "Sygnal.h"
#include <memory>
#include <istream>

std::unique_ptr<Sygnal> deserializujSygnal(std::istream& in);