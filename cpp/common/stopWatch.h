#ifndef STOPWATCH_INCLUDED
#define STOPWATCH_INCLUDED

#include <sys/time.h>
#include <iostream>
#include <climits>
#include <cstring>

class StopWatch {
    static const long N = 10000;
    static const int BUCKETS = 20;
public:
    template <typename F>
    void run(F f) {
        for (long i = 0; i < N; i++)
        {
            clock_gettime(CLOCK_REALTIME, &times[i]);
            f();
        }

        clock_gettime(CLOCK_REALTIME, &times[N]);
    }

    void printResults() {
        long min = LONG_MAX;
        long max = -1;
        double total = 0;
        long time[N];
        for (long i = 0; i < N; i++)
        {
            time[i] = (times[i + 1].tv_sec - times[i].tv_sec) * 1000000000L + times[i+1].tv_nsec - times[i].tv_nsec;
            if (time[i] > max) max = time[i];
            if (time[i] < min) min = time[i];
            total += time[i];
        }

        if (min == max)
        {
            std::cout << "all is: " << min << " ns" << std::endl;
            return;
        }

        int count[BUCKETS + 1];
        long dist = max - min;
        std::memset(&count, 0, sizeof(count));
        for (long i = 0; i < N; i++)
            count[(time[i] - min) * BUCKETS / dist]++;

        std::cout << "min/max:" << min << "/" << max << " avg:" << total / N << std::endl;
        for (int i = 0; i <= BUCKETS; i++)
            std::cout << min + dist * i/(BUCKETS + 1)<< " to " << min + dist * (i+1) / (BUCKETS+1) << " :" << count[i] << std::endl;
    }

private:
    timespec times[N + 1];
};

#endif // STOPWATCH_INCLUDED
