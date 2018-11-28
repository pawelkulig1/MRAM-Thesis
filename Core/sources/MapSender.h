#include "Pipe.h"
#include <functional>

class MapSender
{
    MapSender(std::function<double (double, double)> func);
    void setConstraints(double xmin, double xmax, double ymin, double ymax, double dx, double dy);
    void sendMap();

};
