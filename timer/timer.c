#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

int	timer(int deadline)
{
	struct timeval	time;
	int				current;
	long			start;
	long			end;
	long			mcs;

	// conver ms to micro
	mcs = deadline * 1000;

	// print current time
	gettimeofday(&time, NULL);
	start = time.tv_sec;
	printf("start at %ld\n", start);
	
	// sleep for deadline
	usleep(mcs);

	// print new time
	gettimeofday(&time, NULL);
	end = time.tv_sec;
	printf("end at %ld\n", end);
	printf ("def = %ld", end - start);
	return (1);
}

int	main(void)
{
	timer(2000);
	return (1);
}
