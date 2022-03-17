module keyboard_top (
    input CLK_50,       // 50MHz Clock
    input PS2_CLK,       // PS2 Clock
    input PS2_DAT,      // PS2 Data

	 /* outputs are for testing purposes */
    output reg [6:0] HEX0,  // 7 segment display
    output reg [6:0] HEX1,
    output [6:0] HEX2,
    output [6:0] HEX3,
    output [6:0] HEX4,
    output [6:0] HEX5
);

/* keyboard scancodes */
parameter keycode_up = 8'h75;
parameter keycode_down = 8'h72;
parameter keycode_left = 8'h6B;
parameter keycode_right = 8'h74;

parameter keycode_space = 8'h29;
parameter keycode_enter = 8'h5A;

/* counter */
reg [7:0] counter;
reg data_enable;

wire counter_enable = (counter >= 8'd11) ? 1'b1 : 1'b0;

always @ (negedge PS2_CLK or posedge counter_enable ) begin 
    if (counter_enable) begin
        counter <= 0;
        data_enable <= 1;
    end else begin
        counter <= counter + 1;
        data_enable <= 0;
    end	
end

/* Seriel shift register to get data from PS_DATA*/
reg valid;
reg [10:0] keycode;
always @ (negedge PS2_CLK or posedge data_enable ) begin

    if (data_enable) begin valid <= 1; end
    else
        case (counter)
            8'd0	: begin valid <= 1; keycode[0] <= PS2_DAT; end // start
            8'd1	: begin valid <= 0; keycode[1] <= PS2_DAT; end // bit 0 to 8
            8'd2	: begin valid <= 0; keycode[2] <= PS2_DAT; end
            8'd3	: begin valid <= 0; keycode[3] <= PS2_DAT; end	
            8'd4	: begin valid <= 0; keycode[4] <= PS2_DAT; end
            
            8'd5	: begin valid <= 0; keycode[5] <= PS2_DAT; end
            8'd6	: begin valid <= 0; keycode[6] <= PS2_DAT; end		
            8'd7	: begin valid <= 0; keycode[7] <= PS2_DAT; end
            8'd8	: begin valid <= 0; keycode[8] <= PS2_DAT; end
            
            8'd9	: begin valid <= 1; keycode[9] <= PS2_DAT; end // parity
            8'd10   : begin valid <= 1; keycode[10] <= PS2_DAT; end // stop
            8'd11	: begin valid <= 1; end 
            8'd12	: begin valid <= 1; end
        endcase
end


/*
*   Below are for testing purposes
*   Based on the keycode value, display on 7 segment display
*/
parameter sseg_up = 14'b10000010001100;
parameter sseg_down = 14'b01000010100011;
parameter sseg_left = 14'b10001110000110;
parameter sseg_right = 14'b01011111001111;

parameter sseg_enter = 14'b00001100101011;  	// enter
parameter sseg_space = 14'b00100100001100;      // space

parameter sseg_off   = 7'b1111111;		        // display off

// initiallize hex_out
reg [13:0] hex_out = {sseg_off, sseg_off};

always @( posedge CLK_50 ) begin
    if (valid) begin
        case (keycode[8:1])
            keycode_up: hex_out <= sseg_up;       // arrows
            keycode_down: hex_out <= sseg_down;
            keycode_left: hex_out <= sseg_left;
            keycode_right: hex_out <= sseg_right;

            keycode_enter: hex_out <= sseg_enter; // enter
            keycode_space: hex_out <= sseg_space; // space
        endcase
    end
end


/* assign output */
always HEX0 <= hex_out[6:0];
always HEX1 <= hex_out[13:7];
assign HEX2 = sseg_off; // not using hex2 to hex5
assign HEX3 = sseg_off;
assign HEX4 = sseg_off;
assign HEX5 = sseg_off;

endmodule
