
#include <Keypad.h>

#define _R 7
#define _G 8
#define _B 9

#define L1 10
#define L2 11
#define L3 12
#define L4 13

#define _R2 2
#define _G2 3
#define _B2 4

#define L5 5
#define L6 6
#define L7 45
#define L8 46


struct Color {
  Color(): red(0), green(0), blue(0) {}
  Color(byte r, byte g, byte b): red(r), green(g), blue(b) {}
  byte red;
  byte green;
  byte blue;
};

const uint8_t ROWS=1;
const uint8_t COLS=4;
char keys[ROWS][COLS] = {{1,2,3,4}};
byte rowPins[ROWS] = {26};
byte colPins[COLS] = {22, 23, 24, 25};


const uint8_t ROWS2=1;
const uint8_t COLS2=4;
char keys2[ROWS2][COLS2] = {{1,2,3,4}};
byte rowPins2[ROWS2] = {31};
byte colPins2[COLS2] = {27,28,29,30};


Color led[4];
Color led2[4];

uint8_t button_state[4] = {0,0,0,0};

uint8_t button_state2[4] = {0,0,0,0};

Keypad buttons = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

Keypad buttons2 = Keypad(makeKeymap(keys2), rowPins2, colPins2, ROWS2, COLS2);

Color color_states[] = {

  Color(255, 255  , 255 ),
   Color(0  , 255, 255),
 Color(0  , 0, 255  ),
  Color(0  , 255, 255),
  Color(255, 255  , 255 ),
   Color(255  , 255, 0),
};

uint8_t num_color_states = sizeof(color_states) / sizeof(color_states[0]);

void setup() {
  Serial.begin(9600);
   
  pinMode(_R, OUTPUT);
  pinMode(_G, OUTPUT);
  pinMode(_B, OUTPUT);
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(L3, OUTPUT);
  pinMode(L4, OUTPUT);

  pinMode(_R2, OUTPUT);
  pinMode(_G2, OUTPUT);
  pinMode(_B2, OUTPUT);
  pinMode(L5, OUTPUT);
  pinMode(L6, OUTPUT);
  pinMode(L7, OUTPUT);
  pinMode(L8, OUTPUT);
writeLeds();

led[0] = Color (0, 255  , 255 );
led[1] = Color (255, 255  , 255 );
led[2] = Color (255, 255  , 255 );
led[3] = Color (255, 255   , 0);

writeLeds2();
led2[0] = Color (255 , 255  , 0);
led2[1] = Color (255, 255  , 255 );
led2[2] = Color (255, 255  , 255 );
led2[3] = Color (0, 255   , 255);


}

void loop() {

 writeLeds();
 readButtons();

  writeLeds2();
 readButtons2();
}

void readButtons() {
  char key = buttons.getKey();
  if (key && key <= 4) {
    button_state[key-1] = (button_state[key-1] + 1) % num_color_states;
    led[key-1] = color_states[button_state[key-1]];
   
   MIDImessage(176,(25+key),1); //-----------------------------MIDI MESSAGE KEYPAD
  }
}

void readButtons2() {
  char key = buttons2.getKey();
  if (key && key <= 4) {
    button_state2[key-1] = (button_state2[key-1] + 1) % num_color_states;
    led2[key-1] = color_states[button_state2[key-1]];
   
   MIDImessage(176,(30+key),1); //-----------------------------MIDI MESSAGE KEYPAD
  }
}

void writeLeds() {
  digitalWrite(_R, LOW);
  digitalWrite(_G, LOW);
  digitalWrite(_B, LOW);
  analogWrite(L1, 255-led[0].red);
  analogWrite(L2, 255-led[1].red);
  analogWrite(L3, 255-led[2].red);
  analogWrite(L4, 255-led[3].red);
  digitalWrite(_R, HIGH);
  // reds are on now, wait a bit
  delayMicroseconds(10);
  digitalWrite(_R, LOW);
  analogWrite(L1, 255-led[0].green);
  analogWrite(L2, 255-led[1].green);
  analogWrite(L3, 255-led[2].green);
  analogWrite(L4, 255-led[3].green);
  digitalWrite(_G, HIGH);
  // green are on now, wait a bit
  delayMicroseconds(10);
  digitalWrite(_G, LOW);
  analogWrite(L1, 255-led[0].blue);
  analogWrite(L2, 255-led[1].blue);
  analogWrite(L3, 255-led[2].blue);
  analogWrite(L4, 255-led[3].blue);
  digitalWrite(_B, HIGH);
  // blue are on now, wait a bit
  delayMicroseconds(10);
  digitalWrite(_B, LOW);
}


void writeLeds2() {
  digitalWrite(_R2, LOW);
  digitalWrite(_G2, LOW);
  digitalWrite(_B2, LOW);
  analogWrite(L5, 255-led2[0].red);
  analogWrite(L6, 255-led2[1].red);
  analogWrite(L7, 255-led2[2].red);
  analogWrite(L8, 255-led2[3].red);
  digitalWrite(_R2, HIGH);
  // reds are on now, wait a bit
  delayMicroseconds(10);
  digitalWrite(_R2, LOW);
  analogWrite(L5, 255-led2[0].green);
  analogWrite(L6, 255-led2[1].green);
  analogWrite(L7, 255-led2[2].green);
  analogWrite(L8, 255-led2[3].green);
  digitalWrite(_G2, HIGH);
  // green are on now, wait a bit
  delayMicroseconds(10);
  digitalWrite(_G2, LOW);
  analogWrite(L5, 255-led2[0].blue);
  analogWrite(L6, 255-led2[1].blue);
  analogWrite(L7, 255-led2[2].blue);
  analogWrite(L8, 255-led2[3].blue);
  digitalWrite(_B2, HIGH);
  // blue are on now, wait a bit
  delayMicroseconds(10);
  digitalWrite(_B2, LOW);
}

void MIDImessage(byte command, byte data1, byte data2) // --------- NECESSARY, pass values out through standard Midi Command
{
   Serial.write(command);
   Serial.write(data1);//channel
   Serial.write(data2);//value
}
