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

} stage_one_ip;

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
} stage_two_ip;

stage_two_ip* conv_layer_stage_one(stage_one_ip* inputs);
int multiplier (int a, int b);
int adder(int a, int b);

