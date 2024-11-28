#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/cdev.h>
#include <linux/device.h> 
#include <linux/gpio.h>   
#include <linux/delay.h>   

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Grupo 4 - Sistemas Embarcados");
MODULE_DESCRIPTION("Driver para o sensor HC-SR04");
MODULE_VERSION("1.0");

static int major_number;
static struct class *hc_sr04_class = NULL;
static struct device *hc_sr04_device = NULL;

#define TRIGGER_PIN 26
#define ECHO_PIN 6

static int hc_sr04_open(struct inode *, struct file *);
static int hc_sr04_release(struct inode *, struct file *);
static ssize_t hc_sr04_read(struct file *, char *, size_t, loff_t *);

static struct file_operations fops = {
    .open = hc_sr04_open,
    .release = hc_sr04_release,
    .read = hc_sr04_read,
};

static int hc_sr04_open(struct inode *inodep, struct file *filep) {
    printk(KERN_INFO "HC-SR04: Dispositivo aberto\n");
    return 0;
}

static int hc_sr04_release(struct inode *inodep, struct file *filep) {
    printk(KERN_INFO "HC-SR04: Dispositivo fechado\n");
    return 0;
}

static long read_distance(void) {
    long distance;
    int pulse_duration;

    gpio_set_value(TRIGGER_PIN, 1);
    udelay(10);
    gpio_set_value(TRIGGER_PIN, 0);

    while (!gpio_get_value(ECHO_PIN));  
    pulse_duration = 0;

    while (gpio_get_value(ECHO_PIN)) {  
        pulse_duration++;
        udelay(1);  
    }

    distance = (pulse_duration * 17150) / 1000;  
    
    return distance;
}

static ssize_t hc_sr04_read(struct file *filep, char *buffer, size_t len, loff_t *offset) {
    long distance = read_distance();
    char result[50];
    size_t result_len;

    result_len = snprintf(result, sizeof(result), "Distância: %ld cm\n", distance);

    if (copy_to_user(buffer, result, result_len)) {
        return -EFAULT;
    }

    msleep(1000);  

    return result_len;
}

static int __init hc_sr04_init(void) {
    int ret;

    printk(KERN_INFO "HC-SR04 Driver carregado\n");

    ret = gpio_request(TRIGGER_PIN, "TRIGGER_PIN");
    if (ret) {
        printk(KERN_ALERT "Falha ao solicitar GPIO do Trigger\n");
        return ret;
    }
    ret = gpio_request(ECHO_PIN, "ECHO_PIN");
    if (ret) {
        printk(KERN_ALERT "Falha ao solicitar GPIO do Echo\n");
        gpio_free(TRIGGER_PIN);
        return ret;
    }

    gpio_direction_output(TRIGGER_PIN, 0);  
    gpio_direction_input(ECHO_PIN);          

    major_number = register_chrdev(0, "hc_sr04", &fops);
    if (major_number < 0) {
        printk(KERN_ALERT "Falha ao registrar o dispositivo de caractere\n");
        gpio_free(TRIGGER_PIN);
        gpio_free(ECHO_PIN);
        return major_number;
    }

    hc_sr04_class = class_create(THIS_MODULE, "hc_sr04_class");
    if (IS_ERR(hc_sr04_class)) {
        unregister_chrdev(major_number, "hc_sr04");
        gpio_free(TRIGGER_PIN);
        gpio_free(ECHO_PIN);
        printk(KERN_ALERT "Falha ao criar a classe do dispositivo\n");
        return PTR_ERR(hc_sr04_class);
    }

    hc_sr04_device = device_create(hc_sr04_class, NULL, MKDEV(major_number, 0), NULL, "hc_sr04");
    if (IS_ERR(hc_sr04_device)) {
        class_destroy(hc_sr04_class);
        unregister_chrdev(major_number, "hc_sr04");
        gpio_free(TRIGGER_PIN);
        gpio_free(ECHO_PIN);
        printk(KERN_ALERT "Falha ao criar o dispositivo no /dev\n");
        return PTR_ERR(hc_sr04_device);
    }

    return 0;
}

static void __exit hc_sr04_exit(void) {
    device_destroy(hc_sr04_class, MKDEV(major_number, 0));  
    class_destroy(hc_sr04_class);  
    unregister_chrdev(major_number, "hc_sr04");  

    gpio_free(TRIGGER_PIN);  
    gpio_free(ECHO_PIN);

    printk(KERN_INFO "HC-SR04 Driver descarregado\n");
}

module_init(hc_sr04_init);
module_exit(hc_sr04_exit);
