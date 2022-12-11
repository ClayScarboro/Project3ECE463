#ifndef SIM_PROC_H
#define SIM_PROC_H

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
	vector<vector<uint32_t>> instTable;
	
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
