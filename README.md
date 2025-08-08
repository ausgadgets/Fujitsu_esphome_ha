My Own version of the Fujitsu HeatPump and climate control code.

This version works for me in my environment and happy to share.

Code heavily inspired by unreality and rabbit-aaron who should
take most of the praise for their awesome work.

This is a version that works for me, and resolves issues such as:
1. Boot looping.
2. Having to send the same command more than once.
3. Having to get the sequence of turning off on on again the
   main controller to get it to sync up.
4. Issues with the serial code blocking processes.
5. Added ability to specify the serial/gpio ports in the .YAML file
6. Added ability to turn on logging from the YAML file.
7. General code robustness changes.

I am not a programmer, just a Home Assistant and reverse engineering enthusiast.
I hope it helps someone...
