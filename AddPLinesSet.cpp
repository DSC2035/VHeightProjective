#include "ImageDataClass.h"

#include "AddPLinesSet.h"


AddPLinesSet::AddPLinesSet()
{
}


AddPLinesSet::~AddPLinesSet()
{
}

const char* AddPLinesSet::GetDescription()
{
	return "Define a set of parallel lines on the plane";
}

void AddPLinesSet::Run()
{
	ImPLinesVec pLines;
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
			pLines.push_back(newLine);

			ImageDataClass::GetInstance().CalculatePlaneVanishingLine();

			UpdateFigure(ImageDataClass::GetInstance().m_image0, newLine);
			ImageDataClass::GetInstance().m_image0.copyTo(ImageDataClass::GetInstance().m_image);
			ImageDataClass::GetInstance().m_imageUpdated = true;
		}
		else
		{
			if (pLines.size() > 1)

			ImageDataClass::GetInstance().m_imagePlanePLinesPoints.push_back(pLines);

			ImageDataClass::GetInstance().CalculatePlaneVanishingLine();

			UpdateFigure(ImageDataClass::GetInstance().m_image0, newLine);
			ImageDataClass::GetInstance().m_image0.copyTo(ImageDataClass::GetInstance().m_image);
			ImageDataClass::GetInstance().m_imageUpdated = true;

			return;
		}
	}
}

void AddPLinesSet::UpdateFigure(cv::Mat& _imag, ImLinePtsVec& _pointVector)
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