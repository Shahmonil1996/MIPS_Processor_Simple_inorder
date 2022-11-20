#include <iostream>
using namespace std;
class mem_wb_pipeline{
    protected:
        int rd_data;
        int dst_reg_idx;
        int mem_wr_en;
    public:
        void update_pipeline(int dst_reg_idx_updt, int rd_data_updt, int mem_wr_en_updt, int mem_stall){
            if(!mem_stall) rd_data = rd_data_updt;
            if(!mem_stall) dst_reg_idx = dst_reg_idx_updt;
            if(!mem_stall) mem_wr_en = mem_wr_en_updt;
            cout << "[MEM/WB PIPELINE] rd_data: " << rd_data << " dst_reg_idx: " << dst_reg_idx << " mem_wr_en: " << mem_wr_en << endl;
        }
        void get_pipeline_regs(int & dst_reg_idx_temp, int & rd_data_temp, int & mem_wr_en_temp){
            rd_data_temp = rd_data;
            dst_reg_idx_temp = dst_reg_idx;
            mem_wr_en_temp = mem_wr_en;
        }
};