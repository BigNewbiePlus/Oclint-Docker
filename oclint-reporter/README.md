基于Most stars排序统计静态缺陷集合
=================================

# 项目信息
    项目名称  star数     大小    行数   生成json编译配置           项目简述          
    flatbuffers 8.7k     11M    28540       Y                 数据序列化
    tinyxml2    1.9k     6.5M   7993        Y                  XML解析器
    glog        1.8k     4.8M   7955        Y                 谷歌日志模块
    xlearn      1.4k     31M    48217       Y                  机器学习包
    asmjit      1.2k     7.8M   60854       Y                JIT和远程编译单元
    pugixml     1.2k     9.2M   30449       Y                 XML处理单元
    msgpack-c   1.2k     24M    26231       Y                 MessagePack实现
# 统计信息
    错误类型    总个数     缺陷个数
## flatbuffer统计信息
    k405      4       4
    k413      2       2
    k417      1       1
## tinyxml2统计信息
    k405      3      1
    k419      6      0
    k424      1      1
## glog统计信息
    k401      1      1
    k404      1      1
    k421      3      1
    k422      1      1
## xlearn统计信息
    k403      7      4
    k420      3      3
    k421      1      1
## asmjit统计信息
    k403      19      5
    k405      58      33
    k407      2       2
    k408      6       6
    k409      8       1
    k410      1       1
    k413      9       2
    k415      1       1
    k416      5       1
## pugixml统计信息
    k404      5       1
    k405      8       3
## msgpack-c统计信息
    k401      11      10
    k405      5       5
## 缺陷id和name对照表
    id                   name
    k401        NonVoidFunctionShouldReturnAValue
    K402        TwoIfStmtWithIdenticalCondtion
    K403       IdenticalAlongsideIfCondition
    K404       TwoFunctionBodyEquivalenit
    k405       InvalidPointToLocalVariable
    k406       AssignInCondition
    k407       OperationLogicNotCorrespondWithItsFormat
    k408       TruncationOfConstantValue
    k409       AssignSameVariableTwiceSuccessively
    k410       SameReturnValueOfConditionalOperator
    k411       ElseBlockWasPossibleForgottenOrCommentOut
    k412       RepeatedIfCondition
    k413       PointerUnaryAndDerefConfuse
    k414       ConstResultAccordToValueRange
    k415       ContinueWillTerminateDoWhileFalseLoop
    k416       UnconditionalBreakWithinALoop
    k417       RecuringCheck
    k418       InitAndFinalForIteratorValueAreSame
    k419       SameArgumentForFuncCall
    k420       ThenAndElseBodyEquivalent
    k421       IdenticalSubExprs
    k422       ConstantValueWithZeroPrefix
    k423       OddFloatPreciseComparision
    k424       CmpFuncUseInCondition

# 具体缺陷举例
* [flatbuffers缺陷详解](flatbuffer.md)
* [tinyxml2缺陷详解](tinyxml2.md)
* [glog缺陷详解](glog.md)
* [xlearn缺陷详解](xlearn.md)
* [asmjit缺陷详解](asmjit.md)
* [pugixml缺陷详解](pugixml.md)
* [msgpack-c缺陷详解](msgpack-c.md)

# 具体缺陷举例(英文版，给开发者)
* [flatbuffers defact](flatbuffer-en.md)
* [tinyxml2 defact](tinyxml2-en.md)
* [glog defact](glog-en.md)
* [xlearn defact](xlearn-en.md)
* [asmjit defact](asmjit-en.md)
* [pugixml defact](pugixml-en.md)
* [msgpack-c defact](msgpack-c-en.md)
## 写给开发者
Dear xxx:
        I am xxx and come from Beijing University Of Posts and Telecommunications. I wrote a static code analysis tool and use it check the
        proeject 'xxx'. There is a few mistake i can't judge. would you mind spending a few minutes to help me . I have write it formly in github, it's eazy to check, maybe a few minutes.<br>
  Yours<br>
  2017/12/29<br>
