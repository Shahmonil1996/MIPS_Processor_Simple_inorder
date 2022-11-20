#include <iostream>
using namespace std;

class Forward{

    public:
        void exstart_fwd(int ex_dst_reg_idx, int mem_dst_reg_idx, int id_src_reg_idx, int ex_output, int mem_output, int id_reg_file_read_data, int & final_ex_input, int id_ex_wr_en, int ex_mem_is_wr_en){
            if((ex_dst_reg_idx == id_src_reg_idx) && id_ex_wr_en){
                final_ex_input = ex_output;
                cout << "[FORWARD] Forwarded data from EX to EX" << endl;
            }
            else if ((mem_dst_reg_idx == id_src_reg_idx) && ex_mem_is_wr_en){ //Not a store operation
                final_ex_input = mem_output;
                cout << "[FORWARD] Forwarded data from MEM to EX" << endl;
            }
            else
                final_ex_input = id_reg_file_read_data;
        }
};