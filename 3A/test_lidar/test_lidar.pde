/**
 * Simple Read
 * 
 * Read data from the serial port and change the color of a rectangle
 * when a switch connected to a Wiring or Arduino board is pressed and released.
 * This example works with the Wiring / Arduino program that follows below.
 */


import processing.serial.*;

Serial myPort;  // Create object from Serial class
byte[] rx_buffer = new byte[32];      // Data received from the serial port
int[]  lidar_value = new int[16];

void setup() 
{
  size(720, 720);
  // I know that the first port in the serial list on my mac
  // is always my  FTDI adaptor, so I open Serial.list()[0].
  // On Windows machines, this generally opens COM1.
  // Open whatever port is the one you're using.
  String portName = Serial.list()[0];
  myPort = new Serial(this, portName, 115200);
  myPort.buffer(32);
  myPort.write(0xAA); //<>//
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
    float x_B = cos(angle_btwn_line*i)*(abs(lidar_value[i]/2));
    float y_B = sin(angle_btwn_line*i)*(abs(lidar_value[i]/2));
    line(origine_x + x_A, origine_y + y_A, origine_x + x_B, origine_y + y_B);
  }
}

void serialEvent(Serial myPort){
  rx_buffer = myPort.readBytes();
  for(int i=0;i<32;i++){
    if(i%2==0){
      lidar_value[i>>1] = rx_buffer[i];
      lidar_value[i>>1] = lidar_value[i>>1]<<8;
    }else{
      lidar_value[i>>1] = lidar_value[i>>1] + rx_buffer[i];
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
