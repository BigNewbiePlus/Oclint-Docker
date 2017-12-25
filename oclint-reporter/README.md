基于Most stars排序统计静态缺陷集合
=================================

#项目信息
项目名称  star数     大小    行数   生成json编译配置        项目简述          缺陷个数  
flatbuffers 8.7k     11M    28540       Y                 数据序列化
asmjit      1.2k     7.8M   60854       Y
pugixml     1.2k     9.2M   30449       Y
xlearn      1.4k     31M    48217       Y
cereal      1.4k     22M    23687       Y                   
glog        1.8k     4.8M   7955        Y                 谷歌日志模块
msgpack-c   1.2k     24M    26231       Y                  MessagePack实现
tinyxml2    1.9k     6.5M   7993        Y                  XML解析器
#统计信息
##msgpack-c统计信息
错误类型    总个数     缺陷个数
k401          19         10
k402        1           0
k403        2          0
k403        1          0
k404        18          0
k405        5          5

##asmjit统计数据
k401       20       0
k405       58       58
k406       4        0
k407       2        2
k408       6        6
k403      19       5
k409       8       1
k404       2       0
k410       1       1
k411       2       0
k412       5       0
k413       9       9
k414       4       4
k415       1       1
k416       4       2
k417       5      0
k418      3       1
#pugixml统计数据
k404      5       1
k405      8       8
k401      5       0
#xlearn统计概率
k403      7      4
k419      4       2
k420      3       3
k421      1       1
k410      1       1
# 缺陷id和name对照表
id                   name
k401        NonVoidFunctionShouldReturnAValue
K402        TwoIfStmtWithIdenticalCondtion
K403       IdenticalAlongsideIfCondition
K404       TwoFunctionBodyEquivalenit
k405       InvalidPointToLocalVariable
k406       AssignInCondition
k407       OperationLogic
k408       TruncationOf
k409       AssignSameVariable
k410       SameReturnValue
k411       ElseBlock
k412       RepeatedIfCondition
k413       PointerUnary
k414       ConstResultAccord
k415       ContinueWillTer
k416       UnconditionalBreak
k417       RecuringCheck
k418       InitAndFinal
k419       SameArgumentForFunction
k420       ThenAndElseBody
k421       IdenticalSubExprs
