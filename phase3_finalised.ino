 #define cs 12
 #define ls 13
 #define rs 11
 #define lmp 6
 #define lmn 7
 #define rmp 4
 #define rmn 5
 #define trigPin 2
 #define echoPin 3

  
int fx=0,fy=0,x=0,y=0,xmax=0,ymax=0,ix=0,iy=0,cx=0,cy=0;
int flag = 0,pole=1,count=0;
char dir = 'N';
char watdir[5]="left", obdir[3];
int obx[3],oby[3];
long duration;
int distance;
char cdir;
int node();
int forward();
int backward();
int forright();
int backright();
int forleft();
int backleft();
int pause();
int imright();
int imleft();
int obstrucle();
int left_obstrucle();
int right_obstrucle();
int turn_wrt_x();
int turn_wrt_y();
int line_follower(int pole);
int serial_available();
int stoping();


void setup()
 {
  pinMode(ls,INPUT);
  pinMode(rs,INPUT);
  pinMode(cs,INPUT);
  pinMode(lmp,OUTPUT);
  pinMode(lmn,OUTPUT);
  pinMode(rmp,OUTPUT);
  pinMode(rmn,OUTPUT);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  Serial.begin(9600);
 }


void loop() 
{
  serial_available();
  obstrucle();
     
    turn_wrt_x();
    turn_wrt_y();
 

    line_follower(pole);
    if(digitalRead(ls) && digitalRead(cs) && digitalRead(rs)) 
         node();
  
}   
//end of void lopp//

//function definitions//

int node()
  {
    if(cdir=='N' || cdir=='S')
    {
         if(!flag)
          x++;
         else
          y++;
         if((x==abs(xmax)+1) && ((ymax>0 && dir=='E')|| (ymax<0 && dir=='W')))
         {
          imleft();
          flag=1;
         }
         else if((x==abs(xmax)+1) && ((ymax<0 && dir=='E')|| (ymax>0 && dir=='W')))
         {
          imright();
          flag=1;
         }
         if(y==abs(ymax) && x==abs(xmax)+1)
         {
          stoping();
          cdir='N';
          count=0;
          obx[1]=100,oby[1]=100,obdir[1]='A';
          obx[2]=100,oby[2]=100,obdir[2]='A';
          obx[0]=100,oby[0]=100,obdir[0]='A';
          strcpy(watdir,"left");
         
         }
    }
    else if (cdir=='E' || cdir=='W')
    {
      if(!flag)
          y++;
         else
          x++;
         if(y==abs(ymax) && ((xmax>0 && dir=='E') || (xmax<0 && dir=='W')))
         {
           imright();
           flag=1;
         }
         else if(y==abs(ymax) && ((xmax<0 && dir=='E') || (xmax>0 && dir=='W'))) 
         {
          imleft();
          flag=1;
         }
         if(y==abs(ymax) && x==abs(xmax)+1)
         {
          stoping();
          cdir='N';
          count=0;
          obx[0]=100,oby[0]=100,obdir[0]='A';
          obx[1]=100,oby[1]=100,obdir[1]='A';
          obx[2]=100,oby[2]=100,obdir[2]='A';
          strcpy(watdir,"left");
         }
     }
  }
  int forward()
  {
     digitalWrite(lmp,HIGH);
     digitalWrite(lmn,LOW);
     digitalWrite(rmp,HIGH);
     digitalWrite(rmn,LOW);
  }
  int backward()
 {
   digitalWrite(lmp,LOW);
   digitalWrite(lmn,HIGH);
   digitalWrite(rmp,LOW);
   digitalWrite(rmn,HIGH);
 }
 
  int forleft()
  {
     digitalWrite(lmp,LOW);
     digitalWrite(lmn,LOW);
     digitalWrite(rmp,HIGH);
     digitalWrite(rmn,LOW);
    
  }
  int forright()
  {
     digitalWrite(lmp,HIGH);
     digitalWrite(lmn,LOW);
     digitalWrite(rmp,LOW);
     digitalWrite(rmn,LOW);
     
  }
  int backleft()
  {
    digitalWrite(lmp,LOW);
    digitalWrite(lmn,LOW);
    digitalWrite(rmp,LOW);
    digitalWrite(rmn,HIGH);
  }
  int backright()
  {
    digitalWrite(lmp,LOW);
    digitalWrite(lmn,HIGH);
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
    delay(2000);
    }
     
    if(dir=='N')
      dir='E';
    if(dir=='S')
      dir='W';
    if(dir=='E')
      dir='S';
    if(dir=='W')
      dir='N';
 
 }
  int imleft()
  {
    while (!(!(digitalRead(ls)) && digitalRead(cs)&& !(digitalRead(rs))))
    {
    digitalWrite(lmp,LOW);
    digitalWrite(lmn,LOW);
    digitalWrite(rmp,HIGH);
    digitalWrite(rmn,LOW);
    delay(2000);
    }
    if(dir=='N')
      dir='W';
    if(dir=='S')
      dir='E';
    if(dir=='E')
      dir='N';
    if(dir=='W')
      dir='S';

  }
  
  int pause()
  {
     digitalWrite(lmp,LOW);
     digitalWrite(lmn,LOW);
     digitalWrite(rmp,LOW);
     digitalWrite(rmn,LOW);
  }
  
  int line_follower(int pole) //pole=1 for forward line follower 
  {
   if(!(digitalRead(ls)) && digitalRead(cs)&& !(digitalRead(rs))&& pole)
       forward();
   else
       backward();
   if(digitalRead(ls)&& !(digitalRead(cs)) && !(digitalRead(rs))&& pole)
       forleft();
   else
       backright();
   if(!(digitalRead(ls)) && !(digitalRead(cs)) && digitalRead(rs)&& pole)
        forright();
   else
        backleft();
  
  }
 
