module EEE_IMGPROC(
	// global clock & reset
	clk,
	reset_n,
	
	// mm slave
	s_chipselect,
	s_read,
	s_write,
	s_readdata,
	s_writedata,
	s_address,

	// stream sink
	sink_data,
	sink_valid,
	sink_ready,
	sink_sop,
	sink_eop,
	
	// streaming source
	source_data,
	source_valid,
	source_ready,
	source_sop,
	source_eop,
	
	// conduit
	mode
	
);


// global clock & reset
input							clk;
input							reset_n;

// mm slave
input							s_chipselect;
input							s_read;
input							s_write;
output reg		[31:0]			s_readdata;
input			[31:0]			s_writedata;
input			[2:0]			s_address;


// streaming sink
input			[23:0]          sink_data;
input							sink_valid;
output							sink_ready;
input							sink_sop;
input							sink_eop;

// streaming source
output			[23:0]			source_data;
output							source_valid;
input							source_ready;
output							source_sop;
output							source_eop;

// conduit export
input                         	mode;

////////////////////////////////////////////////////////////////////////
//
parameter IMAGE_W = 11'd640;
parameter IMAGE_H = 11'd480;
parameter MESSAGE_BUF_MAX = 256;
parameter MSG_INTERVAL = 6;
parameter BB_COL_DEFAULT = 24'h00ff00;


wire [7:0]   red, green, blue, grey;

wire [7:0]   red_out, green_out, blue_out;

wire         sop, eop, in_valid, out_ready;
////////////////////////////////////////////////////////////////////////


// Detect colours
wire red_detect, yellow_detect, blue_detect, white_detect;

COLOUR_DETECT	Colout_detect_inst (
	.red (red),
	.green (green),
	.blue (blue),
	.red_detect (red_detect),
	.yellow_detect (yellow_detect),
	.blue_detect (blue_detect),
	);

assign white_detect 	= red[7] & green[7] & blue[7];

// Find boundary of cursor box



// Highlight detected areas & Show bounding box
reg [23:0] new_image;
wire bb_active_red, bb_active_yellow, bb_active_blue, bb_active_white;

assign bb_active_red = 	((x > left_red) & (x < right_red) & ((y == top_red) | (y == bottom_red))) | 
						((y > top_red) & (y < bottom_red) & ((x == left_red) | (x == right_red)));
assign bb_active_yellow =	((x > left_yellow) & (x < right_yellow) & ((y == top_yellow) | (y == bottom_yellow))) | 
							((y > top_yellow) & (y < bottom_yellow) & ((x == left_yellow) | (x == right_yellow)));
assign bb_active_blue =	((x > left_blue) & (x < right_blue) & ((y == top_blue) | (y == bottom_blue))) |
						((y > top_blue) & (y < bottom_blue) & ((x == left_blue) | (x == right_blue)));
assign bb_active_white = ((x > left_lane_left) & (x < right_lane_left) & ((y == top_lane_left) | (y == bottom_lane_left))) |
						((y > top_lane_left) & (y < bottom_lane_left) & ((x == left_lane_left) | (x == right_lane_left))) |
						((x > left_lane_right) & (x < right_lane_right) & ((y == top_lane_right) | (y == bottom_lane_right))) |
						((y > top_lane_right) & (y < bottom_lane_right) & ((x == left_lane_right) | (x == right_lane_right)));
assign grey = green[7:1] + red[7:2] + blue[7:2]; //Grey = green/2 + red/4 + blue/4


