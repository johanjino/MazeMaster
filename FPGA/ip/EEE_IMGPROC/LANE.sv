module LANE (
  input logic [10:0] r_x_min,
  input logic [10:0] r_x_max,
  input logic [10:0] r_y_min,
  input logic [10:0] r_y_max,
  input logic [10:0] l_x_min,
  input logic [10:0] l_x_max,
  input logic [10:0] l_y_min,
  input logic [10:0] l_y_max,
  output logic [31:0] offset,
  output logic [31:0] left,
  output logic [31:0] right,
  output logic [31:0] forward
);

  always_comb begin
    offset = (r_x_min - 32'd320) - (32'd320 - l_x_max);
    forward = (r_x_min - l_x_max) < 11'd5;
    left =  (l_y_min > 11'd360);
    right = (r_y_min > 11'd360);
  end

endmodule
