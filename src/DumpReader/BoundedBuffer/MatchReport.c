#include <stdlib.h>
#include "MatchReport.h"

MatchReport *matchreport_create(PatternSetMap reportees, STATE_PTR_TYPE_WIDE state, char *pattern, int idx) {
	MatchReport *new;
	new = (MatchReport*)malloc(sizeof(MatchReport));
	new->reportees = reportees;
	new->state = state;
	new->pattern = pattern;
	new->idx = idx;
	return new;
}

void matchreport_destroy(MatchReport *matchReport) {
	free(matchReport);
}
