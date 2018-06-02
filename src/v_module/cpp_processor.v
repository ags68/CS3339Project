module cpp_processor(
  clk, inst, instAddr, load, regOut
);

input clk, load;
input [31:0] inst, instAddr;
reg [31:0] registers [0:31];
output [1023:0] regOut;

assign regOut = {registers[ 0], registers[ 1], registers[ 2], registers[ 3],
                 registers[ 4], registers[ 5], registers[ 6], registers[ 7],
                 registers[ 8], registers[ 9], registers[10], registers[11],
                 registers[12], registers[13], registers[14], registers[15],
                 registers[16], registers[17], registers[18], registers[19],
                 registers[20], registers[21], registers[22], registers[23],
                 registers[24], registers[25], registers[26], registers[27],
                 registers[28], registers[29], registers[30], registers[31]};

integer regNumber;

always @(posedge clk) begin
    if (load) begin
        $processor_load(inst, instAddr);
    end
    else begin
        $processor_clock();
    end
    for (regNumber = 0; regNumber < 32; regNumber = regNumber +1) begin
        $processor_readReg(regNumber,registers[regNumber]);
    end
end

endmodule