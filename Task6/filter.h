#ifndef FILTER_H
#define FILTER_H
#include "date.h"
#include "article.h"

struct _filter;
typedef struct _filter *FilterP;
typedef struct _filter {
    DateP from;
    DateP to;
    char name[MAX_ARTICLE_NAME];
} Filter;

int InitializeFilter(FilterP filter);
FilterP CreateFilter(char *dateFromStr, char *dateToStr, char *articleName);
int DeleteFilter(FilterP filter);

#endif
