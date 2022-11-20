#include <stdio.h>
#include <iostream>
#include <Fetch.hh>
#include <Decode.hh>
#include <Execute.hh>
#include <Memory.hh>
#include <WB.hh>
#include <if_id_pipeline.hh>
#include <id_ex_pipeline.hh>
#include <ex_mem_pipeline.hh>
#include <mem_wb_pipeline.hh>
#include <defines.hh>
#include <Forward.hh>

using namespace std;
int main(){
    Fetch fetch_obj;
    Decode decode_obj;
    Execute exec_obj;
    Memory mem_obj;
    WB wb_obj;
    Forward fwd_obj;

    if_id_pipeline if_id_pipeline_obj;
    id_ex_pipeline id_ex_pipeline_obj;
    ex_mem_pipeline ex_mem_pipeline_obj;
    mem_wb_pipeline mem_wb_pipeline_obj;

    int t = 10;

    int if_flush_pipeline = 0;
    int if_stall = 0;
    int if_fetched_ins;

    int if_id_latched_ins;

    int id_rd_data1;
    int id_rd_data2;
    int id_opcode;
    int id_dst_reg_idx;
    int id_stall = 0;
    int id_flush = 0;
    int id_is_mem;
    int id_wr_en;
    int id_idx1;
    int id_idx2;
    int id_shift_amt;
    int id_funct;
    int id_imm;

    int id_ex_rd_data1;
    int id_ex_rd_data2;
    int id_ex_opcode;
    int id_ex_dst_reg_idx;
    int id_ex_is_mem;
    int id_ex_wr_en;
    int id_ex_idx1;
    int id_ex_idx2;
    int id_ex_shift_amt;
    int id_ex_funct;
    int id_ex_imm;

    int ex_temp1_input=0;
    int ex_temp2_input=0;
    int ex_output;

    int ex_stall=0;
    int ex_mem_data;
    int ex_mem_dst_reg_idx;
    int ex_mem_is_mem=0;
    int ex_mem_rd_data;

    int mem_rd_data;
    int mem_stall=0;
    
    int ex_mem_wr_en=0;
    
    int mem_wb_rd_data;
    int mem_wb_dst_reg_idx;
    int mem_wb_wr_en=0;

    while(t--){
        cout << "**********************START of CYCLE**********************" << endl;
        cout << "[CPU] Value of t is : " << t << endl;
        //Mem WB pipeline  registers fetching      
        mem_wb_pipeline_obj.get_pipeline_regs(mem_wb_dst_reg_idx, mem_wb_rd_data, mem_wb_wr_en);

        //WB Stage Logic
        decode_obj.write(mem_wb_dst_reg_idx,mem_wb_rd_data, mem_wb_wr_en);

        ex_mem_pipeline_obj.get_pipeline_regs(ex_mem_data, ex_mem_dst_reg_idx, ex_mem_is_mem, ex_mem_rd_data, ex_mem_wr_en);
        //Mem Stage Logic
        //ex_mem_data means the address for memory ops, mem_rd_data is the data read from memory and ex_mem_dst_reg_idx means the data that is supposed to be written for stores
        if(ex_mem_is_mem == 35)
            mem_obj.load(ex_mem_data, mem_rd_data);
        else if(ex_mem_is_mem == 43)
            mem_obj.store(ex_mem_data, ex_mem_dst_reg_idx);
        else
            mem_rd_data = ex_mem_data;
        
        //MEM/WB pipeline update
        mem_wb_pipeline_obj.update_pipeline(ex_mem_dst_reg_idx, mem_rd_data, ex_mem_wr_en, mem_stall);

        //ID/EX pipeline regsters fetching
        id_ex_pipeline_obj.get_pipeline_regs1(id_ex_rd_data1, id_ex_rd_data2, id_ex_opcode, id_ex_is_mem, id_ex_dst_reg_idx, id_ex_wr_en);
        id_ex_pipeline_obj.get_pipeline_regs2(id_ex_idx1, id_ex_idx2, id_ex_shift_amt, id_ex_funct, id_ex_imm);

        //EXEnd -> ExStart Forwarding Logic
        fwd_obj.exstart_fwd(ex_mem_dst_reg_idx, mem_wb_dst_reg_idx, id_ex_idx1, ex_mem_data, mem_wb_rd_data, id_ex_rd_data1, ex_temp1_input, id_ex_wr_en, ex_mem_wr_en);
        fwd_obj.exstart_fwd(ex_mem_dst_reg_idx, mem_wb_dst_reg_idx, id_ex_idx2, ex_mem_data, mem_wb_rd_data, id_ex_rd_data2, ex_temp2_input, id_ex_wr_en, ex_mem_wr_en);

        //Exec Stage Logic
        exec_obj.alu(ex_temp1_input, ex_temp2_input, id_ex_opcode, ex_output, id_ex_shift_amt, id_ex_funct, id_dst_reg_idx, id_ex_imm); 

        // Exec mem pipeline update
        ex_mem_pipeline_obj.update_pipeline(ex_output, id_dst_reg_idx, id_ex_is_mem, id_ex_rd_data1, id_ex_wr_en, ex_stall);

        //IF ID pipeline registers fetching
        if_id_latched_ins = if_id_pipeline_obj.return_ins();

        //Decode Stage Logic
        decode_obj.decode_ins(if_id_latched_ins);
        
        if(id_stall)
            decode_obj.stall();
        else
            decode_obj.clear_stall();

        if(id_flush)
            decode_obj.clear_pipeline();
        else
            decode_obj.resume_pipeline();
        
        decode_obj.get_decoded_ins(id_rd_data1, id_rd_data2, id_opcode, id_dst_reg_idx, id_shift_amt, id_funct, id_imm);
        decode_obj.control_signals(id_is_mem, id_wr_en, id_idx1, id_idx2);

        //Decode Exec pipeline Update
        id_ex_pipeline_obj.update_pipeline(id_rd_data1, id_rd_data2, id_opcode, id_dst_reg_idx, id_is_mem, id_stall);
        id_ex_pipeline_obj.update_pipeline2(id_wr_en, id_idx1, id_idx2, id_shift_amt, id_funct, id_imm, id_stall);

        /// Fetch Stage logic
        fetch_obj.read_ins_from_cache();
        if(if_flush_pipeline)
            fetch_obj.flush_pipeline();
        else
            fetch_obj.resume_pipeline();
        
        if(if_stall)
            fetch_obj.stall();
        else
            fetch_obj.clear_stall();

        fetch_obj.advancePC(1,0);
        if_fetched_ins = fetch_obj.fetched_ins;

        //Update IF/ID pipeline
        if_id_pipeline_obj.update_pipeline(if_fetched_ins, if_stall);
        cout << "*****************END of CYCLE*********************" << endl;
    }
    return 0;

}