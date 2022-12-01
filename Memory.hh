#include <iostream>
using namespace std;
class Memory{
    protected:
        int dat_mem[100];
        int debug_verbosity = 4;
        
    public : 
        int mem_valid = 1;
        int mem_flush = 0;
        Memory(){
            for(int i = 0; i < 100; i++){
                dat_mem[i] = i;
            }        
        }

        

        void flush_pipeline(){
            mem_flush = 1;
        }

        void resume_pipeline(){
            mem_flush = 0;
        }

        void load(int addr, int & rd_data){
            if(addr > 100){
                rd_data =  0;
                cout << "[MEM] addr higher than 100 : " << addr << endl;
            }
            else  {  
                rd_data = dat_mem[addr];
                cout << "[MEM] Loaded valued: " << rd_data << " from addr : " << addr << endl;
            }
        }
        void store(int addr, int data){
            if(addr < 100){
                dat_mem[addr] = data;
                cout << "[MEM] Stored valued: " << data << " at addr : " << addr << endl;
            }
        }
        
        void stall(){
            mem_valid = 0;
        }
        void clear_stall(){
            mem_valid = 1;
        }
        int * get_ptr(){
            return dat_mem;
        }
};