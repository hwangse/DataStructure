#include<stdio.h>
#include<stdlib.h>

enum {yellow=2,green};

typedef struct _Node{
	int num;
	struct _Node* next;
}Node;

typedef struct{
	int numV;
	Node** AJList;
}Graph;

typedef struct{
	Node* front;
	Node* rear;
}Queue;

int PossibleColoring=1;	//Determines if the graph can be COLORED or NOT

void InsertNodeToList(Node** list,int a, int b);
void BFS(Graph* gPtr,int start);
void enqueue(Queue *q,int data);
int dequeue(Queue* q);
int IsEmptyQueue(Queue *q);

int main()
{
	FILE* fp=fopen("Data.txt","r");
	Graph g;
	int temp,num1,num2,i;

	fscanf(fp,"%d",&temp);//Number of Vertex
	g.numV=temp;//Store the Num of Vertex in graph
	g.AJList=(Node**)malloc(sizeof(Node*)*(g.numV+1));
	
	printf("%d\n",g.numV);

	for(i=0;i<g.numV+1;i++)
		g.AJList[i]=NULL;

	while(fscanf(fp,"%d %d",&num1,&num2)!=EOF){
		InsertNodeToList(g.AJList,num1,num2);
		InsertNodeToList(g.AJList,num2,num1);
		printf("%d	%d\n",num1,num2);
	}

	BFS(&g,1);//2nd parameter can be any number between 1 to numV

	if(PossibleColoring)// PossibleColoring==1;
		printf("이 도형은 색칠이 가능하다.\n");
	else		   //PossibleColoring==0;
		printf("이 도형은 색칠이 불가능하다.\n");

	/*free memories*/
	for(i=0;i<g.numV+1;i++)
		free(g.AJList[i]);
	free(g.AJList);

	return 0;
}
void InsertNodeToList(Node** list,int a, int b)
{
	Node* temp;

	Node* newNode=(Node*)malloc(sizeof(Node));
	newNode->num=b;
	newNode->next=NULL;

	temp=list[a];
	if(!temp)	//if list is empty
		list[a]=newNode;	//ADD Node to head of List
	else{
		while(temp->next!=NULL)
			temp=temp->next;
		temp->next=newNode;
	}
}

void BFS(Graph* gPtr,int start)
{
	Queue q;
	int* VisitInfo=(int *)calloc((gPtr->numV)+1,sizeof(int));
	int* ColorInfo=(int *)calloc((gPtr->numV)+1,sizeof(int));
	int StartPoint;
	Node* temp;

	q.front=NULL;
	q.rear=NULL;
	
	enqueue(&q,start);
	VisitInfo[start]=1;
	ColorInfo[start]=yellow;
	
	while(!IsEmptyQueue(&q)){
		StartPoint=dequeue(&q);
		temp=gPtr->AJList[StartPoint];

		while(temp){
		//if currentNode has same color with an adjacent node
		//the graph cannot be colored
			if(ColorInfo[StartPoint]==ColorInfo[temp->num]){
				PossibleColoring=0;
				return;
			}

			if(!VisitInfo[temp->num]){
				enqueue(&q,temp->num);
				VisitInfo[temp->num]=1;

				if(ColorInfo[StartPoint]==yellow)
					ColorInfo[temp->num]=green;
				else
					ColorInfo[temp->num]=yellow;
			}
			temp=temp->next;
		}
	}

	free(VisitInfo);
	free(ColorInfo);
}
void enqueue(Queue* q,int a)
{
	Node* newNode=(Node*)malloc(sizeof(Node));

	newNode->num=a;
	newNode->next=NULL;

	if(IsEmptyQueue(q)){
		q->front=newNode;
		q->rear=newNode;
	}
	else{
		q->rear->next=newNode;
		q->rear=newNode;
	}
}
int dequeue(Queue* q)
{
	Node* DNode;
	int Ddata;

	if(IsEmptyQueue(q)) //if queue is empty,
	{
		printf("Cannot Delete : Empty Queue \n");
		exit(-1);//print Error message and exit
	}
	
	DNode=q->front;
	Ddata=DNode->num;
	q->front=q->front->next;

	free(DNode);
	return Ddata;

}
int IsEmptyQueue(Queue *q)
{
	if(q->front==NULL)
		return 1;
	return 0;
}
