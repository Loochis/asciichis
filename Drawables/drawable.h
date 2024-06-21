//
// Created by loochis on 6/20/24.
//

#ifndef ASCIICHIS_DRAWABLE_H
#define ASCIICHIS_DRAWABLE_H

#define US_CONST 1000000

#include "../asciichis.h"
#include <cstdlib>
#include <cmath>
#include <memory>

using namespace ASCIICHIS;

static const char BOX_DRAW[][4] = {
    " ",
    "░",
    "▒",
    "▓",
    "█"
};

class drawable {
public:
    ulong start_time_us;
    ulong duration_us;

    // drawing parameters
    int seed = 0;
    asciirenderer::color channels;
    char drawchar[4];

    // Enums/Structs
    enum DrawMode { CONSTANT_CHAR, RANDOM_CHAR, FADE_BLOCK };

    struct vector_d {
        double x, y;
        vector_d() : x(0), y(0) {}
        vector_d(double xi, double yi) : x(xi), y(yi) {}
    };

    struct vector_i {
        int x, y;
        vector_i() : x(0), y(0) {}
        vector_i(int xi, int yi) : x(xi), y(yi) {}
        vector_i(vector_d realvec) : x((int)round(realvec.x)), y((int)round(realvec.y)) {}
    };


    drawable(double start_time, double duration, asciirenderer::color channels, char* in_drawchar, DrawMode draw_mode, shared_ptr<asciirenderer> &rend);

    virtual void Draw(ulong t);
protected:
    shared_ptr<asciirenderer> rend;
    DrawMode draw_mode;

    ulong GetColor(int idx, int total);
    double FactorCalc(ulong t) const;

    static double lerp(double a, double b, double t);
    static vector_d lerp(vector_d a, vector_d b, double t);
};


#endif //ASCIICHIS_DRAWABLE_H
