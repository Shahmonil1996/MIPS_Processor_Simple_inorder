#include <iostream>
using namespace std;
class if_id_pipeline{
    protected:
        int ins;
    public:
        int return_ins(){
            return ins;
        }
        void update_pipeline(int new_ins, int stall){
            if(!stall) ins = new_ins;
            cout << "[IF/ID PIPELINE] ins: " << std::hex << ins << std::dec << endl;
        }
};