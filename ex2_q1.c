#include "ex2_q1_given.h"


//declerations of functions and constants

#define MAXNAMESIZE 30
void CheckOpen(int file);
void SplitToFiles();
void ReadCharactersAndSendSignals(int quadChild,int hexChild,int octChild);
void PrepExec(char *instream);
char *myArgs[] = {HELPER,NULL};
void RedirectStreams();



int main(int argc, char* argv[])
{	
	int octChild, quadChild, hexChild;
    
	RedirectStreams();
	SplitToFiles();
    
	quadChild = fork();
	if(quadChild == -1)
	{
		return 1;
	}

    if (quadChild == 0) //child1
    {
		PrepExec(QUAD_IN);
    }

	hexChild = fork();
	if(hexChild == -1)
	{
		   return 1;
	}
	if(hexChild == 0) //child 2
	{
		PrepExec(HEX_IN);
	}

	octChild = fork();
	if(octChild == -1)
	{
		   return 1;
	}
    if(octChild == 0)//child 3
	{
		PrepExec(OCT_IN);
    }


	ReadCharactersAndSendSignals(quadChild,hexChild,octChild);
	
	int childPs;
	while((childPs = wait(NULL))>0);
	return 0;
}

void PrepExec(char *instream)
{
		int infile = open(instream, O_RDONLY, 0777);  //redirect stdin
		CheckOpen(infile);
		dup2(infile,0);
		close(infile);
		execve(HELPER,myArgs,NULL);
}

void RedirectStreams()
{
	//redirect stdin to in.txt
	int file = open("in.txt", O_RDONLY, 0777);
	CheckOpen(file);
	dup2(file,0);
	close(file);

	//redirect stdout
	file = open(ALL_OUT,O_RDWR|O_APPEND|O_CREAT,0777); 
	CheckOpen(file);
	dup2(file,1);
	close(file);
}

void SplitToFiles()
{
	FILE *octFilePtr = NULL,*hexFilePtr=NULL,*quadFilePtr=NULL;
	char input[MAXNAMESIZE];
	int last = 0;

    while (1)
	{
	    scanf("%s",input);
		if (strchr(input,'L')) // Last command
		{
			if(strchr(input,'Q'))//write empty commands to others
			{
			if(!octFilePtr)
			{
				octFilePtr = fopen("oct_in.tmp","w+");
			}
			
			fprintf(octFilePtr,"L\n");
			 if(!hexFilePtr)
			 {
				hexFilePtr = fopen("hex_in.tmp","w+");
			 }
			 fprintf(hexFilePtr,"L\n");
			}

	    	else if(strchr(input,'O'))//write empty commands to others
			{
			if(!quadFilePtr)
			{
				quadFilePtr = fopen("quad_in.tmp","w+");
			}
			fprintf(quadFilePtr,"L\n");
			 if(!hexFilePtr)
			 {
				hexFilePtr = fopen("hex_in.tmp","w+");
			 }
			 fprintf(hexFilePtr,"L\n");
			}

			else if(strchr(input,'H'))//write empty commands to others
			{
			if(!quadFilePtr)
			{
				quadFilePtr = fopen("quad_in.tmp","w+");
			}
			fprintf(quadFilePtr,"L\n");
			 if(!octFilePtr)
			 {
				octFilePtr = fopen("oct_in.tmp","w+");
			 }
			 fprintf(octFilePtr,"L\n");
			}

			else // write empty command for all
			{
			 if(!quadFilePtr)
			{
				quadFilePtr = fopen("quad_in.tmp","w+");
			}

			fprintf(quadFilePtr,"L\n");
			 if(!octFilePtr)
			 {
				octFilePtr = fopen("oct_in.tmp","w+");
			 }
			 
			 fprintf(octFilePtr,"L\n");
			if(!hexFilePtr)
			 {
				hexFilePtr = fopen("hex_in.tmp","w+");
			 }
			 fprintf(hexFilePtr,"L\n");
			}
			last = 1;
		}

		if(strchr(input,'Q')) // New quadri
		{
			if(!quadFilePtr)
			{
				quadFilePtr = fopen("quad_in.tmp","w+");
			}
			 fprintf(quadFilePtr,"%s\n",input);
			 scanf("%s",input);
			 fprintf(quadFilePtr,"%s\n",input);
		}

		if(strchr(input,'O')) //new octagon
		{
			if(!octFilePtr)
			{
				octFilePtr = fopen("oct_in.tmp","w+");
			}
			fprintf(octFilePtr,"%s\n",input);
			scanf("%s",input);
			fprintf(octFilePtr,"%s\n",input);
			scanf("%s",input);
			fprintf(octFilePtr,"%s\n",input);
		}

		if(strchr(input,'H')) //new Hexagon
		{
			if(!hexFilePtr)
			{
				hexFilePtr = fopen("hex_in.tmp","w+");
			}
			fprintf(hexFilePtr,"%s\n",input);
			scanf("%s",input);
			fprintf(hexFilePtr,"%s\n",input);
			scanf("%s",input);
			fprintf(hexFilePtr,"%s\n",input);
		}

		if(last)
		{
			rewind(octFilePtr);
			fclose(octFilePtr);
			rewind(hexFilePtr);
			fclose(hexFilePtr);
			rewind(quadFilePtr);
			fclose(quadFilePtr);
			break;
		}
    }
}



void ReadCharactersAndSendSignals(int quadChild,int hexChild,int octChild)
{
	struct timespec req = {0,NANO_SLEEP};
	nanosleep(&req,NULL);
	char currentCh;
	FILE* charInPtr = fopen(CHARS_IN,"r+");
     while ((currentCh = fgetc(charInPtr)) != EOF)
	{
		switch (currentCh)
		{
			case 'q':
			 kill(quadChild,SIGUSR1);
			 nanosleep(&req,NULL);
			 break;

			case 'h':
		     kill(hexChild,SIGUSR1);
			 nanosleep(&req,NULL);
			 break;

			case 'o':
			 kill(octChild,SIGUSR1);
			 nanosleep(&req,NULL);
			 break;
			
			default:
			 break;

		}
	}


	kill(quadChild,SIGUSR2);
	kill(hexChild,SIGUSR2);
	kill(octChild,SIGUSR2);

	rewind(charInPtr);
	fclose(charInPtr);


}


void CheckOpen(int file)
{
     if(file == -1)
     {
         printf("failed to open file\n");
         exit(-1);
     }
}