#pragma once

#include <vector>
#include <string>

class Plane;

class Passenger
{
public:
    std::string username;
    std::string password;

    int credit;

    //Plane bookedPlanes;

public:

	void bookPlane(Plane airp); //books plane
    void cancelPlane(Plane airp); //cancels plane
    bool checkAvail(Plane airp); //checks availability
};

class Plane
{
public:
	const char* id;
	const char* direction;

	int price;
    bool availability;

public:
    Plane();
    Plane(const char* p_id,
          const char* p_direc,
          int p_price) : availability(true),
                         id(p_id),
                         direction(p_direc),
                         price(p_price){}

	friend Passenger;
};
