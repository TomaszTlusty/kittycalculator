#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

byte eyeOpen[8] = {
  B01110,
  B11111,
  B11011,
  B11011,
  B11011,
  B11111,
  B01110,
  B00000
};
byte eyeClosed[8] = {
  B00000,
  B00000,
  B00000,
  B11111,
  B11111,
  B00000,
  B00000,
  B00000
};

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'A','3','2','1'},
  {'B','6','5','4'},
  {'C','9','8','7'},
  {'D','#','0','*'}
};

byte rowPins[ROWS] = {2,3,4,5};
byte colPins[COLS] = {A0,A1,A2,A3};

Keypad keypad = Keypad(
  makeKeymap(keys),
  rowPins,
  colPins,
  ROWS,
  COLS
);

void drawEyes()
{
  lcd.setCursor(4,0);
  lcd.write(0);
  lcd.setCursor(11,0);
  lcd.write(0);
}

void closeEyes()
{
  lcd.setCursor(4,0);
  lcd.write(1);
  lcd.setCursor(11,0);
  lcd.write(1);
}

void blink()
{
  closeEyes();
  delay(120);
  drawEyes();
}

String input = "";
float firstNumber = 0;
char operation = 0;
bool hasOperation = false;

void refreshDisplay()
{
  lcd.setCursor(0,1);
  lcd.print("                ");
  lcd.setCursor(0,1);
  lcd.print(input);
}

void handleOperator(char op)
{
  if (input.length() == 0 && !hasOperation)
    return; 

  if (input.length() > 0) {
    firstNumber = input.toFloat();
  }
  operation = op;
  hasOperation = true;
  input = "";
  refreshDisplay();
}

void calculate()
{
  if (!hasOperation)
    return;

  float secondNumber = input.toFloat();
  float result;

  switch (operation)
  {
    case '+':
      result = firstNumber + secondNumber;
      break;
    case '-':
      result = firstNumber - secondNumber;
      break;
    case '*':
      result = firstNumber * secondNumber;
      break;
    case '/':
      if (secondNumber == 0) {
        lcd.clear();
        drawEyes();
        lcd.setCursor(0,1);
        lcd.print("Err /0");
        delay(2000);
        input = "";
        hasOperation = false;
        lcd.clear();
        drawEyes();
        return;
      }
      result = firstNumber / secondNumber;
      break;
    default:
      result = secondNumber;
      break;
  }

  lcd.clear();
  drawEyes();
  lcd.setCursor(0,1);
  lcd.print(result);
  delay(2000);

  input = String(result);
  hasOperation = false;
  lcd.clear();
  drawEyes();
}

void resetCalc()
{
  input = "";
  operation = 0;
  hasOperation = false;
  firstNumber = 0;
  lcd.clear();
  drawEyes();
}

// ================= Auto Blink for eyes =================
unsigned long lastBlink = 0;
unsigned long blinkDelay = 4000;

void idleBlink()
{
  if(millis() - lastBlink > blinkDelay)
  {
    blink();
    lastBlink = millis();
    blinkDelay = random(3000,7000);
  }
}

void setup()
{
  Serial.begin(9600);
  randomSeed(analogRead(A5));
  lcd.init();
  lcd.backlight();
  lcd.createChar(0,eyeOpen);
  lcd.createChar(1,eyeClosed);
  lcd.clear();
  drawEyes();
  lastBlink = millis();
}

void loop()
{
  idleBlink();
  char key = keypad.getKey();
  if(key)
  {
    Serial.println(key);
    blink();

    if(key >= '0' && key <= '9')
    {
      input += key;
    }
    else if(key == 'A')
    {
      handleOperator('+');
    }
    else if(key == 'B')
    {
      handleOperator('-');
    }
    else if(key == 'C')
    {
      handleOperator('*');
    }
    else if(key == 'D')
    {
      handleOperator('/');
    }
    else if(key == '#')
    {
      calculate();
      lastBlink = millis();
      return;
    }
    else if(key == '*')
    {
      resetCalc();
      lastBlink = millis();
      return;
    }

    refreshDisplay();
    lastBlink = millis();
  }
}