#define buzzer 3
#define ir 4
#define fire 5
#define ldr 6
#define button 7
#define vib 2
#define trig 8
#define echo 9


unsigned int d,obstacle,fire_state,light_intensity,sw; void VIB();

int ultra();

void send_sms(String phno, String data);

bool vib_flag;

void setup() {
  
Serial.begin(9600);
pinMode(ir, INPUT); pinMode(fire, INPUT); pinMode(ldr, INPUT); pinMode(button,

INPUT); pinMode(vib, INPUT); pinMode(echo, INPUT); pinMode(trig, OUTPUT); pinMode(buzzer, OUTPUT); attachInterrupt(digitalPinToInterrupt(vib), VIB, FALLING);

}



void loop() {

digitalWrite(buzzer,LOW);

d = ultra();

obstacle = digitalRead(ir); fire_state = digitalRead(fire); light_intensity = digitalRead(ldr); sw = digitalRead(button);

if (d < 5)

{
digitalWrite(buzzer,HIGH);delay(1000);

}

if (obstacle == LOW)

{

digitalWrite(buzzer,HIGH);

Serial.println("OBSTACLE DETECTED");delay(1000);

}

if (fire_state == LOW)

{

digitalWrite(buzzer,HIGH);

send_sms("9566987610","FIRE DETECTED");

}

if (sw == HIGH)

{

send_sms("9566987610","I AM AT EMERGENCY SITUATION");

}

if (light_intensity == LOW)

{

Serial.println("DAY TIME");

}

if (vib_flag == 1)

{

send_sms("9566987610","BLIND PERSON FELL DOWN"); vib_flag=0;

}

}

void VIB()

{

if (digitalRead(vib) == 0)

{

vib_flag = 1;

}

}

int ultra()

{

digitalWrite(trig, LOW);

delay(10);

digitalWrite(trig, HIGH);
delay(10);

digitalWrite(trig, LOW);

int duration = pulseIn(echo, HIGH);

int distance = (duration * 0.034) / 2;

return distance;

}


void send_sms(String phno, String data)

{

Serial.println("AT");

delay(100);

Serial.println("AT+CMGF=1"); //msg mode

delay(100);

Serial.println("AT+CMGS=\"+91" + phno + "\"\r");

delay(100);

Serial.println(data);

delay(100);

Serial.println((char)26);

delay(1200);

}
