/*
 * state.h
 *
 *  Created on: Sep 1, 2023
 *      Author: elmag
 */

#ifndef STATE_H_
#define STATE_H_

#define STATE_define(_stateFUN_) void ST_##_stateFUN_()
#define STATE(_stateFUN_) ST_##_stateFUN_

void US_set_distance(int d);
void DC_motor(int s);

#endif /* STATE_H_ */
