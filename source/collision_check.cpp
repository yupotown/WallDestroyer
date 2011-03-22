
#include "collision_check.h"

bool CollisionCheck(const Gfx::BoxRegion& a, const Gfx::BoxRegion& b)
{
	return (
		a.x < b.x + static_cast<int>(b.width) &&
		b.x < a.x + static_cast<int>(a.width) &&
		a.y < b.y + static_cast<int>(b.height) &&
		b.y < a.y + static_cast<int>(a.height)
		);
}
