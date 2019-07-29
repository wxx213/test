/*
* file name: hello.c
*/

#include<linux/module.h>


#include<linux/init.h>                                                          


#include<linux/moduleparam.h>


MODULE_AUTHOR("Kevin Taylor");
MODULE_LICENSE("GPL");

static int nbr = 10; 
module_param(nbr, int, S_IRUGO);

static int __init hello_init(void)
{
   int i;

   printk(KERN_ALERT"Init hello mudule...\n");

   for(i=0;i<nbr;i++)
   {   
       printk(KERN_ALERT"Hello, how are you? %d\n", i); 
   }   

   return 0;
}

static void __exit hello_exit(void)
{
   printk(KERN_ALERT"Exit hello mudule...\n");
   printk(KERN_ALERT"I come from hello's module, I have been unload.\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_DESCRIPTION("A Simple Hello World");
MODULE_ALIAS("A simplest module");
