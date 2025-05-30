#include <stdio.h>
#include "fcu.h"

void print_stage_one_ip(conv_layer_ip *s1);
void print_stage_two_ip(stage_1_2_buffer *s2);
void print_stage_three_ip(stage_2_3_buffer *s3);

int main() {
    conv_layer_ip s1_data = {10, 20, 30, 40, 50, 60, 70, 80, 90};

    stage_1_2_buffer* stage_2 = conv_layer_stage_one(&s1_data);
    stage_2_3_buffer* stage_3 = conv_layer_stage_two(stage_2);

    print_stage_one_ip(&s1_data);
    print_stage_two_ip(stage_2);
    print_stage_three_ip(stage_3);

    return 0;
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

