基于Most stars排序统计静态缺陷集合
=================================

# 项目信息
    项目名称  star数     大小    行数   生成json编译配置        项目简述          缺陷个数  
    flatbuffers 8.7k     11M    28540       Y                 数据序列化
    tinyxml2    1.9k     6.5M   7993        Y                  XML解析器
    glog        1.8k     4.8M   7955        Y                 谷歌日志模块
    xlearn      1.4k     31M    48217       Y                  机器学习包
    asmjit      1.2k     7.8M   60854       Y                   JIT和远程编译单元
    pugixml     1.2k     9.2M   30449       Y                  XML处理单元
    msgpack-c   1.2k     24M    26231       Y                  MessagePack实现
# 统计信息
## flatbuffer统计信息
    k405      4       4
    k413      2       2
    k414      3       3
    k417     1        1
## tinyxml2统计信息
    k405      3      3
    k419      6      6
    k424      1      1
## glog统计信息
    k401      1      1
    k404      1      1
    k421      3      3
    k422      1      1
## xlearn统计信息
    k403      7      4
    k410      1       1
    k419      4       2
    k420      3       3
    k421      1       1
## asmjit统计信息
    k403      19       5
    k405       58       58
    k407       2        2
    k408       6        6
    k409       8       1
    k410       1       1
    k413       9       9
    k414       4       4
    k415       1       1
    k416       4       2
    k418      3       1
## pugixml统计信息
    k404      5       1
    k405      8       8
## msgpack-c统计信息
    错误类型    总个数     缺陷个数
    k401          19         10
    k405          5          5
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
[flatbuffers缺陷详解](flatbuffer.md)
[tinyxml2缺陷详解](tinyxml2.md)
[glog缺陷详解](glog.md)
[xlearn缺陷详解](xlearn.md)
[asmjit缺陷详解](asmjit.md)
[pugixml缺陷详解](pugixml.md)
[msgpack-c缺陷详解](msgpack-c.md)
