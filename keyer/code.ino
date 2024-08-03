const int LED = 9;
const int dit = A2;
const int dah = A3;
const int key = 4;
const int reset = 3;
const int speed = A1;
const int threshold = 512;

int DPM = 25*50;
float element = 3.0;
float ditLang, dahLang;
int ditStat = 0;
int dahStat = 0;

void setup(){
  pinMode(dit, INPUT);
  pinMode(dah, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(key, OUTPUT);
  digitalWrite(LED, LOW);
  ditLang = 100;
  dahLang = ditLang*element;
}
//need Functions
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
  ditStat = 0;
}

void doDah(){
  keyDown();
  delay(dahLang);
  keyUp();
  dahStat = 0;
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
  /*else if (digitalRead(reset) == HIGH){
    int read = analogRead(speed);
    DPM = DPM + ((read-threshold)*0.01);
    ditLang = (1/DPM)*60*1000;
    dahLang = ditLang*element;
  }*/
}
