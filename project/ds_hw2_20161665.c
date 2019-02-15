#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define COMPARE(x,y) ((x)<(y)?-1:(x)==(y)?0:1)

/*circular linkedlist�� ������ polynomial ���*/
typedef struct _poly* polyPtr;
typedef struct _poly {
	float coef;
	int expon;
	polyPtr next;
}polynomial;

polyPtr availA = NULL;		//global avail list1 for polynomialA
polyPtr availB = NULL;		//global avail list2 for polynomialB

void pwrite(polyPtr a, polyPtr b);					//polyA, polyB�� ����Ʈ�ϴ� �Լ�
polyPtr padd(polyPtr a, polyPtr b);					//polyC=polyA+polyB
void attach(float a, int b, polyPtr *);				//padd���� polyC�� ���� �߰��� �� ȣ��Ǵ� �Լ�
void ShowResult(polyPtr a);							//add,sub,mult ���꿡�� ������� ����Ʈ�ϴ� �Լ�
polyPtr psub(polyPtr a, polyPtr b);					//polyC=polyA-polyB
polyPtr pmult(polyPtr a, polyPtr b, int n);			//polyC=polyA*polyB
void eval(polyPtr a, polyPtr b);					//�Է¹��� ���� polyA,polyB�� �������� �� ������ ������� ���
void perase(polyPtr* a, polyPtr* b, polyPtr* c);	//polyA,polyB,polyC�� null�� �ƴ� ��� avail(�������)�� ��ȯ�� null�� �����

