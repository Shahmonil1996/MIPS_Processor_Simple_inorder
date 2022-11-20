#include <iostream>
using namespace std;
class WB{
    public:
        int wb_en = 0;
    
    void write_mode(){
        wb_en = 1;
    }
    void read_mode(){
        wb_en = 0;
    }
};