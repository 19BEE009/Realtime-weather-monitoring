#include "header.h"
#define fan 1<<17
//function declarations
void title_display(void);
void rtc_disp(void);
float sensor_data(unsigned char);
void criterr(void);
float tempVal,crittemp=33.0;

int main()
{
	int Msgflag;
    
	IODIR0|=fan;
	LCD_INI();
	uart0_config();
	Init_SPI0();
	init_i2c();
	gsm_ini();

	title_display();


	delay_s(1);


	while(1)
	{	
	
	    
	    tempVal=sensor_data(0);	    
	if((tempVal>=crittemp)&&(Msgflag==0))
		{
			Msgflag=1;
			LCD_CMD(0x01);
			LCD_CMD(0x80);
		
			lcd_str("High Temp!Fan ON");
			//send_sms("+918248065563");
			LCD_CMD(0xC0);
			lcd_str("Alert Msg Sent!!");
				send_sms();
			IOCLR0=fan;
		}
		else if(tempVal<crittemp)
		{
			Msgflag=0;
			IOSET0=fan;
			LCD_CMD(0x01);
			LCD_CMD(0x80);
			rtc_disp();
			LCD_CMD(0xC0);
			lcd_str("T:");
			FLOATDISP(tempVal);
			LCD_DATA(0);
			LCD_DATA('C');
			delay_s(1);	
		} 	
}
}


void title_display(void)
{
	char title[]="RWMS ID:V24CE3N1";
	char name[]="NAVEENKUMARR";
	int i,j;
	for(i=0X80,j=0XC0;((i<0X90)&&(j<0XD0));i++,j++)
	{
		LCD_CMD(0x01);
		LCD_CMD(i);
		lcd_str(title);
		LCD_CMD(j);
		lcd_str(name);
		delay_ms(500);
	}
	
}

void rtc_disp()
{
	unsigned char min,sec,hr,thr,ohr,tm,om,ts,os;
	hr=i2c_read(0X68,0X02);
		 thr=hr/16;
		 ohr=hr%16;
		 LCD_DATA(thr+48);
	 	 LCD_DATA(ohr+48);
		 LCD_DATA(':');
	min=i2c_read(0X68,0X01);
		 tm=min/16;
		 om=min%16;
		 LCD_DATA(tm+48);
		 LCD_DATA(om+48);
		 LCD_DATA(':');
	sec=i2c_read(0X68,0X00);
		 ts=sec/16;
		 os=sec%16;
		 LCD_DATA(ts+48);
		 LCD_DATA(os+48);
}

float sensor_data(unsigned char channelNo)
{
 unsigned char hByte,lByte;
  unsigned int adcVal=0;
   
  
  CLRBIT(IOPIN0,CS);

	
  SPI0(0x06);	//spi communication initiation
  hByte = SPI0(channelNo<<6);
  lByte = SPI0(0x00);
	
	
  SETBIT(IOSET0,CS);

  adcVal=((hByte&0x0f)<<8)|lByte;
 //return adcVal;
  return ((adcVal*3.3)/4096)*100;
}
