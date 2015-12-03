Compile using make all

core file size should always be set to 0 when running server
ulimit -c 0

First run the vulnerable program: ./server
Then run the attack program: ./client

The attack program searches for the memory address of the target function hidden()
It uses responses from the vulnerable server to determine the next string that it
should send. The vulnerable server catches several signals in order to continue
operating while under attack.
