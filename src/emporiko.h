#ifndef EMPORIKO_H
#define	EMPORIKO_H

#include "ship.h"

class Emporiko : public Ship {
	static int counter_empor_ships_created;
	static int counter_empor_ships_died;
public:
    Emporiko(Naumaxia *n);
    virtual ~Emporiko();
    void leitourgia();
    const char* getCharCode(bool xtend) const {return xtend? "Emporiko" : "M";}
    void info(std::ostream& os) const;

private:
    int total_treasure_acquired;
};

#endif	
