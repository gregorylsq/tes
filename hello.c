#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/ide.h>
#include <linux/init.h>
#include <linux/module.h>

#define CHATBASE_MAJOR 200 /* 主设备号 */
#define CHATBASE_NAME "chatbase" /* 设备名 */

static char readbuf[100];
static char writebuf[100];
static char testdata[]={"test data"};

static int chat_open(struct inode *inode,struct file *filp)
{
    printk("device open\r\n");
    return 0;
}


static int chat_close(struct inode *inode, struct file *filp)
{
    printk("device close\r\n");
    return 0;
}

static ssize_t chat_read(struct file *filp, char __user *buf,size_t cnt, loff_t *offt)
{
    int retvalue=0;
    memcpy(readbuf,testdata,sizeof(testdata));
    retvalue=copy_to_user(buf,readbuf,cnt);
    if(retvalue==0)
        printk("read ok");
    else
    {
        printk("read fail");
    }
    
    return 0;
}

static ssize_t chat_write(struct file *filp,const char __user *buf,size_t cnt,loff_t *offt)
{
    int retvalue=0;

    retvalue=copy_from_user(writebuf,buf,cnt);
    if (retvalue==0)
    {
        printk("write success\r\n");
        memcpy(testdata,writebuf,sizeof(testdata));
    }
    else
    {
        printk("write fail\r\n");
    }
    
    return 0;
}

static struct file_operations chat_fops = {

    .owner = THIS_MODULE,
    .open = chat_open,
    .read = chat_read,
    .write = chat_write,
    .release = chat_close,
};

static int __init chat_init(void)
{
    int retvalue = 0;

    printk("chat init\r\n");
    retvalue = register_chrdev(CHATBASE_MAJOR,CHATBASE_NAME,&chat_fops);
    if(retvalue<0)
        printk("init fail\r\n");

    return 0;
}

static void __exit chat_exit(void)
{
    unregister_chrdev(CHATBASE_MAJOR,CHATBASE_NAME);
    printk("chat exit\r\n");

}



module_init(chat_init);
module_exit(chat_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("liushengquan");