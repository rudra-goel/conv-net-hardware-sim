
#include <stdio.h>

#include "print_buffers.h"

void print_stages(pipeline_buffers* p) {
    if (p->ip) {
        print_stage_one_ip(p->ip);
    } else {
        printf("Inputs not valid");
        return;
    } 

    if (p->s12) {
        print_stage_two_ip(p->s12);
    } else {
        printf("Stage 1 Error");
        return;
    }

    if (p->s23) {
        print_stage_three_ip(p->s23);
    } else {
        printf("Stage 2 Error");
        return;
    }

    if (p->s34) {
        print_stage_3_4_buffer(p->s34);
    } else {
        printf("Stage 3 Error");
        return;
    }

    if (p->s45) {
        print_stage_4_5_buffer(p->s45);
    } else {
        printf("Stage 4 Error");
        return;
    }

    if (p->s56) {
        print_stage_5_6_buffer(p->s56);
    } else {
        printf("Stage 5 Error");
        return;
    }
    
    if (p->s67) {
        print_stage_6_7_buffer(p->s67);
    } else {
        printf("Stage 6 Error");
        return;
    }

    if (p->s78) {
        print_stage_7_8_buffer(p->s78);
    } else {
        printf("Stage 7 Error");
        return;
    }

    if (p->op) {
        print_conv_layer_op(p->op);
    } else {
        printf("Stage 8 Error");
        return;
    }

}

void print_stage_one_ip(conv_layer_ip *s1) {
    printf("stage_one_ip values:\n");
    printf("  x0   : %d\n", s1->x0);
    printf("  x1   : %d\n", s1->x1);
    printf("  x2   : %d\n", s1->x2);
    printf("  h0   : %d\n", s1->h0);
    printf("  h1   : %d\n", s1->h1);
    printf("  h2   : %d\n", s1->h2);
    printf("  h01  : %d\n", s1->h01);
    printf("  h12  : %d\n", s1->h12);
    printf("  h012 : %d\n", s1->h012);
    printf("\n");
}

void print_stage_two_ip(stage_1_2_buffer *s2) {
    printf("stage_two_ip values:\n");
    printf("  x2    : %d\n", s2->x2);
    printf("  x0h0  : %d\n", s2->x0h0);
    printf("  x1h1  : %d\n", s2->x1h1);
    printf("  x2h2  : %d\n", s2->x2h2);
    printf("  x01   : %d\n", s2->x01);
    printf("  x12   : %d\n", s2->x12);
    printf("  h01   : %d\n", s2->h01);
    printf("  h12   : %d\n", s2->h12);
    printf("  h012  : %d\n", s2->h012);
    printf("\n");
}

void print_stage_three_ip(stage_2_3_buffer *s3) {
    printf("stage_three_ip values:\n");
    printf("  x0h0   : %d\n", s3->x0h0);
    printf("  x1h1   : %d\n", s3->x1h1);
    printf("  x2h2   : %d\n", s3->x2h2);
    printf("  x012   : %d\n", s3->x012);
    printf("  x01h01 : %d\n", s3->x01h01);
    printf("  x12h12 : %d\n", s3->x12h12);
    printf("  h012   : %d\n", s3->h012);
    printf("\n");
}

void print_stage_3_4_buffer(stage_3_4_buffer *s34) {
    printf("stage_3_4_buffer values:\n");
    printf("  x0h0             : %d\n", s34->x0h0);
    printf("  x2h2             : %d\n", s34->x2h2);
    printf("  x01h01_x1h1      : %d\n", s34->x01h01_x1h1);
    printf("  x12h12_x1h1      : %d\n", s34->x12h12_x1h1);
    printf("  x012h012         : %d\n", s34->x012h012);
    printf("\n");
}

void print_stage_4_5_buffer(stage_4_5_buffer *s45) {
    printf("stage_4_5_buffer values:\n");
    printf("  x0h0                        : %d\n", s45->x0h0);
    printf("  x2h2                        : %d\n", s45->x2h2);
    printf("  x01h01_x1h1                 : %d\n", s45->x01h01_x1h1);
    printf("  x12h12_x1h1                 : %d\n", s45->x12h12_x1h1);
    printf("  x012h012_qty_x01h01_x1h1 : %d\n", s45->x012h012_qty_x01h01_x1h1);
    printf("\n");
}

void print_stage_5_6_buffer(stage_5_6_buffer *s56) {
    printf("stage_5_6_buffer values:\n");
    printf("  x0h0                                   : %d\n", s56->x0h0);
    printf("  x2h2                                   : %d\n", s56->x2h2);
    printf("  x01h01_x1h1                            : %d\n", s56->x01h01_x1h1);
    printf("  x12h12_x1h1                            : %d\n", s56->x12h12_x1h1);
    printf("  x012h012_x01h01_x12h12_plus_2x1h1 : %d\n", s56->x012h012_x01h01_x12h12_plus_2x1h1);
    printf("\n");
}

void print_stage_6_7_buffer(stage_6_7_buffer *s67) {
    printf("stage_6_7_buffer values:\n");
    printf("  x01h01_x1h1                            : %d\n", s67->x01h01_x1h1);
    printf("  x12h12_x1h1                            : %d\n", s67->x12h12_x1h1);
    printf("  x012h012_x01h01_x12h12_plus_2x1h1 : %d\n", s67->x012h012_x01h01_x12h12_plus_2x1h1);
    printf("  x0h0_x2h2                              : %d\n", s67->x0h0_x2h2);
    printf("\n");
}

void print_stage_7_8_buffer(stage_7_8_buffer *s78) {
    printf("stage_7_8_buffer values:\n");
    printf("  x12h12_x1h1                                    : %d\n", s78->x12h12_x1h1);
    printf("  x0h0_x2h2                                      : %d\n", s78->x0h0_x2h2);
    printf("  x012h012_x01h01_x12h12_plus_2x1h1           : %d\n", s78->x012h012_x01h01_x12h12_plus_2x1h1);
    printf("  x2h2_x0h0_plus_x01h01_x1h1                 : %d\n", s78->x2h2_x0h0_plus_x01h01_x1h1);
    printf("\n");
}

void print_conv_layer_op(conv_layer_op *conv_op) {
    printf("conv_layer_op values:\n");
    printf("  y0 : %d\n", conv_op->y0);
    printf("  y1 : %d\n", conv_op->y1);
    printf("  y2 : %d\n", conv_op->y2);
    printf("\n");
}