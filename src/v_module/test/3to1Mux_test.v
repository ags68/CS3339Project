module Mux3to1_test;
reg [31:0] din_A, din_B, din_C;
reg [1:0] select;
wire [31:0] dout;

Mux3to1 dut(dout, din_A, din_B, select, din_C);

initial begin
    $display("Testing Verilog 3to1 Mux...");
    din_A <= 32'hDEADBEEF;
    din_B <= 32'hF00DCAFE;
    din_B <= 32'h12345678;
    select <= 0;
    #20
    if (dout != din_A) begin
        $display("3to1 Mux FAILURE: dout != din_A when select = 0");
    end
    select <= 1;
    #20
    if (dout != din_B) begin
        $display("3to1 Mux FAILURE: dout != din_B when select = 1");
    end
    select <= 2;
    #20
    if (dout != din_C) begin
        $display("3to1 Mux FAILURE: dout != din_C when select = 2");
    end
end

endmodule