# DoubanFM
使用Qt5构建的豆瓣音乐Linux桌面端。
如果你喜欢本项目，别忘了点个赞！如果你有时间，欢迎加入共同开发～

![DoubanFM](https://raw.githubusercontent.com/sbwtw/doubanFM/master/screenshot/MainWindow.png)

## 功能
- [x] 使用豆瓣帐号登录
- [x] 歌曲播放及基本控制
- [x] 加红心、删除等操作
- [x] 最小化到系统托盘
- [ ] 歌曲保存到本地
- [ ] 资源缓存
- [ ] 离线播放
- [x] 独立的歌词窗口
- [x] 歌词窗口锁定(不接收鼠标事件)
- [ ] 歌词窗口切换动效
- [x] 切换音乐频道
- [ ] 收藏频道
- [ ] 支持Fn媒体热键

## 控制
DoubanFM 为保持与豆瓣网页版一样简洁的显示界面，功能控制由快捷键实现。

|快捷键 |功能             |备注                   |
|-------|-----------------|-----------------------|
|L      |显示/隐藏歌词    |Lyric                  |
|C      |显示/隐藏频道窗口|Channel                |
|W      |解锁歌词窗口     |拖动后自动锁定         |
|Esc    |隐藏主窗口       |隐藏到托盘             |
|Esc+Esc|退出程序         |双击Esc退出            |

## Qt依赖
Qt5-core Qt5-gui Qt5-widgets Qt5-multimedia Qt5-network Qt5-x11extras
## 第三方库
X11 Xext gstreamer1.0-plugins-bad

## 编译
```
git clone git@github.com:sbwtw/DoubanFM.git
cd DoubanFM/src/
mkdir build
cd build
qmake ..
make -j4
```
编译好的二进制文件保存在DoubanFM/src/DoubanFM

## 安装
### 默认安装为 /usr/bin/DoubanFM
```
make install
```
