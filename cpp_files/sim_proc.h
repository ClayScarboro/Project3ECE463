#ifndef SIM_PROC_H
#define SIM_PROC_H

using namespace std;


struct ROB{

	int state;//IF---1  ID---2  IS---3 EX---4 WB----5
	int state1,state2, opState; ///0---occupied 1--available
	int tag, list_dispatch, list_issue, list_execute, valid;
	unsigned int status;
	int src1, src2, dst;
	unsigned int if_cycle, if_dur;
	unsigned int id_cycle, id_dur;
	unsigned int is_cycle, is_dur;
	unsigned int ex_cycle, ex_dur;
	unsigned int wb_cycle, wb_dur;
	unsigned int cycle;

	unsigned int cycleCount;//judge the cycles it takes
	int entry, depend_entry1, depend_entry2;
	ROB *nextrob;
	ROB *lastrob;

};

struct RegisterFile
{
	int tag;
	int valid;
		
};

typedef struct proc_params{
    unsigned long int rob_size;
    unsigned long int iq_size;
    unsigned long int width;
	
	//storing cycle count
	int cycle;
	
	//Pipeline Registers
	vector<uint32_t> DE;
	vector<uint32_t> RN;
	vector<uint32_t> RR;
	vector<uint32_t> DI;
	vector<uint32_t> IQ;
	vector<uint32_t> execute_list;
	vector<uint32_t> WB;
	vector<uint32_t> ROB;
	
	//vector for instruction lookup
	vector< vector<uint32_t> > instTable;
	
	bool Advance_Cycle();
	void Retire();
	void Writeback();
	void Execute();
	void Issue();
	void Dispatch();
	void RegRead();
	void Rename();
	void Decode();
	bool Fetch(FILE*);
	
}proc_params;




#endif
