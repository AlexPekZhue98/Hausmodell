#include <Servo.h>

////////////////////////////////
// !! RESERVED PINS !!
const int FAN_DIRECTION_PIN = 12;
const int FAN_BRAKE_PIN = 9;
const int FAN_SPEED_PIN = 3;
///////////////////////////////

////////////////////////////////
// WINDOWS
////////////////////////////////
const int WINDOW_0_PIN = 8;
const int WINDOW_1_PIN = 7;
const int WINDOW_2_PIN = 6;
const int WINDOW_3_PIN = 5;
const int WINDOW_ROOF_PIN = 4;

////////////////////////////////
// STAIRCASE DOORS
////////////////////////////////
const int STAIRCASE_DOOR_0_PIN = 16;
const int STAIRCASE_DOOR_1_PIN = 14;
const int STAIRCASE_DOOR_2_PIN = 18;
const int STAIRCASE_DOOR_3_PIN = 13;

////////////////////////////////
// OFFICE DOORS
////////////////////////////////
const int OFFICE_DOOR_1_0_PIN = 0;
const int OFFICE_DOOR_1_1_PIN = 1;
const int OFFICE_DOOR_3_0_PIN = 2;

////////////////////////////////
// SMOKE FANS
////////////////////////////////
const int SMOKE_FAN_3 = 22;
const int SMOKE_FAN_2 = 23;
const int SMOKE_FAN_1 = 24;
const int SMOKE_FAN_0 = 25;

////////////////////////////////
// BUTTONS
////////////////////////////////
const int BUTTON_SELECT_0 = 33;
const int BUTTON_SELECT_1 = 35;
const int BUTTON_SELECT_2 = 37;
const int BUTTON_SELECT_3 = 39;

const int BUTTON_ACKNOWLEDGE = 51;
const int BUTTON_VENT = 50;


////////////////////////////////
// LEDS
////////////////////////////////
const int LED_SELECT_0 = 32;
const int LED_SELECT_1 = 34;
const int LED_SELECT_2 = 36;
const int LED_SELECT_3 = 38;

const int LED_RUNNING = 44;
const int LED_FIRE = 45;
const int LED_ACKNOWLEDGE = 47;

////////////////////////////////
// (PHOTO)RESISTORS
////////////////////////////////

const int RES_PHOTO_0 = A0;
const int RES_PHOTO_ON_0 = A1;

const int RES_PHOTO_1 = A2;
const int RES_PHOTO_ON_1 = A3;

const int RES_PHOTO_2 = A4;
const int RES_PHOTO_ON_2 = A5;

const int RES_PHOTO_3 = A8;
const int RES_PHOTO_ON_3 = A9;

////////////////////////////////
// PROGRAM CONSTANTS
////////////////////////////////
const float FIRE_THRESHOLD = 0.5;
const float VENT_THRESHOLD = 0.95;

////////////////////////////////
// INITIALIZE SERVOS
////////////////////////////////

// Windows
Servo window0;
Servo window1;  
Servo window2;  
Servo window3; 
Servo windows[] = {window0,window1,window2,window3};
Servo roofWindow;

// Window Positions
int WINDOW_POS_CLOSED = 130;
int WINDOW_POS_OPEN = 45;

// StaircaseDoors
Servo staircaseDoor0;
Servo staircaseDoor1;
Servo staircaseDoor2;
Servo staircaseDoor3;
Servo staircaseDoors[] = {staircaseDoor0,staircaseDoor1,staircaseDoor2,staircaseDoor3};

// Door Positions
int ST_DOOR_POS_CLOSED = 120;
int ST_DOOR_POS_OPEN = 30;

Servo officeDoor10;
Servo officeDoor11;
Servo officeDoor30;

// Office Door Positions
int OFFICE_DOOR_POS_CLOSED = 100;
int OFFICE_DOOR_POS_OPEN = 50;



// Collect buttons
int floorButtons[] = {BUTTON_SELECT_0, BUTTON_SELECT_1, BUTTON_SELECT_2, BUTTON_SELECT_3};
int floorLEDs[] = {LED_SELECT_0, LED_SELECT_1, LED_SELECT_2, LED_SELECT_3};
int floorSmokeFans[] = {SMOKE_FAN_0, SMOKE_FAN_1, SMOKE_FAN_2, SMOKE_FAN_3};

