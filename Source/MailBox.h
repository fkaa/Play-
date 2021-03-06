#pragma once

#include <functional>
#include <deque>
#include <mutex>
#include <condition_variable>

class CMailBox
{
public:
						CMailBox();
	virtual				~CMailBox();

	typedef std::function<void ()> FunctionType;

	void				SendCall(const FunctionType&, bool = false);
	void				FlushCalls();

	bool				IsPending() const;
	void				ReceiveCall();
	void				WaitForCall();
	void				WaitForCall(unsigned int);

private:
	struct MESSAGE
	{
		FunctionType	function;
		bool			sync;
	};

	typedef std::deque<MESSAGE> FunctionCallQueue;

	FunctionCallQueue		m_calls;
	std::mutex				m_callMutex;
	std::condition_variable	m_callFinished;
	std::condition_variable	m_waitCondition;
	bool					m_callDone;
};
