const int microsw=3;
int res=0;
int score=0;



void setup() {
  // put your setup code here, to run once:
  pinMode(microsw,INPUT);
  digitalWrite(microsw,LOW); 
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  res=digitalRead(microsw);
  if (res==HIGH){
    score++;
  }
  Serial.print("score :");
  Serial.println(score);
  delay(100);

}
