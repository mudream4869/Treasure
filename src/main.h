#include<time.h>
#include<stdlib.h>
#include<stdio.h>
#include<windows.h>
#include<math.h>
#include<conio.h>
//#include<conio2.h>
struct point 
{
   int x;
   int y;
};
char acfile[10]=".sav";
//Element
int SecTime=500;
enum Element
{
   element_Fe=0,
   element_Cu=1,
   element_Ag=2,
   element_Au=3,
   element_Pt=4,
   element_Cordierite=5,
   element_Nephrite,
   element_Ruby,
   element_Sapphire,
   element_Emerald,
   element_Ruber,
   element_MAX, 
};
char ElementName[element_MAX][15];

enum MapType
{
   MT_element_Fe=0,
   MT_element_Cu,
   MT_element_Ag,
   MT_element_Au,
   MT_element_Pt,
   MT_element_Cordierite,
   MT_element_Nephrite,
   MT_element_Ruby,
   MT_element_Sapphire=8,
   MT_element_Emerald=9,
   MT_element_Ruber=10,
   MT_element_MAX=11,
   MT_Soil=13,
   MT_Air=15,
   MT_Stone=17,
   MT_Fire=19,
   //Special  V
   MT_MoneyI=21,  
   MT_MoneyII=23,
   MT_MoneyIII=25,
   //System Set
   MT_Store=27,
   MT_SavePoint=29,
   MT_Sky=30,
};
struct Wwater
{
   char s[1];
   int a;
};
struct Wwater water[13];
struct ES
{
   char chr[1];
   int color;
};
struct ES ElementStyle[element_MAX]; 
//Map

