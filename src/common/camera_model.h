#pragma once
#ifndef CAMERAMODEL_GENERATED_H
#define CAMERAMODEL_GENERATED_H

/** GoPro Model 9 ID */
#define MODEL_9 (1)
/** GoPro Model 10 ID */
#define MODEL_10 (2)
/** GoPro Model 11 ID */
#define MODEL_11 (4)
/** GoPro Model 11 Black ID */
#define MODEL_11_BLACK (8)
/** GoPro Model 12 ID */
#define MODEL_12 (16)
/** GoPro Model 13 ID */
#define MODEL_13 (32)
/** GoPro Model MAX2 ID */
#define MODEL_MAX2 (64)
/** GoPro Model mission 1 ID */
#define MODEL_MISSION (128)

/** Two model 11 includes */
#define MODEL_11S (MODEL_11|MODEL_11_BLACK)
#define MODEL_MISSION_ALL (MODEL_MISSION|MODEL_MAX2|MODEL_13|MODEL_12|MODEL_11_BLACK|MODEL_11|MODEL_10|MODEL_9)
/** Fron Max2 to all the versions below includes */
#define MODEL_MAX2_ALL (MODEL_MAX2|MODEL_13|MODEL_12|MODEL_11_BLACK|MODEL_11|MODEL_10|MODEL_9)
/** Fron 13 to all the versions below includes */
#define MODEL_13_ALL (MODEL_13|MODEL_12|MODEL_11_BLACK|MODEL_11|MODEL_10|MODEL_9)
/** Fron 12 to all the versions below includes */
#define MODEL_12_ALL (MODEL_12|MODEL_11_BLACK|MODEL_11|MODEL_10|MODEL_9)
/** Fron 11 to all the versions below includes */
#define MODEL_11_ALL (MODEL_11_BLACK|MODEL_11|MODEL_10|MODEL_9)
/** Fron 10 to all the versions below includes */
#define MODEL_10_ALL (MODEL_10|MODEL_9)

#endif