module memory(
  data_addr, data_rd, data_wr,
  din,
  inst_addr,
  clk,
  dout,
  inst
);

input [31:0] data_addr, din, inst_addr;
input data_rd, data_wr, clk;
output [31:0] dout, inst;

reg [31:0] mem [1024:0];

assign dout = data_rd ? mem[data_addr/4] : 32'b0;
assign inst = mem[inst_addr/4];

always @(posedge clk) begin
    if (data_wr) mem[data_addr/4] <= din;
end

endmodule
