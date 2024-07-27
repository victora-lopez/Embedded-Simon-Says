int ledPins[] = {2,3,4,5};
const int MAX_LEVEL = 100;
int sequence[MAX_LEVEL];
int yourSequence[MAX_LEVEL];
int level = 1;
int score = 0;

int velocity = 1000;

void setup() {
  
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);

  for(int i = 0; i < 4; i++)
    pinMode(ledPins[i],OUTPUT);
}

void loop(){
  if (level == 1)
    generate_sequence();//generate a sequence;

  if (digitalRead(A4) == LOW || level != 1)
  { //If start button is pressed or you're winning
  
    show_sequence();    //show the sequence
    get_sequence();     //wait for your sequence
  }
}

void show_sequence(){
  for(int i = 0; i < 4; i++)
    digitalWrite(ledPins[i],LOW);

  for (int i = 0; i < level; i++){
    digitalWrite(sequence[i], HIGH);
    delay(velocity);
    digitalWrite(sequence[i], LOW);
    delay(200);
  }
}

void get_sequence()
{
  int flag = 0; //this flag indicates if the sequence is correct

    for (int i = 0; i < level; i++)
    {
    flag = 0;
    while(flag == 0)
    {
      if (digitalRead(A0) == LOW)
      {
        digitalWrite(5, HIGH);
        yourSequence[i] = 5;
        flag = 1;
        delay(200);
        if (yourSequence[i] != sequence[i]){
          wrong_sequence();
          return;
        }
        digitalWrite(5, LOW);
      }

      if (digitalRead(A1) == LOW){
        digitalWrite(4, HIGH);
        yourSequence[i] = 4;
        flag = 1;
        delay(200);
        if (yourSequence[i] != sequence[i]){
            wrong_sequence();
            return;
        }
        digitalWrite(4, LOW);
      }

      if (digitalRead(A2) == LOW){
        digitalWrite(3, HIGH);
        yourSequence[i] = 3;
        flag = 1;
        delay(200);
        if (yourSequence[i] != sequence[i]){
          wrong_sequence();
          return;
        }
        digitalWrite(3, LOW);
      }

      if (digitalRead(A3) == LOW){
        digitalWrite(2, HIGH);
        yourSequence[i] = 2;
        flag = 1;
        delay(200);
        if (yourSequence[i] != sequence[i]){
          wrong_sequence();
          return;
        }
        digitalWrite(2, LOW);
      }
    }
  }
  right_sequence();

}

void generate_sequence()
{
  randomSeed(millis());

  for (int i = 0; i < MAX_LEVEL; i++)
    sequence[i] = random(2,6);
}
void wrong_sequence()
{    
  for (int i = 0; i < 3; i++)
  {
    for(int i = 0; i < 4; i++)
    	digitalWrite(ledPins[i],HIGH);
    delay(250);
    for(int i = 0; i < 4; i++)
    	digitalWrite(ledPins[i],LOW);
    delay(250);
  }
  level = 1;
  score = 0;
  velocity = 1000; 
}

void right_sequence()
{
  for(int i = 0; i < 4; i++)
    digitalWrite(ledPins[i],LOW);
  delay(250);
  for(int i = 0; i < 4; i++)
    digitalWrite(ledPins[i],HIGH);
  delay(500);
  for(int i = 0; i < 4; i++)
    digitalWrite(ledPins[i],LOW);
  delay(500);

  if(level < MAX_LEVEL)
    level++;
  velocity -= 50; //increase difficulty
}
