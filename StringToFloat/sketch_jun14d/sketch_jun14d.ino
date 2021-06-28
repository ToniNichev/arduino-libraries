#include "string_to_float.h"
//char str[] = { '[', '2', '3', ']' };
String serverBodyResponse = "[0,1,42.50,28.90,1]";
  
void setup() 
{

  Serial.begin(9600);
  float *r = parseToValues(serverBodyResponse);  
  

  Serial.println(r[0],4);
  Serial.println(r[1],4);
  Serial.println(r[2],4);
  Serial.println();
  

  //double val[] = { 12.3, 53.21, 4, 6 };
  //String str = valuesToString(val, 3);
  //Serial.println(str);
}
void loop() {}
