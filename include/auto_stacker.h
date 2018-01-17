#ifndef CHAINBAR_H_
#define CHAINBAR_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <main.h>
#include <motor.h>
#include <chassis.h>
#include <lift.h>
#include <mogo.h>
#include <claw.h>
#include <chainbar.h>

void autoStackerUpdate();
void autoStackerRun();

#ifdef __cplusplus
}
#endif

#endif
