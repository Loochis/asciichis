//
// Created by loochis on 6/20/24.
//

#ifndef ASCIICHIS_VIEWMANAGER_H
#define ASCIICHIS_VIEWMANAGER_H

#include <vector>
#include <memory>
#include "asciichis.h"
#include "Drawables/drawable.h"

using namespace ASCIICHIS;
using namespace std;

class viewmanager {
public:
    static const int    FRAMERATE = 60;
    static const ulong  FRAMETIME_US = (ulong)(1000000.0 / (double)FRAMERATE);

    shared_ptr<asciirenderer> rend;
    vector<shared_ptr<drawable>> drawables;

    ulong time_us = 0;
    double speed = 1;

    viewmanager(shared_ptr<asciirenderer> &rend);

    void StartPlayback();
    void StopPlayback();

    void Update();

private:
    ulong d_time_us = 0;
    void ComputeFrame(double t);
};


#endif //ASCIICHIS_VIEWMANAGER_H
