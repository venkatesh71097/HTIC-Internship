/* ========================================
 * UROSENS CODE
 * ========================================
*/
#include <project.h>
#include<stdio.h>
typedef  uint8_t  byte;
#define  bitRead(value, bit)  (((value) >> (bit)) & 0x01)
#define  bitSet(value, bit)   ((value) |= (1UL << (bit)))
#define  bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define  bitWrite(value, bit, bitvalue)  (bitvalue ? bitSet(value, bit) : bitClear(value, bit))


long final_data=0;
long sum=0;
int count=0;
long final=0;
long final1=0;
char result[8];
void getvalue() 
    {
       int i,j;
       byte data[3];
       while(data_Read());
       for(i=0;i<3;i++)
            {
               for( j=0;j<8;j++)
                    {
                     clock_Write(1u);
                     bitWrite(data[2-i], 7-j, data_Read());
                     clock_Write(0u);
                    }
            }
                clock_Write(1u);
                clock_Write(0u);
  //verified till this using arduino code 
  
 final_data=((long)data[2]<<16)|((long)data[1]<<8)|((long)data[0]);
 sum+=final_data;
 count++;
 if(count==25)
 {    final=(long)(sum/25);
  if(final>=8388607)
  {
    final1=final;
    //digitalWrite(pin_powerdown, LOW);
    power_Write(0u);
    CyDelay(200);
    //digitalWrite(pin_powerdown, HIGH);
    power_Write(1u);
    CyDelay(200);
    final=final1-16777216;
 }
 sprintf(result, "%ld", final);
 UART_UartPutString(result);
 UART_UartPutString("\n");

// Serial.println("Sorry");
 /*while(digitalRead(pin_data))
 Serial.println("Stuck");*/
// return((long)data[2]<<16)|((long)data[1]<<8)|((long)data[0]);
//  return(dataz>>8);
count=0;
sum=0;
}
}
 
int main()
{
   
    UART_Start();
    CyGlobalIntEnable; /* Enable global interrupts. */
    long x;
    int i,j;
    char buffer[8];
    power_Write(1u);
    temp_Write(0u);
    channel_Write(0u);
    gain0_Write(0u);
    gain1_Write(0u);
    speed_Write(1u);

    UART_UartPutString("Press the load, you've 5 seconds");
    CyDelay(5000);
 
  while(1)
    {
        if(!data_Read())
  {
    getvalue();
    //Serial.println(getvalue());
    //delay(1000);
  }


/*    x=getvalue();
    if(x>8388607)
    x=x-16777216;
   // UART_UartWriteTxData(x);
    sprintf(buffer, "%ld", x);
    UART_UartPutString(buffer);
    UART_UartPutString("\n");
    CyDelay(1200);
*/
    }
}
    
   
   /* [] END OF FILE */
