视觉slam课本上用ppa安装出现问题  建议下载源代码安装
https://www.cnblogs.com/lifeofershisui/p/9037829.html
1.需要预安装依赖库。官网上提供了使用PPA安装，比较简单，但是之后安装时有错误。（ubuntu16.04 使用ppa预安装时，最后一句apt-get install libpcl-all 应该更改为apt-get install libpcl-dev（好像前者针对ubuntu14.04，后者才 针对ubuntu 16.04）,虽然可以运行成功，仍然不推荐，因为我采用这种方法后面还是有错误了！)
采用一下方式依次安装依赖库：

sudo apt-get update  
sudo apt-get install git build-essential linux-libc-dev  
sudo apt-get install cmake cmake-gui   
sudo apt-get install libusb-1.0-0-dev libusb-dev libudev-dev  
sudo apt-get install mpi-default-dev openmpi-bin openmpi-common    
sudo apt-get install libflann1.8 libflann-dev  
sudo apt-get install libeigen3-dev  
sudo apt-get install libboost-all-dev  
sudo apt-get install libvtk5.10-qt4 libvtk5.10 libvtk5-dev  
sudo apt-get install libqhull* libgtest-dev  
sudo apt-get install freeglut3-dev pkg-config  
sudo apt-get install libxmu-dev libxi-dev   
sudo apt-get install mono-complete  
sudo apt-get install qt-sdk openjdk-8-jdk openjdk-8-jre  
2.下载源码并编译

git clone https://github.com/PointCloudLibrary/pcl.git  
cd pcl  
mkdir release  
cd release  
cmake -DCMAKE_BUILD_TYPE=None -DCMAKE_INSTALL_PREFIX=/usr \  
  -DBUILD_GPU=ON -DBUILD_apps=ON -DBUILD_examples=ON \  
  -DCMAKE_INSTALL_PREFIX=/usr ..  
make -j4 (线程数根据情况选择)
sudo make  install  
测试
按照以上步骤直接生成.cpp文件运行会发现找不到头文件，原因是需要使用Cmake 编译（包括连接到PCL库等）
具体操作直接参照官网（http://pointclouds.org/documentation/tutorials/using_pcl_pcl_config.php#using-pcl-pcl-config）
步骤包括：
（1）.在project 文件夹下生成 pcd_write.cpp（见官网上提供的链接）
（2）.生成 CMakeLists.txt,直接复制一下内容（不需要任何修改）：

 cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
 project(MY_GRAND_PROJECT)
 find_package(PCL 1.3 REQUIRED COMPONENTS common io)
 include_directories(${PCL_INCLUDE_DIRS})
 link_directories(${PCL_LIBRARY_DIRS})
 add_definitions(${PCL_DEFINITIONS})
 add_executable(pcd_write_test pcd_write.cpp)
 target_link_libraries(pcd_write_test ${PCL_COMMON_LIBRARIES} ${PCL_IO_LIBRARIES})           
（3）.编译运行

 cd /PATH/TO/MY/GRAND/PROJECT （project 所在的文件夹）
 mkdir build
 cd build
 cmake ..
 make
 ./pcd_write_test
