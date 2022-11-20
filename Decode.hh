#include <iostream>
using namespace std;
class Decode{
    protected:
        int reg_file[32];
        int idx_rs;
        int idx_rt;
        int opcode;
        int idx_rd;
        int rd_data1;
        int rd_data2;
        int wr_en;
        int shift_amt;
        int funct;
        int imm_data;
        int trgt_addr;
        int imm;
    public:
        int decode_valid = 1;
        int decode_flush = 0;
        int debug_verbosity = 4;

        Decode(){
            for (int i = 0; i < 32; i++){
                reg_file[i] = i;
            }
        }
        void decode_ins(int ins){
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


            if(debug_verbosity > 3) {
                cout << "[DECODE] idx_rs : " << idx_rs << " idx_rt: " << idx_rt << " idx_rd : " << idx_rd << " opcode : " << opcode << " rd_data1 : " << rd_data1 << " rd_data2: " << rd_data2 << " wr_en: " << wr_en 
                << " funct: " << funct << " shift_amt: " << shift_amt << " imm : " << imm << endl;
            }
        }
        void get_decoded_ins(int & rd_data_temp1, int & rd_data_temp2, int & opcode_temp, int & dst_reg_idx_temp, int & shift_amt_temp, int & funct_temp, int & imm){
            rd_data_temp1 = decode_flush ? 0 : rd_data1;
            rd_data_temp2 = decode_flush ? 0 : rd_data2;
            opcode_temp   = decode_flush ? 0 : opcode;
            dst_reg_idx_temp = decode_flush ? 0 : (opcode == 35 || opcode == 43) ? idx_rt : idx_rd;
            shift_amt_temp = decode_flush ? 0 : shift_amt;
            funct_temp = decode_flush ? 0 : funct;
            imm = decode_flush ? 0 : imm;
        }
        void write(int idx, int data, int wr_en){
            if(wr_en==1) { 
                reg_file[idx] = data;
                    if(debug_verbosity > 3) {
                        cout << "[DECODE] Wrote data : " << data << " at idx: " << idx << endl;
                }
            }
        }
        void stall(){
            decode_valid = 0;
        }
        void clear_stall(){
            decode_valid = 1;
        }
        void clear_pipeline(){
            decode_flush = 1;
        }
        void resume_pipeline(){
            decode_flush = 0;
        }
        void control_signals(int & is_mem_temp, int & wr_en_temp, int & idx_rs_temp, int & idx_rt_temp){
            is_mem_temp = (opcode & 63);
            wr_en_temp = wr_en;
            idx_rs_temp = idx_rs;
            idx_rt_temp = idx_rt;
        }
};