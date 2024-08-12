const int LED = 9;
const int dit = A2;
const int dah = A3;
const int key = 4;
const int reset = 3;
const int speed = A1;
const int threshold = 512;

int DPM = 25 * 50;
float element = 3.0;
float ditLang, dahLang;
int ditStat = 0;
int dahStat = 0;

String morseCode = "";  
unsigned long lastInputTime = 0;
const unsigned long pauseTime = 1000; 

String morseLetters[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---","-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", "-----", ".----", "..---","...--", "....-", ".....", "-....", "--...", "---..", "----."};

char letters[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J','K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T','U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3','4', '5', '6', '7', '8', '9'};

void setup(){
  pinMode(dit, INPUT);
  pinMode(dah, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(key, OUTPUT);
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
  
  if (millis() - lastInputTime > pauseTime && morseCode != "") {
    decodeMorse();
  }
}