always @ (posedge clk) begin
	if (bb_active_red) begin
		new_image = 24'hff7276;
	end 
	else begin
		if (bb_active_yellow) begin
			new_image = 24'hffffe0;
		end 
		else begin
			if  (bb_active_blue) begin
					new_image = 24'hadd8e6;
				end 
			else begin
				if (bb_active_white) begin
					new_image = 24'hffffff;
				end
				else begin
					if (red_detect && y<240) begin
						new_image = {8'hff, 8'h0, 8'h0};
					end
					else begin
						if (yellow_detect && y<240) begin
							new_image = {8'hff, 8'hff, 8'h0};
						end
						else begin
							if (blue_detect && y<240) begin
								new_image = {8'h00, 8'h00, 8'hff}; 
							end
							else begin
								if (white_detect && x<320 && y>240) begin
									new_image = {8'hff, 8'hff, 8'hff};
								end
								else begin
									new_image = {grey, grey, grey};
								end
							end
						end
					end
				end
			end
		end
	end
end

// Switch output pixels depending on mode switch
// Don't modify the start-of-packet word - it's a packet discriptor
// Don't modify data in non-video packets
assign {red_out, green_out, blue_out} = (mode & ~sop & packet_video) ? new_image : {red,green,blue};

//Count valid pixels to tget the image coordinates. Reset and detect packet type on Start of Packet.
reg [10:0] x, y;
reg packet_video;
always@(posedge clk) begin
	if (sop) begin
		x <= 11'h0;
		y <= 11'h0;
		packet_video <= (blue[3:0] == 3'h0);
	end
	else begin
		if (in_valid) begin
			if (x == IMAGE_W-1) begin
				x <= 11'h0;
				y <= y + 11'h1;
			end
			else begin
				x <= x + 11'h1;
			end
		end
	end
end

//Find first and last colour pixels
reg [10:0] x_min_red, y_min_red, x_max_red, y_max_red;
reg [10:0] x_min_yellow, y_min_yellow, x_max_yellow, y_max_yellow;
reg [10:0] x_min_blue, y_min_blue, x_max_blue, y_max_blue;
reg [10:0] x_min_lane_left, y_min_lane_left, x_max_lane_left, y_max_lane_left;
reg [10:0] x_min_lane_right, y_min_lane_right, x_max_lane_right, y_max_lane_right;
always@(posedge clk) begin
	if (red_detect & in_valid && y<240) begin	//Update bounds when the pixel is red
		if (x < x_min_red) x_min_red <= x;
		if (x > x_max_red) x_max_red <= x;
		if (y < y_min_red) y_min_red <= y;
		y_max_red <= y;
	end
	else if (yellow_detect & in_valid && y<240) begin 	//Update bounds when the pixel is red
		if (x < x_min_yellow) x_min_yellow <= x;
		if (x > x_max_yellow) x_max_yellow <= x;
		if (y < y_min_yellow) y_min_yellow <= y;
		y_max_yellow <= y;
	end
	else if (blue_detect & in_valid && y<240) begin		//Update bounds when the pixel is red
		if (x < x_min_blue) x_min_blue <= x;
		if (x > x_max_blue) x_max_blue <= x;
		if (y < y_min_blue) y_min_blue <= y;
		y_max_blue <= y;
	end
	else if (white_detect & in_valid && x<320 && y>240 && ((y-y_max_lane_left)<11'd10 || y_max_lane_left==0)) begin 	//Update bounds when left lane
		if (x < x_min_lane_left) x_min_lane_left <= x;
		if (x > x_max_lane_left) x_max_lane_left <= x;
		if (y < y_min_lane_left) y_min_lane_left <= y;
		y_max_lane_left <= y;
			
	end
	else if (white_detect & in_valid && x>320 && y>240) begin 	//Update bounds when left lane
		if (x < x_min_lane_right) x_min_lane_right <= x;
		if (x > x_max_lane_right) x_max_lane_right <= x;
		if (y < y_min_lane_right) y_min_lane_right <= y;
		y_max_lane_right <= y;
			
	end


	if (sop & in_valid) begin	//Reset bounds on start of packet
		x_min_red <= IMAGE_W-11'h1;
		x_max_red <= 0;
		y_min_red <= IMAGE_H-11'h1;
		y_max_red <= 0;

		x_min_yellow <= IMAGE_W-11'h1;
		x_max_yellow <= 0;
		y_min_yellow <= IMAGE_H-11'h1;
		y_max_yellow <= 0;

		x_min_blue <= IMAGE_W-11'h1;
		x_max_blue <= 0;
		y_min_blue <= IMAGE_H-11'h1;
		y_max_blue <= 0;

		x_min_lane_left <= IMAGE_W-11'h1;
		x_max_lane_left <= 0;
		y_min_lane_left <= IMAGE_H-11'h1;
		y_max_lane_left <= 0;

		x_min_lane_right <= IMAGE_W-11'h1;
		x_max_lane_right <= 0;
		y_min_lane_right <= IMAGE_H-11'h1;
		y_max_lane_right <= 0;
	end

end

//Process bounding box at the end of the frame.
reg [4:0] msg_state;
reg [10:0] left_red, right_red, top_red, bottom_red;
reg [10:0] left_yellow, right_yellow, top_yellow, bottom_yellow;
reg [10:0] left_blue, right_blue, top_blue, bottom_blue;
reg [10:0] left_lane_left, right_lane_left, top_lane_left, bottom_lane_left;
reg [10:0] left_lane_right, right_lane_right, top_lane_right, bottom_lane_right;
reg [7:0] frame_count;
always@(posedge clk) begin
	if (eop & in_valid & packet_video) begin  //Ignore non-video packets
		
		//Latch edges for display overlay on next frame
		left_red 	<= x_min_red;
		right_red 	<= x_max_red;
		top_red 	<= y_min_red;
		bottom_red 	<= y_max_red;

		left_yellow 	<= x_min_yellow;
		right_yellow 	<= x_max_yellow;
		top_yellow 		<= y_min_yellow;
		bottom_yellow 	<= y_max_yellow;

		left_blue 	<= x_min_blue;
		right_blue 	<= x_max_blue;
		top_blue 	<= y_min_blue;
		bottom_blue <= y_max_blue;

		left_lane_left 		<= x_min_lane_left;
		right_lane_left 	<= x_max_lane_left;
		top_lane_left 		<= y_min_lane_left;
		bottom_lane_left 	<= y_max_lane_left;

		left_lane_right 	<= x_min_lane_right;
		right_lane_right 	<= x_max_lane_right;
		top_lane_right 		<= y_min_lane_right;
		bottom_lane_right 	<= y_max_lane_right;
		
		
		//Start message writer FSM once every MSG_INTERVAL frames, if there is room in the FIFO
		frame_count <= frame_count - 1;
		
		if (frame_count == 0 && msg_buf_size < MESSAGE_BUF_MAX - 3) begin
			msg_state <= 2'b01;
			frame_count <= MSG_INTERVAL-1;
		end
	end
	
	//Cycle through message writer states once started
	if (msg_state == 4'b0110) msg_state <= 4'b00; 	// max state used reached. Reset here
	else if (msg_state != 4'b00) msg_state <= msg_state + 4'b01;

end
	
//Generate output messages for CPU
reg [31:0] msg_buf_in; 
wire [31:0] msg_buf_out;
reg msg_buf_wr;
wire msg_buf_rd, msg_buf_flush;
wire [7:0] msg_buf_size;
wire msg_buf_empty;

`define RED_BOX_MSG_ID 		"RBB"
`define YELLOW_BOX_MSG_ID 	"YBB"
`define BLUE_BOX_MSG_ID 	"BBB"

//Calculate Area
wire [31:0] area_red, area_yellow, area_blue;
AREA	Area_red (
	.x_min (x_min_red),
	.x_max (x_max_red),
	.y_min (y_min_red),
	.y_max (y_max_red),
	.area (area_red),
	);
AREA	Area_yellow (
	.x_min (x_min_yellow),
	.x_max (x_max_yellow),
	.y_min (y_min_yellow),
	.y_max (y_max_yellow),
	.area (area_yellow),
	);
AREA	Area_blue (
	.x_min (x_min_blue),
	.x_max (x_max_blue),
	.y_min (y_min_blue),
	.y_max (y_max_blue),
	.area (area_blue),
	);

always@(*) begin	//Write words to FIFO as state machine advances
	case(msg_state)
		4'b0000: begin
			msg_buf_in = 32'b0;
			msg_buf_wr = 1'b0;
		end
		4'b0001: begin
			msg_buf_in = `RED_BOX_MSG_ID;	//Message ID
			msg_buf_wr = 1'b1;
		end
		4'b0010: begin
			msg_buf_in = {area_red};	//Area red
			msg_buf_wr = 1'b1;
		end
		4'b0011: begin
			msg_buf_in = {area_yellow}; //Area yellow
			msg_buf_wr = 1'b1;
		end
		4'b0100: begin
			msg_buf_in = {area_blue}; //Area blue
			msg_buf_wr = 1'b1;
		end

		4'b0101: begin
			msg_buf_in = 32'b0;
			msg_buf_wr = 1'b0;
		end

		// 4'b0110: begin
		// 	msg_buf_in = {5'b0, x_min_yellow, 5'b0, y_min_yellow};	//Top left coordinate
		// 	msg_buf_wr = 1'b1;
		// end
		// 4'b0111: begin
		// 	msg_buf_in = {5'b0, x_max_yellow, 5'b0, y_max_yellow}; //Bottom right coordinate
		// 	msg_buf_wr = 1'b1;
		// end
		
		// 4'b1000: begin
		// 	msg_buf_in = 32'b0;
		// 	msg_buf_wr = 1'b0;
		// end
		// 4'b1001: begin
		// 	msg_buf_in = `BLUE_BOX_MSG_ID;	//Message ID
		// 	msg_buf_wr = 1'b1;
		// end
		// 4'b1010: begin
		// 	msg_buf_in = {5'b0, x_min_blue, 5'b0, y_min_blue};	//Top left coordinate
		// 	msg_buf_wr = 1'b1;
		// end
		// 4'b1011: begin
		// 	msg_buf_in = {5'b0, x_max_blue, 5'b0, y_max_blue}; //Bottom right coordinate
		// 	msg_buf_wr = 1'b1;
		// end
		// 4'b1100: begin
		// 	msg_buf_in = {32'hFFFFFFFF}; //Lane Detection Output
		// 	msg_buf_wr = 1'b1;
		// end
		// 4'b1101: begin
		// 	msg_buf_in = {lane_offset, 21'b0 , right , left, straight}; //Offset and boolean values
		// 	msg_buf_wr = 1'b1;
		// end

		default: begin
			msg_buf_wr = 1'b0;
		end
	endcase
end



//Output message FIFO
MSG_FIFO	MSG_FIFO_inst (
	.clock (clk),
	.data (msg_buf_in),
	.rdreq (msg_buf_rd),
	.sclr (~reset_n | msg_buf_flush),
	.wrreq (msg_buf_wr),
	.q (msg_buf_out),
	.usedw (msg_buf_size),
	.empty (msg_buf_empty)
	);


//Streaming registers to buffer video signal
STREAM_REG #(.DATA_WIDTH(26)) in_reg (
	.clk(clk),
	.rst_n(reset_n),
	.ready_out(sink_ready),
	.valid_out(in_valid),
	.data_out({red,green,blue,sop,eop}),
	.ready_in(out_ready),
	.valid_in(sink_valid),
	.data_in({sink_data,sink_sop,sink_eop})
);

STREAM_REG #(.DATA_WIDTH(26)) out_reg (
	.clk(clk),
	.rst_n(reset_n),
	.ready_out(out_ready),
	.valid_out(source_valid),
	.data_out({source_data,source_sop,source_eop}),
	.ready_in(source_ready),
	.valid_in(in_valid),
	.data_in({red_out, green_out, blue_out, sop, eop})
);


/////////////////////////////////
/// Memory-mapped port		 /////
/////////////////////////////////

// Addresses
`define REG_STATUS    			0
`define READ_MSG    				1
`define READ_ID    				2
`define REG_BBCOL					3

//Status register bits
// 31:16 - unimplemented
// 15:8 - number of words in message buffer (read only)
// 7:5 - unused
// 4 - flush message buffer (write only - read as 0)
// 3:0 - unused


// Process write

reg  [7:0]   reg_status;
reg	[23:0]	bb_col;

always @ (posedge clk)
begin
	if (~reset_n)
	begin
		reg_status <= 8'b0;
		bb_col <= BB_COL_DEFAULT;
	end
	else begin
		if(s_chipselect & s_write) begin
		   if      (s_address == `REG_STATUS)	reg_status <= s_writedata[7:0];
		   if      (s_address == `REG_BBCOL)	bb_col <= s_writedata[23:0];
		end
	end
end


//Flush the message buffer if 1 is written to status register bit 4
assign msg_buf_flush = (s_chipselect & s_write & (s_address == `REG_STATUS) & s_writedata[4]);


// Process reads
reg read_d; //Store the read signal for correct updating of the message buffer

// Copy the requested word to the output port when there is a read.
always @ (posedge clk)
begin
   if (~reset_n) begin
	   s_readdata <= {32'b0};
		read_d <= 1'b0;
	end
	
	else if (s_chipselect & s_read) begin
		if   (s_address == `REG_STATUS) s_readdata <= {16'b0,msg_buf_size,reg_status};
		if   (s_address == `READ_MSG) s_readdata <= {msg_buf_out};
		if   (s_address == `READ_ID) s_readdata <= 32'h1234EEE2;
		if   (s_address == `REG_BBCOL) s_readdata <= {8'h0, bb_col};
	end
	
	read_d <= s_read;
end

//Fetch next word from message buffer after read from READ_MSG
assign msg_buf_rd = s_chipselect & s_read & ~read_d & ~msg_buf_empty & (s_address == `READ_MSG);
						


endmodule