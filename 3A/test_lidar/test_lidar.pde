/**
 * Simple Read
 * 
 * Read data from the serial port and change the color of a rectangle
 * when a switch connected to a Wiring or Arduino board is pressed and released.
 * This example works with the Wiring / Arduino program that follows below.
 */


import processing.serial.*;

Serial myPort;  // Create object from Serial class
byte[] rx_buffer = new byte[3];      // Data received from the serial port
int[][] lidar_value = new int[16][2];
byte lidar_active = 0;
byte lidar_ROI_number = 0;
byte lidar_measure_number = 0;
int reading_head=0;
int wait_for_head_cmp=0; 
int wait_for_fill=0;

enum rx_parsing_state {
  BEGIN,
  INFO,
  DISTANCE_MES
}
rx_parsing_state parsing_status = rx_parsing_state.BEGIN;

void setup() 
{
  size(720, 720);
  // I know that the first port in the serial list on my mac
  // is always my  FTDI adaptor, so I open Serial.list()[0].
  // On Windows machines, this generally opens COM1.
  // Open whatever port is the one you're using.
  //String portName = Serial.list()[0];
  myPort = new Serial(this, "COM13", 115200);
  myPort.buffer(3);
}

void draw()
{
  if ( myPort.available() > 0) {  // If data is available,       // read it and store it in val
  }
  background(255);             // Set background to white
  circle(360,360,60);
  //line(360,390-lidar_value[0]<<1,360,330);
  //line(360+29.42,360-5.85,360+98.07,360-19.5);
  //line(10,710,360-21.21,360+21.21);
  //line(710,710,360+21.21,360+21.21);
  float origine_x = 360;
  float origine_y = 360;
  float angle_btwn_line = PI/8;
  for(int i=0; i<16 ; i++){
    float x_A = cos(angle_btwn_line*i)*30;
    float y_A = sin(angle_btwn_line*i)*30;
    float x_B = cos(angle_btwn_line*i)*(abs(lidar_value[i][1]/2))+ x_A;
    float y_B = sin(angle_btwn_line*i)*(abs(lidar_value[i][1]/2))+ y_A;
    line(origine_x + x_A, origine_y + y_A, origine_x + x_B, origine_y + y_B);
  }
}

void serialEvent(Serial myPort){
  rx_buffer = myPort.readBytes();
  for(reading_head = 0; reading_head < rx_buffer.length; reading_head++){
    switch(parsing_status)
    {
      case BEGIN :
        if(  rx_buffer[reading_head] == -1 ){
          wait_for_head_cmp++; //<>//
        }else{
          wait_for_head_cmp = 0; //<>//
        }
        if(wait_for_head_cmp > 5){
          wait_for_head_cmp = 0; //<>//
          parsing_status = rx_parsing_state.INFO;
        }
        break;

      case INFO :
        if(  wait_for_head_cmp == 0 ){
          lidar_active = rx_buffer[reading_head]; //<>//
          wait_for_head_cmp++;
        }else if(wait_for_head_cmp == 1){
          lidar_ROI_number = rx_buffer[reading_head]; //<>//
          wait_for_head_cmp++;
        }else if(wait_for_head_cmp > 1){
          lidar_measure_number = rx_buffer[reading_head]; //<>//
          wait_for_head_cmp = 0;
          parsing_status = rx_parsing_state.DISTANCE_MES;
        }
        break;

      case DISTANCE_MES :
        if(  wait_for_fill%3 == 0 && (wait_for_head_cmp < lidar_measure_number)){
          lidar_value[wait_for_head_cmp][0] = rx_buffer[reading_head]; //<>//
          wait_for_fill++;
        }else if((wait_for_fill%3 == 1) && (wait_for_head_cmp < lidar_measure_number)){
          lidar_value[wait_for_head_cmp][1] = rx_buffer[reading_head]; //<>//
          lidar_value[wait_for_head_cmp][1] = lidar_value[wait_for_head_cmp][1] <<8;
          wait_for_fill++;
        }else if((wait_for_fill%3 == 2) && (wait_for_head_cmp < lidar_measure_number)){
          lidar_value[wait_for_head_cmp][1] = lidar_value[wait_for_head_cmp][1] + rx_buffer[reading_head]; //<>//
          wait_for_fill++;
          wait_for_head_cmp++;
        }
        if(wait_for_head_cmp >= lidar_measure_number){ //<>//
          wait_for_fill = 0;
          wait_for_head_cmp = 0;
          parsing_status = rx_parsing_state.BEGIN;
        }
        break;
    }
  }
}



/*

// Wiring / Arduino Code
// Code for sensing a switch status and writing the value to the serial port.

int switchPin = 4;                       // Switch connected to pin 4

void setup() {
  pinMode(switchPin, INPUT);             // Set pin 0 as an input
  Serial.begin(9600);                    // Start serial communication at 9600 bps
}

void loop() {
  if (digitalRead(switchPin) == HIGH) {  // If switch is ON,
    Serial.write(1);               // send 1 to Processing
  } else {                               // If the switch is not ON,
    Serial.write(0);               // send 0 to Processing
  }
  delay(100);                            // Wait 100 milliseconds
}

*/
