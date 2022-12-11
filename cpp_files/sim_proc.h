#ifndef SIM_PROC_H
#define SIM_PROC_H

typedef struct proc_params{
    unsigned long int rob_size;
    unsigned long int iq_size;
    unsigned long int width;
	
	//storing cycle count
	int cycle;
	
	//Pipeline Registers
	std::vector<uint32_t> DE;
	std::vector<uint32_t> RN;
	std::vector<uint32_t> RR;
	std::vector<uint32_t> DI;
	std::vector<uint32_t> IQ;
	std::vector<uint32_t> execute_list;
	std::vector<uint32_t> WB;
	std::vector<uint32_t> ROB;
	
	//vector for instruction lookup
	std::vector<vector<uint32_t>> instTable;
	
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
