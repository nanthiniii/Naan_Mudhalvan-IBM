#define TRIG_PIN   23 

#define ECHO_PIN   22 

#define BUZZER_PIN 2 

#define DISTANCE_THRESHOLD 50 



float duration_us, distance_cm;



void setup() {

  Serial.begin (9600);         

  pinMode(TRIG_PIN, OUTPUT);   

  pinMode(ECHO_PIN, INPUT);    

  pinMode(BUZZER_PIN, OUTPUT); 

}



void loop() {

  digitalWrite(TRIG_PIN, HIGH);

  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);



  duration_us = pulseIn(ECHO_PIN, HIGH);

  // calculate the distance

  distance_cm = 0.017 * duration_us;



  if (distance_cm < DISTANCE_THRESHOLD)

    digitalWrite(BUZZER_PIN, HIGH); 

  else

    digitalWrite(BUZZER_PIN, LOW);  



  Serial.print("distance: ")

  Serial.print(distance_cm);

  Serial.println(" cm");



  delay(500);

}
