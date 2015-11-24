//物理内存分配
#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/mm.h>
#include <linux/vmalloc.h>

unsigned long pagemem;
unsigned char *kmallocmem;
unsigned char *vmallocmem;

MODULE_LICENSE("GPL");

static int __init init_mmshow(void)
{
	//分配一个或多个物理页面
	pagemem = __get_free_page(GFP_KERNEL);
	if(!pagemem){
		goto fail3;
	}
	printk(KERN_INFO "pagemem = 0x%lx\n", pagemem);

	//为不足一个物理页面的需求分配内存空间，分配的内存空间要联系
	kmallocmem = kmalloc(100, GFP_KERNEL);
	if (!kmallocmem){
		goto fail2;
	}

	printk(KERN_INFO "kmallocmem = 0x%p\n", kmallocmem);

	//获得相应块大小的内存区域,但物理空间不一定连续
	vmallocmem = vmalloc(1000000);
	if (!vmallocmem){
		goto fail1;
	}

	printk(KERN_INFO "vmallocmem = 0x%p\n", vmallocmem);
	
	fail1:
		kfree(kmallocmem);
	fail2:
		free_page(pagemem);
	fail3:
		return -1;

}

static void __exit clean_mmshow(void)
{
	vfree(vmallocmem);
	kfree(kmallocmem);
	free_page(pagemem);
}

module_init(init_mmshow);
module_exit(clean_mmshow);
