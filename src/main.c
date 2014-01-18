#include"main.h"
struct point RltP;
struct point AbsP;

int Backpack[element_MAX];
int BreakCnt=0;
int BackCnt=0;
int money=500;
int Oil=100000;
int HP=30;
// LEVEL
int aDD[7]={0,2,3,4,5,6,7};
int DDL=1;

int FRS[7]={0,1,1.2,1.4,1.6,1.8,2};
int FRSL=1; 

int BP[7]={0,7,11,16,22,29,37};
int BPL=1;

int DS[7]={0,1,2,3,5,8,13};
int DSL=1;

int OB[7]={0,30,60,80,100,150,200};
int OBL=1;

int mHP[7]={0,30,60,100,150,210,250};
int HPL=1;

int UpGradeMoney[6]={0,750,2000,8000,40000,200000};
int DownV=0;
int Acc=3;
int OilTime=0;
char filename[100];
int Down1000Time=0;
int HasBack=1;
int StoneBreaker=0; 

int EEL1=0; // D400,M+500 
int EEL2=0; //D1000,M+1000 
int EEL3=0; //D1500,M+2000 
int GetSecNumber1()
{
   int re=0;
   int lx;
   re+= DDL*FRSL+FRSL*BPL+DSL*DSL+OBL*7+HPL*DDL*4+BreakCnt+3*StoneBreaker;
   re+= EEL1*EEL2+EEL2*EEL3+EEL3*EEL1; 
   for(lx=0;lx<element_MAX;lx++)
      re+=Backpack[lx]*(lx+Backpack[(5*lx)%element_MAX]);
   return re;
}
int GetSecNumber2()
{
   return (int)(HP*3)+(int)(Oil)+money*5+BackCnt*BackCnt;
}
int main()
{
   //--Initial Region
   int lx;
   InitialElement();
   //printf("#");
   InitialMap();
   //printf("1");
   InitialWater();
   
   RltP.x=4;
   RltP.y=3;
   AbsP.x=4;
   AbsP.y=3;
   HP=mHP[HPL];
   for(lx=0;lx<element_MAX;lx++)
      Backpack[lx]=0;  
   //Load File---
   char name[50];
   int Stt=2;
   Stt=Rnd(8,1);
   FILE *fp;
   //ShowMSG("><"); 
   printf("Treasure 2.0 Made By 藍雪 2012(%d)\n",Stt);
   printf("請輸入名子:"); 
   gets(name);
   strcpy(filename,name);
   sprintf(filename,"%s%s",name,acfile);
   //fp=fopen(filename,"r");
   printf("%s #",filename);
   Oil=OB[OBL];
   if((fp=fopen(filename,"r"))!=NULL)
   {
      int c1;
      int c2;
      fp=fopen(filename,"r");
      fscanf(fp,"%d %d %d %d %d %d",&DDL,&FRSL,&OBL,&BPL,&DSL,&HPL);
      fscanf(fp,"%d %d %d %d %d %d",&Oil,&HP,&money,&BackCnt,&BreakCnt,&StoneBreaker);
      fscanf(fp,"%d %d %d",&EEL1,&EEL2,&EEL3); 
      for(lx=0;lx<element_MAX;lx++)
         fscanf(fp,"%d",&Backpack[lx]);
      fscanf(fp,"%d %d",&c1,&c2);
      if((c1==GetSecNumber1())&&(c2==GetSecNumber2()))
      {
      }
      else
      {
         system("cls");
         printf("Your are very laippy= =.\n");
         int g;
         g=getch();
         if(g!='#')
            return 0;
         
      }
      goto skipillustrate; 
   }
   //printf("1K");
   //--------------------
illustrate: 
   system("cls");
   printf("挖礦遊戲\n");
   printf("移動挖礦機(Θ)：←↑→↓鍵，向上移動時，無法挖礦。\n");
   printf("儲存點：Δ ");
   printf("商店：Ω");
   getch(); 
skipillustrate:
   textbackground(7);
   system("cls");
   gotoxy(1,6);
   
   textbackground(7);
   //printf("KKK");
   ShowMap(AbsP,RltP);
   //說明
 
   //-----------
   int RunTime=0;
   int Temp;
   int SET=0;
   int MapTimer=0;    
   while(1)
   {
      InitialWater(MapTimer);  
      MapTimer++;
      MapTimer=MapTimer%SecTime;
      if((AbsP.y-3>=500)&&(HasBack))
      {
         Down1000Time++;
         HasBack=0;
      }
      if((Oil<=0)||(HP<=0))
         break;
      int DigSoilTime=0;
      OilTime+=1;
      Temp=(int)(20*sqrt(sqrt(10+abs(AbsP.y-3))));
      if(OilTime>=100)
      {
         Oil-=(int)(OilTime/100);
         OilTime=0;
      }
      DigSoilTime=(int)(21*sqrt(sqrt(AbsP.y-1))/DS[DSL]);
      gotoxy(1,1);
      textbackground(7);
      textcolor(0);
      printf("Deep:%d   \n",AbsP.y*4);
      printf("Money:%d   \n",money);
      printf("HP:%d/%d   \n",HP,mHP[HPL]);
      printf("Oil:%d   ",Oil);
      if(Oil<=10)
         printf("Low Oil!!\n");
      else
         printf("         \n");
      printf("Temperature:%d    DownTime:%d  ",Temp,Down1000Time);
      if((Temp>100)&&(Backpack[element_Ruber]>0))
      {
         char s[50];
         sprintf(s,"%d Ruber have turned into liquid.It break you backpack><.",Backpack[element_Ruber]);
         BreakCnt+=Backpack[element_Ruber];
         Backpack[element_Ruber]=0;
         sMSG(s);
      }
      gotoxy(24,15);
      printf("Press 'A' to check your backpack.");
      gotoxy(24,16);
      printf("Press 'B' to break the stone.");
      gotoxy(24,17);
      printf("Press 'S' to check you state.");
      if((EEL1==0)&&(4*AbsP.y>=400)) 
      {
         EEL1=1;
         money+=500;
         sMSG("You arrive 400m depth and get 500$!"); 
      }
      if((EEL2==0)&&(4*AbsP.y>=1000)) 
      {
         EEL2=1;
         money+=1000;
         sMSG("You arrive 400m depth and get 500$!"); 
      }
      if((EEL3==0)&&(4*AbsP.y>=1500)) 
      {
         EEL3=1;
         money+=1500;
         sMSG("You arrive 400m depth and get 500$!"); 
      } 
      if(WaterMap[AbsP.x][AbsP.y]>=60)
         DigSoilTime=(int)(DigSoilTime*5/4);
      if(kbhit())
      {

         RunTime=0;
         int Press;
         Press=getch();
         if(Press==0)
            Press=getch();
         switch(Press)
         {
            case 72:
               DownV=0;
               SET=0;
               if(AbsP.y>=2)
               {
                  if((Map[AbsP.x][AbsP.y-1]==MT_Air)||(Map[AbsP.x][AbsP.y-1]==MT_Sky))
                  {
                     AbsP.y--;
                     RltP.y--;
                     if(IsInArea(RltP)==0)
                        RltP.y++;
                     exsleep((int)(30/FRS[FRSL]));
                  }
                  if(Map[AbsP.x][AbsP.y-1]==MT_SavePoint)
                  {
                     fp=fopen(filename,"w");
                     fprintf(fp,"%d %d %d %d %d %d ",DDL,FRSL,OBL,BPL,DSL,HPL);
                     fprintf(fp,"%d %d %d %d %d %d ",Oil,HP,money,BackCnt,BreakCnt,StoneBreaker);
                     fprintf(fp,"%d %d %d ",EEL1,EEL2,EEL3); 
                     for(lx=0;lx<element_MAX;lx++)
                        fprintf(fp,"%d ",Backpack[lx]);
                     fprintf(fp,"%d %d ",GetSecNumber1(),GetSecNumber2());
                     sMSG("Save successfully!!"); 
                  }

               }
               break;
            case 75:
               if(AbsP.x>=2)
               {
                  if(Map[AbsP.x-1][AbsP.y]==MT_Fire)
                  {
                     Oil=0;
                     break;
                  }
                  if((Map[AbsP.x-1][AbsP.y]==MT_Stone)||(Map[AbsP.x-1][AbsP.y]==MT_Fire))
                  {
                     goto EmptyTime;
                     break;
                  }
                  if((Map[AbsP.x-1][AbsP.y]==MT_Air)||(Map[AbsP.x-1][AbsP.y]==MT_Sky))
                  {
                     AbsP.x--;
                     RltP.x--;
                     if(IsInArea(RltP)==0)
                        RltP.x++;
                     break;
                  }
                  else 
                  {
                     if((Map[AbsP.x][AbsP.y+1]==MT_Air)==0)
                     {
                        if(Map[AbsP.x-1][AbsP.y]==MT_Soil)
                        {
                           Map[AbsP.x-1][AbsP.y]=MT_Air;
                           AbsP.x--;
                           RltP.x--;
                           CntDelay(DigSoilTime);
                           if(IsInArea(RltP)==0)
                              RltP.x++;
                           break;
                        }
                        else if(Map[AbsP.x-1][AbsP.y]<=element_MAX)
                        {
                           if(BackCnt<BP[BPL]-BreakCnt)
                           {
                              Backpack[Map[AbsP.x-1][AbsP.y]]++; 
                              BackCnt++;
                           }
                           else
                              sMSG("BackPack is full.");  
                           Map[AbsP.x-1][AbsP.y]=MT_Air;
                           AbsP.x--;
                           RltP.x--;
                           if(IsInArea(RltP)==0)
                              RltP.x++;
                           CntDelay(DigSoilTime);break;
                        }
                        else if(Map[AbsP.x-1][AbsP.y]==MT_MoneyI)
                        {
                           int g=Rnd(1250,250);
                           if(WaterMap[AbsP.x][AbsP.y]>=1)
                              g=(int)(g-10*WaterMap[AbsP.x][AbsP.y]);
                           char c[20];
                           sprintf(c,"You get %d$.",g);
                           Map[AbsP.x-1][AbsP.y]=MT_Air;
                           AbsP.x--;
                           RltP.x--;
                           if(IsInArea(RltP)==0)
                              RltP.x++;
                           CntDelay(DigSoilTime);
                           money+=g;
                           sMSG(c);break;
                        }
                        else if(Map[AbsP.x-1][AbsP.y]==MT_MoneyII)
                        {
                           int g=Rnd(2250,250);
                           char c[20];
                           if(WaterMap[AbsP.x][AbsP.y]>=1)
                              g=(int)(g-10*WaterMap[AbsP.x][AbsP.y]);
                           sprintf(c,"You get %d$.",g);
                           Map[AbsP.x-1][AbsP.y]=MT_Air;
                           AbsP.x--;
                           RltP.x--;
                           if(IsInArea(RltP)==0)
                              RltP.x++;
                           CntDelay(DigSoilTime);
                           money+=g;
                           sMSG(c);break;
                        }
                        else if(Map[AbsP.x-1][AbsP.y]==MT_MoneyIII)
                        {
                           int g=Rnd(2500,250);
                           char c[20];
                           if(WaterMap[AbsP.x][AbsP.y]>=1)
                              g=(int)(g-10*WaterMap[AbsP.x][AbsP.y]);
                           sprintf(c,"You get %d$.",g);
                           Map[AbsP.x-1][AbsP.y]=MT_Air;
                           AbsP.x--;
                           RltP.x--;
                           if(IsInArea(RltP)==0)
                              RltP.x++;
                           CntDelay(DigSoilTime);
                           money+=g;
                           sMSG(c);break;
                        }
                     }
                  }
                  
               }
               break;
            case 77:
               if(AbsP.x<=19)
               {
                  if(Map[AbsP.x+1][AbsP.y]==MT_Fire)
                  {
                     Oil=0;
                     break;
                  }
                  if((Map[AbsP.x+1][AbsP.y]==MT_Stone)||(Map[AbsP.x+1][AbsP.y]==MT_Fire))
                  {
                     goto EmptyTime;
                     break;
                  }
                  if((Map[AbsP.x+1][AbsP.y]==MT_Air)||(Map[AbsP.x+1][AbsP.y]==MT_Sky))
                  {
                     AbsP.x++;
                     RltP.x++;
                     if(IsInArea(RltP)==0)
                        RltP.x--;
                  }
                  else 
                  {
                     if((Map[AbsP.x][AbsP.y+1]==MT_Air)==0)
                     {
                        if(Map[AbsP.x+1][AbsP.y]==MT_Soil)
                        {
                           Map[AbsP.x+1][AbsP.y]=MT_Air;
                           AbsP.x++;
                           RltP.x++;
                           CntDelay(DigSoilTime);
                           if(IsInArea(RltP)==0)
                              RltP.x--;
                           break;
                        }
                        else if(Map[AbsP.x+1][AbsP.y]<=element_MAX)
                        {
                           if(BackCnt<BP[BPL]-BreakCnt)
                           {
                              Backpack[Map[AbsP.x+1][AbsP.y]]++; 
                              BackCnt++;
                           }
                           else
                              sMSG("BackPack is full.");
 
                           Map[AbsP.x+1][AbsP.y]=MT_Air;
                           AbsP.x++;
                           RltP.x++;
                           if(IsInArea(RltP)==0)
                              RltP.x--;
                           
                           CntDelay(DigSoilTime);
                           break;
                        }
                        else if(Map[AbsP.x+1][AbsP.y]==MT_MoneyI)
                        {
                           int g=Rnd(1250,250);
                           char c[20];
                           if(WaterMap[AbsP.x][AbsP.y]>=1)
                              g=(int)(g-10*WaterMap[AbsP.x][AbsP.y]);
                           sprintf(c,"You get %d$.",g);
                           Map[AbsP.x+1][AbsP.y]=MT_Air;
                           AbsP.x++;
                           RltP.x++;
                           if(IsInArea(RltP)==0)
                              RltP.x--;
                           CntDelay(DigSoilTime);
                           money+=g;
                           sMSG(c);
                           break;
                        }
                        else if(Map[AbsP.x+1][AbsP.y]==MT_MoneyII)
                        {
                           int g=Rnd(2250,250);
                           char c[20];
                           if(WaterMap[AbsP.x][AbsP.y]>=1)
                              g=(int)(g-10*WaterMap[AbsP.x][AbsP.y]);
                           sprintf(c,"You get %d$.",g);
                           Map[AbsP.x+1][AbsP.y]=MT_Air;
                           AbsP.x++;
                           RltP.x++;
                           if(IsInArea(RltP)==0)
                              RltP.x--;
                           CntDelay(DigSoilTime);
                           money+=g;
                           sMSG(c);
                           break;
                        }
                        else if(Map[AbsP.x+1][AbsP.y]==MT_MoneyIII)
                        {
                           int g=Rnd(2500,250);
                           char c[20];
                           if(WaterMap[AbsP.x][AbsP.y]>=1)
                              g=(int)(g-10*WaterMap[AbsP.x][AbsP.y]);
                           sprintf(c,"You get %d$.",g);
                           Map[AbsP.x+1][AbsP.y]=MT_Air;
                           AbsP.x++;
                           RltP.x++;
                           if(IsInArea(RltP)==0)
                              RltP.x--;
                           CntDelay(DigSoilTime);
                           money+=g;
                           sMSG(c);
                           break;
                        }
                     }
                  }
               }
               break;
            case 80:
               if(Map[AbsP.x][AbsP.y+1]==MT_Store)
               {
                  HasBack=1;
                  GoShop();
                  if(Down1000Time>=Stt)
                  {
                     Stt=Rnd(8,1);
                     ReMap();
   //printf("1");
                     RltP.x=8;
                     RltP.y=2;
                     AbsP.x=10;
                     AbsP.y=2;
                     sMSG("Earthquake!!");
                     Down1000Time=0;
                  }
                  break;
               }
               if(AbsP.y<=1749)
               {
                  if((Map[AbsP.x][AbsP.y+1]==MT_Fire))
                  {
                     Oil=0;
                     break;
                  }
                  if((Map[AbsP.x][AbsP.y+1]==MT_Stone)||(Map[AbsP.x][AbsP.y+1]==MT_Fire))
                     break;  
                  if((Map[AbsP.x][AbsP.y+1]==MT_Air)||(Map[AbsP.x][AbsP.y+1]==MT_Sky))
                  {
                     SET++;
                     DownV+=3;
                     if(DownV>6)
                        DownV=6;
                     AbsP.y++;
                     RltP.y++;
                     if(IsInArea(RltP)==0)
                        RltP.y--;
                  }
                  else
                  {
                     if(Map[AbsP.x][AbsP.y+1]==MT_Soil)
                     {
                        SET=0;
                        Map[AbsP.x][AbsP.y+1]=MT_Air;
                        AbsP.y++;
                        RltP.y++;
                        if(IsInArea(RltP)==0)
                           RltP.y--;
                        CntDelay(DigSoilTime);
                        break;
                     }
                     else if(Map[AbsP.x][AbsP.y+1]<=element_MAX)
                     {
                        if(BackCnt<BP[BPL]-BreakCnt)
                        {
                           Backpack[Map[AbsP.x][AbsP.y+1]]++; 
                           BackCnt++;
                        }
                        else
                           sMSG("BackPack is full.");
                        Map[AbsP.x][AbsP.y+1]=MT_Air;
                        AbsP.y++;
                        RltP.y++;
                        if(IsInArea(RltP)==0)
                           RltP.y--;
                        CntDelay(DigSoilTime);
                        break;
                     }
                     else if(Map[AbsP.x][AbsP.y+1]==MT_MoneyI)
                     {
                        int g=Rnd(1250,250);
                        char c[20];
                        if(WaterMap[AbsP.x][AbsP.y]>=1)
                           g=(int)(g-10*WaterMap[AbsP.x][AbsP.y]);
                        sprintf(c,"You get %d$.",g);
                        Map[AbsP.x][AbsP.y+1]=MT_Air;
                        AbsP.y++;
                        RltP.y++;
                        if(IsInArea(RltP)==0)
                           RltP.y--;
                        CntDelay(DigSoilTime);
                        money+=g;
                        sMSG(c);
                        break;
                     }
                     else if(Map[AbsP.x][AbsP.y+1]==MT_MoneyII)
                     {
                        int g=Rnd(2250,250);
                        char c[20];
                        if(WaterMap[AbsP.x][AbsP.y]>=1)
                           g=(int)(g-10*WaterMap[AbsP.x][AbsP.y]);
                        sprintf(c,"You get %d$.",g);
                        Map[AbsP.x][AbsP.y+1]=MT_Air;
                        AbsP.y++;
                        RltP.y++;
                        if(IsInArea(RltP)==0)
                           RltP.y--;
                        CntDelay(DigSoilTime);
                        money+=g;
                        sMSG(c);
                        break;
                     }
                     else if(Map[AbsP.x][AbsP.y+1]==MT_MoneyIII)
                     {
                        int g=Rnd(2500,250);
                        char c[20];
                        if(WaterMap[AbsP.x][AbsP.y]>=1)
                           g=(int)(g-10*WaterMap[AbsP.x][AbsP.y]);
                        sprintf(c,"You get %d$.",g);
                        Map[AbsP.x][AbsP.y+1]=MT_Air;
                        AbsP.y++;
                        RltP.y++;
                        if(IsInArea(RltP)==0)
                           RltP.y--;
                        CntDelay(DigSoilTime);
                        money+=g;
                        sMSG(c);
                        break;
                     }
                  }
               }
               break;
            case 'A':
               system("cls");
               printf(" Your backpack(%d/%d): \n",BackCnt,BP[BPL]-BreakCnt);
               for(lx=0;lx<element_MAX;lx++)
               {
                  if(lx==0)
                  {
                     textbackground(1);
                     textcolor(15);
                  }
                  else
                  {
                     textbackground(7);
                     textcolor(0);
                  }
                  if(strlen(ElementName[lx])>=8)
                     printf("%s\t%d\t\n",ElementName[lx],Backpack[lx]);
                  else
                     printf("%s\t\t%d\t\n",ElementName[lx],Backpack[lx]);
               }
               printf("Press K to throw selection away.\n");
               printf("Press E to Exit\n");
               int sel=1;
               while(1)
               {
                  //int Press1;
                  char Press1;
                  Press1=getch();
                  if(Press1==0)
                     Press1=getch();
                  if(Press1==72)
                  {
                     if(sel>=2)
                        sel--;
                  }
                  else if(Press1==80)
                  {
                     if(sel<element_MAX)
                        sel++;
                  }
                  else if(Press1=='K')
                  {
                     if(Backpack[sel-1]>0)
                     {
                        Backpack[sel-1]--;
                        BackCnt--;
                     }
                  }
                  else if(Press1=='E')
                     break;
                  textbackground(7);
                  gotoxy(1,1);
                  printf(" Your backpack(%d/%d):\n",BackCnt,BP[BPL]-BreakCnt);
                  for(lx=0;lx<element_MAX;lx++)
                  {
                     if(lx+1==sel)
                     {
                        textbackground(1);
                        textcolor(15);
                     }
                     else
                     {
                        textbackground(7);
                        textcolor(0);
                     }
                     if(strlen(ElementName[lx])>=8)
                        printf("%s\t%d\t\n",ElementName[lx],Backpack[lx]);
                     else
                        printf("%s\t\t%d\t\n",ElementName[lx],Backpack[lx]);
                     textbackground(7);
                     textcolor(0);
                  }
               }
               //getch();
               textbackground(7);
               system("cls");
               break;
            case 'W':
               WaterMap[AbsP.x][AbsP.y]=50;
               break;
            case 'S':
               system("cls");
               gotoxy(1,1);
               printf("StoneBreaker:%d  \n",StoneBreaker);
               printf("HP:%d  \n",HP);
               printf("Oil:%d   \n",Oil);
               getch();
               system("cls"); 
               break; 
            case 'B':
               if(AbsP.y<=10)
                  break;
               if(StoneBreaker<=0)
                  ShowMSG("You don't have enough StoneBreaker.");
               else
               {
                  system("cls");
                  gotoxy(1,1);
                  printf("press 'x' to break the selected stone.");
                  int StoneCnt=0;
                  if(Map[AbsP.x][AbsP.y+1]==MT_Stone)
                     StoneCnt++;
                  if(Map[AbsP.x+1][AbsP.y]==MT_Stone)
                     StoneCnt++;
                  if(Map[AbsP.x-1][AbsP.y]==MT_Stone)
                     StoneCnt++;
                  int sx=0;
                  if(StoneCnt>=1)
                  {
                     int sel=1;
                     while(1)
                     {
                        //system("cls");
                        gotoxy(1,6);
                        ShowMap(AbsP,RltP,aDD[DDL],1);
                        if(sel==1)
                           gotoxy(2*(RltP.x)-1,RltP.y+6);
                        else if(sel==2)
                           gotoxy(2*(RltP.x)+1,RltP.y+7);
                        else if(sel==3)
                           gotoxy(2*(RltP.x)+3,RltP.y+6);
                        printf("⊕");
                        
                        int ch;
                        ch=getch();
                        if(ch==0)
                           ch=getch();
                        switch(ch)
                        {
                           case 75:
                              if(sel>=2)
                                 sel--;
                              break;
                           case 77:
                              if(sel<=2)
                                 sel++;
                              break;
                           case 'X':
                           case 'x':
                                sx=1;
                              int b=0;
                              if((sel==1)&&(Map[AbsP.x-1][AbsP.y]==MT_Stone))
                              {
                                 Map[AbsP.x-1][AbsP.y]=MT_Air;
                                 StoneBreaker--;
                                 sMSG("Break Stone Successfully!");
                                 b=1;
                              }
                              if((sel==2)&&(Map[AbsP.x][AbsP.y+1]==MT_Stone))
                              {
                                 Map[AbsP.x][AbsP.y+1]=MT_Air;
                                 StoneBreaker--;
                                 sMSG("Break Stone Successfully!");
                                 b=1;
                              }
                              if((sel==3)&&(Map[AbsP.x+1][AbsP.y]==MT_Stone))
                              {
                                 Map[AbsP.x+1][AbsP.y]=MT_Air;
                                 StoneBreaker--;
                                 sMSG("Break Stone Successfully!");
                                 b=1;
                              }
                              if(b==0)
                                 sMSG("No Stone!!");
                              break;
                           
                        }
                        if(sx)
                           break;
                     }
                      
                  }
                  else
                     sMSG("No Stone to break!!");
               }
         } 
         
      }
      if(1)
      {
EmptyTime:
         RunTime++;
         //gotoxy(1,12);
         //printf("%d",RunTime);
         if(RunTime>=30-6*DownV)
         {
            
            if((Map[AbsP.x][AbsP.y+1]==MT_Air)||(Map[AbsP.x][AbsP.y+1]==MT_Sky))
            {
               if(WaterMap[AbsP.x][AbsP.y]>=60)
               {
                  DownV=2;
                  Acc=3-0.6*DownV;
               }
               else
               {
                  DownV+=Acc;
                  Acc=3-0.6*DownV;
               }
            }
            if(DownV<=1)
            {
               if((Map[AbsP.x][AbsP.y+1]==MT_Air)||(Map[AbsP.x][AbsP.y+1]==MT_Sky))
               {
                  AbsP.y+=(int)DownV;
                  RltP.y+=(int)DownV;
                  if(IsInArea(RltP)==0)
                     RltP.y-=(int)DownV;
               }
               else
                  DownV=0;
            }
            else
            {
               int mov=0;
               for(mov=1;mov<=DownV;mov++)
               {
                  if(kbhit())
                  {
                     int g=getch();
                     g=getch();
                     if(g==72)
                     {
                        DownV=0;
                        break;
                     }
                  }
                  if((Map[AbsP.x][AbsP.y+1]==MT_Air)||(Map[AbsP.x][AbsP.y+1]==MT_Sky))
                  {
                     AbsP.y++;
                     RltP.y++;
                     if(IsInArea(RltP)==0)
                        RltP.y-=1;
                  }
                  else
                  {
                     if(WaterMap[AbsP.x][AbsP.y]>=80)
                     {
                        if((DownV==1))
                           HP-=1;
                        if(DownV==2)
                           HP-=2;
                     }
                     else
                     {
                        if((DownV==3))
                           HP-=0;
                        if(DownV==4)
                           HP-=(11+(mov-1)*2);
                        if((DownV==6)&&(SET>=3))
                           HP-=20;
                        else if((DownV==6)&&(SET==2))
                           HP-=5;
                     }
                     DownV=0;
                  }
                  exsleep((int)(1));
                  gotoxy(1,6);
                  textbackground(7);
                  ShowMap(AbsP,RltP,aDD[DDL]);  
               }
            }
            RunTime=0;
         }
      }        
      gotoxy(1,6);
      textbackground(7);
      ShowMap(AbsP,RltP,aDD[DDL],MapTimer);  
   }
   textbackground(7);
   system("cls");
   //textcolor(2);
   textcolor(0);
   printf("You lose!");
   while(1)
      getch();
   return 0;
}
int GoShop()
{
   textbackground(7);
   system("cls");
   gotoxy(1,1);
   textbackground(1);
   textcolor(15);
   printf("Add your Oil\n");
   textbackground(7);
   textcolor(0);
   printf("Sell the stone\n");
   printf("UpGrade the equipment\n");
   printf("Fix\n");
   printf("Sepcial tool(s)\n");
   printf("Exit\n");
   printf("Press 'z' to Enter into.");
   int sel=1;
   int lx;
   while(1)
   {
      int Press;
      Press=getch();
      if(Press==0)
         Press=getch();
      switch(Press)
      {
         case 72:
            if(sel>=2)
               sel--;
            break;
         case 80:
            if(sel<=5)
               sel++;
            break;
         case 'z':
            if(sel==1)
               AddOil();
            else if(sel==2)
               Sell();
            else if(sel==3)
               UpGrade();
            else if(sel==4)
               Fix();
            else if(sel==5)
               SpecialTool();
            else
            {
               system("cls");
               return 0;
            }
      }
      textbackground(7);
      gotoxy(1,1);
      if(sel==1)
      {
         textbackground(1);
         textcolor(15);
         printf("Add your Oil\n");
         textbackground(7);
         textcolor(0);
         printf("Sell the stone\n");
         printf("UpGrade the equipment\n");
         printf("Fix\n");
         printf("Sepcial tool(s)\n");
         printf("Exit\n");
      }
      else if(sel==2)
      {
         printf("Add your Oil\n");
         textbackground(1);
         textcolor(15);
         printf("Sell the stone\n");
         textbackground(7);
         textcolor(0);
         printf("UpGrade the equipment\n");
         printf("Fix\n");
         printf("Sepcial tool(s)\n");
         printf("Exit\n");
      }
      else if(sel==3)
      {
         printf("Add your Oil\n");
         printf("Sell the stone\n");
         textbackground(1);
         textcolor(15);
         printf("UpGrade the equipment\n");
         textbackground(7);
         textcolor(0);
         printf("Fix\n");
         printf("Sepcial tool(s)\n");
         printf("Exit\n");
      }
      else if(sel==4)
      {
         printf("Add your Oil\n");
         printf("Sell the stone\n");
         printf("UpGrade the equipment\n");
         textbackground(1);
         textcolor(15);
         printf("Fix\n");
         textbackground(7);
         textcolor(0);
         printf("Sepcial tool(s)\n");
         printf("Exit\n");
      }
      else if(sel==5)
      {
         printf("Add your Oil\n");
         printf("Sell the stone\n");
         printf("UpGrade the equipment\n");
         printf("Fix\n");
         textbackground(1);
         textcolor(15);
         printf("Sepcial tool(s)\n");
         textbackground(7);
         textcolor(0);
         printf("Exit\n");
      }
      else if(sel==6)
      {
         printf("Add your Oil\n");
         printf("Sell the stone\n");
         printf("UpGrade the equipment\n");
         printf("Fix\n");
         printf("Sepcial tool(s)\n");
         textbackground(1);
         textcolor(15);
         printf("Exit\n");
         textbackground(7);
         textcolor(0);
      }
   }
   getch();
   system("cls");
}
int SpecialTool()
{
   int m;
   int ch=0; 
   system("cls");
   printf("How many StoneBreaker(2000$) do you want to buy? ");
   scanf("%d",&m);
   printf("Spend %d$ and buy %d stonebreaker(s)?(y/n)",2000*m,m);
   if((ch=='y')||(ch=='Y'))
   { 
      if(money>=2000*m)
      {  
         money-=2000*m ;
         StoneBreaker--; 
         printf("\n Buy successfully!"); 
      } 
      else
         printf("\nYou don't have enough money.");
   }
   exsleep(500);
   system("cls"); 
}
int Fix()
{
   if((mHP[HPL]==HP)&&(BreakCnt==0))
      return 0;
   system("cls");
   textbackground(1);
   textcolor(15);
   printf("Fix the HP.\n");
   textbackground(7);
   textcolor(0);
   printf("Fix the Backpack.\n");
   printf("Exit");
   
   int sel=1;
   while(1)
   {
      char c;
      c=getch();
      if(c==0)
         c=getch();
      if(c==72)
      {
         if(sel>=2)
            sel--;
      }
      else if(c==80)
      {
         if(sel<=2)
            sel++;
      }
      else if((c=='z')||(c=='Z'))
      {
         if((sel==1)&&(HP<mHP[HPL]))
         {
            system("cls");
            printf("Your HP=(%d/%d).If you want to fix, you have to pay %d$.(Y/N)",HP,mHP[HPL],2*(mHP[HPL]-HP));
            char c;
            c=getch();
            if((c=='y')||(c=='Y'))
            {
               money+=2*(HP-mHP[HPL]);
               HP=mHP[HPL];
               printf("Fix ok.");
               getch();
            }
            system("cls");
         }   
         else if((sel==2)&&(BreakCnt>0))
         {
            system("cls");
            printf("You have to pay 500$ for each break backpack.(%d break backpack)\n",BreakCnt);
            printf("How many backpack do you want to fix?  ");
            int k;
            while(1)
            {
               scanf("%d",&k);
               if((money>=k*500)&&(BreakCnt>=k))
                  break;
               printf("You don't have enough money or you fix so much! ");
               getch();
               gotoxy(1,3);
               printf("                                                 ");
               gotoxy(40,2);
            }
            money-=k*500;
            BreakCnt-=k;
            system("cls");
         }
         else if(sel==3)
         {
            system("cls");
            return 0;
         }
      }
      if(sel==1)
      {
         gotoxy(1,1);
         textbackground(1);
         textcolor(15);
         printf("Fix the HP.\n");
         textbackground(7);
         textcolor(0);
         printf("Fix the Backpack.\n");
         printf("Exit");
      }
      else if(sel==2)
      {
         gotoxy(1,1);
         printf("Fix the HP.\n");
         textbackground(1);
         textcolor(15);
         printf("Fix the Backpack.\n");
         textbackground(7);
         textcolor(0);
         printf("Exit");
      }
      else if(sel==3)
      {
         gotoxy(1,1);
         printf("Fix the HP.\n");
         printf("Fix the Backpack.\n");
         textbackground(1);
         textcolor(15);
         printf("Exit");
         textbackground(7);
         textcolor(0);
      }
   }
   
   system("cls");   
}
int AddOil()
{
   textbackground(7);
   system("cls");
   gotoxy(1,1);
   if(Oil==OB[OBL])
   {
      printf("You are so laippy><\n");
      exsleep(5000);
      gotoxy(1,1);
      printf("                     ");
      return 0;
   }
   textbackground(1);
   textcolor(15);
   printf("Add 25%(%d$)\n",(int)(OB[OBL]/4));
   textbackground(7);
   textcolor(0);
   printf("Add 50%(%d$)\n",(int)(OB[OBL]/2));
   printf("Add Until full(%d$)\n",(int)(OB[OBL]-Oil));
   printf("Exit\n");
   printf("Press 'z' to Enter into.");
   int sel=1;
   int lx;
   while(1)
   {
      if(Oil==OB[OBL])
         break;
      int Press;
      Press=getch();
      if(Press==0)
         Press=getch();
      switch(Press)
      {
         case 72:
            if(sel>=2)
               sel--;
            break;
         case 80:
            if(sel<=3)
               sel++;
            break;
         case 'z':
            if(sel==1)
            {
               if(money>=(int)(OB[OBL]/4))
               {
                  money-=(int)(OB[OBL]/4);
                  Oil=GetMin((int)(OB[OBL]/4)+Oil,OB[OBL]);
               }
               else
               {
                  gotoxy(2,7);
                  printf("You don't have enough money!");
               }
            }
            else if(sel==2)
            {
               if(money>=(int)(OB[OBL]/2))
               {
                  money-=(int)(OB[OBL]/2);
                  Oil=GetMin((int)(OB[OBL]/2)+Oil,OB[OBL]);
               }
               else
               {
                  gotoxy(2,7);
                  printf("You don't have enough money!");
               }
            }
            else if(sel==3)
            {
               if(money>=(int)(OB[OBL])-Oil)
               {
                  money-=(int)(OB[OBL])-Oil;
                  Oil=OB[OBL];
               }
               else
               {
                  gotoxy(2,7);
                  printf("You don't have enough money!");
               }
            }
            else
            {
               system("cls");
               return 0;
            }
      }
      textbackground(7);
      gotoxy(1,1);
      if(sel==1)
      {
         textbackground(1);
         textcolor(15);
         printf("Add 25%(%d$)\n",(int)(OB[OBL]/4));
         textbackground(7);
         textcolor(0);
         printf("Add 50%(%d$)\n",(int)(OB[OBL]/2));
         printf("Add Until full(%d$)\n",(int)(OB[OBL]-Oil));
         printf("Exit\n");
      }
      else if(sel==2)
      {
         printf("Add 25%(%d$)\n",(int)(OB[OBL]/4));
         textbackground(1);
         textcolor(15);
         printf("Add 50%(%d$)\n",(int)(OB[OBL]/2));
         textbackground(7);
         textcolor(0);
         printf("Add Until full(%d$)\n",(int)(OB[OBL]-Oil));
         printf("Exit\n");
      }
      else if(sel==3)
      {
         printf("Add 25%(%d$)\n",(int)(OB[OBL]/4));
         printf("Add 50%(%d$)\n",(int)(OB[OBL]/2));
         textbackground(1);
         textcolor(15);
         printf("Add Until full(%d$)\n",(int)(OB[OBL]-Oil));
         textbackground(7);
         textcolor(0);
         printf("Exit\n");
      }
      else if(sel==4)
      {
         printf("Add 25%(%d$)\n",(int)(OB[OBL]/4));
         printf("Add 50%(%d$)\n",(int)(OB[OBL]/2));
         printf("Add Until full(%d$)\n",(int)(OB[OBL]-Oil));
         textbackground(1);
         textcolor(15);
         printf("Exit\n");
         textbackground(7);
         textcolor(0);
      }
      
   }
   getch();
   system("cls");
}
int Sell()
{
   int lx;
   int m=0; 
   textbackground(7);
   system("cls");
   printf("Your backpack(%d/%d):\n",BackCnt,BP[BPL]);
   for(lx=0;lx<element_MAX;lx++)
   {
      if(strlen(ElementName[lx])>=8)
         printf("%s\t%d",ElementName[lx],Backpack[lx]);
      else
         printf("%s\t\t%d",ElementName[lx],Backpack[lx]);
      printf("\t%d$\n",Backpack[lx]*ElementPrice(lx));
      m+=Backpack[lx]*ElementPrice(lx); 
   }
   textbackground(1);
   textcolor(15);      
   printf("Sell all and get(%d$)\n",m);
   textbackground(7);
   textcolor(0);
   printf("Exit");
   int sel=1;   
   while(1)
   {
      int Press; 
      Press=getch();
      if(Press==0)
         Press=getch();
      switch(Press)
      {
         case 72:
            if(sel==2)
               sel=1;
            break;
         case 80:
            if(sel==1)
               sel=2;
            break;
         case 'z':
            if(sel==2)
            { 
               system("cls"); 
               return 0;
            }
            else
            {
               for(lx=0;lx<element_MAX;lx++)
                  Backpack[lx]=0;
               BackCnt=0;
               money+=m;  
               system("cls");
               gotoxy(1,1); 
               printf("Sell successfully!"); 
               getch();
               system("cls"); 
               return 0;  
            } 
      }
      if(sel==1) 
      {
         gotoxy(1,element_MAX+2);
         textbackground(1);
         textcolor(15);      
         printf("Sell all and get(%d$)\n",m);
         textbackground(7);
         textcolor(0);
         printf("Exit");
      }
      else
      {
         gotoxy(1,element_MAX+2);
         printf("Sell all and get(%d$)\n",m);
         textbackground(1);
         textcolor(15);
         printf("Exit"); 
         textbackground(7);
         textcolor(0); 
      } 
       
   } 
   getch();
   system("cls");
}
int UpGrade()
{
   int lx;
   textbackground(7);
   system("cls");
   printf("Here's your equipment(you have %d$):\n",money);
   textbackground(1);
   textcolor(15);      
   printf("Oil Box Level:    ");
   for(lx=1;lx<=OBL;lx++)
      printf("●");
   for(lx=OBL+1;lx<=6;lx++)
      printf("○");
   printf("\n");
   textbackground(7);
   textcolor(0);
   printf("Fan Fly Level:    ");
   for(lx=1;lx<=FRSL;lx++)
      printf("●");
   for(lx=FRSL+1;lx<=6;lx++)
      printf("○");
   printf("\n");
   
   printf("Back Pack Level:  ");
   for(lx=1;lx<=BPL;lx++)
      printf("●");
   for(lx=BPL+1;lx<=6;lx++)
      printf("○");
   printf("\n");
   
   printf("Detect Level:     ");
   for(lx=1;lx<=DDL;lx++)
      printf("●");
   for(lx=DDL+1;lx<=6;lx++)
      printf("○");
   printf("\n");
   
   printf("Drill Sharp Level:");
   for(lx=1;lx<=DSL;lx++)
      printf("●");
   for(lx=DSL+1;lx<=6;lx++)
      printf("○");
   printf("\n");
   
   printf("HP Level:         ");
   for(lx=1;lx<=HPL;lx++)
      printf("●");
   for(lx=HPL+1;lx<=6;lx++)
      printf("○");
   printf("\n");
   printf("Exit\n");
   printf("Press z to Enter.\n");
   int sel=1;
   while(1)
   {
      int Press;
      Press=getch();
      if(Press==0)
         Press=getch();
      switch(Press)
      {
         case 72:
            if(sel>=2)
               sel--;
            break;
         case 80:
            if(sel<=6)
               sel++;
            break;
         case 'z':
            switch(sel)
            {
               case 1:
                  if(OBL==6)
                  {
                     gotoxy(1,12);
                     printf("You are so laippy!!       ");;
                     break;
                  }
                  if(money>=UpGradeMoney[OBL])
                  {
                     money-=UpGradeMoney[OBL];
                     OBL++;
                     Oil=(int)(Oil*OB[OBL]/OB[OBL-1]);
                     gotoxy(1,12);
                     printf("UpGrade successfully!");
                     
                  }
                  else
                  {
                     gotoxy(1,12);
                     printf("You need %d$!",UpGradeMoney[OBL]);
                  }
                  break;
               case 2:
                  if(FRSL==6)
                  {
                     gotoxy(1,12);
                     printf("You are so laippy!!        ");;
                     break;
                  }
                  if(money>=UpGradeMoney[FRSL])
                  {
                     money-=UpGradeMoney[FRSL];
                     FRSL++;
                     //Oil=(int)(Oil*UpGradeMoney[FRSL]/UpGradeMoney[FRSL-1]);
                     gotoxy(1,12);
                     printf("UpGrade successfully!");
                     
                  }
                  else
                  {
                     gotoxy(1,12);
                     printf("You need %d$!",UpGradeMoney[FRSL]);
                  }
                  break;
               case 3:
                  if(BPL==6)
                  {
                     gotoxy(1,12);
                     printf("You are so laippy!!         ");;
                     break;
                  }
                  if(money>=UpGradeMoney[BPL])
                  {
                     money-=UpGradeMoney[BPL];
                     BPL++;
                    // Oil=(int)(Oil*UpGradeMoney[BPL]/UpGradeMoney[BPL-1]);
                     gotoxy(1,12);
                     printf("UpGrade successfully!");
                     
                  }
                  else
                  {
                     gotoxy(1,12);
                     printf("You need %d$!",UpGradeMoney[BPL]);
                  }
                  break;
               case 4:
                  if(DDL==6)
                  {
                     gotoxy(1,12);
                     printf("You are so laippy!!         ");;
                     break;
                  }
                  if(money>=UpGradeMoney[DDL])
                  {
                     money-=UpGradeMoney[DDL];
                     DDL++;
                    // Oil=(int)(Oil*UpGradeMoney[BPL]/UpGradeMoney[BPL-1]);
                     gotoxy(1,12);
                     printf("UpGrade successfully!");
                     
                  }
                  else
                  {
                     gotoxy(1,12);
                     printf("You need %d$!",UpGradeMoney[DDL]);
                  }
                  break;
                  break;
               case 5:
                  if(DSL==6)
                  {
                     gotoxy(1,12);
                     printf("You are so laippy!!         ");;
                     break;
                  }
                  if(money>=UpGradeMoney[DSL])
                  {
                     money-=UpGradeMoney[DSL];
                     DSL++;
                    // Oil=(int)(Oil*UpGradeMoney[BPL]/UpGradeMoney[BPL-1]);
                     gotoxy(1,12);
                     printf("UpGrade successfully!");
                     
                  }
                  else
                  {
                     gotoxy(1,12);
                     printf("You need %d$!",UpGradeMoney[DSL]);
                  }
                  break;
               case 6:
                  if(HPL==6)
                  {
                     gotoxy(1,12);
                     printf("You are so laippy!!         ");;
                     break;
                  }
                  if(money>=UpGradeMoney[HPL])
                  {
                     money-=UpGradeMoney[HPL];
                     HPL++;
                    // Oil=(int)(Oil*UpGradeMoney[BPL]/UpGradeMoney[BPL-1]);
                     HP=(int)(HP*mHP[HPL]/mHP[HPL-1]);
                     gotoxy(1,12);
                     printf("UpGrade successfully!");
                     
                  }
                  else
                  {
                     gotoxy(1,12);
                     printf("You need %d$!",UpGradeMoney[HPL]);
                  }
                  break;
                  break;
               case 7:
                  system("cls");
                  return 0;
                  break;
                  
            }
      }
      switch(sel)
      {
         case 1:
            gotoxy(1,2);
            textbackground(1);
            textcolor(15);      
            printf("Oil Box Level:    ");
            for(lx=1;lx<=OBL;lx++)
               printf("●");
            for(lx=OBL+1;lx<=6;lx++)
               printf("○");
            printf("\n");
            textbackground(7);
            textcolor(0);
            printf("Fan Fly Level:    ");
            for(lx=1;lx<=FRSL;lx++)
               printf("●");
            for(lx=FRSL+1;lx<=6;lx++)
               printf("○");
            printf("\n");
            break;
         case 2:
            gotoxy(1,2);    
            textbackground(7);
            textcolor(0);
            printf("Oil Box Level:    ");
            for(lx=1;lx<=OBL;lx++)
               printf("●");
            for(lx=OBL+1;lx<=6;lx++)
               printf("○");
            printf("\n");
            textbackground(1);
            textcolor(15);  
            printf("Fan Fly Level:    ");
            for(lx=1;lx<=FRSL;lx++)
               printf("●");
            for(lx=FRSL+1;lx<=6;lx++)
               printf("○");
            textbackground(7);
            textcolor(0);
            printf("\n");
            printf("Back Pack Level:  ");
            for(lx=1;lx<=BPL;lx++)
               printf("●");
            for(lx=BPL+1;lx<=6;lx++)
               printf("○");
            printf("\n");
            break;
         case 3:
            gotoxy(1,3);    
            textbackground(7);
            textcolor(0);  
            printf("Fan Fly Level:    ");
            for(lx=1;lx<=FRSL;lx++)
               printf("●");
            for(lx=FRSL+1;lx<=6;lx++)
               printf("○");
            textbackground(1);
            textcolor(15);
            printf("\n");
            printf("Back Pack Level:  ");
            for(lx=1;lx<=BPL;lx++)
               printf("●");
            for(lx=BPL+1;lx<=6;lx++)
               printf("○");
            printf("\n");
            textbackground(7);
            textcolor(0);
            
            printf("Detect Level:     ");
            for(lx=1;lx<=DDL;lx++)
               printf("●");
            for(lx=DDL+1;lx<=6;lx++)
               printf("○");
            printf("\n");
            break;
         case 4:
            gotoxy(1,4);    
            textbackground(7);
            textcolor(0);
            printf("Back Pack Level:  ");
            for(lx=1;lx<=BPL;lx++)
               printf("●");
            for(lx=BPL+1;lx<=6;lx++)
               printf("○");
            printf("\n");
            textbackground(1);
            textcolor(15);
            printf("Detect Level:     ");
            for(lx=1;lx<=DDL;lx++)
               printf("●");
            for(lx=DDL+1;lx<=6;lx++)
               printf("○");
            printf("\n");
            textbackground(7);
            textcolor(0);
            printf("Drill Sharp Level:");
            for(lx=1;lx<=DSL;lx++)
               printf("●");
            for(lx=DSL+1;lx<=6;lx++)
               printf("○");
            printf("\n");
            break;
         case 5:
            gotoxy(1,5); 
            textbackground(7);
            textcolor(0);
            printf("Detect Level:     ");
            for(lx=1;lx<=DDL;lx++)
               printf("●");
            for(lx=DDL+1;lx<=6;lx++)
               printf("○");
            textbackground(1);
            textcolor(15);
            printf("\n");
            printf("Drill Sharp Level:");
            for(lx=1;lx<=DSL;lx++)
               printf("●");
            for(lx=DSL+1;lx<=6;lx++)
               printf("○");
            printf("\n");
            textbackground(7);
            textcolor(0);
            printf("HP Level:         ");
            for(lx=1;lx<=HPL;lx++)
               printf("●");
            for(lx=HPL+1;lx<=6;lx++)
               printf("○");
            printf("\n");
            break;
         case 6:
            gotoxy(1,6); 
            textbackground(7);
            textcolor(0);
            printf("Drill Sharp Level:");
            for(lx=1;lx<=DSL;lx++)
               printf("●");
            for(lx=DSL+1;lx<=6;lx++)
               printf("○");
            printf("\n");
            textbackground(1);
            textcolor(15);
            printf("HP Level:         ");
            for(lx=1;lx<=HPL;lx++)
               printf("●");
            for(lx=HPL+1;lx<=6;lx++)
               printf("○");
            textbackground(7);
            textcolor(0);
            printf("\n");
            printf("Exit\n");
            break;
         case 7:
            gotoxy(1,7); 
            textbackground(7);
            textcolor(0);
            printf("HP Level:         ");
            for(lx=1;lx<=HPL;lx++)
               printf("●");
            for(lx=HPL+1;lx<=6;lx++)
               printf("○");
            
            textbackground(1);
            textcolor(15);
            printf("\n");
            printf("Exit\n");
            
            textbackground(7);
            textcolor(0);
            break;
            
      }
   }
   
   getch();
}

