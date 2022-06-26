/**
 * @file MetalTypes.h
 * @author Milo Heinrich (MikuoH15TH@gmail.com)
 * @brief This file contains type definitions for the Metal backend.
 * @version 1.0
 * @date 2022-06-26
 */
#ifndef ELSA_METAL_TYPES_H
#define ELSA_METAL_TYPES_H

#include <MetalKit/MetalKit.h>

typedef struct MetalContext {
    CAMetalLayer* Layer;
    id<MTLDevice> Device;
} MetalContext;

#endif