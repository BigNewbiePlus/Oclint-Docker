xlearn统计信息
=======================
### k420(ThenAndElseBodyEquivalent)
1.1 [xlearn/src/reader/reader_test.cc 100:3](xlearn/src/reader/reader_test.cc#L100)<br>
错误信息: The 'then' statement is equivalent to the 'else' statement.<br>
代码:
```
...
if (disk) {
     EXPECT_EQ(matrix->row_length, kNumLines);
   } else {
     EXPECT_EQ(matrix->row_length, kNumLines);
   }
...
```
1.2 同样错误发生在 [xlearn/src/reader/reader_test.cc 127:3](xlearn/src/reader/reader_test.cc#L127)  <br>
[xlearn/src/reader/reader_test.cc 154:3](xlearn/src/reader/reader_test.cc#L154)<br>
### k421(IdenticalSubExprs)
1.1 [xlearn/src/loss/metric_test.cc 116:32](xlearn/src/loss/metric_test.cc#L116) <br>
'2.0' repeated in expression '2.0/2.0' !<br>
代码:
```
...
XPECT_FLOAT_EQ(metric_val, (2.0 / 2.0));
...
```
