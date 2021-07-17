#include <89c51rd2.h>
#include "LCD.prm"
#include "LCD.h"

static void lcd_init(void);
static void lcd_Wrtcmd(U1);
static void lcd_Wrtdata(U1);


int main(void)
{
    lcd_Bon();
    lcd_Wkup();
    lcd_routine();
    return(0);
}

void lcd_Bon(void){

    lcd_init();
}

void lcd_Wkup(void){
    
    lcd_init();
    lcd_Wrtcmd(INI);
    lcd_Wrtcmd(INC);
    lcd_Wrtcmd(LIN_1);
    lcd_Wrtcmd(CUR);

}

void nop(void){
    U1 u1_dly;
    u1_dly  =   (U1)250;
    while(u1_dly){
        u1_dly--;
    }
}

static void lcd_init(void){

    RS  =   LO;
    E   =   LO;
    u1_DAT = U1_MIN;
}

static void lcd_Wrtcmd(U1 u1_cmd){
    u1_DAT = u1_cmd;
    RS  =   LO;
    E   =   HI;
    nop();
    E   =   LO;
}

static void lcd_Wrtdata(U1 u1_cmd){
    u1_DAT = u1_cmd;
    RS  =   HI;   
    E   =   HI;
    nop();
    E   =   LO;
}


void lcd_dispstr(U1 *p){

    while (*p)
    {
        lcd_Wrtdata(*p);
        *p++;
    }
    
}

D1 u1_Hex2Bcd(U1 u1_Hex){

    U1 u1_D1;
    u1_D1 = (D1)0;

    if(u1_Hex > Hex_d1MAX){
        
        u1_D1 = Hex_d1MAX;
    }
    
    u1_D1 = (u1_Hex/(U1)10)<<4;

    u1_D1 = u1_D1 | (u1_Hex%(U1)10);
    
    return(u1_D1);
}

void lcd_routine(void){
//  lcd_Wrtcmd(LIN_1);
//  lcd_dispstr("   albtronics   ");
//  lcd_Wrtcmd(LIN_2);
//  lcd_dispstr(" albtronics.org ");
    u1_Hex2Bcd(0x62);
    while (1);   
}