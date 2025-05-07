#define DATAPIN 0xf<<20
#define RS 1<<17
#define rw 1<<18
#define E 1<<19
void LCD_INI(void);
void LCD_CMD(unsigned char);
void LCD_DATA(unsigned char);
void lcd_str(char *);
void lcd_strscroll(char *);
void INTDISP(int);
void FLOATDISP(float);
void cgram_write(unsigned char);
char a[]={0x1c,0x14,0x1c,0x00,0x00,0x00,0x00,0x00}; 



void LCD_INI(void)
{
	IODIR1|=DATAPIN|RS|E|rw;
	IOCLR1=rw;
	LCD_CMD(0X01);
	LCD_CMD(0X02);
	LCD_CMD(0X0c);
	LCD_CMD(0X28);
	LCD_CMD(0x80);
	cgram_write(8);
}
void LCD_CMD(unsigned char c)
{
	IOCLR1=DATAPIN;
	IOSET1=((c&0XF0)<<16);
	IOCLR1=RS;
	IOSET1=E;
	delay_ms(2);
	IOCLR1=E;
	
  	IOCLR1=DATAPIN;
	IOSET1=((c&0X0F)<<20);
	IOCLR1=RS;
	IOSET1=E;
	delay_ms(2);
	IOCLR1=E;
}
void LCD_DATA(unsigned char c)
{
	IOCLR1=DATAPIN;
	IOSET1=((c&0XF0)<<16);
	IOSET1=RS;
	IOSET1=E;
	delay_ms(2);
	IOCLR1=E;
	
  	IOCLR1=DATAPIN;
	IOSET1=((c&0X0F)<<20);
	IOSET1=RS;
	IOSET1=E;
	delay_ms(2);
	IOCLR1=E;
}
void lcd_str(char *s)
{
	int i=0;
	for(i=0;s[i];i++)
	LCD_DATA(s[i]);
}
void lcd_strscroll(char *s)
{
	int l=strlen(s);
	while(1)
	{
		int j,k,i,h;
		for(j=0X80;j<0X90;j++)
		{
			k=l+j;
			LCD_CMD(0X01);
			LCD_CMD(j);
			if(k>0X90)
			{
				i=k-0X90;
				for(h=0;h<l-i;h++)
					LCD_DATA(s[h]);
			}
			else
				lcd_str(s);
			delay_s(1);
		}
	}
}

void INTDISP(int n)
{
	int i=0;
	unsigned char a[3];
	if(n==0)
	{
	LCD_DATA('0');	
	}
	else
	{
  	     if(n<0)
		{
			LCD_DATA('-');
			n=-n;
		}
		 while(n>0)
		{
			a[i++]=n%10;
			n/=10;
		}
		for(i=i-1;i>=0;i--)
		LCD_DATA(a[i]+48);
}}	
void FLOATDISP(float f)
{
	int x=f;
	INTDISP(x);
	LCD_DATA('.');
	x=(f-x)*10;
	INTDISP(x);
}

void cgram_write(unsigned char c)
{
	int i=0;
	LCD_CMD(0X40);
	for(i=0;i<c;i++)
	LCD_DATA(a[i]);
}
