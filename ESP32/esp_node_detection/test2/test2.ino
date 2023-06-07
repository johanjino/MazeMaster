#include <Arduino.h>


////////////////////////////   INITIALIZATIONS   //////////////////////////// 
#define SAMPLES 4
#define DATA_ELEMENTS 7
float Image[4] = {};
float Cam_Data[DATA_ELEMENTS] = {};
float Curr_Data[DATA_ELEMENTS] = {};
float Node_Data[4] = {};
static float Cam_Data_Buff[SAMPLES][DATA_ELEMENTS] = {};


////////////////////////////   FUNCTIONS   //////////////////////////// 
void get_Cam_Data(float Cam_Data[]) 
  //retrns Cam_Data(R_area, B_area, Y_area, offset, R_turn, F_turn, L_turn)
}

float get_compass_angle() {
  //retuns the heading angle
}

void send_to_server(float Node_Data[]){
  //send the node images' array to server
}

void make_image(float Curr_Data[], float Image[]) {
  float R_area = Curr_Data[0];
  float B_area = Curr_Data[1];
  float Y_area = Curr_Data[2];

  float compass_angle = get_compass_angle();

  Image[0] = R_area;
  Image[1] = B_area;
  Image[2] = Y_area;
  Image[3] = compass_angle;
}

void get_Curr_Data(float Curr_Data[]) {
  get_Cam_Data(Cam_Data);

  for (int i = 0; i < SAMPLES - 1; i++) {
    for (int j = 0; j < DATA_ELEMENTS; j++) {
      Cam_Data_Buff[i][j] = Cam_Data_Buff[i + 1][j];
    }
  }

  for (int i = 0; i < DATA_ELEMENTS; i++) {
    Cam_Data_Buff[SAMPLES - 1][i] = Cam_Data[i];
  }

  for (int i = 0; i < DATA_ELEMENTS; i++) {
    float sum = 0;
    for (int j = 0; j < SAMPLES; j++) {
      sum += Cam_Data_Buff[j][i];
    }
    Curr_Data[i] = sum / SAMPLES;
  }
}

void junction_routine(){

}

////////////////////////////   SETUP   //////////////////////////// 
void setup() {
  for (int i = 0; i < SAMPLES; i++){
    get_Curr_Data(Curr_Data);
  }

}


////////////////////////////   LOOP   //////////////////////////// 
void loop() {


}
