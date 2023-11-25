/**************************************************
Contributors:       Shreekavin Umasankar, Fawaaz Kamali
                    Siddiqui, Gursahaj Chawla, Yajav 
                    Trivedi, Sam Mamkottil, Joshua 
                    Kollanur, Lemi Miyu
Last Update:      	23 November 2023
===================================================
Description:      	Contains program for a door lock system
                    controlled through a 4x4 matrix keypad.
                    This project was controlled through 
                    an Arduino Mega.
===================================================
Connections:      	R1:     9
                    R2:     8
                    R3:     7
                    R4:     6
                    C1:     5
                    C2:     4
                    C3:     3
                    C4:     2       
                    rs:     42
                    e:      44
                    d4:     51
                    d5:     53
                    d6:     50
                    d7:     52
                    buzzer: 24
                    servo:  13          
**************************************************/


#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>


// Variable declarations
const byte rows = 4;
const byte cols = 4;
char keys [rows][cols] = {
     {'1' , '2' , '3', 'A' },
     {'4' , '5' , '6', 'B'},
     {'7' , '8' , '9', 'C' },
     {'*' , '0' , '#', 'D' }
};
String password = "1234#";
String input = "";
byte rowPins[rows] = {9, 8, 7, 6};
byte colPins[cols] = {5, 4, 3, 2};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);

int rs = 42;
int e = 44;
int d4 = 51;
int d5 = 53;
int d6 = 50;
int d7 = 52;

int buzzerPin = 24;
int servoPin = 13;

// Instantiations - for devices with separate libraries
LiquidCrystal lcd(rs, e, d4, d5, d6, d7);
Servo servo;


void setup() {
    // Initialize Connections
    Serial.begin(9600);
    lcd.begin(16,2);
    pinMode(buzzerPin, OUTPUT);
    servo.attach(servoPin);

}

void loop() {
 
    // Main Program
    // Initialize Conditions
    input = "";
    servo.write(0);

    Serial.println("Enter a number: ");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Enter passcode:");
    lcd.setCursor(0, 1);

    // Collect passcode
    for (int i = 0; i < 5; i++)
    {
        char userInput = getNumber();
        lcd.print(userInput);
        input += userInput;
    }
    delay(1000);
    lcd.clear();
    lcd.setCursor(0,0);

    // validate input
    if (input.equals(password))
    {
        lcd.print("Access granted!");
        unlockDoor();
        for (int i = 0; i < 2; i ++) // very short buzzer beeps
        {
        digitalWrite(buzzerPin, HIGH);
        delay(100);
        digitalWrite(buzzerPin, LOW);
        delay(100);
        }
        delay(5000);
        lockDoor();
    }
    else 
    {
        lcd.print("Access denied!");
        digitalWrite(buzzerPin, HIGH); // long buzzer beep
        delay(1000);
        digitalWrite(buzzerPin, LOW);
        delay(1000);
    }
    delay(1000);
    
    

}

// method to collect individual characters from keypad
char getNumber()
{
    char key = keypad.waitForKey();
    if (key)
    {
        return key;
    }

}

// method to unlock bolt using servo
void unlockDoor()
{
    for (int pos = 0; pos <= 75; pos ++)
    {
        servo.write(pos);
        delay(15);
    }
}

// method to lock bolt using servo
void lockDoor()
{
    for (int pos = 75; pos >= 0; pos --)
    {
        servo.write(pos);
        delay(15);
    }
}
