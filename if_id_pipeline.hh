#include <iostream>
using namespace std;
class if_id_pipeline{
    protected:
        int ins=0;
        int idx_src1=0;
        int idx_src2=0;
    public:
        void return_ins(int & ins_temp, int & idx_src1_temp, int & idx_src2_temp){
            idx_src1_temp = idx_src1;
            idx_src2_temp = idx_src2;
            ins_temp = ins;
        }
        void update_pipeline(int new_ins, int stall){
            if(!stall) ins = new_ins;
            if(!stall) idx_src1 = (ins>>21) & 31;
            if(!stall) idx_src2 = (ins>>16) & 31;
            cout << "[IF/ID PIPELINE] updated ins: " << std::hex << ins << std::dec << endl;
        }
};