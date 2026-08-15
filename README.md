# 2023 年全国大学生电子设计竞赛 H 题：信号分离装置

本仓库保存 2023 年全国大学生电子设计竞赛 H 题“信号分离装置”的 STM32F407 工程、参赛报告，以及与固件查表数据一致的 Python/MATLAB 生成脚本。

系统对两路正弦波或三角波的叠加信号进行采样，通过 DFT 相关运算识别两个基频，通过 FFT 谐波能量判断波形类型，再使用片内双路 DAC 重建两路信号。程序持续测量输入与重建信号的相位差，并调整定时器计数值完成相位校准，以减小输出漂移。

> 本仓库用于学习和复现参赛方案。实际电路的模拟前端增益、偏置、输入保护和供电方式请以自己的硬件为准，不要将负电压或超过 VDDA 的电压直接接入 STM32 ADC。

## 实现效果

参赛报告记录的主要结果如下：

- 支持约 10 kHz～100 kHz 的正弦波/三角波分离，固件频率步进为 5 kHz。
- 双路 DAC 分别输出识别和重建后的波形。
- 输出信号可保持同频并通过实时校相抑制漂移。
- 分离信号相位差可控，报告测试点的误差不超过约 0.4°。
- 报告中的重建输出峰峰值约为 1.47 V～1.53 V；该结果依赖实际模拟电路和测试条件。

原始赛题见 [`H题_信号分离装置.pdf`](./H题_信号分离装置.pdf)，完整的方案论证、电路框图和测试数据见 [`S08_2023电赛H题报告.pdf`](./S08_2023电赛H题报告.pdf)。

## 工作原理

整体数据流如下：

```text
信号 A ─┐
        ├─ 模拟加法器 ─ ADC1 + DMA ─ DFT 频率检测 ─ FFT 波形分类 ─┬─ DAC1 + DMA ─ A'
信号 B ─┘                                                        └─ DAC2 + DMA ─ B'
                                  ↑                                       │
                                  └──────── 相关法测相 + 定时器校相 ────────┘
```

### 1. 采样

- ADC1 通道 9（PB1）采集叠加信号。
- TIM3 更新事件触发 ADC，DMA2 Stream0 将数据搬运到采样缓冲区。
- APB1 定时器时钟为 84 MHz，预分频器为 0、自动重装载值为 83，因此实际触发频率为：

  ```text
  fs = 84 MHz / (0 + 1) / (83 + 1) = 1 MHz
  ```

- DFT 检测使用 1000 个采样点，即约 1 ms 数据。

源码部分注释写有“2 MHz”，但根据时钟树和定时器参数计算为 **1 MHz**；理解或移植工程时应以寄存器配置为准。

### 2. 频率检测

程序预存 19 组正弦和余弦模板，对应 10、15、20、……、100 kHz。每组保存 200 点，相关计算时通过 `i % 200` 重复模板，覆盖 1000 个采样点。

对每个候选频率分别计算同相、正交相关量：

```text
I(k) = Σ (x[n] - 2048) × (sin_table[k][n mod 200] - 2048)
Q(k) = Σ (x[n] - 2048) × (cos_table[k][n mod 200] - 2048)
P(k) = sqrt(I(k)² + Q(k)²)
```

`P(k)` 最大和第二大的两个候选频点即被认为是输入信号的两个基频。该方法只计算已知候选频点，比计算完整频谱更直接，也能同时得到相位信息。

### 3. 波形分类

程序对采样数据去直流后执行 1024 点 FFT，比较基波与三次谐波附近各 3 个频点的能量。正弦波的高次谐波很弱，而三角波包含明显的奇次谐波，因此可以据此分类。

当较高频率恰好等于较低频率的 3 倍时，较低信号的三次谐波会与另一信号的基波重合。程序对 10/30、15/45、20/60、25/75、30/90 kHz 这几组情况改用五次谐波辅助判断。

### 4. 波形重建与相位校准

