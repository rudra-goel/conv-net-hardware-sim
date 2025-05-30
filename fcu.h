/**
 * Header file for the FCU Pipeline
 */
//Structs for the kernel, and input. 
typedef struct {
    int input[3];
} input_s;

typedef struct {
    int kernel[3][3];
} kernel_s;

typedef struct {
    int output[3];
} output_s;

typedef struct {
    int x0;
    int x1;
    int x2;

    int h0;
    int h1;
    int h2;
    
    int h01;
    int h12;
    int h012;

} conv_layer_ip;

typedef struct {
    int x2;

    int x0h0;
    int x1h1;
    int x2h2;
    
    int x01;
    int x12;

    int h01;
    int h12;
    int h012;
} stage_1_2_buffer;

typedef struct {
    int x0h0;
    int x1h1;
    int x2h2;
    
    int x012;
    int x01h01;
    int x12h12;

    int h012;

} stage_2_3_buffer;

typedef struct {
    int x0h0;
    int x2h2;
    
    int x01h01_x1h1;
    int x12h12_x1h1;
    int x012h012;
    
} stage_3_4_buffer;

typedef struct {
    int x0h0;
    int x2h2;
    int x01h01_x1h1;
    int x12h12_x1h1;
    
    int x012h012_qty_x01h01_x1h1;
    
} stage_4_5_buffer;

typedef struct {
    int x0h0;
    int x2h2;
    int x01h01_x1h1;
    int x12h12_x1h1;
    
    int x012h012_x01h01_x12h12_plus_2x1h1;
    
} stage_5_6_buffer;

typedef struct {
    int x01h01_x1h1;
    int x12h12_x1h1;
    int x012h012_x01h01_x12h12_plus_2x1h1;
    
    int x0h0_x2h2;
    
} stage_6_7_buffer;

typedef struct {
    int x12h12_x1h1;
    int x0h0_x2h2;
    int x012h012_x01h01_x12h12_plus_2x1h1;

    int x2h2_x0h0_plus_x01h01_x1h1;
} stage_7_8_buffer;

typedef struct {
    int y0;
    int y1;
    int y2;
} conv_layer_op;

stage_1_2_buffer* conv_layer_stage_one(conv_layer_ip* inputs);
stage_2_3_buffer* conv_layer_stage_two(stage_1_2_buffer* inputs);
stage_3_4_buffer* conv_layer_stage_three(stage_2_3_buffer* inputs);
stage_4_5_buffer* conv_layer_stage_four(stage_3_4_buffer* inputs);
stage_5_6_buffer* conv_layer_stage_five(stage_4_5_buffer* inputs);
stage_6_7_buffer* conv_layer_stage_six(stage_5_6_buffer* inputs);
stage_7_8_buffer* conv_layer_stage_seven(stage_6_7_buffer* inputs);
conv_layer_op* conv_layer_stage_eight(stage_7_8_buffer* inputs);

int multiplier (int a, int b);
int adder(int a, int b);

