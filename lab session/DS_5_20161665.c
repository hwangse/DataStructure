#include<stdio.h>
#include<stdlib.h>

#define FALSE 0
#define TRUE 1
#define MAX_STACK 1000

typedef struct{
	int row;
	int col;
	int dir;
}element;

typedef struct{
	int dir;
	int vert;
	int horiz;
}offsets;
offsets move[8];

element stack[MAX_STACK];

element pop(int* top)
{
	if(*top == -1)
	{
		printf("Stack is Empty!\n");
	}
	else
	{
		*top -= 1;
		return stack[*top+1];
	}
}
void push(element item,int *top)
{
	if(*top >= MAX_STACK-1)
		printf("Stack is Full!\n");
	stack[++(*top)]=item;
}

int main()
{
	FILE *fp=fopen("MAZE.txt","r");
	int row,col,nextrow,nextcol,found=FALSE,dir,top=0;
	int EXIT_ROW,EXIT_COL;
	int temp,temp2,i=0,j,m=0,n=0;
	int **maze,**mark;
	element position;

	/*move initialization*/
	move[0].dir=0;move[0].vert=-1;move[0].horiz=0;
	move[1].dir=1;move[1].vert=-1;move[1].horiz=1;
	move[2].dir=2;move[2].vert=0;move[2].horiz=1;
	move[3].dir=3;move[3].vert=1;move[3].horiz=1;
	move[4].dir=4;move[4].vert=1;move[4].horiz=0;
	move[5].dir=5;move[5].vert=1;move[5].horiz=-1;
	move[6].dir=6;move[6].vert=0;move[6].horiz=-1;
	move[7].dir=7;move[7].vert=-1;move[7].horiz=-1;
	/*initialization end*/
	
	while(1)
	{
		if(i==0)
		{
			fscanf(fp,"%d %d",&row,&col);
			maze=(int **)calloc(row,sizeof(int *));
			maze[0]=(int *)calloc(row*col,sizeof(int));
			for(j=1;j<row;j++)
				maze[j]=maze[j-1]+col;
			i++;

		}
		else if(i==1)
		{
			fscanf(fp,"%d %d",&temp,&temp2);
			i++;
		}
		else if(i==2)
		{
			fscanf(fp,"%d %d",&EXIT_ROW,&EXIT_COL);
			fgetc(fp);
			i++;
		}
		else
		{
			temp=fgetc(fp);
			
			if(temp==EOF){
				break;
			}
			else if(temp==' ')
					;
			else if(temp=='\n')
			{	 
				m++;
				n=0;
			}
			else
				maze[m][n++]=temp-'0';

		}}


	fclose(fp);

	mark=(int **)calloc(row,sizeof(int *));
	mark[0]=(int *)calloc(row*col,sizeof(int));
	for(j=1;j<row;j++)
		mark[j]=mark[j-1]+col;

	mark[1][1]=1;
	mark[EXIT_ROW][EXIT_COL]=1;
	stack[0].row=1;stack[0].col=1;stack[0].dir=1;

	while(top>-1 && !found)
	{
		position=pop(&top);
		row=position.row;
		col=position.col;
		dir=position.dir;

		while(dir<8 && !found)
		{
			nextrow=row+move[dir].vert;
			nextcol=col+move[dir].horiz;
			if(nextrow==EXIT_ROW && nextcol==EXIT_COL)
				found=TRUE;
			else if(!maze[nextrow][nextcol] && !mark[nextrow][nextcol])
			{
				mark[nextrow][nextcol]=1;
				position.row=row;position.col=col;position.dir=++dir;
				push(position,&top);
				row=nextrow;col=nextcol;dir=0;
			}
			else
				++dir;
		}
		if(row>=1 && col>=1 && !found)
			mark[row][col]=0;

	}

	if(found)
	{
		for(i=0;i<EXIT_ROW+2;i++)
		{
			for(j=0;j<EXIT_COL+2;j++)
			{
				if(maze[i][j]==0) 
				{
					if(mark[i][j]==1)
					{
						if(i==1 && j==1)
							printf(" S");
						else if(i==EXIT_ROW && j==EXIT_COL)
							printf(" E");
						else
							printf("□");
					}
					else
						printf("  ");
				}
				else // maze가 1일 경우에
				{
					printf("■");
				}

			}
			printf("\n");
		}
	}
	else
		printf("The maze does not have a path\n");

	free(maze);free(mark);
	return 0;
}
