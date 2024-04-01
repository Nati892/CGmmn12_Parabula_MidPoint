#pragma once
#include <stdlib.h>
#include <random>

/// <summary>
/// Helper method for Random Float Number Generation in range
/// </summary>
/// <param name="start">the start of the range</param>
/// <param name="end">end of the range</param>
/// <returns>the random generated number</returns>
float RandInRange(float start, float end);


class Point2di
{
public:
	int x = 0;
	int y = 0;

	Point2di(int x_tmp, int y_tmp)
	{
		x = x_tmp;
		y = y_tmp;
	}


};
