// 4x4 async memory, so not clock driven
module async
    (output reg [3:0] data_out,
     input reg [1:0] address,
     input wire write, // drive high if you want to write
     input wire [3:0] data_in);

    reg [3:0] memory [0:3];

    always @ (*)
        if (write)  memory[address] = data_in;
        else        data_out        = memory[address];

endmodule
