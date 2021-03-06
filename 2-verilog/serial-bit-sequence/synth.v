/* Generated by Yosys 0.9 (git sha1 UNKNOWN, gcc 10.2.0 -march=x86-64 -mtune=generic -O2 -fno-plt -fPIC -Os) */

(* src = "serial.v:2" *)
module serial(error, Din, clk, reset);
  wire _00_;
  wire _01_;
  wire _02_;
  wire _03_;
  wire _04_;
  wire _05_;
  (* src = "serial.v:4" *)
  input Din;
  (* src = "serial.v:4" *)
  input clk;
  (* onehot = 32'd1 *)
  reg [4:0] current_state;
  (* src = "serial.v:3" *)
  output error;
  (* src = "serial.v:4" *)
  input reset;
  assign _05_ = current_state[3] & ~(Din);
  assign _04_ = _05_ | current_state[2];
  assign _03_ = current_state[1] | current_state[4];
  assign _02_ = current_state[3] & Din;
  assign _00_ = current_state[0] & ~(Din);
  assign _01_ = current_state[0] & Din;
  assign error = Din & current_state[4];
  always @(posedge clk or negedge reset)
    if (!reset)
      current_state[0] <= 1;
    else
      current_state[0] <= _03_;
  always @(posedge clk or negedge reset)
    if (!reset)
      current_state[1] <= 0;
    else
      current_state[1] <= _04_;
  always @(posedge clk or negedge reset)
    if (!reset)
      current_state[2] <= 0;
    else
      current_state[2] <= _00_;
  always @(posedge clk or negedge reset)
    if (!reset)
      current_state[3] <= 0;
    else
      current_state[3] <= _01_;
  always @(posedge clk or negedge reset)
    if (!reset)
      current_state[4] <= 0;
    else
      current_state[4] <= _02_;
endmodule
