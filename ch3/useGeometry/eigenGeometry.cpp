#include <iostream>
#include <cmath>
using namespace std;

#include <Eigen/Core>
// Eigen 几何模块
#include <Eigen/Geometry>

/****************************
* 本程序演示了 Eigen 几何模块的使用方法
****************************/
// cout<<"debug = "<< v <<endl;
int main ( int argc, char** argv )
{
    // Eigen/Geometry 模块提供了各种旋转和平移的表示
    // 3D 旋转矩阵直接使用 Matrix3d 或 Matrix3f
    // Matrix3d 实质上是 Eigen::Matrix<double, 3, 3>
    // Identity()为赋值一个单位阵
    Eigen::Matrix3d rotation_matrix = Eigen::Matrix3d::Identity();
    // rotation_matrix = 2 * rotation_matrix;
    // cout<<"debug = "<< rotation_matrix <<endl;
    // 旋转向量使用 AngleAxis, 它底层不直接是Matrix，但运算可以当作矩阵（因为重载了运算符）
    // 利用罗德里格斯公式将旋转轴跟旋转角转化成旋转矩阵
    Eigen::AngleAxisd rotation_vector ( M_PI/4, Eigen::Vector3d ( 0,0,1 ) );     // 沿 Z 轴旋转 45 度
    cout .precision(3);                                                          // 配置输出格式输出小数点后三位
    cout<<"rotation matrix =\n"<<rotation_vector.matrix() <<endl;                // 用matrix()转换成矩阵
    // Eigen::Matrix3d rotation_matrix_new = rotation_vector.matrix() * rotation_matrix;
    // cout<<"debug = "<< rotation_matrix_new <<endl;

    // 也可以直接赋值
    // 角度和旋转轴已经在创建变量rotation_vector中声明了
    rotation_matrix = rotation_vector.toRotationMatrix();                        // 成员函数对矩阵进行变换
    cout<<"rotation matrix =\n"<<rotation_matrix <<endl;
   
    // 用 AngleAxis 可以进行坐标变换
    // Vector3d 实质上是 Eigen::Matrix<double, 3, 1>，即三维向量
    Eigen::Vector3d v ( 1,0,0 );
    Eigen::Vector3d v_rotated = rotation_vector * v;
    cout<<"(1,0,0) after rotation = "<<v_rotated.transpose()<<endl;
    // 或者用旋转矩阵
    v_rotated = rotation_matrix * v;
    cout<<"(1,0,0) after rotation = "<<v_rotated.transpose()<<endl;   // .transpose()求矩阵的转置

    // 欧拉角: 可以将旋转矩阵直接转换成欧拉角
    // 其中eulerAngles()的三个参数表示旋转顺序。0,1,2分别代表X,Y,Z
    Eigen::Vector3d euler_angles = rotation_matrix.eulerAngles ( 2,1,0 ); //2 1 0 ZYX顺序，即yaw roll pitch顺序
    cout<<"yaw roll pitch = "<<(euler_angles /M_PI * 180).transpose()<<endl; //弧度转化为角度

    // 欧氏变换矩阵使用 Eigen::Isometry 4*4矩阵 
    Eigen::Isometry3d T=Eigen::Isometry3d::Identity();                // 虽然称为3d，实质上是4＊4的矩阵
    // cout<<"debug = \n"<<T.matrix() <<endl;
    T.rotate ( rotation_vector );                                     // 按照rotation_vector进行旋转
    T.pretranslate ( Eigen::Vector3d ( 1,3,4 ) );                     // 把平移向量设成(1,3,4)
    cout << "Transform matrix = \n" << T.matrix() <<endl;

    // 用变换矩阵进行坐标变换
    // 虽然T是4*4 v是3*1  但是函数库重新定义了*运算符，可以直接相乘
    Eigen::Vector3d v_transformed = T*v;                              // 相当于R*v+t
    cout<<"v tranformed = "<<v_transformed.transpose()<<endl;

    // 对于仿射和射影变换，使用 Eigen::Affine3d 和 Eigen::Projective3d 即可，略

    // 四元数
    // 可以直接把AngleAxis赋值给四元数，反之亦然
    Eigen::Quaterniond q = Eigen::Quaterniond ( rotation_vector );
    cout<<"quaternion = \n"<<q.coeffs() <<endl;   // 请注意coeffs的顺序是(x,y,z,w),w为实部，前三者为虚部
    // 也可以把旋转矩阵赋给它
    q = Eigen::Quaterniond ( rotation_matrix );
    cout<<"quaternion = \n"<<q.coeffs() <<endl;
    // 使用四元数旋转一个向量，使用重载的乘法即可
    v_rotated = q * v;                       // 注意数学上是qvq^{-1}
    // v_rotated = rotation_matrix * v;      // 旋转矩阵 * 初始向量
    cout<<"(1,0,0) after rotation = "<<v_rotated.transpose()<<endl;

    return 0;
}
