/*
 * MatchReport.h
 *
 *  Created on: Jan 21, 2014
 *      Author: yotam
 */

#ifndef MATCHREPORT_H_
#define MATCHREPORT_H_

#include "../../Common/Types.h"
#include "../../AhoCorasick/ACTypes.h"

typedef struct {
	PatternSetMap reportees;
	STATE_PTR_TYPE_WIDE state;
	char *pattern;
	int idx;
} MatchReport;

MatchReport *matchreport_create(PatternSetMap reportees, STATE_PTR_TYPE_WIDE state, char *pattern, int idx);
void matchreport_destroy(MatchReport *matchReport);

#endif /* MATCHREPORT_H_ */