int turn_wrt_x()
{
 if (cdir=='N' || cdir=='S')
 {
  pole=1;
    
   if(xmax>0 && dir=='N')
      imright();
   else if(xmax>0 && dir=='S')
      imleft();
   else if(xmax>0 && dir=='E')
      forward();
   else if (xmax>0 && dir=='W')
      {
        backward();
        pole=0;
      }
    else if (xmax<0 && dir=='N')
        imleft();
    else if(xmax<0 && dir=='S')
        imright();
    else if(xmax<0 && dir=='E')
      {
       backward();
       pole=0;
      }
   else if(xmax<0 && dir=='W')
         forward();
   else if(xmax==0 && ymax>0 && dir=='N')
        forward();
    else if(xmax==0 && ymax>0 && dir=='S')
       {
        backward();
        pole=0;
       }
    else if(xmax==0 && ymax>0 && dir=='E')
        imleft();
    else if(xmax==0 && ymax>0 && dir=='W')
        imright();
    else if(xmax==0 && ymax<0 && dir=='N')
       {
        backward();
        pole=0;
       }
    else if(xmax==0 && ymax<0 && dir=='S')
        forward();
    else if(xmax==0 && ymax<0 && dir=='E')
        imright();
    else if(xmax==0 && ymax<0 && dir=='W')
        imleft();
  }
}
 

