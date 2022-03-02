module draw_background
(
    input vga_clk,
    input [9:0] x_pos,
    input [9:0] y_pos,
    input next_frame,
    input [23:0] bg_data,
    output logic [7:0] vga_r,
    output logic [7:0] vga_g,
    output logic [7:0] vga_b,
    output logic [9:0] bg_addr
);

    assign bg_addr = {y_pos[4:0], x_pos[4:0]};

    /*logic [23:0] bg_data_reg;
    always_ff @(posedge vga_clk) begin
        bg_data_reg <= bg_data;
    end*/

    logic [9:0] sqr_x;
    always_ff @(posedge next_frame) begin
        if (sqr_x >= 10'd540) begin
            sqr_x <= 10'b0;
        end
        else begin
            sqr_x <= sqr_x + 10'b1;
        end
    end

    logic line1, line2, line3, pipe1, pipe2;

    always_ff @(posedge vga_clk) begin
        if (y_pos >= 10'd 239 && y_pos <= 10'd241) begin
            line1 <= 1'b1;
        end
        else begin
            line1 <= 1'b0;
        end

        if (x_pos == 10'd200 || x_pos == 10'd201 || x_pos == 10'd439 || x_pos == 10'd440) begin
            pipe1 <= 1'b1;
        end
        else begin
            pipe1 <= 1'b0;
        end

        if (pipe1 && y_pos >= 380) begin
            line2 <= 1'b1;
        end
        else begin 
            line2 <= 1'b0;
        end

        if (y_pos == 10'd379 || y_pos == 10'd378) begin
            pipe2 <= 1'b1;
        end
        else begin
            pipe2 <= 1'b0;
        end 

        if (x_pos >= 10'd201 && x_pos <= 10'd441 && pipe2) begin
            line3 <= 1'b1;
        end
        else begin
            line3 <= 1'b0;
        end

        if (x_pos >= sqr_x && x_pos <= sqr_x + 10'd49 && y_pos <= 10'd49) begin
            vga_r <= 8'hff;
            vga_g <= 8'h0;
            vga_b <= 8'h0;
        end
        else if (line1 | line2 | line3) begin
            vga_r <= 8'h3a;
            vga_g <= 8'h28;
            vga_b <= 8'h08;
        end
        else begin 
            vga_r <= bg_data[23:16];
            vga_g <= bg_data[15:8];
            vga_b <= bg_data[7:0];
        end
    end

endmodule