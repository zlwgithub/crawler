#include <QtCore/QCoreApplication>
#include<iostream>
#include"Service.h"
#include"QQPimRequest.h"
#include "dealData.h"

using namespace std;

string hashDecode(string qrsig)
{
    //hash 33，解密ptqrtoken
    int e = 0;
    for (int i = 0; i < qrsig.length(); i++) {
        e += (e << 5) + qrsig[i];
    }
    return to_string(e & 2147483647);

}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    //
    /*re.fetchWXloginCode();
    int b;
    cin >> b;
    if (b == 1) {
        re.fetchQrConnect();
        re.confirmLogin();
        re.contact();
    }*/
   /* string sig = "9c264b87e7adaf8a7ae9477bdbf93445382e4113614ee333880c18a6759b97bc4e9b935cbdca0e71477a65f82a147c436a3faf8456ebe8e61c09707c9279cc64";
    cout << hashDecode (sig)<< endl;*/
    
    dealData d;
    d.dealDataBaseContact();
    d.dealDataBaseTel();

    //int b;
    //CQQPimRequest re;

    ////获取qq二维码
    //re.fetchQQloginCode();
    //cin >> b;
    ////扫码后输入1开始请求数据
    //if (b == 1) {
    //    re.waitScan();
    //    re.auth();
    //    re.auth2();
    //    re.qqContact();
    //    re.callLog(1);
    //}

    Service sv;
    sv.GET_QRCODE_MSG_callback();
    int b;
    cin >> b;
    if (b == 1) {
        sv.QRCODE_CONFRIM_MSG_callback();
        sv.START_CRAWL_CONTACT_MSG_callback();
        sv.START_CRAWL_callLog_MSG_callback();
    }




    


    //int b;
    //re.fetchQQloginCode();
    //cin >> b;
    //if (b == 1) {
    //    re.waitScan(); 
    //    re.auth();
    //    re.auth2();
    //    
    //    re.callLog(1);
    //    //re.callLog("2");
    //}
    
    /*string std_str("./tel1.txt");
    QString filepath = QString::fromStdString(std_str);
    dealData dd;
    dd.dealJsonTel(filepath);*/

    /*dealData dd;
    dd.dealDataBase();*/


    std::cout << "结束" << std::endl;
    return a.exec();
    
}
