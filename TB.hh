#include <iostream>
#include <Execute.hh>
using namespace std;
class TB{
    protected:
        int ins_mem[100];
        int dat_mem[100];
        int reg_file[32];
        int idx_rs=0;
        int idx_rt=0;
        int opcode=0;
        int idx_rd=0;
        int rd_data1=0;
        int rd_data2=0;
        int wr_en=0;
        int shift_amt=0;
        int funct=0;
        int imm_data=0;
        int trgt_addr=0;
        int imm=0;
        int ins = 0;
        int ex_output = 0;
        int mem_rd_data=0;
        Execute exec_obj;
    public:
        
        TB(){
            // for(int i = 0; i < 100; i+=2){
            //     ins_mem[i] = (0x8FE10000); //LW R1, 0(R31) ...
            //     ins_mem[i+1] = 0x210821; // Add R1, R1, R1
            // } 
            for(int i = 0; i < 100; i++){
                //if(i == 1)
                    //ins_mem[i] = 0x210821; // Add R1, R1, R1
                    //ins_mem[i] = 0x8C200000; // LW R0, 0(R1)
                    //ins_mem[i] = 0x8FE00000; // LW R0, 0(R31)
                     ins_mem[i] = (0x8FE0+i) << 16; //LW R0, 0(R31) --> LW R1, 0(R31) --> LW R2, 0(R31) ...
                    //ins_mem[i] = 0xAFE00000; // ST R0, 0(R31)
                    //ins_mem[i] = (0xAFE0+i) << 16;; // //ST R0, 0(R31) --> ST R1, 0(R31) --> ST R2, 0(R31) ...
                //else
                //   ins_mem[i] = 0x4000C41;
            }
            for(int i = 0; i < 100; i++){
                dat_mem[i] = i;
            } 
            for (int i = 0; i < 32; i++){
                reg_file[i] = i;
            }       
        }
        void run_cpu_tb(int cycles){
            for(int i = 0; i < cycles; i++){
                ins = ins_mem[i];
                idx_rs = (ins>>21) & 31;
                idx_rt = (ins>>16) & 31;
                idx_rd = (ins>>11) & 31;
                opcode = (ins>>26) & 63;
                funct =  (ins & 63);
                shift_amt = (ins >> 6) & 31;

                wr_en = (opcode == 0 || opcode == 35); //In case of load or r type
                rd_data1 = reg_file[idx_rs];
                rd_data2 = reg_file[idx_rt];
                imm = (ins & 0xFFFF);
                idx_rd = (opcode == 35 || opcode == 43) ? idx_rt : idx_rd;
                exec_obj.alu(rd_data1, rd_data2, opcode, ex_output, shift_amt, funct, idx_rd, imm); 
                cout << "opcode: " << opcode << " wr_en: " << wr_en << " ex_output: " << ex_output << endl;
                if(opcode == 35){
                    if(ex_output > 100){
                        mem_rd_data =  0;
                    }
                    else  {  
                        mem_rd_data = dat_mem[ex_output];
                    }
                }
                else if(opcode == 43){
                    if(i < cycles-1){ // Any stores before the final cycle will commit to memory
                        if(ex_output < 100){
                            dat_mem[ex_output] = rd_data2;
                        }
                    }
                }
                else{
                    mem_rd_data = ex_output;
                }
                if(i < cycles-4){ // Last 4 values will not be written into Reg File as simulation will finish before it
                    if(wr_en){
                        reg_file[idx_rd] = mem_rd_data;
                        cout << "Writing data to register file at location : " << idx_rd << "with data: "  << mem_rd_data << endl;
                    }
                }
            }
        }
        int check_dat_mem(int golden[]){
            for(int i = 0; i < 100; i++){
                if(dat_mem[i] != golden[i]){
                    cout << " Failed something here golden : " << golden[i] << " reference[i] : " << dat_mem[i] << " for location : " << i << endl;
                    return false;
                }
            }
            return true;
        }
        int check_reg_file(int golden[]){
            for(int i = 0; i < 32; i++){
                if(reg_file[i] != golden[i]){
                    cout << " Failed something here golden : " << golden[i] << " reference[i] : " << reg_file[i] << " for location : " << i << endl;
                    return false;
                }
            }
            return true;
        }
        int check_reg_file(){
            return true;
        }
};