////////////////////////////////
// INITIALIZE VARIABLES
////////////////////////////////
float defaultResPhoto0 = 0.0;
float defaultResPhotoOn0 = 0.0;

float defaultResPhoto1 = 0.0;
float defaultResPhotoOn1 = 0.0;

float defaultResPhoto2 = 0.0;
float defaultResPhotoOn2 = 0.0;

float defaultResPhoto3 = 0.0;
float defaultResPhotoOn3 = 0.0;

//// Group Resistors
int resPhoto[] = {RES_PHOTO_0, RES_PHOTO_1, RES_PHOTO_2, RES_PHOTO_3};
int resPhotoOn[] = {RES_PHOTO_ON_0, RES_PHOTO_ON_1, RES_PHOTO_ON_2, RES_PHOTO_ON_3};


void setup() {
  Serial.begin(9600);

  // Initialize windows
  window0.attach(WINDOW_0_PIN); 
  window1.attach(WINDOW_1_PIN); 
  window2.attach(WINDOW_2_PIN); 
  window3.attach(WINDOW_3_PIN);
  roofWindow.attach(WINDOW_ROOF_PIN);

  // Initialize doors
  staircaseDoor0.attach(STAIRCASE_DOOR_0_PIN); 
  staircaseDoor1.attach(STAIRCASE_DOOR_1_PIN); 
  staircaseDoor2.attach(STAIRCASE_DOOR_2_PIN); 
  staircaseDoor3.attach(STAIRCASE_DOOR_3_PIN);

  // Initialize doors
  officeDoor10.attach(OFFICE_DOOR_1_0_PIN);
  officeDoor11.attach(OFFICE_DOOR_1_1_PIN);
  officeDoor30.attach(OFFICE_DOOR_3_0_PIN);

  // Initialize fan
  pinMode(FAN_DIRECTION_PIN, OUTPUT); //Initiates Motor Channel A pin
  pinMode(FAN_BRAKE_PIN, OUTPUT); //Initiates Brake Channel A pin
  
  pinMode(SMOKE_FAN_0, OUTPUT); 
  pinMode(SMOKE_FAN_1, OUTPUT); 
  pinMode(SMOKE_FAN_2, OUTPUT); 
  pinMode(SMOKE_FAN_3, OUTPUT); 

  pinMode(BUTTON_SELECT_0, INPUT);
  pinMode(BUTTON_SELECT_1, INPUT);
  pinMode(BUTTON_SELECT_2, INPUT);
  pinMode(BUTTON_SELECT_3, INPUT);
  pinMode(BUTTON_ACKNOWLEDGE, INPUT);
  pinMode(BUTTON_VENT, INPUT);

  pinMode(LED_SELECT_0, OUTPUT); 
  pinMode(LED_SELECT_1, OUTPUT);  
  pinMode(LED_SELECT_2, OUTPUT);  
  pinMode(LED_SELECT_3, OUTPUT);  

  pinMode(LED_RUNNING, OUTPUT);  
  pinMode(LED_FIRE, OUTPUT);  
  pinMode(LED_ACKNOWLEDGE, OUTPUT); 

  pinMode(RES_PHOTO_0, INPUT);
  pinMode(RES_PHOTO_ON_0, INPUT); 
  pinMode(RES_PHOTO_1, INPUT);
  pinMode(RES_PHOTO_ON_1, INPUT); 
  pinMode(RES_PHOTO_2, INPUT);
  pinMode(RES_PHOTO_ON_2, INPUT); 
  pinMode(RES_PHOTO_3, INPUT);
  pinMode(RES_PHOTO_ON_3, INPUT); 


  delay(1000); // wait for a second

  // Read the default values
  defaultResPhoto0 = analogRead(RES_PHOTO_0);
  delay(100);  
  defaultResPhotoOn0 = analogRead(RES_PHOTO_ON_0);
  delay(100); 
  Serial.print("Floor 0 - Default: ");
  Serial.print(defaultResPhoto0);
  Serial.print("Default On: ");
  Serial.println(defaultResPhotoOn0);
  delay(100); 
  defaultResPhoto1 = analogRead(RES_PHOTO_1);
  delay(100);  
  defaultResPhotoOn1 = analogRead(RES_PHOTO_ON_1);
  delay(100); 
  Serial.print("Floor 1 - Default: ");
  Serial.print(defaultResPhoto1);
  Serial.print("Default On: ");
  Serial.println(defaultResPhotoOn1);

  delay(100); 
  defaultResPhoto2 = analogRead(RES_PHOTO_2);
  delay(100);  
  defaultResPhotoOn2 = analogRead(RES_PHOTO_ON_2);
  delay(100); 
  Serial.print("Floor 2 - Default: ");
  Serial.print(defaultResPhoto2);
  Serial.print("Default On: ");
  Serial.println(defaultResPhotoOn2);

  delay(100); 
  defaultResPhoto3 = analogRead(RES_PHOTO_3);
  delay(100);  
  defaultResPhotoOn3 = analogRead(RES_PHOTO_ON_3);
  delay(100); 
  Serial.print("Floor 3 - Default: ");
  Serial.print(defaultResPhoto3);
  Serial.print("Default On: ");
  Serial.println(defaultResPhotoOn3);

  // Set program to running
  digitalWrite(LED_RUNNING, HIGH);
}

