#ifndef SIM_PROC_H
#define SIM_PROC_H

using namespace std;

typedef struct proc_params{
    unsigned long int rob_size;
    unsigned long int iq_size;
    unsigned long int width;
	
	//storing cycle count
	int cycle;
	
	//Pipeline Registers
	vector<int> DE;
	vector<int> RN;
	vector<int> RR;
	vector<int> DI;
	vector<int> IQ;
	vector<int> execute_list;
	vector<int> WB;
	vector<int> ROB;
	
	//vector for instruction lookup
	vector<vector<int>> instTable;
	
	bool Advance_Cycle();
	void Retire();
	void Writeback();
	void Execute();
	void Issue();
	void Dispatch();
	void RegRead();
	void Rename();
	void Decode();
	void Fetch(FILE);
	
}proc_params;


#endif
