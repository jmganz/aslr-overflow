Compile using "make all"

core file size should always be set to 0 when running server
"ulimit -c 0"

First run the vulnerable program: "./server"
Then run the attack program: "./client"

The attack program searches for the memory address of the target function hidden()
It uses responses from the vulnerable server to determine the next string that it
should send. The vulnerable server catches several signals in order to continue
operating while under attack.

The amount of entropy in the memory address of hidden() can be computed by first
starting "./runServer.sh", then start "./runClient.sh $LOGFILE"

When runClient.sh finishes executing, run "./entropy $LOGFILE"

Modify runClient.sh to choose how many times client executes
Choose the filename for $LOGFILE

Python programs are also provided to plot the values represented by each byte of
memory address. Run "./binaryToDec.sh $LOGFILE >> $DECIMALDATA" to convert the binary
values into groups of bytes represented in decimal.

Then run "python plot.addresses.py $DECIMALDATA" and
"python flatten.addresses.py $DECIMALDATA" to visualize the results
