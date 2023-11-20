#ifndef CCU_H_
#define CCU_H_

const double EARTH_RADIUS = 6371; // in kilometers

static double deg2rad(double deg_in);

static double rad2deg(double rad_in);

static double bearingFunc(double lat1,
													double lon1,
													double lat2,
													double lon2);

void GIS2Radar(double *range,
	            double *bearing1,
              double *bearing2,
              double lat1,
              double lon1,
              double lat2,
              double lon2);

void RtoG (double range,
          double bearing1,
          double lat1,
          double lon1,
          double *lat2,
          double *lon2,
          double *bearing2);

#endif // CCU_H_
