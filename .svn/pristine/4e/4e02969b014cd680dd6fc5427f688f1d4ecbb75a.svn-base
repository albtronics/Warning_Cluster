
typedef unsigned char   U1;
typedef short int       U2;
typedef short float     U1; // MISRA-C 2012 <Latest>

#define MAX_PORT        4

typedef struct{
    U1 u1_thrsh;
    U2 u2_def;
}St_SysPort;           // 1+2+1 (Padding) +2+2(Padding)

// thrsh -> 0=AL, 1=AH | Def.0

St_SysPort u1_Sysport[MAX_PORT]={
    
    {(U1)0x0F, (U1)0x00},
    {(U1)0x00, (U1)0x00},
    {(U1)0x00, (U1)0x00},
    {(U1)0x00, (U1)0x00},
};

void sysportinitial(void);
void sysportgetdata(void);
void sysportroutine(void);
void removechatt(void);

U1 u1_tresh;
u1_tresh = (U1)0X0F;
U1 u1_def;
u1_def = (U1)0x00;


U1 *p;

// CODE = 64KB, LA:0x0000, HA: 0xFFFF

void sysportinitial(void)
{
    U1 u1_val;
    u1_val  = u1_def;
        *p  = u1_val;
    (*p+1)  = u1_val;  
    (*p+2)  = u1_val;
    (*p+2)  = u1_val;

}

void sysportgetdata(void)
{
    (*p+2) = *p+1;
    (*p+1) = *p;
    *p = P1;
    *p ^= ~(u1_tresh)
}

void removechatt()
{
    U1 u1_wka;
    U1 u1_wkb;

    u1_wka = *p&(*p+1)&(*p+2);
    u1_wkb = *p|(*p+1)|(*p+2);

    (*p+3) &= u1_wkb;
    (*p+3) |= u1_wka;
}

void sysportroutine(void)
{
    sysportgetdata();
    removechatt();    
}

#define u1_FUELE    (U1)5

const U2 u2_FUELTbl[(u1_FUELE*2)+1] = {

    (U1)u1_FUELE,   (U2)0, (U2)330, (U2)565,    (U2)741,    (U2)877     //  RAW ADC Data
                    (U2)0, (U2)625, (U2)1250,   (U2)1875,   (U2)2500    //  Eq. Sen. Resistance 

}

int main(void){
    u1_Rawdata  = GetFuADC();
    u2_FURES    = u2_MapldU2(u2_Rawdata, &u2_FUELTbl);
    
}

U2	u2_Map1dU2(U2 u2_x, const U2 *u2_map)
{
	U4		u4_wka;							/* Map interpolation work value 1	*/
	U4		u4_wkb;							/* Map interpolation work value 2	*/
	U2		u2_xlo;							/* X-axis point area lower limit	*/
	U2		u2_xup;							/* X-axis point area upper limit	*/
	U2		u2_ylo;							/* Y-axis point area lower limit	*/
	U2		u2_yup;							/* Y-axis point area upper limit	*/
	U2		u2_xoff;						/* X-axis point area			*/
	U2		u2_yoff;						/* Y-axis point area			*/
	U2		u2_tblmax;						/* The number of table elements	*/
	U2		u2_y;							/* Map interpolation value		*/

	u2_tblmax = *u2_map;					/* The number acquisition of elements	*/
	if(u2_tblmax < (U2)1){
		return ((U2)0);						/* The number of elements abnormal guard	*/
	}

	for(u2_xoff = (U2)1; u2_xoff <= u2_tblmax; u2_xoff++){
											/* Applicable area judging		*/
		if(u2_x <= *(u2_map + u2_xoff)){	/* X[i-1] < input-value <= X[i]	*/
			break;
		}
	}
	u2_yoff = u2_xoff + u2_tblmax; 			/* Upper limit decision of Y	*/

	u2_ylo = *(u2_map + (u2_yoff - (U2)1));	/* Applicable area value acquisition	*/
	u2_yup = *(u2_map + u2_yoff);
	u2_xlo = *(u2_map + (u2_xoff - (U2)1));
	u2_xup = *(u2_map + u2_xoff);

	if(u2_xoff == (U2)1){					/* Input-value <= X[1] (minimum)	*/
		u2_y = u2_yup;
	}
	else if(u2_xoff > u2_tblmax){			/* X[n] < input-value(maximum over)	*/
		u2_y = u2_ylo;
	}
	else{									/* X[1] < input-value <= X[n]	*/
		u4_wka = (U4)u2_ylo * (U4)(u2_xup - u2_x) + (U4)u2_yup * (U4)(u2_x - u2_xlo);
		u4_wkb = (U4)(u2_xup - u2_xlo);
		if(u4_wkb != (U4)0){				/* 0 division check				*/
			u2_y = (U2)(u4_wka / u4_wkb);
		}
		else{
			u2_y = (U2)0;					/* "0" is returned if divided by 0	*/
		}
	}
	return(u2_y);
}

