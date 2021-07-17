#include "Common.h"
#include "Telltale.h"

void Task_1(void);
void Task_2(void);
void Task_3(void);
void Event(void (*event_TBL[])(void));

U1 u1_1Sec;
U1 u1_Port;
U1 u1_PrtSts;
U1 u1_BUF_1MS;
F1 St_Temp;

void (*const MS10_TBL[])(void) = {&Task_1,&Task_2,&Task_3,NULL};

int main(void)
{ 
	u1_PrtSts = (U1)0xFF;
	u1_BUF_1MS = (U1)OFF;
	St_Temp.Bit.b00 = ON;
	TT_Dr_Init();
	
	TMOD = 0x01;
	IE   = 0x82;
	TL0  = 0xF0;
  TH0  = 0xD8;
	TR0  = 1; 
	
	while(1)
	{
	  if(St_Temp.Bit.b00 == ON)
	  {
		  Event(MS10_TBL);
		  St_Temp.Bit.b00 = OFF;
		  EA = 1;
	  }	
	} 	
}

void Timer0(void) interrupt 1
{
  St_Temp.Bit.b00 = ON; 
  TF0 	= 0; 
  TL0  	= 0xF0;
  TH0  	= 0xD8;
  EA 		= 0;
}

void Task_1(void)
{
	u1_Port = P1;
	if(u1_Port != u1_PrtSts){
		TT_Dr_Write(P1);
	}
	u1_PrtSts = u1_Port;
}

void Task_2(void)
{
	u1_1Sec++;
	if(u1_1Sec >= 100)
	{
	P1_0 = ~P1_0;
	u1_1Sec = 0;
	}			
}

void Task_3(void)
{

}

void Event(void (*const *MS10_TBL)(void))
{
	for(; *MS10_TBL != 0 ;){
		(*MS10_TBL)();
		MS10_TBL++;
	}
}



