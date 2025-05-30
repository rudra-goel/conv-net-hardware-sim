#include <stdio.h>
#include <stdlib.h>

#include "fcu.h"
#include "print_buffers.h"

int main() {
    conv_layer_ip s1_data = {10, 20, 30, 40, 50, 60, 70, 80, 90};

    pipeline_buffers* p1 = (pipeline_buffers*) malloc(sizeof(pipeline_buffers));
    p1->ip = (conv_layer_ip*) malloc(sizeof(conv_layer_ip));
    p1->ip = &s1_data;

    p1->s12 = conv_layer_stage_one(p1->ip);
    p1->s23 = conv_layer_stage_two(p1->s12);
    p1->s34 = conv_layer_stage_three(p1->s23);
    p1->s45 = conv_layer_stage_four(p1->s34);
    p1->s56 = conv_layer_stage_five(p1->s45);
    p1->s67 = conv_layer_stage_six(p1->s56);
    p1->s78 = conv_layer_stage_seven(p1->s67);
    p1->op = conv_layer_stage_eight(p1->s78);

    print_stages(p1);



    return 0;
}
