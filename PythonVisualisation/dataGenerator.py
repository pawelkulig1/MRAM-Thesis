#amplitude, width, x, y

import matplotlib
matplotlib.use("MacOSX")
import matplotlib.pyplot as plt
import matplotlib.contour as cont
import matplotlib.cm as cm
import numpy as np
import math as mt
from mpl_toolkits.mplot3d import Axes3D

class Plane:
	def __init__(self, dmin, dmax, dd):
		self.dmin = dmin
		self.dmax = dmax
		self.dd = dd
		self.data = \
		[
			[5, 	1,		0, 		0],
			[-1,    1,	       -2, 	        0],
			[-1,    1,		2, 		0],
			[1,   	1,		0,		1],
			[-1, 	1,		0,		-1],
                        [3,     1,              2,             -1]
			# [-1,	1,		2, 		0]
		]

	def getPointXY(self, x, y):
		value = 0
		for i, _ in enumerate(self.data):
			value += self.data[i][0] * mt.exp(-((x + self.data[i][2])**2 + \
				(y + self.data[i][3])**2)/(2 * self.data[i][1]**2))
		return value

	def generatePlane(self):
		self.X = np.arange(self.dmin, self.dmax, self.dd)
		self.Y = np.arange(self.dmin, self.dmax, self.dd)
		self.Z = np.zeros((len(self.X), len(self.Y)))
		xnum = 0
		ynum = 0
		for y in self.Y:
			xnum = 0
			for x in self.X:
				self.Z[ynum][xnum] = self.getPointXY(x, y)
				xnum += 1
			ynum += 1

	def plot(self):
		plt.contourf(self.X, self.Y, self.Z)
		plt.show()

	def exportPlotData(self):
		return self.X, self.Y, self.Z

	def exportData(self, filename):
		file = open(filename + ".dat", "w")





if __name__ == "__main__":
	p = Plane(-5, 5, 0.1)
	p.generatePlane();
	p.plot()
	xdata = np.arange(-5, 5, 0.5)




