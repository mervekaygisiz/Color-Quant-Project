#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#define HI(num) (((num) & 0x0000FF00) >> 8)
#define LO(num) ((num) & 0x000000FF)

typedef struct _PGMData {
	int row;
	int col;
	int max_gray;
	int **matrix;
} PGMData;

float** distanceMatris(int boyut, float dizi[]);
void yazdir(float **, int);
float enKucukDeger(float **dist, int *satir, int *sutun, int boyut);
void updateUnique(float *sirali, float ort, float sayi1, float sayi2, int boyut);
void updateMatris(float **matris, float ort, float sayi1, float sayi2);
void bubbleSort(float *dizi,int boyut);
int elemanSayisi;
int **allocate_dynamic_matrix(int, int);
void SkipComments(FILE*);
PGMData* readPGM(const char*,PGMData*);
void writePGM(const char*,const PGMData*);

int n,m;

int main(){
	PGMData *kappa;
	kappa = (PGMData*)malloc(sizeof(PGMData));
	char pgmINPUT[30],pgmOUTPUT[30];
	printf("Resmin ismini uzantisi ile birlikte giriniz :");
	gets(pgmINPUT);
	kappa = readPGM(pgmINPUT, kappa);
	printf("Olusturalacak olan resmin ismini uzantisi ile birlikte giriniz :");
	gets(pgmOUTPUT);
	
	
	
	float **matris;
	float *sirali;
	float *dizi;
	int renkSayisi;
	int i = 0, j = 0, k = 0, temp = 0;
	n=kappa->row;
	m=kappa->col;
	
	matris= (float **)malloc(n*sizeof(float *)); //matrise dinamik olarak yer ayýrdýk
	
	if(matris==NULL)
	{
		printf("Matris/Bellekte yer acilamadi!\n");
	}

	for (i = 0; i < m; i++)
	{
		matris[i] =(float*)malloc(sizeof(float)*m);
	}
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			matris[i][j]=kappa->matrix[i][j];
		}
	}
	
	
	dizi=(float*)malloc(sizeof(float)*(m*n));  //dizi icin hafýzada yer actýk
	if(dizi==NULL)
	{
		printf("Dizi /Bellekte yer acilamadi!\n");
	}
	
	sirali=(float*)malloc(sizeof(float)*(m*n));   //sirali icin bellekten yer actýk
	if(sirali==NULL)
	{
		printf("Sirali/Dizi /Bellekte yer acilamadi!\n");
	}
	
	
	printf("Renk sayisini giriniz :\n");
	scanf("%d",&renkSayisi);
	
	

	/*for (i = 0; i<n; i++)
	{
		for (j = 0; j<m; j++)
		{
			matris[i][j] = rand() % 10;
		}

	}*/


	/*for (i = 0; i<n; i++)
	{
		for (j = 0; j<m; j++)
		{
			printf("%5.2f", matris[i][j]);
		}
		printf("\n");
	}*/
//	puts("\n--------------------------------");








	for (i = 0; i<n; i++)    //matrisi diziye atad¨k
	{
		for (j = 0; j<m; j++)
		{
			dizi[k] = matris[i][j];
			k++;
		}

	}
	
//	puts("\n------------------");

   /*  for(i=0;i<m*n;i++)   //diziyi yazdirdik
	printf("%5.1f",dizi[i]);*/
	

    bubbleSort(dizi,m*n);

//	puts("");

/*	for (i = 0; i<n*m; i++)   //diziyi yazdirdik
		printf("%5.2f", dizi[i]);*/
		



	k = 0;       //uniqe yaptýk
	i = 0;

	sirali[k] = dizi[i++];
	
	while (i<(m*n))
	{
		if (dizi[i] == sirali[k])
		{	//printf("\n%f     %f\n",sirali[k],dizi[i]);
			i++;
			continue;
		}
		else{
			//printf("\n%f     %f\n",sirali[k],dizi[i]);
			sirali[++k] = dizi[i];

			i++;

		}

	}
	
    elemanSayisi = k+1; //unique dizisinin boyu
    
