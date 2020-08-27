#ifndef EKSEREUNISIS_H
#define	EKSEREUNISIS_H

#include "ship.h"

class Eksereunisis : public Ship {
	static int counter_ekser_ships_created;
	static int counter_ekser_ships_died;
public:
    Eksereunisis(Naumaxia *n);
    virtual ~Eksereunisis();
    void leitourgia();
    const char* getCharCode(bool xtend) const {return xtend? "Eksereunitiko" : "E";}
private:

};

#endif	
