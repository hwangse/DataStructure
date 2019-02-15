#include<stdio.h>
#define MAX_TREE 100

typedef  int TData;
TData tree[MAX_TREE]={0};//배열로 선언된 트리

void Inorder(int i);

int flag=0;	//만약 이진 트리가 아니라면 flag=1로 set
int temp=-100;  //이진트리인지를 확인하기 위한 변수

int main()
{
	FILE* fp=fopen("data2.txt","r");
	int temp,idx=0;

	while(fscanf(fp,"%d",&temp)!=EOF)
	{
		tree[++idx]=temp;
	}

	Inorder(1);	//inorder로 탐색하며 BST인지를 확인한다.

	if(flag)//이진 트리가 아니라면 flag=1로 set
		printf("This Tree is Not a BST\n");
	else
		printf("This Tree is BST\n");

	return 0;
}
void Inorder(int i)
{
	if(!tree[i])
		return;
	else
	{
		Inorder(i*2);

		if(temp>tree[i])//숫자가 오름차순으로 정렬되지 않았다면
			flag=1; //flag=1로 설정한다.
		temp=tree[i];

		Inorder(i*2+1);
	}
}
