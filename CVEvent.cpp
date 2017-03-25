/*
 * CVEvent.cpp
 *
 *  Created on: 16.02.2017
 *      Author: test-dev
 */

#include "CVEvent.h"

CV_Event::CV_Event() {
	// TODO Auto-generated constructor stub

}

CV_Event::~CV_Event() {
	// TODO Auto-generated destructor stub
}

void CV_Event::SetData(int _e, int _x, int _y, int _fl, void* _usrdat)
{
	std::lock_guard<std::mutex> lk(m_mut);
	m_eventData = EventData(_e, _x, _y, _fl, _usrdat);
}

EventData CV_Event::GetData()
{
	std::lock_guard<std::mutex> lk(m_mut);
	EventData evdata = m_eventData;
	m_eventData = EventData();
	return evdata;
}

void CV_Event::Flush()
{
	std::lock_guard<std::mutex> lk(m_mut);
	m_eventData = EventData();
}
