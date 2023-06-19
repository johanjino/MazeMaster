module  RGBtoHSV(
	input   logic           clk,	
	input   logic           rst_n,
	input   logic   [7:0]   red, green, blue,
	output  logic   [9:0]   h,                  // 0 - 360
	output  logic   [7:0]   s,                  // 0 - 255
	output  logic   [7:0]   v                   // 0 - 255
);

	logic [7:0] Cmax, Cmin;
	logic [7:0] delta;
	logic r,g,b;

	// Max calculation
	always_comb begin
		if (red >= green && red >= blue) begin
			Cmax = red;
			r = 1;
			g = 0;
			b = 0;
		end
		else if (green >= red && green >= blue) begin
			Cmax = green;
			r = 0;
			g = 1;
			b = 0;
		end
		else begin
			Cmax = blue;
			r = 0;
			g = 0;
			b = 1;
		end
	end

	// Min calculation
	always_comb begin
		if (red <= green && red <= blue) begin
			Cmin = red;
		end
		else if (green <= red && green <= blue) begin
			Cmin = green;
		end
		else begin
			Cmin = blue;
		end
	end

	always_comb begin
		delta = Cmax - Cmin;
	end


	always_comb

            
endmodule