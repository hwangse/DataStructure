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

/*���α׷��� ���������� Ȯ���ϴ� �Լ�. 
board�迭�� ��� ���Ұ� 1�̻��� ��� SUCCESS�� ��ȯ�Ѵ�.*/
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

	//������ǥ�� (0,1)�̴�
	currentR--;currentC--;
	board[currentR][currentC]++;

	///////�������� �߻�///////	
	srand((unsigned int)seed);
	///////////////////////

	/*��ã�� ���� �κ�*/
	while(totalCount<MOVE_LIMIT && !flag)
	{
		/*���� ����*/
		
			k = rand() % 8; //k is index of move array

			nextRow=currentR+move[k].r;
			nextCol=currentC+move[k].c;

			/*�ε��� ���� Ȯ��*/
			if(nextRow>=0 && nextRow<row && nextCol>=0 && nextCol<col)
			{

				currentC=nextCol;
				currentR=nextRow;
				board[currentR][currentC]++;
				totalCount++;
			}

			/*�������� Ȯ��*/
			flag=CompleteOrNot(board,row,col);

			if(flag)
				break;

			
	}
	if(flag) //���������� ��� �̵��ߴٸ�
	{
		for(i=0;i<row;i++)
		{
			for(j=0;j<col;j++)
				printf("%d ",board[i][j]);
			printf("\n");
		}
		printf("\nTotal : %d\n",totalCount);
	}
	else //�̵�Ƚ���� 50000�� �ʰ��ؼ� �����Ŷ��
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