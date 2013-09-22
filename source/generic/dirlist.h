const int maxdirentrys = 500;
class direntry{
	public:
		char filename[256];
		bool folder;
		int extrainfoint;
		direntry(char* filename2);};
direntry::direntry(char* filename2){
	sprintf_s(filename,"%s",filename2);
	folder=0;
	extrainfoint=0;}
direntry *direntrys[maxdirentrys];
int n_direntrys = 0;

void deletedirentry(int number){
	delete direntrys[number];
	direntrys[number]=NULL;
	if(number<n_direntrys-1)for(int a=number;a<n_direntrys;a++)direntrys[a]=direntrys[a+1];
	direntrys[n_direntrys-1]=NULL;
	n_direntrys=n_direntrys-1;
}

void dirlist(char* directory){
	while(n_direntrys)deletedirentry(0);
	char filename[MAX_PATH];
	WIN32_FIND_DATAA findFileData;
	HANDLE hFind = FindFirstFileA(directory,&findFileData);
	if(hFind != INVALID_HANDLE_VALUE){
		bool endoflist=0;
		while(endoflist==0){
			sprintf_s(filename,"%s",findFileData.cFileName);
			direntrys[n_direntrys] = new direntry((char*)filename);
			if(findFileData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)direntrys[n_direntrys]->folder=1;
			n_direntrys++;
			if(FindNextFileA(hFind,&findFileData)==0)endoflist=1;
		}
	}
}
