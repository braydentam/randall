#ifndef OPTIONS_H
#define OPTIONS_H

struct optionsObject{
    char* input;
    char* out;
    int nbytes;
};

void options(struct optionsObject* obj, int argc, char **argv);

#endif /* OPTIONS_H */