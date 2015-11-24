#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/sched.h>
#include<linux/list.h>

static int __init print_pid(void)
{	
    	struct task_struct *task,*p;
        struct list_head *pos;
        int count=0;
        task=&init_task;
        list_for_each(pos,&task->tasks)
        {
        	p=list_entry(pos,struct task_struct,tasks);
		count++;
		printk("%d--->%s\n",p->pid,p->comm);
        } 
	printk("the number of process is:%d\n",count);
	return 0;
}

static void __exit print_exit(void)
{
	printk("end\n");
}
module_init(print_pid);
module_exit(print_exit);
MODULE_LICENSE("GPL");

