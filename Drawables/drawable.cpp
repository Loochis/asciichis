//
// Created by loochis on 6/20/24.
//

#include <cstring>
#include "drawable.h"

drawable::drawable(double start_time, double duration, asciirenderer::color channels, char* in_drawchar, DrawMode draw_mode, shared_ptr<asciirenderer> &rend) :
    start_time_us(ulong(start_time*US_CONST)),
    duration_us(ulong(duration*US_CONST)),
    channels(channels),
    draw_mode(draw_mode),
    rend(rend)
{
    memcpy(drawchar, in_drawchar, 4);
}

void drawable::Draw(ulong t) {

}

double drawable::FactorCalc(ulong t) const {
    if (t < start_time_us)
        return 0;

    if (t > start_time_us + duration_us)
        return 1;

    t -= start_time_us;
    return (double)t / (double)duration_us;
}

double drawable::lerp(double a, double b, double t) {
    return a*(1-t) + b*t;
}

drawable::vector_d drawable::lerp(drawable::vector_d a, drawable::vector_d b, double t) {
    return {lerp(a.x, b.x, t),
            lerp(a.y, b.y, t) };
}

char RandChar(int low, int high) {
    return (char)(low + rand() % (high - low + 1));
}

ulong drawable::GetColor(int idx, int total) {

    switch (draw_mode) {
        case(DrawMode::CONSTANT_CHAR) :
            return asciirenderer::coltobyte(channels, drawchar);

        case(DrawMode::RANDOM_CHAR) :
            char tmpchar[4];
            tmpchar[3] = RandChar('!', '~');
            return asciirenderer::coltobyte(channels, tmpchar);

        case(DrawMode::FADE_BLOCK) :
            if (idx == total)   return asciirenderer::coltobyte(channels, BOX_DRAW[1]);
            if (idx == total-1) return asciirenderer::coltobyte(channels, BOX_DRAW[2]);
            if (idx == total-2) return asciirenderer::coltobyte(channels, BOX_DRAW[3]);

            return asciirenderer::coltobyte(channels, BOX_DRAW[4]);

        default :
            break;
    }

    return 0;
}

