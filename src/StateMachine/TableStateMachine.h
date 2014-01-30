/*
 * TableStateMachine.h
 *
 *  Created on: Jan 23, 2011
 *      Author: yotamhc
 */

#ifndef TABLESTATEMACHINE_H_
#define TABLESTATEMACHINE_H_
#include "../Common/Types.h"
#include "../Common/BitArray/BitArray.h"
#include "../AhoCorasick/ACTypes.h"
//#include "../Multicore/MulticoreManager.h"

//typedef unsigned int STATE_PTR_TYPE_WIDE;
#ifdef COUNT_BY_DEPTH
#define DEPTHMAP
#endif
#ifdef PRINT_STATE_VISIT_HIST
#define DEPTHMAP
#endif

struct multicore_manager;
struct scanner_data;

typedef struct {
	STATE_PTR_TYPE_WIDE *table;
	unsigned char *matches;
	char **patterns;
	unsigned int numStates;
	PatternSetMap *sourcePatternSets;
	PatternSetMap *matchPatternSets;
	STATE_PTR_TYPE_WIDE *failures;
#ifdef DEPTHMAP
	int *depthMap;
#endif
#ifdef HEAVY_PACKET_RECOGNITION
	//unsigned char *commons;
	//int *commons;
	int num_common;
	double uncommon_rate_limit;
#endif
} TableStateMachine;

TableStateMachine *createTableStateMachine(unsigned int numStates, int num_common, double uncommon_rate_limit);
void destroyTableStateMachine(TableStateMachine *machine);

void setGoto(TableStateMachine *machine, STATE_PTR_TYPE_WIDE currentState, char c, STATE_PTR_TYPE_WIDE nextState);
void setMatch(TableStateMachine *machine, STATE_PTR_TYPE_WIDE state, char *pattern, int length, PatternSetMap matchPatternSets);

//int matchTableMachine(TableStateMachine *tableMachine, char *input, int length, int verbose);
int matchTableMachine(TableStateMachine *machine, struct multicore_manager *manager, int transfer_heavy, char *input, int length, int verbose,
		long *numAccesses, long *accessesByDepth, long *accessesByState, int *visits,
		int *is_heavy, int *last_idx_in_root, double *uncommonRate,
		struct scanner_data *scanner);

int matchTableMachine_no_trasfer(TableStateMachine *machine, struct multicore_manager *manager, char *input, int length, int verbose, int drop);

#ifdef HEAVY_PACKET_RECOGNITION

#define IS_COMMON_STATE(machine, stateID) \
	((machine)->commons[stateID])
//	GET_1BIT_ELEMENT((machine)->commons, stateID)

#define SET_COMMON_STATE(machine, stateID) \
	(((machine)->commons[stateID]) = 1)
//	SET_1BIT_ELEMENT((machine)->commons, stateID, 1)

#define SET_UNCOMMON_STATE(machine, stateID) \
	(((machine)->commons[stateID]) = 0)
//	SET_1BIT_ELEMENT((machine)->commons, stateID, 0)

#endif

#endif /* TABLESTATEMACHINE_H_ */
