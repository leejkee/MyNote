---
title: How to uninstall adhesive applications in Android
date: 2022-03-31 18:42:17
lang: en
tags:
- Android
- adb
categories:
- 新的入门
- adb
---
<font color=green>Preface:</font></b>As we know, some applications called "XiaomiStore", we can't remove it in our smartphone. However, a tool named "adb", which means Android Debug Bridge, gives us the freedom.  
This page will tell you what it is and how to use, a command line tool, which can remove the adhesive apps.  

_*<font color=red>Tips: This function is true only in __Windows10__ .</font></b>This is my first blog in English, whose mistakes could be send to `cww.lhame@foxmail.com`.*_

# Firstly, download adb for your windows 10.

Visit this [page](https://dl.google.com/android/repository/platform-tools_r33.0.1-windows.zip), and save it in the path what you like.(Recommended in `C:\Users\ _*usename*_ \adb`)  

`\adb` is a directory created by yourself, you will get a "zip flie" called `platform-tools_r33.0.1-windows.zip` if you click the link above.

Then you should extract it to this path, the final directory is like `C:\Users\LHame\adb\platform-tools`, where you can find the file `adb.exe`.  

# Then, add this path to environment variable.
On Windows, just follow these steps:  
- Copy the path you save the `platform-tools`, such as `C:\Users\LHame\adb\platform-tools`.
- Right click `This computer`, chose `properties`(How to do for the disappear of my `This computer`? Right click on your desktop and chose the `Personalize`, `themes` on the left, `Desktop Icons Settings` upper right, ✔ the `computer`)
- Click `Advanced system settings` on the right
- Click `environment variable` on the bottom
- Chose the `path` in the `system variable`, then click `new`, `add`, paste what you copy before
- Finally, click the `OK` to save changes.  


![](/images/eg.gif)




# Check if the adb is OK.
Open a terminal, a software we can do some interesting jobs with it, which can be installed by serching words including "terminal" in Microsoft Store. What's more, you can chose press `Win` + `R` in keyboard to open the `CMD`, alse called `command prompt`.  
Then ,type `adb version` and you should get some messages like here:
```shell
PS C:\Users\LHame> adb version
Android Debug Bridge version 1.0.41
Version 33.0.1-8253317
Installed as C:\Users\LHame\adb\platform-tools\adb.exe
```

# changes for your smartphone
This [page](https://zhuanlan.zhihu.com/p/429854110) will tell you how to do.  
(Emmmm, I am a lazy boy, so I just link a post from Bing. Also many posts about how to unlock the USB-debug options for your mobile can be found. )


Now, evething is OK.  

# Get the start.
Type `adb devices` to list the infomation your smartphone, your will get message as:
```shell
PS C:\Users\LHame> adb devices
List of devices attached
xxxxxxxx        device
```
You can not make sure your mobile is OK until you have gotten the number of your device.(must be a number)

## list the applications
Type
```shell
adb shell pm list packages
```

for example:
```shell
PS C:\Users\LHame> adb shell pm list packages
package:com.miui.screenrecorder
package:com.qualcomm.qti.haven.telemetry.service
package:com.android.cts.priv.ctsshim
package:com.qualcomm.qti.auth.sampleextauthservice
package:com.qualcomm.qti.perfdump
package:com.android.providers.telephony
package:com.miui.powerkeeper
package:com.miui.qr
package:com.mi.liveassistant
package:org.codeaurora.bt_wipowersdk
package:com.android.providers.calendar
package:com.android.providers.media
package:com.milink.service
package:com.qti.service.colorservice
package:com.xiaomi.powerchecker
package:com.xiaomi.account
package:com.android.wallpapercropper
package:com.quicinc.cne.CNEService
package:com.qualcomm.qti.autoregistration
package:com.xiaomi.micloud.sdk
package:com.qualcomm.qti.smcinvokepkgmgr
package:com.android.updater
package:com.leiting.xian
package:com.android.documentsui
package:com.android.externalstorage
package:com.qualcomm.uimremoteclient
package:com.xiaomi.gamecenter.sdk.service
package:com.android.htmlviewer
package:com.qualcomm.svi
package:com.qualcomm.qti.uceShimService
package:com.android.companiondevicemanager
package:com.miui.gallery
package:com.android.quicksearchbox
package:com.android.mms.service
package:com.android.providers.downloads
package:com.qualcomm.qti.auth.sampleauthenticatorservice
package:com.xiaomi.payment
......
......
```

## uninstall what you want to remove
Type
```shell
adb shell pm uninstall --user 0 <apps name>
```
for example:
We want to remove a application called "XiaomiPayment", we can find it from above list.
```shell
PS C:\Users\LHame> adb shell pm uninstall --user 0 com.xiaomi.payment
Success
```
The app was uninstalled when we got "Success".

Of course, you shouldn't remove some important packages(apps) for the Android.(You can get detials by Bing and Google.)
