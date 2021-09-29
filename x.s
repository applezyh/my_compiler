  .global print
  .global getint
  .global newline
  .global f
  .global main
  // 声明所有函数
  //arm-v7中参数传递前四个参数由r0-r3四个寄存器完成，多出来的参数则利用栈完成参数传递，故此时r0中存储的为n的值。
f: 
  push {lr}
  sub sp, sp, #4
  mov r1, #1
  str r1, [sp, #0]
.L0:
  cmp r0, #1 //如果n大于等于1则执行循环主体
  ble .L2 //不符合则跳出循环
.L1:
  ldr r1, [sp, #0]
  mul r1, r1, r0 
  str r1, [sp, #0] //完成re=re*n
  sub r0, r0, #1 //完成n=n-1
  b .L0 //继续循环
.L2: //循环结束返回
  ldr r0, [sp, #0] 
  add sp, sp, #4
  pop {pc}
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
