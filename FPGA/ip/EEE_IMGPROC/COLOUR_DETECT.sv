module COLOUR_DETECT (
  input logic [7:0] red,
  input logic [7:0] green,
  input logic [7:0] blue,
  output logic red_detect,
  output logic yellow_detect,
  output logic blue_detect
);

  always_comb begin
    red_detect 		= red>8'd160 & green<8'd70 & blue<8'd70;
    yellow_detect 	= red>8'd70 & green>8'd220 & blue<8'd70;
    blue_detect 	= red<8'd20 & green>8'd30 & blue>8'd80;
  end

endmodule
