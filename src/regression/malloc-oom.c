// malloc should set errno on oom
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "test.h"

int main(void)
{
	if (t_vmfill(0,0,0) < 0)
		t_error("vmfill failed: %s\n", strerror(errno));

	errno = 0;
	if (malloc(50000))
		t_error("malloc was successful\n");
	if (errno != ENOMEM)
		t_error("expected ENOMEM, got %s\n", strerror(errno));

	return t_status;
}
