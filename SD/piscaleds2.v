module piscaleds1(
  input CLOCK_50,
  input [3:0] KEY,
  input [9:0] SW,
  output [7:0]LEDG,
  output [7:0]LEDR
);

//assign LEDG = KEY; 
//assign LEDR = SW;

reg [25:0] contador = 0;
reg l = 0;
assign LEDG = l;

always @(posedge CLOCK_50) begin
  contador = contador + 1;
  if (KEY[0] == 1) begin
    if (contador == 50000000) begin
      contador = 0;
      l = ~l;
    end
  end
  if (KEY[0] == 0) begin
    if (contador == 5000000) begin
      contador = 0;
      l = ~l;
    end
  end
end

endmodule
