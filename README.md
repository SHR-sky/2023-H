# 2023-H
2023年电赛H题工程，完成所有问题。主控采用STM32，软件上采用DFT与FFT算法，通过控制定时器实现精准延时，从而实现相位校准，抑制漂移



思路来自：

[2023全国大学生电子设计竞赛H题全解 [原创www.cnblogs.com/helesheng\] - helesheng - 博客园](https://www.cnblogs.com/helesheng/p/17888312.html)



在实验过程中一定需要注意：

- TIM的位数
- STM32 栈的大小，爆栈之后会使得DA波形出现问题

