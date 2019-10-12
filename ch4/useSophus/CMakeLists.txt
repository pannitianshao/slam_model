cmake_minimum_required( VERSION 2.8 )
project( useSophus )

# 为使用 sophus，您需要使用find_package命令找到它
# find_package命令报错  需要安装sophus  然后添加路径 https://app.yinxiang.com/Home.action?_sourcePage=nftl4-A1vvDiMUD9T65RG_YvRLZ-1eYO3fqfqRu0fynRL_1nukNa4gH1t86pc1SP&__fp=aT6hGj5W11o3yWPvuidLz-TPR6I9Jhx8&hpts=1564410311280&showSwitchService=true&usernameImmutable=false&rememberMe=true&login=&login=%E7%99%BB%E5%BD%95&login=true&username=626032672%40qq.com&hptsh=6y7MExWhnRX%2FMS7jGuFRTm3hod0%3D#n=0e1e1b06-3c74-480f-b178-57adad1fa3a6&s=s31&ses=4&sh=2&sds=2&
find_package( Sophus REQUIRED )
include_directories( ${Sophus_INCLUDE_DIRS} )

add_executable( useSophus useSophus.cpp )
target_link_libraries( useSophus ${Sophus_LIBRARIES} )