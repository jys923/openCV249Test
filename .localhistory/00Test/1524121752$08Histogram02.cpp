#include <stdafx.h>
// ��� ���� ����
class Histogram1D {
private:
	int histSize[1]; // �󵵼�
	float hranges[2]; // �ּ�/�ִ� ȭ�Ұ�
	const float* ranges[1];
	int channels[1]; // ���⼭ 1ä�θ� ���
public:
	Histogram1D() { // 1���� ������׷��� ���� ���� �غ�
		histSize[0] = 256;
		hranges[0] = 0.0;
		hranges[1] = 255.0;
		ranges[0] = hranges;
		channels[0] = 0; // �⺻������ ä���� 0���� ����
	}

	// ������ ��� ������ �׷��̷��� ������ ������׷��� ����� ���� ���� �޼ҵ带 ����� ����
	cv::MatND getHistogram(const cv::Mat &image) {
		// 1����(1D) ������׷� ���.
		cv::MatND hist;
		cv::calcHist(&image, // ������׷� ��� 
			1,   // ���� ������ ������׷���
			channels, // ��� ä��               
			cv::Mat(), // ����ũ ������� ����     
			hist,  // ��� ������׷�         
			1,   // 1����(1D) ������׷�           
			histSize, // �󵵼�                  
			ranges  // ȭ�Ұ� ����             
		);
		return hist;
	}

	// ���� ���������� �ǹ̸� �ľ��ϱ� �����Ƿ� �� �׷����� ���
	// �׷����� �����ϴ� �޼ҵ�
	cv::Mat getHistogramImage(const cv::Mat &image) {
		// 1����(1D) ������׷��� ����ϰ�, �������� ��ȯ

		cv::MatND hist = getHistogram(image); // ���� ������׷� ���

		double maxVal = 0; // �ִ� �󵵼� ��������
		double minVal = 0; // �ּ� �󵵼� ��������
		cv::minMaxLoc(hist, &minVal, &maxVal, 0, 0);

		cv::Mat histImg(histSize[0], histSize[0], CV_8U, cv::Scalar(255));
		// ������׷��� ����ϱ� ���� ����

		int hpt = static_cast<int>(0.9*histSize[0]);
		// nbins�� 90%�� �ִ������� ����


		for (int h = 0; h<histSize[0]; h++) { // �� �󵵿� ���� �������� �׸��� 
			float binVal = hist.at<float>(h);
			int intensity = static_cast<int>(binVal*hpt / maxVal);
			cv::line(histImg, cv::Point(h, histSize[0]), cv::Point(h, histSize[0] - intensity), cv::Scalar::all(0));
			// �� �� ���� �Ÿ��� �׸��� �Լ�
		}
		return histImg;
	}
};

int main()
{
	cv::Mat image = cv::imread("batgirl.jpg", 0);
	// �Է� ���� �б�
	// ���� �������� ������ ����
	if (!image.data)
		return 0;

	cv::namedWindow("Image");
	cv::imshow("Image", image);

	Histogram1D h; // ������׷� ��ü
	cv::MatND histo = h.getHistogram(image); // ������׷� ���

	for (int i = 0; i<256; i++) // �� �� ��ȸ
		std::cout << "Value " << i << " = " << histo.at<float>(i) << std::endl;

	cv::namedWindow("Histogram");
	cv::imshow("Histogram", h.getHistogramImage(image));
	// ������׷��� �������� ����
	// ����� �߽����� ������ ������, �������� �����
	// ��� ���츮 �κ��� �߰� ��ϵ� ��
	// ������ ������ ����, �������� ���

	// ������ �� �׷����� ������ �κ��� ��谪���� ó���� Ȯ��
	cv::Mat thresholded; // ��谪���� ���� ���� ����
	cv::threshold(image, thresholded, 60, 255, cv::THRESH_BINARY);
	// ������ ���ȭ �ϱ� ���� ������׷��� 
	// ���� ���츮(��ϰ� 60) �������� �����ϱ� ������ �ּҰ����� ����.
	cv::namedWindow("Binary Image"); // ���ȭ�� ���� ��� ����
	cv::imshow("Binary Image", thresholded); // ���� ������ ���ҵ�

	cv::waitKey(0);

	return 0;
}