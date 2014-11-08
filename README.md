---
layout: post
category: 科创
tags: 开发 音频 SRT
description: 用于帮助SRT切割音频数据的小工具
---

### 功能简介

  * 根据存储在文件中的起止时间，批量利用ffmpeg一次性将音频切成多段
  * 输出文件的命名即为文件中的标记名称
  * 忽略每行后面的其他信息（可以直接用标记过情感的文本文件输入）
  * 自动将导入的音频文件转换为单声道、16位精度、16K采样的.wav格式

### 使用说明

  1. 将ffmpeg.exe与cut_the_fruit.exe及待切割的音频和存储时间点的txt放在同一路径下
  2. 对于存储时间点的txt的格式要求示例如下：
		
		lyf_1_1.wav 0:00:34 0:01:05 1 2 感伤
		lyf_1_2.wav 0:01:26 0:02:00 这里其实写什么都没关系

	 其中时间格式没有要求，但必须以冒号隔开，至于05写成5、00写成0都无所谓。时间点后面怎么写也不会影响到程序，只要保证前三项分别是文件名、开始时间点、结束时间点即可。
  3. 运行cut_the_fruit.exe，根据提示输入文件名即可，要求必须输入含扩展名的全名，程序运行过程中可能需要根据提示输入y来确认覆盖文件。
  4. 在承认梁盾大神万岁之后，切好的音频片段将出现在同一目录下。

### 使用示例

  * 输入音频文件：test.mp3
  * 输入存储时间点的txt文件：1.txt

		LYF_1_1.WAV 0:00:34 0:01:05 1 -2 感伤的、柔和的
		LYF_1_2.WAV 0:01:25 0:01:40 3 1	激昂的、跳跃的
  
  * 得到文件：

  	| *文件名称* | *文件描述* |
	| ------------- |:--------------------------------:|
	| test.wav | 由test.mp3转换而来的符合要求的.wav文件 |
	| LYF_1_1.WAV | 截取test.wav从0分34秒到1分05秒的音频片段 |
	| LYF_1_2.WAV | 截取test.wav从1分25秒到1分40秒的音频片段 |

### TO DO LIST

  * 如果输入本身就是.wav文件，转换单声道、16位精度、16K采样时会覆盖掉原文件，懒得改了
  * 要求截取音频2-6秒，本想加个计算时间如果不在范围内就拒绝转换，后来觉得这样太针对作业了……
  * **其实应该改用Python的。**
