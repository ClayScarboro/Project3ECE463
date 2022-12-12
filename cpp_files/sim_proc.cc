#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "sim_proc.h"
#define DEBUG_PRINT

struct MAINROB{

	int state;
	int src_state1,src_state2, oprand_state;
	int tag;

	int list_dispatch;
	int list_issue;
	int list_execute;

	int valid;
	unsigned int fu_type;
	int src1, src2, dst;
	unsigned int if_cycle, if_dur;
	unsigned int id_cycle, id_dur;
	unsigned int is_cycle, is_dur;
	unsigned int ex_cycle, ex_dur;
	unsigned int wb_cycle, wb_dur;
	unsigned int i, cycle;

	unsigned int count_ex;
	int entry;
	int depend_entry1, depend_entry2;
	MAINROB *nextROB;
	MAINROB *lastROB;

};

struct regFile
{
	int tag;
	int valid;
		
};



int main (int argc, char* argv[]){	
	int i,j,k;
	char	str[5];
	FILE	*FP,*out;
	char*	trace_file;
	proc_params params;
	char*	outputname;
	
	params.rob_size     = strtoul(argv[1], NULL, 10);
    params.iq_size      = strtoul(argv[2], NULL, 10);
    params.width        = strtoul(argv[3], NULL, 10);
    trace_file          = argv[4];
	

	char	seq_no[10];
	int		op,dst,src1,src2;
	int		cycle_final=0;
	int		tag=0,N=0;
	int		in_n, in_s;
	int		clk_cycle;
	int		count_ROB,count_ROB_id;
	int		count_FU, count_issue;
	static regFile rf[100];
	double IPC;
	MAINROB ROB[params.rob_size];
	MAINROB *head, *tempROB, *tempROB2, *tail;

	head=ROB;
	tail=head;

	ROB[params.rob_size - 1].nextROB=&ROB[0];
	ROB[0].lastROB=&ROB[params.rob_size - 1];

	int printednum=0;
		 

		   for(i=0;i<params.rob_size - 1;i++)
		   {
				ROB[i+1].lastROB=&ROB[i];
				ROB[i].nextROB=&ROB[i+1];
				
		   }
		   
		   
		   for(i=0;i<params.rob_size;i++)
		   {
				
				ROB[i].valid=1;
				ROB[i].list_dispatch=0;
				ROB[i].list_issue=0;
				ROB[i].list_execute=0;
				ROB[i].entry=i;
				ROB[i].oprand_state=1;
		   }
			
		   for(j=0;j<100;j++)
				{
					rf[j].valid=1;
				}

		   clk_cycle=0;
		   count_ROB=0;
		   count_ROB_id=0;
		   

	
	in_s=256;
	in_n=8;
	
	int pipestate=0;

	
    printf("params.rob_size:%lu "
            "iq_size:%lu "
            "width:%lu "
            "tracefile:%s\n", params.rob_size, params.iq_size, params.width, trace_file);
   
    FP = fopen(trace_file, "r");
    if(FP == NULL)
    {
        
        printf("Error: Unable to open file %s\n", trace_file);
        exit(EXIT_FAILURE);
    }

	outputname="myoutput_256_8_gcc.txt";
	out=fopen(outputname, "w");
	if(!out) {printf("cannot open this out file\n");exit(0);}


	count_issue = in_s;
	count_FU=in_n+1;
	count_ROB=in_n;
	count_ROB_id=in_n*2;
	tempROB2=head;
	head->lastROB=NULL;
	int issue_rate=0;


	
	//while(!feof(FP)||count_ROB) //ONE clk cycle begins
while(printednum<10000)
	{	
	
		issue_rate=in_n+1;
		if(clk_cycle==196)
		{
			//gets(str);
		}


	
	
	
	
	

	
	for(tempROB=head;tempROB!=tail;tempROB=tempROB->nextROB)
	{		
		if(head->state==6) head=head->nextROB;
	}
	
	for(tempROB=head;tempROB!=tail;tempROB=tempROB->nextROB)
	{
		if(tempROB->state==5)
		{	

			i++;
			tempROB->state=6;

			tempROB->valid=0;

			

			tempROB->wb_dur=1;


			#ifdef DEBUG_PRINT
					if(tempROB2->state==6&&tempROB2->tag==printednum&&printednum<10000)
		
							{
								if (tempROB2->tag==10053)
								{	gets(str);	printf("STOP\n");	}

				
								if(tag>9990)
										
							if (cycle_final<tempROB2->wb_cycle+tempROB2->wb_dur)
									cycle_final=tempROB2->wb_cycle+tempROB2->wb_dur;

							
							printednum++;
							
							tempROB2=tempROB2->nextROB;
							
					}
			#endif


			#ifdef DEBUG_PRINT1
				
				
				printednum++;
				gets(str);}
			#endif

		}
	
	}



	for(tempROB=head;tempROB!=tail;tempROB=tempROB->nextROB)
		{
			if (!tempROB->count_ex&&tempROB->state==4)
			{	
				
				{
				
				tempROB->list_execute=0;
				tempROB->state=5;
				count_FU++;
				
				
			if(tempROB->dst!=-1)
						{
									if(tempROB->entry==rf[tempROB->dst].tag) 
									{
											rf[tempROB->dst].valid=1; 
									}
						}


				tempROB->oprand_state=1;
				tempROB->wb_cycle=clk_cycle;
				tempROB->ex_dur=(tempROB->wb_cycle - tempROB->ex_cycle);
				}
			}
		else if(tempROB->state==4)
				tempROB->count_ex--;
	


	}


		for(tempROB=head;tempROB!=tail;tempROB=tempROB->nextROB)
		{
			
			if((pipestate==1&&count_FU&&tempROB->state==3)||(pipestate==0&&tempROB->state==3&&issue_rate))//
				{
					
					if((ROB[tempROB->depend_entry1].oprand_state||tempROB->src_state1)&&(ROB[tempROB->depend_entry2].oprand_state||tempROB->src_state2))
					{	
				
						issue_rate--;
						count_FU--;
						tempROB->count_ex--;
						tempROB->list_issue=0;
						tempROB->list_execute=1;
						tempROB->state=4;
						count_issue++;
						tempROB->ex_cycle=clk_cycle;
						tempROB->is_dur=(tempROB->ex_cycle - tempROB->is_cycle);
					}
	
				}
	
		}



	for(tempROB=head;tempROB!=tail;tempROB=tempROB->nextROB)
	{
	if(count_issue&&tempROB->state==2)
		{
			count_issue--;
			count_ROB_id++;
			tempROB->list_dispatch=0;
			tempROB->list_issue=1;
			tempROB->state=3; 
			tempROB->is_cycle=clk_cycle;
			tempROB->id_dur=(tempROB->is_cycle - tempROB->id_cycle);
		
			
		}

	}

	for(tempROB=head;tempROB!=tail;tempROB=tempROB->nextROB)
	 {
		 if(count_ROB_id&&tempROB->state==1)
			{
				tempROB->list_dispatch=1;
			
				count_ROB++;
				tempROB->state=2;
			}

	}

	



	
			while(count_ROB&&count_ROB_id)
			{
		
					count_ROB--;
					count_ROB_id--;
					fscanf(FP,"%s %d %d %d %d\n",&seq_no, &op,&dst,&src1,&src2);
					
					tail->fu_type=op;
					if (tail->fu_type==0)	tail->count_ex=1;
					else if(tail->fu_type==1) tail->count_ex=2;
					else if(tail->fu_type==2) tail->count_ex=5;

					tail->tag=tag;
					tail->src1=src1;
					tail->src2=src2;
					tail->dst=dst;
					tail->if_cycle=clk_cycle;
					tail->id_cycle=clk_cycle + 1;
					tail->if_dur=1;
					tail->state=1;
					


					
					
					tail->oprand_state=0;
					

					if ( !rf[tail->src1].valid && tail->src1!=-1) 
						{
									tail->depend_entry1=rf[tail->src1].tag; 
									tail->src_state1 = 0;
						}
						else if(rf[tail->src1].valid || tail->src1==-1) 
							{
								tail->src_state1=1;
								tail->depend_entry1=tail->entry;
							}


					if(!rf[tail->src2].valid && tail->src2!=-1) 
						{
									tail->depend_entry2=rf[tail->src2].tag;
									tail->src_state2 = 0;
						}
						else if(rf[tail->src2].valid || tail->src2==-1) 
								{
									tail->src_state2=1;
									tail->depend_entry2=tail->entry;
								}

					rf[tail->dst].tag = tail->entry;
					rf[tail->dst].valid = 0;
					#ifdef DEBUG_FPRINT
						
					#endif
					tag++;
					tail=tail->nextROB;
			}
	
	

	clk_cycle++;
	
	
	}
	

	IPC=(double)printednum/(double)cycle_final;
	
	printf("Dynamic Instruction Count = %d\nCycles       = %d\nInstructions Per Cycle (IPC) = %1.2f\n",printednum,cycle_final,IPC);
	

	return 0;


}