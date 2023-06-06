// Import necessary libraries
#include <Arduino.h>

// Define some global variables
#define BUFFER_SIZE 5
#define DATA_SIZE 7

int Cam_Data[BUFFER_SIZE][DATA_SIZE]; // 2D array to store last 5 sets of data
int Curr_Data[DATA_SIZE]; // Current averaged data
int Node_Data[5]; // adjust size as needed
int Image_n = 0;

int buffer_index = 0; // Keep track of oldest data in buffer
int total[DATA_SIZE] = {0}; // Keep track of total for moving average

// Placeholder functions
void get_data_from_FPGA() {
  // Get data from FPGA and save to Cam_Data[buffer_index]
}

void move_bot(int val1, int val2) {
  // Move bot
}

void make_image() {
  // Make image from Curr_Data and a compass_angle
}

int get_compass_angle() {
  // Get compass angle
  return 0;
}

void send_to_server() {
  // Send Node_Data to server
}

bool server_signals_all_nodes_visited() {
  // Check if all nodes are visited
  return false;
}

void process() {
  while (!server_signals_all_nodes_visited()) {
    // Update circular buffer and total
    for (int i = 0; i < DATA_SIZE; i++) {
      total[i] -= Cam_Data[buffer_index][i];
    }

    get_data_from_FPGA();

    for (int i = 0; i < DATA_SIZE; i++) {
      total[i] += Cam_Data[buffer_index][i];
      Curr_Data[i] = total[i] / BUFFER_SIZE;
    }

    buffer_index = (buffer_index + 1) % BUFFER_SIZE; // Move index to next oldest

    move_bot(Curr_Data[3], Curr_Data[3]);

    if (Curr_Data[4] == 0 && Curr_Data[5] == 1 && Curr_Data[6] == 0) {
      move_bot(1, 1);
    } else {
      Image_n = make_image();
      move_bot(1, 1);

      while (Image_n != Node_Data[0]) {
        move_bot(1, -1);
        get_data_from_FPGA();

        for (int i = 0; i < DATA_SIZE; i++) {
          total[i] += Cam_Data[buffer_index][i] - Cam_Data[(buffer_index + 1) % BUFFER_SIZE][i];
          Curr_Data[i] = total[i] / BUFFER_SIZE;
        }

        buffer_index = (buffer_index + 1) % BUFFER_SIZE;

        if (Curr_Data[4] == 0 && Curr_Data[5] == 1 && Curr_Data[6] == 0) {
          Image_n = make_image();
          Node_Data[0] = Image_n;
        }
      }
      send_to_server();
      memset(Node_Data, 0, sizeof(Node_Data));

      if (Curr_Data[4] == 1) {
        move_bot(1, -1);
      } else if (Curr_Data[5] == 1) {
        move_bot(1, 1);
      } else {
        move_bot(0, 1);
      }
    }
  }
}

void setup() {

}

void loop() {
  process();
}
