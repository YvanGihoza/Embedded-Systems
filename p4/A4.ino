#define FREQ_A4_HZ 440
#define FREQ_D4_HZ 587.33

//shared varialable
//int  treshold = 512;
int sensorPin = A0;
const char menuMain[] = "***Main Menu***\n1: Arm Security Sytesm\n2: Test Light Sensor\n3: Test Alarm\n4: Set Light Sensor Threshold\n5: Set Keycode\n";
char my_buffer[50] = "";
int i = 0;

//prototypes for the tasks
void lightSensor(void* DS);
void playingTone(void* DS);
void readingPort(void* DS);
void checkInput(void* DS);


void stripEOL(char string[], int n)
{
    char *token;
    int i;
    for(i = 0; i < n; i++)
    {
        if(string[i] == '\n' || string[i] == '\r')
          string[i] = '\0';
    }
}
//serial code
void ReadString()
{
  int i = 0;
  int keep_reading = 1;
  while(keep_reading){
    while(Serial.available() == 0);
    my_buffer[i] = Serial.read();
    if(my_buffer[i] == '\n'){
      keep_reading = 0;
    }
    if(i == 49){
      keep_reading = 0;
    }
    i+=1;
  } 
 
 stripEOL(my_buffer,50);
}

//light sensor struct 
typedef struct light{
  //treshold val
  int  treshold = 512;
  //adc value
  int adc;
  bool tresholdBroken = false;
}light;

//playing tone struct 
typedef struct play{
  //states
  int timeState;
  char noteState;
}play;

//reading input struct 
typedef struct reading{
  //ptr to the read buffer
  char *buff;
  //index
  int index;
  //return value
  int val; 
}reading;

//checking input struct 
typedef struct checking{
  int keyCode;
  int input;
}checking;

//TCB
typedef struct {
   void* taskDataptr;
   void (*taskPtr)(void*);
} TCB;

//tasks
TCB task[4];
TCB* TCBptr1 = &task[0];
TCB* TCBptr2 = &task[1];
TCB* TCBptr3 = &task[2];
TCB* TCBptr4 = &task[3];

light lightData;
play playData;
reading readingData;
checking checkingData;


//menu
void DisplayMenu(const char menu[])
{
    char * copy = strdup(menu);
    char * tokenMenu = strtok(copy, "\n");
    while( tokenMenu != NULL)
    {
      Serial.println(tokenMenu);
      tokenMenu = strtok(NULL, "\n");
    }
    Serial.println("======================");
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while(!Serial);
  pinMode(A1, INPUT);
  pinMode(5, OUTPUT);
  task[0].taskDataptr = &lightData;
  task[0].taskPtr = &lightSensor;

  task[1].taskDataptr = &playData;
  task[1].taskPtr = &playingTone;

  task[2].taskDataptr = &readingData;
  task[2].taskPtr = &readingPort;

  task[3].taskDataptr = &checkingData;
  task[3].taskPtr = &checkInput; 

  
  DisplayMenu(menuMain);
  //input read
  readingPort(TCBptr3->taskDataptr);
  
  
}

void loop() {
  
  
}

//light sensor function
void lightSensor(void* DS)
{
  light* like = (light*) DS;
  like->adc = analogRead(A1);
  int i =0;
  for(; i < 100; i++)
  {
    Serial.println(like->adc);
  }
  if(like->adc > like->treshold)
  {
    like -> tresholdBroken = true; 
    
  }
}


//playing tone function
void playingTone(void* DS)
{
  play* Tone = (play*) DS;
  int periodA = 1000000/FREQ_A4_HZ;
  int halfPeriodA = periodA/2;
  int periodD = FREQ_D4_HZ/2;
  int halfPeriodD = periodD/2;
  int numIterations = 1000;

  int i = 0;
  int x = 0;
  while(1)
  {
      //play A
      if(x == 0 )
      {
        analogWrite(A0, 255);
        delayMicroseconds(halfPeriodA);
        analogWrite(A0, 0);
        delayMicroseconds(halfPeriodA);
      }
      //play D
      else{
        analogWrite(A0, 8);
        delayMicroseconds(halfPeriodD);
        analogWrite(A0, 0);
        delayMicroseconds(halfPeriodD);
      }
    x = (x+1)%2;
  } 
}
//testing the alarm
void alarmTest(void* DS)
{
  play* Tone = (play*) DS;
}

//setting the treshold function
void setTreshold(void* DS)
{
  light* setTresh = (light*) DS;
  Serial.println("Please provide type in the new treshold: ");
  ReadString();
  int tresh = my_buffer[0];
  if(tresh > 0 && tresh < 1024)
    setTresh->treshold  = tresh;  
  Serial.println("New treshold: ");
  Serial.println(tresh);
}
//setting the keycode function
int setKeyCode(void* DS)
{
  checking* setKey = (checking*) DS;
  Serial.println("Please provide type in the key code ");
  ReadString();
  int key = my_buffer[0];
  if(key > 0 && key < 9999)
    return setKey->keyCode  = key;
  else 
    return -1;
}

// serial read function (task[3])
void readingPort(void* DS)
{
  reading* input = (reading*) DS;
  input->buff = my_buffer;
  input->index = 0;
  int keep_reading = 1;
  while(keep_reading){
    while(Serial.available() == 0);
    my_buffer[input->index] = Serial.read();
    if(my_buffer[input->index] == '\n'){
      keep_reading = 0;
    }
    input->index ++;
  }
  //return value
  input->val = atoi(my_buffer);
}

//check input function
void checkInput(void* DS)
{
  checking* input = (checking*) DS;
  reading* serialRead = (reading*) DS;
  //check the return value of the read serial
  if(serialRead->val > 0 && serialRead->val < 9999)
     input->keyCode = serialRead->val;
  else
     input->keyCode = -1;
}
