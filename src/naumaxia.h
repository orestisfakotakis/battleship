#ifndef NAUMAXIA_H
#define NAUMAXIA_H

#include "cell.h"
#include <vector>

class Naumaxia
{
    typedef std::vector<std::vector<Cell> > CellGrid;

    enum CellAttribute
    {
        THISAUROS,
        LIMANI,
        KAIROS,
        KARAVI
    };

public:
    Naumaxia(int rows, int cols, int num_ships);
    void setWeatherThreshold(int thres);
    void setTreasureTarget(int Tar);
    void play();
    bool validLocation(int row, int col) const;
    std::vector<Cell*> getNeighbourCells(const int row, const int col);
    std::vector<Ship*> getNeighbours(const int row, const int col);
    std::vector<Coords> getFreeNeigbourCells(const int row, const int col);
	Cell* getCell(const int row, const int col);

private: // Private Data
    CellGrid map;
    std::vector<Ship*> karavia;
    int rows, cols, num_ships;
    int weather_threshold;
    unsigned round_counter;
    int target_treasure;

private: // Private Methods
    int menu();
    void step();
    bool alive();
    void metakinisi();
    void leitourgia();
    int getActiveShipNumber ();
    void populateMap ();
    void initMap ();
    void printMap (CellAttribute);
    void newRoundActions ();
    void updateWeather ();
    void removeDeadShips ();
};

#endif // NAUMAXIA_H
