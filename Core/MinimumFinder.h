#ifndef __MINIMUM_FINDER_H__
#define __MINIMUM_FINDER_H__

#include "Plane.h"

namespace GNEB
{
	class MinimumFinder
	{
	public:
		MinimumFinder();
		std::deque<Point> findMinima();
	};
}

#endif //__MINIMUM_FINDER_H__
