#include<stdio.h>

typedef struct{
	int shortest;
	int key;
}arr;

typedef struct{
	int x;
	int y;
	int num;
}Route;

int main(){
	FILE* fp=fopen("data.txt","r");
	int matrix[6][6],start,idx;
	int numV=6,i,j,stored=0,minVal,minCost=0;
	arr update[6];
	Route r[6];
	int Visited[6];

	for(i=0;i<6;i++)
		Visited[i]=0;

	for(i=0;i<6;i++)
		for(j=0;j<6;j++)
			fscanf(fp,"%d",&matrix[i][j]);
	fclose(fp);
	
	stored=1; //처음 위치 저장 (+1)
	for(i=0;i<6;i++){
		update[i].shortest=matrix[0][i];
		update[i].key=0;
	}

	start=0;
	Visited[0]=1;
	while(stored<6){
		minVal=9999;
		for(i=0;i<6;i++){
			if(update[i].shortest>matrix[start][i] && !Visited[i])//배열 정보 update
			{
				update[i].shortest=matrix[start][i];
				update[i].key=start;
			}
			if(update[i].shortest<minVal && !Visited[i]){
				minVal=update[i].shortest;
				idx=i;
			}
		}

		//minVal을 찾았다면, 경로 저장후 start값 변경
		minCost += minVal;
		r[stored-1].x=update[idx].key;
		r[stored-1].y=idx;
		r[stored-1].num=minVal;
		Visited[idx]=1;
		stored++;

		start=idx;
	}

	if(stored==6)
	{
		printf("Vertex	Vertex	Cost\n");
		for(i=0;i<5;i++)
			printf("%c	%c	%d\n",r[i].x+'A',r[i].y+'A',r[i].num);
		printf("prim algorithm's minimum cost = %d\n",minCost);
	}

	return 0;
}
