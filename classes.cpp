#include "classes.h"

//Passenger
	void Passenger::bookPlane(Plane airp)
    {
        credit -= airp.price;
	}
	void Passenger::cancelPlane(Plane airp)
    {
        credit += airp.price;
	}
    bool Passenger::checkAvail(Plane airp)
    {
        if(airp.availability) return true;
        return false;
    }
