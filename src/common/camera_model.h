/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#pragma once
#ifndef GCG_CAMERAMODEL_GENERATED_H
#define GCG_CAMERAMODEL_GENERATED_H

constexpr int32_t MODEL_9 = 1;
constexpr int32_t MODEL_10 = 2;
constexpr int32_t MODEL_11 = 4;
constexpr int32_t MODEL_11_BLACK = 8;
constexpr int32_t MODEL_12 = 16;
constexpr int32_t MODEL_13 = 32;
constexpr int32_t MODEL_MAX2 = 64;
constexpr int32_t MODEL_MISSION = 128;

constexpr int32_t MODEL_11S = MODEL_11|MODEL_11_BLACK;
constexpr int32_t MODEL_MISSION_ALL = MODEL_MISSION|MODEL_MAX2|MODEL_13|MODEL_12|MODEL_11_BLACK|MODEL_11|MODEL_10|MODEL_9;
constexpr int32_t MODEL_MAX2_ALL = MODEL_MAX2|MODEL_13|MODEL_12|MODEL_11_BLACK|MODEL_11|MODEL_10|MODEL_9;
constexpr int32_t MODEL_13_ALL = MODEL_13|MODEL_12|MODEL_11_BLACK|MODEL_11|MODEL_10|MODEL_9;
constexpr int32_t MODEL_12_ALL = MODEL_12|MODEL_11_BLACK|MODEL_11|MODEL_10|MODEL_9;
constexpr int32_t MODEL_11_ALL = MODEL_11_BLACK|MODEL_11|MODEL_10|MODEL_9;
constexpr int32_t MODEL_10_ALL = MODEL_10|MODEL_9;

#endif