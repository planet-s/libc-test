#include <stdint.h>
#include <stdio.h>
#include "util.h"

static struct l_l t[] = {
#if LDBL_MANT_DIG == 53
#include "sanity/erfc.h"

#elif LDBL_MANT_DIG == 64
#include "sanity/erfcl.h"

#endif
};

int main(void)
{
	long double y;
	float d;
	int e, i, err = 0;
	struct l_l *p;

	for (i = 0; i < sizeof t/sizeof *t; i++) {
		p = t + i;
		setupfenv(p->r);
		y = erfcl(p->x);
		e = getexcept();
		if (!checkexcept(e, p->e, p->r)) {
			printf("%s:%d: bad fp exception: %s erfcl(%La)=%La, want %s",
				p->file, p->line, rstr(p->r), p->x, p->y, estr(p->e));
			printf(" got %s\n", estr(e));
			err++;
		}
		d = ulperrl(y, p->y, p->dy);
		if (!checkulp(d, p->r)) {
			printf("%s:%d: %s erfcl(%La) want %La got %La ulperr %.3f = %a + %a\n",
				p->file, p->line, rstr(p->r), p->x, p->y, y, d, d-p->dy, p->dy);
			err++;
		}
	}
	return !!err;
}