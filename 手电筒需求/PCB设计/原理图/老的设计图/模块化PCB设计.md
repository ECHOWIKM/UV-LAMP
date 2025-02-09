# 模块化PCB设计方案

## 1. LED模块（铜基板）
- 尺寸：Φ30mm
- 材质：铝基板（1.0mm厚）
- 散热：整层背面铜箔

### 1.1 元器件布局
```
[LED模块俯视图]
    
         Φ30
    +------------+
    |            |
    |   UV-LED   |
    |    ↑       |
    | LED+  LED- |
    |   红  黑   |
    +------------+

布局说明：
- LED中心定位
- 焊盘尺寸：2×3mm
- 引线：20AWG硅胶线
```

## 2. 充电管理模块
- 尺寸：20×15mm
- 板厚：1.0mm
- 双层PCB

### 2.1 顶层布局
```
[充电模块顶层]
    20mm
+---------------+
| Type-C        |
| TP4056        | 15mm
| DW01+FS8205A  |
+---------------+

元器件位置：
1. Type-C：板边中心
2. TP4056：中心位置
3. 保护IC：靠近电池端
```

## 3. 升压模块（新增）
- 尺寸：15×12mm
- 输入：1.7-2.8V
- 输出：3.7V/1A

### 3.1 元器件布局
```
[升压模块布局]
    15mm
+-------------+
| MT3608      |
| L1  C1      | 12mm
| IN+  OUT+   |
+-------------+

关键器件：
- MT3608（SOT23-6）
- 电感：10μH/2A
- 输入电容：22μF
- 输出电容：47μF
```

## 4. 恒流驱动模块
- 尺寸：15×12mm
- 输入：3.7V
- 输出：700mA恒流

### 4.1 元器件布局
```
[恒流模块布局]
    15mm
+-------------+
| PT4115      |
| L1  D1      | 12mm
| IN+  OUT+   |
+-------------+

关键器件：
- PT4115（SOT23-6）
- 电感：22μH
- 肖特基：SS34
```

## 5. 模块互连关系
```
[系统连接图]

电池(1.7V) → 升压模块(3.7V) → 恒流模块 → LED模块
     ↑
充电模块(5V)
```

## 6. 各模块详细参数

### 6.1 LED模块
- 工作电压：3.7V
- 工作电流：700mA
- 发热功率：2.6W
- 散热要求：铝基板导热系数>1W/m·K

### 6.2 充电模块
- 输入：Type-C 5V
- 充电电流：1A
- 保护功能：
  * 过充：4.2V
  * 过放：2.5V
  * 过流：3A

### 6.3 升压模块
- 升压芯片：MT3608
- 效率：>85%
- 输入范围：1.7-2.8V
- 输出电压：3.7V固定
- 最大输出电流：1A

### 6.4 恒流模块
- 恒流芯片：PT4115
- 输出电流：700mA
- 调光方式：PWM
- 效率：>90%

## 7. 模块间连接

### 7.1 连接线规格
```
1. 电池到升压模块：
   - 规格：20AWG
   - 长度：30mm
   - 颜色：红黑

2. 升压到恒流模块：
   - 规格：22AWG
   - 长度：20mm
   - 颜色：红黑

3. 恒流到LED模块：
   - 规格：20AWG
   - 长度：40mm
   - ��色：红黑
```

### 7.2 焊接要求
- 所有电源连接使用锡焊
- 加装热缩管保护
- 关键点加强固定 