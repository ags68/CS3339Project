module memory_test;

reg [31:0] data_addr, inst_addr, din;
reg clk, data_rd, data_wr;
wire [31:0] dout, inst;

reg [5:0] indexA, indexB;
reg [31:0] randomData [0:511];

reg fail;

memory dut(
  data_addr, data_rd, data_wr,
  din,
  inst_addr,
  clk,
  dout,
  inst
);

initial begin
    $display("Testing Verilog Memory Unit...");
    clk = 0;
    data_wr = 1;
    data_rd = 0;
    fail = 0;

    // Fill memory.
    for (data_addr = 0; data_addr < 4096 && !fail; data_addr = data_addr +4) begin
        randomData[data_addr] = $random;
        din = randomData[data_addr];
        clk = 1;
        #10
        clk = 0;
        #10;
    end

    // Stop writing and make sure you can read back all data with all combinations of rd_reg
    data_wr = 0;
    data_rd = 1;
    for (data_addr = 0; data_addr < 4096 && !fail; data_addr = data_addr +4) begin
        for (inst_addr = 0; inst_addr < 4096; inst_addr = inst_addr +4) begin
            clk = 1;
            #10
            clk = 0;
            if (dout !== randomData[data_addr]) begin
                $display("Memory FAILURE: dout (0x%08x) read from address 0x%08x does not equal what was written (0x%08x)", dout, data_addr, randomData[data_addr]);
                fail = 1;
            end
            if (inst !== randomData[inst_addr]) begin
                $display("Memory FAILURE: inst (0x%08x) read from address 0x%08x does not equal what was written (0x%08x)", inst, inst_addr, randomData[inst_addr]);
                fail = 1;
            end
            #10;
        end
    end
end

endmodule
