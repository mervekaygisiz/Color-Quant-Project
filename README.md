# Color-Quant-Project

YÖNTEM: Bottom-up algoritması kullanılmıştır.
İlk olarak pikselleri dosyadan alıp algoritma için kullanmak amacıyla matrise atadık, sonra bu pikselleri diziye atadık .
Diziyi sıraladık. Piksellerim dizide 1 kere geçmesi gerektiğinden diziyi unique hale getirip farklı bir diziye atadık.

Kümeleme yapılırken gerçeklenen adımlar: 

 Bir distance matrisi oluşturmak
Her pikselin diğer piksellerle olan mesafesini buluyoruz ancak burda distance matrisinin boyutu unique piksel sayısı+1 olmalıdır. 
Çünkü distance matrisimin 0. Satır ve 0. Sutun elemanlarına unique piksel değerlerimi atarım
Distance matrisini hesaplarken 1. Satır ve 1. Sutundan itibaren başlarım. Distance matrisini böyle kullanmamızın amacı bu matristeki en küçük mesafeyi bulunca bu en küçük mesafe hangi piksel değerlerine ait olduğunu kolayca bulabilmektir.
 Distance matrisinde ki en küçük mesafeyi bulmak
 Bulunan en küçük mesafe hangi piksellere aitse bu piksel değerlerinin
ortalamasını almak
 Unique dizisindeki en küçük mesafeye sahip olan o iki piksel değerini
artık bulunan ortalama değerle değiştirmek yanı o değere kümelemek. Sonra bu diziyi sıralayarak unique dizisini tekil hale getirmek (tekrar eden sayı olmamalı), dizi tekil hale gelirken her defasında dizi boyu 1 eleman azalıcaktır.
 Algoritma için kulanılan piksellerimin var olduğu maristeki bu en küçük mesafe hangi piksellere aitse bu piksel değerlerini hesaplanan ortalama değerle değiştirmek yani o değere kümelemek.
 Bu yukarıdaki adımlar unique dizimdeki elemansayısı -1 degeri kullanıcının istediği indergeme sayısına eşit olana dek döngü devam eder.
While döngüsü devam ederken her seferinde unique piksel eleman sayısı 1 azalacagından distance matisi her defasında o oranda küçülecektir.

Projenin perfonmansını arttırmak amacıyla while döngüsünde matrisi güncelemek yerine en son güncelleme yapılırsa optimum hale gelmiş olacaktır.
