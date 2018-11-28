import matplotlib
matplotlib.use("MacOSX")

import matplotlib.pyplot as plt
import matplotlib.contour as cont
import matplotlib.cm as cm


class FIFOReader:
    def __init__(self, path):
        self.path = path
        self.open()
    
    def open(self):
        f = open(self.path, "r")
        self.data = f.read()
        f.close()
        if len(self.data) == 0:
            exit(0)
        return self.data

    def parsePlane(self):
        pass

    def parseSimulationData(self):
        pass

if __name__ == "__main__":
    f = FIFOReader("plotFIFO")
    print(f.data)
