#include <iostream>
using namespace std;
class ex_mem_pipeline{
    protected:
        int ex_data=0;
        int dst_reg_idx=0;
        int is_mem=0;
        int rd_data1=0;
        int is_wr_en=0;
        int idx_reg1=0;
        int idx_reg2=0;
    public:

        void get_pipeline_regs(int & ex_data_temp, int & dst_reg_idx_temp, int & is_mem_temp, int & rd_data1_temp, int & is_wr_en_temp, int & idx_reg1_temp, int & idx_reg2_temp){
            ex_data_temp  = ex_data;
            dst_reg_idx_temp = dst_reg_idx;
            is_mem_temp = is_mem;
            rd_data1_temp = rd_data1;
            is_wr_en_temp = is_wr_en;
            idx_reg1_temp = idx_reg1;
            idx_reg2_temp = idx_reg2;
        }

        void update_pipeline(int ex_data_updt, int dst_reg_idx_updt, int is_mem_updt, int rd_data1_updt, int is_wr_en_updt, int idx_reg1_updt, int idx_reg2_updt, int ex_stall){
            if(!ex_stall) ex_data = ex_data_updt;
            if(!ex_stall) dst_reg_idx = dst_reg_idx_updt;
            if(!ex_stall) is_mem = is_mem_updt;
            if(!ex_stall) rd_data1 = rd_data1_updt;
            if(!ex_stall) is_wr_en = is_wr_en_updt;
            if(!ex_stall) idx_reg1 = idx_reg1_updt;
            if(!ex_stall) idx_reg2 = idx_reg2_updt;
            cout << "[EX/MEM PIPELINE] ex_data: " << ex_data << " dst_reg_idx: " << dst_reg_idx << " is_mem: " << is_mem << " rd_data1 : " << rd_data1 << " is_wr_en: " << is_wr_en << " idx_reg1: " << idx_reg1 << " idx_reg2: " << idx_reg2 << endl;
        }
};