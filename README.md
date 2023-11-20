# ERT_Project


### 1. Code_Optimization
- Our initial benchmark of the original code resulted in an elapsed time of 276.42 seconds
- We were able to mitigate this time by introducing two things:
  - a header file defining all of the constants
  - declaring our variables as global variables, allowing us to declare the variables once rather than redeclaring it repeatedly in the nested loop
- An interesting roadblock we ran into:
  - At first we defined any variable that could be defined before the loop with a helper function. Unfortunately, the issue with that is that it required the user to invoke calculateConstants() before the loop in their source code
  - This meant the user would have to manually call calculateConstants() before calling function_j()
  - Assuming we only want the user to worry about function_j(), we have to redefine variables internally (consequently in the nested loop)
- After implementing these changes and keeping in mind the constraints, the new code had an elapsed time of 261.81 seconds

***note:*** There were some conflicting issues with GPROF and Mac OS so as a result, we were forced to take a more "archaic" approach to measure our benchmarks. 


### 2. Coordinate_Transformation
- Here we have 2 functions that convert radar coordinates (bearing, range) to GIS coordinates (lat, lon) and vice versa
- GIS2Radar() reads in initial & final coordinates and outputs the following:
  - the great-circle distance between the coordinates
  - initial and final bearing
- RtoG() will read in an intial coordinates, range, & intial bearing and output the following:
  - final coordinates
  - final bearing

***note:*** For the sake of the demonstration, we start with known initial and final coordinates and use GIS2Radar(). We then use the calculated intial bearing & calculated range as our input parameters (along with the known intial coordinate) for RtoG().


### 3. Data_Collection
- CollectData.py will allow the user to collect data from a NOAA data source
- The collected data will then be saved to a file that will be categorized first by source, then by local time collected

Example:
```
$ python3 CollectData.py https://services.swpc.noaa.gov/products/geospace/propagated-solar-wind-1-hour.json

$ JSON data from propagated-solar-wind-1-hour has been written to propagated-solar-wind-1-hour_2023-11-20T11-22-24.txt
```



### 4. Interpolation
- Interpolate.py will interpolate given grid points to a specified structured grid
- We opted for a radially basis function, specifically Inverse Multiquadratic, for our interpolator
  - Inverse Multiquadratic was selected based on testing and visual observations & comparisons with other functions
  - This function appeared to be effective for scattered data, while not being overly aggressive or too passive
 - The produced graph will be saved and sorted by named first, then by local time created


![output of python script](https://github.com/gfabricante/ERT_Project/blob/main/Interpolation/outputInterpolation_2023-11-20T15-23-34.png)
