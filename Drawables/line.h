//
// Created by loochis on 6/20/24.
//

#ifndef ASCIICHIS_LINE_H
#define ASCIICHIS_LINE_H


#include "drawable.h"

using namespace ASCIICHIS;

class line : public drawable {
public:
    vector_i start_pos;
    vector_i end_pos;

    line(double start_time, double duration, drawable::vector_i start_pos, drawable::vector_i end_pos,
         asciirenderer::color channels, char *in_drawchar, drawable::DrawMode draw_mode, shared_ptr<asciirenderer> &rend);
    void Draw(ulong t) override;

private:
    void DrawLine(vector_i a, vector_i b, double t);
};


#endif //ASCIICHIS_LINE_H