- 正弦波和三角波均使用 200 点、12 位量化表，中心值为 2048，幅度为 1500，理论范围为 548～3548。
- TIM4 触发 DAC1（PA4），DMA1 Stream5 循环输出第一路表。
- TIM6 触发 DAC2（PA5），DMA1 Stream6 循环输出第二路表。
- 两个 DAC 的更新率均为 1 MHz；同一张 200 点表中预先放入整数个周期，从而得到 10～100 kHz、步进 5 kHz 的输出。
- 程序通过正交相关量的 `atan2` 计算相位，再调整 TIM4/TIM6 的计数器实现延迟校相。

## 硬件与软件环境

| 项目 | 本工程配置 |
| --- | --- |
| MCU | STM32F407ZGTx，Cortex-M4F |
| 系统时钟 | 168 MHz |
| IDE | Keil µVision 5（最后一次构建记录为 5.38） |
| 编译器 | Arm Compiler 5.06 update 7 |
| 固件库 | STM32F4xx Standard Peripheral Library + CMSIS |
| 调试器 | 工程配置为 ST-Link |
| 构建目标 | `Control` |

关键接口：

| 功能 | 引脚/外设 | 说明 |
| --- | --- | --- |
| 混合信号 ADC 输入 | PB1 / ADC1_IN9 | 12 位 ADC，TIM3 触发，DMA2 Stream0 |
| 重建信号 A′ | PA4 / DAC_OUT1 | TIM4 触发，DMA1 Stream5 |
| 重建信号 B′ | PA5 / DAC_OUT2 | TIM6 触发，DMA1 Stream6 |
| 控制串口 | PA2/PA3 / USART2 | 115200，8-N-1 |
| 预留串口 | PB10/PB11 / USART3 | 工程中已初始化为 115200，8-N-1 |

USART2 当前采用单字节控制协议：接收 `0x01` 时软件复位；其他字节进入扩展模式，并把字节值作为待设置的相位角。由于协议只有一个字节，可直接表示的范围为 0～255；`0x01` 已被复位命令占用。

## 仓库结构

```text
.
├── H/                              # 原始 Keil/STM32 工程（本次未修改）
│   ├── Hardware/                   # ADC、DAC、DMA、定时器和串口驱动
│   ├── Libraries/                  # CMSIS 与 STM32F4 标准外设库
│   ├── Project/RVMDK/              # Keil 工程、构建产物和调试配置
│   └── User/                       # 主程序、FFT 库与查表数据
├── scripts/
│   ├── generate_lookup_tables.py   # Python 3 打表程序
│   └── generate_lookup_tables.m    # MATLAB 打表程序
├── H题_信号分离装置.pdf              # 2023 年 H 题原始赛题
├── S08_2023电赛H题报告.pdf          # 参赛报告
└── README.md
```

## Keil 编译与下载教程

### 1. 准备环境

1. 安装 Keil MDK 5，并安装支持 Arm Compiler 5 的工具链。工程最后一次成功构建使用 `V5.06 update 7 (build 960)`。
2. 在 Pack Installer 中安装 STM32F4 系列器件支持包。
3. 使用 ST-Link 连接开发板，确认目标芯片、供电和 SWD 接线正确。

### 2. 打开并构建

1. 用 Keil 打开 [`H/Project/RVMDK/TemplateF407.uvprojx`](./H/Project/RVMDK/TemplateF407.uvprojx)。
2. 在工具栏选择目标 `Control`。
3. 打开 `Options for Target`，确认 Device 为 `STM32F407ZGTx`、编译器为 Arm Compiler 5。
4. 执行 `Rebuild`。仓库现有构建记录为 `0 Error(s), 7 Warning(s)`，生成文件位于 `H/Project/RVMDK/Objects/`。
5. 连接 ST-Link 后执行 `Download`，然后复位运行。工程已配置生成 `TemplateF407.hex`，也可以用其他烧录工具写入该文件。

若 Keil 提示找不到 Compiler 5，可在 `Manage Project Items / Folders/Extensions` 或 MDK 安装器中补装 Legacy Arm Compiler 5，并在 Target 设置中重新选择它。

### 3. 接线与测试

