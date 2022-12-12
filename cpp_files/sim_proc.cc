#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "sim_proc.h"
#define DEBUG_PRINT

struct myROB{

	int state;//IF---1  ID---2  IS---3 EX---4 WB----5
	int src_state1,src_state2, oprand_state; ///0---occupied 1--available
	int tag;

	int list_dispatch;
	int list_issue;
	int list_execute;//	dispatch_list---1   issue_list----2 execute_list----3

	int valid;
	unsigned int fu_type;
	int src1, src2, dst;
	unsigned int if_cycle, if_dur;
	unsigned int id_cycle, id_dur;
	unsigned int is_cycle, is_dur;
	unsigned int ex_cycle, ex_dur;
	unsigned int wb_cycle, wb_dur;
	unsigned int i, cycle;

	unsigned int count_ex;//judge the cycles it takes
	int entry;
	int depend_entry1, depend_entry2;
	myROB *nextrob;
	myROB *lastrob;

};

struct RegisterFile
{
	int tag;
	int valid;
		
};



int main (int argc, char* argv[])


{

	
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
	int		count_rob,count_rob_id;//increment when move instr into rob[]
	int		count_FU, count_issue;
	static RegisterFile rf[100];//Register File
	double IPC;
	myROB rob[params.rob_size];
	myROB *head, *temprob, *temprob2, *tail;

	head=rob;
	tail=head;

	rob[params.rob_size - 1].nextrob=&rob[0];
	rob[0].lastrob=&rob[params.rob_size - 1];

	int printednum=0;
		 
/////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////Initializing
/////////////////////////////////////////////////////////////////////////////////////////
		   for(i=0;i<params.rob_size - 1;i++)
		   {
				rob[i+1].lastrob=&rob[i];
				rob[i].nextrob=&rob[i+1];
				
		   }
		   
		   
		   for(i=0;i<params.rob_size;i++)
		   {
				
				rob[i].valid=1;
				//rob[i].temp=i;
				rob[i].list_dispatch=0;
				rob[i].list_issue=0;
				rob[i].list_execute=0;
				rob[i].entry=i;
				rob[i].oprand_state=1;
		   }
			
		   for(j=0;j<100;j++)
				{
					rf[j].valid=1;
				}

		   clk_cycle=0;
		   count_rob=0;
		   count_rob_id=0;
		   
/////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////Read_In File
/////////////////////////////////////////////////////////////////////////////////////////
	
	in_s=256;//2
	in_n=8;//8
	
	int pipestate=0;//0--pipe   1-nonpipe

	// Open trace_file in read mode
    printf("params.rob_size:%lu "
            "iq_size:%lu "
            "width:%lu "
            "tracefile:%s\n", params.rob_size, params.iq_size, params.width, trace_file);
    // Open trace_file in read mode
    FP = fopen(trace_file, "r");
    if(FP == NULL)
    {
        // Throw error and exit if fopen() failed
        printf("Error: Unable to open file %s\n", trace_file);
        exit(EXIT_FAILURE);
    }

	outputname="myoutput_256_8_gcc.txt";
	out=fopen(outputname, "w");
	if(!out) {printf("cannot open this out file\n");exit(0);}

	//myInstr instr[9999];
	count_issue = in_s;
	count_FU=in_n+1;
	count_rob=in_n;
	count_rob_id=in_n*2;
	temprob2=head;
	head->lastrob=NULL;
	int issue_rate=0;

/////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////Cycle begins
/////////////////////////////////////////////////////////////////////////////////////////
	
	//while(!feof(FP)||count_rob) //ONE clk cycle begins
while(printednum<10000)
	{	
	
		issue_rate=in_n+1;
		if(clk_cycle==196)
		{
			//gets(str);
		}


	
	
	
	
	
	////////    1.FakeRetire(); WB-> OUT
	
	for(temprob=head;temprob!=tail;temprob=temprob->nextrob)
	{		
		if(head->state==6) head=head->nextrob;
	}
	
	for(temprob=head;temprob!=tail;temprob=temprob->nextrob)
	{
		if(temprob->state==5)//reach WB, completed
		{	

			i++;
			temprob->state=6;//state=6

			temprob->valid=0;

			

			temprob->wb_dur=1;


			#ifdef DEBUG_PRINT
					if(temprob2->state==6&&temprob2->tag==printednum&&printednum<10000)
		
							{
								if (temprob2->tag==10053)
								{	gets(str);	printf("STOP\n");	}

				
								if(tag>9990)
										
							if (cycle_final<temprob2->wb_cycle+temprob2->wb_dur)
									cycle_final=temprob2->wb_cycle+temprob2->wb_dur;

							
							printednum++;
							
							temprob2=temprob2->nextrob;
							//gets(str);
					}
			#endif


			#ifdef DEBUG_PRINT1
				//while(printednum<=temprob->tag)
				
				printednum++;
				gets(str);}
			#endif

		}
	
	}

	////////     2.Execute(); EX-> WB
	////////////////////////////LATENCY

	for(temprob=head;temprob!=tail;temprob=temprob->nextrob)
		{
			if (!temprob->count_ex&&temprob->state==4)
			{	
				
				{
				
				temprob->list_execute=0;
				temprob->state=5;//state=5
				count_FU++;
				
				
			if(temprob->dst!=-1)
						{
									if(temprob->entry==rf[temprob->dst].tag) 
									{
											rf[temprob->dst].valid=1; //tag match
									}
						}


				temprob->oprand_state=1;//oprand ready
				temprob->wb_cycle=clk_cycle;
				temprob->ex_dur=(temprob->wb_cycle - temprob->ex_cycle);
				}
			}
		else if(temprob->state==4)
				temprob->count_ex--;//depend on op type
	


	}
/////////////    3.Issue();IS-> EX
////////////////////////////////////////DEPENDENCY &&  MAX=N+1

		for(temprob=head;temprob!=tail;temprob=temprob->nextrob)
		{
			
			if((pipestate==1&&count_FU&&temprob->state==3)||(pipestate==0&&temprob->state==3&&issue_rate))//
				{
					
					if((rob[temprob->depend_entry1].oprand_state||temprob->src_state1)&&(rob[temprob->depend_entry2].oprand_state||temprob->src_state2))
					{	
				
						issue_rate--;
						count_FU--;
						temprob->count_ex--;
						temprob->list_issue=0;
						temprob->list_execute=1;
						temprob->state=4;//state=4
						count_issue++;
						temprob->ex_cycle=clk_cycle;
						temprob->is_dur=(temprob->ex_cycle - temprob->is_cycle);
					}
	
				}
	
		}


/////////////    4.Dispatch(); ID->IS
///////////////////////////////////////////S IS FULL OR NOT
	for(temprob=head;temprob!=tail;temprob=temprob->nextrob)
	{
	if(count_issue&&temprob->state==2)
		{
			count_issue--;
			count_rob_id++;
			temprob->list_dispatch=0;
			temprob->list_issue=1;
			temprob->state=3; //state=3
			temprob->is_cycle=clk_cycle;
			temprob->id_dur=(temprob->is_cycle - temprob->id_cycle);
			//if(temprob->dst!=-1) rf[temprob->dst]=0;
			
		}

	}
/////////////   5.Fetch(); IF->ID
	for(temprob=head;temprob!=tail;temprob=temprob->nextrob)
	 {
		 if(count_rob_id&&temprob->state==1)
			{
				temprob->list_dispatch=1;
				//if(temprob->dst!=-1) rf[temprob->dst].valid=0; 
				count_rob++;
				temprob->state=2;//state=2
			}

	}

	

/////////////////////////   6. IN ->IF

	
			while(count_rob&&count_rob_id)
			{
		
					count_rob--;
					count_rob_id--;
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
					tail->state=1;//IF
					


					
					
					tail->oprand_state=0; //not completed
					

					if ( !rf[tail->src1].valid && tail->src1!=-1) 
						{
									tail->depend_entry1=rf[tail->src1].tag; 
									tail->src_state1 = 0;//occupied by others
						}
						else if(rf[tail->src1].valid || tail->src1==-1) 
							{
								tail->src_state1=1;
								tail->depend_entry1=tail->entry;
							}


					if(!rf[tail->src2].valid && tail->src2!=-1) 
						{
									tail->depend_entry2=rf[tail->src2].tag;// else  tail->depend_entry2=0;
									tail->src_state2 = 0;
						}
						else if(rf[tail->src2].valid || tail->src2==-1) 
								{
									tail->src_state2=1;
									tail->depend_entry2=tail->entry;
								}

					rf[tail->dst].tag = tail->entry;//entry means the entry of ROB
					rf[tail->dst].valid = 0;
					#ifdef DEBUG_FPRINT
						
					#endif
					tag++;
					tail=tail->nextrob;
			}
	
	

	clk_cycle++;
}
	

	IPC=(double)printednum/(double)cycle_final;
	
	printf("number of instructions = %d\nnumber of cycles       = %d\nIPC                    = %1.5f",printednum,cycle_final,IPC);
	fprintf(out,"number of instructions = %d\nnumber of cycles       = %d\nIPC                    = %1.5lf",printednum,cycle_final,IPC);
	fclose(out);

	fclose(FP);
	
	getchar();
	return(0);


}