========================================================================
    CONSOLE APPLICATION : amr-nb-dec-example Project Overview
========================================================================

AppWizard has created this amr-nb-dec-example application for you.

This file contains a summary of what you will find in each of the files that
make up your amr-nb-dec-example application.


amr-nb-dec-example.vcproj
    This is the main project file for VC++ projects generated using an Application Wizard.
    It contains information about the version of Visual C++ that generated the file, and
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

amr-nb-dec-example.cpp
    This is the main application source file.

/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named amr-nb-dec-example.pch and a precompiled types file named StdAfx.obj.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" comments to indicate parts of the source code you
should add to or customize.

/////////////////////////////////////////////////////////////////////////////

编码方式
Mode 0 - AMR 4.75 - Encodes at 4.75kbit/s
Mode 1 - AMR 5.15 - Encodes at 5.15kbit/s
Mode 2 - AMR 5.9 - Encodes at 5.9kbit/s
Mode 3 - AMR 6.7 - Encodes at 6.7kbit/s
Mode 4 - AMR 7.4 - Encodes at 7.4kbit/s
Mode 5 - AMR 7.95 - Encodes at 7.95kbit/s
Mode 6 - AMR 10.2 - Encodes at 10.2kbit/s
Mode 7 - AMR 12.2 - Encodes at 12.2kbit/s
8~15位一些 noise frames 和保留位的定义。

对应帧的大小
CMR Mode Frame size (bytes)
0 AMR 4.75 13
1 AMR 5.15 14
2 AMR 5.9 16
3 AMR 6.7 18
4 AMR 7.4 20
5 AMR 7.95 21
6 AMR 10.2 27
7 AMR 12.2 32

我们来做一个简单的计算，PCM16和AMR之间的转换
Amr 一帧为20毫秒

AMR 4.75Kbits/s:
每秒产生的声音位数 = 4750bits/s
每20ms帧占用的位数 = 4750bits/s / 50frames/s = 95bits
每20ms帧占用的字节数 = 95bits / 8bits/byte = 11.875bytes - 圆整到12字节，不足的补0
加上一个字节的帧头，所以，20ms一帧的AMR: 12-bytes + 1-byte = 13-bytes
相反，转换回来就成了
13-bytes * 50frames/s * 8bits/byte = 5200bits/s
注意，这里两个数值并不对应，是由于圆整地原因
编辑本段

文件格式

Amr的文件格式极为简单，如图1所示：
文件最开始时6个字节的header，
[#!AMR\n] 括号间的部分
(或者十六进制表示为 0x2321414d520a ).
接下来就是连续的语音帧，
每个帧包含一个帧头+语音数据
帧头如图2所示：
P设置为0
FT为编码模式，上面已经列举了可用的值。
Q为帧质量指示器，如果为0表明帧被损坏，接受者需要将RX_TYPE设置成SPEECH_BAD或者SID_BAD。
何为RX_TYPE请参考RFC3267，其实该节介绍的内容都可以在RFC3267里面找到。
图3 这个图表为 5.9 kbit 编码的文件格式 (with 118 speech bits)
其中P为补0位。