int sMSG(s)
char s[50];
{
   gotoxy(4,18);
   printf("                                 ");
   gotoxy(4,18);
   printf("%s",s);
   exsleep(500);
}
int CntDelay(n)
int n;
{
   int i=0; 
   int lx; 
   if(n==0)
      return 1;
   while(1)
   {
      //ungetch(10);
      gotoxy(4,18); 
      i++;
      exsleep(1);
      OilTime+=1; 
      if(i==n)
         break;
      printf("Progress:"); 
      for(lx=1;lx<=10;lx++)
      {
         if((lx*10)<=(int)(i*100/n))
            printf("●");
         else
            printf("○");
      }
      printf("\n");
   }    
   gotoxy(4,18); 
   printf("                                 \n"); 
   gotoxy(0,4);
   return 0; 
} 
int IsInArea(p)
struct point p;
{
   if(((p.x>=2)&&(p.x<=8))&&((p.y>=2)&&(p.y<=8)))
      return 1;
   else
      return 0;
}
int Rnd(int a,int p)
{
   return a-p+(rand()%(2*p));
}
int ShowMSG(msg)
char msg[100];
{
   MessageBox(0,msg, "Treasure 3.0",
         MB_ICONEXCLAMATION | MB_OK | MB_SYSTEMMODAL);
}
