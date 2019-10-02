/* Yvan Gihoza
 *  010785599
 *  Assignment #3
 */
 
#define USER_LINE_MAX 128 
char userLine[USER_LINE_MAX];
#define NUMBER_OF_SONGS 4
#define MAX_SONG_LENGTH 64
#define NOTE_A 0
#define NOTE_B 1
#define NOTE_C 2
#define NOTE_D 3
#define NOTE_E 4
#define NOTE_F 5
#define NOTE_G 6
#define NOTE_R 7
#define STR_LENGTH 100

#define FREQ_A4_HZ 440
#define FREQ_B4_HZ 493
#define FREQ_C4_HZ 261
#define FREQ_D4_HZ 293
#define FREQ_E4_HZ 329
#define FREQ_F4_HZ 349
#define FREQ_G4_HZ 392
#define FREQ_R4_HZ 0

#define HALFPERIOD_G4_US 1276 // delay in microseconds


char songTitle [NUMBER_OF_SONGS][STR_LENGTH]={" Title1"," Title2"," Title3"," Title4"};
// "B2 A2 G2 R0 R0 R0"
uint8_t song1[NUMBER_OF_SONGS][MAX_SONG_LENGTH] =
{{(NOTE_B<<5)+2 ,(NOTE_A<<5) +2,(NOTE_G<<5) +2 },{NOTE_R<<5},{NOTE_R<<5},{NOTE_R<<5}};
uint8_t song[NUMBER_OF_SONGS][MAX_SONG_LENGTH] =
{{(NOTE_B<<5)+1 ,(NOTE_A<<5) +1,(NOTE_G<<5) +1 },{(NOTE_R<<5)+8},{(NOTE_R<<5)+0},{NOTE_R<<5}};
uint8_t song2[NUMBER_OF_SONGS][MAX_SONG_LENGTH] =
{{(NOTE_B<<5)+2 ,(NOTE_A<<5) +2,(NOTE_G<<5) +2 },{NOTE_R<<5},{NOTE_R<<5},{NOTE_R<<5}};
uint8_t song3[NUMBER_OF_SONGS][MAX_SONG_LENGTH] =
{{(NOTE_B<<5)+2 ,(NOTE_A<<5) +2,(NOTE_G<<5) +2 },{NOTE_R<<5},{NOTE_R<<5},{NOTE_R<<5}};
// some initial song with notes
const char menuMain[] = "***Main Menu***\n1: List Song\n2: Play Song\n3: Create Song\n";
const char menuPlay[] = "Play Menu\nSearch By Title\nNumber\n";

char my_buffer[50] = "";
//
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
   // put your main code here, to run repeatedly:
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

//menu function
uint8_t DisplayMenu(const char menu[])
{
    // Make a duplicate 
    char * copy = strdup(menu);

    char * tokenMenu = strtok(copy, "\n");

    while( tokenMenu != NULL)
    {
      Serial.println(tokenMenu);
      tokenMenu = strtok(NULL, "\n");
    }
    Serial.println("======================");
    Serial.println("Please Enter Choice:");
    ReadString();
    int  chooseMenuType = my_buffer[0];
    switch(chooseMenuType)
    {
       //listing the songs
       case '1':
       {
          ListSongs(songTitle);
          ReadString();
        break;
       }
        //playing the songs
        case '2':
        {
         Serial.println();
         Serial.println("====Play Song Menu====");
         Serial.println("1: Play By Number ");
         Serial.println("2: Search By Title");
         Serial.println("======================");
         Serial.println("Please Enter Choice:");
         Serial.println();
         Serial.println();
         ReadString();
         int  choice = my_buffer[0];
         if(choice == '1')
         {
            ListSongs(songTitle);
            ReadString();
            int songToPlay = my_buffer[0];
            PlaySong(song[songToPlay]);
         }
         if(choice == '2')
         {
            Serial.println("Please Enter the name of the song");
            ReadString();
            int songToPlay = my_buffer[0];
            PlaySong(song[songToPlay]);
         }         
         break;
        }
         //creating song
         case '3':
         {
            Serial.println("which son would you like to overwrite (1-4): ");
            ReadString();
            int songToReplace = my_buffer[0];
            Serial.println("Enter the song: ");
            ReadString();
            String title = my_buffer;
            StoreSong(song[songToReplace], title.c_str());
            Serial.println("Song was created: ");
            Serial.println();
            ListSongs(songTitle);
            ReadString();
         break;
         }
     }  
}

//List Songs Function
void ListSongs(char songTitle[NUMBER_OF_SONGS][STR_LENGTH])
{
     int i = 0;
     Serial.println();
     Serial.println("====Song List====");
     for(; i < NUMBER_OF_SONGS; i++)
     {
        Serial.print(i+1);
        Serial.print(":");
        Serial.print("Title: ");
        Serial.println(songTitle[i]);
     }
     Serial.println();
     Serial.println();
}

//Play Song Function
void PlaySong(uint8_t song[])
{

    //uint8_t duration = 0;
    uint8_t store[50];
    uint8_t character;
    uint8_t duration;
 
    int i=0;
    for(; i < MAX_SONG_LENGTH; i++)
    {
       character = UnpackNoteLetterASCII(store[i]);
       duration = UnpackNoteDuration(store[i]);
       //while(character != 'R' && duration != 0)
       if((character != 'R' || character != 'r') && duration != 0)
         PlayNote(character, duration);
       if(character == 'R' || character == 'r')
         continue;
       else
        return;
    }
}
 