/////////////////////
// Program Variables
/////////////////////
int selectedFloor = -1;
bool fireDetected = false;
bool vent = false;
bool acknowledge = false;
bool reset = false;

void loop() {
  float defaultResPhoto[] = {defaultResPhoto0, defaultResPhoto1, defaultResPhoto2, defaultResPhoto3};
  float defaultResPhotoOn[] = {defaultResPhotoOn0, defaultResPhotoOn1, defaultResPhotoOn2, defaultResPhotoOn3};

  
  // Step 1: Wait for floor selection & set doors to initial state
  while (selectedFloor == -1) {
    setNonFireState();
    for (int floor = 0; floor < 4; floor++) {
      if (isButtonTrue(floorButtons[floor])) {
        selectedFloor = floor;
        setNonFireState();
        break;
      }
    }
  }

  // Step 2: Light the according LED & start the smoke fan
  for (int floor = 0; floor < 4; floor++) {
    if (floor == selectedFloor) {
      digitalWrite(floorLEDs[floor], HIGH);
      startSmokeFan(floor);
    } else {
      digitalWrite(floorLEDs[floor], LOW);
      stopSmokeFan(floor);
    }
  }

  // Step 3: Wait for fire
  while (!fireDetected) {
    delay(500);
    if (isFireActive(FIRE_THRESHOLD, defaultResPhoto, defaultResPhotoOn)) {
      fireDetected = true;
    }
  }
  
  if (fireDetected) {
    digitalWrite(LED_FIRE, HIGH);
  }

  // Step 4: Wait for vent
  while (fireDetected && !vent) {
    if (isButtonTrue(BUTTON_VENT)) {
      vent = true;
      break;
    }
  } 

  // Step 5: Start big fan & open doors & open windows
  if (fireDetected && vent) {
    startBigFan();
    delay(100);
    setFireState();
    delay(1000);
  }

  // Step 5: FIRE LED off & acknowledge LED on == that fire is over
  while (fireDetected) {
    digitalWrite(LED_FIRE, LOW);
    delay(200);
    digitalWrite(LED_FIRE, HIGH);
    delay(200);
    if (isFireActive(VENT_THRESHOLD, defaultResPhoto, defaultResPhotoOn) == false) {
      fireDetected = false;
      digitalWrite(LED_FIRE, LOW);
      acknowledge = true;
      digitalWrite(LED_ACKNOWLEDGE, HIGH);
    }
    
  }

  // Step 6: Acknowledge and reset to initial state
  while (acknowledge) {
    setFireState();
    if (isButtonTrue(BUTTON_ACKNOWLEDGE)) {
      acknowledge = false;
      reset = true;
      break;
    }
  }

  // Step 7: Reset
  if (reset) {
    selectedFloor = -1;
    fireDetected = false;
    vent = false;
    acknowledge = false;
    stopBigFan();
    digitalWrite(LED_ACKNOWLEDGE, LOW);
    reset = false;
    for (int floor = 0; floor < 4; floor++) {
      digitalWrite(floorLEDs[floor], LOW);
      stopSmokeFan(floor);
    }
  }

 
}

