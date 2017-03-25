/*
 * CVEvent.h
 *
 *  Created on: 16.02.2017
 *      Author: test-dev
 */

#ifndef CVEVENT_H_
#define CVEVENT_H_

#include <mutex>

//int event, int x, int y, int flags, void* userdata

#define NO_EVENT (-1)

struct EventData
{
	EventData(int _event, int _x, int _y, int _flags, void* _usrdata): m_event(_event), m_x(_x), m_y(_y), m_flags(_flags), m_usrdata(_usrdata){}
	EventData() : m_event(NO_EVENT),m_x(0), m_y(0), m_flags(0), m_usrdata(nullptr){}
	int m_event;
	int m_x;
	int m_y;
	int m_flags;
	void* m_usrdata;
};

class CV_Event {
public:
	CV_Event();
	~CV_Event();

	void SetData(int, int, int, int, void*);
	EventData GetData();
	void Flush();
private:
	EventData m_eventData;
	std::mutex m_mut;

};

#endif /* CVEVENT_H_ */
