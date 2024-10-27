int size = 100;
int current_move = 0;
int user_current_move = 0;
int* move_list;

unsigned long last_test = 0;
unsigned long min_delay = 240;

int buzzer = 6;
int inputs[4] = {0,0,0,0};
int lights[4] = {2,3,4,5};
int buttons[4] = {12,13,10,11};
int notes[4] = {55,110,220,440};
bool isWaiting = false;


int loser_song[5] = {55,65,233,20,333};

void generate_moves()
{
  for(int i = 0; i < size;i++)
  {
    move_list[i]= random(0, 4);
  }
}


void get_input()
{
  for(int i = 0; i < 4; i++)
  {
    inputs[i] = 0;
    if(digitalRead(buttons[i]) == 0)
    {
      inputs[i] = 1;
      
    }
  }
  
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
    delay(150);

    digitalWrite(lights[color],1);
    tone(buzzer,notes[color]);
    delay(150);
    noTone(buzzer);
  }
}

void light_up_leds_input()
{
   for(int i = 0;i<4;i++)
  {
    digitalWrite(lights[i],0);
    noTone(buzzer);
  }
  for(int i = 0;i < 4;i++)
  {
    if(inputs[i])
    {
      digitalWrite(lights[i],1);
      tone(buzzer,notes[i]);
    }
  }
}

//TODO:
int check_move() //this is checking 24/7 make condition checking systeme if input is diff then 0,0,0,0
{
  unsigned long now = millis();
  unsigned long diff = now - last_test;
    for(int i = 0; i < 4;i++)
    {
      if(inputs[i] == 1)
      {
        if(diff > min_delay)
          {
            last_test = now;
            if(user_current_move < 100)
            {
              if(i == move_list[user_current_move])
              {
                return 1;
              }
              else
                return -1;
            }
              
          }
      }
    } 
    return 0;
}
  

void lose_animation()
{
  for(int j = 0;j < 5;j++)
  {
    for(int i = 0;i < 4;i++)
    {
      digitalWrite(lights[i],0);
    }
    delay(150);
    for(int i = 0;i < 4;i++)
    {
      digitalWrite(lights[i],1);
    }
    delay(150);
  }
}

void setup() {
  move_list = (int*)malloc(100 * sizeof(int));

  randomSeed(analogRead(0));
  generate_moves();
  for(int i = 0; i < 4;i++)
  {
    pinMode(lights[i],OUTPUT);
    pinMode(buttons[i],INPUT_PULLUP);
  }
  pinMode(buzzer,OUTPUT);
  Serial.begin(115200);
}

void reset()
{
  generate_moves();
  current_move = 0;
  user_current_move = 0;
  isWaiting = false;
}


void loop() {
  // put your main code here, to run repeatedly:
 
  if(!isWaiting)
  {
    current_move++;
    Serial.print("Current move :");
    Serial.println(current_move);
    play_move_to(current_move);
    isWaiting = true;
  }
  else
  {
    get_input();
    light_up_leds_input();
    int test = check_move();
    if(test == -1)
    {
      lose_animation();
      get_input();
      light_up_leds_input();
      reset();
      delay(2000);
    }
    else if(test)
    {
      user_current_move++;
      if(user_current_move >= current_move)
      {
        isWaiting = false;
        user_current_move = 0;
      }
    }
  }
}