void startSmokeFan(int floorNumber) {
  digitalWrite(floorSmokeFans[floorNumber], HIGH);
}

void stopSmokeFan(int floorNumber) {
  digitalWrite(floorSmokeFans[floorNumber], LOW);
}

void openWindow(int floorNumber) {
  windows[floorNumber].write(WINDOW_POS_OPEN);
}

void closeWindow(int floorNumber) {
  windows[floorNumber].write(WINDOW_POS_CLOSED);
}

void openRoofWindow() {
  roofWindow.write(WINDOW_POS_OPEN);
}

void closeRoofWindow() {
  roofWindow.write(WINDOW_POS_CLOSED);
}

void openStaircaseDoor(int floorNumber) {
  staircaseDoors[floorNumber].write(ST_DOOR_POS_OPEN);
}

void closeStaircaseDoor(int floorNumber) {
  staircaseDoors[floorNumber].write(ST_DOOR_POS_CLOSED);
}

void closeOfficeDoors() {
  officeDoor10.write(OFFICE_DOOR_POS_CLOSED);
  officeDoor11.write(OFFICE_DOOR_POS_CLOSED);
  officeDoor30.write(OFFICE_DOOR_POS_CLOSED);
}

void openOfficeDoors() {
  officeDoor10.write(OFFICE_DOOR_POS_OPEN);
  officeDoor11.write(OFFICE_DOOR_POS_OPEN);
  officeDoor30.write(OFFICE_DOOR_POS_OPEN);
}

void startBigFan() {
  digitalWrite(12, HIGH); //Establishes forward direction of Channel A
  digitalWrite(9, LOW);   //Disengage the Brake for Channel A
  analogWrite(3, 255);   //Spins the motor on Channel A at full speed
}

void stopBigFan() {
  digitalWrite(9, HIGH);   //Disengage the Brake for Channel A
  analogWrite(3, 0);   //Spins the motor on Channel A at full speed
}

bool isButtonTrue(int button) {
  int buttonState = digitalRead(button);
  if (buttonState == HIGH) {
    return true;
  } else {
    return false;
  }
}

float calculatePercentage(float defaultValue, float defaultPhotoValue, float value, float photoValue) {
  //return  (defaultValue * photoValue / (defaultPhotoValue * value)); 
  return  photoValue / defaultPhotoValue;
  //return (value) / (photoValue); 
}

bool isFireActive(float threshold, float defaultResPhoto[], float defaultResPhotoOn[]) {
  
  for (int floor = 0; floor < 4; floor++) {
      Serial.print("Floor ");
      Serial.print(floor);
      float photoValue = analogRead(resPhoto[floor]);
      //Serial.print("- Sensor: ");
      //Serial.print(photoValue);
      float photoOnValue = analogRead(resPhotoOn[floor]);
      //Serial.print("- Illuminated Sensor: ");
      //Serial.print(photoOnValue);
      float floorFirePercentage = calculatePercentage(defaultResPhoto[floor], defaultResPhotoOn[floor], photoValue, photoOnValue);
      
      Serial.print(" - Percentage: ");
      Serial.println(floorFirePercentage);
      
      if (floorFirePercentage <= threshold) {
        return true;
      }
    }
  
  return false;
}

void setNonFireState() {
  // Windows & Doors: Closed
    for (int floor = 0; floor < 4; floor++) {
      closeWindow(floor);
      closeStaircaseDoor(floor);
    }
    closeRoofWindow();
    // Office Doors: Open
    openOfficeDoors();
}

void setFireState() {
    for (int floor = 0; floor < 4; floor++) {
      openWindow(floor);
      openStaircaseDoor(floor);
    }
    openRoofWindow();
}
