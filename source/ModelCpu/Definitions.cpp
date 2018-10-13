#include "Cluster.h"
#include "Cell.h"

#include "Definitions.h"

std::size_t CellClusterHash::operator()(Cluster* const& s) const
{
	return s->getId();
}

std::size_t CellHash::operator()(Cell* const& s) const
{
	return s->getId();
}
