#ifndef CCU_H_
#define CCU_H_

const double EARTH_RADIUS = 6371; // in kilometers

 // helper function
static double deg2rad(double deg_in);

// helper function
static double rad2deg(double rad_in);

// helper function
static void checkLat(double lat_in);

// helper function
static void checkLon(double lat_in);

// helper function
static double bearingFunc(double lat1_in,
													double lon1_in,
													double lat2_in,
													double lon2_in);

void GIS2Radar(double lat1_in,
	            double lon1_in,
              double lat2_in,
              double lon2_in,
              double *range_in,
              double *bearing1_in,
              double *bearing2_in);

void RtoG (double range_in,
          double bearing1_in,
          double lat1_in,
          double lon1_in,
          double *lat2_in,
          double *lon2_in,
          double *bearing2_in);

#endif // CCU_H_
