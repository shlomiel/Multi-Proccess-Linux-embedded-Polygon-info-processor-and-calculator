
#include "ex2_q1_given.h"





//declerations of constants and functions
#define MAXNAMESIZE 30
#define BYTESIZE 8

void CheckMalloc(void* pointer);
void InsertToList(struct polygon *i_poly);
void FreeList(struct Node* head);
void SetVertices(struct polygon *i_Poly);
void PrintPolyPoints(struct polygon *i_Poly);
void WriteAndClacSingle(struct polygon* poly);
void SIGUSR_handler(int signum);
void set_sig_handlers();


struct Node *head = NULL,*current = NULL, *tail = NULL;
int printed = 0,created = 0;


void SIGUSR_handler(int signum)
{
  enum POLY_TYPE type;
  
  switch(signum)
  {
    case SIGUSR1:
	  if(!current)
	  {
		  current = head;
	  }
	  WriteAndClacSingle(current->poly);
	  fflush(stdout);
	  current = current->next;
	  printed++;
      break;


    case SIGUSR2:
	 type = head->poly->poly_type;
	 print_helper_end_msg(created,printed,type);
	 FreeList(head);
	 exit(0);
     break;

  }
}



void set_sig_handlers()
{
  struct sigaction act = {0};
  act.sa_flags = SA_RESTART;   // Restart functions if interrupted by handler
  act.sa_handler = SIGUSR_handler;
  sigaction(SIGUSR1, &act, NULL);
  sigaction(SIGUSR2, &act, NULL);
}

int main(int argc,char* argv[])
{
	set_sig_handlers();
	
	int i;
	char input[MAXNAMESIZE];
	struct polygon *newPolygon = NULL;

	while (1)
	{
	    scanf("%s",input);
        i = 0;
		while (input[i] != '\0' && input[i] != '\n')
		{
			switch (input[i])
			{
			case 'N':
				newPolygon = (struct polygon*)malloc(sizeof(struct polygon));
				CheckMalloc(newPolygon);
				created++;
				break;

			case 'Q': // Quadrilateral
				newPolygon->poly_type = QUADRI;
				SetVertices(newPolygon);
				InsertToList(newPolygon);
				break;

			case 'H': // Hexagon
				newPolygon->poly_type = HEXAGON;
				SetVertices(newPolygon);
				InsertToList(newPolygon);
				break;

			case 'O': // Octagon
				newPolygon->poly_type = OCTAGON;
				SetVertices(newPolygon);
				InsertToList(newPolygon);
				break;
            
			default:
			   break;

			}
			i++;
		}

		if (strchr(input,'L')) //Last command
			break;
	}

	while(1)
	{
		pause();
	}  

	return 0;
}




void WriteAndClacSingle(struct polygon* i_Poly)
{
	char polyName[MAXNAMESIZE];
	print_polygon_name(i_Poly->poly_type, polyName);
	printf("%s ", polyName);
	PrintPolyPoints(i_Poly);
}

void PrintPolyPoints(struct polygon *i_Poly)
{
	for (int i = 0; i < i_Poly->poly_type; i++)
	{
		print_point(i_Poly->vertices[i]);
	}
	printf("\n");
}

void InsertToList(struct polygon *i_poly)
{
	if (!(head))
	{
	   head = (struct Node*)malloc(sizeof(struct Node));
	   head->poly = i_poly;
	   head->next = NULL;
	   tail = head;
	}

	else
	{
		struct Node* newnode = (struct Node*)malloc(sizeof(struct Node));
		CheckMalloc(newnode);
		newnode->poly = i_poly;
		tail->next = newnode;
		tail = newnode;
		tail->next = head;
	}
}

void FreeList(struct Node* head)
{
	struct Node* current = head;
	struct Node* next = current->next;

	while (current != tail)
	{
		free(current->poly);
		free(current);
		current = next;
		if(current)
			next = current->next;
	}

	if(tail)
	{
		free(tail->poly);
		free(tail);
	}

}

void SetVertices(struct polygon *i_Poly)
{
	lluint num;
	int i = 0;
	unsigned char mask = 0xff;
	char xByte;
	char yByte;
	scanf("%llx", &num);
	for (i = 0; i < QUADRI; i++)
	{
		xByte = mask & (num);
		i_Poly->vertices[i].x = (int)xByte;
		num = (num >> BYTESIZE);
		yByte = mask & (num);
		i_Poly->vertices[i].y = (int)yByte;
		num = (num >> BYTESIZE);
	}

	if (i_Poly->poly_type > QUADRI)
	{
		scanf("%llx", &num);
		while(i < i_Poly->poly_type)
		{
			xByte = mask & (num);
			i_Poly->vertices[i].x = (int)xByte;
			num = (num >> BYTESIZE);

			yByte = mask & (num);
			i_Poly->vertices[i].y = (int)yByte;
			num = (num >> BYTESIZE);
			i++;
		}

	}
}


void CheckMalloc(void* pointer) {
	if (pointer == NULL) {
		puts("memmory allocation error. shutting program down");
		exit(-1);
	}
}