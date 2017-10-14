using namespace std;
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include "imdb.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define NUM_OF_ACTORS (*(int*) actorFile)
#define NUM_OF_FILMS (*(int*) movieFile)

typedef pair <const void*, const void*> myStruct;

const char *const imdb::kActorFileName = "actordata";
const char *const imdb::kMovieFileName = "moviedata";


imdb::imdb(const string& directory)
{
	const string actorFileName = directory + "/" + kActorFileName;
	const string movieFileName = directory + "/" + kMovieFileName;

	actorFile = acquireFileMap(actorFileName, actorInfo);
	movieFile = acquireFileMap(movieFileName, movieInfo);
}

bool imdb::good() const
{
	return !( (actorInfo.fd == -1) || 
			(movieInfo.fd == -1) ); 
}

void toLowerCase(char &ch) {
	if (ch >= 'A' && ch <= 'Z') {
		ch = ch - 'A' + 'a';
	}
}

int comp(const void* keyBases, const void* offset) {
	
	myStruct pi = *(myStruct*) keyBases;
	const void* stringInFile = (char*)pi.first + *((int*)offset);
	const void* searchString = pi.second;

	
	for (int i = 0; ; i++) {
		char firstsChar = *((char*) searchString + i);
		char secondsChar = *((char*) stringInFile + i);
		toLowerCase(firstsChar); toLowerCase(secondsChar);
		if (firstsChar < secondsChar) return -1;
		if (firstsChar > secondsChar) return 1;
		if (firstsChar == 0 && secondsChar == 0) return 0;
	}
	return 0;
}

void getFilm(char* curFilmPtr, film &curFilm) {
	curFilm.title = string(curFilmPtr);
	int curFilmNameLen = strlen(curFilmPtr);
	curFilm.year = 1900 + *(curFilmPtr + curFilmNameLen + 1);
}

void getFilmsForActor(char* mvFile, char* curActorPtr, vector<film> &films) {
	int actorNameLen = strlen(curActorPtr) + 1;
	char* filmsCountPtr = curActorPtr + actorNameLen + ((actorNameLen) & 1);
	
	short filmCount = *((short*)filmsCountPtr);
	char* filmsStartPtr = (char*) filmsCountPtr + 2;
	
	if (((filmsStartPtr - curActorPtr) & 3) != 0) 
		filmsStartPtr = filmsStartPtr + 2;
	
	for (int i = 0; i < filmCount; i++) {
		film curFilm;
		int curFilmOffset = *((int*) (filmsStartPtr + i * sizeof(int)));
		
		getFilm(mvFile + curFilmOffset, curFilm);

		films.push_back(curFilm);
	}
}

bool imdb::getCredits(const string &player, vector<film> &films) const {
	myStruct savedData = make_pair(actorFile, &player[0]);
	void* findedActor = bsearch(&savedData, (char*) actorFile + sizeof(int), NUM_OF_ACTORS, sizeof(int), 
								(int (*)(const void*, const void*)) comp);
	
	if (findedActor == NULL)  return false;
	
	char* curActorPtr = (char*)actorFile + (*(int*)findedActor);

	getFilmsForActor((char*) movieFile, curActorPtr, films);

	return true;

}

bool imdb::getCast(const film& movie, vector<string>& players) const {
	
	return false; 
}

imdb::~imdb()
{
	releaseFileMap(actorInfo);
	releaseFileMap(movieInfo);
}

// ignore everything below... it's all UNIXy stuff in place to make a file look like
// an array of bytes in RAM.. 
const void *imdb::acquireFileMap(const string& fileName, struct fileInfo& info)
{
	struct stat stats;
	stat(fileName.c_str(), &stats);
	info.fileSize = stats.st_size;
	info.fd = open(fileName.c_str(), O_RDONLY);
	return info.fileMap = mmap(0, info.fileSize, PROT_READ, MAP_SHARED, info.fd, 0);
}

void imdb::releaseFileMap(struct fileInfo& info)
{
	if (info.fileMap != NULL) munmap((char *) info.fileMap, info.fileSize);
	if (info.fd != -1) close(info.fd);
}
