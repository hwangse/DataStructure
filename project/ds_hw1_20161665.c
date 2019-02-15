#include<stdio.h>
#include<stdlib.h> 
#include <time.h>
#define MOVE_LIMIT 50000
#define FAIL 0
#define SUCCESS 1

typedef struct{
	int r;
	int c;
}offsets;

offsets move[8];

/*프로그램의 종료조건을 확인하는 함수. 
board배열의 모든 원소가 1이상일 경우 SUCCESS를 반환한다.*/
int CompleteOrNot(int **,int ,int); 

void main() {
	int seed, k,tmp,flag=0,totalCount=0;
	int row,col,nextRow,nextCol,currentR,currentC;
	int **board;
	int i,j;
	FILE* fp = fopen("data.txt", "r");

	/*initialize move array*/
	move[0].r=1;move[0].c=-1;
	move[1].c=0;move[1].r=1;
	move[2].c=1;move[2].r=1;
	move[3].c=1;move[3].r=0;
	move[4].c=1;move[4].r=-1;
	move[5].c=0;move[5].r=-1;
	move[6].c=-1;move[6].r=-1;
	move[7].c=-1;move[7].r=0;

	fscanf(fp,"%d %d",&row,&col);
	fscanf(fp,"%d %d",&currentC,&currentR);
	fscanf(fp,"%d",&seed);
	fclose(fp);

	board=(int **)calloc(row,sizeof(int *));
	board[0]=(int *)calloc(row*col,sizeof(int));
	for(i=1;i<row;i++)
		board[i]=board[i-1]+col;

	//시작좌표는 (0,1)이다
	currentR--;currentC--;
	board[currentR][currentC]++;

	///////랜덤난수 발생///////	
	srand((unsigned int)seed);
	///////////////////////

	/*길찾기 시작 부분*/
	while(totalCount<MOVE_LIMIT && !flag)
	{
		/*난수 설정*/
		
			k = rand() % 8; //k is index of move array

			nextRow=currentR+move[k].r;
			nextCol=currentC+move[k].c;

			/*인덱스 범위 확인*/
			if(nextRow>=0 && nextRow<row && nextCol>=0 && nextCol<col)
			{

				currentC=nextCol;
				currentR=nextRow;
				board[currentR][currentC]++;
				totalCount++;
			}

			/*종료조건 확인*/
			flag=CompleteOrNot(board,row,col);

			if(flag)
				break;

			
	}
	if(flag) //성공적으로 모두 이동했다면
	{
		for(i=0;i<row;i++)
		{
			for(j=0;j<col;j++)
				printf("%d ",board[i][j]);
			printf("\n");
		}
		printf("\nTotal : %d\n",totalCount);
	}
	else //이동횟수가 50000을 초과해서 끝난거라면
		printf("ERROR : OVER THE MOVE LIMIT\n");

	free(board[0]);free(board);
}
int CompleteOrNot(int **board,int row,int col)
{
	int i,j;

	for(i=0;i<row;i++)
	{
		for(j=0;j<col;j++)
		{
			if(board[i][j]<1)
				return FAIL;
		}
	}
	return SUCCESS;
}