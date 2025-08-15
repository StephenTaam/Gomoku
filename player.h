#include<stdio.h>
typedef struct pk
{
	int a;
	int b;
}pdata;
int pcount_1(int chess[10][10],int x,int y)//打横的计算 //calculate in row
{
    int n=1;int b;
	b=y-1;
	while(b!=-1&&chess[x][b]==1)//左 //left
	{
      n++;
	  b--;
	}
    b=y+1;
	while(b!=10&&chess[x][b]==1)//右 //right
	{
      n++;
	  b++;
	}
	return n;
}
int pcount_2(int chess[10][10],int x,int y)//竖直方向的计算 //calculate in column 
{
	int n=1;int a;
	a=x-1;
	while(a!=-1&&chess[a][y]==1)//上 //top
	{
      n++;
	  a--;
	}
    a=x+1;
	while(a!=10&&chess[a][y]==1)//下 //bottom
	{
      n++;
	  a++;
	}
	return n;
}
int pcount_3(int chess[10][10],int x,int y)//从左上到右下 //from top of left to bottom of right
{
	int n=1;int a;int b;
    a=x-1;b=y-1;
	while(a!=-1&&b!=-1&&chess[a][b]==1)
	{
		n++;
		a--;
		b--;
	}
	a=x+1;b=y+1;
    while(a!=10&&b!=10&&chess[a][b]==1)
	{
		n++;
		a++;
		b++;
	}
	return n;
}
int pcount_4(int chess[10][10],int x,int y)//从右上到左下 //from top of right to bottom of left
{
	int n=1;int a;int b;
    a=x-1;b=y+1;
	while(a!=-1&&b!=10&&chess[a][b]==1)
	{
		n++;
		a--;
		b++;
	}
	a=x+1;b=y-1;
    while(a!=100&&b!=0&&chess[a][b]==1)
	{
		n++;
		a++;
		b--;
	}
	return n;
}
int pc1(int chess[10][10],int x,int y)
{
    int b;int k1=1,k2=1;
	b=y-1;
	while(b!=-1&&chess[x][b]==1)//左 //left
	  b--;
	if(chess[x][b]==-1||b==-1)k1=0;
    b=y+1;
	while(b!=10&&chess[x][b]==1)//右 //right
	  b++;
	if(chess[x][b]==-1||b==10)k2=0;
	return(k1&&k2);
}
int pc2(int chess[10][10],int x,int y)
{
    int b;int k1=1,k2=1;
	b=x-1;
	while(b!=-1&&chess[b][y]==1)//上 //top
	  b--;
	if(chess[b][y]==-1||b==-1)k1=0;
    b=y+1;
	while(b!=10&&chess[b][y]==1)//下 //bottom
	  b++;
	if(chess[b][y]==-1||b==10)k2=0;
	return(k1&&k2);
}
int pc3(int chess[10][10],int x,int y)
{
    int b,a;int k1=1,k2=1;
	a=x-1;b=y-1;
	while(a!=-1&&b!=-1&&chess[a][b]==1)//上 //top
	{
		b--;
		a--;
	}
	if(chess[a][b]==-1||b==-1||a==-1)k1=0;
    b=y+1;a=x+1;
	while(a!=10&&b!=10&&chess[a][b]==1)//下 //bottom
	{
		b++;
		a++;
	}
	if(chess[a][b]==-1||b==10||a==10)k2=0;
	return(k1&&k2);
}
int pc4(int chess[10][10],int x,int y)
{
    int b,a;int k1=1,k2=1;
	a=x-1;b=y+1;
	while(a!=-1&&b!=10&&chess[a][b]==1)//上 //top
	{
		b++;
		a--;
	}
	if(chess[a][b]==-1||b==10||a==-1)k1=0;
    b=y-1;a=x+1;
	while(a!=10&&b!=-1&&chess[a][b]==1)//下 //bottom
	{
		b--;
		a++;
	}
	if(chess[a][b]==-1||b==-1||a==10)k2=0;
	return(k1&&k2);
}
int player_danger(int chess[10][10],int x,int y)//评估危险性 //evaluate dangers
{
   if(pcount_1(chess,x,y)==5||pcount_2(chess,x,y)==5||pcount_3(chess,x,y)==5||pcount_4(chess,x,y)==5)return 100;
   else if((pcount_1(chess,x,y)==4&&pc1(chess,x,y)==1)||(pcount_2(chess,x,y)==4&&pc2(chess,x,y)==1)||(pcount_3(chess,x,y)==4&&pc3(chess,x,y)==1)||(pcount_4(chess,x,y)==4&&pc4(chess,x,y)==1))return 50;
   else return(pcount_1(chess,x,y)+pcount_2(chess,x,y)+pcount_3(chess,x,y)+pcount_4(chess,x,y));
}
int player_winornot(int chess[10][10],int x,int y)//判断是否赢了？//judge is it win?
{
	int n=0;
	if(pcount_1(chess,x,y)>=5||pcount_2(chess,x,y)>=5||pcount_3(chess,x,y)>=5||pcount_4(chess,x,y)>=5)
	{
		n=1;
		printf("Player win\n");
	}
	return n;
}
int pline(int chess[10][10],int x,int y)
{
	int n=4;
	if(pcount_1(chess,x,y)==1)n--;
	if(pcount_2(chess,x,y)==1)n--;
	if(pcount_3(chess,x,y)==1)n--;
	if(pcount_4(chess,x,y)==1)n--;
	return n;
}
int player_choice(int chess[10][10])//压制player的下法,选择危险度最高的区域,已经有棋子的区域危险度为0 //Suppress the player's move by selecting the area with the highest danger level. The area with chess pieces already has a danger level of 0
{
	pdata dan[100];int i,j;
	for(i=0;i<100;i++)
	{
		dan[i].a=0;
		dan[i].b=0;
	}
	for(i=0;i<10;i++)//把危险度和线数存入数组 //Store the degree of danger and the number of lines in an array
	{
		for(j=0;j<10;j++)
		{
			if(chess[i][j]==0)
			{
				dan[i*10+j].a=player_danger(chess,i,j);
				dan[i*10+j].b=pline(chess,i,j);
			}
		}
	}
	int k=4;int z=0;int f;
	for(i=0;i<100;i++)
		{
			if(dan[i].a>k)
			{
				k=dan[i].a;
				z=dan[i].b;
				f=i;
			}
			else if(dan[i].a==k)//危险度同分//Equal risk level
			{
				if(dan[i].b<=z)//选择集中在线最少的点//Choose the point with the least concentration line
				{
					k=dan[i].a;
					z=dan[i].b;
					f=i;
				}
			}
		}
	return f;
}