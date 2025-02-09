# UV手电筒模块化PCB设计说明

## 1. 模块基本参数

### 1.1 LED模块（铝基板）
- 尺寸：Φ30mm圆形
- 材质：铝基板
- 厚度：1.0mm
- 铜箔：2oz
- 阻焊：白色
- 表面：沉金

### 1.2 充电管理模块
- 尺寸：20×15mm
- 层数：双层FR4
- 厚度：1.0mm
- 铜箔：1oz
- 阻焊：绿色
- 表面：喷锡

### 1.3 升压模块
- 尺寸：15×12mm
- 层数：双层FR4
- 厚度：1.0mm
- 铜箔：1oz
- 最小线宽：0.25mm
- 最小孔径：0.3mm

### 1.4 恒流模块
- 尺寸：15×12mm
- 层数：双层FR4
- 厚度：1.0mm
- 铜箔：1oz
- 散热设计：过孔阵列

## 2. 模块布局设计

### 2.1 LED模块布局
```
[LED模块顶层]
    
         Φ30mm
    +---------------+
    |   散热区域    |
    |  +--------+  |
    |  |UV-LED  |  |
    |  |焊盘区域|  |
    |  +--------+  |
    |   引线区域   |
    +---------------+

布局要求：
1. LED中心定位
2. 热焊盘：5×5mm
3. 电源焊盘：3×2mm
4. 散热过孔：0.3mm间距
```

### 2.2 充电模块布局
```
[充电模块顶层]
      20mm
+------------------+
| Type-C  LED指示  |
|   TP4056         | 15mm
| DW01-P FS8205A   |
| BAT+    BAT-     |
+------------------+

布局要求：
1. Type-C靠边缘
2. 充电IC居中
3. 保护IC靠近输出端
4. LED指示清晰可见
```

### 2.3 升压模块布局
```
[升压模块顶层]
      15mm
+------------------+
| MT3608  L1(10μH) |
| C1   D1(SS34)    | 12mm
| IN+  OUT+        |
| IN-  OUT-        |
+------------------+

布局要求：
1. 电感靠近芯片
2. 输入输出端分开
3. 大面积铺铜
4. 关键走线短粗
```

### 2.4 恒流模块布局
```
[恒流模块顶层]
      15mm
+------------------+
| PT4115  L1(22μH) |
| C1   D1(SS34)    | 12mm
| IN+  OUT+        |
| IN-  OUT-        |
+------------------+

布局要求：
1. 电感靠近芯片
2. 采样电阻独立
3. 散热优先考虑
4. 反馈走线短小
```

## 3. 走线设计要求

### 3.1 电源走线
- LED电流路径：1.2mm宽
- 充电电流路径：0.8mm宽
- 信号线：0.25mm宽
- 地线：大面积铺铜

### 3.2 关键信号
1. 升压反馈：
   - 差分布线
   - 远离干扰源
   - 包地保护

2. 电流采样：
   - 开尔文连接
   - 独立走线
   - 就近采样

### 3.3 接口设计
1. 电源接口：
   - 焊盘：3×2mm
   - 过孔：Φ0.8mm
   - 加强铜箔

2. 信号接口：
   - 焊盘：2×1.5mm
   - 过���：Φ0.4mm
   - 阻焊开窗适中

## 4. 特殊工艺要求

### 4.1 散热设计
1. LED模块：
   - 整层背铜
   - 散热过孔阵列
   - 导热系数>1W/m·K

2. 升压模块：
   - 芯片下方铺铜
   - 过孔散热设计
   - 电感散热区域

3. 恒流模块：
   - 大面积铺铜
   - 关键器件散热
   - 边缘散热槽

### 4.2 EMC设计
1. 地平面分割：
   - 数字地独立
   - 模拟地分开
   - 单点连接

2. 去耦设计：
   - 电源去耦
   - 旁路电容
   - 高频抑制

### 4.3 防护要求
1. 机械防护：
   - 加强焊盘
   - 过孔填充
   - 边缘圆弧

2. 电气防护：
   - 防反接设计
   - 过流保护
   - 静电防护 