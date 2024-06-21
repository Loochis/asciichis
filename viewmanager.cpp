//
// Created by loochis on 6/20/24.
//

#include "viewmanager.h"
#include <chrono>
#include <thread>
#include <algorithm>


using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

viewmanager::viewmanager(shared_ptr<asciirenderer> &rend) : rend(rend) {

}

void viewmanager::StartPlayback() {
    speed = 1;
}

void viewmanager::StopPlayback() {
    speed = 0;
}

void viewmanager::Update() {
    auto start_t = high_resolution_clock::now();

    //-- START frame --//

    rend->flushscreen();
    for (int i = 0; i < drawables.size(); i++)
        (drawables[i])->Draw(time_us);
    rend->pushscreen();

    //-- END frame --//

    auto end_t = chrono::high_resolution_clock::now();
    d_time_us = chrono::duration_cast<chrono::microseconds>(end_t - start_t).count();

    // keep accurate time
    time_us += (ulong)((double)d_time_us * speed);

    // Add frame delay if compute is too fast
    if (d_time_us < FRAMETIME_US) {
        time_us += FRAMETIME_US - d_time_us;
        sleep_for(microseconds(FRAMETIME_US - d_time_us));
    } else {
        time_us += 2000;
        sleep_for(microseconds(2000));
    }
}

void viewmanager::ComputeFrame(double t) {

}
