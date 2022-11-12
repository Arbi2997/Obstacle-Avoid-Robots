#include <Servo.h>
#define Trig 8
#define Echo 9

//Ultrasonik/Jarak
int duration;
int distance;
int JarakKanan = 0;
int JarakKiri = 0;

//Motor Kanan
int In1 = 22;
int In2 = 23;
int In3 = 24;
int In4 = 25;
int Ena = 2;
int Enb = 3;

//Motor Kiri
int in1 = 26;
int in2 = 27;
int in3 = 28;
int in4 = 29;
int ena = 4;
int enb = 5;

//Speed & GigiBiru
int Speed = 100;
int data;

//Mg90
int pin_servo = 6;
Servo myservo;
int sudut = 0;

void setup(){
  Serial.begin(9600);
  myservo.write(90);

  //Ultrasonik/Jarak+Mg90
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  myservo.attach(pin_servo);
  
  //Motor Kanan
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);
  pinMode(Ena, OUTPUT);
  pinMode(Enb, OUTPUT);

  //Motor Kiri
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(ena, OUTPUT);
  pinMode(enb, OUTPUT);
}

void loop(){
  if(distance <= 25){
    Stop();
    delay(100);
    Backward();
    delay(500);
    Stop();
    delay(200);
    JarakKanan = lihatKanan();
    delay(200);
    JarakKiri = lihatKiri();
    delay(200);

    if(JarakKanan>=JarakKiri){
      MajuKanan();
      Stop();
    }
    else{
      MajuKiri();
      Stop();
    }
  }
  else{
    Forward();  
  }
  BacaJarak();
}
//_______________________________________ALL_FUNCTION________________________
void Stop(){
  digitalWrite(In1, LOW);     //Backward
  digitalWrite(In2, LOW);    //Forward
  digitalWrite(In3, LOW);     //B
  digitalWrite(In4, LOW);    //F
  digitalWrite(Ena, Speed);
  digitalWrite(Enb, Speed);

  digitalWrite(in1, LOW);     //F
  digitalWrite(in2, LOW);      //B
  digitalWrite(in3, LOW);     //F
  digitalWrite(in4, LOW);      //B
  digitalWrite(ena, Speed);
  digitalWrite(enb, Speed);  
}

void Forward(){
  digitalWrite(In1, LOW);     //Backward
  digitalWrite(In2, HIGH);    //Forward
  digitalWrite(In3, LOW);     //B
  digitalWrite(In4, HIGH);    //F
  digitalWrite(Ena, Speed);
  digitalWrite(Enb, Speed);

  digitalWrite(in1, HIGH);     //F
  digitalWrite(in2, LOW);      //B
  digitalWrite(in3, HIGH);     //F
  digitalWrite(in4, LOW);      //B
  digitalWrite(ena, Speed);
  digitalWrite(enb, Speed);  
}

void Backward(){
  digitalWrite(In1, HIGH);     //Backward
  digitalWrite(In2, LOW);    //Forward
  digitalWrite(In3, HIGH);     //B
  digitalWrite(In4, LOW);    //F
  digitalWrite(Ena, Speed);
  digitalWrite(Enb, Speed);

  digitalWrite(in1, LOW);     //F
  digitalWrite(in2, HIGH);      //B
  digitalWrite(in3, LOW);     //F
  digitalWrite(in4, HIGH);      //B
  digitalWrite(ena, Speed);
  digitalWrite(enb, Speed);  
}

void MajuKanan(){
  digitalWrite(In1, HIGH);     //Backward
  digitalWrite(In2, LOW);    //Forward
  digitalWrite(In3, HIGH);     //B
  digitalWrite(In4, LOW);    //F
  digitalWrite(Ena, Speed);
  digitalWrite(Enb, Speed);

  digitalWrite(in1, HIGH);     //F
  digitalWrite(in2, LOW);      //B
  digitalWrite(in3, HIGH);     //F
  digitalWrite(in4, LOW);      //B
  digitalWrite(ena, Speed);
  digitalWrite(enb, Speed); 
  delay(700);

  Forward();
}

void MajuKiri(){
  digitalWrite(In1, LOW);     //Backward
  digitalWrite(In2, HIGH);    //Forward
  digitalWrite(In3, LOW);     //B
  digitalWrite(In4, HIGH);    //F
  digitalWrite(Ena, Speed);
  digitalWrite(Enb, Speed);

  digitalWrite(in1, LOW);     //F
  digitalWrite(in2, HIGH);      //B
  digitalWrite(in3, LOW);     //F
  digitalWrite(in4, HIGH);      //B
  digitalWrite(ena, Speed);
  digitalWrite(enb, Speed);
  delay(700);

    Forward();
}

int lihatKiri(){
  myservo.write(0);
  delay(500);
  int jarak = BacaJarak();
  delay(100);
  myservo.write(90);
  return jarak;
  delay(100); 
}

int lihatKanan(){
  myservo.write(180);
  delay(500);
  int jarak = BacaJarak();
  delay(100);
  myservo.write(90);
  return jarak;
  delay(100); 
}

int BacaJarak(){
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);

  duration = pulseIn(Echo, HIGH);
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  return distance;
}