/*	printf("\n----------------Unique dizi------------------------\n");
	for (i = 0; i<elemanSayisi ; i++)   //diziyi yazdirdik
		printf("%5.2f", sirali[i]);*/


	
	float **dist;
	float enk;
	int bas = 0, bitis = 0;
	int *satir = &bas, *sutun = &bitis;
	float ort;
	int l=0;
	
	int sayac=elemanSayisi+1;


	while (sayac-1>renkSayisi){
        
		dist = distanceMatris(sayac, sirali);  //distance matrisi oluþturduk.
	//	yazdir(dist, sayac);
		enk = enKucukDeger(dist, satir, sutun, sayac);

//		printf("\nDistance matrisindeki  kucuk deger: %2.f\n", enk);


//		printf("\n%d   %d", *satir, *sutun);


//		printf("\n%f   %f\n", dist[*satir][0], dist[0][*sutun]);
		ort = (dist[*satir][0] + dist[0][*sutun]) / 2;
//		printf("\nort: %.6f\n", ort);


		updateUnique(sirali, ort, dist[*satir][0], dist[0][*sutun], sayac);
		sayac--;
		updateMatris(matris, ort, dist[*satir][0], dist[0][*sutun]);
	}
//	puts("");
/*	for (i = 0; i<elemanSayisi ; i++)   //diziyi yazdirdik
		printf("%5.2f", sirali[i]);*/





	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			kappa->matrix[i][j]=matris[i][j];
		}
	}

//	puts("\n-----------------------------");
/*	for (i = 0; i<n; i++)
	{
		for (j = 0; j<m; j++)
		{
			printf("%5.2f", matris[i][j]);
		}
		printf("\n");
	}*/
	//system("PAUSE");
	writePGM(pgmOUTPUT, kappa);
	return 0;
}
int **allocate_dynamic_matrix(int row, int col)
{
	int **ret_val;
	int i;

	ret_val = (int **)malloc(sizeof(int *) * row);
	if (ret_val == NULL) {
		perror("memory allocation failure");
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < row; ++i) {
		ret_val[i] = (int *)malloc(sizeof(int) * col);
		if (ret_val[i] == NULL) {
			perror("memory allocation failure");
			exit(EXIT_FAILURE);
		}
	}

	return ret_val;
}

void deallocate_dynamic_matrix(int **matrix, int row)
{
	int i;

	for (i = 0; i < row; ++i)
		free(matrix[i]);
	free(matrix);
}
void SkipComments(FILE *fp)
{
	int ch;
	char line[100];

	while ((ch = fgetc(fp)) != EOF && isspace(ch))
		;
	if (ch == '#') {
		fgets(line, sizeof(line), fp);
		SkipComments(fp);
	}
	else
		fseek(fp, -1, SEEK_CUR);
}
PGMData* readPGM(const char *file_name, PGMData *data)
{
	FILE *pgmFile;
	char version[3];
	int i, j;
	int lo, hi;

	pgmFile = fopen(file_name, "rb");
	if (pgmFile == NULL) {
		perror("cannot open file to read");
		exit(EXIT_FAILURE);
	}

	fgets(version, sizeof(version), pgmFile);
	if (strcmp(version, "P5")) {
		fprintf(stderr, "Wrong file type!\n");
		exit(EXIT_FAILURE);
	}

	SkipComments(pgmFile);
	fscanf(pgmFile, "%d", &data->col);
	SkipComments(pgmFile);
	fscanf(pgmFile, "%d", &data->row);
	SkipComments(pgmFile);
	fscanf(pgmFile, "%d", &data->max_gray);
	fgetc(pgmFile);

	data->matrix = allocate_dynamic_matrix(data->row, data->col);
	if (data->max_gray > 255)
		for (i = 0; i < data->row; ++i)
			for (j = 0; j < data->col; ++j) {
				hi = fgetc(pgmFile);
				lo = fgetc(pgmFile);
				data->matrix[i][j] = (hi << 8) + lo;
			}
	else
		for (i = 0; i < data->row; ++i)
			for (j = 0; j < data->col; ++j) {
				lo = fgetc(pgmFile);
				data->matrix[i][j] = lo;
			}

	fclose(pgmFile);
	return data;
}
void writePGM(const char *filename, const PGMData *data)
{
	FILE *pgmFile;
	int i, j;
	int hi, lo;

	pgmFile = fopen(filename, "wb");
	if (pgmFile == NULL) {
		perror("cannot open file to write");
		exit(EXIT_FAILURE);
	}

	fprintf(pgmFile, "P5 ");
	fprintf(pgmFile, "%d %d ", data->col, data->row);
	fprintf(pgmFile, "%d ", data->max_gray);

	if (data->max_gray > 255) {
		for (i = 0; i < data->row; ++i) {
			for (j = 0; j < data->col; ++j) {
				hi = HI(data->matrix[i][j]);
				lo = LO(data->matrix[i][j]);
				fputc(hi, pgmFile);
				fputc(lo, pgmFile);
			}

		}
	}
	else {
		for (i = 0; i < data->row; ++i)
			for (j = 0; j < data->col; ++j) {
				lo = LO(data->matrix[i][j]);
				fputc(lo, pgmFile);
			}
	}

	fclose(pgmFile);
	deallocate_dynamic_matrix(data->matrix, data->row);
}
float** distanceMatris(int boyut, float dizi[])
{
	int i, j, k = 0;
	float deger;

	//unique dizisinin eleman sayýsý

	float **dist; //bellekten uniquedeki farklý eleman sayisi kadar kare matris olusturdum.

	dist = (float **)malloc((boyut)*sizeof(float *));

	for (i = 0; i < (boyut); i++)
	{
		dist[i] = (float *)malloc(sizeof(float)*(boyut));
	}



	for (i = 1; i < boyut; i++) //distance matrisi oluþturma
	{
		dist[i][0] = dizi[k];
		dist[0][i] = dizi[k];
		k++;
	}


	for (i = 1; i < boyut; i++)
	{
		for (j = 1; j < boyut; j++)
		{
			


			if (i<j)
			{
                deger = dist[i][0] - dist[0][j];
				dist[i][j] = fabs(deger);
			}
		}

	}

	return dist;

}

