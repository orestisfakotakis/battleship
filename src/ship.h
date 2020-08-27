#ifndef SHIP_H
#define	SHIP_H

#include "naumaxia.h"
#include <ostream>

class Ship {

    static int counter_shipes_created;
    static int counter_shipes_died;

private:
    int total_distance;
    int total_damage;

protected:
    Naumaxia *n;
    int taxitita;
    int apo8ema;
    int megisti_antoxi;
    int trexousa_antoxi;
    int row, col;

public:
    Ship(Naumaxia* n, int taxitita,int megisti_antoxi);
    virtual ~Ship();
     
    void set_taxutita(int speed);
    void set_row(int row_);
    void set_col(int col_);
    
    int get_taxutita();
    int get_apo8ema();
    int get_antoxi();
    int get_megisti_antoxi();
    int get_row();
    int get_col();

	void inc_apo8ema(int apoth);
	void dec_apo8ema(int apoth);
	void inc_antoxi(int stamina);
	void dec_antoxi(int stamina);
    
    virtual void metakinisi();
	virtual void leitourgia() = 0;
    virtual const char* getCharCode(bool extended=false) const = 0;
    virtual void info(std::ostream &os) const;

    static int get_total_created_counter() {return counter_shipes_created;}
    static int get_total_created_died() {return counter_shipes_died;}

    friend std::ostream& operator<<(std::ostream& os, const Ship& dt);
};

#endif
