#include "ImageDataClass.h"
#include "UtilityFunctions.h"

#include "AddVerticalPLinesSet.h"



AddVerticalPLinesSet::AddVerticalPLinesSet()
{
}


AddVerticalPLinesSet::~AddVerticalPLinesSet()
{
}

const char* AddVerticalPLinesSet::GetDescription()
{
	return "Define set of vertical parallel lines";
}


void AddVerticalPLinesSet::Run()
{
	ImageDataClass::GetInstance().m_imageVertPLinesPoints.clear();
	while (true)
	{
		if (ImageDataClass::GetInstance().m_image.empty())
		{
			std::cout << "No image is opened, first open the image." << std::endl;
			return;
		}

		ImLinePtsVec newLine = m_lineInsertObj.InsertLine(2); //arbitryry number of points (>1)
		if (newLine.size() > 0)
		{
			ImageDataClass::GetInstance().m_imageVertPLinesPoints.push_back(newLine);

			UpdateFigure(ImageDataClass::GetInstance().m_image0, newLine);
			ImageDataClass::GetInstance().m_image0.copyTo(ImageDataClass::GetInstance().m_image);
			ImageDataClass::GetInstance().m_imageUpdated = true;
		}
		else
		{
			if (ImageDataClass::GetInstance().CalculateVertVanishingPoint())
			{
				auto pt = ImageDataClass::GetInstance().m_verticalVanishingPoint;
				cv::line(ImageDataClass::GetInstance().m_image0, cv::Point(pt.x, pt.y), cv::Point(pt.x, pt.y), cv::Scalar(0, 0, 255), 5);
				ImageDataClass::GetInstance().m_image0.copyTo(ImageDataClass::GetInstance().m_image);
				ImageDataClass::GetInstance().m_imageUpdated;

			}
			ImageDataClass::GetInstance().RedrawLines();
			return;
		}
	}
}

void AddVerticalPLinesSet::UpdateFigure(cv::Mat& _imag, ImLinePtsVec& _pointVector)
{

	if (_pointVector.size() > 0)
	{
		auto it1 = _pointVector.begin();
		auto it0 = it1;
		it1++;
		while (it1 != _pointVector.end())
		{
			cv::line(_imag, *it0, *it1, cv::Scalar(0, 0, 255), 3);
			it0 = it1;
			it1++;
		}
	}
}