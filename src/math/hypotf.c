#include <stdint.h>
#include <stdio.h>
#include "util.h"

static struct ff_f t[] = {
#include "ucb/hypotf.h"
#include "sanity/hypotf.h"

};

int main(void)
{
	float y;
	float d;
	int e, i, err = 0;
	struct ff_f *p;

	for (i = 0; i < sizeof t/sizeof *t; i++) {
		p = t + i;
		setupfenv(p->r);
		y = hypotf(p->x, p->x2);
		e = getexcept();
		if (!checkexcept(e, p->e, p->r)) {
			printf("%s:%d: bad fp exception: %s hypotf(%a,%a)=%a, want %s",
				p->file, p->line, rstr(p->r), p->x, p->x2, p->y, estr(p->e));
			printf(" got %s\n", estr(e));
			err++;
		}
		d = ulperrf(y, p->y, p->dy);
		if (!checkulp(d, p->r)) {
			printf("%s:%d: %s hypotf(%a,%a) want %a got %a ulperr %.3f = %a + %a\n",
				p->file, p->line, rstr(p->r), p->x, p->x2, p->y, y, d, d-p->dy, p->dy);
			err++;
		}
	}
	return !!err;
}