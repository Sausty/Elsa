#include "Math.h"

#include <math.h>
#include <stdlib.h>
#include <time.h>

static b8 RandSeeded = false;

f32 Sin(f32 x)
{
	return sinf(x);
}

f32 Cos(f32 x)
{
	return cosf(x);
}

f32 Tan(f32 x)
{
	return tanf(x);
}

f32 Acos(f32 x)
{
	return acosf(x);
}

f32 Asin(f32 x)
{
	return asinf(x);
}

f32 Atan(f32 x)
{
	return atanf(x);
}

f32 Sqrt(f32 x)
{
	return sqrtf(x);
}

f32 Abs(f32 x)
{
	return fabsf(x);
}

b8 IsPowerOf2(u64 value)
{
	return (value != 0) && ((value & (value - 1)) == 0);
}

i32 Random()
{
	if (!RandSeeded) {
		srand((u32)time(NULL));
		RandSeeded = true;
	}
	return rand();
}

i32 RandomInRange(i32 min, i32 max)
{
	if (!RandSeeded) {
		srand((u32)time(NULL));
		RandSeeded = true;
	}
	return (rand() % (max - min + 1)) + min;
}

f32 FRandom()
{
	return (float)Random() / (f32)RAND_MAX;
}

f32 FRandomInRange(f32 min, f32 max)
{
	return min + ((float)FRandom() / ((f32)RAND_MAX / (max - min)));
}