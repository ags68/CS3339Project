module Mux2to1_test;
reg [31:0] din_A, din_B;
reg select;
wire [31:0] dout;

Mux2to1 dut(dout, din_A, din_B, select);

initial begin
    $display("Testing Verilog 2to1 Mux...");
    din_A <= 32'hDEADBEEF;
    din_B <= 32'hF00DCAFE;
    select <= 0;
    #20
    if (dout != din_A) begin
        $display("2to1 Mux FAILURE: dout != din_A when select = 0");
    end
    select <= 1;
    #20
    if (dout != din_B) begin
        $display("2to1 Mux FAILURE: dout != din_B when select = 1");
    end
end

endmodule