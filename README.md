Bu program, simüle edilmiş sensör verileri üretir, 
farklı filtreleme tekniklerini kullanarak veriyi işler ve 
temel istatistiksel analizler gerçekleştirir. Sonuçlar hem 
konsolda görüntülenir hem de bir metin dosyasına kaydedilir.

***Derleme ve Çalıştırma***

Geliştirme Ortamı: Visual Studio'22
Derleyici: C++17 uyumlu bir derleyici (ör. GCC, MSVC, Clang).
Geliştirme Ortamı: Visual Studio, VS Code veya tercih ettiğiniz bir IDE.
C++ Standardı: C++17 veya üstü.

***Tasarım Kararları***

-------1. Sınıf Tabanlı Tasarım-------
 --a. Sensor Sınıfı--
 Amaç:
 Rastgele sensör verileri üretir ve bu verileri bir vektörde saklar.

 Tasarım Kararı:
 Sensör veri üretimini kapsüllemek için ayrı bir sınıf kullanmak, 
 veri üretiminden bağımsız bir yapı oluşturur. Bu sayede, veri üretim 
 algoritması kolayca değiştirilebilir.
 
 --b. DataProcessor Sınıfı--
 Amaç:
 Sensör verileri üzerinde filtreleme ve istatistiksel analiz yapmak.
 
 Tasarım Kararı:
 Veri işleme işlevlerini bir sınıf içinde kapsüllemenin avantajı, bu işlevlerin tekrar kullanılabilir hale gelmesidir.
 Veri işleme algoritmaları, ham veri ve işlenmiş veri üzerinde ayrı ayrı çalışır. Bu, veri işleme sürecini daha modüler hale getirir.

 Özellikler:
 Basit Ortalama Filtresi: Tüm veri setinin ortalamasını alır.
 Hareketli Ortalama Filtresi: Pencere boyutuna göre kayan bir ortalama hesaplar. Bu, veriyi daha pürüzsüz hale getirmek için kullanılır.
 Minimum, maksimum ve ortalama değerlerin hesaplanması.
 Veri boş olduğunda bu işlevlerin güvenli bir şekilde çalışmasını sağlamak için kontroller eklenmiştir.
 Modülerlik: Eğer yeni bir filtre eklenmesi gerekirse, mevcut sınıfa yeni bir metot eklemek yeterlidir.


***İsteğe Bağlı Bölümlerin Açıklaması***

----Dosya Çıktısı----
Program, analiz edilen verileri bir metin dosyasına kaydetmek için şu adımları izler:
1-)Dosya adının benzersiz olması için bir timestamp (zaman damgası) kullanılır. 
Bu, dosya adının her çalıştırmada farklı olmasını sağlar.
2-)Dosya yazma işlemi için bir std::ofstream nesnesi kullanılır. 
Dosyanın doğru bir şekilde açılıp açılmadığı kontrol edilir
3-)Dosyaya yazma işlemi, std::ofstream kullanılarak yapılır. Hem ham veri (raw data) 
hem de işlenmiş veri (processed data) dosyaya yazılır. 

----Kullanıcı Veri Girişi----
Kullanıcıdan veri girişi, programın sensör verilerini oluşturma, işleme ve analiz etme sürecini özelleştirmek için alınır. Program, 
kullanıcıya şu esnekliği sağlar:

Üretilecek Veri Sayısı: Kullanıcı, kaç adet sensör verisi üretileceğini belirler.
Veri Aralığı: Kullanıcı, sensör verilerinin hangi minimum ve maksimum değerler arasında olması gerektiğini tanımlar.
Filtreleme Yöntemi: Kullanıcı, verilerin nasıl işleneceğini seçer:
 Basit Ortalama Filtresi
 Hareketli Ortalama Filtresi
Hareketli Ortalama Pencere Boyutu: Eğer hareketli ortalama filtresi seçilirse, kullanıcı pencere boyutunu belirler.
Bu girişler sayesinde program, farklı kullanıcı ihtiyaçlarına göre özelleştirilir ve esneklik kazanır.

----Kullanıcı Girdilerinin Hata Kontrolü----
Kullanıcıdan alınan girdiler üzerinde çeşitli doğrulamalar yapılır. Bu, yanlış veya eksik girdilerin tespit
 edilmesini ve kullanıcıya tekrar giriş yapması için fırsat tanınmasını sağlar.
Her hata durumunda kullanıcıya açıklayıcı mesajlar verilir. Mesajlar, hatanın nedenini ve nasıl düzeltileceğini açıklar.
Bu geri bildirimler, kullanıcı deneyimini artırır ve programın doğru kullanımını kolaylaştırır.
