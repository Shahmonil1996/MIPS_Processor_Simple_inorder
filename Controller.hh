#include <iostream>
using namespace std;
class Controller{
    protected:
        int if_stall=0;
        int id_stall=0;
    public:
        void update_stall_signals(int mem_dst_reg_idx, int ex_src_idx1, int ex_src_idx2, int mem_wr_en, int is_mem_ins, int & if_stall_temp, int & id_stall_temp){
            if (((mem_dst_reg_idx == ex_src_idx1) || (mem_dst_reg_idx == ex_src_idx2)) && mem_wr_en && is_mem_ins){ //Not a store operation
                if_stall = 1;
                id_stall = 1;
                if_stall_temp = 1;
                id_stall_temp = 1;
                cout << "[CONTROL] Stalling ID and IF" << endl;
                cout << "{CONTROL DEBUG] mem_dst_reg_idx: " << mem_dst_reg_idx << " ex_src_idx1: " << ex_src_idx1 << " ex_src_idx2: " << ex_src_idx2 << " mem_wr_en: " << mem_wr_en << " is_mem_ins: " << is_mem_ins << endl; 
            }
            else{
                if_stall = 0;
                id_stall = 0;
                if_stall_temp = 0;
                id_stall_temp = 0;
                cout << "[CONTROL] unStalling ID and IF" << endl;
            }
        }
        void get_stall_signals(int & if_stall_temp, int & id_stall_temp){
            if_stall_temp = if_stall;
            id_stall_temp = id_stall;
        }
};