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
                std::cout << "station distance "
                    << s.first <<" "<< s.second <<"\n"
                    << b1.first <<" "<< b1.second <<", "
                    << b2.first <<" "<< b2.second << " d= "
                                    << geo::distance(
                        geo::line_t({b1, b2}),
                        s) << "\n";

                if (
                    geo::distance(
                        geo::line_t({b1, b2}),
                        s) < myMinDistance)
                {
                    
                    sBuildingSolve.insert(b1);
                    sBuildingSolve.insert(b2);
                    sLinkSolve.insert(geo::line_t({b1, b2}));
                    std::cout << "inserted " << sBuildingSolve.size()
                    <<" "<< sLinkSolve.size() << "\n";
                    break;
                }
            }
            if (sBuildingSolve.size() >= myBuildingCountRequired)
                break;
        }
        if (sBuildingSolve.size() >= myBuildingCountRequired)
            break;
    }
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
