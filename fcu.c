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

/**
 * 7 Stage Pipelined Convolution Processor for 1D vectors length 3
 * 
 * for a 3x3 kernel, employ three of these pipelines in parallel
 * 
 * This is known as the Fast Convolutional Unit (FCU)
 */

stage_1_2_buffer* conv_layer_stage_one(conv_layer_ip* inputs) {
    stage_1_2_buffer* outputs = (stage_1_2_buffer*) malloc(sizeof(stage_1_2_buffer));

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

    return outputs;
}

stage_2_3_buffer* conv_layer_stage_two(stage_1_2_buffer* inputs) {
    stage_2_3_buffer* outputs = (stage_2_3_buffer*) malloc(sizeof(stage_2_3_buffer));
    
    outputs->x0h0 = inputs->x0h0;
    outputs->x1h1 = inputs->x1h1;
    outputs->x2h2 = inputs->x2h2;
    
    outputs->h012 = inputs->h012;
    
    outputs->x012 = adder(inputs->x01, inputs->x2);
    outputs->x01h01 = multiplier(inputs->x01, inputs->h01);
    outputs->x12h12 = multiplier(inputs->x12, inputs->h12);
    return outputs;
}

stage_3_4_buffer* conv_layer_stage_three(stage_2_3_buffer* inputs) {
    stage_3_4_buffer* outputs = (stage_3_4_buffer*) malloc(sizeof(stage_3_4_buffer));

    outputs->x0h0 = inputs->x0h0;
    outputs->x2h2 = inputs->x2h2;

    outputs->x01h01_x1h1 = adder((-1)*inputs->x1h1, inputs->x01h01);
    outputs->x12h12_x1h1 = adder((-1)*inputs->x1h1, inputs->x12h12);
    outputs->x012h012 = multiplier(inputs->x012, inputs->h012);

    return outputs;
}


stage_4_5_buffer* conv_layer_stage_four(stage_3_4_buffer* inputs) {
    stage_4_5_buffer* outputs = (stage_4_5_buffer*)malloc(sizeof(stage_4_5_buffer));

    outputs->x0h0 = inputs->x0h0;
    outputs->x01h01_x1h1 = inputs->x01h01_x1h1;
    outputs->x12h12_x1h1 = inputs->x12h12_x1h1;
    outputs->x2h2 = inputs->x2h2;
    
    outputs->x012h012_qty_x01h01_x1h1 = adder((-1)*inputs->x01h01_x1h1, inputs->x012h012);
    
    return outputs;
}

stage_5_6_buffer* conv_layer_stage_five(stage_4_5_buffer* inputs) {
    stage_5_6_buffer* outputs = (stage_5_6_buffer*) malloc(sizeof(stage_5_6_buffer));
    
    outputs->x0h0 = inputs->x0h0;
    outputs->x01h01_x1h1 = inputs->x01h01_x1h1;
    outputs->x12h12_x1h1 = inputs->x12h12_x1h1;
    outputs->x2h2 = inputs->x2h2;
    
    outputs->x012h012_x01h01_x12h12_plus_2x1h1 = adder((-1)*inputs->x12h12_x1h1, inputs->x012h012_qty_x01h01_x1h1);
    
    return outputs;
}

stage_6_7_buffer* conv_layer_stage_six(stage_5_6_buffer* inputs) {
    stage_6_7_buffer* outputs = (stage_6_7_buffer*)malloc(sizeof(stage_6_7_buffer));
    
    outputs->x01h01_x1h1 = inputs->x01h01_x1h1;
    outputs->x12h12_x1h1 = inputs->x12h12_x1h1;
    outputs->x012h012_x01h01_x12h12_plus_2x1h1 = inputs->x012h012_x01h01_x12h12_plus_2x1h1;

    outputs->x0h0_x2h2 = adder(inputs->x0h0, (-1)*inputs->x2h2);

    return outputs;
}

stage_7_8_buffer* conv_layer_stage_seven(stage_6_7_buffer* inputs) {
    stage_7_8_buffer* outputs = (stage_7_8_buffer*)malloc(sizeof(stage_7_8_buffer));

    outputs->x12h12_x1h1 = inputs->x12h12_x1h1;
    outputs->x0h0_x2h2 = inputs->x0h0_x2h2;
    outputs->x012h012_x01h01_x12h12_plus_2x1h1 = inputs->x012h012_x01h01_x12h12_plus_2x1h1;

    outputs->x2h2_x0h0_plus_x01h01_x1h1 = adder(inputs->x01h01_x1h1, (-1)*inputs->x0h0_x2h2);

    return outputs;
}

conv_layer_op* conv_layer_stage_eight(stage_7_8_buffer* inputs) {
    conv_layer_op* outputs = (conv_layer_op*) malloc(sizeof(conv_layer_op));

    outputs->y0 = adder(inputs->x12h12_x1h1, inputs->x0h0_x2h2);
    outputs->y1 = inputs->x2h2_x0h0_plus_x01h01_x1h1;
    outputs->y2 = inputs->x012h012_x01h01_x12h12_plus_2x1h1;

    return outputs;
}