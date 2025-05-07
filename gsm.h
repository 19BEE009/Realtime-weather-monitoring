void gsm_ini(void);
void send_sms(void);
void gsm_ini(void)
{
	uart0_str("AT\r\n");
	delay_ms(3000);
	uart0_str("AT+CMGF=1\r\n");
    delay_ms(3000);
}
void send_sms()
{
//	int i=0;
	char n[]="+917904773795",s[]="High Temperature!!! Fan Turned ON!!!";
	uart0_str("AT+CMGS=\"");
	uart0_str(n);
	uart0_str("\"\r\n""");
	delay_ms(3000);
	uart0_str(s);
	delay_ms(3000);
	uart0_tx(0X1A);//FOR CONTROL+Z 
	delay_ms(6000);
	return;

}
