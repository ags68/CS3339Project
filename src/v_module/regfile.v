module regfile(
  rd_reg_A, rd_reg_B,
  wr_reg,
  din,
  dout_A, dout_B,
  clk, regWrite,
  regOut
);

input [4:0] rd_reg_A, rd_reg_B, wr_reg;
input [31:0] din;
input clk, regWrite;
output [31:0] dout_A, dout_B;
output [1023:0] regOut;

reg [31:0] registers [31:0];

assign dout_A = registers[rd_reg_A];
assign dout_B = registers[rd_reg_B];

assign regOut = {registers[ 0], registers[ 1], registers[ 2], registers[ 3],
                 registers[ 4], registers[ 5], registers[ 6], registers[ 7],
                 registers[ 8], registers[ 9], registers[10], registers[11],
                 registers[12], registers[13], registers[14], registers[15],
                 registers[16], registers[17], registers[18], registers[19],
                 registers[20], registers[21], registers[22], registers[23],
                 registers[24], registers[25], registers[26], registers[27],
                 registers[28], registers[29], registers[30], registers[31]};

integer regNumber;

initial begin
    for (regNumber = 0; regNumber < 32; regNumber = regNumber +1) begin
        registers[regNumber] = 32'b0;
    end
end

always @(negedge clk) begin
    if (regWrite) registers[wr_reg] <= din;
end

endmodule
