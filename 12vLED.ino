#define RED_PIN 14
#define GREEN_PIN 13
#define BLUE_PIN 15

String message;

String strRed;
String strGreen;
String strBlue;

int intRed;
int intGreen;
int intBlue;

void setup() {
  // set baud rate
  Serial.begin(9600);

  // 12V SETUP
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
}

void setLEDS (int ipR, int ipG, int ipB) {
  analogWrite(RED_PIN, ipR);
  analogWrite(GREEN_PIN, ipG);
  analogWrite(BLUE_PIN, ipB);
}

String getSplitValue(String data, char separator, int index) {
  int found = 0;
  int strIndex[] = { 0, -1 };
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
      if (data.charAt(i) == separator || i == maxIndex) {
          found++;
          strIndex[0] = strIndex[1] + 1;
          strIndex[1] = (i == maxIndex) ? i+1 : i;
      }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void loop() {
  // check if serial port has data
  while (Serial.available() > 0) {

    message = Serial.readString();

    strRed = getSplitValue(message, ':', 0);
    strGreen = getSplitValue(message, ':', 1);
    strBlue = getSplitValue(message, ':', 2);

    intRed = strRed.toInt();
    intGreen = strGreen.toInt();
    intBlue = strBlue.toInt();

    setLEDS(intRed, intGreen, intBlue);
    delay(100);
  }
}
