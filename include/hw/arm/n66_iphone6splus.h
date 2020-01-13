/*
 * iPhone 6s plus - n66 - S8000
 *
 * Copyright (c) 2019 Jonathan Afek <jonyafek@me.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef HW_ARM_N66_H
#define HW_ARM_N66_H

#include "qemu-common.h"
#include "exec/hwaddr.h"
#include "hw/boards.h"
#include "hw/arm/boot.h"
#include "hw/arm/xnu.h"
#include "exec/memory.h"
#include "cpu.h"
#include "sysemu/kvm.h"

#define TYPE_N66 "iPhone6splus-n66-s8000"

#define TYPE_N66_MACHINE   MACHINE_TYPE_NAME(TYPE_N66)

#define N66_MACHINE(obj) \
    OBJECT_CHECK(N66MachineState, (obj), TYPE_N66_MACHINE)

#define N66_CPREG_VAR_NAME(name) cpreg_##name
#define N66_CPREG_VAR_DEF(name) uint64_t N66_CPREG_VAR_NAME(name)

typedef struct {
    MachineClass parent;
} N66MachineClass;

typedef struct {
    MachineState parent;
    hwaddr extra_data_pa;
    hwaddr kpc_pa;
    hwaddr kbootargs_pa;
    hwaddr uart_mmio_pa;
    ARMCPU *cpu;
    KernelTaskPortParams ktpp;
    PtrNtfDev ptr_ntf;
    struct arm_boot_info bootinfo;
    char ramdisk_filename[1024];
    char kernel_filename[1024];
    char secmon_filename[1024];
    char dtb_filename[1024];
    char tc_filename[1024];
    char driver_filename[1024];
    char kern_args[1024];
    uint16_t tunnel_port;
    FileMmioDev raw_kernel_file_dev;
    FileMmioDev ramdisk_file_dev;
    FileMmioDev tc_file_dev;
    N66_CPREG_VAR_DEF(ARM64_REG_HID11);
    N66_CPREG_VAR_DEF(ARM64_REG_HID3);
    N66_CPREG_VAR_DEF(ARM64_REG_HID5);
    N66_CPREG_VAR_DEF(ARM64_REG_HID4);
    N66_CPREG_VAR_DEF(ARM64_REG_HID8);
    N66_CPREG_VAR_DEF(ARM64_REG_HID7);
    N66_CPREG_VAR_DEF(ARM64_REG_LSU_ERR_STS);
    N66_CPREG_VAR_DEF(PMC0);
    N66_CPREG_VAR_DEF(PMC1);
    N66_CPREG_VAR_DEF(PMCR1);
    N66_CPREG_VAR_DEF(PMSR);
} N66MachineState;

typedef struct {
    uint8_t fake_port[FAKE_PORT_ALLOC_SIZE];
    uint8_t kernel_task[KERNEL_TASK_ALLOC_SIZE];
    uint8_t hook_code[HOOK_CODE_ALLOC_SIZE];
} __attribute__((packed)) AllocatedData;

#endif
