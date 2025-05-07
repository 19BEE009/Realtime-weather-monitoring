void uart0_config(void);
void uart0_tx(unsigned char);
unsigned char uart0_rx(void);
void uart0_str(unsigned char *);
void uart0_config()
{
	PINSEL0|=0X05;
	U0LCR=0X83;
	U0DLL=97;
	U0DLM=0;
	U0LCR=0X03;

}
void uart0_tx(unsigned char c)
{
	U0THR=c;
	while(((U0LSR>>5)&1)==0);
}
unsigned char uart0_rx()
{
	while(((U0LSR)&1)==0);
	return U0RBR;
}

void uart0_str(unsigned char *s)
{
	while(*s)
	{
		uart0_tx(*s++);
	}
}
