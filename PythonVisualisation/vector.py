import math as mt
class Vector():
	def __init__(self, x, y, z):
		self.x = x
		self.y = y
		self.z = z
		self.length = None


	def length(self):
		return mt.sqrt(x**2 + y**2 + z**2)

	def crossProduct(self):
		raise NotImplemented("Cross Product is not implemented yet.")

	@staticmethod
	def dotProduct(vec1, vec2):
		return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z

	@staticmethod
	def angleBetweenVectors(vec1, vec2):
		mt.acos((Vector.dotProduct(vec1, vec2) / (vec1.length * vec2.length)))

	@staticmethod
	def distanceBetweenVectors(vec1, vec2):
		return ((vec1.x - vec2.x)**2 + (vec1.y - vec2.y)**2 + (vec1.z - vec2.z)**2)**0.5


