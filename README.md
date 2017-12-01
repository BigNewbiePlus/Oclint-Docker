#搭建oclint编译环境
##各文件目录介绍
1.Dockerfile dokcer构建文件<br>
2.oclint-rules 创建的oclint-rules, 可以直接和容器内VOLUMN映射<br>
##搭建oclint环境
`docker build -t bignewbie/oclint .`
##使用镜像创建容器
使用-v将本项目下oclint-rules和容器内oclint-rules映射:<br>
`docker run -ti --rm -v /home/fdh/oclint-docker/oclint-rules:/src/usr/app/oclint/oclint-rules bignewbie/oclint /bin/bash`
