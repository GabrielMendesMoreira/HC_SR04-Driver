#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0x34e45237, "module_layout" },
	{ 0x5038d8f6, "device_destroy" },
	{ 0x538fc154, "class_destroy" },
	{ 0x20ac0995, "device_create" },
	{ 0x6bc3fbc0, "__unregister_chrdev" },
	{ 0x1f287b1c, "__class_create" },
	{ 0xc69ae48a, "__register_chrdev" },
	{ 0xd75d8046, "gpiod_direction_input" },
	{ 0xd752f452, "gpiod_direction_output_raw" },
	{ 0xfe990052, "gpio_free" },
	{ 0x47229b5c, "gpio_request" },
	{ 0x8f678b07, "__stack_chk_guard" },
	{ 0x86332725, "__stack_chk_fail" },
	{ 0xf9a482f9, "msleep" },
	{ 0x51a910c0, "arm_copy_to_user" },
	{ 0xc358aaf8, "snprintf" },
	{ 0xc85fd3f7, "gpiod_get_raw_value" },
	{ 0x2c63173d, "gpiod_set_raw_value" },
	{ 0xcf356351, "gpio_to_desc" },
	{ 0x8e865d3c, "arm_delay_ops" },
	{ 0xc5850110, "printk" },
	{ 0xb1ad28e0, "__gnu_mcount_nc" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "2916722001DB10F2EEDF308");