int turn_wrt_y()
{
  if (cdir=='E' || cdir=='W') 
  {
    pole=1;
    
    if(ymax>0 && dir=='N')
       forward();
    else if(ymax>0 && dir=='S')
      {
        backward();
        pole=0;
      }
    else if(ymax>0 && dir=='E')
       imleft();
    else if(ymax>0 && dir=='W')
       imright();
    else if(ymax<0 && dir=='N')
      {
        backward();
        pole=0;
      }
    else if(ymax<0 && dir=='S')
        forward();
    else if(ymax>0 && dir=='E')
        imright();
    else if(ymax>0 && dir=='W')
        imleft();
    else if(ymax==0 && xmax>0 && dir=='N')
        imright();
    else if(ymax==0 && xmax>0 && dir=='S')
        imleft();
    else if(ymax==0 && xmax>0 && dir=='E')
        forward();
    else if(ymax==0 && xmax>0 && dir=='W')
       {
        backward();
        pole=0;
       }
    else if(ymax==0 && xmax<0 && dir=='N')
       imleft();
    else if(ymax==0 && xmax<0 && dir=='S')
       imright();
    else if(ymax==0 && xmax<0 && dir=='E')
       backward();
    else if(ymax==0 && xmax<0 && dir=='W')
       forward();
   }
 } 
 int obstrucle()
 {
   digitalWrite(trigPin,LOW);
   delayMicroseconds(2);
   digitalWrite(trigPin,HIGH);
   delayMicroseconds(10);
   digitalWrite(trigPin,LOW);
   duration= pulseIn(echoPin,HIGH);
   distance= duration*0.034/2;

   
if(distance<=15)
{
  
  if(xmax>0)
   cx=ix+x;
  else
   cx=ix-x;
  if (ymax>0)
   cy=iy+y;
  else
   cy=iy-y;
   
   //infite loop program start............... 
   
    if((( obx[0]==cx && oby[0]==cy && obdir[0]==dir) || (obx[1]==cx && oby[1]==cy && obdir[1]==dir) ||  (obx[2]==cx && oby[2]==cy && obdir[2]==dir)) && cx!=0 && cx!=4 && cy!=0 && cy!=4)
        {
          if(!(strcmp(watdir,"left")))
            
              strcpy(watdir,"right");
          else 
              strcpy(watdir,"left");
        }
     else
        {
          obx[count]=cx, oby[count]=cy,  obdir[count]=dir;
          count+=1;
        }

    //infinite loop program end............
           
           if ((cx==0 && dir=='N') || (cy==4 && dir=='E') || (cx==4 && dir=='S') || (cy==0 && dir=='W') || (!(strcmp(watdir,"right"))))
               right_obstrucle();
           else
               left_obstrucle();
               
    }
  }
 

     
 int left_obstrucle()
 {
  pause();
  delay(100);
  while (!(digitalRead(ls) && digitalRead(cs) && digitalRead(rs)))
       line_follower(0); 
  delay(100);
  imleft();
  delay(100);
  while (!(digitalRead(ls) && digitalRead(cs) && digitalRead(rs))) 
      {
        obstrucle();
        line_follower(1);
      }
      
       cdir=dir;
  
  
  if(((dir=='N') && ymax>=0) || ((dir=='S') && ymax<0))
     y=y+1;
  else if(((dir=='S') && ymax>=0) || ((dir=='N') && ymax<0))
     y=y-1;
  else if(((dir=='E') && xmax>=0) || ((dir=='W') && xmax<0))
     x=x+1;
  else if(((dir=='W') && xmax>=0) || ((dir=='E') && xmax<0))
     x=x-1;


    if(xmax>0)
     xmax=xmax-x;
    else
     xmax=xmax+x;
    if (ymax>0)
     ymax=ymax-y;
    else
     ymax=ymax-y;
    x=0,y=0;
 }
 

 int right_obstrucle()
 {
  pause();
  delay(100);
  while (!(digitalRead(ls) && digitalRead(cs) && digitalRead(rs)))
      line_follower(0);
  delay(100);
  imright();
  delay(100);
  while (!(digitalRead(ls) && digitalRead(cs) && digitalRead(rs))) 
   {
    obstrucle();
    line_follower(1);
   }

   
  cdir=dir;

  
  if(((dir=='N') && ymax>=0) || ((dir=='S') && ymax<0))
     y=y+1;
  else if(((dir=='S') && ymax>=0) || ((dir=='N') && ymax<0))
     y=y-1;
  else if(((dir=='E') && xmax>=0) || ((dir=='W') && xmax<0))
     x=x+1;
  else if(((dir=='W') && xmax>=0) || ((dir=='E') && xmax<0))
     x=x-1;


  if(xmax>0)
   xmax=xmax-x;
  else
   xmax=xmax+x;
  if (ymax>0)
   ymax=ymax-y;
  else
   ymax=ymax-y;
  x=0,y=0;
  
}
int serial_available()
{
  if(x==0 && y==0)
  {
  while(Serial.available())
  {
    
    x=Serial.read();
    Serial.println(x);
   
    
    y=Serial.read();
    Serial.println(y);
    
  }
  
    xmax=x-fx;
    ymax=y-fy;
    ix=fx,iy=fy;
    fx=x,fy=y;
    x=0,y=0;
    return(true);
  }
}
int stoping()
 {
     while(!(serial_available()))
     {
     digitalWrite(lmp,LOW);
     digitalWrite(lmn,LOW);
     digitalWrite(rmp,LOW);
     digitalWrite(rmn,LOW);
     }
  }

 


 
 
  
