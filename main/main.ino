int size = 100;
int current_move = 0;
int move_list[100];


int buzzer = 6;
int lights[4] = {2,3,4,5};
int buttons[4] = {12,13,10,11};
int notes[4] = {55,110,220,440};
bool isWaiting = false;
void generate_moves()
{
  for(int i = 0; i < size;i++)
  {
    move_list[i]= random(0, 4);
  }
}


int* get_input()
{
  int inputs[4] = {0,0,0,0};
  for(int i = 0; i < 4; i++)
  {
    if(digitalRead(buttons[i]) == 0)
    {
      Serial.println(i);
      inputs[i] = 1;
    }
  }
  return inputs;
}

void play_move_to(int index)
{
  for(int i = 0; i < index;i++)
  {
    int color = move_list[i];
    for(int i = 0;i<4;i++)
    {
      digitalWrite(lights[i],0);
    }
    delay(100);
    digitalWrite(lights[color],1);
    tone(buzzer,notes[color]);
    delay(100);
    noTone(buzzer);
  }
}

void setup() {
  generate_moves();
  for(int i = 0; i < 4;i++)
  {
    pinMode(lights[i],OUTPUT);
    pinMode(buttons[i],INPUT_PULLUP);
  }
  pinMode(buzzer,OUTPUT);
  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  int* inp = get_input();
}
