#ifndef CELL_H
#define	CELL_H

#include <cstdio>
#include <ostream>

struct Coords {
    int row;
    int col;
};

class Ship;

class Cell {
	
	int kairos;
	bool limani;
	bool thisauros;
    Ship *ship;
    Coords coords;

public:
	Cell() : kairos(0), limani(0), thisauros(0), ship(NULL) {}
	
	void set_kairos(int entasikairou);
	void set_limani(bool lim);
    void set_thisauros(bool thisa);
    void set_ship(Ship* ship);
    void set_coords(Coords coords_);
	
	int get_kairos();
	bool get_limani();
	bool get_thisauros();
	Ship* get_ship();
    Coords get_coords();
	
    bool hasShip() const { return ship==NULL? false: true; }
	
    friend std::ostream& operator<<(std::ostream& os, const Cell& dt);
};

#endif