void yazdir(float **matris, int boyut)
{
	int i, j;
	printf("\n\n");
	for (i = 0; i < boyut; i++)
	{
		for (j = 0; j < boyut; j++)
		{
			if (i<j)
				printf("%5.2f", matris[i][j]);

			else if (j == 0 && i != 0)
				printf("%5.2f", matris[i][j]);

			else
				printf("     ");
		}
		printf("\n");
	}

}

float enKucukDeger(float **dist, int *satir, int *sutun, int boyut)
{
	float enk = n*m;
	int i, j;

	for (i = 1; i < boyut; i++)
	{
		for (j = i+1; j < boyut; j++)
		{
			if (i<j && enk>dist[i][j])
			{
			
				enk = dist[i][j];
				*satir = i;
				*sutun = j;

				//	printf("\n%d  %d\n",*satir,*sutun);
			}

		}
	}

	return enk;
}

void updateUnique(float *sirali, float ort, float sayi1, float sayi2, int boyut){

	int i,index=0;
	

	for (i = 0; i<boyut-1; i++)
	{
		

		if (sirali[i] == sayi1 || sirali[i] == sayi2)
		{
			
			sirali[i] = ort;
	//		printf("\n-----------------%d -----%f\n",i,sirali[i]);
		}
		

	}
	
	bubbleSort(sirali,boyut);
	

	
	for (i = 0; i < boyut-1 ; i++){				//sirali diziyi guncelle
		if (sirali[i] == sirali[i + 1]){
			index = i;
			break;
		}
	}
	for (i = index; i < boyut-1 ; i++){
		sirali[i] = sirali[i + 1];
	}
	
	//printf("Sirali adli matrsi------------------------\n");

	
	/*for(i=0;i<boyut-1;i++)
	{
		printf("%.1f   ",sirali[i]);
	}
	puts("");*/
}

void updateMatris(float **matris, float ort, float sayi1, float sayi2){

	int i, 

		j;

	for (i = 0; i<n; i++)
	{for (j = 0; j<m; j++)
		{

			if (matris[i][j] == sayi1 || matris[i][j] == sayi2)
			{
				matris[i][j] = ort;
			}
		}
	}

}


void bubbleSort(float *dizi,int boyut)
{
    int i,j;
    float temp;
    
    for (i = 1; i<boyut; i++)    //diziyi siraladik
	{
		for (j = 0; j<(boyut-1) ; j++)
		{
			if (dizi[j]>dizi[j + 1])
			{
				temp = dizi[j];
				dizi[j] = dizi[j + 1];
				dizi[j + 1] = temp;


			}

		}

	}
        
    }
