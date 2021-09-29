  .global print
  .global getint
  .global newline
  .global f
  .global main
  // 声明所有函数
  //arm-v7中参数传递前四个参数由r0-r3四个寄存器完成，多出来的参数则利用栈完成参数传递，故此时r0中存储的为n的值。
f: 
  push {lr} //保存返回地址
  cmp r0, #1 //判断n==1
  beq   .L0 //因为或运算，若等于一则直接跳转到为真的情况，反之继续进行判断
  cmp r0, #2 //判断n==2
  bne   .L1 //若不等于二则代表n==1与n==2都不成立则直接跳转到为假的情况，反之执行为真的情况。
.L0:  //为真情况
  mov r0, #1
  pop {pc}
.L1: //为假情况
  mov r4, #0
  push {r0}
  push {r4} //暂存r0,r4的值在栈中因为r0既要传参又要作为返回值返回
  ldr r0, [sp, #4]
  sub r0, r0, #1 //r0寄存器传递参数n-1
  bl f //调用函数f
  str r0, [sp, #0]  //f的返回值存在栈中
  ldr r0, [sp, #4]
  sub r0, r0, #2 //重复上述操作最终得到r4中的值即为返回值f(n-1)+f(n-2)
  bl f
  ldr r4, [sp, #0]
  add r4, r4, r0
  str r4, [sp, #0]
  ldr r0, [sp, #0]
  add sp, sp, #8
  pop {pc} //将push进栈的lr链接pop到pc中完成返回
main:
  push {lr}
  bl getint //从标准输入得到一个整数并存到变量n中
  pop {r0}
  sub sp, sp, #4
  str r0, [sp, #0]
  ldr r0, [sp, #0]
  bl f
  sub sp, sp, #4
  str r0, [sp, #0] //计算f(n)并将之存入变量a中
  ldr r0, [sp, #0]
  push {r0}
  bl print //输出a的值到屏幕
  pop {r0}
  bl newline
  add sp, sp, #8 //恢复栈
  pop {pc}
