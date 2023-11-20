import numpy as np
import scipy.interpolate
import matplotlib.pyplot as plt

xMin, xMax = 121.0, 131.0
yMin, yMax = 10.0, 16.0

datmat = np.loadtxt("info.dat")
x = datmat.T[0]
y = datmat.T[1]
z = datmat.T[2]

xi = np.linspace(xMin, xMax, 70)
yi = np.linspace(yMin, yMax, 50)
xi, yi = np.meshgrid(xi, yi)

interp = scipy.interpolate.Rbf(x, y, z, function='inverse')
zi = interp(xi, yi)

plt.plot(x, y, 'r+')
plt.pcolor(xi, yi, zi, cmap='winter')
plt.xlim(xMin, xMax)
plt.ylim(yMin, yMax)
plt.colorbar()

plt.show()
