#include <stdlib.h>
#include "fcu.h"

int multiplier (int a, int b) {
    //multiplier function to multiply two integers
    return a * b;
}

int adder(int a, int b) {
    //adder function to add two integers
    return a + b;
}

stage_two_ip* conv_layer_stage_one(stage_one_ip* inputs) {
    stage_two_ip* outputs = (stage_two_ip*) malloc(sizeof(stage_two_ip));

    //actual computation
    outputs->x0h0 = multiplier(inputs->x0, inputs->h0);
    outputs->x1h1 = multiplier(inputs->x1, inputs->h1);
    outputs->x2h2 = multiplier(inputs->x2, inputs->h2);
    outputs->x01 = adder(inputs->x0, inputs->x1);
    outputs->x12 = adder(inputs->x1, inputs->x2);

    //passthrough signals - essentially act as buffer registers for this stage
    outputs->x2 = inputs->x2;
    outputs->h01 = inputs->h01;
    outputs->h12 = inputs->h12;
    outputs->h012 = inputs->h012;
}

