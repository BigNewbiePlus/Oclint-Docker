xlearn defact information
=======================
### k420(ThenAndElseBodyEquivalent)
**Explanation of k420:** The then body and else body of if expression equal, error occurs.<br>
1.1 [xlearn/src/reader/reader_test.cc 100:3](xlearn/src/reader/reader_test.cc#L100)<br>
**error message:** The 'then' statement is equivalent to the 'else' statement.<br>
**code sample:**
```
...
if (disk) {
     EXPECT_EQ(matrix->row_length, kNumLines);
   } else {
     EXPECT_EQ(matrix->row_length, kNumLines);
   }
...
```
same error in [xlearn/src/reader/reader_test.cc 127:3](xlearn/src/reader/reader_test.cc#L127)  <br>
same error in [xlearn/src/reader/reader_test.cc 154:3](xlearn/src/reader/reader_test.cc#L154)<br>
### k421(IdenticalSubExprs)
**Explanation of k421:** The left and right subexpression of binary expression is identical.<br>
1.1 [xlearn/src/loss/metric_test.cc 116:32](xlearn/src/loss/metric_test.cc#L116) <br>
**error message:** '2.0' repeated in expression '2.0/2.0' !<br>
**code sample:**
```
...
XPECT_FLOAT_EQ(metric_val, (2.0 / 2.0));
...
```
