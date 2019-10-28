#include <unistd.h>
#include <string.h>
#include <fw.h>
#include <mt.h>
#include <test.h>
#include <signal.h>
#include <locale.h>
#include "project.h"


PROTOTYPES


int main()
{
	t_mt	*mt = mt_create("get_next_line");

	setbuf(stdout, NULL);

	ADD_TESTS

	mt_exec(mt);

	free(mt);
	return(0);
}
