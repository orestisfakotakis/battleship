#ifndef PEIRATIKOI_H
#define	PEIRATIKOI_H

#include "defs.h"
#include "ship.h"

 
class Peiratiko : public Ship {

	static int counter_peir_ships_created;
	static int counter_peir_ships_died;

public:
    Peiratiko(Naumaxia *n);
    virtual ~Peiratiko();
    void leitourgia();
    const char* getCharCode(bool xtend) const {return xtend? "Peiratiko" : "P";}
    void info(std::ostream& os) const;

    int get_dinami();
    void set_dinami(int n);

private:
    int  dinami;
    int total_attacks;
};

#endif	
