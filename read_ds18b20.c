#define ONE_WIRE_PIN PIN_A0
void OneWire_Reset()
{
   output_low(ONE_WIRE_PIN);  
   delay_us( 500 );
   output_float(ONE_WIRE_PIN); 
   delay_us( 500 ); 
   output_float(ONE_WIRE_PIN); 
}
void OneWire_Write(int data)
{
   int gui;
   for (gui=0; gui<8; ++gui)
   {
   output_low(ONE_WIRE_PIN);
   delay_us( 2 ); 
   output_bit(ONE_WIRE_PIN, shift_right(&data,1,0)); 
   delay_us( 60 ); 
   output_float(ONE_WIRE_PIN); 
   delay_us( 2 ); 
   }
}

int OneWire_Read()
{
   int doc, data;
   for (doc=0; doc<8; ++doc)
   {
   output_low(ONE_WIRE_PIN); 
   delay_us( 2 );                      
   output_float(ONE_WIRE_PIN);       
   delay_us( 8 );                
   shift_right(&data,1,input(ONE_WIRE_PIN));
   delay_us( 120 );  
}
return( data );
} 

ds1820_read()
{
   int8 busy=0, thanhghi1, thanhghi2;
   signed int16 temp;
   float nhiet;
   OneWire_Reset();
   OneWire_Write(0xCC);
   OneWire_Write(0x44);
   while (busy == 0)
   busy = OneWire_Read();
   OneWire_Reset();
   OneWire_Write(0xCC); 
   OneWire_Write(0xBE); 
   thanhghi1 = OneWire_Read();  
   thanhghi2 = OneWire_Read();   
   temp = make16(thanhghi2, thanhghi1); 
   nhiet = (float) temp / 16.0; 
   delay_ms(100);
   return nhiet;
} 
