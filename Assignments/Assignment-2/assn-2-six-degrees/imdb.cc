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

#define NUM_OF_ACTORS (*(int *)actorFile)
#define NUM_OF_FILMS (*(int *)movieFile)

typedef pair<const void *, const void *> myStruct;

const char *const imdb::kActorFileName = "actordata";
const char *const imdb::kMovieFileName = "moviedata";

int fixPtr(int inc, int rem)
{
	rem--;
	inc += ((rem + 1 - (inc & rem)) & rem);
	return inc;
}

void getFilm(char *curFilmPtr, film &curFilm)
{
	curFilm.title = string(curFilmPtr);
	int curFilmNameLen = strlen(curFilmPtr);
	curFilm.year = 1900 + *(curFilmPtr + curFilmNameLen + 1);
}

void getActor(char *curActorPtr, string &curActor)
{
	curActor = string(curActorPtr);
}

int compForActors(const void *keyBases, const void *offset)
{

	myStruct pi = *(myStruct *)keyBases;
	const void *stringInFile = (char *)pi.first + *((int *)offset);
	const void *searchString = pi.second;

	return strcmp((char *)searchString, (char *)stringInFile);
}

int compForFilms(const void *keyBases, const void *offset)
{
	const void *movieFile = (*(myStruct *)keyBases).first;
	char *curMoviePtr = (char *)movieFile + (*(int *)offset);
	film curFilmInBase;
	curFilmInBase.title = string(curMoviePtr);
	curFilmInBase.year = 1900 + *(char *)(curMoviePtr + strlen(curMoviePtr) + 1);
	film curSearchFilm = *((film *)(*(myStruct *)keyBases).second);

	if (curSearchFilm < curFilmInBase)
		return -1;
	if (curFilmInBase < curSearchFilm)
		return 1;
	return 0;
}

void getFilmsForActor(char *mvFile, char *curActorPtr, vector<film> &films)
{
	char *itOfFile = curActorPtr + fixPtr(strlen(curActorPtr) + 1, 2);

	short filmCount = *((short *)itOfFile);
	itOfFile += 2;
	itOfFile = curActorPtr + fixPtr(itOfFile - curActorPtr, 4);

	for (int i = 0; i < filmCount; i++)
	{
		film curFilm;
		int curFilmOffset = *((int *)(itOfFile + i * sizeof(int)));

		getFilm(mvFile + curFilmOffset, curFilm);
		films.push_back(curFilm);
	}
}

void getActorsForFilm(char *actorFile, char *curMoviePtr, vector<string> &players)
{
	char *itOfFile = curMoviePtr;
	itOfFile += fixPtr(strlen(curMoviePtr) + 2, 2);

	size_t actorCount = *(short *)itOfFile;

	itOfFile += 2;
	itOfFile = curMoviePtr + fixPtr(itOfFile - curMoviePtr, 4);

	for (size_t i = 0; i < actorCount; i++)
	{
		string player;
		int curActorOffset = *((int *)(itOfFile + i * sizeof(int)));
		getActor(actorFile + curActorOffset, player);
		players.push_back(player);
	}
}

imdb::imdb(const string &directory)
{
	const string actorFileName = directory + "/" + kActorFileName;
	const string movieFileName = directory + "/" + kMovieFileName;

	actorFile = acquireFileMap(actorFileName, actorInfo);
	movieFile = acquireFileMap(movieFileName, movieInfo);
}

bool imdb::good() const
{
	return !((actorInfo.fd == -1) ||
			 (movieInfo.fd == -1));
}

bool imdb::getCredits(const string &player, vector<film> &films) const
{

	myStruct savedData = make_pair(actorFile, &player[0]);
	void *findedActor = bsearch(&savedData, (char *)actorFile + sizeof(int), NUM_OF_ACTORS, sizeof(int), compForActors);

	if (findedActor == NULL)
		return false;

	char *curActorPtr = (char *)actorFile + (*(int *)findedActor);
	getFilmsForActor((char *)movieFile, curActorPtr, films);

	return true;
}

bool imdb::getCast(const film &movie, vector<string> &players) const
{
	myStruct savedData = make_pair(movieFile, &movie);
	void *findedMovie = bsearch(&savedData, (char *)movieFile + sizeof(int), NUM_OF_FILMS, sizeof(int), compForFilms);

	if (findedMovie == NULL)
		return false;

	char *curMoviePtr = (char *)movieFile + (*(int *)findedMovie);
	getActorsForFilm((char *)actorFile, curMoviePtr, players);

	return true;
}

imdb::~imdb()
{
	releaseFileMap(actorInfo);
	releaseFileMap(movieInfo);
}

// ignore everything below... it's all UNIXy stuff in place to make a file look like
// an array of bytes in RAM..
const void *imdb::acquireFileMap(const string &fileName, struct fileInfo &info)
{
	struct stat stats;
	stat(fileName.c_str(), &stats);
	info.fileSize = stats.st_size;
	info.fd = open(fileName.c_str(), O_RDONLY);
	return info.fileMap = mmap(0, info.fileSize, PROT_READ, MAP_SHARED, info.fd, 0);
}

void imdb::releaseFileMap(struct fileInfo &info)
{
	if (info.fileMap != NULL)
		munmap((char *)info.fileMap, info.fileSize);
	if (info.fd != -1)
		close(info.fd);
}