1. 将两路待分离信号先通过外部加法器叠加，并进行幅值缩放和直流偏置，使 PB1 上的电压始终处于 ADC 合法输入范围。
2. 信号频率应选择 10～100 kHz 范围内的 5 kHz 整数步进频点，且两路频率不同。
3. 将 PA4、PA5 分别接到示波器通道，观察重建后的两路信号。
4. 基础模式会持续测相并校准；需要设置相位差时，可通过 USART2 发送单字节角度值。
5. 若输出削顶、幅度异常或分类不稳定，优先检查输入偏置/幅度、共地、采样时钟和模拟前端带宽。

## 生成查表数据

两个脚本使用同一组默认参数，并生成可直接复制到 C 工程中的头文件和便于检查的 CSV：

- 采样率：1 MHz
- 频率：10～100 kHz，步进 5 kHz，共 19 组
- 每组：200 点
- 12 位 DAC 中心值：2048
- 幅度：1500
- 采样序号从 `n = 1` 开始，与 `H/User/main.c` 的现有数据一致

量化前的波形为：

```text
sine(n)     = offset + amplitude × sin(2πft)
cosine(n)   = offset + amplitude × cos(2πft)
triangle(n) = offset + amplitude × (2/π) × asin(sin(2πft - π/2))
t           = (n + 1) / fs,  n = 0, 1, ..., points - 1
```

所有结果四舍五入并限制在 0～4095。

### Python 3

无需安装第三方库：

```bash
python scripts/generate_lookup_tables.py
```

默认输出到 `scripts/generated/`。查看参数和自定义输出目录：

```bash
python scripts/generate_lookup_tables.py --help
python scripts/generate_lookup_tables.py --output-dir build/tables
```

### MATLAB

在仓库根目录执行：

```matlab
addpath('scripts');
generate_lookup_tables;
```

也可以指定输出目录：

```matlab
generate_lookup_tables(fullfile('build', 'tables'));
```

两种实现都会生成：

- `lookup_tables.h`：`DAC_SIN`、`DAC_COS`、`Tri_Wave` 三个扁平 C 数组，每 200 个元素对应一个频率。
- `lookup_tables.csv`：每行包含频率、样本序号及三种波形的量化值，适合绘图或对比。

脚本默认输出目录已被 Git 忽略，避免误提交大量派生数据。如需更新固件中的表，请先生成并核对，再手动替换；脚本不会修改原始 Keil 工程。

## 移植与调参

修改采样率、定时器或候选频率时，以下参数必须保持一致：

1. TIM3 的 ADC 触发率。
2. TIM4/TIM6 的 DAC 更新率。
3. Python/MATLAB 脚本的 `sample_rate`、频率范围和点数。
4. `main.c` 中频率索引换算、数组长度和相关计算的取模长度。
5. FFT 频点索引 `frequency / sample_rate × FFT_length`。

只改其中一处会造成频率识别错误、输出频率偏差或相位持续漂移。

## 已知注意事项

- `startup_stm32f40xx.s` 中栈大小为 `0x6000`。FFT 和多个局部大数组会占用较多栈空间；缩小栈可能导致异常或 DAC 波形错误。
- 当前 `ADCConvertedValue` 和 DMA 长度定义为 1000，但波形分类函数按 1024 点读取数据。原工程保留了这一实现；继续开发时应统一缓冲区、DMA 长度与算法长度，并重新验证时序和内存占用。
- 三次/五次谐波超过奈奎斯特频率时，需要考虑频谱折叠和 FFT 索引边界。扩展频率范围前应增加边界处理。
- 固件的候选频率映射是 `10 kHz + index × 5 kHz`。报告中个别“5 kHz 起始”或“2 MHz 采样”的描述与当前代码不一致，复现本仓库时以代码配置为准。
- 工程依赖 Arm Compiler 5 汇编版本的 FFT 实现；直接切换 Arm Compiler 6 可能需要替换汇编文件或使用 CMSIS-DSP 的兼容实现。

## 参考资料

- 原始赛题：[`H题_信号分离装置.pdf`](./H题_信号分离装置.pdf)
- 仓库内参赛报告：[`S08_2023电赛H题报告.pdf`](./S08_2023电赛H题报告.pdf)
- 思路参考：[2023 全国大学生电子设计竞赛 H 题全解（helesheng）](https://www.cnblogs.com/helesheng/p/17888312.html)

欢迎通过 Issue 交流复现过程、硬件差异和改进方案。
