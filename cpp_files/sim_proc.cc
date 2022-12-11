#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <iostream>
#include <vector>
#include "sim_proc.h"

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
    do {
		params.Fetch();
		
		
		
		
	}
	while (Advance_Cycle());

    return 0;
}

bool proc_params::Advance_Cycle(){
	++cycle;
	//if fscanf() == NULL, RETURN FALSE;
	
	return true
}

void proc_params::Fetch(FP){
	unsigned char pc, op, destReg, srcReg1, srcReg2;
	vector<uint32_t> toAdd;
	
	while(DE.size() < width){
		if(5 != fscanf(FP, "%x %x %x %x %x\n", &pc, &op, &destReg, &srcReg1, &srcReg2)){
				//NOTHING LEFT TO READ; DO NOTHING
				return;
		}
		
		//for instruction table
		toAdd.push_back(pc);
		toAdd.push_back(op);
		toAdd.push_back(destReg);
		toAdd.push_back(srcReg1);
		toAdd.push_back(srcReg2);
		instTable.push_back(toAdd);
		
		//adding DE
		DE.push_back(pc);
	}
	
	//DE is filled, we won, GET OUT OF THERE SOLIDER!!!
	return;
	
}
