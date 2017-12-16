sdasmodule sinal (
	input [11:0] pt1X, pt1Y, pt2X, pt2Y, ptX, ptY
	output sinal
);

wire signed [11:0] sub1, sub2, sub3, sub4;
wire signed [22:0] mp1, mp2, sub5;

assign sub1 = ptX - pt2Y;
assign sub2 = pt1Y - pt2Y;
assign sub3 = pt1X - ptX;
assign sub4 = ptY - pt2Y;
assign mp1 = sub1 * sub2;
assign mp2 = sub3 * sub4;
assign sub5 = mp1 - mp2;
assign sinal = (sub5 >= 0) ? 1 : 0;

endmodule


module tstpt (
	input [11:0] pt1X, pt1Y, pt2X, pt2Y, ptX, ptY, pt3X, pt3Y
	output dentro
);

wire sinal1, sinal2, sinal3;
assign dentro = (sinal1 == 1 && sinal2 == 1 && sinal3 == 1) ? 1:0;

sinal s1(pt1X, pt1Y, pt2X, pt2Y, ptX, ptY, sinal1);
sinal s2(pt2X, pt2Y, pt3X, pt3Y, ptX, ptY, sinal2);
sinal s3(pt3X, pt3Y, pt1X, pt1Y, ptX, ptY, sinal3);

endmodule


module testbench;

reg [11:0] pt1X, pt1Y, pt2X, pt2Y, ptX, ptY, pt3X, pt3Y;
wire dentro;
triangulo A(pt1X, pt1Y, pt2X, pt2Y, ptX, ptY, pt3X, pt3Y, dentro);

initial
    begin
        $dumpvars(0,A);
        #1
        pt1X <= 13;
        pt1Y <= 13;
        pt2X <= 32;
        pt2Y <= 10;
        pt3X <= 16;
        pt3Y <= 30;
        ptX <= 18;
        ptY <= 18;
		
        #1
        ptX <= 15;
        ptY <= 15;
		
        #1
        ptX <= 09;
        ptY <= 15;
		
        #1
        ptX <= 18;
        ptY <= 10;
		
        #1
        ptX <= 32;
        ptY <= 10;
        #40
        $finish;
    end
endmodule