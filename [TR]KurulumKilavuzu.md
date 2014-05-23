Kurulum Kılavuzu	{#welcome}
=====================
[TOC]

##1. Kodların Derlenmesi {#compiling}

###1.1 Client
[ISMR Repo][1]'sundan kodları indirin. [Gerekli yazılımları][2] bilgisayarınıza kurduktan sonra **Client** klasörünün içerisine girip **buildAll.sh** dosyasını çalıştırarak kodları derleyin.

```
./buildAll.sh
```

> Not: Irrlicht kütüphanesi ile ilgili hatalar için 4.1 başlığına bakınız.

###1.2 Rover
Robotun içerisindeki /home/pi klasöründe repodaki **Raspberry PI** klasörü bulunmaktadır.  Client ile aynı şekilde burada da kodları derlemek için **buildAll.sh** dosyasını çalıştırmak yeterli olacaktır.

```
./buildAll.sh
```


##2. Robota Güç Verilmesi  {#initsh}
ISMR robota güç vermek için 5V 1A çıkış veren PowerBank'i Raspberry PI'a micro USB girişinden, 11V'luk LiPo'yu ise kırmızı motor driver board'dan çıkan mavi kabloya Vcc, siyah kabloya ground gelecek şekilde bağlayın. Robot açılırken client tarafında start isimli dosyayı çalıştırdığınıza emin olun. Eğer robot daha önce açılmışsa start dosyasını çalıştırdıktan sonra robot içerisinde /home/pi klasörüne giderek init.sh scriptini tekrar çalıştırın.

```
./init.sh
```


##3. Bilgisayar ile İletişim

ISMR **GYTE_Bilmuh** SSID ile yayın yapa kablosuz ağa otomatik olarak bağlanır. Bağlandıktan bir süre sonra aldığı IP adresini client'a socket aracılığıyla gönderip video streamini açıp GPIO pinlerini motor sürmek için ayarlar. Bu nedenle robota güç verdikten sonra **Client** klasöründeki start isimli dosyayı 7879 argümanıyla beraber çalıştırın. 


```
./start 7879
```

> **İlk Kez Çalıştırma:** 
Robot'un kendi IP adresini göndereceği client'ın IP adresi /home/pi/init.sh dosyasında SERVERIP değişkeninde tanımlanmıştır. Bu nedenle IP adresinizi önelikle bu dosyaya girerek [2.başlıkta][3] belirtildiği gibi init.sh scriptini tekrar çalıştırın.
> 
> *Robota ilk erişim için eth0 arayüzü kullanılabilir.*


##4. Kurulum ile İlgili Olası Hatalar
###4.1 Irrlicht ile ilgili hatalar

```
#include <irrlicht/irrlicht.h>
#include <irrlicht/ICursorControl.h>
```

Yukarıdaki dosyalar bazı sistemlerde irrlicht/ klasörü altındadır. Eğer derleme esnasında hata alıyorsanız yukarıdaki iki satırı aşağıdaki gibi değiştirerek tekrar derleyin.

```
#include <irrlicht.h>
#include <ICursorControl.h>
```
###4.2 Video Stream Açılmıyor/Model geç geliyor
Video stream açılışta bir süre gelen görüntüyü önbelleklemektedir. Bu nedenle 30sn sonra model açılmaktadır. Eğer video stream açılmazsa opencv-stream-overlay klasörüne girerek aşağıdaki şekilde tekrar başlatabilirsiniz.

```
./opencv-stream-overlay http://RASPIBERRYIP:8090 AugmentationPORT(default:7578)
```
###4.3 Program Çıktıları ve Hata Mesajları
####4.3.1 Client
Program çıktıları ve hata mesajları logs klasöründedir.

Program Çıktıları:
> model.log
> stream.log

Program hata mesajları:
> modelerrors.log
> streamerrors.log
####4.3.2 Rover
Program çıktıları ve hata mesajları /home/pi/logs klasöründedir.

Program Çıktıları:
> driver.log
> stream.log

Program hata mesajları:
> drivererrors.log
> streamerrors.log


  [1]: https://github.com/furkantektas/ismr
  [2]: #requiredlibs
  [3]: #initsh
  [4]: http://math.stackexchange.com/
  [5]: http://daringfireball.net/projects/markdown/syntax "Markdown"
  [6]: https://github.com/jmcmanus/pagedown-extra "Pagedown Extra"
  [7]: http://meta.math.stackexchange.com/questions/5020/mathjax-basic-tutorial-and-quick-reference
  [8]: https://code.google.com/p/google-code-prettify/
  [9]: http://highlightjs.org/
