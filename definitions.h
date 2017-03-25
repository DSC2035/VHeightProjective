/*
 * definitions.h
 *
 *  Created on: 17.02.2017
 *      Author: test-dev
 */

#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

typedef cv::Point3d VectorReal;
typedef cv::Point2i VectorImagePoint;
typedef std::vector<VectorImagePoint> ImLinePtsVec;
typedef std::vector<ImLinePtsVec> ImPLinesVec;
typedef std::vector<ImPLinesVec> ImPLinesSetsVec;
typedef std::vector<VectorReal> VecRealVec;



#define TAG_IMPDAT	"IMAGE_PLANE_POINTS"
#define TAG_VPTS	"VERTICAL_LINE_POINTS"
#define TAG_REFPTS	"REFERENCE_POINTS"
#define TAG_IMFILE	"IMAGE_FILE"
#define TAG_END		"DATA_END"
#define TAG_DELIM	"<delimiter>"

struct InpStream
{
	static std::istream& GetInpStream()
	{
		if (!m_stream.rdbuf()->in_avail()) return std::cin;
		return m_stream;
	}
	static std::stringstream m_stream;
};

#endif /* DEFINITIONS_H_ */
