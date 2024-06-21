//
// Created by loochis on 6/20/24.
//

#include <iostream>
#include "line.h"

line::line(double start_time, double duration, drawable::vector_i start_pos, drawable::vector_i end_pos,
           asciirenderer::color channels, char *in_drawchar, drawable::DrawMode draw_mode, shared_ptr<asciirenderer> &rend)
: drawable(start_time, duration, channels, in_drawchar, draw_mode, rend),
  start_pos(start_pos),
  end_pos(end_pos)
{

}

void line::Draw(ulong t) {
    double t_val = FactorCalc(t);
    //std::cout << t_val << "\n";
    if (t_val <= 0) return;
    if (t_val >= 1) DrawLine(start_pos, end_pos, 1);

    DrawLine(start_pos, end_pos, t_val);
}

void line::DrawLine(drawable::vector_i a, drawable::vector_i b, double t) {
    int d_x = b.x - a.x;
    int d_y = b.y - a.y;

    int total_steps;
    if (abs(d_x) > abs(d_y))
        total_steps = abs(d_x);
    else
        total_steps = abs(d_y);

    float inc_x = (float)d_x / (float)total_steps;
    float inc_y = (float)d_y / (float)total_steps;

    int steps = (int)round(total_steps*t);

    vector_d pos = vector_d(start_pos.x,start_pos.y);
    seed = int(pos.x*2000.0f + pos.y*735.0f);
    //srand(seed);

    for (int i = 0; i < steps; i++) {
        auto raster = vector_i(pos);
        rend->setpix(raster.x, raster.y, GetColor(i, steps));
        pos.x += inc_x;
        pos.y += inc_y;
    }
}
