//left sensor
const int trigL=4;
const int echoL=5;

//right sensor
const int trigR=6;
const int echoR=7;

//motor direction
const int mtrFWD=8;
const int mtrRVS=9;

//button pin
const int btnPin=12;

//----------------IMPORTANT VARIABLES----------------
bool start=false;
bool reverse;
int repeat=6;
int distanceL,distanceR;
//---------------------------------------------------

long durationL,durationR;
int speed=150,StopDelay=750;

void setup() {
  
  //----------OUTPUT PIN----------
  pinMode(LED_BUILTIN,OUTPUT);
  pinMode(trigL, OUTPUT);
  pinMode(trigR, OUTPUT);
  pinMode(mtrFWD, OUTPUT);
  pinMode(mtrRVS, OUTPUT);
  
  //----------INPUT PIN----------
  pinMode(btnPin, INPUT_PULLUP);
  pinMode(echoL, INPUT);
  pinMode(echoR, INPUT);
  
  //Serial begin
  Serial.begin(9600);

  reverse=false;

}

void loop() {

  //press button to start
  ButtonPress();

  //start process
  if(start==true){

    //move left
    if(reverse==false){
      MoveLeft();
      DistanceMeasureL();
      
      //stop and set reverse to true
      if(distanceL<=6){
        reverse=true;
        Stop();
        delay(StopDelay);
      }

    //move right
    }else{
      MoveRight();
      DistanceMeasureR();

      if(distanceR<=6){
        Stop();
        repeat--;
        reverse=false;
        delay(StopDelay);
      }
    }
  }

  //stop and reset condition
  if(repeat==0){
    Stop();
    start=false;
    reverse=false;
    repeat=6;
  }
  
  Serial.print(start);
  Serial.print(reverse);
  Serial.println(repeat);
}

void ButtonPress(){

  int btn=digitalRead(btnPin);
  
  //button press start the process
  if(btn==LOW){
    digitalWrite(LED_BUILTIN, HIGH);
    start=true;
  }else{
    digitalWrite(LED_BUILTIN, LOW);
  }
}

void DistanceMeasureL() {
  digitalWrite(trigL, LOW);
  delayMicroseconds(2);

  digitalWrite(trigL, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigL, LOW);
  
  durationL= pulseIn(echoL, HIGH);
  distanceL= durationL/29/2;

  Serial.println("Distance: " + String(distanceL)+"cm");
  delay(50);
}

void DistanceMeasureR() {
  digitalWrite(trigR, LOW);
  delayMicroseconds(2);

  digitalWrite(trigR, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigR, LOW);
  
  durationR= pulseIn(echoR, HIGH);
  distanceR= durationR/29/2;

  Serial.println("Distance: " + String(distanceR)+"cm");
  delay(50);
}

//Rotate motor to move left
void MoveLeft(){
  digitalWrite(mtrFWD, HIGH);
  digitalWrite(mtrRVS, LOW);
}

//Rotate motor to move right
void MoveRight(){
  digitalWrite(mtrFWD, LOW);
  digitalWrite(mtrRVS, HIGH);
}

//stop everything
void Stop(){
  digitalWrite(mtrFWD, LOW);
  digitalWrite(mtrRVS, LOW); 
}
