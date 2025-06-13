#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <pthread.h>
//copilot, i dont want you edititing my code, just write  comments for what I am doing

#include "fcu.h"

void print_fcu_outputs(fcu_outputs_s* outputs, int starting, int ending, int idx);
void print_shift_reg(queue_s* queue);
void grab_next_ip_set(fcu_inputs_s* inputs); 
double* init_pixel_inputs(int size);
void print_image_pixels(double* pixels, int size);


fcu_thread_data_s* fcu_thread_data[3];
fcu_coefficients_s* kernel[3]; //3x3 kernel for the three FCUs

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <image_size>\n", argv[0]);
        return EXIT_FAILURE;
    }
    double* image_pixels;

    init_fcu_thread_args(fcu_thread_data[0]);
    init_fcu_thread_args(fcu_thread_data[1]);
    init_fcu_thread_args(fcu_thread_data[2]);


    kernel[0] = (fcu_coefficients_s*)malloc(sizeof(fcu_coefficients_s));
    kernel[1] = (fcu_coefficients_s*)malloc(sizeof(fcu_coefficients_s));
    kernel[2] = (fcu_coefficients_s*)malloc(sizeof(fcu_coefficients_s));
    if (kernel[0] == NULL || kernel[1] == NULL || kernel[2] == NULL) {
        fprintf(stderr, "Memory allocation failed for kernel\n");
        return EXIT_FAILURE;
    }
    fcu_thread_data[0]->kernel = kernel[0];
    fcu_thread_data[1]->kernel = kernel[1];
    fcu_thread_data[2]->kernel = kernel[2];

    //initialize the image and divide the pixels into three sets of 1D vectors
    //each thread (opr FCU) will act on a different vector preventing race conditions (since multiple threads running concurrently one for each fcu)
    int image_size = atoi(argv[1]);
    image_pixels = init_pixel_inputs(image_size);

    //NEED TO CHECK
    fcu_thread_data[0]->image_set = (int*)malloc((image_size * image_size / 3) * sizeof(int));

    //assign the image_set for each FCU by slicing the image_pixels array into sections of 3
    pthread_t threads[3];

    for (int i = 0; i < image_size*image_size / 9; i++) {
    
        for (int i = 0; i < 3; i++) {
            pthread_create(&threads[i], NULL, process_row, (void*)fcu_thread_data[i]);
        }
    
        for (int i = 0; i < 3; i++) {
            pthread_join(threads[i], NULL);
        }
        
    }

    
}

//function to initiialize each FCUs thread data
void init_fcu_thread_args(fcu_thread_data_s* thread_arg) {
    thread_arg = (fcu_thread_data_s*)malloc(sizeof(fcu_thread_data_s));
    if (thread_arg == NULL) {
        fprintf(stderr, "Memory allocation failed for thread arguments\n");
        exit(EXIT_FAILURE);
    }

    //initialize the shift registers
    init_shift_reg(&thread_arg->shift_reg_1, 'A');
    init_shift_reg(&thread_arg->shift_reg_2, 'B');

    thread_arg->inputs = (fcu_inputs_s*)malloc(sizeof(fcu_inputs_s));
    if (thread_arg->inputs == NULL) {
        fprintf(stderr, "Memory allocation failed for inputs\n");
        exit(EXIT_FAILURE);
    }

    thread_arg->inputs->x_0 = (double*)malloc(sizeof(double));
    thread_arg->inputs->x_1 = (double*)malloc(sizeof(double));
    thread_arg->inputs->x_2 = (double*)malloc(sizeof(double));

    //kernel pointer will be initialized in the main function
}


void* process_row(void *arg) {

    //cast thread function argument to fcu_thread_data_s pointer
    fcu_thread_data_s* thread_data = (fcu_thread_data_s*)arg;

    grab_next_ip_set(thread_data->inputs);

    fcu_outputs_s* outputs = three_parallel_fcu(
        thread_data->inputs, 
        thread_data->kernel, 
        thread_data->shift_reg_1, 
        thread_data->shift_reg_2
    );

    //somehow print the outputs
    
}



//print all the pixel data in the image
void print_image_pixels(double* pixels, int size) {
    if (pixels == NULL) {
        printf("Pixels are NULL\n");
        return;
    }
    printf("\n\t");
    for (int i = 0; i < 5; i++){
        printf("--------");
    }
    printf("Image Pixels");
    for (int i = 0; i < 4; i++){
        printf("--------");
    }
    printf("-----\n\t|\t");
    for (int i = 0; i < size * size; i++) {
        printf("%d \t", (int)pixels[i]);
        if ((i + 1) % size == 0 && i != (size * size - 1)) {
            printf("|\n\t|\t");
        }
    }
    printf("|");

    printf("\n\t");
    for (int i = 0; i < 5; i++){
        printf("--------");
    }
    printf("Image Pixels");
    for (int i = 0; i < 4; i++){
        printf("--------");
    }
    printf("-----");
}

/**
 * Function that will initialize the testing pixel data with random values
 * 
 * @param size the width of the image in pixels.
 * 
 * Stored as an array that is size^2 long
 */
double* init_pixel_inputs(int size) {
    double* pixels = (double*)malloc(size * size * sizeof(double));
    if (pixels == NULL) {
        fprintf(stderr, "Memory allocation failed for pixel inputs\n");
        exit(EXIT_FAILURE);
    }

    //mod by 255 since pixels are 8-bit values
    for (int i = 0; i < size * size; i++) {
        pixels[i] = (double)(rand() % 255);
    }

    return pixels;

}

/**
 * Function that will parse the overall pixel data and output three new values to the fcu_inputs_s struct
 * 
 * @param inputs Pointer to the fcu_inputs_s structure where the next input set will be stored.
 */

void grab_next_ip_set(fcu_inputs_s* inputs) {
    // Check if inputs is NULL
    if (inputs == NULL) {
        fprintf(stderr, "Inputs pointer is NULL\n");
        return;
    }

    //pointer arithmetic. Grab the next three by setting the poiunters three ahead of their original spot
    inputs->x_0 = inputs->x_0 + 3; 
    inputs->x_1 = inputs->x_1 + 3;
    inputs->x_2 = inputs->x_2 + 3;
}


void print_fcu_outputs(fcu_outputs_s* outputs, int starting, int ending, int idx) {
    if (outputs == NULL) {
        printf("Outputs are NULL\n");
        return;
    }

    int header_dash_count = 6; // Number of dashes in the header

    if (starting) {
        printf("\n\n\t\t\tOutputs\n");
        printf("\t");
        for (int i = 0; i < header_dash_count; i++){
            printf("--------");
        }
        printf("-\n");
    }
    
    if (!starting && !ending) {
        printf("%d:\t| Y_0: %.2f \t| Y_1: %.2f \t| Y_2: %.2f \t|\n", idx, outputs->y_0, outputs->y_1, outputs->y_2);
    }

    if (ending) {
        printf("\t");
        for (int i = 0; i < header_dash_count; i++){
            printf("--------");
        }
        printf("-\n");
    }
}

void print_shift_reg(queue_s* queue) {
    if (queue == NULL) {
        printf("Shift Reg is NULL\n");
        return;
    }
    printf("\n\t\t\t\tShift Register %c:\n", queue->name);
    printf("\t\t----------------------------------------------\n");
    printf("\t\t| %f | --> | %f | --> | %f |\n", queue->tail->data, queue->middle->data, queue->head->data);
    printf("\t\t----------------------------------------------\n");
}