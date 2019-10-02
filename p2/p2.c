/*
This code was automatically generated using the Riverside-Irvine State machine Builder tool
Version 2.8 --- 10/26/2018 15:4:39 PST
*/

#include "rims.h"

//#include "secret_code.h"
/*This code will be shared between state machines.*/
int btnPressed = 0;
#define SECRET_CODE   0x00
int blinking = 0;
unsigned char GetBit(unsigned char x, unsigned char k) {
   return ((x & (0x01 << k)) != 0);
}

unsigned char BitsSum(unsigned char x)
{
return GetBit(x,0) + GetBit(x,1) +GetBit(x,2)+ GetBit(x,3) +  GetBit(x,4) + GetBit(x,5) +  GetBit(x,6) + GetBit(x,7) ;
}

unsigned char TimerFlag = 0;
void TimerISR() {
   TimerFlag = 1;
}


enum SM3_States { SM3_UP, SM3_Delay, SM3_Pressed } SM3_State;

TickFct_State_machine_3() {
   /*VARIABLES MUST BE DECLARED STATIC*/
/*e.g., static int x = 0;*/
/*Define user variables for this state machine here. No functions; make them global.*/
static int delay;
   switch(SM3_State) { // Transitions
      case -1:
         SM3_State = SM3_UP;
         break;
      case SM3_UP:
         if (C0==1) {
            SM3_State = SM3_Delay;
         }
         break;
      case SM3_Delay:
         if (!C0 ) {
            SM3_State = SM3_UP;
         }
         else if (C0 && delay >= 2) {
            SM3_State = SM3_Pressed;
         }
         break;
      case SM3_Pressed:
         if (!C0) {
            SM3_State = SM3_UP;
         }
         break;
      default:
         SM3_State = SM3_UP;
      } // Transitions

   switch(SM3_State) { // State actions
      case SM3_UP:
         delay = 0;
         btnPressed = 0;
         blinking = 0;
         break;
      case SM3_Delay:
         delay++;
         break;
      case SM3_Pressed:
         btnPressed = 1;
         break;
      default: // ADD default behaviour below
         break;
   } // State actions
}

enum SM4_States { SM4_INPUT_WAIT, SM4_Win, SM4_check, SM4_again, SM4_lost, SM4_s6, SM4_s7, SM4_s8, SM4_s9, SM4_initial } SM4_State;

TickFct_State_machine_4() {
   /*VARIABLES MUST BE DECLARED STATIC*/
/*e.g., static int x = 0;*/
/*Define user variables for this state machine here. No functions; make them global.*/
static int d = 10;
static int cnt = 0;
static int wait = 0;
static int incorrect = 0;
   switch(SM4_State) { // Transitions
      case -1:
         SM4_State = SM4_initial;
         break;
      case SM4_INPUT_WAIT:
         if (btnPressed) {
            SM4_State = SM4_check;
         }
         break;
      case SM4_Win:
         if (1) {
            SM4_State = SM4_s6;
         }
         break;
      case SM4_check:
         if (incorrect == 0) {
            SM4_State = SM4_Win;
         }
         else if (incorrect != 0 && d != 0) {
            SM4_State = SM4_again;
         }
         else if (incorrect != 0 && d == 0) {
            SM4_State = SM4_lost;
         }
         break;
      case SM4_again:
         if (incorrect != 0 && d != 0&&!btnPressed) {
            SM4_State = SM4_INPUT_WAIT;
         }
         break;
      case SM4_lost:
         if (1) {
            SM4_State = SM4_s7;
         }
         break;
      case SM4_s6:
         if (1) {
            SM4_State = SM4_s8;
         }
         break;
      case SM4_s7:
         if (1) {
            SM4_State = SM4_s9;
         }
         break;
      case SM4_s8:
         if (cnt<=10) {
            SM4_State = SM4_s6;
         }
         else if (cnt>=10 && btnPressed==0) {
            SM4_State = SM4_initial;
         }
         break;
      case SM4_s9:
         if (cnt<=10) {
            SM4_State = SM4_s7;
         }
         else if (cnt>=10 && btnPressed==0) {
            SM4_State = SM4_initial;
         }
         break;
      case SM4_initial:
         if (1) {
            SM4_State = SM4_INPUT_WAIT;
         }
         break;
      default:
         SM4_State = SM4_initial;
      } // Transitions

   switch(SM4_State) { // State actions
      case SM4_INPUT_WAIT:
         blinking = 1;
         
         break;
      case SM4_Win:
         printf("\n you won in %d tries",  d);
         break;
      case SM4_check:
         incorrect = BitsSum(A ^ SECRET_CODE);
         d--;
         blinking = 0;
         break;
      case SM4_again:
         B = BitsSum(A^SECRET_CODE);
         
         break;
      case SM4_lost:
         printf(" \n you lost");
         break;
      case SM4_s6:
         B=0x0f;
         cnt++;
         blinking = 0;
         break;
      case SM4_s7:
         B=0xf0;
         cnt++;
         break;
      case SM4_s8:
         B=0x00;
         blinking = 0;
         break;
      case SM4_s9:
         B=0x00;
         break;
      case SM4_initial:
         d=10;
         cnt = 0;
         break;
      default: // ADD default behaviour below
         break;
   } // State actions
}

