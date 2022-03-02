module toplevel
(
    input CLOCK_50,
    input KEY[0],
    output logic VGA_CLK,
    output logic VGA_BLANK_N,
    output logic VGA_SYNC_N,
    output logic VGA_HS,
    output logic VGA_VS,
    output logic [7:0] VGA_R,
    output logic [7:0] VGA_G,
    output logic [7:0] VGA_B
);

    logic vga_clk;
    logic [9:0] x_pos, y_pos;
    logic [9:0] bg_mem_addr;
    logic [23:0] bg_data;
    assign VGA_CLK = vga_clk;

    clk_generator gen_vga_clk(
        .in_clk(CLOCK_50), 
        .scale_count(0), 
        .out_clk(vga_clk)
    );
    
    vga_controller vga_ctrl(
        .vga_clk(vga_clk),
        .reset(~KEY[0]),
        .vga_hs(VGA_HS),
        .vga_vs(VGA_VS),
        .vga_blank(VGA_BLANK_N),
        .vga_sync(VGA_SYNC_N),
        .x_pos(x_pos),
        .y_pos(y_pos)
    );

    draw_background draw_bg(
        .vga_clk(vga_clk),
        .x_pos(x_pos),
        .y_pos(y_pos),
        .vga_r(VGA_R),
        .vga_g(VGA_G),
        .vga_b(VGA_B),
        .next_frame(VGA_VS),
        .bg_data(bg_data),
        .bg_addr(bg_mem_addr)
    );

    bg_tex_mem bg_mem_inst(
        .address(bg_mem_addr),
        .clock(vga_clk),
        .q(bg_data)
    );

endmodule