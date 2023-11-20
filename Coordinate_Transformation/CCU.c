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

static void checkLat(double lat)
{
  if (lat < -90.0 || lat > 90.0)
  {
    fprintf(stderr, "Error: Latitude is not in the specified range [-90.0, 90.0].\n");
    exit(EXIT_FAILURE);
  }
}

static void checkLon(double lat)
{
  if (lat < -180.0 || lat > 180.0)
  {
    fprintf(stderr, "Error: Longitude is not in the specified range [-180.0, 180.0].\n");
    exit(EXIT_FAILURE);
  }
}


// bearing function is meant to have radians inputted since it is used internally
// and GIS2Radar() & RtoG() already initially convert to radians, makes sense to only do it once
static double bearingFunc(double lat1, double lon1, double lat2, double lon2)
{
  double deltaLon, Y, X, temp;

  deltaLon = lon2 - lon1;
  lat1 = lat1;
  lat2 = lat2;

  Y = cos(lat2) * sin(deltaLon);
  X = cos(lat1) * sin(lat2) - sin(lat1) * cos(lat2) * cos(deltaLon);

  temp = rad2deg(atan2(Y, X));

  // make sure it is within [0.0, 360.0]
  if(temp < 0)
  {
    temp += 360;
  }

  return temp;
}

void GIS2Radar(double *range, double *bearingInit, double *bearingFinal, double lat1, double lon1, double lat2, double lon2)
{
  double deltaLat, deltaLon, A, B;

  // check inputs are within valid ranges
  checkLat(lat1);
  checkLon(lon1);
  checkLat(lat2);
  checkLon(lon2);

  // convert to radians
  deltaLat = deg2rad(lat2 - lat1);
  deltaLon = deg2rad(lon2 - lon1);
  lat1 = deg2rad(lat1);
  lon1 = deg2rad(lon1);
  lat2 = deg2rad(lat2);
  lon2 = deg2rad(lon2);

  // calculate constants for equation
  A = deltaLat / 2.0;
  B = deltaLon / 2.0;

  *range = 2 * EARTH_RADIUS * asin(sqrt( (sin(A) * sin(A)) + (sin(B) * sin(B)) * cos(lat1) * cos(lat2) )); // haversine equation
  *bearingInit = bearingFunc(lat1, lon1, lat2, lon2);
  *bearingFinal = bearingFunc(lat2, lon2, lat1, lon1) - 180;
}

void RtoG (double range, double bearingInit, double lat1, double lon1, double *lat2, double *lon2, double *bearingFinal)
{
  // check inputs are within valid ranges
  checkLat(lat1);
  checkLon(lon1);

  // convert to radians
  bearingInit = deg2rad(bearingInit);
  lat1 = deg2rad(lat1);
  lon1 = deg2rad(lon1);

  // we use the calculated lat2 and lon2 for calculating bearingFinal
  *lat2 = rad2deg(asin(sin(lat1) * cos(range/EARTH_RADIUS) + cos(lat1) * sin(range/EARTH_RADIUS) * cos(bearingInit)));
  *lon2 = rad2deg(lon1 + atan2(sin(bearingInit) * sin(range/EARTH_RADIUS) * cos(lat1), cos(range/EARTH_RADIUS) - sin(lat1) * sin(deg2rad(*lat2))));
  *bearingFinal = bearingFunc(deg2rad(*lat2), deg2rad(*lon2), lat1, lon1) - 180;
}

// Driver code for demonstration
int main()
{
  double lat1 = 37;
  double lon1 = -75;
  double lat2 = 18;
  double lon2 = -66;

  double bearingInit, bearingFinal, range;

  GIS2Radar(&range, &bearingInit, &bearingFinal, lat1, lon1, lat2, lon2);

  printf("\nThe shortest distance between the two coordinates is %.2fkm\n", range);
  printf("wih an initial bearing of %.2f degress\n", bearingInit);
  printf("and final bearing of %.2f degress\n", bearingFinal);

  RtoG(range, bearingInit, lat1, lon1, &lat2, &lon2, &bearingFinal); // note: calculated range and bearingInit from earlier are used here for demonstration purposes

  printf("\nThe calculated coordinates are lat: %.2f and lon: %.2f\n", lat2, lon2);
  printf("with a final bearing of %.2f degress\n\n", bearingFinal);

	return 0;
}
