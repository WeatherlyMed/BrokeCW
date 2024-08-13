const int LED = 9;
const int dit = A2;
const int dah = A3;
const int key = 4;
const int cqButton = 5;
const int setCallSignButton = 6;
const int qrlButton = 7;
const int deButton = 8;
const int kButton = 10;
const int reset = 3;
const int speed = A1;
const int threshold = 512;

int DPM = 25 * 50;
float element = 3.0;
float ditLang, dahLang;
int ditStat = 0;
int dahStat = 0;

String morseCode = "";  
String userCallSign = ""; 
unsigned long lastInputTime = 0;
const unsigned long pauseTime = 1000; 

String morseLetters[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",
                         "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",
                         "..-", "...-", ".--", "-..-", "-.--", "--..", "-----", ".----", "..---",
                         "...--", "....-", ".....", "-....", "--...", "---..", "----."};

char letters[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
                  'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
                  'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3',
                  '4', '5', '6', '7', '8', '9'};

void setup(){
  pinMode(dit, INPUT);
  pinMode(dah, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(key, OUTPUT);
  pinMode(cqButton, INPUT);
  pinMode(setCallSignButton, INPUT);
  pinMode(qrlButton, INPUT);
  pinMode(deButton, INPUT);
  pinMode(kButton, INPUT);
  Serial.begin(9600); 
  digitalWrite(LED, LOW);
  ditLang = 100;
  dahLang = ditLang * element;
}

void keyUp(){
  digitalWrite(key, HIGH);
  digitalWrite(LED, LOW);
}

void keyDown(){
  digitalWrite(key, LOW);
  digitalWrite(LED, HIGH);
}

void doDit(){
  keyDown();
  delay(ditLang);
  keyUp();
  morseCode += "."; 
  ditStat = 0;
  lastInputTime = millis(); 
}

void doDah(){
  keyDown();
  delay(dahLang);
  keyUp();
  morseCode += "-"; 
  dahStat = 0;
  lastInputTime = millis(); 
}

void decodeMorse(){
  for (int i = 0; i < sizeof(morseLetters)/sizeof(morseLetters[0]); i++) {
    if (morseCode == morseLetters[i]) {
      Serial.print(letters[i]);
      break;
    }
  }
  morseCode = ""; 
}

void sendCQ(){
  String cqSequence = "-.-.--.-.--.-."; 
  for (int i = 0; i < cqSequence.length(); i++) {
    if (cqSequence[i] == '.') {
      doDit();
    } else if (cqSequence[i] == '-') {
      doDah();
    }
    delay(ditLang); 
  }
  delay(dahLang * 2); 
}

void sendCallSign(String callSign){
  for (int i = 0; i < callSign.length(); i++) {
    char c = callSign[i];
    if (c == ' ') {
      delay(dahLang * 2); 
    } else {
      String morse = getMorseCode(c);
      for (int j = 0; j < morse.length(); j++) {
        if (morse[j] == '.') {
          doDit();
        } else if (morse[j] == '-') {
          doDah();
        }
        delay(ditLang); 
      }
      delay(dahLang); 
    }
  }
  delay(dahLang * 2); 
}

String getMorseCode(char c){
  c = toupper(c);
  for (int i = 0; i < sizeof(letters)/sizeof(letters[0]); i++) {
    if (c == letters[i]) {
      return morseLetters[i];
    }
  }
  return ""; 
}

void sendQRL(){
  String qrlSequence = "--.-.-...-.."; 
  for (int i = 0; i < qrlSequence.length(); i++) {
    if (qrlSequence[i] == '.') {
      doDit();
    } else if (qrlSequence[i] == '-') {
      doDah();
    }
    delay(ditLang); 
  }
  delay(dahLang * 2); 
}

void sendDE(){
  String deSequence = "-....";
  for (int i = 0; i < deSequence.length(); i++) {
    if (deSequence[i] == '.') {
      doDit();
    } else if (deSequence[i] == '-') {
      doDah();
    }
    delay(ditLang); 
  }
  delay(dahLang * 2); 
}

void sendK(){
  String kSequence = "-.-";
  for (int i = 0; i < kSequence.length(); i++) {
    if (kSequence[i] == '.') {
      doDit();
    } else if (kSequence[i] == '-') {
      doDah();
    }
    delay(ditLang); 
  }
  delay(dahLang * 2); 
}

void loop(){
  ditStat = analogRead(dit);
  dahStat = analogRead(dah);
  if (ditStat >= 900){
    doDit();
    delay(ditLang);
  }
  else if (dahStat >= 900){
    doDah();
    delay(ditLang);
  }
  
  if (digitalRead(cqButton) == HIGH){
    sendCQ();
  }
  
  if (digitalRead(setCallSignButton) == HIGH && userCallSign.length() > 0){
    sendCallSign(userCallSign);
  }

  if (digitalRead(qrlButton) == HIGH){
    sendQRL();
  }

  if (digitalRead(deButton) == HIGH){
    sendDE();
  }

  if (digitalRead(kButton) == HIGH){
    sendK();
  }
  
  if (millis() - lastInputTime > pauseTime && morseCode != "") {
    decodeMorse();
  }
}
