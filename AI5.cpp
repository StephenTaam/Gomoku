#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include"ai.h"
#include"player.h"
int chess[10][10];
void init()//init chessboard
{
   int i,j;
   for(i=0;i<10;i++)
   {
	   for(j=0;j<10;j++)
		   chess[i][j]=0;
   }
}
void list()//list chessboard
{
   int i,j;
   printf("  ");
   for(i=0;i<10;i++)
	   printf("%d ",i);
   printf("\n");
   for(i=0;i<10;i++)
   {
	   printf("%d ",i);
	   for(j=0;j<10;j++)
	   {
		   if(chess[i][j]==0)printf("- ");
		   else if(chess[i][j]==1)printf("o ");
		   else printf("x ");
	   }
	   printf("\n");
   }
}
int main()
{
	int m=0;
   system("color 70");
   init();
   list();
   for(;;)
   {
   int a,b;
   printf("input the x coordinate of your next move:");
   scanf("%d",&a);
   printf("input the y coordinate of your next move:");
   scanf("%d",&b);
   chess[a][b]=1;m++;
   system("cls");
   list();
   if(player_winornot(chess,a,b)==1)
	   break;
   if(m==100){printf("Its a draw!\n");break;}
   int n=player_choice(chess);
   
   chess[n/10][n%10]=-1;m++;
   system("cls");
   list();
   printf("the last move of computer was: (%d,%d)\n",n/10,n%10);
   if(ai_winornot(chess,n/10,n%10)==1)
	   break;
   if(m==100){printf("Its a draw!\n");break;}
   }
   getch();
}