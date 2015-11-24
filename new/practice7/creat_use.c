// =====================================================================================
// 
//       Filename:  creat_use.c
//
//    Description:  生产者消费者实例
//
//        Version:  1.0
//        Created:  2015年06月15日 16时51分25秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Striver (CuiJiaojiao), cuijiaojiao@xiyoulinux.org
//        Company:  Class 1204 of Software Engineering
// 
// =====================================================================================

#include <linux/init.h>
#include <linux/module.h>
#include <linux/semaphore.h>
#include <linux/sched.h>
#include <asm/atomic.h>
#include <linux/delay.h>

#define PRODUCT_NUMS 10

static struct semaphore sem_producer;
static struct semaphore sem_consumer;
static char product[2];
static atomic_t num;
static int producer(void *product);
static int consumer(void *product);
static int consume_num = 1;
static int id = 1;

/*
 *生产者线程
 * */
static int producer(void *p)
{
	char *product = (char *)p;
	int i;

	atomic_inc(&num);
	printk("producer[%d] start...\n", current->pid);
	for (i = 0; i < PRODUCT_NUMS; i++){
		down(&sem_producer);   //获取信号量
		snprintf(product, 12, "2010-01-%d", id++);
		printk("producer [%d] prosuct %s\n", current->pid, product);
		up(&sem_consumer);   //释放信号量
	}

	printk("producer [%d] exit...\n", current->pid);
}

/*
 *消费者线程
 * */
static int consumer(void *p)
{
	char *product = (char *)p;
	printk("consumer[%d]start....\n",current->pid);
	for(;;){
		msleep(100);
		down_interruptible(&sem_consumer);
		if(consume_num>=PRODUCT_NUMS * atomic_read(&num))
			break;
	printk("consumer [%d] consumer %s\n",current->pid,product);
	consume_num++;
	memset(product,'\0',12);
	up(&sem_producer);
	}
	printk("consumer[%d] exit...\n", current->pid);
	return 0;
}

/*
 *模块插入和删除
 * */
static int procon_init(void)
{
	printk(KERN_INFO "show producer and consumer\n");
	sema_init(&sem_producer, 1);
	sema_init(&sem_consumer, 0);
	atomic_set(&num, 0);

	kernel_thread(producer, product, CLONE_KERNEL);
	kernel_thread(consumer, product, CLONE_KERNEL);

	return 0;
}

static void procon_exit(void)
{
	printk(KERN_INFO "exit producer and consumer\n");
}
module_init(procon_init);
module_exit(procon_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("producer and consmer Module");
MODULE_ALIAS("a simplest module");
