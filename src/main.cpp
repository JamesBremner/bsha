#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include "geo.h"
#include <wex.h>
#include "cStarterGUI.h"

class cSolution
{
public:
    std::vector<geo::point_t> vBuilding;
    std::set<geo::point_t> sBuildingSolve;
    std::set<geo::line_t> sLinkSolve;
    std::vector<geo::point_t> vStation;
    int myBuildingCountRequired;
    int myMinDistance;

    cSolution();
    void generateRandom();
    void solve();
    void draw(wex::shapes &S);

    void add( const geo::line_t& link);
    void add( const geo::point_t& building );
    bool isEnough();
};

class cGUI : public cStarterGUI
{
public:
    cGUI()
        : cStarterGUI(
              "Starter",
              {50, 50, 1000, 1000}),
          lb(wex::maker::make<wex::label>(fm))
    {
        lb.move(50, 50, 100, 30);
        lb.text("");

        fm.events().draw(
            [&](PAINTSTRUCT &ps)
            {
                wex::shapes S(ps);
                mySolution.draw(S);
            });

        show();
        run();
    }

private:
    wex::label &lb;
    cSolution mySolution;
};

cSolution::cSolution()
{
    generateRandom();
    solve();
}
void cSolution::generateRandom()
{
    myBuildingCountRequired = 5;
    myMinDistance = 5;

    const int maxloc = 800;

    srand(time(NULL));
    int countStationInit = rand() % 15 + 10;

    int countBuildingInit = rand() % 15 + 10;

    for (int k = 0; k < countBuildingInit; k++)
    {
        vBuilding.push_back(geo::point_t({rand() % maxloc + 100,
                                          rand() % maxloc + 100}));
    }
    for (int k = 0; k < countStationInit; k++)
    {
        vStation.push_back(geo::point_t({rand() % maxloc + 100,
                                         rand() % maxloc + 100}));
    }
}
void cSolution::solve()
{
    for (auto &b1 : vBuilding)
    {
        for (auto &b2 : vBuilding)
        {
            if (b1.first == b2.first && b1.second == b2.second)
                continue;
            for (auto &s : vStation)
            {
                // check distance from station to link between b1 and b2
                if (
                    geo::distance(
                        geo::line_t({b1, b2}),
                        s) < myMinDistance)
                {
                    
                    add(b1);
                    add(b2);
                    add(geo::line_t({b1, b2}));
                    break;
                }
            }
            if ( isEnough() )
                break;
        }
        if (isEnough() )
            break;
    }
}
bool cSolution::isEnough()
{
    return sBuildingSolve.size() >= myBuildingCountRequired;
}
void cSolution::add( const geo::line_t& link)
{
    sLinkSolve.insert( link );
}
 void cSolution::add( const geo::point_t& building )
 {
     sBuildingSolve.insert( building );
 }
void cSolution::draw(wex::shapes &S)
{
    S.fill();
    S.penThick(2);
    S.color(0xFF0000);
    for (auto &p : sBuildingSolve)
        S.circle(p.first, p.second, 20);
    S.color(0x0000ff);
    for (auto &p : vStation)
        S.circle(p.first, p.second, 20);
    S.color(0x000000);
    for (auto &l : sLinkSolve)
        S.line({l.first.first, l.first.second,
                l.second.first, l.second.second});
}

main()
{
    cGUI theGUI;

    return 0;
}
