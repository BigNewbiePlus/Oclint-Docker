搭建oclint编译环境
====================
# 各文件目录介绍
1.Dockerfile dokcer构建文件<br>
2.oclint-rules 创建的oclint-rules, 可以直接和容器内VOLUMN映射<br>
# 搭建oclint环境
`docker build -t bignewbie/oclint .`
# 使用镜像创建容器
使用-v将本项目下oclint-rules和容器内oclint-rules映射:<br>
`docker run -ti --rm -v /home/fdh/oclint-docker/oclint-rules:/usr/src/app/oclint/oclint-rules bignewbie/oclint /bin/bash`
# Error: stddef.h cannt find
在TestRuleOnCode.cpp文件中添加clang头文件参数 `I/usr/src/app/oclint/build/llvm-install/lib/clang/5.0.0/include`<br>
可以使用以下命令获取clang头文件<br>
`./clang-check test.cc -- -c -v`<br>

