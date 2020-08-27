#ifndef EPISKEUASTIKO_H
#define	EPISKEUASTIKO_H

#include "ship.h"

class Episkeuastiko : public Ship {
	static int counter_epis_ships_created;
	static int counter_epis_ships_died;
public:
    Episkeuastiko(Naumaxia *n);
    virtual ~Episkeuastiko();
    void leitourgia();
    const char* getCharCode(bool xtend) const {return xtend? "Episkeyastiko" : "X";}
    void info(std::ostream& os) const;

private:
    int total_treasure_acquired;
};

#endif
