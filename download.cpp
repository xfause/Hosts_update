#include <stdio.h>
#include <windows.h>
#include <wininet.h>
#include <ctime>
#include <cstring>
#include <string>
#include <iostream>
#define MAXBLOCKSIZE 1024
#pragma comment(lib,"Wininet.lib")
/**
* 执行 文件下载 操作
* @param Url: The target action url
*
*/
using namespace std;
void download(const char *Url){
    HINTERNET hSession = InternetOpen("IE", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
    if (hSession != NULL){
        HINTERNET handle2 = InternetOpenUrl(hSession, Url, NULL, 0, INTERNET_FLAG_DONT_CACHE, 0);
        if (handle2 != NULL){
            printf("%s\n",Url);
            byte Temp[MAXBLOCKSIZE];
            ULONG Number = 1;

            FILE *stream;
            if( (stream = fopen( "C:\\Windows\\System32\\drivers\\etc\\hosts", "wb" )) != NULL ){
                printf("open success\n");
                while (Number > 0){
                    InternetReadFile(handle2, Temp, MAXBLOCKSIZE - 1, &Number);
                    fprintf(stream, (const char*)Temp);
                    //fwrite(Temp, sizeof (char), Number , stream);
                }
                fclose( stream );
            }
            InternetCloseHandle(handle2);
            handle2 = NULL;
        }
        InternetCloseHandle(hSession);
        hSession = NULL;
        printf("download success\n");
    }
}
//int argc, char* argv[]
void Fordownload(){
    if(1){
        download("https://raw.githubusercontent.com/racaljk/hosts/master/hosts");
    }else{
        printf("Usage: auto-Update url");
    }
}
void rewrite_new(){
    char str[255];
    FILE* fstream_in;
    FILE* fstream_out;
    fstream_in=fopen("C:\\Windows\\System32\\drivers\\etc\\hosts","rt");
    fstream_out=fopen("C:\\Windows\\System32\\drivers\\etc\\hosts_new","wt");
    while(!feof(fstream_in)){
		fgets(str,1024,fstream_in);
		fprintf(fstream_out,"%s",str);
	}
    fclose(fstream_in);
    fclose(fstream_out);
}
void rewrite_back(){
    char str[255];
    FILE* fstream_in;
    FILE* fstream_out;
    fstream_in=fopen("C:\\Windows\\System32\\drivers\\etc\\hosts_new","rt");
    fstream_out=fopen("C:\\Windows\\System32\\drivers\\etc\\hosts","wt");
    while(!feof(fstream_in)){
		fgets(str,1024,fstream_in);
		fprintf(fstream_out,"%s",str);
	}
    fclose(fstream_in);
    fclose(fstream_out);
}
void delete_new(){
    remove("C:\\Windows\\System32\\drivers\\etc\\hosts_new");
}
void Backup(){
    tm *year;
	time_t t;
	t=time(0);
	year=localtime(&t);
	int true_year=(year->tm_year+1900); // get year
	tm *month;
	t=time(0);
	month=localtime(&t);
	int true_month=(month->tm_mon+1); // get month
	tm *day;
	t=time(0);
	day=localtime(&t);
	int true_day=(day->tm_mday); // get day

    // for new file name
    char tra_year[10],tra_month[10],tra_day[10];
    sprintf(tra_year, "%d", true_year);
    string new_year=tra_year;
    sprintf(tra_month, "%d", true_month);
    string new_month=tra_month;
    sprintf(tra_day, "%d", true_day);
    string new_day=tra_day;

    if (true_month<10) new_month='0'+new_month;
    string new_name=new_year+new_month+new_day;

    // new file
    FILE* fstream_in;
    FILE* fstream_out;
    string new_road="C:\\Windows\\System32\\drivers\\etc\\hosts_"+new_name;
    fstream_in=fopen("C:\\Windows\\System32\\drivers\\etc\\hosts","rt+");
    fstream_out=fopen(new_road.c_str(),"wt");
    char str[255];
    while(!feof(fstream_in)){
		fgets(str,1024,fstream_in);
		fprintf(fstream_out,"%s",str);
	}
    fclose(fstream_in);
	fclose(fstream_out);
}
int main(){
    Backup();
    //delete_old();
    Fordownload();
    rewrite_new();
    rewrite_back();
    delete_new();
    //int ErrorCode=GetLastError();
    //printf("%d\n",ErrorCode);
    //system("pause");
    return 0;
}