int Map[21][2000];
int WaterMap[21][2000];
int InitialWater(Timer)
int Timer;
{
   int lx;
   int ly;
   int skip=0;
   int Temp=0;
   for(ly=251;ly<=1000;ly++)
   {
      Temp=(int)(20*sqrt(sqrt(10+abs(ly-3))));
      for(lx=1;lx<=20;lx++)
      {
         //printf("%d,%d,%d\n",lx,ly,WaterMap[lx][ly]);
         if((Temp>=101)&&(10*Timer>=9*SecTime))
         {
            if(WaterMap[lx][ly]>=4)
               WaterMap[lx][ly]-=4;
            else
               WaterMap[lx][ly]=0;
         }
         if(Map[lx][ly]==MT_Soil)
            skip=0;
         if(WaterMap[lx][ly]>=1)
         {
            if((Map[lx][ly+1]==MT_Air)&&(WaterMap[lx][ly+1]<100))
            {
               if(WaterMap[lx][ly+1]==0)
               {
                  WaterMap[lx][ly+1]=WaterMap[lx][ly];
                  WaterMap[lx][ly]=0;
               }
               else if((100-WaterMap[lx][ly+1])>=WaterMap[lx][ly])
               {
                  WaterMap[lx][ly+1]+=WaterMap[lx][ly];
                  WaterMap[lx][ly]=0;
               }
               else
               {
                  WaterMap[lx][ly]-=100-WaterMap[lx][ly+1];
                  WaterMap[lx][ly+1]=100;
               }
            }
            else
            {
               if(skip>=1)
               {
                  skip--;
                  continue;
               }
               int Right=0;
               int Left=0;
               if(lx<=19)
               {
                  if(Map[lx+1][ly]==MT_Air)
                  {
                     Right=1;
                     while(1)
                     {
                        //printf("R%d",Right);
                        if((Map[lx+Right][ly]==MT_Air))
                        {
                           Right++;
                           //if(Map[lx+Right+1][ly+1]==MT_Air)
                             // break;
                        }
                        else
                        
                           break;
                        if(lx+Right>=20)
                           break;
                     }
                     Right--;
                  }
               }
               //printf("\n");
               if(lx>=2)
               {
                  if(Map[lx-1][ly]==MT_Air)
                  {
                     Left=1;
                     while(1)
                     {
                        //printf("L%d",Left);
                        if((Map[lx-Left][ly]==MT_Air))
                        {
                           Left++;
                           //if(Map[lx-Left-1][ly+1]==MT_Air)
                             // break;
                        }
                        else
                           break;
                        if(lx>=Left)
                           break;
                     }
                     Left--;
                  }
               }
               //printf("\n");
               if(Left+Right>=1)
               {
                  int g=0;
                  int l;
                  for(l=1;l<=Left;l++)
                     g+=WaterMap[lx-l][ly];
                  for(l=1;l<=Right;l++)
                     g+=WaterMap[lx+l][ly];
                  g+=WaterMap[lx][ly];
                  //g=WaterMap[lx][ly];
                  int w=(int)(g/(Left+Right+1));
                  
                  if(w*(Left+Right+1)<WaterMap[lx][ly])
                     WaterMap[lx][ly]-=w*(Left+Right);
                  else
                     WaterMap[lx][ly]=w;
                  for(l=1;l<=Left;l++)
                     WaterMap[lx-l][ly]=w;
                  for(l=1;l<=Right;l++)
                     WaterMap[lx+l][ly]=w;
                  skip=Right+1;
               }      
            }      
         }
      }
   }
}
int InitialMap()
{
   int lx,ly;
   srand(time(NULL));
   for(ly=1;ly<=2000;ly++)
   {
      for(lx=1;lx<=20;lx++)
         WaterMap[lx][ly]=0;
   }
   for(ly=1;ly<=3;ly++)
   {
      for(lx=1;lx<=20;lx++)
         Map[lx][ly]=MT_Sky;
   }
   //return 0;
   Map[9][1]=MT_Stone;
   Map[11][1]=MT_Stone;
   Map[9][3]=MT_Stone;
   Map[11][3]=MT_Stone;
   Map[10][1]=MT_SavePoint;
   Map[10][3]=MT_Store;
   //0~400 		(Fe Cu) 3/4 Ag 1/4    20sec
   
   for(ly=4;ly<=100;ly++)
   {
      for(lx=1;lx<=20;lx++)
      {
         if(ThrowDise(9,100))
         {
            if(ThrowDise(12,16))
            {
               if(ThrowDise(10,20))
                  Map[lx][ly]=MT_element_Fe;
               else
                  Map[lx][ly]=MT_element_Cu;
            }
            else
                Map[lx][ly]=MT_element_Ag;
         }
         else
         {
            if(ThrowDise(1,10))
               Map[lx][ly]=MT_Air;
            else
               Map[lx][ly]=MT_Soil;
         }  
      }
   }
   //400~1000 	((Fe Cu)3/4 Ag1/4)2/3 (Au Pt)1/2	 
   for(ly=101;ly<=250;ly++)
   {
      for(lx=1;lx<=20;lx++)
      {
         if(ThrowDise(8,100))
         {
            if(ThrowDise(4,12))
            {
               if(ThrowDise(10,20))
                  Map[lx][ly]=MT_element_Au;
               else
                  Map[lx][ly]=MT_element_Pt;
            }
            else
            {
               if(ThrowDise(12,16))
               {
                  if(ThrowDise(10,20))
                     Map[lx][ly]=MT_element_Fe;
                  else
                     Map[lx][ly]=MT_element_Cu;
               }
               else
                   Map[lx][ly]=MT_element_Ag;
            }
         }
         else
         {
            if(ThrowDise(1,10))
               Map[lx][ly]=MT_Air;
            else
            {
               if(ThrowDise(10,150))
                  Map[lx][ly]=MT_element_Ruber;
               else
                  Map[lx][ly]=MT_Soil;
            }
         }  
      }
   }
   //return 0;
   //1000~1500 	((Fe Cu) Ag Au Pt  [Cordierite]
   for(ly=251;ly<=375;ly++)
   {
      for(lx=1;lx<=20;lx++)
      {
         if(ThrowDise(8,100))
         {
            if(ThrowDise(4,12))
            {
               if(ThrowDise(10,20))
                  Map[lx][ly]=MT_element_Au;
               else
                  Map[lx][ly]=MT_element_Pt;
            }
            else
            {
               if(ThrowDise(12,16))
               {
                  if(ThrowDise(10,20))
                     Map[lx][ly]=MT_element_Fe;
                  else
                     Map[lx][ly]=MT_element_Cu;
               }
               else
                   Map[lx][ly]=MT_element_Ag;
            }
         }
         else
         {
            if(ThrowDise(10,910))
            {
               if(ThrowDise(15,1000))
                  Map[lx][ly]=MT_element_Cordierite;
               else
                  Map[lx][ly]=MT_Stone;
            }
            else
            {
               if(ThrowDise(1,10))
               {
                  Map[lx][ly]=MT_Air;
                  if(ThrowDise(1,10))
                     WaterMap[lx][ly]=100;
               }
               else
                  Map[lx][ly]=MT_Soil;
            }
         }  
      }
   }
   //1500~2000 	Fe Cu Ag Au Pt  [Cordierite Nephrite]	
   for(ly=376;ly<=500;ly++)
   {
      for(lx=1;lx<=20;lx++)
      {
         if(ThrowDise(8,100))
         {
            if(ThrowDise(4,12))
            {
               if(ThrowDise(10,20))
                  Map[lx][ly]=MT_element_Au;
               else
                  Map[lx][ly]=MT_element_Pt;
            }
            else
            {
               if(ThrowDise(12,16))
               {
                  if(ThrowDise(10,20))
                  {
                     if(ThrowDise(1,100))
                        Map[lx][ly]=MT_MoneyI;
                     else
                        Map[lx][ly]=MT_element_Fe;
                  }
                  else
                     Map[lx][ly]=MT_element_Cu;
               }
               else
                   Map[lx][ly]=MT_element_Ag;
            }
         }
         else
         {
            if(ThrowDise(10,910))
            {
               if(ThrowDise(20,1000))
               {               
                  if(ThrowDise(10,20))
                     Map[lx][ly]=MT_element_Cordierite;
                  else
                     Map[lx][ly]=MT_element_Nephrite;
               }
               else
                  Map[lx][ly]=MT_Stone;
            }
            else
            {
               if(ThrowDise(1,10))
               {
                  Map[lx][ly]=MT_Air;
                  if(ThrowDise(1,10))
                     WaterMap[lx][ly]=100;
               }
               else
               {
                  if(ThrowDise(10,150))
                     Map[lx][ly]=MT_element_Ruber;
                  else
                     Map[lx][ly]=MT_Soil;
               }
            }
         }  
      }
   }
   //2000~2252 	Fe Cu Ag Au Pt  [Cordierite Nephrite Ruby]
   for(ly=501;ly<=563;ly++)
   {
      for(lx=1;lx<=20;lx++)
      {
         if(ThrowDise(8,100))
         {
            if(ThrowDise(4,12))
            {
               if(ThrowDise(10,20))
                  Map[lx][ly]=MT_element_Au;
               else
                  Map[lx][ly]=MT_element_Pt;
            }
            else
            {
               if(ThrowDise(12,16))
               {
                  if(ThrowDise(10,20))
                  {
                     if(ThrowDise(1,30))
                        Map[lx][ly]=MT_MoneyI;
                     else
                        Map[lx][ly]=MT_element_Fe;
                  }
                  else
                     Map[lx][ly]=MT_element_Cu;
               }
               else
                   Map[lx][ly]=MT_element_Ag;
            }
         }
         else
         {
            if(ThrowDise(10,910))
            {
               if(ThrowDise(30,1000))
               {               
                  if(ThrowDise(10,40))
                     Map[lx][ly]=MT_element_Ruby;
                  else
                  {
                     if(ThrowDise(10,20))
                        Map[lx][ly]=MT_element_Cordierite;
                     else
                        Map[lx][ly]=MT_element_Nephrite;
                  }
               }
               else
                  Map[lx][ly]=MT_Stone;
            }
            else
            {
               if(ThrowDise(1,10))
               {
                  Map[lx][ly]=MT_Air;
                  if(ThrowDise(1,10))
                     WaterMap[lx][ly]=100;
               }
               else
                  Map[lx][ly]=MT_Soil;
            }
         }  
      }
   }
   //return 0;
   //2250~4000 	Fe Cu Ag Au Pt  [Cordierite Nephrite Ruby Emerald]
   for(ly=564;ly<=1000;ly++)
   {
      for(lx=1;lx<=20;lx++)
      {
         if(ThrowDise(8,100))
         {
            if(ThrowDise(4,12))
            {
               if(ThrowDise(10,20))
                  Map[lx][ly]=MT_element_Au;
               else
                  Map[lx][ly]=MT_element_Pt;
            }
            else
            {
               if(ThrowDise(12,16))
               {
                  if(ThrowDise(10,20))
                  {
                     if(ThrowDise(1,30))
                     {
                        if(ThrowDise(2,3))
                           Map[lx][ly]=MT_MoneyI;
                        else
                           Map[lx][ly]=MT_MoneyII;
                     }
                     else
                        Map[lx][ly]=MT_element_Fe;
                  }
                  else
                     Map[lx][ly]=MT_element_Cu;
               }
               else
                   Map[lx][ly]=MT_element_Ag;
            }
         }
         else
         {
            if(ThrowDise(10+ly/28,910))
            {
               if(ThrowDise((ly-300)/2,500))
               {               
                  if(ThrowDise(30,40))
                  {
                     if(ThrowDise(10,40))
                        Map[lx][ly]=MT_element_Ruby;
                     else
                     {
                        if(ThrowDise(10,20))
                           Map[lx][ly]=MT_element_Cordierite;
                        else
                           Map[lx][ly]=MT_element_Nephrite;
                     }
                  }
                  else
                  {
                     Map[lx][ly]=MT_element_Emerald;
                  }
               }
               else
               {
                  Map[lx][ly]=MT_Stone;
                  if(ThrowDise(1,10))
                     Map[lx][ly]=MT_Fire;
               }
            }
            else
            {
               if(ThrowDise(1,10))
               {
                  Map[lx][ly]=MT_Air;
                  if(ThrowDise(1,10))
                     WaterMap[lx][ly]=100;
               }
               else
                  Map[lx][ly]=MT_Soil;
            }
         }  
      }
   }
   //return 0;
   //4000~7000 	Fe Cu Ag Au Pt  [Cordierite Nephrite Ruby Emerald Sapphire]
   for(ly=1001;ly<=1750;ly++)
   {
      for(lx=1;lx<=20;lx++)
      {
         if(ThrowDise(8,100))
         {
            if(ThrowDise(4,12))
            {
               if(ThrowDise(10,20))
                  Map[lx][ly]=MT_element_Au;
               else
                  Map[lx][ly]=MT_element_Pt;
            }
            else
            {
               if(ThrowDise(12,16))
               {
                  if(ThrowDise(10,20))
                  {
                     if(ThrowDise(1,100))
                     {
                        if(ThrowDise(1,3))
                           Map[lx][ly]=MT_MoneyI;
                        else if(ThrowDise(1,2))
                           Map[lx][ly]=MT_MoneyII;
                        else
                           Map[lx][ly]=MT_MoneyIII;
                     }
                     else
                        Map[lx][ly]=MT_element_Fe;
                  }
                  else
                     Map[lx][ly]=MT_element_Cu;
               }
               else
                   Map[lx][ly]=MT_element_Ag;
            }
         }
         else
         {
            if(ThrowDise(10,910))
            {
               if(ThrowDise((ly-490)*2,1000))
               {               
                  if(ThrowDise(30,40))
                  {
                     if(ThrowDise(10,40))
                        Map[lx][ly]=MT_element_Ruby;
                     else
                     {
                        if(ThrowDise(10,20))
                           Map[lx][ly]=MT_element_Cordierite;
                        else
                           Map[lx][ly]=MT_element_Nephrite;
                     }
                  }
                  else
                  {
                     if(ThrowDise(10,20))
                        Map[lx][ly]=MT_element_Emerald;
                     else
                        Map[lx][ly]=MT_element_Sapphire;
                  }
               }
               else
               {
                  Map[lx][ly]=MT_Stone;
                  if(ThrowDise((int)(sqrt(10000*ly/750)),100))
                     Map[lx][ly]=MT_Fire;
               }
            }
            else
            {
               if(ThrowDise(1,10))
                  Map[lx][ly]=MT_Air;
               else
                  Map[lx][ly]=MT_Soil;
            }
         }  
      }
   }    
}
/*
MT_Soil:
MT_Air:
MT_Stone:
MT_Fire:
MT_MoneyI:
MT_MoneyII:
MT_MoneyIII:
MT_Store:
MT_SavePoint:
MT_Sky:
*/
int ShowMap(AbsP,RltP,DD,Timer)
struct point AbsP;
struct point RltP; 
int DD;
int Timer;
{
   int lx,ly;
   //textbackground(15);
   for(ly=AbsP.y-RltP.y;ly<=AbsP.y-RltP.y+10;ly++)
   {
      if((ly<=0)||(ly>1750))
      {
         textbackground(7);
         printf("                      \n");
         continue;
      } 
      for(lx=AbsP.x-RltP.x;lx<=AbsP.x-RltP.x+10;lx++)
      {
         //printf("%d",GetDistance(lx,ly,AbsP.x,AbsP.y));
         if((lx<=0)||(lx>=21))
         { 
            textbackground(7); 
            printf("  "); 
            textbackground(6);
            continue;
         }
         if(GetDistance(lx,ly,AbsP.x,AbsP.y)<=DD)
         {   
            if((lx==AbsP.x)&&(ly==AbsP.y))
            {
               if(ly<=3)
               {
                  textbackground(9);
                  textcolor(15);
               } 
               else
               {
                  if(WaterMap[lx][ly]>=80)
                  {
                     textbackground(9);
                     textcolor(15);
                  }
                  else
                  {
                     textbackground(15);
                     textcolor(1);
                  } 
               }
               //textcolor(1);
               printf("£K");
               textcolor(0);
               continue;
            }
            if (Map[lx][ly]<MT_element_MAX)
            {
               textbackground(6);
               textcolor(ElementStyle[Map[lx][ly]].color);
               printf("%s",ElementStyle[Map[lx][ly]].chr);
               textbackground(6);
               textcolor(0);
            }
            else if(Map[lx][ly]>MT_element_MAX)
            {
               switch(Map[lx][ly])
               {
                  case MT_Soil:
                     textbackground(6);
                     printf("  ");
                     break;
                  case MT_Air:
                     textbackground(15);
                     if(WaterMap[lx][ly]>=1)
                     {
                        textcolor(9);
                        if(2*Timer>=SecTime)
                        {
                           if(WaterMap[lx][ly]>=101)
                              printf("%d",(int)(WaterMap[lx][ly]/10));
                           else
                              printf("%s",water[(int)(WaterMap[lx][ly]/10)].s);
                        }
                        else
                        {
                           printf("%s",water[GetMax(0,((int)(WaterMap[lx][ly]/10)-1))].s);
                        }
                     }
                     else
                        printf("  ");
                     break;
                  case MT_Stone:
                     if(ly<=3)
                     {
                        textbackground(9);
                        textcolor(15);
                        printf("¡ó");
                        textcolor(0);
                     }
                     else
                     {
                        textbackground(6);
                        textcolor(9);
                        printf("¡ó");
                        textcolor(0);
                     }
                     textbackground(6);
                     break;
                  case MT_MoneyI:
                     textcolor(15);
                     printf("¡ð");
                     textcolor(0);
                     break;
                  case MT_MoneyII:
                     textcolor(15);
                     printf("£Z");
                     textcolor(0);
                     break;
                  case MT_MoneyIII:
                     textcolor(15);
                     printf("£S");
                     textcolor(0);
                     break;
                  case MT_Store:
                     textbackground(9);
                     textcolor(15);
                     printf("£[");
                     textcolor(0);
                     textbackground(6);
                     break;
                  case MT_SavePoint:
                     textbackground(9);
                     textcolor(15);
                     printf("£G");
                     textcolor(0);
                     textbackground(6);
                     break;
                  case MT_Sky:
                     textbackground(9);
                     textcolor(0);
                     printf("  ");
                     break;
                  case MT_Fire:
                     textcolor(4);
                     if(3*Timer<=SecTime)
                        printf("¡³"); 
                     else if((3*Timer>SecTime)&&(3*Timer<=2*SecTime))
                        printf("¡ó");
                     else
                        printf("¡´");
                     textcolor(0);
                     break;
                  
               }   
            }
         }
         else
         {
            if((lx<=0)||(lx>=21))
            { 
               textbackground(7); 
               printf("  "); 
               textbackground(6);
               continue;
            }
            
            if (Map[lx][ly]<MT_element_MAX)
            {
               textbackground(6);
               textcolor(0);
               //textcolor(ElementStyle[Map[lx][ly]].color);
               printf("%s",ElementStyle[Map[lx][ly]].chr);
               textbackground(6);
               textcolor(0);
            }
            else if(Map[lx][ly]>MT_element_MAX)
            {
               switch(Map[lx][ly])
               {
                  case MT_Soil:
                     textbackground(6);
                     printf("  ");
                     break;
                  case MT_Air:
                     textbackground(15);
                     if(WaterMap[lx][ly]>=1)
                     {
                        textcolor(9);
                        if(2*Timer>=SecTime)
                        {
                           if(WaterMap[lx][ly]>=101)
                              printf("%d",(int)(WaterMap[lx][ly]/10));
                           else
                              printf("%s",water[(int)(WaterMap[lx][ly]/10)].s);
                        }
                        else
                        {
                           printf("%s",water[GetMax(0,((int)(WaterMap[lx][ly]/10)-1))].s);
                        }
                     }
                     else
                        printf("  ");
                     textcolor(0);
                     break;
                  case MT_Stone:
                     if(ly<=3)
                     {
                        textbackground(9);
                        textcolor(15);
                        printf("¡ó");
                        textcolor(0);
                     }
                     else
                     {
                        textbackground(6);
                        textcolor(9);
                        printf("¡ó");
                        textcolor(0);
                     }
                     textbackground(6);
                     break;
                  case MT_MoneyI:
                     textcolor(15);
                     printf("¡ð");
                     textcolor(0);
                     break;
                  case MT_MoneyII:
                     textcolor(15);
                     printf("£Z");
                     textcolor(0);
                     break;
                  case MT_MoneyIII:
                     textcolor(15);
                     printf("£S");
                     textcolor(0);
                     break;
                  case MT_Store:
                     textbackground(9);
                     textcolor(15);
                     printf("£[");
                     textcolor(0);
                     textbackground(6);
                     break;
                  case MT_SavePoint:
                     textbackground(9);
                     textcolor(15);
                     printf("£G");
                     textcolor(0);
                     textbackground(6);
                     break;
                  case MT_Sky:
                     textbackground(9);
                     textcolor(0);
                     printf("  ");
                     break;
                  case MT_Fire:
                     textcolor(4);
                     if(3*Timer<=SecTime)
                        printf("¡³"); 
                     else if((3*Timer>SecTime)&&(3*Timer<=2*SecTime))
                        printf("¡ó");
                     else
                        printf("¡´");
                     textcolor(0);
                     break;
               }   
            }
         }
      }
      printf("\n");
   }
   return 0;
}
int ReMap()
{
   int HAVEDO[21][2000];
   int lx;
   int ly;
   for(ly=1;ly<=2000;ly++)
   {
      for(lx=1;lx<=20;lx++)
         HAVEDO[lx][ly]=0;
   }
   srand(time(NULL));
   //return 0;
   //0~400 		(Fe Cu) 3/4 Ag 1/4    20sec
   
   for(ly=4;ly<=100;ly++)
   {
      for(lx=1;lx<=20;lx++)
      {
         if(ThrowDise(1,3))
            continue; 
         if(HAVEDO[lx][ly]==1)
            continue;
         if(ThrowDise(1,2))
         {
            if(lx<=19)
            {
               int temp;
               temp=Map[lx][ly];
               Map[lx][ly]=Map[lx+1][ly];
               Map[lx][ly]=temp;
               HAVEDO[lx+1][ly]=1;
               continue; 
            } 
         } 
         if(ThrowDise(9,100))
         {
            if(ThrowDise(12,16))
            {
               if(ThrowDise(10,20))
                  Map[lx][ly]=MT_element_Fe;
               else
                  Map[lx][ly]=MT_element_Cu;
            }
            else
                Map[lx][ly]=MT_element_Ag;
         }
         else
         {
            if(ThrowDise(1,10))
               Map[lx][ly]=MT_Air;
            else
               Map[lx][ly]=MT_Soil;
         }  
      }
   }
   //400~1000 	((Fe Cu)3/4 Ag1/4)2/3 (Au Pt)1/2	 
   for(ly=101;ly<=250;ly++)
   {
      for(lx=1;lx<=20;lx++)
      {
         if(ThrowDise(1,3))
            continue; 
         if(HAVEDO[lx][ly]==1)
            continue;
         if(ThrowDise(1,2))
         {
            if(lx<=19)
            {
               int temp;
               temp=Map[lx][ly];
               Map[lx][ly]=Map[lx+1][ly];
               Map[lx][ly]=temp;
               HAVEDO[lx+1][ly]=1;
               continue; 
            } 
         } 
         if(ThrowDise(8,100))
         {
            if(ThrowDise(4,12))
            {
               if(ThrowDise(10,20))
                  Map[lx][ly]=MT_element_Au;
               else
                  Map[lx][ly]=MT_element_Pt;
            }
            else
            {
               if(ThrowDise(12,16))
               {
                  if(ThrowDise(10,20))
                     Map[lx][ly]=MT_element_Fe;
                  else
                     Map[lx][ly]=MT_element_Cu;
               }
               else
                   Map[lx][ly]=MT_element_Ag;
            }
         }
         else
         {
            if(ThrowDise(1,10))
               Map[lx][ly]=MT_Air;
            else
            {
               if(ThrowDise(10,150))
                  Map[lx][ly]=MT_element_Ruber;
               else
                  Map[lx][ly]=MT_Soil;
            }
         }  
      }
   }
   //return 0;
   //1000~1500 	((Fe Cu) Ag Au Pt  [Cordierite]
   for(ly=251;ly<=375;ly++)
   {
      for(lx=1;lx<=20;lx++)
      {
         if(ThrowDise(1,3))
            continue; 
         if(HAVEDO[lx][ly]==1)
            continue;
         if(ThrowDise(1,2))
         {
            if(lx<=19)
            {
               int temp;
               temp=Map[lx][ly];
               Map[lx][ly]=Map[lx+1][ly];
               Map[lx][ly]=temp;
               HAVEDO[lx+1][ly]=1;
               continue; 
            } 
         } 
         if(ThrowDise(8,100))
         {
            if(ThrowDise(4,12))
            {
               if(ThrowDise(10,20))
                  Map[lx][ly]=MT_element_Au;
               else
                  Map[lx][ly]=MT_element_Pt;
            }
            else
            {
               if(ThrowDise(12,16))
               {
                  if(ThrowDise(10,20))
                     Map[lx][ly]=MT_element_Fe;
                  else
                     Map[lx][ly]=MT_element_Cu;
               }
               else
                   Map[lx][ly]=MT_element_Ag;
            }
         }
         else
         {
            if(ThrowDise(10,910))
            {
               if(ThrowDise(15,1000))
                  Map[lx][ly]=MT_element_Cordierite;
               else
                  Map[lx][ly]=MT_Stone;
            }
            else
            {
               if(ThrowDise(1,10))
               {
                  Map[lx][ly]=MT_Air;
                  if(ThrowDise(1,10))
                     WaterMap[lx][ly]=100;
               }
               else
                  Map[lx][ly]=MT_Soil;
            }
         }  
      }
   }
   //1500~2000 	Fe Cu Ag Au Pt  [Cordierite Nephrite]	
   for(ly=376;ly<=500;ly++)
   {
      for(lx=1;lx<=20;lx++)
      {
         if(ThrowDise(1,3))
            continue; 
         if(HAVEDO[lx][ly]==1)
            continue;
         if(ThrowDise(1,2))
         {
            if(lx<=19)
            {
               int temp;
               temp=Map[lx][ly];
               Map[lx][ly]=Map[lx+1][ly];
               Map[lx][ly]=temp;
               HAVEDO[lx+1][ly]=1;
               continue; 
            } 
         } 
         if(ThrowDise(8,100))
         {
            if(ThrowDise(4,12))
            {
               if(ThrowDise(10,20))
                  Map[lx][ly]=MT_element_Au;
               else
                  Map[lx][ly]=MT_element_Pt;
            }
            else
            {
               if(ThrowDise(12,16))
               {
                  if(ThrowDise(10,20))
                  {
                     if(ThrowDise(1,100))
                        Map[lx][ly]=MT_MoneyI;
                     else
                        Map[lx][ly]=MT_element_Fe;
                  }
                  else
                     Map[lx][ly]=MT_element_Cu;
               }
               else
                   Map[lx][ly]=MT_element_Ag;
            }
         }
         else
         {
            if(ThrowDise(10,910))
            {
               if(ThrowDise(20,1000))
               {               
                  if(ThrowDise(10,20))
                     Map[lx][ly]=MT_element_Cordierite;
                  else
                     Map[lx][ly]=MT_element_Nephrite;
               }
               else
                  Map[lx][ly]=MT_Stone;
            }
            else
            {
               if(ThrowDise(1,10))
               {
                  Map[lx][ly]=MT_Air;
                  if(ThrowDise(1,10))
                     WaterMap[lx][ly]=100;
               }
               else
               {
                  if(ThrowDise(10,150))
                     Map[lx][ly]=MT_element_Ruber;
                  else
                     Map[lx][ly]=MT_Soil;
               }
            }
         }  
      }
   }
   //2000~2252 	Fe Cu Ag Au Pt  [Cordierite Nephrite Ruby]
   for(ly=501;ly<=563;ly++)
   {
      for(lx=1;lx<=20;lx++)
      {
         if(ThrowDise(1,3))
            continue; 
         if(HAVEDO[lx][ly]==1)
            continue;
         if(ThrowDise(1,2))
         {
            if(lx<=19)
            {
               int temp;
               temp=Map[lx][ly];
               Map[lx][ly]=Map[lx+1][ly];
               Map[lx][ly]=temp;
               HAVEDO[lx+1][ly]=1;
               continue; 
            } 
         } 
         if(ThrowDise(8,100))
         {
            if(ThrowDise(4,12))
            {
               if(ThrowDise(10,20))
                  Map[lx][ly]=MT_element_Au;
               else
                  Map[lx][ly]=MT_element_Pt;
            }
            else
            {
               if(ThrowDise(12,16))
               {
                  if(ThrowDise(10,20))
                  {
                     if(ThrowDise(1,30))
                        Map[lx][ly]=MT_MoneyI;
                     else
                        Map[lx][ly]=MT_element_Fe;
                  }
                  else
                     Map[lx][ly]=MT_element_Cu;
               }
               else
                   Map[lx][ly]=MT_element_Ag;
            }
         }
         else
         {
            if(ThrowDise(10,910))
            {
               if(ThrowDise(30,1000))
               {               
                  if(ThrowDise(10,40))
                     Map[lx][ly]=MT_element_Ruby;
                  else
                  {
                     if(ThrowDise(10,20))
                        Map[lx][ly]=MT_element_Cordierite;
                     else
                        Map[lx][ly]=MT_element_Nephrite;
                  }
               }
               else
                  Map[lx][ly]=MT_Stone;
            }
            else
            {
               if(ThrowDise(1,10))
               {
                  Map[lx][ly]=MT_Air;
                  if(ThrowDise(1,10))
                     WaterMap[lx][ly]=100;
               }
               else
                  Map[lx][ly]=MT_Soil;
            }
         }  
      }
   }
   //return 0;
   //2250~4000 	Fe Cu Ag Au Pt  [Cordierite Nephrite Ruby Emerald]
   for(ly=564;ly<=1000;ly++)
   {
      for(lx=1;lx<=20;lx++)
      {
         if(ThrowDise(1,3))
            continue; 
         if(HAVEDO[lx][ly]==1)
            continue;
         if(ThrowDise(1,2))
         {
            if(lx<=19)
            {
               int temp;
               temp=Map[lx][ly];
               Map[lx][ly]=Map[lx+1][ly];
               Map[lx][ly]=temp;
               HAVEDO[lx+1][ly]=1;
               continue; 
            } 
         } 
         if(ThrowDise(8,100))
         {
            if(ThrowDise(4,12))
            {
               if(ThrowDise(10,20))
                  Map[lx][ly]=MT_element_Au;
               else
                  Map[lx][ly]=MT_element_Pt;
            }
            else
            {
               if(ThrowDise(12,16))
               {
                  if(ThrowDise(10,20))
                  {
                     if(ThrowDise(1,30))
                     {
                        if(ThrowDise(2,3))
                           Map[lx][ly]=MT_MoneyI;
                        else
                           Map[lx][ly]=MT_MoneyII;
                     }
                     else
                        Map[lx][ly]=MT_element_Fe;
                  }
                  else
                     Map[lx][ly]=MT_element_Cu;
               }
               else
                   Map[lx][ly]=MT_element_Ag;
            }
         }
         else
         {
            if(ThrowDise(10+ly/28,910))
            {
               if(ThrowDise((ly-300)/2,500))
               {               
                  if(ThrowDise(30,40))
                  {
                     if(ThrowDise(10,40))
                        Map[lx][ly]=MT_element_Ruby;
                     else
                     {
                        if(ThrowDise(10,20))
                           Map[lx][ly]=MT_element_Cordierite;
                        else
                           Map[lx][ly]=MT_element_Nephrite;
                     }
                  }
                  else
                  {
                     Map[lx][ly]=MT_element_Emerald;
                  }
               }
               else
               {
                  Map[lx][ly]=MT_Stone;
                  if(ThrowDise(1,10))
                     Map[lx][ly]=MT_Fire;
               }
            }
            else
            {
               if(ThrowDise(1,10))
               {
                  Map[lx][ly]=MT_Air;
                  if(ThrowDise(1,10))
                     WaterMap[lx][ly]=100;
               }
               else
                  Map[lx][ly]=MT_Soil;
            }
         }  
      }
   }
   //return 0;
   //4000~7000 	Fe Cu Ag Au Pt  [Cordierite Nephrite Ruby Emerald Sapphire]
   for(ly=1001;ly<=1750;ly++)
   {
      for(lx=1;lx<=20;lx++)
      {
         if(ThrowDise(1,3))
            continue; 
         if(HAVEDO[lx][ly]==1)
            continue;
         if(ThrowDise(1,2))
         {
            if(lx<=19)
            {
               int temp;
               temp=Map[lx][ly];
               Map[lx][ly]=Map[lx+1][ly];
               Map[lx][ly]=temp;
               HAVEDO[lx+1][ly]=1;
               continue; 
            } 
         } 
         if(ThrowDise(8,100))
         {
            if(ThrowDise(4,12))
            {
               if(ThrowDise(10,20))
                  Map[lx][ly]=MT_element_Au;
               else
                  Map[lx][ly]=MT_element_Pt;
            }
            else
            {
               if(ThrowDise(12,16))
               {
                  if(ThrowDise(10,20))
                  {
                     if(ThrowDise(1,100))
                     {
                        if(ThrowDise(1,3))
                           Map[lx][ly]=MT_MoneyI;
                        else if(ThrowDise(1,2))
                           Map[lx][ly]=MT_MoneyII;
                        else
                           Map[lx][ly]=MT_MoneyIII;
                     }
                     else
                        Map[lx][ly]=MT_element_Fe;
                  }
                  else
                     Map[lx][ly]=MT_element_Cu;
               }
               else
                   Map[lx][ly]=MT_element_Ag;
            }
         }
         else
         {
            if(ThrowDise(10,910))
            {
               if(ThrowDise((ly-490)*2,1000))
               {               
                  if(ThrowDise(30,40))
                  {
                     if(ThrowDise(10,40))
                        Map[lx][ly]=MT_element_Ruby;
                     else
                     {
                        if(ThrowDise(10,20))
                           Map[lx][ly]=MT_element_Cordierite;
                        else
                           Map[lx][ly]=MT_element_Nephrite;
                     }
                  }
                  else
                  {
                     if(ThrowDise(10,20))
                        Map[lx][ly]=MT_element_Emerald;
                     else
                        Map[lx][ly]=MT_element_Sapphire;
                  }
               }
               else
               {
                  Map[lx][ly]=MT_Stone;
                  if(ThrowDise((int)(sqrt(10000*ly/750)),100))
                     Map[lx][ly]=MT_Fire;
               }
            }
            else
            {
               if(ThrowDise(1,10))
                  Map[lx][ly]=MT_Air;
               else
                  Map[lx][ly]=MT_Soil;
            }
         }  
      }
   }
   
}
//int p[6000];
int ElementPrice(p)
int p;
{
   switch(p)
   {
      case element_Fe:
         return 30;
      case element_Cu:
         return 50;
      case element_Ag:
         return 100;
      case element_Au:
         return 200;
      case element_Pt:
         return 400;
      case element_Cordierite:
         return 450;
      case element_Nephrite:
         return 750;
      case element_Ruby:
         return 1000;
      case element_Sapphire:
         return 2500;
      case element_Emerald:
         return 1000;
      case element_Ruber:
         return 1;
   } 
}
int InitialElement()
{
   //ElementName
   strcpy(ElementName[element_Fe],"Iron");
   strcpy(ElementName[element_Cu],"Copper");
   strcpy(ElementName[element_Ag],"Silver");
   strcpy(ElementName[element_Au],"Gold");
   strcpy(ElementName[element_Pt],"Platinum");
   strcpy(ElementName[element_Cordierite],"Cordierite");
   strcpy(ElementName[element_Nephrite],"Nephrite");
   strcpy(ElementName[element_Ruby],"Ruby");
   strcpy(ElementName[element_Sapphire],"Sapphire");
   strcpy(ElementName[element_Emerald],"Emerald");
   strcpy(ElementName[element_Ruber],"Ruber");
   //ElementPricee; 
   /* 
   ElementPrice[element_Fe]=30;
   ElementPrice[element_Cu]=50;
   ElementPrice[element_Ag]=100;
   ElementPrice[element_Au]=200;
   ElementPrice[element_Pt]=400;
   ElementPrice[element_Cordierite]=450;
   ElementPrice[element_Nephrite]=750;
   ElementPrice[element_Ruby]=1000;
   ElementPrice[element_Sapphire]=2500;
   ElementPrice[element_Emerald]=1000;
   */ 
   //Element Print Style
   strcpy(ElementStyle[element_Fe].chr,"¡»");
   ElementStyle[element_Fe].color=0;
   strcpy(ElementStyle[element_Cu].chr,"¡»");
   ElementStyle[element_Cu].color=4;
   strcpy(ElementStyle[element_Ag].chr,"¡¿"); //
   ElementStyle[element_Ag].color=7;
   strcpy(ElementStyle[element_Au].chr,"¡¿");
   ElementStyle[element_Au].color=14; 
   strcpy(ElementStyle[element_Pt].chr,"¡¶");
   ElementStyle[element_Pt].color=7;
   strcpy(ElementStyle[element_Cordierite].chr,"¡¹");
   ElementStyle[element_Cordierite].color=9;
   strcpy(ElementStyle[element_Nephrite].chr,"¡´");
   ElementStyle[element_Nephrite].color=13;
   strcpy(ElementStyle[element_Ruby].chr,"¡¹");
   ElementStyle[element_Ruby].color=4;
   strcpy(ElementStyle[element_Sapphire].chr,"¡¹");
   ElementStyle[element_Sapphire].color=14;
   strcpy(ElementStyle[element_Emerald].chr,"¡¹");
   ElementStyle[element_Emerald].color=1;
   strcpy(ElementStyle[element_Ruber].chr,"¡¼");
   ElementStyle[element_Emerald].color=1;
   //¡Z¢b¢c¢d¢e¢f¢g¢h¢i
   strcpy(water[0].s,"¡Z")  ; 
   strcpy(water[1].s,"¡Z");
   strcpy(water[2].s,"¢b");
   strcpy(water[3].s,"¢c");
   strcpy(water[4].s,"¢d");
   strcpy(water[5].s,"¢e");
   strcpy(water[6].s,"¢f");
   strcpy(water[7].s,"¢g");
   strcpy(water[8].s,"¢h");;
   strcpy(water[9].s,"¢i")  ; 
   strcpy(water[10].s,"¢i")  ; 
}

//Extra Function
int ThrowDise(a,b)
int a;
int b;
{
   int k=(rand()%b+1);
   return (k<=a);
}
void exsleep(int time)
{
   sleep(time);
   while(1)
   {
      if(kbhit()==1)
         getch();
      if(kbhit()==0)break;
   }
   return;
}
int GetDistance(x1,y1,x2,y2)
int x1;
int y1;
int x2;
int y2;
{
   return (abs(x1-x2)+abs(y1-y2));
}
int GetMin(a,b)
int a;
int b;
{
   if(b>=a)
      return a;
   else
      return b;
}
int GetMax(a,b)
int a;
int b;
{
   if(b>=a)
      return b;
   else
      return a;
}
