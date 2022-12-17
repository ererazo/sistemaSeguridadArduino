#include <Keypad.h>
#include <LiquidCrystal.h>
#include <AsyncTaskLib.h>
#define SPEAKER_PIN 22

//-----------------------------------------------------------------
const int redPin = 8; // R petal on RGB LED module connected to digital pin 11
const int greenPin = 10; // G petal on RGB LED module connected to digital pin 9
const int bluePin = 9; // B petal on RGB LED module connected to digital pin 10
//-----------------------------------------------------------------

//-----------------------------------------------------------------
const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {23, 25, 27, 29}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {31, 33, 35}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
//-----------------------------------------------------------------

//-----------------------------------------------------------------
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
//-----------------------------------------------------------------

//-----------------------------------------------------------------
String password = "";
String passwordMask = "";
const String clave = "123456";
int contKeyPress = 0;
int contIntentos = 0;
int iniKeyPress = 0;
//-----------------------------------------------------------------

//-----------------------------------------------------------------
void color (unsigned char red, unsigned char green, unsigned char blue);
void printLCD(String txt);
void verificarPassword();
void finishPassword();
void soundBloqueo();
//-----------------------------------------------------------------

//-----------------------------------------------------------------
AsyncTask keyPress(4000, true, []() { finishPassword(); });
//-----------------------------------------------------------------

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void setup() {
  pinMode(redPin, OUTPUT); // sets the redPin to be an output
  pinMode(greenPin, OUTPUT); // sets the greenPin to be an output
  pinMode(bluePin, OUTPUT); // sets the bluePin to be an output  
  lcd.begin(16, 2);
  pinMode(SPEAKER_PIN, OUTPUT);
  keyPress.Start();
}

//-----------------------------------------------------------------

void loop() {
  keyPress.Update();
  if (contIntentos == 3) {
    color(255, 255, 0);
    printLCD("BLOQUEADO");
    soundBloqueo();
    delay(3000);
    contIntentos = 0;
    contKeyPress = 0;
    iniKeyPress = 0;
    color(0, 0, 0);
  } else if (contKeyPress == 6) {
    verificarPassword();
  } else if (contKeyPress == 0){
    iniKeyPress = 0;
    lcd.setCursor(0, 0);
    lcd.print("DIGITE CLAVE:");
  }

  char key = keypad.getKey();
  if (key) {
    keyPress.Reset();
    if (contKeyPress < 6) {
      iniKeyPress = 1;
      password = password + key;
      passwordMask = passwordMask + "*";
      contKeyPress++;
    }
    lcd.setCursor(0, 1);
    lcd.print(passwordMask);
  }

}

//-----------------------------------------------------------------

void color (unsigned char red, unsigned char green, unsigned char blue) {
  analogWrite(redPin, red);
  analogWrite(bluePin, blue);
  analogWrite(greenPin, green);
}

//-----------------------------------------------------------------

void verificarPassword() {
  lcd.clear();
  if (password.equals(clave)) {
    color(255, 0, 0);
    printLCD("BIENVENIDO");
    delay(7000);
  } else {
    contIntentos++;
    color(0, 0, 255);
    printLCD("ERROR");
  }
  password = "";
  passwordMask = "";
  contKeyPress = 0;
  delay(1500);
  color(0, 0, 0);
}

//-----------------------------------------------------------------

void printLCD(String txt) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(txt);
}

//-----------------------------------------------------------------

void finishPassword() {
  if (iniKeyPress == 1) {
    contKeyPress = 6;
  }
}

//-----------------------------------------------------------------

void soundBloqueo() {
  tone(SPEAKER_PIN, 262, 250);
  delay(1000);
  tone(SPEAKER_PIN, 262, 250);
  delay(1000);
  tone(SPEAKER_PIN, 262, 250);
  delay(1000);
  tone(SPEAKER_PIN, 262, 250);
  delay(1000);
  tone(SPEAKER_PIN, 262, 250);
  delay(1000);
  tone(SPEAKER_PIN, 262, 250);
  delay(1000);
  tone(SPEAKER_PIN, 262, 250);
  delay(1000);
  tone(SPEAKER_PIN, 262, 250);
  delay(1000);
  tone(SPEAKER_PIN, 262, 250);
  delay(1000);
  tone(SPEAKER_PIN, 262, 250);
  delay(1000);
}

//-----------------------------------------------------------------
