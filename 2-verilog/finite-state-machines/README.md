Glitches can occur when more than two inputs change in the Verilog code. This can affect outputs, such as clocks, which are fed into other components that need stable rising/falling edge triggers.

General pattern to avoid glitches is to drive the output of a combinational circuit directly to a flip-flop before using it further (outside of FSM logic)

             ---------------------
            | combinational logic |                         -----
---input--->| 1. next state logic |---output-------------->|     |---glitch-free-output---->
        --->| 2. output logic     | |          ---clock--->| DFF |
        |    ---------------------  |          ---reset--->|     |
        |                           |                       -----
        |                           |
        |    ---------------------  |
         ---| sequential logic    |<-
            | only seq statements |<---clock---
            | flip-flops          |<---reset---
             ---------------------
