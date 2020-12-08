 #define cs 12
 #define ls 13
 #define rs 11
 #define lmp 6
 #define lmn 7
 #define rmp 4
 #define rmn 5
int x=0,y=0,xmax,ymax,ix=2,iy=-1,fx=0,fy=0;
int flag = 0;
char dir = 'N';


void setup()
 {
  pinMode(ls,INPUT);
  pinMode(rs,INPUT);
  pinMode(cs,INPUT);
  pinMode(lmp,OUTPUT);
  pinMode(lmn,OUTPUT);
  pinMode(rmp,OUTPUT);
  pinMode(rmn,OUTPUT);
  Serial.begin(9600); 
 }
  
void loop() 
{
  if(x==0 && y==0)
  {
  while(Serial.available())
   {
    
    fx=Serial.read();
    Serial.println(fx);
 
    
    fy=Serial.read();
    Serial.println(fy);
    
  }
    xmax=fx-ix;
    ymax=fy-iy;
  }

   if(xmax>0 && dir=='N')
      imright();
   else if(xmax>0 && dir=='S')
      imleft();
   else if(xmax>0 && dir=='E')
       forward();
   else if (xmax>0 && dir=='W')
        uturn();
   else if (xmax<0 && dir=='N')
       {
         imleft();
        
       }
   else if(xmax<0 && dir=='S')
       {
         imright();
      
       }
   else if(xmax<0 && dir=='E')
        { 
           uturn();
       
        }
   else if(xmax<0 && dir=='W')
        {
         forward();
      
        }
    else if(xmax==0 && ymax>0 && dir=='N')
        forward();
    else if(xmax==0 && ymax>0 && dir=='S')
        uturn();
    else if(xmax==0 && ymax>0 && dir=='E')
        imleft();
    else if(xmax==0 && ymax>0 && dir=='W')
        imright();
    else if(xmax==0 && ymax<0 && dir=='N')
        uturn();
    else if(xmax==0 && ymax<0 && dir=='S')
        forward();
    else if(xmax==0 && ymax<0 && dir=='E')
        imright();
    else if(xmax==0 && ymax<0 && dir=='W')
        imleft();

   if(!(digitalRead(ls)) && digitalRead(cs)&& !(digitalRead(rs)))
      {
         forward();
      }
    if(digitalRead(ls)&& !(digitalRead(cs)) && !(digitalRead(rs)))
      {
         left();
         
      }
       
   if(!(digitalRead(ls)) && !(digitalRead(cs)) && digitalRead(rs))
      {
         right();
        
      }
  
    if(digitalRead(ls) && digitalRead(cs) && digitalRead(rs)) 
      {
         node();
         
      }
}



int node()
  {
         if(!flag)
         {
          x++;
          delay(100);
         }
         else
        {  
          y++;
          delay(100); 
        }
         if(x==abs(xmax)+1 && ((ymax>0 && dir=='E')||(ymax<0 && dir=='W')))
         {
          imleft();
          flag=1;
         }
         else if(x==abs(xmax)+1 &&(( ymax<0 && dir=='E')|| (ymax>0 && dir=='W')))
         {
          imright();
          flag=1;
          
         }
         if(y==abs(ymax) && x==abs(xmax)+1)
         {
          pause();
          flag=0;
          x=ix,y=iy;
          ix=fx,iy=fy;
          fx=x,fy=y;
          x=0,y=0;
         }
         
 }
  int forward()
  {
     digitalWrite(lmp,HIGH);
     digitalWrite(lmn,LOW);
     digitalWrite(rmp,HIGH);
     digitalWrite(rmn,LOW);
    
  }
  int left()
  {
     digitalWrite(lmp,LOW);
     digitalWrite(lmn,LOW);
     digitalWrite(rmp,HIGH);
     digitalWrite(rmn,LOW);
    
  }
  int right()
  {
     digitalWrite(lmp,HIGH);
     digitalWrite(lmn,LOW);
     digitalWrite(rmp,LOW);
     digitalWrite(rmn,LOW);
     
  }
  int imright()
  {
      while (!(!(digitalRead(ls)) && digitalRead(cs)&& !(digitalRead(rs))))
      {
   
        digitalWrite(lmp,HIGH);
        digitalWrite(lmn,LOW);
        digitalWrite(rmp,LOW);
        digitalWrite(rmn,LOW);
      }
    
    
    if(dir=='N')
      dir='E';
    else if(dir=='S')
      dir='W';
    else if(dir=='E')
      dir='S';
    else if(dir=='W')
      dir='N';
    
      
 
  }
  int imleft()
  {
     while(!(!(digitalRead(ls)) && digitalRead(cs)&& !(digitalRead(rs))))
      {
        digitalWrite(lmp,LOW);
        digitalWrite(lmn,LOW);
        digitalWrite(rmp,HIGH);
        digitalWrite(rmn,LOW);
      }
   
    if(dir=='N')
      dir='W';
    else if(dir=='S')
      dir='E';
    else if(dir=='E')
      dir='N';
    else if(dir=='W')
      dir='S';

  }
  int pause()
  {
     digitalWrite(lmp,LOW);
     digitalWrite(lmn,LOW);
     digitalWrite(rmp,LOW);
     digitalWrite(rmn,LOW);
     delay(1000);
  }
 int uturn()
 {
    int i;
    for(i=0;i<2;i++)
   {
     imright();
     delay(2000);
   }
 }
