#include <iostream>
using namespace std;
class Fetch{
    protected:
        int ins_mem[100];
        int PC=0;
        int debug_verbosity = 4;
        
    public : 
        int fetch_valid = 1;
        int fetch_flush = 0;
        int fetched_ins=0;
        Fetch(){
            for(int i = 0; i < 100; i++){
                //if(i == 1)
                    //ins_mem[i] = 0x210821; // Add R1, R1, R1
                    //ins_mem[i] = 0x8C200000; // LW R0, 0(R1)
                    //ins_mem[i] = 0x8FE00000; // LW R0, 0(R31)
                    ins_mem[i] = (0x8FE0+i) << 16; //LW R0, 0(R31) --> LW R1, 0(R31) --> LW R2, 0(R31) ...
                    //ins_mem[i] = 0xAFE00000; // ST R0, 0(R31)
                    //ins_mem[i] = (0xAFE0+i) << 16;; // //ST R0, 0(R31) --> ST R1, 0(R31) --> ST R2, 0(R31) ...
                //else
                //    ins_mem[i] = 0x4000C41;
            }
            //for(int i = 0; i < 100; i+=2){
                //if(i == 1)
                    //ins_mem[i] = 0x210821; // Add R1, R1, R1
                    //ins_mem[i] = 0x8C200000; // LW R0, 0(R1)
                    //ins_mem[i] = 0x8FE00000; // LW R0, 0(R31)
                    //ins_mem[i] = (0x8FE10000); //LW R1, 0(R31) ...
                    //ins_mem[i+1] = 0x210821; // Add R1, R1, R1
                    //ins_mem[i] = 0xAFE00000; // ST R0, 0(R31)
                    //ins_mem[i] = (0xAFE0+i) << 16;; // //ST R0, 0(R31) --> ST R1, 0(R31) --> ST R2, 0(R31) ...
                //else
                //    ins_mem[i] = 0x4000C41;
            //}               
        }

        void read_ins_from_cache(){
            fetched_ins =  fetch_flush ? 0 : ins_mem[PC];
            if(debug_verbosity > 3) cout << "[FETCH] Within read_ins_from_cache processing for PC: " << PC << " and fetched ins is : "  << hex << fetched_ins << std::dec << endl;
        }

        void flush_pipeline(){
            fetch_flush = 1;
        }

        void resume_pipeline(){
            fetch_flush = 0;
        }

        void advancePC(int offset, int branch_pred){
            if(fetch_valid) {
                PC += offset; 
                if(debug_verbosity > 3) cout << "[FETCH] Updated PC to be: " << PC << " for next fetch" << endl;
            }
        }
        void decPC(int offset, int branch_pred){
            if(fetch_valid) {
                PC -= offset; 
                if(debug_verbosity > 3) cout << "[FETCH] Updated PC to be: " << PC << " for next fetch" << endl;
            }
        }
        
        void stall(){
            fetch_valid = 0;
        }
        void clear_stall(){
            fetch_valid = 1;
        }
};