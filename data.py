
# theta, fi -angles in spherical coordinate system
# i, amplitude, width, theta, fi
data = [
[1, -2.500, 0.200, 0.600, 3.700],
[2, -2.000, 0.150, 0.650, 6.300],
[3, 4.000, 0.300, 0.150, 5.000],
[4, 0.656, 0.080, 1.523, 4.280],
[5, 1.609, 0.341, 1.662, 4.899],
[6, 0.696, 0.303, 1.753, 3.963],
[7, 1.753, 0.488, 1.404, 5.777],
[8, 0.429, 0.276, 0.132, 5.655],
[9, 1.659, 0.862, 1.831, 3.974],
[10, 1.222, 0.568, 1.291, 4.539],
[11, 1.302, 0.402, 0.020, 1.968],
[12, 1.685, 0.743, 2.494, 1.141],
[13, 1.287, 0.800, 1.438, 3.046],
[14, 0.249, 0.282, 0.780, 2.869],
[15, 0.304, 0.443, 1.609, 0.611],
[16, 0.656, 0.430, 1.361, 4.123],
[17, 0.057, 0.601, 2.260, 2.854],
[18, 1.337, 0.236, 2.245, 2.135],
[19, 0.075, 0.813, 0.561, 5.211],
[20, 0.652, 0.776, 2.232, 4.565],
[21, 0.392, 0.453, 1.741, 4.825],
[22, 0.014, 0.565, 0.860, 3.719],
[23, 0.111, 0.484, 1.648, 0.490],
[24, 0.884, 0.160, 2.867, 5.354]
]

import numpy as np
import math as mt

class Coordinates:
	def __init__(self):
		self.x = None
		self.y = None
		self.z = None
		self.r = None
		self.theta = None
		self.fi = None

	def initSpherical(self, r, theta, fi):
		self.r = r
		self.theta = theta
		self.fi = fi
		self.x = self.r * mt.sin(self.theta) * mt.cos(self.fi)
		self.y = self.r * mt.sin(self.theta) * mt.sin(self.fi)
		self.z = self.r * mt.cos(self.theta)

	def initCartesian(self, x, y, z):
		self.x = x
		self.y = y
		self.z = z
		self.r = mt.sqrt(self.x**2 + self.y**2 + self.z**2)
		self.theta = mt.arccos(self.z/self.r)
		self.fi = mt.arctan(self.y/self.x)

	def getSpherical(self):
		return self.r, self.theta, self.fi

	def getCartesian(self):
		return self.x, self.y, self.z

class Gaussian3D:
	def __init__(self, amplitude, width, theta, fi, size, step):
		#angles in degrees
		self.amplitude = amplitude
		self.width = width
		self.theta = theta
		self.fi = fi
		self.r = self.getR()
		self.cords = Coordinates()
		self.cords.initSpherical(self.r, self.theta, self.fi)
		self.size = size
		self.step = step

	def getR(self):
		# return 10
		return self.amplitude / mt.sin((90 * mt.pi / 180) - self.theta)

	def gaussianFunction3D(self, x, y):
		# print(self.cords.x**2 + self.cords.y**2)
		return self.amplitude * mt.exp(-((x + self.cords.x)**2 + (y + self.cords.y)**2)/(2 * self.width**2))

	def getGaussianData(self):
		X = np.arange(-self.size/2, self.size/2, self.step)
		Y = np.arange(-self.size/2, self.size/2, self.step)
		Z = []
		i = 0
		for x in X:
			Z.append([])
			for y in Y:
				Z[i].append(self.gaussianFunction3D(x, y))
			i+=1

		return np.array(Z)
