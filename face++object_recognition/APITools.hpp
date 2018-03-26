#include<opencv2/opencv.hpp>  
#include<iostream>  
#include<vector>  
#include<string>  
#include"curl/curl.h"
#include"Zbase64.h"
//#pragma warning (push)
//#pragma warning (disable: 4996)
#include"json/json.h"
//#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
using namespace std;
using namespace cv;
#pragma comment(lib,"lib_json.lib")
#pragma comment(lib,"LIBCURL.LIB")

string outer_id = "firstfaceset_token";
int writer(char *data, size_t size, size_t nmemb, string *writerData)
{
	if (writerData == NULL)
		return 0;
	int len = size*nmemb;
	writerData->append(data, len);
	return len;
}
class faceplusplusApi
{
public:
	faceplusplusApi();
	~faceplusplusApi();
	string Objectrecognition(Mat inputimg);
private:
	
};

faceplusplusApi::faceplusplusApi()
{
	
	
}

faceplusplusApi::~faceplusplusApi()
{
}

inline string faceplusplusApi::Objectrecognition(Mat inputimg)
{
	//Mat src = imread("timg.jpg");
	vector<uchar> vecImg;                               //Mat 图片数据转换为vector<uchar>  
	vector<int> vecCompression_params;
	vecCompression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
	vecCompression_params.push_back(90);
	imencode(".jpg", inputimg, vecImg, vecCompression_params);

	ZBase64 base64;
	String imgbase64 = base64.Encode(vecImg.data(), vecImg.size());     //实现图片的base64编码  
	string buffer;
	CURL *curl;
	CURLcode res;
	struct curl_slist *http_header = NULL;
	struct curl_httppost *formpost = 0;
	struct curl_httppost *lastptr = 0;
	curl = curl_easy_init();
	curl_formadd(&formpost,
		&lastptr,
		CURLFORM_COPYNAME, "api_key",
		CURLFORM_COPYCONTENTS, "jlgTxl2mUrOoYrCOy39lKmCNsCmbZ0Nw",
		CURLFORM_END);
	curl_formadd(&formpost,
		&lastptr,
		CURLFORM_COPYNAME, "api_secret",
		CURLFORM_COPYCONTENTS, "ROU_X2AD0dtwV78NTu9mRqpqz4O89rVu",
		CURLFORM_END);
	curl_formadd(&formpost,
		&lastptr,
		CURLFORM_COPYNAME, "image_base64",
		CURLFORM_COPYCONTENTS, imgbase64.c_str(),
		CURLFORM_END);

	

	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
	curl_easy_setopt(curl, CURLOPT_URL, "https://api-cn.faceplusplus.com/imagepp/beta/detectsceneandobject");
	curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
	res = curl_easy_perform(curl);
	curl_easy_cleanup(curl);

	Json::Value root;
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(buffer, root);

	if (!parsingSuccessful)
	{
		cout << "Failed to parse the data!" << endl;
		exit(0);
	}
	cout << root["objects"][0]["value"];
	return buffer;
}
