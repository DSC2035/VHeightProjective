#include "ceres/ceres.h"
#include "glog/logging.h"


#include "CeresBAL.h"

using ceres::AutoDiffCostFunction;
using ceres::CostFunction;
using ceres::Problem;
using ceres::Solver;
using ceres::Solve;


double vpoint[2] = {0,0};

double* middlePts;

void LSQFindLinesClosestPoint(std::vector<cv::Vec4f>&, double&, double&);


struct LSEstimatorError 
{
	LSEstimatorError(const cv::Vec4f& _cvline4f): m_perp_dir(_cvline4f[1], -_cvline4f[0], 0), m_origin(_cvline4f[2], _cvline4f[3], 0)
	{
		
		float length = m_perp_dir.dot(m_perp_dir);
		m_perp_dir /= length;
	}

	template <typename T>	bool operator()(const T* const _vpoint, T* residuals) const
	{
		T xcomp = _vpoint[0] - T(m_origin.x);
		T ycomp = _vpoint[1] - T(m_origin.y);

		residuals[0] = T(m_perp_dir.x*xcomp + m_perp_dir.y*ycomp);
		return true;
	}
	// Factory to hide the construction of the CostFunction object from
	// the client code.
	static ceres::CostFunction* Create(const cv::Vec4f& _cvline4f) {
		return (new ceres::AutoDiffCostFunction<LSEstimatorError, 1, 2>(
			new LSEstimatorError(_cvline4f)));
	}

	VectorReal m_origin;
	VectorReal m_perp_dir;
};


struct VPEstimatorError {
	VPEstimatorError(const ImLinePtsVec& _lineData, int _iindex, int _jindex): m_index(_jindex)
	{
		m_lineData.resize(_lineData.size());
		auto vecRealt = m_lineData.begin();
		for (auto it : _lineData) 
		{
			(*vecRealt).x = double(it.x);
			(*vecRealt).y = double(it.y);
			(*vecRealt).z = 0;
			vecRealt++;
		}
		m_middlePt = VectorReal(0, 0, 0);
		double lineptsnum = double(m_lineData.size());
		for (auto it : m_lineData) m_middlePt += it / lineptsnum;
		for (int i = 0; i < m_lineData.size(); i++) m_lineData[i] -= m_middlePt;

		middlePts[_iindex*2] = m_middlePt.x;
		middlePts[_iindex*2+1] = m_middlePt.y;
//		int b{0};
//		b++;

	}

	template <typename T>	bool operator()(const T* const _vpoint, const T* const _mpoint, T* residuals) const
	{
		T xcomp = _vpoint[0] - _mpoint[0];
		T ycomp = _vpoint[1] - _mpoint[1];


		//VectorReal p = VectorReal(_vpoint) - m_middlePt;
		T length = sqrt(xcomp*xcomp + ycomp*ycomp);
		
		//assert(length > 0);
		xcomp /= length;
		ycomp /= length;

		T res = -T(m_lineData[m_index].x)*ycomp + T(m_lineData[m_index].y)*xcomp;
		residuals[0] = res;
	
		return true;
	}
	// Factory to hide the construction of the CostFunction object from
	// the client code.
	static ceres::CostFunction* Create(const ImLinePtsVec& _lineData, int _iindex, int _jindex) {
		return (new ceres::AutoDiffCostFunction<VPEstimatorError, 1, 2, 2>(
			new VPEstimatorError(_lineData, _iindex, _jindex)));
	}

	VecRealVec m_lineData;
	VectorReal m_middlePt;
	int m_index;
};

void LSQFindLinesClosestPoint(std::vector<cv::Vec4f>& _cvlines4f, double& _x, double& _y)
{
	//
	Problem problem;

	// Set up the only cost function (also known as residual). This uses
	// auto-differentiation to obtain the derivative (jacobian).
	for (auto it : _cvlines4f)
	{
		CostFunction* cost_function = LSEstimatorError::Create(it);
		problem.AddResidualBlock(cost_function, NULL, vpoint);
	}

	Solver::Options options;
	options.max_num_iterations = 25;
	options.linear_solver_type = ceres::DENSE_QR;
	options.minimizer_progress_to_stdout = true;

	Solver::Summary summary;
	Solve(options, &problem, &summary);
	std::cout << summary.BriefReport() << "\n";
	std::cout << "LSE vanishing point: " << vpoint[0] << ' ' << vpoint[1] << std::endl;
}


VectorReal CalculateVPointFromPLinesSet(ImPLinesVec& _linesVec, std::vector<cv::Vec4f>& _lines)
{
	LSQFindLinesClosestPoint(_lines, vpoint[0], vpoint[1]);

	middlePts = new double[_lines.size()*2];

	// Build the problem.
	Problem problem;

	// Set up the only cost function (also known as residual). This uses
	// auto-differentiation to obtain the derivative (jacobian).
	for (int i = 0; i < _linesVec.size(); i++)
	{
		for (int j = 0; j < _linesVec[i].size(); j++)
		{
			CostFunction* cost_function = VPEstimatorError::Create(_linesVec[i], i, j);
			problem.AddResidualBlock(cost_function, NULL/*new ceres::CauchyLoss(0.1)*/, vpoint, &middlePts[i*2]);
		}
	}

	Solver::Options options;
	options.max_num_iterations = 25;
	options.linear_solver_type = ceres::DENSE_QR;
	options.minimizer_progress_to_stdout = true;

	Solver::Summary summary;
	Solve(options, &problem, &summary);
	std::cout << summary.BriefReport() << "\n";

	std::cout << "MLE vanishing point: " << vpoint[0] << ' ' << vpoint[1] << '\n';

	delete[] middlePts;

	VectorReal res(vpoint[0], vpoint[1], 1.0);
	return res;
}




/*
int Random(int range)
{
	return std::rand()*range / RAND_MAX;
}

int main(int argc, char** argv) {
	google::InitGoogleLogging(argv[0]);

	//Debugging initialize data

	cv::Point2i lvpoint(500,0);
	int STARTRANGE = 50; int LINELENGTH = 200;

	ImLinePtsVec lineData;
	int NUMLNS = 4; int NUMPTS = 16;

	std::vector<std::vector<cv::Point2i>> lines;

	for (int i = 0; i < NUMLNS; i++)
	{
		std::vector<cv::Point2i> line;
		int y_start = -STARTRANGE + (STARTRANGE / (NUMLNS-1))*i + Random(5);
		for (int j = 0; j < NUMPTS; j++)
		{
			int x = LINELENGTH / (NUMPTS - 1)*j;
			int y = y_start*(float(lvpoint.x - x)/ float(lvpoint.x)) ;
			line.push_back(cv::Point2i(x,y));
		}
		lines.push_back(line);
	}
	


	for (int i = 0; i < NUMLNS; i++)
	{
		std::cout << "Line: " << i << std::endl;
		for (int j = 0; j < NUMPTS; j++)
		{
			std::cout << ' ' << lines[i][j];
		}
		std::cout << std::endl;
	}


	std::vector<cv::Vec4f> linesLSA; //least square approximation of lines
	for (auto it : lines)
	{
		cv::Vec4f lineFit;
		cv::fitLine(it, lineFit, cv::DIST_L1, 1, 0.001, 0.001);
		linesLSA.push_back(lineFit);
	}

	VectorReal realVec =  CalculateVPointFromPLinesSet(lines, linesLSA);
	

//		<< " -> " << x << "\n";
	std::system("Pause");
	return 0;
}

//*/