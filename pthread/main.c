# include <pthread.h>
#include <stdio.h>

typedef struct s_arguments
{
	int		i;
	char	*str;
}	t_arguments;

void *fn(void *tt)
{
	t_arguments *jj;

	jj = (t_arguments *)tt;

	printf ("here %s %d\n", jj->str, jj->i);
	return (NULL);
}

int main()
{
	pthread_t t[5];
	t_arguments tt[5];
	int i;

	i = 0;
	while (i < 5)
	{
		tt[i].i = i;
		tt[i].str = "kaka";
		pthread_create (&t[i], NULL, fn, &tt[i]);
		i++;
	}

	i = 0;
	while (i < 5)
	{
		pthread_join (t[i], NULL);
		i++;
	}






}