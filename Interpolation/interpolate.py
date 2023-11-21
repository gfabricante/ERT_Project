import numpy as np
import scipy.interpolate
import matplotlib.pyplot as plt
import datetime

# domain specified by prompt
xMin, xMax = 121.0, 131.0
yMin, yMax = 10.0, 16.0

# reads in data
datmat = np.loadtxt("info.dat")
x = datmat.T[0] # longitude
y = datmat.T[1] # latitude
z = datmat.T[2] # point values

# incremented based on instructions
xi = np.linspace(xMin, xMax, 70)
yi = np.linspace(yMin, yMax, 50)
xi, yi = np.meshgrid(xi, yi) # creates grid that will be used during interpolation

# begin interpolation
interp = scipy.interpolate.Rbf(x, y, z, function='inverse') # create interpolator
zi = interp(xi, yi) # call and use interpolator along created grid

# begin plotting
plt.title('Point Locations')
plt.xlabel('longitude')
plt.ylabel('latitude')

plt.plot(x, y, 'r+') # plot original point values
plt.pcolor(xi, yi, zi, cmap='winter') # plot interpolated values

plt.xlim(xMin, xMax)
plt.ylim(yMin, yMax)

plt.colorbar()

# here we create unique name for file
today = datetime.datetime.today()
year = today.year
month = today.month
day = today.day
hour = today.hour
minute = today.minute
second = today.second

outputFilePath = "outputInterpolation_"+str(year)+"-"+str(month)+"-"+str(day)+"T"+str(hour)+"-"+str(minute)+"-"+str(second)+".png"
plt.savefig(outputFilePath)
plt.show()
