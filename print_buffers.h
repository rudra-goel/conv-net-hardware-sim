#include <stdio.h>
#include <stdlib.h>

#ifndef PRINT_BUFFERS_H
#define PRINT_BUFFERS_H
#include "fcu.h"



void print_stage_one_ip(conv_layer_ip *s1);
void print_stage_two_ip(stage_1_2_buffer *s2);
void print_stage_three_ip(stage_2_3_buffer *s3);
void print_stage_3_4_buffer(stage_3_4_buffer *s34);
void print_stage_4_5_buffer(stage_4_5_buffer *s45);
void print_stage_5_6_buffer(stage_5_6_buffer *s56);
void print_stage_6_7_buffer(stage_6_7_buffer *s67);
void print_stage_7_8_buffer(stage_7_8_buffer *s78);
void print_conv_layer_op(conv_layer_op *conv_op);
void print_stages(pipeline_buffers* p);

#endif
