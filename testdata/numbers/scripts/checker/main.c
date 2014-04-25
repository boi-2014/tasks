#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

enum {
	ANSW_OK,
	ANSW_FAIL
};


static const char *pts_zero = "0";
static const char *pts_full = "1";
static const char *pts_half = "0.5";


struct reader_t {
	FILE *f;
	int c;
};


void
reader_init(struct reader_t *r, char *fname)
{
	r->f = fopen(fname, "r");
	r->c = 0;
}


void
reader_free(struct reader_t *r)
{
	fclose(r->f);
}


void
reader_read(struct reader_t *r)
{
	r->c = fgetc(r->f);
}


void
reader_skipline(struct reader_t *r)
{
	while ((r->c != EOF) && (r->c != '\n'))
		r->c = fgetc(r->f);
}

void
reader_skipblank(struct reader_t *r)
{
	while ((r->c != EOF) && isblank(r->c))
		r->c = fgetc(r->f);
}


void
reader_skip_blank_lines(struct reader_t *r)
{
	while ((r->c != EOF) && isspace(r->c))
		r->c = fgetc(r->f);
}


/* unused */
long long int
reader_read_llint(struct reader_t *r)
{
	long long int n = 0;

	reader_skipblank(r);
	if ((r->c == EOF) || !isdigit(r->c))
		return -1;
	do {
		n *= 10;
		n += r->c - '0';
		r->c = fgetc(r->f);
	} while ((r->c != EOF) && isdigit(r->c));

	return n;
}


static int
isnewline(int c)
{
	return (c == '\r') || (c == '\n');
}


static void
read_digit_while_eq(struct reader_t *rsol, struct reader_t *rout)
{
	while ((rsol->c != EOF) && isdigit(rsol->c) && (rsol->c == rout->c)) {
		reader_read(rsol);
		reader_read(rout);
	}
}


static int
check_first_line(struct reader_t *rsol, struct reader_t *rout)
{
	reader_read(rsol);
	reader_read(rout);
	reader_skipblank(rsol);
	reader_skipblank(rout);

	read_digit_while_eq(rsol, rout);

	if (rsol->c == rout->c)
		return ANSW_OK;
	if ((rsol->c != EOF) && isdigit(rsol->c))
		return ANSW_FAIL;

	reader_skipblank(rout);
	if ((rout->c == EOF) || isnewline(rout->c))
		return ANSW_OK;

	return ANSW_FAIL;
}


static int
check_second_line(struct reader_t *rsol, struct reader_t *rout)
{
	if (rsol->c == EOF)
		return ANSW_OK; /* skip_blank_lines(rout) will be called later */

	reader_read(rsol);
	reader_read(rout);

	for (;;) {
		reader_skipblank(rsol);
		reader_skipblank(rout);
		if ((rsol->c == EOF) || isnewline(rsol->c))
			return ANSW_OK; /* skip_blank_lines(rout) will be called later */
		if (rsol->c != rout->c)
			return ANSW_FAIL;

		read_digit_while_eq(rsol, rout);
		if ((rsol->c == EOF) || isnewline(rsol->c))
			return ANSW_OK; /* skip_blank_lines(rout) will be called later */
		if ((rsol->c == rout->c) || (isblank(rsol->c) && isblank(rout->c)))
			continue;
		return ANSW_FAIL;
	}
}


static const char *
get_answer(struct reader_t *rsol, struct reader_t *rout)
{
	int answer = check_first_line(rsol, rout);

	if (answer == ANSW_FAIL)
		return pts_zero;

	reader_skipline(rsol);
	reader_skipline(rout);
	answer = check_second_line(rsol, rout);

	if (answer == ANSW_FAIL)
		return pts_half;

	reader_skip_blank_lines(rout);
	if (rout->c != EOF)
		return pts_half;
	return pts_full;
}


int
main(int argc, char *argv[])
{
	struct reader_t rout;
	struct reader_t rsol;
	const char *pts;

	if (argc != 4)
		return 1;

	reader_init(&rsol, argv[2]);
	reader_init(&rout, argv[3]);

	if (rsol.f == NULL)
		return 1;

	if (rout.f == NULL) {
		reader_free(&rsol);
		printf("%s\n", pts_zero);
		return 0;
	}

	pts = get_answer(&rsol, &rout);
	printf("%s\n", pts);

	reader_free(&rsol);
	reader_free(&rout);
	return 0;
}
