module aluControl_test;
wire [3:0] Operation;
reg [1:0] ALUOp;
reg [5:0] Function;

wire [3:0] ALU_AND = 'b0000;
wire [3:0] ALU_OR  = 'b0001;
wire [3:0] ALU_ADD = 'b0010;
wire [3:0] ALU_SUB = 'b0110;
wire [3:0] ALU_SLT = 'b0111;
wire [3:0] ALU_NOR = 'b1100;
wire [3:0] ALU_XOR = 'b1101;

wire [5:0] FUNCT_ADD = 32;
wire [5:0] FUNCT_SUB = 34;
wire [5:0] FUNCT_AND = 36;
wire [5:0] FUNCT_OR  = 37;
wire [5:0] FUNCT_XOR = 38;
wire [5:0] FUNCT_NOR = 39;
wire [5:0] FUNCT_SLT = 42;

ALUControlUnit dut( Operation, ALUOp, Function);

initial begin
    $display("Testing Verilog ALU Control Unit...");
    ALUOp <= 0;
    Function <= 37;
    #20
    if (Operation != ALU_ADD) begin
        $display("ALU Ctrl FAILURE: Operation (0b%04b) != ALU_ADD (0b%04b), when ALUOp = 0b%02b and Function = 0b%06b", Operation, ALU_ADD, ALUOp, Function);
    end

    ALUOp <= 1;
    Function <= 37;
    #20
    if (Operation != ALU_SUB) begin
        $display("ALU Ctrl FAILURE: Operation (0b%04b) != ALU_SUB (0b%04b), when ALUOp = 0b%02b and Function = 0b%06b", Operation, ALU_SUB, ALUOp, Function);
    end

    ALUOp <= 2;
    Function <= FUNCT_ADD;
    #20
    if (Operation != ALU_ADD) begin
        $display("ALU Ctrl FAILURE: Operation (0b%04b) != ALU_ADD (0b%04b), when ALUOp = 0b%02b and Function = 0b%06b", Operation, ALU_ADD, ALUOp, Function);
    end

    ALUOp <= 2;
    Function <= FUNCT_SUB;
    #20
    if (Operation != ALU_SUB) begin
        $display("ALU Ctrl FAILURE: Operation (0b%04b) != ALU_SUB (0b%04b), when ALUOp = 0b%02b and Function = 0b%06b", Operation, ALU_SUB, ALUOp, Function);
    end

    ALUOp <= 2;
    Function <= FUNCT_XOR;
    #20
    if (Operation != ALU_XOR) begin
        $display("ALU Ctrl FAILURE: Operation (0b%04b) != ALU_XOR (0b%04b), when ALUOp = 0b%02b and Function = 0b%06b", Operation, ALU_XOR, ALUOp, Function);
    end
end

endmodule