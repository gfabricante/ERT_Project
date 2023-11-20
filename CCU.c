#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "CCU.h"

static double deg2rad(double deg_in)
{
  return deg_in * (M_PI / 180.0);
}

static double rad2deg(double rad_in)
{
  return rad_in * (180.0 / M_PI);
}

static double bearingFunc(double lat1, double lon1, double lat2, double lon2)
{
  double deltaLon, Y, X, temp;

  deltaLon = lon2 - lon1;
  lat1 = lat1;
  lat2 = lat2;

  Y = cos(lat2) * sin(deltaLon);
  X = cos(lat1) * sin(lat2) - sin(lat1) * cos(lat2) * cos(deltaLon);

  temp = rad2deg(atan2(Y, X));
  if(temp < 0)
  {
    temp += 360;
  }

  return temp;
}

void GIS2Radar(double *range, double *bearing1, double *bearing2, double lat1, double lon1, double lat2, double lon2)
{
  double deltaLat, deltaLon, A, B;

  deltaLat = deg2rad(lat2 - lat1);
  deltaLon = deg2rad(lon2 - lon1);
  lat1 = deg2rad(lat1);
  lon1 = deg2rad(lon1);
  lat2 = deg2rad(lat2);
  lon2 = deg2rad(lon2);

  A = deltaLat / 2.0;
  B = deltaLon / 2.0;

  *range = 2 * EARTH_RADIUS * asin(sqrt( (sin(A) * sin(A)) + (sin(B) * sin(B)) * cos(lat1) * cos(lat2) ));
  *bearing1 = bearingFunc(lat1, lon1, lat2, lon2);
  *bearing2 = bearingFunc(lat2, lon2, lat1, lon1) - 180;
}

void RtoG (double range, double bearing1, double lat1, double lon1, double *lat2, double *lon2, double *bearing2)
{
  bearing1 = deg2rad(bearing1);
  lat1 = deg2rad(lat1);
  lon1 = deg2rad(lon1);

  *lat2 = rad2deg(asin(sin(lat1) * cos(range/EARTH_RADIUS) + cos(lat1) * sin(range/EARTH_RADIUS) * cos(bearing1)));
  *lon2 = rad2deg(lon1 + atan2(sin(bearing1) * sin(range/EARTH_RADIUS) * cos(lat1), cos(range/EARTH_RADIUS) - sin(lat1) * sin(deg2rad(*lat2))));
  *bearing2 = bearingFunc(deg2rad(*lat2), deg2rad(*lon2), lat1, lon1) - 180;
}

// Driver code
int main()
{
  double lat1 = 37;
  double lon1 = -75;
  double lat2 = 18;
  double lon2 = -66;

  double bearing1, bearing2, range;

  GIS2Radar(&range, &bearing1, &bearing2, lat1, lon1, lat2, lon2);

  printf("%f\n", range);
  printf("%f\n", bearing1);
  printf("%f\n", bearing2);

  RtoG(range, bearing1, lat1, lon1, &lat2, &lon2, &bearing2);

  printf("%f\n", lat2);
  printf("%f\n", lon2);
  printf("%f\n", bearing2);

	return 0;
}
