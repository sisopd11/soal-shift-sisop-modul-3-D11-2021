# soal-shift-sisop-modul-3-D11-2021

Modul 3 
|Nama|NRP|
|----|-----|
|Afifah Nur Sabrina Syamsudin|05111940000022|
|Dewi Mardani Cristin|05111940000225|
|Avind Pramana Azhari|05111940000226|

## Soal No 2

### a: Jawaban dan Penjelasan
Pada soal bagian a kita diminta untuk membuat program perkalian matrix (4x3 dengan 3x6) dan menampilkan hasilnya. Matriks nantinya akan berisi angka 1-20 (tidak perlu dibuat filter angka):

Output:

![Gambar output bagian a](https://github.com/sisopd11/soal-shift-sisop-modul-3-D11-2021/blob/main/soal2/soal2a.png)

### b: Jawaban dan Penjelasan
Pada soal bagian b kita diminta untuk membuat program dengan menggunakan matriks output dari program sebelumnya (program soal2a.c) (Catatan!: gunakan shared memory). Kemudian matriks tersebut akan dilakukan perhitungan dengan matrix baru (input user) sebagai berikut contoh perhitungan untuk matriks yang a	da. Perhitungannya adalah setiap cel yang berasal dari matriks A menjadi angka untuk faktorial, lalu cel dari matriks B menjadi batas maksimal faktorialnya matri(dari paling besar ke paling kecil) (Catatan!: gunakan thread untuk perhitungan di setiap cel):

Output:

![Gambar output bagian b](https://github.com/sisopd11/soal-shift-sisop-modul-3-D11-2021/blob/main/soal2/soal2b.png)

### c: Jawaban dan Penjelasan
Pada soal bagian c diminta untuk membuat program (soal2c.c) untuk mengecek 5 proses teratas apa saja yang memakan resource komputernya dengan command “ps aux | sort -nrk 3,3 | head -5” (Catatan!: Harus menggunakan IPC Pipes)

Output:

![Gambar output bagian c](https://github.com/sisopd11/soal-shift-sisop-modul-3-D11-2021/blob/main/soal2/soal2c.png)

## Kendala
1. Masih belum bisa menghitung faktorial dengan tepat (soal2b.c)

## Soal No.3
  Seorang mahasiswa bernama Alex sedang mengalami masa gabut. Di saat masa gabutnya, ia memikirkan untuk merapikan sejumlah file yang ada di laptopnya. Karena jumlah filenya terlalu banyak, Alex meminta saran ke Ayub. Ayub menyarankan untuk membuat sebuah program C agar file-file dapat dikategorikan. Program ini akan memindahkan file sesuai ekstensinya ke dalam folder sesuai ekstensinya yang folder hasilnya terdapat di working directory ketika program kategori tersebut dijalankan.
  
### Soal
- A. Program menerima opsi -f seperti contoh di bawah, jadi pengguna bisa menambahkan argumen file yang bisa dikategorikan sebanyak yang diinginkan oleh pengguna.
	
	```
	# Program soal3 terletak di /home/izone/soal3
	$ ./soal3 -f path/to/file1.jpg path/to/file2.c path/to/file3.zip
	#Hasilnya adalah sebagai berikut
	/home/izone
	|-jpg
	|--file1.jpg
	|-c
	|--file2.c
	|-zip
	|--file3.zip
	```
	
	Program akan mengeluarkan Output sebagai berikut :
	
	```
	-File 1 : Berhasil Dikategorikan (jika berhasil)
	-File 2 : Sad, gagal :( (jika gagal)
	-File 3 : Berhasil Dikategorikan
	```
	
- B.Program juga dapat menerima opsi -d untuk melakukan pengkategorian pada suatu directory. Namun pada opsi -d ini, user hanya bisa memasukkan input 1 directory saja, 	    tidak seperti file yang bebas menginput file sebanyak mungkin. Contohnya adalah seperti ini :
	
	```
	$ ./soal3 -d /path/to/directory/
	```
	Perintah di atas akan mengkategorikan file di /path/to/directory, lalu hasilnya akan disimpan di working directory dimana program C tersebut berjalan (hasil kategori 		filenya bukan di /path/to/directory).
	Output yang dikeluarkan adalah seperti ini :
	```
	- Jika berhasil, print “Direktori sukses disimpan!”
	- Jika gagal, print “Yah, gagal disimpan :(“
	```
- C. Selain menerima opsi-opsi di atas, program ini menerima opsi *, contohnya ada di bawah ini:
	```
	$ ./soal3 \*
	```
	Opsi ini akan mengkategorikan seluruh file yang ada di working directory ketika menjalankan program C tersebut.

- D. Semua file harus berada di dalam folder, jika terdapat file yang tidak memiliki ekstensi, file disimpan dalam folder “Unknown”. Jika file hidden, masuk folder “Hidden”.
- E. Setiap 1 file yang dikategorikan dioperasikan oleh 1 thread agar bisa berjalan secara paralel sehingga proses kategori bisa berjalan lebih cepat.

	Namun karena Ayub adalah orang yang hanya bisa memberi ide saja, tidak mau bantuin buat bikin programnya, Ayub meminta bantuanmu untuk membuatkan programnya. Bantulah agar program dapat berjalan!

Catatan: 

- Kategori folder tidak dibuat secara manual, harus melalui program C
- Program ini tidak case sensitive. Contoh: JPG dan jpg adalah sama
- Jika ekstensi lebih dari satu (contoh “.tar.gz”) maka akan masuk ke folder dengan titik terdepan (contoh “tar.gz”)
- Dilarang juga menggunakan fork-exec dan system()
- Bagian b dan c berlaku rekursif

### Jawaban :

- Fungsi toLower

```
char toLower(char* str)
{
	 for(int i = 0; i<strlen(str); i++)
            {
                if(str[i]>64 && str[i]<91)
		    str[i]+=32;
            }
}

```

Fugnsi toLower berfungsi untuk melakukan pengecekan pada setiap huruf dari string, jadi pada fungsi ini akan dibuat perulangan sepanjang panjang dari string, setelah itu dicek apabila string masih berbentuk huruf kapital maka akan ditambah dengan 32 agar menjadi huruf kecil.

- Fungsi getFileExt

```
void getFileExt(char* fileName, char *exten)
{
    char *ext = strchr(fileName, '.');
    if (ext == NULL) {
        strcpy(exten,"Unknown");
    } 
    else if (ext == fileName){
        strcpy(exten,"Hidden");
    }
    else
    {
        strcpy(exten,ext+1);
    }
}
```

Fungsi getFileExt berfungsi untuk mendapatkan eksistensi dari file. Pada fungsi ini pertama kita mendeklarasikan variabel ```ext``` kemudian menggunakan strchr untuk mendapatkan . pada file. Kemudian di cek apabila ```ext==NULL``` maka kita mengcopy Unknown ke exten. Setelah itu kita cek apabila ```ext==fileName``` maka kita akan mencopy Hidden kedalam exten. dan selain daripada itu maka kita akan mencopy ext+1(menggunakan plus 1 agar tanda ext(.) tidak ikut) ke dalam exten.

- Fungsi checkFile
```
bool checkFile(char *basePath)
{
    struct stat buffer;
    int exist = stat(basePath,&buffer);
    if(exist == 0)
    {
        if( S_ISREG(buffer.st_mode) ) return true;
        else return false;
    }
    else  
        return false;
}
```
Fungsi checkFile berfungsi untuk mengecek file apakah file termasuk file regular atau tidak. Pertama kita akan membuat variabel exist untuk menampung apakah file ada atau tidak, kemudian kita cek ```if(exist == 0)``` kita lakukan pengecekan kembali  ```if( S_ISREG(buffer.st_mode) ) return true;``` apabila file yang tersedia merupakan file regular maka return true namun apabila bukan file regular return false. Kemudian di cek apabila file tidak tersedia maka return false.

- Fungsi moveFile
```
void *moveFile(void *arg)
{
    char basePath[PATH_MAX];
    strcpy(basePath,(char *) arg);

    if(checkFile(basePath))
    {
        char *i,*b;
        char fullPath[PATH_MAX];
        strcpy(fullPath,(char *) arg);

        char fileName[100];

        for(i=strtok_r(fullPath,"/",&b); i!=NULL; i=strtok_r(NULL,"/",&b)) 
	{
            memset(fileName,0,sizeof(fileName));
            strcpy(fileName,i);
        }

        char ext[PATH_MAX];
        getFileExt(fileName,ext);

        if(strcmp(ext,"Hidden") != 0 && strcmp(ext,"Unknown") != 0)
        {
            toLower(ext);
        }
        char workDir[PATH_MAX];
        if (getcwd(workDir, sizeof(workDir)) == NULL)
	{
            perror("getcwd() error");
            return (void *) 0;
        }

       
        char destDir[PATH_MAX];
        sprintf(destDir,"%s/%s",workDir,ext);
        
        mkdir(destDir,0777);

        char destination[PATH_MAX];
        sprintf(destination,"%s/%s/%s",workDir,ext,fileName);
       
        rename(basePath,destination);
        
        return (void *) 1;
    }

    else return (void *) 0;
}
```

Fungsi moveFile berfungsi untuk memindahkan file ke dalam suatu direktori di dalam working direcrtory. Pada fungsi ini pertama kita akan mencopy argumen ke dalam variabel basePath. Setelah itu kita cek apakah file tersedia dan merupakan regular file. Jika iya, maka pertama kita akna mengcopy argumen ke dalam variabel fullPath.Kemudian utnuk mendapatkan nama file kita lakukan perulangan menggunakan strtok untuk memisahkan ```/``` kemudian ```memset(fileName,0,sizeof(fileName)); strcpy(fileName,a);``` di memset menjadi 0 jadi selamabelum nol maka akan di copy sehingga nama yang paling belakang yang akan tersimpan nantinya. Setelah itu, kita akan mencari ekstensi dari file sehingga kita call fungsi checkFile seperti yang telah dijelaskan sebelumnya. Karena pada soal dikatakan program tidak besifat case sensitive maka kita kaan mengcall fungsi toLower. Untuk mendaptkan working directory kita dapat menggunakan ```getcwd(cwd, sizeof(cwd)``` setelah itu kita sprintf untuk menggabungkan ext dan filename ke dalam destinationDir dan kita sprintf kembali untuk mengabungkan ext,cwd, dan fileName ke dalam destination. Setelah semua ini kita dapat memindahkan destination ke basePath.

- Fungsi listFileRecursively
```
int listFilesRecursively(char *basePath, int *fileCount)
{
    char path[PATH_MAX];
    struct dirent *dp;
    DIR *dir = opendir(basePath);

    if (!dir)
        return 0;

    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
            char fullPath[PATH_MAX];
            sprintf(fullPath,"%s/%s",basePath,dp->d_name);
            //printf("%s\n", fullPath);
            if(checkExistAndRegFile(fullPath))
            {
                sprintf(fileList[*fileCount],"%s",fullPath);
                *fileCount += 1;
            }
            // Construct new path from our base path
            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);

            listFilesRecursively(path,fileCount);
        }
    }

    closedir(dir);
    return 1;
}
```

Pada fungsi ini kita akan mnegecek file yang ada daam folder secara rekursif. Pertama kita akan ```DIR *dir = opendir(basePath);``` membuka directory dari basePath. setelah itu di cek jika file bukan directory maka akan mereturn 0. Setelah itu, di lakukan perulangan untuk mengecek file, jika file ada dan merupakan file reguler maka akan  ```sprintf(fileList[*fileCount],"%s",fullPath); *fileCount += 1;``` untuk memindahkan fullPath ke dalam fileList sehingga semua file yang akan dicek nantinya akan masuk ke dalam fileList dan kemudian count+=1 untuk menghitung banyaknya file. Setelah itu, dilakukan rekursif untuk mengecek file yang lainnya.

- Untuk Opsi -f
```
int main(int argc,char* argv[])
{

    char baseDir[PATH_MAX];

    if(strcmp(argv[1],"-f")==0) 
    {
	int i=2;

		while(argv[i]!=NULL)
		{
		    pthread_create( &(tid[i-2]), NULL, moveFile, (void*) argv[i]);
		    i++;
		}

		for (int j=0;j<(i-2);j++)
		{
		    long cek;
		    void *ptr;
		    pthread_join( tid[j], &ptr);
		    cek = (long) ptr;
		    if(cek) printf("File %d : Berhasil Dikategorikan\n", j+1);
		    else printf("File %d : Sad, gagal :(\n", j+1);
		}
        
        return 0;
    }
```
Apabila user menginputkan opsi(-f) maka akan dilakukan perulangan selama argumen value != NULL untuk membuat ``` pthread_create( &(tid[i-2]), NULL, moveFile, (void*) argv[i]);``` kemudian kita akan melakukan perulangan kedua untuk j=0 hingga i-2 untuk melakukan join setelah itu ilakukan pengecekan ```if(cek)``` maka mencetak file ke-j berhasil dikategorikan namun apabila !cek maka mencetak file ke-j Sad,gagal :(.

- Untuk Opsi -d
```
else if(strcmp(argv[1],"-d")==0) 
    {
	int cekFile,count_file = 0;
        strcpy(baseDir,argv[2]);
	cekFile = listFilesRecursively(baseDir, &count_file);
    	for(int i = 0; i<count_file; i++)
    	{
        	pthread_create( &(tid[i]), NULL, moveFile, (void*) fileList[i]);
   	}

   	for (int i = 0; i < count_file; i++)
    	{
        	void *ptr;
        	pthread_join( tid[i], &ptr);
    	}

	if(!cekFile)
    	{
		printf("Yah, gagal disimpan :(\n");
		return 0;
    	}
	else
	{
		
    		printf("Direktori sukses disimpan!\n");
    	}
    }

```
Apabila user menginputkan opsi(-d) maka argumen value akan di copy ke baseDir, kemudian untuk mengecek file di dalam folder dilakukan secara rekursif menggunakan fungsi listFilesRecursively seperti yang telah dijelaskan sebelumnya. Kemudian dilakukan perulangan untuk membuat thread mulai dari 0 hingga count_file kemudian di joinkan. setelah itu dicek jika folder tidak ada maka cetak Yah, gagal disimpan. Sementara itu, jika file tersebut ada maka cetak Direktori sukses disimpan!.

- Untuk Opsi \*
```
else if(strcmp(argv[1],"*")==0)
    {
	int count_file=0;
        getcwd(baseDir,sizeof(baseDir));
	int cekFile = listFilesRecursively(baseDir, &count_file);
    	for(int i = 0; i<count_file; i++)
    	 {
        	pthread_create( &(tid[i]), NULL, moveFile, (void*) fileList[i]);
   	 }

   	 for (int i = 0; i < count_file; i++)
    	{
        	void *ptr;
        	pthread_join( tid[i], &ptr);
    	}

    }
```
Apabila user menginputkan \* maka akan dilakukan seperti opsi d tadi menggunakan fungsi rekursif akan tetapi pada opsi ini directory yang yang akan di passing berasal dari   ```getcwd(baseDir,sizeof(baseDir));``` selebihnya sama seperti yang sudah dijelaskan dari opsi -d diatas.

- Untuk Mengkategorikan File Hidden dan File Unknown
```
void getFileExt(char* fileName, char *exten)
{
    char *ext = strchr(fileName, '.');
    if (ext == NULL) {
        strcpy(exten,"Unknown");
    } 
    else if (ext == fileName){
        strcpy(exten,"Hidden");
    }
    else
    {
        strcpy(exten,ext+1);
    }
}
```

Fungsi getFileExt berfungsi untuk mendapatkan eksistensi dari file. Pada fungsi ini pertama kita mendeklarasikan variabel ```ext``` kemudian menggunakan strchr untuk mendapatkan . pada file. Kemudian di cek apabila ```ext==NULL``` maka kita mengcopy Unknown ke exten. Setelah itu kita cek apabila ```ext==fileName``` maka kita akan mencopy Hidden kedalam exten. dan selain daripada itu maka kita akan mencopy ext+1(menggunakan plus 1 agar tanda ext(.) tidak ikut) ke dalam exten.

- Setiap 1 file yang dikategorikan dioperasikan oleh 1 thread agar bisa berjalan secara paralel sehingga proses kategori bisa berjalan lebih cepat.

### Output Program

Untuk menjalankan program kita dapat melakukan:

```gcc -pthread soal3.c -o soall```

```./soall -f /home/dewi/modul3/soal3/sdyasdas.JPG /home/dewi/modul3/soal3/anything.tar.gz``` kemudian kita coba menjalankannya lagi untuk melihat hasil dari proses yang gagal ```./soall -f /home/dewi/modul3/soal3/sdyasdas.JPG /home/dewi/modul3/soal3/anything.tar.gz```` berikut outputnya :

![modul3-1](https://user-images.githubusercontent.com/80894892/118941318-2b682800-b984-11eb-8edc-d1ffd61bf6cb.png)

![modul3-3](https://user-images.githubusercontent.com/80894892/118941871-c3661180-b984-11eb-8503-ebc8ee61ff18.png)

![modul3-4](https://user-images.githubusercontent.com/80894892/118941915-d11b9700-b984-11eb-95c2-377bb661c423.png)

![modul3-5](https://user-images.githubusercontent.com/80894892/118941966-de388600-b984-11eb-8e3f-998fed19730d.png)

![modul3-2](https://user-images.githubusercontent.com/80894892/118942018-eabcde80-b984-11eb-83be-3302439e5de1.png)

```./soal3 -d /home/dewi/modul3/soal3``` atau ```./soal3 -d /home/dewi/modul3/folderngawur```
![modul3-6](https://user-images.githubusercontent.com/80894892/118942400-44250d80-b985-11eb-97c2-8e889a070598.png)

![modul3-7](https://user-images.githubusercontent.com/80894892/118942408-45563a80-b985-11eb-9440-671c12faa6a7.png)

Dapat diperhatikan bahwa disini terbentuk file Hidden dan juga file Unknown 

![modul3-8](https://user-images.githubusercontent.com/80894892/118942410-45eed100-b985-11eb-95c2-2f54619430ad.png)

```./soal3 \* ```

![modul3-9](https://user-images.githubusercontent.com/80894892/118942545-6880ea00-b985-11eb-9f6e-8701cf0ff951.png)


