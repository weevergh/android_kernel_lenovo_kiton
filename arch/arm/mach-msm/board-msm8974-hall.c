#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <linux/module.h>
#include <asm/mach-types.h>
#include <mach/msm_iomap.h>
#include <mach/board.h>
#include <mach/irqs-7xxx.h>
#include <mach/vreg.h>


static struct platform_device msm_hall_switch = {
	.name      = "msm_hall_switch",
};


static struct platform_device *hall_devices_evb[] __initdata = {
        &msm_hall_switch,
};

void __init msm_hall_init(void)
{
	platform_add_devices(hall_devices_evb, ARRAY_SIZE(hall_devices_evb));

}

