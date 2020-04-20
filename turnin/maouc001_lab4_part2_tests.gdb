# Test file for "CS120B_LAB4"
# commands.gdb provides the following functions for ease:
#   test "<message>"
#       Where <message> is the message to print. Must call this at the beginning of every test
#       Example: test "PINA: 0x00 => expect PORTC: 0x01"
#   checkResult
#       Verify if the test passed or failed. Prints "passed." or "failed." accordingly, 
#       Must call this at the end of every test.
#   expectPORTx <val>
#       With x as the port (A,B,C,D)
#       The value the port is epected to have. If not it will print the erroneous actual value
#   setPINx <val>
#       With x as the port or pin (A,B,C,D)
#       The value to set the pin to (can be decimal or hexidecimal
#       Example: setPINA 0x01
#   printPORTx f OR printPINx f 
#       With x as the port or pin (A,B,C,D)
#       With f as a format option which can be: [d] decimal, [x] hexadecmial (default), [t] binary 
#       Example: printPORTC d
#   printDDRx
#       With x as the DDR (A,B,C,D)
#       Example: printDDRB

echo ======================================================\n
echo Running all tests..."\n\n


# test sequence from Init:  A1,!A1  => PORTC: 0x06
 test "PINA: 0x02, 0x00 => PORTC: 0x06, state: DecrementWait"
 set state = Start
 setPINA 0x02
 continue 5
 setPINA 0x00
 continue 5
 expectPORTC 0x06
 expect state DecrementWait
 checkResult

# test sequence from Init:  A0,!A0  => PORTC: 0x08
 test "PINA: 0x01, 0x00 => PORTC: 0x08, state: IncrementWait"
 set state = Start
 setPINA 0x01
 continue 5
 setPINA 0x00
 continue 5
 expectPORTC 0x08
 expect state IncrementWait
 checkResult

#test sequence from Init:  A1,A1 A0  => PORTC: 0x00
 test "PINA: 0x02, 0x03 => PORTC: 0x00, state: S0"
 set state = Start
 setPINA 0x02
 setPINA 0x03
 continue 5
 expectPORTC 0x00
 expect state S0
 checkResult

#test sequence from Init:  A0, A1 A0  => PORTC: 0x00
 test "PINA: 0x01, 0x03 => PORTC: 0, state: S0"
 set state = Start
 setPINA 0x01
 setPINA 0x03
 continue 5
 expectPORTC 0x00
 expect state S0
 checkResult

#test sequence from Incrementwait:  A0  => PORTC: 0x09
 test "PINA: 0x01 => PORTC: 0, state: S9"
 set state = IncrementWait
 set Tick::cnt = 0x08
 setPINA 0x01
 continue 5
 expectPORTC 0x09
 expect state S9
 checkResult




# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
