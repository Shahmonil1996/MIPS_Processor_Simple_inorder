#include <iostream>
using namespace std;
class id_ex_pipeline{
    protected:
        int rd_data1=0;
        int rd_data2=0;
        int opcode=0;
        int dst_reg_idx=0;
        int is_mem=0;
        int is_wr_en=0;
        int src_idx1=0;
        int src_idx2=0;
        int id_funct=0;
        int id_shift_amt=0;
        int id_imm=0;
    public:

        void get_pipeline_regs1(int & rd_data_temp1, int & rd_data_temp2, int & opcode_temp, int & is_mem_temp, int & dst_reg_idx_temp,int & is_wr_en_temp){
            rd_data_temp1 = rd_data1;
            rd_data_temp2 = rd_data2;
            opcode_temp   = opcode;
            dst_reg_idx_temp = dst_reg_idx;
            is_mem_temp = is_mem;
            is_wr_en_temp = is_wr_en;
        }
        void get_pipeline_regs2(int & idx1_temp, int & idx2_temp, int & id_shift_amt_temp, int & id_funct_temp, int & id_imm_temp){
            idx1_temp = src_idx1;
            idx2_temp = src_idx2;
            id_shift_amt_temp = id_shift_amt;
            id_funct_temp = id_funct;
            id_imm_temp = id_imm;
        }
        void update_pipeline(int rd_data_up1, int rd_data_up2, int opcode_updt, int dst_reg_idx_updt, int is_mem_updt, int id_stall){
            if(!id_stall) rd_data1 = rd_data_up1;
            if(!id_stall) rd_data2 = rd_data_up2;
            if(!id_stall) opcode   = opcode_updt;
            if(!id_stall) dst_reg_idx = dst_reg_idx_updt;
            if(!id_stall) is_mem = is_mem_updt;
            //if(!id_stall) is_wr_en = is_wr_en_updt;
            cout << "[ID/EX PIPELINE] rd_data1: " << rd_data1 << " rd_data2: " << rd_data2 << " opcode: " << opcode << " dst_reg_idx: " << dst_reg_idx << " is_mem: " << is_mem << endl;
        }
        void update_pipeline2(int is_wr_en_updt, int id_idx1_updt, int id_idx2_updt, int id_shift_amt_updt, int id_funct_updt, int id_imm_updt, int id_stall){
            if(!id_stall) is_wr_en = is_wr_en_updt;
            if(!id_stall) src_idx1 = id_idx1_updt;
            if(!id_stall) src_idx2 = id_idx2_updt;
            if(!id_stall) id_shift_amt = id_shift_amt_updt;
            if(!id_stall) id_funct = id_funct_updt;
            if(!id_stall) id_imm = id_imm_updt;
            cout << "[ID/EX PIPELINE] is_wr_en: " << is_wr_en << " src_idx1: " << src_idx1 << " src_idx2: " << src_idx2 << " id_shift_amt: "<< id_shift_amt << " id_funct: " << id_funct << " id_imm: " << id_imm << endl;
        }
};