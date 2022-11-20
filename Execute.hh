#include <iostream>
using namespace std;
class Execute{
    public:
        int debug_verbosity = 4;
        void alu(int dat_1, int dat_2, int opcode, int & output_temp, int shift_amt, int funct, int rdst, int imm){
            int out;
            if(opcode == 0)
            {
                switch(funct){
                    case 0 : out = dat_2 << shift_amt; break;
                    case 2 : out = dat_2 >> shift_amt;break;
                    case 33 : out = dat_1 + dat_2;break;
                    case 35 : out = dat_1 - dat_2;break;
                    case 36 : out = dat_1 & dat_2;break;
                    case 37 : out = dat_1 | dat_2;break;
                    case 38 : out = dat_1 ^ dat_2;break;
                    case 39 : out = ~(dat_1 | dat_2);break;
                    default : out = 0;
                }
            } 
            else if(opcode == 35 || opcode == 43){
                out =  dat_1 + imm;
            }
            if(debug_verbosity > 3) {
                cout << "[EXECUTE] dat_1 : " << dat_1 << " dat_2: " << dat_2 << " imm : " << imm << " out : " << out 
                << " shft : " << shift_amt << " funct : " << funct  << " opcode : " << opcode << " rdst: " << rdst << endl;
            }
            output_temp = out;
        }
};