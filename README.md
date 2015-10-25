# DoubanFM
使用Qt5构建的豆瓣音乐Linux桌面端。

![DoubanFM](https://raw.githubusercontent.com/sbwtw/doubanFM/master/screenshot/MainWindow.png)

## Qt依赖
Qt5-core Qt5-gui Qt5-widgets Qt5-multimedia Qt5-network Qt5-x11extras
## 第三方库
X11 Xext

## 编译
```
git clone git@github.com:sbwtw/doubanFM.git
cd doubanFM/
mkdir build
cd build
qmake ..
make -j4
./DoubanFM
```

## 安装
### 默认安装为 /usr/bin/DoubanFM
```
make install
```

## 功能
- [x] 使用豆瓣帐号登录
- [x] 歌曲播放及基本控制
- [ ] 加红心、删除等操作
- [x] 最小化到系统托盘
- [ ] 歌曲保存到本地
- [x] 独立的歌词窗口
- [x] 歌词窗口锁定(不接收鼠标事件)
- [ ] 歌词窗口切换动效
- [ ] 切换音乐频道
- [ ] 收藏频道
