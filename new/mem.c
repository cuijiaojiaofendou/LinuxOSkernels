/*内核模块，打印进程的虚存区*/
#include <linux/module.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/sched.h>

static int pid;

module_param(pid, int, 0644);

static int __init memtest_init(void)
{
	struct task_struct *p;
	struct vm_area_struct *temp;
	
	printk("the virtual memory areas(VMA) are:\n");
	struct pid *kpid = find_get_pid(pid); //获得进程的描述符
	p = pid_task(kpid, PIDTYPE_PID);
	temp = p->mm->mmap;
	
	while(temp){
		printk("start:%p\ntend:%p\n", (unsigned long *)temp->vm_start, (unsigned long *)temp->vm_end);

		temp = temp->vm_next;
	}
	return 0;
}

static void __exit memtest_exit(void)
{
	 printk("Unloading my module\n");
	return ;
}

module_init(memtest_init);
module_exit(memtest_exit);
MODULE_LICENSE("GPL");