//Pack function
uint8_t PackNote(char letterASCII, uint8_t duration)
{
    uint8_t packNote = 0 ;
    if(letterASCII == 'a' || letterASCII == 'A')
        packNote = (NOTE_D << 5) | (duration);
    else if(letterASCII == 'b' || letterASCII == 'B')
        packNote = (NOTE_D << 5) | (duration);
    else if(letterASCII == 'c' || letterASCII == 'C')
        packNote = (NOTE_D << 5) | (duration);
    else if(letterASCII == 'd' || letterASCII == 'D')
        packNote = (NOTE_D << 5) | (duration);
    else if(letterASCII == 'e' || letterASCII == 'E')
        packNote = (NOTE_D << 5) | (duration);
    else if(letterASCII == 'f' || letterASCII == 'F')
        packNote = (NOTE_D << 5) | (duration);
    else if(letterASCII == 'g' || letterASCII == 'G')
        packNote = (NOTE_D << 5) | (duration);
    else if(letterASCII == 'r' || letterASCII == 'R')
        packNote = (NOTE_D << 5) | (duration);
    else
        packNote = 0xf | duration;
    return packNote;       
}

//Unpack function
uint8_t UnpackNoteLetterASCII(uint8_t packedNote)
{
    return packedNote>>5;
}

//
uint8_t UnpackNoteDuration(uint8_t packedNote)
{
    return(packedNote & 31);
}
//letter
 bool checkChar(char letter)
 {
    if(letter == 'a' || letter == 'A' ||letter == 'b' || letter == 'B' ||letter == 'c' || letter == 'C' ||letter == 'd' || letter == 'D' ||letter == 'e' || letter == 'E' ||letter == 'f' || letter == 'F' ||letter == 'g' || letter == 'G' ||letter == 'r' || letter == 'R' )
      return  true;
 }
//number
  bool checkNum(char x)
 {
    if(x >= '0' && x <= '9')
      return  true;
 }
//Store song function
void StoreSong(uint8_t song[], const char songString[])
{
  uint8_t packNote;
  char character;
  uint8_t duration;
  int cFlag=0; 
  int dFlag = 0;


  int i = 0;
  for(; i < strlen(songString); i++)
  {
    if(cFlag && dFlag)
    {
      int n = 0;
      packNote = PackNote(character, duration); 
      cFlag = 0;
      dFlag = 0;
      song[n] = packNote;
      n++;
    }
    //check for the char if one set a flag
    if(checkChar(songString[i]))
    {
      character = songString[i];
      cFlag = 1;
    }    
    //check for numbers
    if(checkNum(songString[i]))
    {
      if(checkNum(songString[i+1]))
      {
        char x[] = {songString[i]};
        char y[] = {songString[i+1]};
        strcat(x, y);
        duration = atoi(x);      
        //dFlag = 1;
      }
      else
      {
        duration = songString[i];
        //dFlag = 1;
      }
      dFlag = 1;
    }
  }
}

//Play Note Functions
void PlayNote(uint8_t letterASCII, uint8_t quarters)
{
   int period ;
   int halfPeriodUS;
   int numIterations;
   
   //A
   if(letterASCII == 0)
   {
     period = (1000000/FREQ_A4_HZ);
     halfPeriodUS = period/2;
     numIterations = (FREQ_A4_HZ/4)*quarters;
   }
   //B
   else if(letterASCII == 1)
   {
     period = (1000000/FREQ_B4_HZ);
     halfPeriodUS = period/2;
     numIterations = (FREQ_B4_HZ/4)*quarters;
   }
   //C
   else if(letterASCII == 2)
   {
     period = (1000000/FREQ_C4_HZ);
     halfPeriodUS = period/2;
     numIterations = (FREQ_C4_HZ/4)*quarters;
   }
   //D
   else if(letterASCII == 3)
   {
     period = (1000000/FREQ_D4_HZ);
     halfPeriodUS = period/2;
     numIterations = (FREQ_D4_HZ/4)*quarters;
   }
   //E
   else if(letterASCII == 4)
   {
     period = (1000000/FREQ_E4_HZ);
     halfPeriodUS = period/2;
     numIterations = (FREQ_E4_HZ/4)*quarters;
   }
   //F
   else if(letterASCII == 5)
   {
     period = (1000000/FREQ_F4_HZ);
     halfPeriodUS = period/2;
     numIterations = (FREQ_F4_HZ/4)*quarters;
   }
   //G
   else if(letterASCII == 6)
   {
     period = (1000000/FREQ_G4_HZ);
     halfPeriodUS = period/2;
     numIterations = (FREQ_G4_HZ/4)*quarters;
   }
   //R
   else if(letterASCII == 7)
   {
     //period = (1000000/1000);
     halfPeriodUS = 500;
     numIterations = (1000/4)*quarters;
   }
   
   int i;
   for(i = 0; i < numIterations; i++)
   {
     if(letterASCII!= 7) 
      analogWrite(5, 8);
     delayMicroseconds(halfPeriodUS);  
     analogWrite(5, 0);
     delayMicroseconds(halfPeriodUS); 
   }
}

//Matching Function
int MatchScore(const char countQueryString[], const char templates[])
{
    /*int i; 
    for(i = 0; i < sizeof(countQueryString); i++)
    {
        if(strcmp(countQueryString, templates))
            i++;
    }
    return i;*/
    
    int i = 0;
    char * countQuery = strdup(countQueryString);
    char * tmplt = strdup(templates);
    char * tokenCountQuery = strtok(countQuery, " ");

    while( tokenCountQuery != NULL)
    {
      if(strcmp(countQuery, tmplt) == 0)
        i++;
    }

    return i;
}

//////////////////////////////////////////////////////////////////////
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while(!Serial);
}

void loop() {
  DisplayMenu(menuMain);

}
