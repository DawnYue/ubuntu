#include <iostream>
#include <chrono>
using namespace std;
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
int main ()
{
    cv::Mat image;
    image = cv::imread ( "../ubuntu.png" ); //cv::imread函数读取指定路径下的图像
    // 判断图像文件是否正确读取
    if ( image.data == nullptr ) //数据不存在,可能是文件不存在
    {
        cerr<<"文件不存在."<<endl;
        return 0;
    }
    // 文件顺利读取, 首先输出一些基本信息
    cout<<"图像宽为"<<image.cols<<",高为"<<image.rows<<",通道数为"<<image.channels()<<endl;
    cv::imshow ( "image", image );      // 用cv::imshow显示图像
    cv::waitKey ( 0 );                  // 暂停程序,等待一个按键输入
    // 判断image的类型
    if ( image.type() != CV_8UC1 && image.type() != CV_8UC3 )
    {
        // 图像类型不符合要求
        cout<<"请输入一张彩色图或灰度图."<<endl;
        return 0;
    }
    // 遍历图像, 请注意以下遍历方式亦可使用于随机像素访问
    // 使用 std::chrono 来给算法计时
    chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
    for ( size_t y=0; y<image.rows; y++ )
    {
        // 用cv::Mat::ptr获得图像的行指针
        unsigned char* row_ptr = image.ptr<uchar> ( y );  // row_ptr是第y行的头指针
        for ( size_t x=0; x<image.cols; x++ )
        {
            // 访问位于 x,y 处的像素
            unsigned char* data_ptr = &row_ptr[ x*image.channels() ]; // data_ptr 指向待访问的像素数据

            for ( int c = 0; c != image.channels(); c++ )// 输出该像素的每个通道,如果是灰度图就只有一个通道
            {
                unsigned char data = data_ptr[c]; // data为I(x,y)第c个通道的值
            }
        }
    }
    chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
    chrono::duration<double> time_used = chrono::duration_cast<chrono::duration<double>>( t2-t1 );

    return 0;
}
