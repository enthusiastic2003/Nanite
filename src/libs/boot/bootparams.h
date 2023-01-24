#pragma once

#include <stdint.h>

typedef struct {
    
    uint64_t Begin, Length;
    uint32_t Type;
    uint32_t ACPI;
} MemoryRegion;

typedef struct  {
    int RegionCount;
    MemoryRegion* Regions;
    uint32_t MemSizeLo;
    uint32_t MemSizeHi;
} MemoryInfo;

typedef struct {
    MemoryInfo Memory;
    uint8_t BootDevice;
} BootParams;