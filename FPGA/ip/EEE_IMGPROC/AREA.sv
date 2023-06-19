module AREA (
  input logic [10:0] x_min,
  input logic [10:0] x_max,
  input logic [10:0] y_min,
  input logic [10:0] y_max,
  output logic [31:0] area
);

  always_comb begin
    area = (x_max - x_min + 1) * (y_max - y_min + 1);
  end

endmodule