enum SM1_States { SM1_Start, SM1_blink, SM1_B0, SM1_B1, SM1_B2, SM1_B3, SM1_B7, SM1_B6, SM1_B5, SM1_B4, SM1_s11 } SM1_State;

TickFct_State_machine_1() {
   /*VARIABLES MUST BE DECLARED STATIC*/
/*e.g., static int x = 0;*/
/*Define user variables for this state machine here. No functions; make them global.*/
static int cnt = 0;
   switch(SM1_State) { // Transitions
      case -1:
         SM1_State = SM1_Start;
         break;
      case SM1_Start:
         if (cnt<3) {
            SM1_State = SM1_blink;
         }
         else if (cnt>=3&&blinking) {
            SM1_State = SM1_B0;
         }
         else if (cnt>=3 && !blinking) {
            SM1_State = SM1_s11;
         }
         break;
      case SM1_blink:
         if (cnt<3) {
            SM1_State = SM1_Start;
         }
         break;
      case SM1_B0:
         if (blinking) {
            SM1_State = SM1_B1;
         }
         else if (1) {
            SM1_State = SM1_B0;
         }
         else if (!blinking) {
            SM1_State = SM1_s11;
         }
         break;
      case SM1_B1:
         if (blinking) {
            SM1_State = SM1_B2;
         }
         else if (!blinking) {
            SM1_State = SM1_s11;
         }
         break;
      case SM1_B2:
         if (blinking) {
            SM1_State = SM1_B3;
         }
         else if (!blinking) {
            SM1_State = SM1_s11;
         }
         break;
      case SM1_B3:
         if (blinking) {
            SM1_State = SM1_B4;
         }
         else if (!blinking) {
            SM1_State = SM1_s11;
         }
         break;
      case SM1_B7:
         if (!blinking) {
            SM1_State = SM1_s11;
         }
         else if (blinking) {
            SM1_State = SM1_B0;
         }
         break;
      case SM1_B6:
         if (blinking) {
            SM1_State = SM1_B7;
         }
         else if (!blinking) {
            SM1_State = SM1_s11;
         }
         break;
      case SM1_B5:
         if (blinking) {
            SM1_State = SM1_B6;
         }
         else if (!blinking) {
            SM1_State = SM1_s11;
         }
         break;
      case SM1_B4:
         if (blinking) {
            SM1_State = SM1_B5;
         }
         else if (!blinking) {
            SM1_State = SM1_s11;
         }
         break;
      case SM1_s11:
         if (blinking) {
            SM1_State = SM1_B0;
         }
         break;
      default:
         SM1_State = SM1_Start;
      } // Transitions

   switch(SM1_State) { // State actions
      case SM1_Start:
         B = 0xff;
         cnt++;
         
         break;
      case SM1_blink:
         B = 0x00;
         
         break;
      case SM1_B0:
         B = 0x01;
         break;
      case SM1_B1:
         B = 0x02;
         break;
      case SM1_B2:
         B = 0x04;
         break;
      case SM1_B3:
         B = 0x08;
         break;
      case SM1_B7:
         B = 0x80;
         break;
      case SM1_B6:
         B = 0x40;
         break;
      case SM1_B5:
         B = 0x20;
         break;
      case SM1_B4:
         B = 0x10;
         break;
      case SM1_s11:
         break;
      default: // ADD default behaviour below
         break;
   } // State actions
}
int main() {
   B = 0; //Init outputs
   TimerSet(62);
   TimerOn();
   SM3_State = -1;
   SM4_State = -1;
   SM1_State = -1;
   while(1) {
      TickFct_State_machine_3();
      TickFct_State_machine_4();
      TickFct_State_machine_1();
      while (!TimerFlag);
      TimerFlag = 0;
   }
}