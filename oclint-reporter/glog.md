glog统计信息
=======================
### k401(NonVoidFunctionShouldReturnAValue)
1.1 [utilities_unittest.cc 53:1 ](glog/src/utilities_unittest.cc)<br>
错误信息: Non-void function should return a value.<br>
代码:
```
 int main(int argc, char **argv) {
   InitGoogleLogging(argv[0]);
   InitGoogleTest(&argc, argv);

   CHECK_EQ(RUN_ALL_TESTS(), 0);
 }
```
### k404(TwoFunctionBodyEquivalenit)
1.1 [symbolize_unittest.cc 92](glog/src/symbolize_unittest.cc) <br>
错误信息: It is odd that the body of 'nonstatic_func(line:87-90)' function is fully equivalent to the body of 'static_func(line:92-95)' function.<br>
代码:
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
1.1 [logging_unittest.cc 360](glog/src/logging_unittest.cc) <br>
错误信息: '1' repeated in expression '1==1' !<br>
代码:
```
RAW_CHECK(1 == 1, "should be ok");
```
### k422(ConstantValueWithZeroPrefix)
1.1 [logging_unittest.cc 775](/glog/src/logging_unittest.cc) <br>
信息：Be advised that the utilized constant value is represented by an octal form.
代码
```
CHECK_ERR(fd = open(path, O_RDWR | O_CREAT | O_TRUNC, 0600));
```
