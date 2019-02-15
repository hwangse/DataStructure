#include<stdio.h>
#include<stdlib.h>

#define MAX_ELEMENTS 200
#define HEAP_FULL(n) (n==MAX_ELEMENTS-1)
#define SWAP(x,y,t) ((t)=(x),(x)=(y),(y)=(t))
#define HEAP_EMPTY(n) (!n)

typedef struct _heap{
    int key;

}element;
int cur_size=0; //힙의 사이즈를 나타내는 변수

element heap[MAX_ELEMENTS];

void adjust(element a[],int,int);
void heapSort(element a[],int );
void push(int );
void printHeap();
int pop();

int main()
{
    int command,key;
    int turn_on=1;
    int del;
    int i,mix=rand()%50,a,b;
    element tempNode;

    while(turn_on){
	printf("--------------------------------------------------\n");
	printf("- 1. Insert an element into the heap	         -\n");
	printf("- 2. Remove the key with lowest value	         -\n");
	printf("- 3. Change the priority of an arbitrary element -\n");
	printf("- 4. Print the status of a heap 		 -\n");
	printf("- 5. Quit					 -\n");
	printf("--------------------------------------------------\n");

	scanf("%d",&command);

	switch(command){
	    case 1 : 
		 /*힙에 새로운 노드 삽입*/
		printf("삽입할 key 값 : " );
		scanf("%d",&key);
		push(key);
		break;
	    case 2 : 
		/*우선순위가 제일 높은 노드 삭제*/
		del=pop();
		if(del!=-1)
			printf("'%d'를 삭제하였습니다.\n",del);
		printf("아무키나 누르면 메인 메뉴로 이동합니다.\n");

		getchar();
		getchar();
		break;
	    case 3 : 
		/*rand함수를 이용해 임의로 순서를 섞기*/
		while(1){
			a=rand()%cur_size+1;
			b=rand()%cur_size+1;
			if(a!=b) break;
		}
		for(i=0;i<mix;i++)
			SWAP(heap[a],heap[b],tempNode);
		heapSort(heap,cur_size);
		break;
	    case 4 : 
		/*힙 전체 출력하기*/
		printHeap();
		break;
	    case 5 : 
		/*무한 루프 종료*/
		turn_on=0;
		break;
	}

    }


    return 0;
}
void push(int item)
{
    int i;

    if(HEAP_FULL(cur_size)){
	fprintf(stderr,"The heap is full. \n");
	exit(EXIT_FAILURE);
    }

    i=cur_size+1;
    while(i != 1){
	if(item>=heap[i/2].key)
	    break;
	heap[i]=heap[i/2];
	i /= 2;
    }
    heap[i].key=item;
    cur_size++;
    
}
int pop()
{
   int del=heap[1].key,temp; //지울 값 저장
   int parent,child;

   if(HEAP_EMPTY(cur_size)){
       fprintf(stderr,"The heap is empty\n");
       return -1;
   }
   parent=1;child=2;

   if(cur_size>2){
   while(child<cur_size){
	   temp=heap[cur_size].key;

	   if(child<cur_size && heap[child].key>=heap[child+1].key)
		   child++;
	   if(heap[child].key>=temp) //바꿔야하는 경우
		break;
	   heap[parent]=heap[child];
	   parent=child;
	   child *= 2;
   }
   	heap[parent].key=temp;
   }
   else
	heap[1]=heap[2];

	cur_size--;

   return del;

}
void printHeap()
{
    int i=1;

    if(HEAP_EMPTY(cur_size)){
	fprintf(stderr,"The heap is empty\n");
	exit(EXIT_FAILURE);
    }

    for(i=1;i<=cur_size;i++)
    {
	printf("%d 번쩨 : %d\n",i,heap[i].key);
    }
    
}
void heapSort(element h[],int n)
{
	int i,j;
	element temp;

	for(i=n/2;i>0;i--)
		adjust(h,i,n);
	for(i=n-1;i>0;i--){
		SWAP(h[1],h[i+1],temp);
		adjust(h,1,i);
	}
}
void adjust(element h[],int root,int n)
{
	element temp;
	int child,rootKey;
	temp = h[root];
	rootKey=h[root].key;
	child=2*root;

	while(child<=n){
		if(child<n && h[child].key<h[child+1].key)
			child++;
		if(rootKey>h[child].key)
			break;
		else{
			h[child/2]=h[child];
			child *= 2;
		}
	}
	h[child/2]=temp;
}
