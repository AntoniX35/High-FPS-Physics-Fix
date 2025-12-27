#pragma once

#include "OS/SysCall.h"

namespace HFPF
{
	class FramerateLimiter
	{
	public:
		FramerateLimiter() :
			m_lastTimePoint(IPerfCounter::Query()),
			m_hTimer(nullptr)
		{
			/*if (ISysCall::NtWaitForSingleObject != nullptr) {
                m_hTimer = ::CreateWaitableTimerA(nullptr, FALSE, nullptr);
            }*/
		}

		void Wait(long long a_limit)
		{
			auto now      = IPerfCounter::Query();
			auto interval = IPerfCounter::delta_us(m_lastTimePoint, now);
			auto waitTime = a_limit - interval;

			if (waitTime > 0)
			{
				// convert the perf-counter timestamp to steady_clock
				// or if your IPerfCounter already uses QPC, just call it directly
				auto a_deadline = now + IPerfCounter::T(waitTime);

				while (true) {
					now = IPerfCounter::Query();
					if (now >= a_deadline) {
						now = a_deadline;
						break;
					}

					const long long remaining_us = IPerfCounter::delta_us(now, a_deadline);

					// If more than ~2ms left, sleep coarsely
					if (remaining_us > 2000) {
						std::this_thread::sleep_for(std::chrono::microseconds(remaining_us - 1500));
						continue;
					}

					// Final microspin for timing precision
					_mm_pause();
				}
			}

			// Adjust in case we overran
			m_lastTimePoint = now;
		}

	private:
		SKMP_FORCEINLINE void WaitTimer(long long a_waitTime, long long a_deadline)
		{
			LARGE_INTEGER dueTime;
			dueTime.QuadPart = static_cast<LONGLONG>(
				static_cast<long double>(a_waitTime));

			if (dueTime.QuadPart <= 0)
				return;

			dueTime.QuadPart =
				-(dueTime.QuadPart * 10LL);

			if (::SetWaitableTimer(m_hTimer, &dueTime, 0, nullptr, nullptr, TRUE) == FALSE)
			{
				return;
			}

			NTSTATUS status = STATUS_ALERTED;

			while (status != STATUS_SUCCESS)
			{
				_mm_pause();

				auto to_next = IPerfCounter::delta_us(IPerfCounter::Query(), a_deadline);

				if (to_next <= 0LL)
				{
					return;
				}

				LARGE_INTEGER timeOut;
				timeOut.QuadPart = -(to_next * 10LL);

				status = ISysCall::NtWaitForSingleObject(m_hTimer, FALSE, &timeOut);
			}
		}

		long long m_lastTimePoint;
		HANDLE    m_hTimer;
	};
}
