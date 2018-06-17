
#include<reg52.h>    
#include <intrins.h> 
#define uchar unsigned char
#define uint unsigned int


sbit D=P1^5; //Pin14 ????
sbit Out=P1^6 ;//Pin12 RCLK ���������
sbit SRCLK=P1^7;	// Pin11 SRCLK ��������
sbit  OutA=P1^3;  //154 ��16�п���  0ʹ�����
sbit  OutB=P1^4;  // 154 ��16�п��� 0
sbit 	KEY1=P1^2;  //����
sbit  KEY2=P1^1;   // ����

unsigned char code LED4[]={
	/* ��*/
  0xFF,0xFF,0xC0,0x0F,0xFF,0xEF,0xFF,0xDF,0xFF,0xBF,0xFE,0x7F,0xFE,0xFF,0x00,0x01,
	0xFE,0xFF,0xFE,0xFF,0xFE,0xFF,0xFE,0xFF,0xFE,0xFF,0xFE,0xFF,0xFA,0xFF,0xFC,0xFF
};

unsigned char code LED3[]={
  0xFD,0xFF,0xFD,0xFF,0xFD,0xFF,0x80,0x0F,0xBD,0xEF,0xBD,0xEF,0x80,0x0F,0xBD,0xEF,
  0xBD,0xEF,0x80,0x0F,0xFD,0xFF,0xFD,0xFF,0xFD,0xFB,0xFD,0xFB,0xFC,0x03,0xFF,0xFF
};

unsigned char code LED2[]={
0xFF,0xFF,0xFF,0xFF,0x80,0x03,0xFE,0xFF,0xFE,0xFF,0xFE,0xFF,0xFE,0xFF,0xFE,0xFF,
0xFE,0xFF,0xFE,0xFF,0xFE,0xFF,0xFE,0xFF,0xFE,0xFF,0x00,0x01,0xFF,0xFF,0xFF,0xFF};


unsigned char code LED1[]={
0xBE,0xBF,0xCE,0xDF,0xEE,0xFB,0xFC,0x01,0x79,0xDF,0x95,0xD7,0xDC,0x03,0xF5,0xDF,
0xED,0xD7,0xDC,0x03,0x1D,0xDF,0xDD,0xDF,0xDD,0xDB,0xDC,0x01,0xDD,0xFF,0xDD,0xFF};


void Delay(uint n)   // ��ʱ����
{
   uchar i;
   while(n--)
   {
     for(i=0;i<120;i++);
}
}

// 595 ���ú���
void HC595SendData (unsigned int SendVal)
{
	int i;
	for(i=0;i<8;i++)
	{
		if(((SendVal << i)&0x80) !=0)
				D=1;
	   else 
			 D=0;
		 SRCLK=0;
	  //	 Out=0;
		// Out=1;
		 Delay(0);
		 SRCLK=1;
	}
}

// 595 ������λ����
void Move (unsigned int n)
{
	while(n--){
		 D=1;
		 SRCLK=0;
		 Delay(1);
		 SRCLK=1;
	}}

/*������ʾ���� ���� ��������һ�п�ʼ*/
		void ShowLed(unsigned int Line)
		{
    	int i,A;
			A=Line;
			
		if(Line<0x1f)
			{		
			OutA=0;
			for(i=0;Line<=0x0f;i++,Line++)
			{
				P0=Line;
				HC595SendData(LED2[2*i+1]);  // ��32λ����
				HC595SendData(LED2[2*i]);
				HC595SendData(LED1[2*i+1]);
				HC595SendData(LED1[2*i]);
				Out=0;   //��������
				Out=1;
				Delay(7);
			}
			Line -=0x10;
			OutA=1;
			
			
			OutB=0;		
			for(i=0;Line<=0xff;i++,Line+=0x10)
			{
				
				P0=Line;
				HC595SendData(LED4[2*i+1]);  // ��32λ����
				HC595SendData(LED4[2*i]);
				HC595SendData(LED3[2*i+1]);
				HC595SendData(LED3[2*i]);
				Out=0;   //��������
				Out=1;
				Delay(7);
			}
		OutB=1;
		
		}
		else{			OutB=0;		
			for(i=0;Line<=0xff;i++,Line+=0x10)
			{
				
				P0=Line;
				HC595SendData(LED4[2*i+1]);  // ��32λ����
				HC595SendData(LED4[2*i]);
				HC595SendData(LED3[2*i+1]);
				HC595SendData(LED3[2*i]);
				Out=0;   //��������
				Out=1;
				Delay(7);
			}
		OutB=1;}
		}

		
/*��������   δʵ��  */
		void Clear_LED(void)
		{
			OutB=1;
			OutA=1;
			Delay(10000);
		}
		
/*����һ ���ϵ������� */
		void KEY1Out(void){
			int Line;
								 for(Line=0x00;Line<0x1f;Line++)
								{	
									ShowLed(Line);
									Delay(50);
								} 
								Line=Line-0x01;
								for(Line=0x10;Line<=0xff;Line+=0x10)
								{	
								ShowLed(Line);
								Delay(500);
								} 
		}

/* �ҹ���������������  */
void HC595Send(unsigned int SendVal)
{
	int i;
	for(i=0;i<8;i++)
	{
		if(((SendVal << i)&0x80) !=0)
				D=1;
	   else 
			 D=0;
		 SRCLK=0;
	  	 Out=0;
		 Out=1;
		 Delay(700);
		 SRCLK=1;
	}}

		
		
		/*���ƶ� */
		void MoveRight(void){
		int n,i,j;
	  int Line=0x00;
			for(j=0;j<=32;j++){
			OutA=0;
			Line=0x00;
			for(i=0;Line<=0x0f;i++,Line++)
			{
				P0=Line;
				HC595SendData(LED2[2*i+1]);  // ��32λ����
				HC595SendData(LED2[2*i]);
				HC595SendData(LED1[2*i+1]);
				HC595SendData(LED1[2*i]);
				Move(j);
				Out=0;   //��������
				Out=1;
				Delay(7);
			}
			Line -=0x10;
			OutA=1;
			
			
			OutB=0;		
			for(i=0;Line<=0xff;i++,Line+=0x10)
			{
				
				P0=Line;
				HC595SendData(LED4[2*i+1]);  // ��32λ����
				HC595SendData(LED4[2*i]);
				HC595SendData(LED3[2*i+1]);
				HC595SendData(LED3[2*i]);
				Move(j);
				Out=0;   //��������
				Out=1;
				Delay(7);
			}
		OutB=1;	
		}
		}
	

		
void main()
{
	int Line,n,i;
	int Data=0xff;

	KEY1=0;
		while(1){

			KEY1=1; //��������˿ڵ�ƽ�ø�
						if(!KEY1)  //�����⵽�͵�ƽ��˵����������
			{
				Delay(10); //��ʱȥ����һ��10-20ms
				if(!KEY1)     //�ٴ�ȷ�ϰ����Ƿ��£�û�а������˳�
				{
				 while(!KEY1);//���ȷ�ϰ��°����ȴ������ͷţ�û���ͷ���һֱ�ȴ�
						{
							KEY1Out();
						}}}
				else if(!KEY2){
						Delay(10); //��ʱȥ����һ��10-20ms
						if(!KEY2)     //�ٴ�ȷ�ϰ����Ƿ��£�û�а������˳�
						{
						 while(!KEY2);//���ȷ�ϰ��°����ȴ������ͷţ�û���ͷ���һֱ�ȴ�
								{
								MoveRight();
								}}}
				else{
							Line=0x00;
							ShowLed(Line);//�ͷ���ִ����Ҫ�ĳ���
						}
		}
	
}


