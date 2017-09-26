module piscaleds(
  input CLOCK_50,
  input [3:0] KEY,
  input [9:0] SW,
  output [7:0]LEDG,
  output [9:0]LEDR
);

//assign LEDG = KEY; 
//assign LEDR = SW;

reg [27:0] contador = 0;
reg [9:0] l = 0;
assign LEDG[0] = l;
assign LEDG[1] = ~l;
assign LEDG[2] = l;
assign LEDG[3] = ~l;
assign LEDG[4] = l;
assign LEDG[5] = ~l;
assign LEDG[6] = l;
assign LEDG[7] = ~l;

assign LEDR[0] = l;
assign LEDR[1] = ~l;
assign LEDR[2] = l;
assign LEDR[3] = ~l;
assign LEDR[4] = l;
assign LEDR[5] = ~l;
assign LEDR[6] = l;
assign LEDR[7] = ~l;
assign LEDR[8] = l;
assign LEDR[9] = ~l;


always @(posedge CLOCK_50) begin
  contador = contador + 1;
  if (SW[0] == 1) begin
    if (contador == 200000000) begin //4s
      contador = 0;
      l = ~l;
    end
  end
  
   if (SW[1] == 1) begin
    if (contador == 150000000) begin //3s
      contador = 0;
      l = ~l;
    end
  end

   if (SW[2] == 1) begin
    if (contador == 100000000) begin //2s
      contador = 0;
      l = ~l;
    end
  end
  
   if (SW[3] == 1) begin
    if (contador == 75000000) begin //1.5s
      contador = 0;
      l = ~l;
    end
  end
  
   if (SW[4] == 1) begin
    if (contador == 50000000) begin //1s
      contador = 0;
      l = ~l;
    end
  end
  
   if (SW[5] == 1) begin
    if (contador == 6250000) begin //.125s
      contador = 0;
      l = ~l;
    end
  end
  
   if (SW[6] == 1) begin
    if (contador == 12500000) begin //.25s
      contador = 0;
      l = ~l;
    end
  end
  
   if (SW[7] == 1) begin
    if (contador == 25000000) begin //.5s
      contador = 0;
      l = ~l;
    end
  end
  
  if (SW[8] == 1) begin
    if (contador == 37500000) begin //.75s
      contador = 0;
      l = ~l;
    end
  end
  
  if (SW[9] == 1) begin
    if (contador == 50000000) begin //1s
      contador = 0;
      l = ~l;
    end
  end

 end

endmodule
