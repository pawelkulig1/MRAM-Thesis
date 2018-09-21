import numpy as np
import matplotlib
matplotlib.use("MacOSX")
import matplotlib.pyplot as plt
import matplotlib.contour as cont
import matplotlib.cm as cm
# from data import *
import time as tm
import dataGenerator as dg


chains = []
chain = []

x = True

# print(size)

def parseVector(vector):
	vector = vector[1:-1]
	vector = vector.split(",")
	tempVec = []
	print(vector)
	for i in range(2):
		try:
			tempVec.append(float(vector[i]))
		except:
			print("cannot parse: ", vector)
	return tempVec

def getXYArray(arr, poz=0):
	# print("ARR:", arr)
	if len(arr[0]) == 1 and poz != 0:
		return 0, 0
	X = []
	Y = []
	for el in arr:
		# print("EL: ", el)
		X.append(el[poz][0])
		Y.append(el[poz][1])

	return X, Y	

def readFromPipe(name):
	f = open(name, "r")
	data = f.read()
	f.close()
	if len(data) == 0:
		return False
	return data

x = True
data = []
for i in range(30):
	x = readFromPipe("plotFIFO")

	# print("' ", x, "'")
	if x == ";|;|;|" or x == False:
		break
	data.append(x)

print("data[1]:", data[1])

def parseCords(cords):
	cords = cords.split(",")
	return float(cords[0]), float(cords[1])

def parseToDict(one):
	temp = one.split(":")
	try:
		return temp[0], temp[1]
	except:
		print("exception: ", one)


for i, e in enumerate(data):
	tempData = e.split(";")
	Points = []
	# print(tempData)
	for el in tempData:
		if el == "|":
			continue
		key, val = parseToDict(el)
		if key == "coords":
			Points.append([parseCords(val)])
		if key == "deriv":
			Points[-1].append(parseCords(val))
		if key == "spring":
			Points[-1].append(parseCords(val))


	# ['GTK', 'GTKAgg', 'GTKCairo', 'MacOSX', 'Qt4Agg', 'Qt5Agg', 'TkAgg', 'WX', 'WXAgg', 'GTK3Cairo', 'GTK3Agg', 'WebAgg', 'nbAgg', 'agg', 'cairo', 'gdk', 'pdf', 'pgf', 'ps', 'svg', 'template']

	# X = np.arange(-5, 5, 0.1)
	# Y = np.arange(-5, 5, 0.1)
	# Z = np.zeros((len(X), len(Y)))

	# for i, line in enumerate(data):
	# 	Gaussian = Gaussian3D(line[1], line[2], line[3], line[4], 10, 0.1)
	# 	Z += Gaussian.getGaussianData()

	# X, Y = np.meshgrid(X, Y)

	p = dg.Plane(-5, 5, 0.1)
	p.generatePlane()
	
	plt.subplot(311)
	# plt.contourf(X, Y, Z, cmap=cm.RdYlGn_r)
	plt.contourf(*p.exportPlotData(), cmap=cm.RdYlGn_r)
	plt.scatter(*getXYArray(Points), color="r")
	plt.xlim(-5, 5)

	plt.subplot(312)
	plt.title("deriv")
	# plt.contourf(X, Y, Z, cmap=cm.RdYlGn_r)
	plt.contourf(*p.exportPlotData(), cmap=cm.RdYlGn_r)
	Points = Points[1:-1]
	plt.scatter(*getXYArray(Points), color="r")
	# # plt.quiver(*getXYArray(Points),0, *getXYArray(Points, 1),0, scale = 1)
	# print("second plot: ", Points[1:-1], Points)
	
	plt.quiver(*getXYArray(Points), *getXYArray(Points, 1), units="xy", scale=1)
	plt.xlim(-5, 5)	
	plt.ylim(-5, 5)	

	plt.subplot(313)
	plt.title("spring force")
	# plt.contourf(X, Y, Z, cmap=cm.RdYlGn_r)
	plt.contourf(*p.exportPlotData(), cmap=cm.RdYlGn_r)
	# Points = Points[1:-1]
	plt.scatter(*getXYArray(Points), color="r")
	plt.quiver(*getXYArray(Points), *getXYArray(Points, 2), units="xy")
	plt.xlim(-5, 5)
	plt.ylim(-5, 5)
	
	plt.show()
