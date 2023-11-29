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

static void checkLat(double lat_in)
{
  if (lat_in < -90.0 || lat_in > 90.0)
  {
    fprintf(stderr, "Error: Latitude is not in the specified range [-90.0, 90.0].\n");
    exit(EXIT_FAILURE);
  }
}

static void checkLon(double lat_in)
{
  if (lat_in < -180.0 || lat_in > 180.0)
  {
    fprintf(stderr, "Error: Longitude is not in the specified range [-180.0, 180.0].\n");
    exit(EXIT_FAILURE);
  }
}


// bearing function is meant to have radians inputted since it is used internally
// and GIS2Radar() & RtoG() already initially convert to radians, makes sense to convert once
static double bearingFunc(double lat1_in, double lon1_in, double lat2_in, double lon2_in)
{
  double deltaLon, Y, X, temp;

  deltaLon = lon2_in - lon1_in;

  Y = cos(lat2_in) * sin(deltaLon);
  X = cos(lat1_in) * sin(lat2_in) - sin(lat1_in) * cos(lat2_in) * cos(deltaLon);

  temp = rad2deg(atan2(Y, X));

  // make sure it is within [0.0, 360.0]
  if(temp < 0)
  {
    temp += 360;
  }

  return temp;
}

void GIS2Radar(double lat1_in, double lon1_in, double lat2_in, double lon2_in, double *range_in, double *bearingInit_in, double *bearingFinal_in)
{
  double deltaLat, deltaLon, A, B;

  // check inputs are within valid ranges
  checkLat(lat1_in);
  checkLon(lon1_in);
  checkLat(lat2_in);
  checkLon(lon2_in);

  // convert to radians
  deltaLat = deg2rad(lat2_in - lat1_in);
  deltaLon = deg2rad(lon2_in - lon1_in);
  lat1_in = deg2rad(lat1_in);
  lon1_in = deg2rad(lon1_in);
  lat2_in = deg2rad(lat2_in);
  lon2_in = deg2rad(lon2_in);

  // calculate constants for equation
  A = deltaLat / 2.0;
  B = deltaLon / 2.0;

  *range_in = 2 * EARTH_RADIUS * asin(sqrt( (sin(A) * sin(A)) + (sin(B) * sin(B)) * cos(lat1_in) * cos(lat2_in) )); // haversine equation
  *bearingInit_in = bearingFunc(lat1_in, lon1_in, lat2_in, lon2_in);
  *bearingFinal_in = bearingFunc(lat2_in, lon2_in, lat1_in, lon1_in) - 180;
}

void RtoG (double range_in, double bearingInit_in, double lat1_in, double lon1_in, double *lat2_in, double *lon2_in, double *bearingFinal_in)
{
  // check inputs are within valid ranges
  checkLat(lat1_in);
  checkLon(lon1_in);

  // convert to radians
  bearingInit_in = deg2rad(bearingInit_in);
  lat1_in = deg2rad(lat1_in);
  lon1_in = deg2rad(lon1_in);

  // we use the calculated lat2 and lon2 for calculating bearingFinal
  *lat2_in = rad2deg(asin(sin(lat1_in) * cos(range_in/EARTH_RADIUS) + cos(lat1_in) * sin(range_in/EARTH_RADIUS) * cos(bearingInit_in)));
  *lon2_in = rad2deg(lon1_in + atan2(sin(bearingInit_in) * sin(range_in/EARTH_RADIUS) * cos(lat1_in), cos(range_in/EARTH_RADIUS) - sin(lat1_in) * sin(deg2rad(*lat2_in))));
  *bearingFinal_in = bearingFunc(deg2rad(*lat2_in), deg2rad(*lon2_in), lat1_in, lon1_in) - 180;
}

// Driver code for demonstration
int main()
{
  double lat1 = 37;
  double lon1 = -75;
  double lat2 = 18;
  double lon2 = -66;

  double bearingInit, bearingFinal, range;

  GIS2Radar(lat1, lon1, lat2, lon2, &range, &bearingInit, &bearingFinal);

  printf("\nThe shortest distance between the two coordinates is %.2fkm\n", range);
  printf("wih an initial bearing of %.2f degress\n", bearingInit);
  printf("and final bearing of %.2f degress\n", bearingFinal);

  RtoG(range, bearingInit, lat1, lon1, &lat2, &lon2, &bearingFinal); // note: calculated range and bearingInit from earlier are used here for demonstration purposes

  printf("\nThe calculated coordinates are lat: %.2f and lon: %.2f\n", lat2, lon2);
  printf("with a final bearing of %.2f degress\n\n", bearingFinal);

	return 0;
}
