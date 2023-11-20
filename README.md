# ERT_Project


### 1. Code_Optimization
- Our initial benchmark of the original code had an elapsed time of 276.42 seconds
- We were able to mitigate this time by introducing two things:
  - a header file defining all of the used constants
  - calculateConstants();
- The variables selected to be extracted from function_j() are independent from our inputs (f, fp, and fptilde)
- This allows us to declare and define our variables once, rather than repeatedly for each iteration of our nested loop, resulting in a minimized number of calcuations


### 2. Coordinate_Transformation
- Here we have 2 functions that convert radar coordinates (bearing, range) to GIS coordinates (lat, lon) and vice versa
- GIS2Radar() will read in initial & final coordinates and output the following:
  - the great-circle distance between the coordinates
  - initial and final bearing
- RtoG() will read in an intial coordinate, range, & intial bearing and output the following:
  - final coordinates
  - final bearing

***Note:*** for the sake of the demonstration, we start with known initial and final coordinates and use GIS2Radar(). We then use the calculated intial bearing & calculated range as our input parameters (along with the known intial coordinate) for RtoG().


### 3. Data_Collection
- This python script will allow the user to collect data from a NOAA data source by executing the following:
```
python3 CollectData.py EXACT_URL
```
Example:
```
python3 CollectData.py https://services.swpc.noaa.gov/products/geospace/propagated-solar-wind-1-hour.json
```
- The collected data will then be saved to a file that will be categorized first by source, then by local time collected

Example (continuing):
```
JSON data from propagated-solar-wind-1-hour has been written to propagated-solar-wind-1-hour_2023-11-20T11-22-24.txt
```



### 4. Interpolation
blah blah blah
