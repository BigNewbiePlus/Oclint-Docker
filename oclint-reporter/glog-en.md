glog defact information
=======================
### k401(NonVoidFunctionShouldReturnAValue)
**Explanation of k401:** The function should return a value according to the definition, however, it not.<br>
1.1 [glog/src/utilities_unittest.cc 53:1 ](glog/src/utilities_unittest.cc#L53)<br>
**error message:** Non-void function should return a value.<br>
**code sample:**
```
 int main(int argc, char **argv) {
   InitGoogleLogging(argv[0]);
   InitGoogleTest(&argc, argv);

   CHECK_EQ(RUN_ALL_TESTS(), 0);
 }
```
### k404(TwoFunctionBodyEquivalenit)
**Explanation of k404:** the body of two function equals, Perhaps write just one.<br>
1.1 [glog/src/symbolize_unittest.cc 92](glog/src/symbolize_unittest.cc#L87-L95) <br>
**error message:** It is odd that the body of 'nonstatic_func(line:87-90)' function is fully equivalent to the body of 'static_func(line:92-95)' function.<br>
**code sample:**
```
 extern "C" {
 void nonstatic_func() {
   volatile int a = 0;
   ++a;
 }

 static void static_func() {
   volatile int a = 0;
   ++a;
 }
 }
```
### k421(IdenticalSubExprs)
**Explanation of k421:** The left and right subexpression of binary expression is identical.<br>
1.1 [glog/src/logging_unittest.cc 360](glog/src/logging_unittest.cc#L360) <br>
**error message:** '1' repeated in expression '1==1' !<br>
**code sample:**
```
RAW_CHECK(1 == 1, "should be ok");
```
### k422(ConstantValueWithZeroPrefix)
**Explanation of k422:** const value with zero prefix means octal form, be careful when using.<br>
1.1 [glog/src/logging_unittest.cc 775](glog/src/logging_unittest.cc#L775) <br>
**error message:** Be advised that the utilized constant value is represented by an octal form.<br>
**code sample:**
```
CHECK_ERR(fd = open(path, O_RDWR | O_CREAT | O_TRUNC, 0600));
```