int main()
{
	polyPtr headA=NULL, headB=NULL, headC=NULL, tempTail, newNode;
	polyPtr temp;
	float tempCof;
	FILE *fp;
	int sum, tempExp, command, turnoff = 0, numA = 0; //numA is the number of elements in polyA

	/*initialization start*/

	headA = (polyPtr)malloc(sizeof(polynomial));
	headB = (polyPtr)malloc(sizeof(polynomial));
	headA->expon = -1;
	headB->expon = -1;

	tempTail = headA;
	fp = fopen("A.txt", "r");
	while (fscanf(fp, "%f %d", &tempCof, &tempExp) != EOF)
	{
		newNode = (polyPtr)malloc(sizeof(polynomial));
		newNode->coef = tempCof;
		newNode->expon = tempExp;
		numA++;

		/*circular list linking*/
		tempTail->next = newNode;
		tempTail = newNode;
		newNode->next = headA;
	}
	fclose(fp);

	tempTail = headB;
	fp = fopen("B.txt", "r");
	while (fscanf(fp, "%f %d", &tempCof, &tempExp) != EOF)
	{
		newNode = (polyPtr)malloc(sizeof(polynomial));
		newNode->coef = tempCof;
		newNode->expon = tempExp;

		/*circular list linking*/
		tempTail->next = newNode;
		tempTail = newNode;
		newNode->next = headB;
	}
	/*initialization end*/

	/*main start*/
	while (!turnoff) {			//if turnoff sets 1, the loop ends
		printf("------------------------\n");
		printf("    M    E    N    U    \n");
		printf("1. Polynomial Write\n");
		printf("2. Polynomial Add\n");
		printf("3. Polynomail Subtraction\n");
		printf("4. Polynomial Multiply\n");
		printf("5. Polynomial Evaluation\n");
		printf("6. Polynomial Erase\n");
		printf("7. Exit\n");
		printf("------------------------\n");

		scanf("%d", &command);

		switch (command) {
		case 1:	
			if (headA && headB)			//headA !=NULL && headB !=NULL
				pwrite(headA, headB);
			else
				printf("Empty polynomials.\n");
			break;
		case 2:
			if (headA && headB) {
				printf("Polynomial Add\n");
				headC = padd(headA, headB);
				ShowResult(headC);
			}
			else
				printf("Empty polynomials.\n");
			break;
		case 3:
			if (headA && headB) {
				printf("Polynomial Subtraction\n");
				headC = psub(headA, headB);
				ShowResult(headC);
			}
			else
				printf("Empty polynomials.\n");
			break;
		case 4:
			if (headA && headB) {
				printf("Polyomial Multiply\n");
				headC = pmult(headA, headB, numA);
				ShowResult(headC);
			}
			else
				printf("Empty polynomials.\n");
			break;
		case 5:
			if (headA && headB) {
				printf("Polynomial Evaluation (X = a)\n");
				eval(headA, headB);
			}
			else
				printf("Empty polynomials.\n");
			break;
		case 6:
			perase(&headA,&headB,&headC);
			break;
		case 7:
			turnoff = 1;
			break;
		default:
			printf("Error : Input the number within 7\n");
			break;
		}

	}


	/*main end*/


	return 0;
}
void pwrite(polyPtr a, polyPtr b)
{
	polyPtr temp;

	printf("Polynomial A : ");
	temp = a->next;
	while (temp->expon != -1) {
		if (temp->next->expon == -1)
			printf("%.0fx^%d\n", temp->coef, temp->expon);
		else
			printf("%.0fx^%d + ", temp->coef, temp->expon);
		temp = temp->next;
	}

	printf("Polynomial B : ");
	temp = b->next;
	while (temp->expon != -1) {
		if (temp->next->expon == -1)
			printf("%.0fx^%d\n", temp->coef, temp->expon);
		else
			printf("%.0fx^%d + ", temp->coef, temp->expon);
		temp = temp->next;
	}
}
polyPtr padd(polyPtr a, polyPtr b)
{
	polyPtr Res;		//the head of a+b list
	polyPtr TailOfRes;	//the tail of a+b list
	polyPtr headA, headB;
	float sum = 0;

	Res = (polyPtr)malloc(sizeof(polynomial));
	Res->expon = -1;
	TailOfRes = Res;

	headA = a->next; headB = b->next;
	while (headA->expon != -1 && headB->expon != -1) {
		switch (COMPARE(headA->expon, headB->expon)) {
		case -1:
			attach(headB->coef, headB->expon, &TailOfRes);
			headB = headB->next;
			break;
		case 0:
			sum = headA->coef + headB->coef;
			if (sum)
				attach(sum, headA->expon, &TailOfRes);
			headA = headA->next; headB = headB->next;
			break;
		case 1:
			attach(headA->coef, headA->expon, &TailOfRes);
			headA = headA->next;
			break;
		}
	}

	for (; headA->expon != -1; headA = headA->next)
		attach(headA->coef, headA->expon, &TailOfRes);
	for (; headB->expon != -1; headB = headB->next)
		attach(headB->coef, headB->expon, &TailOfRes);

	return Res;
}
void attach(float coef, int expon, polyPtr *p)
{
	polyPtr temp = (polyPtr)malloc(sizeof(polynomial));
	/*newNode allocation*/
	temp->coef = coef;
	temp->expon = expon;
	if ((*p)->expon == -1)
		temp->next = *p;
	else
		temp->next = (*p)->next;

	/*Linking Nodes*/
	(*p)->next = temp;
	*p = temp;
}
void ShowResult(polyPtr a)
{
	polyPtr temp;

	printf("Result : ");
	temp = a->next;
	while (temp->expon != -1) {
		if (temp->next->expon == -1) {

			printf("%.0fx^%d\n", temp->coef, temp->expon);
		}
		else {
			if (temp->next->coef<0)
				printf("%.0fx^%d ", temp->coef, temp->expon);
			else
				printf("%.0fx^%d + ", temp->coef, temp->expon);
		}
		temp = temp->next;
	}
}
polyPtr psub(polyPtr a, polyPtr b)
{
	polyPtr Res; //a-b�� ����� ����Ʈ�� ���
	polyPtr TailOfRes; //Res����Ʈ�� ����(�� ���� ���� �κ�)
	polyPtr headA, headB;
	float sub = 0;

	Res = (polyPtr)malloc(sizeof(polynomial));
	Res->expon = -1;
	TailOfRes = Res;

	headA = a->next; headB = b->next;
	while (headA->expon != -1 && headB->expon != -1) {
		switch (COMPARE(headA->expon, headB->expon)) {
		case -1:
			attach(-(headB->coef), headB->expon, &TailOfRes);
			headB = headB->next;
			break;
		case 0:
			sub = headA->coef - headB->coef;
			if (sub)
				attach(sub, headA->expon, &TailOfRes);
			headA = headA->next; headB = headB->next;
			break;
		case 1:
			attach(headA->coef, headA->expon, &TailOfRes);
			headA = headA->next;
			break;
		}
	}

	for (; headA->expon != -1; headA = headA->next)
		attach(headA->coef, headA->expon, &TailOfRes);
	for (; headB->expon != -1; headB = headB->next)
		attach(-(headB->coef), headB->expon, &TailOfRes);

	return Res;
}
polyPtr pmult(polyPtr a, polyPtr b, int n)
{
	polyPtr Res, temp, tail;
	polyPtr headA = a->next, headB = b->next;
	/*arr�� �������꿡 �ʿ��� ���� polynomialPtr�� ���� polyPtr������ �迭*/
	polyPtr* arr = (polyPtr *)malloc(sizeof(polyPtr)*n);
	int i = 0;

	/*A���׽��� ���� ���� ��� ���׽��� ����(������ ������ 8���� ���׽� ����)*/
	while (headA->expon != -1) {
		arr[i] = (polyPtr)malloc(sizeof(polynomial));
		arr[i]->expon = -1;

		temp = headB;
		tail = arr[i];
		while (temp->expon != -1) {
			attach(headA->coef*temp->coef, headA->expon + temp->expon, &tail);
			temp = temp->next;
		}
		i++;
		headA = headA->next;
	}
	/*������ ���׽ĵ鿡���� ��� ���� ������ ����*/
	Res = arr[0];
	for (i = 1; i < n; i++)
		Res = padd(Res, arr[i]); //�ռ� ������ padd �Լ� �̿�

	/*free*/
	for (i = 0; i < n; i++)
		free(arr[i]);
	free(arr);

	return Res;
}
void eval(polyPtr a, polyPtr b)
{
	double resA = 0, resB = 0;
	double input, temp = 0;
	int i,repeat;
	polyPtr headA = a->next, headB = b->next;

	printf("INPUT X : ");
	scanf("%lf", &input);

	/*pow �Լ��� �̿��� �ŵ������� ���*/
	while (headA->expon != -1) {

		resA += (double)(headA->coef)*pow(input, (double)headA->expon);
		headA = headA->next;
	}
	while (headB->expon != -1) {

		resB += (double)(headB->coef)*pow(input, (double)headB->expon);
		headB = headB->next;
	}

	printf("Result A : %.4lf\n", resA);
	printf("Result B : %.4lf\n", resB);
}
void perase(polyPtr* a, polyPtr* b,polyPtr *c)
{
	polyPtr temp,prev;
	
		if ((*a) != NULL) {
			temp = (*a)->next;
			(*a)->next = availA;
			availA = temp;
			(*a) = NULL;
	}
		if ((*b) != NULL) {
			temp = (*b)->next;
			(*b)->next = availB;
			availB= temp;
			(*b) = NULL;
		}

		/*polyA�� polyB�� avail�� ���� �Űܵΰ� ������ ����� 
		polyC�� ��� ���Ҹ� �����Ѵ�. */
		if ((*c) != NULL) {
			temp = (*c)->next;
			prev = (*c)->next->next;

			while (temp->expon != -1)
			{
				free(temp);
				temp = prev;
				prev = prev->next;
					
			}
			(*c) = NULL;
		}

		if(!(*a) && !(*b) && !(*c))		//If three polynomials erase compeletely
			printf("Polynomial Erase\n");

}