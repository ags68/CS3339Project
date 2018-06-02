module forwardingUnit
	(
	    ID_EX_RegisterRs,
	    ID_EX_RegisterRt,

	    EX_MEM_RegisterWr,
	    EX_MEM_RegisterRd,

	    MEM_WB_RegisterWr,
	    MEM_WB_RegisterRd,

	    forwardA,
	    forwardB
	);

	input [4:0] ID_EX_RegisterRs,
				ID_EX_RegisterRt,
				EX_MEM_RegisterRd,
				MEM_WB_RegisterRd;

	input EX_MEM_RegisterWr, MEM_WB_RegisterWr;
	
	output reg [1:0] forwardA, forwardB;

//---------------------------------------------------------------------------------------------------

	//Forwarding Unit A------------------------------------------------------------------
	always @(*)
		begin
			//----------------------------------------
			if(EX_MEM_RegisterWr && EX_MEM_RegisterRd != 0 && EX_MEM_RegisterRd == ID_EX_RegisterRs)
			begin forwardA <= 2'b10; end
			//----------------------------------------
			else if(MEM_WB_RegisterWr && MEM_WB_RegisterRd != 0 && MEM_WB_RegisterRd == ID_EX_RegisterRs)
			begin forwardA <= 2'b01; end
			//----------------------------------------
			else begin forwardA <= 2'b00; end
		end

	//Forwarding Unit B------------------------------------------------------------------
	always @(*)
		begin
			//----------------------------------------
			if(EX_MEM_RegisterWr && EX_MEM_RegisterRd != 0 && EX_MEM_RegisterRd == ID_EX_RegisterRt)
			begin forwardB <= 2'b10; end
			//----------------------------------------
			else if(MEM_WB_RegisterWr && MEM_WB_RegisterRd != 0 && MEM_WB_RegisterRd == ID_EX_RegisterRt)
			begin forwardB <= 2'b01; end
			//----------------------------------------
			else begin forwardB <= 2'b00; end
		end
endmodule
