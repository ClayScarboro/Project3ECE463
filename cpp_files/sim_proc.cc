#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <iostream>
#include <vector>
#include "sim_proc.h"

using namespace std;

/*  argc holds the number of command line arguments
    argv[] holds the commands themselves

    Example:-
    sim 256 32 4 gcc_trace.txt
    argc = 5
    argv[0] = "sim"
    argv[1] = "256"
    argv[2] = "32"
    ... and so on
*/


int main (int argc, char* argv[])
{
	
	// DECLARATIONS
	
	char	str[5];
	FILE	*tracefile,*out;
	char*	tracename;
	char*	outputname;
	int issue_rate=0;
	char	seq_no[10];
	int		op,dst;
	int		cycle_final=0;
	int		tag=0,N=0;
	int		in_n, in_s;
	int		clk_cycle;
	int		count_rob,count_rob_id;//increment when move instr into rob[]
	int		count_FU, count_issue;
	static RegisterFile rf[100];//Register File
	double IPC;
	ROB rob[1024];
	ROB *head, *temprob, *temprob2, *tail;

	head=rob;
	tail=head;

	rob[1023].nextrob=&rob[0];
	rob[0].lastrob=&rob[1023];

	int printednum=0;
	
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	
    FILE *FP;               // File handler
    char *trace_file;       // Variable that holds trace file name;
    proc_params params;       // look at sim_bp.h header file for the the definition of struct proc_params
    int op_type, dest, src1, src2;  // Variables are read from trace file
    unsigned long int pc; // Variable holds the pc read from input file
    
    if (argc != 5)
    {
        printf("Error: Wrong number of inputs:%d\n", argc-1);
        exit(EXIT_FAILURE);
    }
    
    params.rob_size     = strtoul(argv[1], NULL, 10);
    params.iq_size      = strtoul(argv[2], NULL, 10);
    params.width        = strtoul(argv[3], NULL, 10);
	
	//Initalize cycle count to 0
	params.cycle = 0;
	
    trace_file          = argv[4];
    printf("rob_size:%lu "
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
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // The following loop just tests reading the trace and echoing it back to the screen.
    //
    // Replace this loop with the "do { } while (Advance_Cycle());" loop indicated in the Project 3 spec.
    // Note: fscanf() calls -- to obtain a fetch bundle worth of instructions from the trace -- should be
    // inside the Fetch() function.
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
	
	int traceDone = 0;
	
	
    while(printednum<10000)
	{	
	
		issue_rate=in_n+1;
		if(clk_cycle==196)
		{
			//gets(str);
		}

	int pipestate=0
	printf("CYCLE=%d,TAG=%d\n",clk_cycle,tag);
	
	//printf("TEST_BEGIN ,COUNT_ROB=%d, count_issue=%d, cycleCount=%d, CYCLE=%d\n",count_rob, count_issue, count_FU, clk_cycle);
	//gets(str);
	
	
	////////    1.FakeRetire(); WB-> OUT
	
	for(temprob=head;temprob!=tail;temprob=temprob->nextrob)
	{		
		if(head->state==6) head=head->nextrob;
	}
	
	int i = 0;
	
	
	for(temprob=head;temprob!=tail;temprob=temprob->nextrob)
	{
		if(temprob->state==5)//reach WB, completed
		{	

			i++;
			temprob->state=6;//state=6

			temprob->valid=0;

			//printf("i=%d\n",head->temp);

			temprob->wb_dur=1;


			#ifdef DEBUG_PRINT
					if(temprob2->state==6&&temprob2->tag==printednum&&printednum<10000)
		
							{
								if (temprob2->tag==10053)
								{	gets(str);	printf("STOP\n");	}

								fprintf(out,"%d fu{%d} src{%d,%d} dst{%d} IF{%d,%d} ID{%d,%d} IS{%d,%d} EX{%d,%d} WB{%d,%d}\n",temprob2->tag,temprob2->status,temprob2->src1, temprob2->src2,temprob2->dst,temprob2->if_cycle, temprob2->if_dur,
																												temprob2->id_cycle, temprob2->id_dur,temprob2->is_cycle, temprob2->is_dur,temprob2->ex_cycle, temprob2->ex_dur,
																												temprob2->wb_cycle, temprob2->wb_dur);
								if(tag>9990)
										printf("%d fu{%d} src{%d,%d} dst{%d} IF{%d,%d} ID{%d,%d} IS{%d,%d} EX{%d,%d} WB{%d,%d}\n",temprob2->tag,temprob2->status,temprob2->src1, temprob2->src2,temprob2->dst,temprob2->if_cycle, temprob2->if_dur,
																												temprob2->id_cycle, temprob2->id_dur,temprob2->is_cycle, temprob2->is_dur,temprob2->ex_cycle, temprob2->ex_dur,
																												temprob2->wb_cycle, temprob2->wb_dur);
							if (cycle_final<temprob2->wb_cycle+temprob2->wb_dur)
									cycle_final=temprob2->wb_cycle+temprob2->wb_dur;

							printf("pringted: %d temprob2->tag: %d\n",printednum,temprob2->tag);
							printednum++;
							
							temprob2=temprob2->nextrob;
							//gets(str);
					}
			#endif


			#ifdef DEBUG_PRINT1
				//while(printednum<=temprob->tag)
				{printf("%d fu{%d} src{%d,%d} dst{%d} IF{%d,%d} ID{%d,%d} IS{%d,%d} EX{%d,%d} WB{%d,%d}\n",temprob->tag,temprob->status,temprob->src1, temprob->src2,temprob->dst,temprob->if_cycle, temprob->if_dur,
																									temprob->id_cycle, temprob->id_dur,temprob->is_cycle, temprob->is_dur,temprob->ex_cycle, temprob->ex_dur,
																									temprob->wb_cycle, temprob->wb_dur);
				printednum++;
				gets(str);}
			#endif

		}
	
	}

	////////     2.Execute(); EX-> WB
	////////////////////////////LATENCY

	for(temprob=head;temprob!=tail;temprob=temprob->nextrob)
		{
			if (!temprob->cycleCount&&temprob->state==4)
			{	
				//if((temprob->lastrob==NULL)||((temprob->src1==-1||temprob->lastrob->dst!=temprob->src1)&&(temprob->src2==-1||temprob->lastrob->dst!=temprob->src2)&&(temprob->lastrob->state!=3)&&(temprob->lastrob->src1==-1||rf[temprob->lastrob->src1]==1)&&(temprob->lastrob->src2==-1||rf[temprob->lastrob->src2]==1)))
				{
				//printf("I'M HERE....");
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


				temprob->opState=1;//oprand ready
				temprob->wb_cycle=clk_cycle;
				temprob->ex_dur=(temprob->wb_cycle - temprob->ex_cycle);
				}
			}
		else if(temprob->state==4)
				temprob->cycleCount--;//depend on op type
	


	}
/////////////    3.Issue();IS-> EX
////////////////////////////////////////DEPENDENCY &&  MAX=N+1
	//for(k=0;k<34;k++)		printf("rf[%d]=%d  ",k, rf[k]);////Register File

		for(temprob=head;temprob!=tail;temprob=temprob->nextrob)
		{
			//if(pipestate==1)
			if((pipestate==1&&count_FU&&temprob->state==3)||(pipestate==0&&temprob->state==3&&issue_rate))//
				{
					//printf("\ntag=%d rf[src1]=rf[%d]=%d,rf[src2]=rf[%d]=%d\n",temprob->tag, temprob->src1,rf[temprob->src1],temprob->src2,rf[temprob->src2]);
					if((rob[temprob->depend_entry1].opState||temprob->state1)&&(rob[temprob->depend_entry2].opState||temprob->state2))
					{	
				
						issue_rate--;
						count_FU--;
						temprob->cycleCount--;
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
	//printf("count_rob=%d, count_rob_id=%d\n",count_rob,count_rob_id);
	
			while(count_rob&&count_rob_id)
			{
		
					count_rob--;
					count_rob_id--;
					fscanf(tracefile,"%s %d %d %d %d\n",&seq_no, &op,&dst,&src1,&src2);
					//printf("N=%d  %d\n",tag,op);
					tail->status=op;
					if (tail->status==0)	tail->cycleCount=1;
					else if(tail->status==1) tail->cycleCount=2;
					else if(tail->status==2) tail->cycleCount=5;

					tail->tag=tag;
					tail->src1=src1;
					tail->src2=src2;
					tail->dst=dst;
					tail->if_cycle=clk_cycle;
					tail->id_cycle=clk_cycle + 1;
					tail->if_dur=1;
					tail->state=1;//IF
					


					
					
					tail->opState=0; //not completed
					

					if ( !rf[tail->src1].valid && tail->src1!=-1) 
						{
									tail->depend_entry1=rf[tail->src1].tag; 
									tail->state1 = 0;//occupied by others
						}
						else if(rf[tail->src1].valid || tail->src1==-1) 
							{
								tail->state1=1;
								tail->depend_entry1=tail->entry;
							}


					if(!rf[tail->src2].valid && tail->src2!=-1) 
						{
									tail->depend_entry2=rf[tail->src2].tag;// else  tail->depend_entry2=0;
									tail->state2 = 0;
						}
						else if(rf[tail->src2].valid || tail->src2==-1) 
								{
									tail->state2=1;
									tail->depend_entry2=tail->entry;
								}

					rf[tail->dst].tag = tail->entry;//entry means the entry of ROB
					rf[tail->dst].valid = 0;
					#ifdef DEBUG_FPRINT
						fprintf(out,"%d %d %d %d\n",op,dst,src1,src2);
					#endif
					tag++;
					tail=tail->nextrob;
			}
	
	//for(temprob=head;temprob!=tail;temprob=temprob->nextrob)		printf("tag=%d temprob=%d STATE= %d\n",temprob->tag, temprob, temprob->state);
		//printf("HEAD= %d  TAIL= %d temprob=%d STATE= %d\n", head, tail, temprob, temprob->state);

	clk_cycle++;
	//printf("END_OF_TEST, TAIL= %d\n",tail);
	//gets(str);
}
	

	IPC=(double)printednum/(double)cycle_final;
	
	printf("number of instructions = %d\nnumber of cycles       = %d\nIPC                    = %1.5f",printednum,cycle_final,IPC);
	fprintf(out,"number of instructions = %d\nnumber of cycles       = %d\nIPC                    = %1.5lf",printednum,cycle_final,IPC);
	fclose(out);

	fclose(tracefile);
	
	getchar();
	return(0);


}
